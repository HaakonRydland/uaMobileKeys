// MobileKeysManagerDelegate.h
// Copyright (c) 2014 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "MobileKeysReader.h"
NS_ASSUME_NONNULL_BEGIN
@class MobileKeysReader;
@class MobileKeysOpeningResult;
@class MobileKeysEndpointUpdateSummary;

/**
 * Delegate protocol to implement for callbacks from the `MobileKeysManager` class
 * @see `MobileKeysManager`
 */
@protocol MobileKeysManagerDelegate

 /**
 * Callback for when `-[MobileKeysManager startup]` was successfully completed.
 * @note since version 2.0
 */
- (void)mobileKeysDidStartup;

/**
 * Callback for when `-[MobileKeysManager startup]` failed.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @note since version 2.0
 */
- (void)mobileKeysDidFailToStartup:(NSError *)error;

 /**
 * Callback for when `-[MobileKeysManager setupEndpoint]` was successfully completed. The endpoint is now setup.
 * @note since version 2.0
 */
- (void)mobileKeysDidSetupEndpoint;

 /**
 * Callback for when `-[MobileKeysManager setupEndpoint]` failed. The endpoint hasn't been setup.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @note since version 2.0
 */
- (void)mobileKeysDidFailToSetupEndpoint:(NSError *)error;

@optional
 /**
 * Callback for when `-[MobileKeysManager updateEndpoint]` was successfully completed and the endpoint has been updated.
 * @note since version 2.0. There are two versions of this callback, both have been marked @optional for technical reasons,
 * but at least one of them should be implemented
 * @see -[MobileKeysManagerDelegate mobileKeysDidUpdateEndpointWithSummary:]
 */
- (void)mobileKeysDidUpdateEndpoint;

@optional
/**
 * Callback for when `-[MobileKeysManager updateEndpoint]` was successfully completed and the endpoint has been updated.
 * @note since version 6.2. There are two versions of this callback, both have been marked @optional for technical reasons,
 * but at least one of them should be implemented
 * @param endpointUpdateSummary a summary of the update performed
 * @see -[MobileKeysManagerDelegate mobileKeysDidUpdateEndpoint]
 */
- (void)mobileKeysDidUpdateEndpointWithSummary:(MobileKeysEndpointUpdateSummary *) endpointUpdateSummary;
 /**
 * Callback for when `-[MobileKeysManager updateEndpoint]` failed. The endpoint wasn't updated.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @note since version 2.0
 */
- (void)mobileKeysDidFailToUpdateEndpoint:(NSError *)error;

 /**
 * Callback for when the endpoint has been terminated. This can happen even without calling `-[MobileKeysManager updateEndpoint]`.
  From version 6.0.0 this will also be called if the SDK detects a fatal error with the local Seos Vault. The expected behaviour
  when this callback is made is to restart personalization.
 * @note since version 2.0
 */
- (void)mobileKeysDidTerminateEndpoint;

 /**
 * Callback for when the application has just connected to reader.
 * @param reader - The reader which the application has connected to.
 * @param type - The type of opening which connected the application with reader.
 * @note since version 4.0
 */
- (void)mobileKeysDidConnectToReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type;

 /**
 * Callback for when a connection has failed.
 * @param reader - The reader which the application failed to connect to.
 * @param type - The type of opening which initiated the connection attempt.
 * @param status - Status of the failed connection
 * @note since version 2.0
 */
- (void)mobileKeysDidFailToConnectToReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type openingStatus:(MobileKeysOpeningStatusType)status;

 /**
 * Callback for when the application disconnected the reader.
 * @param reader - The reader which application has disconnected from.
 * @param type - The type of opening which initiated the connection attempt.
 * @param result - Status of the failed connection
 * @note since version 4.0
 */
- (void)mobileKeysDidDisconnectFromReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type openingResult:(MobileKeysOpeningResult *)result;

 /**
 * Decides if application should allow connection to reader. This will be called by the library
 * prior to attempting connect to reader.
 * @param reader - The reader which the application is considering connecting to.
 * @param type - The type of opening which initiated the connection attempt.
 * @note since version 2.0
 */
- (BOOL)mobileKeysShouldAttemptToOpen:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)type;

@optional
/**
* IMPORTANT: Only implement this callback method if you absolutely need scan results for all Readers.
* If this method is NOT implemented, the SDK assumes that it returns YES. See below.
* This is a callback method  for each advertisement the SDK receives from all seen readers in the vicinity.
* If this callback is implemented, the SDK will call this function for each and every RSSI value measurement,
* which could impact battery consumption of your application.
*
* When this method in implemented and returns NO, the SDK will not run its internal Opening Triggers for this particular
* MobileKeysReader RSSI measurement. In practice, this means that the Reader will be ignored.
* If this method is implemented and returns YES, the SDK will process the RSSI values.
* If this method is NOT IMPLEMENTED, the SDK will assume that the response was YES.
*
* Possible use cases for this method includes but is not limited to:
*  - Custom opening triggers (e.g. custom RSSI value analysis etc)
*  - Disabling SDK built-in unlock mechanisms temporarily, while at the same time the SDK keeps scanning.
*
*
* @return NO id the MobileKeysReader should be ignored, otherwise YES
* @warning This is a low-level method that should only be implemented for custom opening behaviors,
* i.e. not one of the types in `MobileKeysOpeningType`.
* @param mobileKeysReader - The reader that sent the advertisement
* @note since version 5.1
* @deprecated this delegate callback will be moved to `MobileKeysManagerExtendedDelegate`
*/
- (BOOL)mobileKeysShouldInteractWithScannedReader:(MobileKeysReader *)mobileKeysReader DEPRECATED_MSG_ATTRIBUTE("This delegate callback will moved to MobileKeysManagerExtendedDelegate");

@optional
/**
* Callback for when the user did an unlock gesture. If this method is implemented, the SDK will enable it's own built-in
 * motion detection, even if the MobileKeysOpeningType "Motion" is not specified eh nscanning
 *
 * @note since version 2.0
 * @deprecated this delegate callback will be moved to `MobileKeysManagerExtendedDelegate`
 */
- (void)mobileKeysUserDidUnlockGesture DEPRECATED_MSG_ATTRIBUTE("This delegate callback will moved to MobileKeysManagerExtendedDelegate");

@optional
/**
 * An optional callback for when the reader gets inactive.
 * @param reader - The reader that stopped updating RSSI
 * @note since version 7.6.4
 */
- (void)mobileKeysReaderDisappeared:(MobileKeysReader*) reader;
@end
NS_ASSUME_NONNULL_END
