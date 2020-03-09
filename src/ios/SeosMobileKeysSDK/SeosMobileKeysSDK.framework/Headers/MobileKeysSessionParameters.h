// MobileKeysSessionParameters.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

@class MobileKeysPrivacyKeySet;
@class MobileKeysAuthenticationKeySet;
@class MobileKeysSymmetricKeyPair;
/**
 * Describes the type of ADF selection to use during session establishment.
 */
typedef NS_ENUM(NSInteger, MobileKeysSelectionType) {
            /**
             * Generates a command to select an ADF as specified by the SELECT ADF by sequence of OID with Privacy.
             */
            MobileKeysSelectionADF,
            /**
             * Selects the GDF.
             */
            MobileKeysSelectionGDF,
            /**
            *  Generates a command to select an ADF. This version of select ignores the disabled state of an ADF, and can
            *  be used to select an ADF even if it's disabled.
            *
            *  @note This version of select ADF requires previous authentication with a key granting
            *  "core administration" permissions.
            */
            MobileKeysSelectionExtendedADF,
            /**
             * Selects an empty Seos card, use the {@link GenesisPrivacyKeyset} for privacy when using this
             * selection mode.
             */
            MobileKeysSelectionEmptySeos,
            /**
             * Do not perform any selection.
             */
            MobileKeysSelectionNone
};


typedef NS_ENUM(NSInteger, MobileKeysSessionClientIdentifier) {
    /**
     * Specifies that the session was initiated by an unspecified client.
     */
            MobileKeysSessionClientUnspecified =0x01,
    /**
     * Specifies that the session was initiated by the Mobile Access SDK Bluetooth subsystem.
     */
            MobileKeysSessionClientBle=0x02,
    /**
     * Specifies that the session was initiated by the Mobile Access SDK TSM Communication subsystem.
     */
            MobileKeysSessionClientTsm=0x03,
    /**
    * Specifies that the session was initiated by the Mobile Access SDK Readback Communication subsystem.
    */
            MobileKeysSessionClientReadback=0x04,
    /**
     * Specifies that the session was initiated by the Mobile Access SDK Readback Communication subsystem.
     */
    MobileKeysSessionClientInternal=0x05,

    /**
     * Specifies that the session was initiated by a third party client
    */
            MobileKeysSessionClientThirdParty=0x06
};


/**
 * Represents key number of a key in an ADF
 */
typedef NS_ENUM(uint8_t, MobileKeysKeyNumber) {
    MOBILE_KEYS_KEY_0 = 0x00,
    MOBILE_KEYS_KEY_1 = 0x01,
    MOBILE_KEYS_KEY_2 = 0x02,
    MOBILE_KEYS_KEY_3 = 0x03,
    MOBILE_KEYS_KEY_4 = 0x04,
    MOBILE_KEYS_KEY_5 = 0x05,
    MOBILE_KEYS_KEY_6 = 0x06,
    MOBILE_KEYS_KEY_7 = 0x07,
    MOBILE_KEYS_KEY_8 = 0x08,
    MOBILE_KEYS_KEY_9 = 0x09,
    MOBILE_KEYS_KEY_10 = 0x0A,
    MOBILE_KEYS_KEY_11 = 0x0B,
    MOBILE_KEYS_KEY_12 = 0x0C,
    MOBILE_KEYS_KEY_13 = 0x0D,
    MOBILE_KEYS_KEY_14 = 0x0E,
    MOBILE_KEYS_KEY_15 = 0x0F,
    MOBILE_KEYS_KEY_16 = 0x10,
    MOBILE_KEYS_KEY_17 = 0x11,
    MOBILE_KEYS_KEY_18 = 0x12,
    MOBILE_KEYS_KEY_19 = 0x13,
    MOBILE_KEYS_KEY_20 = 0x14,
    MOBILE_KEYS_KEY_21 = 0x15,
    MOBILE_KEYS_KEY_22 = 0x16,
    MOBILE_KEYS_KEY_23 = 0x17,
    MOBILE_KEYS_KEY_24 = 0x18,
    MOBILE_KEYS_KEY_25 = 0x19,
    MOBILE_KEYS_KEY_26 = 0x1A,
    MOBILE_KEYS_KEY_27 = 0x1B,
    MOBILE_KEYS_KEY_28 = 0x1C,
    MOBILE_KEYS_KEY_29 = 0x1D,
    MOBILE_KEYS_KEY_30 = 0x1E,
    MOBILE_KEYS_KEY_31 = 0x1F,

    MOBILE_KEYS_KEY_0_GLOBAL = 0x40,
    MOBILE_KEYS_KEY_1_GLOBAL = 0x01 | MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_2_GLOBAL = 0x02 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_3_GLOBAL = 0x03 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_4_GLOBAL = 0x04 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_5_GLOBAL = 0x05 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_6_GLOBAL = 0x06 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_7_GLOBAL = 0x07 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_8_GLOBAL = 0x08 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_9_GLOBAL = 0x09 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_10_GLOBAL = 0x0A & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_11_GLOBAL = 0x0B & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_12_GLOBAL = 0x0C & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_13_GLOBAL = 0x0D & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_14_GLOBAL = 0x0E & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_15_GLOBAL = 0x0F & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_16_GLOBAL = 0x10 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_17_GLOBAL = 0x11 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_18_GLOBAL = 0x12 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_19_GLOBAL = 0x13 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_20_GLOBAL = 0x14 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_21_GLOBAL = 0x15 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_22_GLOBAL = 0x16 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_23_GLOBAL = 0x17 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_24_GLOBAL = 0x18 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_25_GLOBAL = 0x19 & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_26_GLOBAL = 0x1A & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_27_GLOBAL = 0x1B & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_28_GLOBAL = 0x1C & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_29_GLOBAL = 0x1D & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_30_GLOBAL = 0x1E & MOBILE_KEYS_KEY_0_GLOBAL,
    MOBILE_KEYS_KEY_31_GLOBAL = 0x1F & MOBILE_KEYS_KEY_0_GLOBAL,

};

