// MobileKeysMasterAuthenticationKeySet.h
// Copyright (c) 2017 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>
#import "MobileKeysAuthenticationKeySet.h"

/**
 * Represents a master authentication credential, used to calculate derived keys based on diversification data.
 *
 * @see "Section 2.1 in the Seos Core Technology Specification"
 */
@interface MobileKeysMasterAuthenticationKeySet : MobileKeysAuthenticationKeySet

/**
 * Constructs a master key credential.
 *
 * @param keyNumber   the key number this key should authenticate to.
 * @param global      true of the referred key is global, false if the key number refers to a ADF local key.
 * @param masterKey   the master key data, 16 bytes AES key used to derive card specific keys.
 * @param oid         oid to use during key derivation, selected Oid used if null
 * @param diversifier diversifier to use during key derivation, selected ADF Diversifier used if null
 */
- (instancetype)initWithKeyNumber:(MobileKeysKeyNumber)keyNumber masterKeyData:(NSData *)masterKey oid:(NSData *)oid diversifier:(NSData *)diversifier encryptionAlgorithm:(MobileKeysEncryptionAlgorithm)encryptionAlgorithm global:(BOOL)global;

/**
 * Get the `MobileKeysSymmetricKeyPair` used for encryption and MAC calculations during authentication.
 *
 * @param result Information about selected OID and it's diversifier.
 * @return the key pair used for encryption and MAC calculation.
 */
- (MobileKeysSymmetricKeyPair *)authenticationKeysWithSelectionResult:(MobileKeysSelectionResult *)result;
@end