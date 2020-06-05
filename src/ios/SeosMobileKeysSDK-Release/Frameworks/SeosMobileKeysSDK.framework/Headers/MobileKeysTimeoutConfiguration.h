// MobileKeysTimeoutConfiguration.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Bluetooth reader timeout parameters.
 * Configuration for the BLE reader communication for overriding default values regarding Reader communication.
 *
 */
@interface MobileKeysTimeoutConfiguration : NSObject

/**
 * Default APDU fragment timeout
 */
#define AMS_DEFAULT_MAX_TIME_BETWEEN_FRAGMENTS 0.3

/**
 * Default APDU timeout
 */
#define AMS_DEFAULT_MAX_TIME_BETWEEN_APDUS 1.2

/**
 * Default connection timeout
 */
#define AMS_DEFAULT_MAX_TIME_CONNECTION 3.2

/**
 * Set APDU fragment timeout between queued APDU fragments.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxTimeBetweenFragments;
/**
 * Set timeout between APDU's.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxTimeBetweenApdus;

/**
 * Set the timeout before aborting the connection during connection establishment.
 * A timeout value of zero or negative is interpreted as an immediate timeout.
 */
@property(nonatomic) NSTimeInterval maxConnectionTime;

- (NSString *)description;

@end