/**
 * Seos encryption algorithms supported by the API
 */
typedef NS_ENUM(Byte, MobileKeysEncryptionAlgorithm) {
            /**
             * Unknown or unsupported algorithm
             */
            MOBILE_KEYS_ENCRYPTION_ALGO_ERROR = 0x00,
            /**
             * AES 128
             */
            MOBILE_KEYS_ENCRYPTION_ALGO_AES_128 = 0x09
};

/**
 * Seos hash algorithms supported by the API
 */
typedef NS_ENUM(Byte, MobileKeysHashAlgorithm) {
            /**
             * Unknown or unsupported hash algorithm
             */
            MOBILE_KEYS_HASH_ALGO_ERROR = 0x00,
            /**
             * HMAC SHA1
             * @warning currently not supported
             */
            MOBILE_KEYS_HASH_ALGO_HMAC_SHA1 = 0x06,
            /**
             * HMAC SHA256
             */
            MOBILE_KEYS_HASH_ALGO_HMAC_SHA_256 = 0x07,
            /**
             * CMAC AES
             */
            MOBILE_KEYS_HASH_ALGO_CMAC_AES = 0x09,
};

/**
 * When establishing a session to Seos, pass a MobileKeysSessionParameters to MobileKeysSeosProvider#openSessionWithParams:withError: to configure the
 * session. Here's an overview of the parameters and what they are used for:
 *  - mobileKeysSelectionType: The type of initial selection that should be performed when establishing the session
 *  - mobileKeysPrivacyKeySet: The keyset used to decrypt the initial selection response for any selection type other than
 *  MobileKeysSelectionType#MobileKeysSelectionNone
 *  -  mobileKeysAuthenticationKeySet: The authentication Keyset
 *  - contactless: NO if this is a contactless connection
 *  - requireSelectAID: YES if the Seos AID should be selected before the session is established
 *  - useTestVectors: YES if the session should be established using test vectors
 *  - requiresSecureMessaging: If NO, the session establishement will not do mutual authentication
 *  - oidSelectionList: A list of OIDs that should be used when the MobileKeysSeosProvider selects the ADF or GDF
 * @note since version 5.0.0
 */
@interface MobileKeysSessionParameters : NSObject

/**
 * The type of selection that the MobileKeysSeosProvider#openSessionWithParams:withError: should perform.
 *  - MobileKeysSelectionADF : Select an ADF
 *  - MobileKeysSelectionGDF : Select the GDF
 *  - MobileKeysSelectionExtendedADF : Administration
 *  - MobileKeysSelectionNone : do not perform an initial select
 */
