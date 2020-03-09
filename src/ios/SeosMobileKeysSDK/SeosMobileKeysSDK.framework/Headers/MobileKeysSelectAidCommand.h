// MobileKeysPrivacyKeySet.h
// Copyright (c) 2017 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import <Foundation/Foundation.h>
#import "MobileKeysApduCommand.h"

/**
 * The default Seos AID
 */
static unsigned char SEOS_AID[] =      {0xa0, 0x00, 0x00, 0x04, 0x40, 0x00, 0x01, 0x01, 0x00, 0x01};

/**
 * The default Seos AID over HCE
 */
static unsigned char SEOS_HCE_AID[] =  {0xa0, 0x00, 0x00, 0x04, 0x40, 0x00, 0x06, 0x01, 0x00, 0x01};

/**
 * The base for all Seos flavoured AID's
 */
static unsigned char BASE_SOFT_AID[] = {0xa0, 0x00, 0x00, 0x04, 0x40, 0x00, 0x06, 0x01, 0x00, 0x01};

/**
 * APDU Command to do select by AID.
 *
 * @warning this command is sent automatically by passing YES as value of parameter `requireSelectAid`
 * to `-[MobileKeysSeosProvider openRemoteSessionWithSelectAid:withError:]` or by setting
 * `-[MobileKeysSessionParameters requireSelectAid]` to YES when using
 * `-[MobileKeysSeosProvider openSessionWithParams:withError:]`
 */
@interface MobileKeysSelectAidCommand : MobileKeysApduCommand

/**
 * Initializes this object with the default Seos AID
 *
 * @return  an instance of MobileKeysSelectAidCommand
 */
- (instancetype)initWithSeosAid;

/**
 * Initialize this object with a custom AID
 *
 * @param   aidData the AID to use
 * @return  an instance of MobileKeysSelectAidCommand
 */
- (instancetype)initWithCustomAid:(NSData *)aidData;

/**
 * Checks if the passed command is a select by AID command
 * @param command   the command to check
 * @return          YES if the command is a select by AID, NO otherwise
 */
+ (BOOL)isSelectAid:(MobileKeysApduCommand *)command;

/**
 * Checks if the passed data is a supported Seos AID
 * @param aidData   the AID data to check
 * @return          YES if the data is a supported Seos AID, NO otherwise
 */
+ (BOOL)isSupportedSeosAid:(NSData *)aidData;

/**
 * Checks if the passed data is a soft Seos AID
 * @param aidData   the AID data to check
 * @return          YES if the data is a soft Seos AID, NO otherwise
 */
+ (BOOL)isSoftSeosAid:(NSData *)aidData;
@end