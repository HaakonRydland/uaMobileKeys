// MobileKeysManager.h
// Copyright (c) 2014 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "MobileKeysKey.h"
#import "MobileKeysLastAuthenticationInfo.h"
#import "MobileKeysErrorCodes.h"
#import "MobileKeysSeosSession.h"
#import "MobileKeysSeosProvider.h"
#import "MobileKeysManagerDelegate.h"
#import "MobileKeysSeosTag.h"
#import "MobileKeysSeosSession.h"
#import "MobileKeysTimeoutConfiguration.h"
#import "MobileKeysEndpointInfo.h"
NS_ASSUME_NONNULL_BEGIN
extern NSString *MobileKeysPreconditionFailedException;

extern void MobileKeysPreconditionCheckTriggered(NSString *message);

#define MobileKeysPreconditionCheck(condition, ...) if(!(condition)) MobileKeysPreconditionCheckTriggered([NSString stringWithFormat:__VA_ARGS__])

extern const NSString *MobileKeysOptionApplicationId;
extern const NSString *MobileKeysOptionVersion;
extern const NSString *MobileKeysOptionBeaconUUID;
extern const NSString *MobileKeysOptionTSMPublicCert;
extern const NSString *MobileKeysOptionTSMBaseURL;
extern const NSString *MobileKeysOptionMotionManager;
extern const NSString *MobileKeysOptionCustomEventValue;
extern const NSString *MobileKeysOptionCustomSetupAkeKey;

/**
 * Configuration definition for the scan modes available in the Mobile Keys SDK
 * @see `-[MobileKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]`
 */
typedef NS_ENUM(NSInteger, MobileKeysScanMode) {
    /**
     * Enable Location Monitoring while scanning for readers
     */
            MobileKeysScanModeOptimizePerformance = 0,
    /**
     * Do not enable Location Monitoring while scanning for readers
     */
            MobileKeysScanModeOptimizePowerConsumption = 1
};

/**
 * Contains assorted information about the device and the device settings to provide a good user experience.
 * @see `-[MobileKeysManager healthCheck]`
 */
typedef NS_ENUM(NSInteger, MobileKeysInfoType) {
    /**
     * Bluetooth services is not authorized by user. Recommended user action is to change permissions.
     */
            MobileKeysInfoTypeBleNotSupported = 1,
    /**
     * Bluetooth services is not authorized by this device. Recommended user action is to change device.
     */
            MobileKeysInfoTypeBleTurnedOff,
    /**
     * Location services is not enabled in app project settings. Recommended developer action is to change project settings.
     */
            MobileKeysInfoTypeLocationServicesNotEnabled,
    /**
     * Location services authorization is not determined by user. Recommended developer action is to call requestAlwaysAuthorization.
     */
            MobileKeysInfoTypeLocationServicesNotDetermined,
    /**
     * Location services is not authorized by user. Recommended user action is to change permissions.
     */
            MobileKeysInfoTypeLocationServicesTurnedOff,
    /**
     * CLBeaconRegion monitoring or ranging is not supported by this device. Recommended user action is to change device.
     */
            MobileKeysInfoTypeLocationMonitoringNotSupported,
    /**
     * CLBeaconRegion monitoring or ranging is not authorized by the user. Recommended user action is to change permissions.
     */
            MobileKeysInfoTypeLocationMonitoringTurnedOff,
    /**
     * Passcode may be turned off. This cannot be verified 100% reliably, but this could be an indication that the phone is not protected by a password.
     */
            MobileKeysInfoTypePasscodeWarning,
    /**
     * Bluetooth sharing authorization for BLE Peripheral mode has not been granted. This should only happen when using Enhanced Tap. Recommended user action is to go to App System Settings and enable Bluetooth Sharing.
     */
            MobileKeysInfoTypeBleSharingTurnedOff

};

