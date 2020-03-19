/********* UaMobileKeys.m Cordova Plugin Implementation *******/

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
// #import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
// #import "UaMobileKeys.h"
#import <Cordova/CDV.h>

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

// #import "src/ios/SeosMobileKeysSDK.framework/Headers/SeosMobileKeysSDK.h"

@implementation UaMobileKeys
  BOOL _applicationIsStarting;

- (id)init {
    self = [super init];
    // _mobileKeysManager = [self createInitializedMobileKeysManager];
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
    // [_mobileKeysManager startup];
}

- (void)isEndpointSetup:(CDVInvokedUrlCommand*)command
{

}

- (void)setupEndpoint:(CDVInvokedUrlCommand*)command
{

}

- (void)updateEndpoint:(CDVInvokedUrlCommand*)command
{

}

- (void)listMobileKeys:(CDVInvokedUrlCommand*)command
{

}

- (void)endpointInfo:(CDVInvokedUrlCommand*)command
{
    
}

- (void)unregisterEndpoint:(CDVInvokedUrlCommand*)command
{    

}

- (void)startForegroundScanning:(CDVInvokedUrlCommand*)command
{

}

- (void)stopScanning:(CDVInvokedUrlCommand*)command
{
    
}

// Error handeling and callbacks
- (void)handleError:(NSError *)error {
    if (error != nil) {
        CDVPluginResult* pluginResult = nil;
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
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

// Helper methods

// - (MobileKeysManager *)createInitializedMobileKeysManager {

//     NSString* applicationId = @"UaMobileKeys";
//     NSString *version = [NSString stringWithFormat:@"%@-%@ (%@)", applicationId, [[NSBundle mainBundle] infoDictionary][@"CFBundleShortVersionString"], [[NSBundle mainBundle] infoDictionary][@"CFBundleVersion"]];
//     NSDictionary *config = @{MobileKeysOptionApplicationId: applicationId, MobileKeysOptionVersion: version};
    
//     // Specify your own iBeacon UUID or use the internal one by not specifying this option
//     // ***********************************************************************************
//     // NSString *myBeaconUUIDString = @"XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX";
//     // NSDictionary *config = @{MobileKeysOptionApplicationId: APPLICATION_ID, MobileKeysOptionVersion: version, MobileKeysOptionBeaconUUID: myBeaconUUIDString};

//     return [[MobileKeysManager alloc] initWithDelegate:self options:config];
// }

@end
