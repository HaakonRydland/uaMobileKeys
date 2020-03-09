// MobileKeysPrivacyKeySet.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>
#import "MobileKeysSessionParameters.h"

/**
 * Privacy keyset to use during Seos session establishment.
 * @note since version 5.0.0
 */
@interface MobileKeysPrivacyKeySet : NSObject

/**
 * Set this to YES to enable privacy.
 */
@property(nonatomic) BOOL usesPrivacy;

/**
 * The key number for this credential. When authenticating to the card,
 * you specify which key on the card to use. This reference must point to the
 * key used for authentication. E.g. when authenticating with key DF72 on the
 * card, the key reference must be set to MOBILE_KEYS_KEY_2.
 */
@property(nonatomic) MobileKeysKeyNumber keyNumber;

/**
 * The `MobileKeysSymmetricKeyPair` to use for encryption in the Seos Session.
 */
@property(nonatomic, strong) MobileKeysSymmetricKeyPair * symmetricKeyPair;

/**
 * The Encryption algorithm used.
 */
@property(nonatomic) MobileKeysEncryptionAlgorithm encryptionAlgorithm;

/**
 * Creates an instance of a MobileKeysPrivacyKeySet object
 * @param keyNumber             the key number for this credential
 * @param symmetricKeyPair      the symmetric key pair to use for encryption in this session
 * @param encryptionAlgorithm   The encryption algorithm to use
 * @return                      an instance of MobileKeysPrivacyKeySet
 */
- (instancetype)initWithKeyNumber:(MobileKeysKeyNumber)keyNumber symmetricKeyPair:(MobileKeysSymmetricKeyPair *)symmetricKeyPair encryptionAlgorithm:(MobileKeysEncryptionAlgorithm)encryptionAlgorithm;

/**
 * Initialize a keyset without privacy for unencrypted Seos sessions.
 *
 * @param keyNumber             the key number for this credential
 * @return                      an instance of MobileKeysPrivacyKeySet
 */
- (instancetype)initWithWithoutPrivacyWithKeyNumber:(MobileKeysKeyNumber)keyNumber;

/**
 * The MobileKeysKeyNumber as a uint8_t number. For example, MOBILE_KEYS_KEY_2 will return 0x02
 * @return a uint8_t representing the keynumber.
 */
-(Byte) keyRef;

@end
