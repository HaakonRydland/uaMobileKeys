// MobileKeysSeosTag.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>

/**
 * Represents a Seos Tag. Use this class in conjunction with MobleKeysGetDataApduCommand and MobileKeysPutDataApduCommand
 * to read and write data to Seos.
 *
 * @note Seos tags uses the DER tag encoding and one or two byte tags are supported.
 * @note since version 5.0.0
 */
@interface MobileKeysSeosTag : NSObject

/**
 * Constructs a seos tag from the given DER encoded tag number.
 *
 * @param tagNumber The DER encoded tag number.
 */
- (instancetype)initWithTagNumber:(NSUInteger)tagNumber;

/**
 * Get the full DER encoded tag.
 *
 * @return The full DER encoded tag.
 */
@property (atomic) NSUInteger tag;

/**
 * Get the tag number of this tag.
 *
 * @return The tag number of this tag.
 */
@property (atomic) NSUInteger tagNumber;

/**
 * Get the full DER encoded tag as a byte array.
 *
 * @return The full DER encoded tag as a byte array.
 */
- (NSData *)toBytes;

/**
 * Check if the tag is constructed.
 *
 * @return YES if the tag is constructed.
 */
- (BOOL)isConstructed;

/**
 * @return a tag descriptor "select all" for tags.
 */
- (NSData *)toTagDescriptorSelectAll;

/**
 * Create a tag descriptor with the specified selector
 * @param   selectorTag the tag selector
 * @return  a tag descriptor with extended header
 */
- (NSData *)toTagDescriptorExtendedHeader:(NSData *)selectorTag;
@end