/**
 * This is the main class of the ASSA ABLOY Mobile Keys API.
 * <p>
 * This API is used to communicate with the Seos TSM and to read/write mobile keys to the
 * Seos application, located in a secure storage file on the device.
 * </p>
 * <p>
 * The API contains some asynchronous methods. The API will not allow for  multiple asynchronous tasks to be
 * launched at the same time. If you launch an asynchronous task while another has not yet finished
 * a NSError` will be returned with error code `MobileKeysErrorCode MobileKeysApiIsBusyError`.
 * </p>
 * When initializing the BLE scan, the SDK can optionally enable Location Monitoring as well. This will improve
 * the responsiveness when finding Readers, but will consume more power, especially if the application is running
 * in the background.
 */
@interface MobileKeysManager : NSObject

#pragma mark Initialization and configuration

/**
 * Creates and initializes an instance of the `MobileKeysManager`. It is advisable that you keep the reference to the
 * Manager for the duration of your application life cycle. It is not currently possible to have multiple instances
 * of the Manager.
 *
 * @param delegate - The object who wishes to implement the protocols enforced by the API
 * @param options - Application settings for controlling application behaviour. The key `MobileKeysOptionApplicationId`
 * is a string provided by ASSA ABLOY that uniquely identifies the application and the key `MobileKeysOptionVersion`
 * is a string describing the application name and version. The key `MobileKeysOptionBeaconUUID` is a string describing
 * a iBeacon UUID to monitor. If defined, this string will override the default iBeacon UUID monitored.
 * For advanced configuration of the TSM, see the documentation on "Custom TSM Configuration"
 * @note since version 2.0
 */
- (instancetype)initWithDelegate:(NSObject <MobileKeysManagerDelegate> *)delegate options:(NSDictionary *)options;

/**
 * Changes opening types provided in application config during runtime
 * @param openingTypes A list of @(MobileKeysOpeningType)
 * @note since version 2.0
 */
- (void)setSupportedOpeningTypes:(NSArray *)openingTypes;

/**
 * Override default timeout values
 * @param timeoutConfiguration A timeout configuration
 * @note since version 3.2
 */
- (void)setTimeoutConfiguration:(MobileKeysTimeoutConfiguration *)timeoutConfiguration;

/**
 * Override default usage of machine learning model.
 * Default value is off. If enabled the Twist and Go algorithm will use a core Machine Learning model to predict
 * user twists. The machinelearning model url need to be specified with MobileKeysOptionMachineLearningModelUrl
 * and added to the app bundle
 * @param enable Enable/disable usage of machinelearning model
 */
- (void)setSupportsMachineLeaningModel:(BOOL) enable DEPRECATED_MSG_ATTRIBUTE("Not in use");

#pragma mark Seos TSM Integration calls

/**
 * Installs and personalizes the Seos application on current secure element. This is a long running process
 * involving TCP/IP communication with the Seos TSM, so good practice is to make sure the phone has an internet
 * connection before calling this method.
 *
 * The delegate method `-[MobileKeysManagerDelegate mobileKeysDidSetupEndpoint]` is called when the endpoint
 * has successfully been set up. If the setup fails, the delegate method
 * `-[MobileKeysManagerDelegate mobileKeysDidDidFailToSetupEndpoint:]` will be called.
 *
 * @param invitationCode A Mobile Keys Invitation code on the form "XXXX-XXXX-XXXX-XXXX". The invitation code
 * includes information specifying what environment (e.g. test or prod) that should be used.
 * @see isEndpointSetup:
 * @warning This method will throw an exception if the sdk has not been started
 * @note since version 2.0
 */
- (void)setupEndpoint:(NSString *)invitationCode;

