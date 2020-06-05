// MobileKeysSelectionResult.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>
#import "MobileKeysSessionParameters.h"

/**
 * Describes the result of ADF/GDF selection.
 */
@interface MobileKeysSelectionResult : NSObject

/**
 * Constructs a selection result from the specified parameters.
 *
 * @param hashAlgorithm     hash algorithm used by the selected Seos card.
 * @param encAlgorithm      encryption algorithm used by the selected Seos card.
 * @param selectedAdf       oid of the selected ADF.
 * @param diversifier       diversifier of the selected ADF.
 * @return                  an instance of MobileKeysSelectionResult
 */
- (instancetype)initWithHashAlgorithm:(MobileKeysHashAlgorithm)hashAlgorithm encAlgorithm:(MobileKeysEncryptionAlgorithm)encAlgorithm selectedAdf:(NSData *)selectedAdf diversifier:(NSData *)diversifier;

/**
 * Get the hash algorithm used by the selected ADF.
 *
 * @return the hash algorithm used by the selected ADF.
 */
@property(nonatomic) MobileKeysHashAlgorithm hashAlgorithm;

/**
 * Get the encryption algorithm used by the selected ADF.
 *
 * @return the encryption algorithm used by the selected ADF.
 */
@property(nonatomic) MobileKeysEncryptionAlgorithm encAlgorithm;

/**
 * Get the OID of the selected ADF.
 *
 * @return the OID of the selected ADF.
 */
@property (nonatomic) NSData * selectedOid;

/**
 * Get the diversifier used by the selected ADF.
 *
 * @return the diversifier used by the selected ADF.
 */
@property (nonatomic) NSData * diversifier;

@end
