/********* UaMobileKeys.m Cordova Plugin Implementation *******/

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
#import <AudioToolbox/AudioServices.h>
#import <Cordova/CDV.h>

@interface UaMobileKeys : CDVPlugin {

}

@property(nonatomic) MobileKeysManager *mobileKeysManager;
@property(nonatomic) CLLocationManager *locationManager;
- (void)coolMethod:(CDVInvokedUrlCommand*)command;
- (void)startup:(CDVInvokedUrlCommand*)command;
- (void)isEndpointSetup:(CDVInvokedUrlCommand*)command;
- (void)setupEndpoint:(CDVInvokedUrlCommand*)command;
- (void)updateEndpoint:(CDVInvokedUrlCommand*)command;
- (void)listMobileKeys:(CDVInvokedUrlCommand*)command;
- (void)endpointInfo:(CDVInvokedUrlCommand*)command;
- (void)unregisterEndpoint:(CDVInvokedUrlCommand*)command;
- (void)startForegroundScanning:(CDVInvokedUrlCommand*)command;
- (void)stopScanning:(CDVInvokedUrlCommand*)command;
- (id)init:(CDVInvokedUrlCommand*)command;
@end

@implementation UaMobileKeys
  BOOL _applicationIsStarting;
  MobileKeysManager* _mobileKeysManager;
  NSArray<MobileKeysKey*> *_mobilekey;
  NSArray * _openingTypes;
  NSArray * _openingModesWithoutSeamless;
  static const NSTimeInterval minTimeBetweenConnections = 1.0;
  NSDate* _timeOfLastConnection;

  // CallbackIds
  NSString* _startupCallbackId;
  NSString* _setupEndpointCallbackId;
  NSString* _terminateEndpointCallbackId;
  NSString* _updateEndpointCallbackId;
  NSString* _scanCallbackId;
  NSString* _listKeysCallbackId;
  NSString* _endpointInfoCallbackId;

#pragma mark - SetupMethods
- (id)init:(CDVInvokedUrlCommand*)command {
    self = [super init];
    _startupCallbackId = command.callbackId;
    BOOL startupHasRun = YES;

    if (self) {
        if (_mobileKeysManager == nil) {
            startupHasRun = NO;
            _mobileKeysManager = [self createInitializedMobileKeysManager];
        }
        _timeOfLastConnection = [NSDate dateWithTimeIntervalSince1970:1.0];
        _openingModesWithoutSeamless=@[@(MobileKeysOpeningTypeProximity)];
    }

    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(handleEnteredBackground) name:UIApplicationDidEnterBackgroundNotification object:nil];
   
    if (startupHasRun == NO) {
        [_mobileKeysManager startup];
    } else {
        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"already_done"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
    
    return self;
}

- (MobileKeysManager *)createInitializedMobileKeysManager {
    NSString* applicationId = @"AAH.ONB.PRECERT.VIEW-SOFTWARE";
    NSString *version = [NSString stringWithFormat:@"%@-%@ (%@)", applicationId, [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"], [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]];
    NSDictionary *config = @{MobileKeysOptionApplicationId: applicationId, MobileKeysOptionVersion: version};

    return [[MobileKeysManager alloc] initWithDelegate:self options:config];
}

#pragma mark - Event listener functions
- (void)handleEnteredBackground {
    [self getKeysFromSeos];

    if (_mobileKeysManager.isScanning) {
        NSString* callbackId = _scanCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"background_entered"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];

        [_mobileKeysManager stopReaderScan];
    }
}

#pragma mark - SDK Methods
- (void)startup:(CDVInvokedUrlCommand*)command
{
    _startupCallbackId = command.callbackId;

    if (self) {
        _mobileKeysManager = [self createInitializedMobileKeysManager];
        _openingTypes =@[@(MobileKeysOpeningTypeEnhancedTap)];
    }

    [_mobileKeysManager startup];
}

- (void)isEndpointSetup:(CDVInvokedUrlCommand*)command
{
    _setupEndpointCallbackId = command.callbackId;
    NSError *error;
    BOOL setupComplete = [_mobileKeysManager isEndpointSetup:&error];
    NSString *setupCompleteString = setupComplete ? @"true" : @"false";

    if (error != nil) {
        [self handleEndpointSetupError:error];
    } else {
        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:setupCompleteString];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
    }
}

- (void)setupEndpoint:(CDVInvokedUrlCommand*)command
{
    _setupEndpointCallbackId = command.callbackId;
    NSString* invitationCode = [command.arguments objectAtIndex:0];

    if ([self isValidCode:invitationCode]) {
        [_mobileKeysManager setupEndpoint:invitationCode];
    }
}

- (void)updateEndpoint:(CDVInvokedUrlCommand*)command
{
    _updateEndpointCallbackId = command.callbackId;

    [_mobileKeysManager updateEndpoint];
}

- (void)listMobileKeys:(CDVInvokedUrlCommand*)command
{
    _listKeysCallbackId = command.callbackId;
    NSError *listKeysError;
    _mobilekey = [_mobileKeysManager listMobileKeys:&listKeysError];

    if (listKeysError != nil) {
        [self handleListKeysError:listKeysError];
    }

    NSString *strResultFromInt = [NSString stringWithFormat:@"%lu", _mobilekey.count];

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:strResultFromInt];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)endpointInfo:(CDVInvokedUrlCommand*)command
{
    _endpointInfoCallbackId = command.callbackId;
    NSError *error = nil;
    MobileKeysEndpointInfo *endpointInfo = [_mobileKeysManager endpointInfo:&error];

    if (error != nil) {
        [self handleEndpointInfoError:error];
    }

    NSInteger _seosId = [endpointInfo seosId];
    NSString *_seosIdString = [NSString stringWithFormat: @"%ld", (long)_seosId];
    NSDate *_lastSync = [endpointInfo lastServerSyncDate];
    NSString *_seosVersion = [endpointInfo seosAppletVersion];

    NSString *usefulInfo = [NSString stringWithFormat:@"%@,%@,%@", _seosIdString, _lastSync, _seosVersion];

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:usefulInfo];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)unregisterEndpoint:(CDVInvokedUrlCommand*)command
{    
    _terminateEndpointCallbackId = command.callbackId;
    
    [_mobileKeysManager unregisterEndpoint];
}