/**
 * This method will take care of contacting the Seos TSM to download any updates to the local
 * personalized endpoint. This is a long running process
 * involving TCP/IP communication with the Seos TSM, so good practice is to make sure the phone has an internet
 * connection before calling this method. The updates can be new keys, key revocations, key updates, but also endpoint
 * terminations. If the endpoint is successfully updated, the MobileKeysManager object calls the mobileKeysDidUpdateEndpoint:
 * method of its delegate object. If the connection attempt fails, the MobileKeysManager object calls the
 * mobileKeysDidFailToUpdateEndpoint: method of its delegate object instead. If the endpoint was terminated, the
 * MobileKeysManager object also calls the mobileKeysDidTerminateEndpoint method on its delegate object.
 *
 * If the endpoint has been terminated, a new invitation code is required to set it up.
 * @note since version 2.0
 * @warning This method will throw an exception if the SDK has not been started, or if the endpoint is not already setup
 */
- (void)updateEndpoint;

/**
 * This method will take care of contacting the Seos TSM to unregister (terminate) the local
 * personalized endpoint. This is a long running process
 * involving TCP/IP communication with the Seos TSM, so good practice is to make sure the phone has an internet
 * connection before calling this method. If the endpoint was terminated, the
 * MobileKeysManager object also calls the mobileKeysDidTerminateEndpoint method on its delegate object.
 *
 * If the endpoint has been terminated, a new invitation code is required to set it up.
 * @note since version 2.0
 * @warning This method will throw an exception if the SDK has not been started, or if the endpoint is not already setup
 */
- (void)unregisterEndpoint;

/**
 * This method should always be called after `-[MobileKeysManager initWithDelegate:options:]` weather the endpoint is setup or not. If the
 * startup is successful, the `MobileKeysManager` object calls the `mobileKeysDidStartup` method on its delegate object. If the startup
 * fails, the MobileKeysManager object calls the mobileKeysDidFailToStartup: method of its delegate object instead.
 *
 * This method may involve TCP/IP communication with the Seos TSM, so good practice is to make sure the phone has an internet
 * connection before calling this method. (One of the tasks performed by this method is upgrading the local environment if
 * the server protocol has been updated.)
 *
 * @note since version 2.0
 * @warning This method will throw an exception if called more than once
 */
- (void)startup;

/**
 * Checks if Seos is installed and personalized on the secure element. If not, you need to call the
 * endpointSetup method to complete the setup.
 * Note that most of the other methods in the API requires the setup to be complete to run successfully.
 *
 * Because of concurrency reasons, the result of this method may not be always accurate, but it will always return the
 * last known state. For example; if the endpoint is currently being terminated, this method will return @YES if called
 * before the termination has been completed.
 *
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode` or nil if no error.
 * @note since version 2.0
 */
- (BOOL)isEndpointSetup:(NSError **)error;

/**
 * Checks system and returns a list of MobileKeysInfoType values.
 * @return An array of `MobileKeysInfoType` values
 * @note since version 2.0
 */
- (NSArray *)healthCheck;


/**
 * Returns the API version on the form major.minor.maintenance.build, e.g. 4.0.0.123.
 */
- (NSString *)apiVersion;


#pragma mark Seos API calls

/**
 * List the Mobile Keys currently stored in Seos. This method will return an `NSArray` of `MobileKeysKey` objects,
 * or an empty `NSArray` if no keys are found. It is advisable that this method is called whenever a call to update has
 * been successful.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @return Returns a list of MobileKeysKey objects
 * @see MobileKeysKey class
 * @note since version 2.0
 */
- (NSArray<MobileKeysKey *> *)listMobileKeys:(NSError **)error;

/**
 * This method will return one `MobileKeysKey` object, representing the key that was last used to authenticate to a reader.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode.
 * @return Returns the last authenticated key object.
 * If there is no last authenticated key, this method will return nil.
 * @see MobileKeysKey class
 * @note since version 2.2
 */
- (MobileKeysLastAuthenticationInfo *  _Nullable)lastAuthenticationInfo:(NSError **)error;

/**
 * Method to get information about the Seos Endpoint.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @return Returns information about the Endpoint
 * @see MobileKeysEndpointInfo class
 * @note since version 2.0
 */
- (MobileKeysEndpointInfo *)endpointInfo:(NSError **)error;

