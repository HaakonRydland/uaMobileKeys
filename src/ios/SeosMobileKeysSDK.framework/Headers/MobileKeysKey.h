// MobileKeysKey.h
// Copyright (c) 2014 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Representation of a mobile key. This object contains metadata available for the mobile key.
 * Cryptographic keys and data are never exposed outside of the secure element.
 *
 * @note Please note that the NSDate objects
 * describing the "beginDate" (valid from) and the "endDate" (valid to) data is always describing UTC times,
 * and will have to be localized appropriately before displaying to the User.
 */
@interface MobileKeysKey : NSObject

/**
 * The type of this key.
 */
@property(nonatomic, assign) Byte credentialType;

/**
 * Get the validity start date for this key.
 * @note
 * <ul>
 * <li>This information is only metadata, no automatic revocation or anything like that will
 * be performed based on this data</li>
 * <li>This field is optional</li>
 * </ul>
 *
 * @return The key validity start date, or nil if no date was provided when issuing this key.
 */
@property(nonatomic, strong) NSDate *beginDate;

/**
 * Get the validity end date for this key.
 * @note
 * <ul>
 * <li>This information is only metadata, no automatic revocation or anything like that will
 * be performed based on this data</li>
 * <li>This field is optional</li>
 * </ul>
 *
 * @return The key validity end date, or nil if no date was provided when issuing this key.
 */
@property(nonatomic, strong) NSDate *endDate;

/**
 * Identifier of this key. The OID.
 *
 * @note that this value is HEX encoded (02020202) and is not using the OID dot notation (2.2.2.2)
 * @return The identifier of this key.
 */
@property(nonatomic, strong) NSString *keyId;

/**
 * Get the external id of this key, as specified by the system issuing the key.
 *
 * @return The external id of this key.
 */
@property(nonatomic, strong) NSString *externalId;

/**
 * Get the label of this key.
 *
 * @return The label of this key.
 */
@property(nonatomic, strong) NSString *label;

/**
 * Get additional configuration data for this key. What resource this URL points to is up to the
 * application and key issuer to agree on. This field is optional.
 *
 * @return An configuration URL, or null if no URL was provided when the key was issued.
 */
@property(nonatomic, strong) NSString *configUrl;

/**
 * Get the readback URL from this key. See the TSM documentation to learn more about Readback.
 */
@property(nonatomic, strong) NSString *readbackUrl;

/**
 * Get the ID of the issuer who issued this key.
 *
 * @return ID of the issuer who issued this key.
 */
@property(nonatomic, strong) NSString *issuer;

/**
 * Get the type of this key.
 *
 * @return The type of this key.
 */
@property(nonatomic, strong) NSString *keyType;

/**
 * Get the card number of this key. This field is optional.
 *
 * @return The card number of this key, or nil if no card number was provided when the key was issued.
 */
@property(nonatomic, strong) NSString *cardNumber;

/**
 * Check if this key is active. The key is always active unless explicitly deactivated.
 *
 * @return YES if the key is active, otherwise NO.
 */
@property(nonatomic) BOOL active;

/**
 * A dictionary of additional metadata on the ADF. Normally this could include tags 0x8b to 0x9f
 *
 */
@property(nonatomic, strong) NSDictionary < NSNumber* , NSData* > * additionalMetaData;

/**
* This can be used to produce a pseudo-unique identifier of this particular key.
* Please note that this is only unique for keys on this Endpoint.
*/
- (NSString *)uniqueIdentifier;

/**
 * Utility method for checking if the endDate property is in the past and not the future
 * @return YES if the key endDate property is in the future or is nil, otherwise NO.
 */
- (BOOL)isExpired;

/**
 * Check if this key supports one time password generation
 */
- (BOOL)supportsOTP;

@end
