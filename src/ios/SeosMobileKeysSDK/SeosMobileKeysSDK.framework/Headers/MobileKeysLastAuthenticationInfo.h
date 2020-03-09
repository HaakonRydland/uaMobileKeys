// MobileKeysLastAuthenticationInfo.h
// Copyright (c) 2014 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>

@class MobileKeysKey;

/**
 * Object representing the last authenticated key in the Seos Secure Storage
 */
@interface MobileKeysLastAuthenticationInfo : NSObject

/**
 * @return Returns the `MobileKeysKey` that was authenticated
 * @see MobileKeysKey class
 */
@property(nonatomic, strong) MobileKeysKey *lastAuthenticatedMobileKey;

/**
 * @return a counter representing how many times the key has authenticated with a reader
 */
@property(nonatomic) NSUInteger authenticationCounter;

/**
 * @return whether or not the reader has written anything to the key
 */
@property(nonatomic) BOOL isModified;

@end
