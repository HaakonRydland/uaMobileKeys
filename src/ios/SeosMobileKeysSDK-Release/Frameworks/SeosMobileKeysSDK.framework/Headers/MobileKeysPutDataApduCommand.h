// MobileKeysPutDataApduCommand.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import "MobileKeysApduCommand.h"
#import "MobileKeysSeosTag.h"

/**
 * Interface for constructing a put APDU command.
 *
 * @note since version 5.0.0
 */
@interface MobileKeysPutDataApduCommand : MobileKeysApduCommand

/**
 * Creates an instance of a MobileKeysPutDataApduCommand object without secure messaging.
 * @param tag               put data on Seos tag
 * @param data              data to send to Seos Tag
 * @return                  an instance of MobileKeysPutDataApduCommand
 */
- (instancetype)initWithTag:(MobileKeysSeosTag *)tag andData:(NSData *)data;

/**
 * Creates an instance of a MobileKeysPutDataApduCommand object.
 * @param tag               put data on Seos tag
 * @param data              data to send to Seos Tag
 * @param secureMessaging   set to Yes to enable secure messaging
 * @return                  an instance of MobileKeysPutDataApduCommand
 */
- (instancetype)initWithTag:(MobileKeysSeosTag *)tag andData:(NSData *)data secureMessaging:(BOOL)secureMessaging;

@end
