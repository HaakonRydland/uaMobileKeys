/********* UaMobileKeys.m Cordova Plugin Implementation *******/

#import <Cordova/CDV.h>
#import <./SeosMobileKeysSDK.framework/Headers/SeosMobileKeysSDK.h>

@interface UaMobileKeys : CDVPlugin {
  // Member variables go here.
}

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
@end

@implementation UaMobileKeys
  BOOL _applicationIsStarting;


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
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];

    [_mobileKeysManager startup];
}

- (void)isEndpointSetup:(CDVInvokedUrlCommand*)command
{
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];
    CDVPluginResult* pluginResult = nil;

    NSError *error;
    BOOL setupComplete = [_mobileKeysManager isEndpointSetup:&error];
    [self handleError:error];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:setupComplete];
}

- (void)setupEndpoint:(CDVInvokedUrlCommand*)command
{
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];
    NSString* results = @"True";
    NSString* invitationCode = [command.arguments objectAtIndex:0];

    [_mobileKeysManager setupEndpoint:invitationCode];
    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:results];
}

- (void)updateEndpoint:(CDVInvokedUrlCommand*)command
{
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];

    [_mobileKeysManager updateEndpoint];
}

- (void)listMobileKeys:(CDVInvokedUrlCommand*)command
{
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];
    CDVPluginResult* pluginResult = nil;

    NSError *listKeysError;
    NSString* results = [_mobileKeysManager listMobileKeys:&listKeysError];

    pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:results]
}

- (void)endpointInfo:(CDVInvokedUrlCommand*)command
{
    
}

- (void)unregisterEndpoint:(CDVInvokedUrlCommand*)command
{    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];
    
    [_mobileKeysManager unregisterEndpoint];
}

- (void)startForegroundScanning:(CDVInvokedUrlCommand*)command
{
    NSArray *_lockServiceCodes;
    _lockServiceCodes = @[@1, @2];
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];
    if (_mobileKeysManager.isScanning) {
        [_mobileKeysManager.stopReaderScan];
    }

    [_mobileKeysManager startReaderScanInMode:scanMode supportedOpeningTypes:openingTypes lockServiceCodes:_lockServiceCodes error:&error];
}

- (void)stopScanning:(CDVInvokedUrlCommand*)command
{
    self = [super init];
    _mobileKeysManager = [self createInitializedMobileKeysManager];

    [_mobileKeysManager stopReaderScan];
}

// Error handeling and callbacks
- (void)handleError:(NSError *)error {
    if (error != nil) {
        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR]
    }
}

- (void)mobileKeysDidStartup {
    if (_applicationIsStarting) {
        [self setupEndpoint];
        _applicationIsStarting = NO;
    }
}

- (void)mobileKeysDidFailToStartup:(NSError *)error {
    [self handleError:error];
}

@end
