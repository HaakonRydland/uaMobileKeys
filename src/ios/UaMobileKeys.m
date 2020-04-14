/********* UaMobileKeys.m Cordova Plugin Implementation *******/

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
#import <Cordova/CDV.h>

@interface UaMobileKeys : CDVPlugin {
  // Member variables go here.
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

- (id)init:(CDVInvokedUrlCommand*)command {
    self = [super init];

    if (self) {
        _mobileKeysManager = [self createInitializedMobileKeysManager];
        _openingTypes =@[@(MobileKeysOpeningTypeEnhancedTap)];
    }
    
    return self;
}

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

// Mobile keys core methods
- (void)startup:(CDVInvokedUrlCommand*)command
{
    if (self) {
        _mobileKeysManager = [self createInitializedMobileKeysManager];
        _openingTypes =@[@(MobileKeysOpeningTypeEnhancedTap)];
    }

    CDVPluginResult* pluginResult = nil;

    [_mobileKeysManager startup];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)isEndpointSetup:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;

    NSError *error;
    BOOL setupComplete = [_mobileKeysManager isEndpointSetup:&error];
    NSString *setupCompleteString = setupComplete ? @"True" : @"False";

    [self handleError:error];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:setupCompleteString];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)setupEndpoint:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;

    // NSString* results = @"True";
    NSString* invitationCode = [command.arguments objectAtIndex:0];

    if ([self isValidCode:invitationCode]) {
        [_mobileKeysManager setupEndpoint:invitationCode];
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:invitationCode];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Invalid code"];
    }

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)updateEndpoint:(CDVInvokedUrlCommand*)command
{
    CDVPluginResult* pluginResult = nil;

    [_mobileKeysManager updateEndpoint];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
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
    CDVPluginResult* pluginResult = nil;
    [_mobileKeysManager unregisterEndpoint];
    
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"True"];

    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
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

// Error handeling and callbacks
- (void)handleError:(NSError *)error {
    if (error != nil) {
        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:error.localizedFailureReason];
    }
}

- (void)mobileKeysDidStartup {
    if (_applicationIsStarting) {
        // [self setupEndpoint];
        _applicationIsStarting = NO;
    }
}

- (void)mobileKeysDidFailToStartup:(NSError *)error {
    [self handleError:error];
}

- (BOOL) isEndpointSetup {
    NSError *error;
    BOOL setupComplete = [_mobileKeysManager isEndpointSetup:&error];
    [self handleError:error];

    return setupComplete;
}

- (void) mobileKeysDidSetupEndpoint {
    CDVPluginResult* pluginResult = nil;

    if (!self.isEndpointSetup) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Endpoint is not setup"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:@"Callback"];
    } else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Endpoint is setup"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:@"Callback"];
    }
}

- (void) mobileKeysDidFailToSetupEndpoint:(NSError * ) error {
    [self handleError:error];

    CDVPluginResult* pluginResult = nil;
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Failed to setup endpoint"];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:@"Callback"];
}

// Helper methods
- (BOOL)isValidCode:(NSString *)code {
    NSString *validPattern = @"^[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}-[0-9a-zA-Z]{4}$";
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:validPattern options:0 error:nil];
    
    return (code != nil) && ([regex firstMatchInString:code options:0 range:NSMakeRange(0, code.length)] != nil);
}

- (MobileKeysManager *)createInitializedMobileKeysManager {

    NSString* applicationId = @"UaMobileKeys";
    NSString *version = [NSString stringWithFormat:@"%@-%@ (%@)", applicationId, [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"], [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]];
    NSDictionary *config = @{MobileKeysOptionApplicationId: applicationId, MobileKeysOptionVersion: version};
    
//     // Specify your own iBeacon UUID or use the internal one by not specifying this option
//     // ***********************************************************************************
//     // NSString *myBeaconUUIDString = @"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
//     // NSDictionary *config = @{MobileKeysOptionApplicationId: APPLICATION_ID, MobileKeysOptionVersion: version, MobileKeysOptionBeaconUUID: myBeaconUUIDString};

    return [[MobileKeysManager alloc] initWithDelegate:self options:config];
}

@end