@property(nonatomic) MobileKeysSelectionType mobileKeysSelectionType;

/**
 * Open Sessions can be classified by the client identifier.
 *  - MobileKeysSessionClientUnspecified : Select an ADF
 *  - MobileKeysSessionClientBle : Internally used by the Mobile Access SDK. Don't use.
 *  - MobileKeysSessionClientTsm : Internally used by the Mobile Access SDK. Don't use.
 *  - MobileKeysSessionClientThirdParty : Third party integrators should use this.
 */
@property(nonatomic) MobileKeysSessionClientIdentifier mobileKeysSessionClientIdentifier;

/**
 * This is privacy keyset used when selecting the ADF or GDF.
 */
@property(nonatomic, strong) MobileKeysPrivacyKeySet *mobileKeysPrivacyKeySet;
/**
 * This is the authentication keyset used for mutual authentication when setting up a session with Seos.
 * Set this to nil if no mutual authentication should be performed.
 *
 * @see {@link MobileKeysAuthenticationKeyset}
 * @see {@link MobileKeysMasterAuthenticationKeyset}
 */
@property(nonatomic, strong) MobileKeysAuthenticationKeySet *mobileKeysAuthenticationKeySet;

/**
 * Not implemented yet. Let us know if this is needed. :)
 */
@property(nonatomic, strong) MobileKeysSymmetricKeyPair *mobileKeysKekKey;

/**
 * If the Seos implementation supports it, this parameter will define whether or not the communication will be
 * performed over the contactless or the contact interface.
 */
@property(nonatomic) BOOL contactless;

/**
 * If this property is set to YES, the SDK will gladly accept payload larger than 255 bytes, and will automatically split
 * these APDUs into multiple commands. Normally, this can be used to PUT data larger than 255 bytes to a tag.
 * Defaults to NO
 */
@property(nonatomic) BOOL autoSplitLargeApduCommands;

/**
 * If the property is set to YES, the SDK will automatically request the next response if a ApduResponse indicates that
 * there is more data to read. Normally, this can be used to GET data from a tag where the data is larger than 255 bytes.
 * Defaults to NO.
 */
@property(nonatomic) BOOL autoJoinMultipleApduResponses;

/**
 * If this parameter is set to YES, the session will initially select the Seos application by it's AID.
 * Default value is YES.
 */
@property(nonatomic) BOOL requireSelectAid;
/**
 * If this parameter is YES, the mutual authentication to Seos will be performed using hard-coded test vectors
 * according to the Seos Specification.
 */
@property(nonatomic) BOOL useTestVectors;
/**
 * A list of OIDs that will be used when selecting the ADF or the GDF. It is possible to pass multiple OIDs,
 * and Seos will try to select them in the order in which they are specified. Only one OID will be selected however,
 * and the OID of the successfully selected file will be returned by the MobileKeysSeosProvider#openSessionWithParams:withError:
 * method
 *
 * Seos supports partial selects, and keep in mind that if multiple keys match a partial OID selection, the first found key
 * (undefined order) will be selected. 
 */
@property(nonatomic, strong) NSArray <NSData *> *oidSelectionList;

/**
 * A timeout when acquiring a seos session, since Seos can only handle one session at time. Defaults to "0" meaning that session opening fails immediately if Seos is busy.
 * If this is set to a positive number larger than zero, the thread will lock and wait for the specified amount waiting for a Seos session to become
 * available. If no session can be opened within timeout seconds, the session opening will fail.
 * The timeout needs to be specified in miliseconds.
 * @since 6.1.0 The timeout needs to be specified in miliseconds. This change was neccessary to avoid bugs in 5.5.0
 */
@property(nonatomic) NSInteger timeoutInMilliSeconds;

/**
 * A dictionary of options to pass to the ApduConnectionProtocol instance on setup. This dictionary will be passed "as is"
 * to the MobileKeysApduConnectionProtocol when the session is opened. The actual options themselves are implementation
 * specific. If this property is nil, no options will be passed.
 */
@property (nonatomic, strong) NSDictionary  *apduConnectionPreSessionSetupOptions;

/**
 * A dictionary of options to pass to the ApduConnectionProtocol instance on teardown. This dictionary will be passed "as is"
 * to the MobileKeysApduConnectionProtocol when the session is closed. The actual options themselves are implementation
 * specific. If this property is nil, no options will be passed.
 */
