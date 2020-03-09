// MobileKeysReader.h
// Copyright (c) 2014 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

/**
 * The maximum age of an RSSI Value
 */
#import <Foundation/Foundation.h>
//#import <SeosMobileKeysSDK/SeosMobileKeysSDK-Swift.h>
@class MobileKeysRssiMeasurement;
#define MAX_RSSI_AGE 3.0

/**
 *
 * MobileKeysOpeningStatus enum
 *
 */
typedef NS_ENUM(NSInteger, MobileKeysOpeningStatusType) {
    /**
     * Reader communication was successful. Please note that the API cannot determine if access was granted,
     * only that the communication with the reader succeeded
     */
    MobileKeysOpeningStatusTypeSuccess = 0,
    /**
     * Reader communication failed. This could happen if the detected BLE device was not really a Reader, or that it
     * failed to recognize the API Connection attempt
     */
    MobileKeysOpeningStatusTypeBluetoothCommunicationFailed = 1,
    /**
     * One of the timeouts triggered (either in the reader or in the SDK)
     */
    MobileKeysOpeningStatusTypeTimedOut = 2,
    /**
     * The reader that the SDK tried to connect to was not in range
     */
    MobileKeysOpeningStatusTypeOutOfRange = 3,
    /**
     * The SDK could not connect to the reader since another session to Seos is currently open
     */
    MobileKeysOpeningStatusTypeBusy = 4,
    /**
     * Opening type was motion, but closest reader does not support motion opening
     */
    MobileKeysOpeningStatusTypeMotionNotSupported = 5,
    /**
     * Opening type was proximity, but closest reader does not support proximity opening.
     */
    MobileKeysOpeningStatusTypeTapNotSupported = 6,
    /**
     * Reader reported that a valid key was not found
     */
    MobileKeysOpeningStatusTypeMobileKeyNotFound = 7,
    /**
     * The interval between openings of this specific reader was to small
     */
    MobileKeysOpeningStatusTypeReaderAntiPassback = 8,
    /**
     * The reader reported that an unknown error occurred
     */
    MobileKeysOpeningStatusTypeReaderFailure = 9,
    /**
     * BLE communication is in a deadlock state!
     */
    MobileKeysOpeningStatusTypeBluetoothCommunicationFailedWithDeadLock = 10,
    /**
     * Device timeout early (The reader found that the phone timeout)
     */
    MobileKeysOpeningStatusTypeDeviceTimedOutEarly = 11,
    /**
     * Device timeout APDU (The reader found that the phone timeout)
     */
    MobileKeysOpeningStatusTypeDeviceTimedOutApdu = 12,
    /**
     * Device timeout Fragment (The reader found that the phone timeout)
     */
    MobileKeysOpeningStatusTypeDeviceTimedOutFragment = 13,
    /**
     * Reader timeout BLE (The phone found that the reader timeout)
     */
    MobileKeysOpeningStatusTypeReaderTimedOutBle = 14,
    /**
     * Reader timeout APDU (The phone found that the reader timeout)
     */
    MobileKeysOpeningStatusTypeReaderTimedOutApdu = 15,
    /**
     * Reader timeout Fragment (The phone found that the reader timeout)
     */
    MobileKeysOpeningStatusTypeReaderTimedOutFragment = 16
};

/**
 *
 * Representation of the various opening types supported by the SDK. For Proximity, Motion and Seamless,
 * the SDK will normally handle these automatically if these opening types are enabled when scanning. See
 * the documentation for [MobileKeysManager connectToReader:openingType:error:] for more information on this.
 *
 */
typedef NS_ENUM(NSInteger, MobileKeysOpeningType) {
            /**
             * Default value used if the OpeningType could not be determined
             */
            MobileKeysOpeningTypeUnknown = 0x00,
            /**
             * Proximity (tap) type Opening Type. This opening type is normally managed by the SDK by specifying
             * it when scanning. the SDK will monitor locks that support this opening type
             */
            MobileKeysOpeningTypeProximity = 0x01,
            /**
             * Motion (Twist and Go) Opening Type
             */
            MobileKeysOpeningTypeMotion = 0x02,
            /**
             * Seamless (Vicinity) opening type
             */
            MobileKeysOpeningTypeSeamless = 0x04,
            /**
            * Application specific (Pulse open) Opening Type.
            */
            MobileKeysOpeningTypeApplicationSpecific = 0x08,
            /**
            * Enhanced solution protocol for Tap opening
            */
            MobileKeysOpeningTypeEnhancedTap = 0x40
};

/**
 * Enum for describing what Seos BLE Protocol Version that the Reader is using
 * @note since version 1.0.9
 */
typedef NS_ENUM(NSInteger, MobileKeysReaderProtocolVersion) {
            /**
             * Using legacy protocol, will not be supported in production systems, only in pilots
             */
            BleProtocolLegacy = 0,
            /**
             * Using the standard ASSA ABLOY BLE Reader Protocol
             */
            BleProtocolV1 = 1,
            /**
             * Reader protocol could not be determined
             */
            BleProtocolUnknown = 0xFFFF
};