#pragma mark Bluetooth API calls

/**
 * This method can be used to verify that the device supports BLE. The API will
 * query the Core Bluetooth system upon startup and this method will return NO if
 * the current device does not support Bluetooth Low Energy. This is a convenience method
 * to allow the application to query for BLE compatibility without having to implement
 * or initialize the Core Bluetooth layer.
 */
- (BOOL)deviceSupportsBluetoothLowEnergy;

/**
 * This method can be used to verify that the device has bluetooth turned on. The API will
 * query the Core Bluetooth system upon startup and this method will return NO if
 * the current device does not have Bluetooth turned on. This is a convenience method
 * to allow the application to query for BLE compatibility without having to implement
 * or initialize the Core Bluetooth layer.
 * @note since version 2.0
 */
- (BOOL)deviceHasBluetoothTurnedOn;

/**
 * This method is used to connect to a specified reader. Valid
 * errors that may be reported are defined in the `NSError` class.
 *
 * - 401 One asynchronous method of the API is already running.
 * - 1101 The current list of allowed OpeningTypes did not contain the supplied OpeningType.
 *
 * @param reader - Reader that should be connected to, cannot be nil
 * @param openingType - OpeningType that should be used.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @note since version 2.0
 */
- (void)connectToReader:(MobileKeysReader *)reader openingType:(MobileKeysOpeningType)openingType error:(NSError **)error;

/**
 * Tell the SDK to start scanning for readers in given `MobilekeysScanMode`. If the device is already scanning, this call will
 * first attempt to stop the current scan before starting the scan.
 * If the scan mode is MobileKeysScanModeOptimizePerformance this
 * will enable the application to continue to run even if the screen is turned
 * off or the phone is locked.
 * Valid errors that may be reported are defined in the `NSError` class.
 *
 * Since the user must give permission to use Location Services, it is necessary for the Application to handle any error
 * reported by this method.
 *
 *  Include an array of the OpeningTypes you would like to be active.
 *
 * - 1001  CLBeaconRegion monitoring or ranging is not supported by this device
 * - 1002  Location services is not enabled in app project settings
 * - 1003  Location services is not authorized by user
 * - 1004  Location services authorization is not determined by user. iOS8 and above need to call `requestAlwaysAuthorization`
 * - 1102  The supplied configuration contained malformed OpeningTypes or no OpeningTypes at all
 * - 1103  MobileKeysManager were unable to serve the request since Bluetooth Low Energy is unavailable
 *
 * @param scanMode - Describes in what mode to start scanning.
 * @param openingTypes - A set of OpeningTypes that the API should support.
 * @param error - The cause of the failure, code is one of `MobileKeysErrorCode`.
 * @note since version 2.0
 */
- (void)startReaderScanInMode:(MobileKeysScanMode)scanMode supportedOpeningTypes:(NSArray *)openingTypes lockServiceCodes:(NSArray *)lockServiceCodes error:(NSError **)error;

/**
 * Stops scanning for readers
 * @note since version 2.0
 */
- (void)stopReaderScan;

/**
 * Returns whether the API is currently scanning for readers or not. Please not that this method does not return the
 * current state of the Core Bluetooth scanning system, but the configuration of the MobileKeysManager. Actual BLE scanning
 * may be turned on or off as the phone communicates with the Reader, but as long as this method returns @YES, the scanning should restart
 * when Reader communication has completed.
 * @note since version 2.0
 */
- (BOOL)isScanning;

#pragma mark Reader Info Calls

/**
 * Returns an array of the active `-[MobileKeysReader} objects from the
 * internal SDK database. If a Reader has not been seen in ten seconds, it is filtered out from the list.
 * @see `-[MobileKeysReader}
 * @note since version 2.0
 */
- (NSArray<MobileKeysReader *> *)listReaders;

