// MobileKeysSessionParameters.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import "MobileKeysSessionParameters.h"

/**
 * Interface for symmetric keys used in Seos authentication and privacy cryptography.
 * @note since version 5.0.0
 */
@interface MobileKeysSymmetricKeyPair : NSObject

/**
 * The encryption key
 */
@property(nonatomic, strong) NSData *encKey;

/**
 * The mac key
 */
@property(nonatomic, strong) NSData *macKey;

/**
 * The algorithm of the `encKey`
 */
@property(nonatomic) MobileKeysEncryptionAlgorithm encAlg;

/**
 * Constructs a `MobileKeysSymmetricKeyPair` using the specified encryption and mac key
 *
 * @param macKey    the mac key value
 * @param encKey    the encryption key value
 * @param encAlg    the encryption algorithm of the `encKey`
 * @return          an instance of `MobileKeysSymmetricKeyPair`
 */
- (instancetype)initWithMacKey:(NSData *)macKey encKey:(NSData *)encKey encAlg:(MobileKeysEncryptionAlgorithm)encAlg;

/**
 * Constructs a `MobileKeysSymmetricKeyPair` using the specified encryption and mac key.
 * This is a convenience method for using `MOBILE_KEYS_ENCRYPTION_ALGO_AES_128` as the encryption algorithm
 *
 * @param macKey    the mac key value
 * @param encKey    the encryption key value
 * @return          an instance of `MobileKeysSymmetricKeyPair`
 */
- (instancetype)initWithEncKey:(NSData *)encKey macKey:(NSData *)macKey;

@end
