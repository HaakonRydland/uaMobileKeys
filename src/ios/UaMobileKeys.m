/********* UaMobileKeys.m Cordova Plugin Implementation *******/

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
#import <Cordova/CDV.h>

@interface UaMobileKeys : CDVPlugin {

}

@property(nonatomic) MobileKeysManager *mobileKeysManager;
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

  // CallbackIds
  NSString* _startupCallbackId;
  NSString* _setupEndpointCallbackId;
  NSString* _terminateEndpointCallbackId;
  NSString* _updateEndpointCallbackId;

#pragma mark - SetupMethods
- (id)init:(CDVInvokedUrlCommand*)command {
    self = [super init];

    if (self) {
        _mobileKeysManager = [self createInitializedMobileKeysManager];
        _openingTypes =@[@(MobileKeysOpeningTypeEnhancedTap)];
    }

    [_mobileKeysManager startup];
    
    return self;
}

- (MobileKeysManager *)createInitializedMobileKeysManager {

    NSString* applicationId = @"UaMobileKeys";
    NSString *version = [NSString stringWithFormat:@"%@-%@ (%@)", applicationId, [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"], [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]];
    NSDictionary *config = @{MobileKeysOptionApplicationId: applicationId, MobileKeysOptionVersion: version};

    return [[MobileKeysManager alloc] initWithDelegate:self options:config];
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
    NSString *setupCompleteString = setupComplete ? @"True" : @"False";

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

    CDVPluginResult* pluginResult = nil;
    if ([self isValidCode:invitationCode]) {
        [_mobileKeysManager setupEndpoint:invitationCode];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Invalid code"];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)updateEndpoint:(CDVInvokedUrlCommand*)command
{
    _updateEndpointCallbackId = command.callbackId;

    [_mobileKeysManager updateEndpoint];
}

- (void)listMobileKeys:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    
    NSError *listKeysError;
    _mobilekey = [_mobileKeysManager listMobileKeys:&listKeysError];
    NSString *strResultFromInt = [NSString stringWithFormat:@"%lu", _mobilekey.count];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:strResultFromInt];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)endpointInfo:(CDVInvokedUrlCommand*)command
{
    
}

- (void)unregisterEndpoint:(CDVInvokedUrlCommand*)command
{    
    _terminateEndpointCallbackId = command.callbackId;
    
    [_mobileKeysManager unregisterEndpoint];
}

- (void)startForegroundScanning:(CDVInvokedUrlCommand*)command
{
    NSArray *_lockServiceCodes;
    _lockServiceCodes = @[@1, @2];
    NSError *error;

    CDVPluginResult* pluginResult = nil;

    if (_mobileKeysManager.isScanning) {
        [_mobileKeysManager stopReaderScan];
    }

    [_mobileKeysManager startReaderScanInMode:MobileKeysScanModeOptimizePerformance supportedOpeningTypes:_openingTypes lockServiceCodes:_lockServiceCodes error:&error];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)stopScanning:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;
    [_mobileKeysManager stopReaderScan];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];

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
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];
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
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Endpoint is not setup"];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Endpoint is setup"];
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
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
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
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Failed to unregister endpoint"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
}

#pragma mark - Error handling
- (void)handleStartupError:(NSError *) error {
    if (error != nil) {
        NSString* callbackId = _startupCallbackId;
        if (callbackId.length == 0) {
            callbackId = @"Found no callbackId";
        }

        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:callbackId];
    }
}

#pragma mark - Helper methods
- (BOOL)isValidCode:(NSString *)code {
    NSString *validPattern = @"^[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}$";
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:validPattern options:0 error:nil];
    
    return (code != nil) && ([regex firstMatchInString:code options:0 range:NSMakeRange(0, code.length)] != nil);
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