/**
 * Returns the closest `MobileKeysReader]` object within range of the
 * specified `-[MobileKeysReader MobileKeysOpeningType]`. May return nil if there is no reader in range for the specified
 * `-[MobileKeysReader#MobileKeysOpeningType]`.
 * @param openingType - the specific `-[MobileKeysReader#MobileKeysOpeningType]` to look for
 * @note since version 2.0
 */
- (MobileKeysReader *  _Nullable)closestReaderWithinRangeOfOpeningType:(MobileKeysOpeningType)openingType;


/**
 * Returns data for the specified `-[MobilekeysSeosTag]` on key with specified object identifier (OID). The OIDString is the keyId property of the `MobileKeysKey`.
 *
 * @param oidString - OIDs of keys to get data from.
 * @param tag - `MobileKeysSeosTag` to get data from.
 * @param error - Error object. Library will set this if an error occurs
 * @deprecated Use `MobileKeysGetDataApduCommand` in Seos Access API instead
 * @version 2.0.0
 */
- (NSData *)dataForKeyOid:(NSString *)oidString tag:(MobileKeysSeosTag *)tag error:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use MobileKeysGetDataApduCommand in Seos Access API instead");


/**
 * Returns an NSString representation of a One Time Password (OTP).
 * A new OTP is returned each time this method is called.
 *
 * @param key - a MobileKeysKey
 * @param error - Error object. Library will set this if an error occurs.
 * @note since version 3.1.0
 */
- (NSString *)generateOTPForKey:(MobileKeysKey *)key error:(NSError **)error;

/**
 * Returns the current counter value as a six character NSString (Numeral, 0-9). It is altered each time generateOTPForKey: is called
 *
 * @param key - a MobileKeysKey
 * @param error - Error object. Library will set this if an error occurs.
 * @note since version 3.1.0
 */
- (NSUInteger)otpCounterForKey:(MobileKeysKey *)key error:(NSError **)error;

/**
 * Saves data to specified tag on key with specified oid. The OIDString is the keyId property of the MobileKeysKey.
 *
 * @param oidString - OIDs of keys to get data from.
 * @param tag - MobileKeysSeosTag to get data from.
 * @param error - Error object. Library will set this if an error occurs.
 */
- (void)putData:(NSData *)data keyOid:(NSString *)oidString tag:(MobileKeysSeosTag *)tag error:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use MobileKeysPutDataApduCommand in Seos Access API instead");

/**
 * Activate a Mobile Key. This will mark the key as ACTIVE in the Seos Storage.
 * @return - YES on success, NO on failure
 * @param key - the MobileKeysKey to activate
 * @error - If method returns NO, check the error.code for details
 */
- (BOOL)activateMobileKey:(MobileKeysKey *)key error:(NSError **)error;

/**
 * Deactivate a Mobile Key. This will mark the key as INACTIVE in the Seos Storage. This means that the key will not
 * be visible to readers, and the key will no longer be selectable.
 * @return - YES on success, NO on failure
 * @param key - the MobileKeysKey to deactivate
 * @error - If method returns NO, check the error.code for details
 */
- (BOOL)deactivateMobileKey:(MobileKeysKey *)key error:(NSError **)error;

/**
 * Use this method to access the default Seos provider. The default Seos Provider is the local soft storage instance of
 * Seos.
 * The current implementation of the MobileKeysSeosProvider suffers from a few limitations:
 * It is recommended that you DO NO call any other Manager functions while the session is open, since these will
 * most likely fail. Seos will be unavailable for all other functions for the duration of the session, so it is
 * very important that you close the session when you're done.
 *  - Do not use the Provider to open a session while the MobileKeysManager is scanning for readers
 *  - Do not use the MobileKeysSeosProvider and the MobileKeysManager methods at the same time
 * These limitation will be adressed in future versions of the SDK implementation.
 * @return the default Seos Provider
 * @note since version 5.0.0
 */
- (MobileKeysSeosProvider *)defaultMobileKeysSeosProvider;

@end
NS_ASSUME_NONNULL_END