@property (nonatomic, strong) NSDictionary  *apduConnectionPostSessionTeardownOptions;


/**
 * Constructs a `MobileKeysSessionParameters` using the selected parameters
 *
 * @param mobileKeysSelectionType           the type of Selection to be performed. Specifies the type of select (ADF or GDF) to use in the session
 * @param mobileKeysPrivacyKeySet           the privacy credential to use to protect privacy during ADF/GDF selection
 * @param mobileKeysAuthenticationKeySet    authentication credential to use during mutual authentication. If no authentication key is specified, no mutual authentication will be performed during session establishment.
 * @return                                  an instance of `MobileKeysSessionParameters`
 */
- (instancetype)initWithMobileKeysSelectionType:(MobileKeysSelectionType)mobileKeysSelectionType mobileKeysPrivacyKeySet:(MobileKeysPrivacyKeySet *)mobileKeysPrivacyKeySet mobileKeysAuthenticationKeySet:(MobileKeysAuthenticationKeySet *)mobileKeysAuthenticationKeySet;

/**
 * Constructs a `MobileKeysSessionParameters` using the selected parameters
 *
 * @param mobileKeysSelectionType           the type of Selection to be performed. Specifies the type of select (ADF or GDF) to use in the session
 * @param mobileKeysPrivacyKeySet           the privacy credential to use to protect privacy during ADF/GDF selection
 * @return                                  an instance of `MobileKeysSessionParameters`
 */
- (instancetype)initWithMobileKeysSelectionType:(MobileKeysSelectionType)mobileKeysSelectionType mobileKeysPrivacyKeySet:(MobileKeysPrivacyKeySet *)mobileKeysPrivacyKeySet;

/**
 * Constructs a `MobileKeysSessionParameters` using the selected parameters
 *
 * @param mobileKeysSelectionType           the type of Selection to be performed. Specifies the type of select (ADF or GDF) to use in the session
 * @return                                  an instance of `MobileKeysSessionParameters`
 */
- (instancetype)initWithMobileKeysSelectionType:(MobileKeysSelectionType)mobileKeysSelectionType;

+ (instancetype)parametersForNoSecurityWithSelectAid:(BOOL)shouldSelectAid contacless:(BOOL)contactless;

+ (instancetype)parametersForMobileKeysBle;

+ (instancetype)parametersForMobileKeysTsm;

+ (instancetype)parametersForMobileKeysCache;

+ (instancetype)parametersForMobileKeysReadback;

- (instancetype)initWithContactless:(BOOL)contactless;

+ (instancetype)parametersWithContactless:(BOOL)contactless;


/**
 * Converts a number from it's numbered representation to the enum defined by the SDK.
 * It will return `MOBILE_KEYS_ENCRYPTION_ALGO_ERROR` if the encryption algorithm is unsupported or not known
 * @param number a number to convert
 * @return a MobileKeysEncryptionAlgorithm
 */
+ (MobileKeysEncryptionAlgorithm)encryptionAlgorithmForNumber:(Byte)number;

/**
 * Converts a number from it's numbered representation to the enum defined by the SDK.
 * It will return `MOBILE_KEYS_HASH_ALGO_ERROR` if the hash algorithm is unsupported or not known
 * @param number a number to convert
 * @return a MobileKeysHashAlgorithm
 */
+ (MobileKeysHashAlgorithm)hashAlgorithmForNumber:(Byte)number;

/**
 * Converts a MobileKeysEncryptionAlgorithm to it's numbered representation
 * @param algorithm a MobileKeysEncryptionAlgorithm to convert
 * @return a number
 */
+ (Byte)numberForEncryptionAlgorithm:(MobileKeysEncryptionAlgorithm)algorithm;

/**
 * Converts a MobileKeysHashAlgorithm to it's numbered representation
 * @param algorithm a MobileKeysHashAlgorithm to convert
 * @return a number
 */
+ (Byte)numberForHashAlgorithm:(MobileKeysHashAlgorithm)algorithm;

/**
 * Convenience method for setting a single oid to select during Seos Session opening
 * @param singleOid
 * @since 6.0.0
 */
 -(void) setSingleOidSelection:(NSData *) singleOid;

@end