typedef NS_ENUM(NSInteger, MobileKeysReaderType) {
    MobileKeysReaderTypeBlePeripheral = 0x00,
    MobileKeysReaderTypeBleCentral    = 0x01,
    MobileKeysReaderTypeHttpRest      = 0x02
};

/**
 * Representation of a BLe reader.
 */
@interface MobileKeysReader : NSObject <NSCopying>

/**
 * Universally unique identifier for the Reader
 */
@property(nonatomic, strong) NSString *uuid;

/**
 * Does this reader support initiating connection from the reader side?
 */
@property(nonatomic) BOOL readerCanConnect;

/**
 * Quick access to last rssi measurement (also stored in rssiList and rssiHistory)
 */
@property(nonatomic, strong, readonly) MobileKeysRssiMeasurement* latestRssiMeasurement;

/**
 * When the last succesful connection was closed. This is set by the SDK whenever a succesful connection was closed,
 * and is used to figure out if this Reader is allowed to connect again.
 */
@property(nonatomic, strong) NSDate* lastSuccessfulConnection;

/**
 * The reader's name, as given by the Reader itself
 */
@property(nonatomic, strong) NSString *name;

/**
 * The local name, as given by the advertised manufacturer data
 */
@property(nonatomic, strong) NSString *localName;

/**
* An array with the supported opening types.
*/
@property(nonatomic, strong) NSArray *supportedOpeningTypes;

/**
 * Time of the last received RSSI update
 */
@property(nonatomic, strong, readonly) NSDate *lastRSSIUpdate;

/**
 * Type of reader
 */
@property(nonatomic) MobileKeysReaderType readerType;

/**
 * An optional scan response data
 */
@property(nonatomic, strong) NSData *optionalScanResponseData;

/**
 * Creates an instance of a MobileKeysReader object.
 * @param name - The reader's name
 * @param uuid - Unique reader identifier
 * @param version - Version of the protocol used in exchange between reader and device
 * @param rssiValuesForOpeningTypes - Dictionary containing a minimum RSSI for each opening type.
 */
- (instancetype)initWithName:(NSString *)name uuid:(NSString *)uuid protocolVersion:(MobileKeysReaderProtocolVersion)version rssiValueForOpeningTypes:(NSDictionary *)rssiValuesForOpeningTypes;

/**
 * Creates an instance of a MobileKeysReader object.
 * @param name - The reader's name
 * @param uuid - Unique reader identifier
 * @param version - Version of the protocol used in exchange between reader and device
 * @param supportedOpeningTypes -
 * @param rssiValuesForOpeningTypes - Dictionary containing a minimum RSSI for each opening type.
 */
- (instancetype)initWithName:(NSString *)name uuid:(NSString *)uuid protocolVersion:(MobileKeysReaderProtocolVersion)version supportedOpeningTypes:(NSArray *)supportedOpeningTypes rssiValueForOpeningTypes:(NSDictionary *)rssiValuesForOpeningTypes requiresTimeoutFreeSession:(BOOL)requiresTimeoutFreeSession;

/**
 * Returns YES if reader supports opening type
 * @param openingType - Opening type to query
 */
- (BOOL)supportsOpeningType:(MobileKeysOpeningType)openingType;

/**
 * Returns the mean of the recently measured RSSI values.
 * Returns INT_MIN if number of measured values aren't enough.
 */
- (NSInteger)meanRssi;


/**
 * Returns YES if this reader has been seen within the last 10 seconds, and has RSSI values that are useful.
 * Will also Return NO if this Reader is in timeout (has a recent succesful connection) less than 2.2 seconds ago.
 */
- (BOOL)isActive;

/**
 * Returns YES if this reader is in timeout (has a recent succesful connection) less than 2.2 seconds ago.
 */
-(BOOL) isInTimeout;
/**
 * Returns YES if the reader is in range of the specified `MobileKeysOpeningType`, NO otherwise.
 * @param openingType - Opening type to query
 */
- (BOOL)isInRangeFor:(MobileKeysOpeningType)openingType;


/**
 * A list of RSSIMeasurement objects (maximum of three entries) showing the most recent measured Received Signal Strength Indications (RSSI values)
 */
- (NSArray<MobileKeysRssiMeasurement *>*) rssiList;
/**
 * A longer list of RSSIMeasurement objects (maximum of 50 entries) showing the most recent measured Received Signal Strength Indications (RSSI values)
 */
- (NSArray<MobileKeysRssiMeasurement *>*) rssiHistory;

/**
 * Returns a readable description about the reader.
 */
- (NSString *)description;

/**
 * Updates the reader with a new rssi value.
 * @param rssi - Measured RSSI to update reader with
 */
- (void)updateWithRssi:(NSInteger)rssi;
@end
