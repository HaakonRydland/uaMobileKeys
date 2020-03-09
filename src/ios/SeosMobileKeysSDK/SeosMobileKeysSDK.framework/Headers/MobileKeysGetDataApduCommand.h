// MobileKeysGetDataApduCommand.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import "MobileKeysApduCommand.h"
#import "MobileKeysSeosTag.h"

/**
 * Interface for constructing a get data APDU command.
 *
 * @note since version 5.0.0
 */
@interface MobileKeysGetDataApduCommand : MobileKeysApduCommand

/**
 * Creates an instance of a MobileKeysGetDataApduCommand object.
 *
 * @param tag               the tag on the DF to get data from
 * @param selectorTag       the tag descriptor to use
 * @param secureMessaging   enable or disable secure messaging
 */
- (instancetype)initWithTag:(MobileKeysSeosTag *)tag selectorTag:(NSData *)selectorTag secureMessaging:(BOOL)secureMessaging;

/**
 * Creates an instance of a MobileKeysGetDataApduCommand object without secure messaging.
 *
 * @param tag Get data from Seos tag
 */
- (instancetype)initWithTag:(MobileKeysSeosTag *)tag;

/**
 * Creates an instance of a MobileKeysGetDataApduCommand object.
 *
 * @param tag Get data from Seos tag
 * @param secureMessaging Set to Yes to enable secure messaging

 */
- (instancetype)initWithTag:(MobileKeysSeosTag *)tag secureMessaging:(BOOL)secureMessaging;

@end
