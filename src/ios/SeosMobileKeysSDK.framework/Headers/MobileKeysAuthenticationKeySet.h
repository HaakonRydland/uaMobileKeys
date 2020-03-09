// MobileKeysAuthenticationKeySet.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>
#import "MobileKeysSelectionResult.h"
#import "MobileKeysSessionParameters.h"

/**
 * Interface for authentication credentials used during mutual authentication with Seos
 * @note since version 5.0.0
 */
@interface MobileKeysAuthenticationKeySet : NSObject

/**
 * The key number for this credential. When authenticating to the card,
 * you specify which key on the card to use. This reference must point to the
 * key used for authentication. E.g. when authenticating with key DF72 on the
 * card, the key reference must be set to MOBILE_KEYS_KEY_2.
 */
@property(nonatomic) MobileKeysKeyNumber keyNumber;

/**
 * The `MobileKeysSymmetricKeyPair` to use for encryption and MAC calculations during authentication.
 */
@property(nonatomic, strong) MobileKeysSymmetricKeyPair * symmetricKeyPair DEPRECATED_MSG_ATTRIBUTE("Use authenticationKeysWithSelectionResult:");

/**
 * If this authentication keyset references a global key or not.
 */
@property(nonatomic) BOOL global;

/**
 * The Encryption algorithm used.
 */
@property(nonatomic) MobileKeysEncryptionAlgorithm encryptionAlgorithm;

/**
 * Initialize
 *
 * @param keyNumber             the key number for this credential.
 * @param symmetricKeyPair      the key pair to use for encryption and MAC calculations during authentication.
 * @param encryptionAlgorithm   the encryption algorithm to use during authentication
 * @param global                yes if this key references a global key
 */
- (instancetype)initWithKeyNumber:(MobileKeysKeyNumber)keyNumber symmetricKeyPair:(MobileKeysSymmetricKeyPair *)symmetricKeyPair encryptionAlgorithm:(MobileKeysEncryptionAlgorithm)encryptionAlgorithm global:(BOOL)global;

/**
 * Get the `MobileKeysSymmetricKeyPair` used for encryption and MAC calculations during authentication.
 *
 * @param result Information about selected OID and it's diversifier.
 * @return the key pair used for encryption and MAC calculation.
 */
- (MobileKeysSymmetricKeyPair *)authenticationKeysWithSelectionResult:(MobileKeysSelectionResult *)result;

/**
 * The MobileKeysKeyNumber as a Byte number. For example, MOBILE_KEYS_KEY_2 will return 0x02
 * @return a Byte representing the keynumber.
 */
- (Byte)keyRef;
@end
