// MobileKeysManagerExtendedDelegate.h
// Copyright (c) 2017 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import "MobileKeysManagerDelegate.h"

/**
 * Extension delegate of `MobileKeysManagerDelegate`
 * @warning this delegate extension is only for advanced use cases. Please consider this before using this delegate.
 * For instance, the tap use case is already supported by the SDK by simply passing `MobileKeysOpeningTypeProximity` to
 * `-[MobileKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]`.
 */
@protocol MobileKeysManagerExtendedDelegate <MobileKeysManagerDelegate>

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
*/
@optional
- (BOOL)mobileKeysShouldInteractWithScannedReader:(MobileKeysReader *)mobileKeysReader;

/**
* Callback for when the user did an unlock gesture. If this method is implemented, the SDK will enable it's own built-in
 * motion detection, even if the MobileKeysOpeningType "Motion" is not specified eh nscanning
*
* @note since version 5.1
*/
@optional
- (void)mobileKeysUserDidUnlockGesture;
@end