- (void)startForegroundScanning:(CDVInvokedUrlCommand*)command
{
    _scanCallbackId = command.callbackId;
    NSArray *_lockServiceCodes;
    _lockServiceCodes = @[@1, @2];
    NSError *error;

    if (_mobileKeysManager.isScanning) {
        [_mobileKeysManager stopReaderScan];
    }

    [_mobileKeysManager startReaderScanInMode:MobileKeysScanModeOptimizePowerConsumption supportedOpeningTypes:_openingModesWithoutSeamless lockServiceCodes:_lockServiceCodes error:&error];

    if (error) {
        switch (error.code) {
            case MobileKeysErrorCodeBluetoothLENotAvailable: {
                CDVPluginResult* pluginResult = nil;
                pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"No bluetooth available"];
                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                break;
            }
            default: [self handleScanningError:error];
            break;
        }
    }
}

- (void)stopScanning:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [_mobileKeysManager stopReaderScan];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"true"];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (BOOL) isEndpointSetup {
    NSError *error;
    BOOL setupComplete = [_mobileKeysManager isEndpointSetup:&error];

    return setupComplete;
}

#pragma mark - Callback methods
- (void)mobileKeysDidStartup {
    NSString* callbackId = _startupCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    if (_applicationIsStarting) {
        _applicationIsStarting = NO;
    }

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"true"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (void)mobileKeysDidFailToStartup:(NSError *)error {
    [self handleStartupError:error];
}

- (void) mobileKeysDidSetupEndpoint {
    NSString* callbackId = _setupEndpointCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    CDVPluginResult* pluginResult = nil;
    if (!self.isEndpointSetup) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"true"];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (void)mobileKeysDidFailToSetupEndpoint:(NSError * ) error {
    [self handleEndpointSetupError:error];
}

- (void)mobileKeysDidUpdateEndpoint {
    NSString* callbackId = _updateEndpointCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"true"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

// Will be triggered after mobileKeysDidUpdateEndpoint, so this isn't important for our use case right now
- (void)mobileKeysDidUpdateEndpointWithSummary:(MobileKeysEndpointUpdateSummary *) endpointUpdateSummary {
    // NSString* callbackId = _updateEndpointCallbackId;
    // if (callbackId.length == 0) {
    //     callbackId = @"Found no callbackId";
    // }

    // CDVPluginResult* pluginResult = nil;
    // pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];
    // [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (void)mobileKeysDidFailToUpdateEndpoint:(NSError *)error {
    [self handleUpdateEndpointError:error];
}

- (void)mobileKeysDidTerminateEndpoint {
    NSString* callbackId = _terminateEndpointCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Terminated"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (void)mobileKeysDidConnectToReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type {
    NSString* callbackId = _scanCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    BOOL enoughTimeHasPassed = ([[NSDate date] timeIntervalSinceDate:_timeOfLastConnection] > minTimeBetweenConnections);
    if (enoughTimeHasPassed) {
        AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);
    }
}

- (void)mobileKeysDidFailToConnectToReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type openingStatus:(MobileKeysOpeningStatusType)status {
    NSString* callbackId = _scanCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Failed to connect to reader"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (void)mobileKeysDidDisconnectFromReader:(MobileKeysReader * )reader openingType:(MobileKeysOpeningType)type openingResult:(MobileKeysOpeningResult *)result {
    NSString* callbackId = _scanCallbackId;
    if (callbackId.length == 0) {
        callbackId = @"Found no callbackId";
    }

    AudioServicesPlayAlertSound(kSystemSoundID_Vibrate);

	// To allow the 'background_entered CDVPluginResult' to hit the UA startForegroundScanning callback (UNIE-959)
    // CDVPluginResult* pluginResult = nil;
    // pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"true"];
    // [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

- (BOOL)mobileKeysShouldAttemptToOpen:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type {
    return YES;
}

#pragma mark - Error handling
- (void)handleStartupError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _startupCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleEndpointSetupError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _setupEndpointCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleUnregisterEndpointError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _terminateEndpointCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleUpdateEndpointError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _updateEndpointCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleListKeysError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _listKeysCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleEndpointInfoError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _endpointInfoCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

- (void)handleScanningError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _scanCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"false"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

#pragma mark - Helper methods
- (BOOL)isValidCode:(NSString *)code {
    NSString *validPattern = @"^[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}$";
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:validPattern options:0 error:nil];
    
    return (code != nil) && ([regex firstMatchInString:code options:0 range:NSMakeRange(0, code.length)] != nil);
}

- (void)getKeysFromSeos {
    NSError *error = nil;
    _mobilekey = [[_mobileKeysManager listMobileKeys:&error] mutableCopy];
}

#pragma mark - Test methods
- (void)coolMethod:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    NSString* echo = [command.arguments objectAtIndex:0];

    if (echo != nil && [echo length] > 0) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:echo];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

@end
