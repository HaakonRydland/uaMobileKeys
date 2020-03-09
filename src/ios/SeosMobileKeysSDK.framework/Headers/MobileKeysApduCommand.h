// MobileKeysApduCommand.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

/**
 * The APDU Command Superclass. Use this class either to construct APDU Commands from raw APDU data, or subclass it.
 * This class WILL allow APDUs with larger payloads than 255 bytes
 *
 * @see <a href="http://en.wikipedia.org/wiki/Smart_card_application_protocol_data_unit">APDU format overview on Wikipedia</a>
 * @note since version 5.0.0
 */
@interface MobileKeysApduCommand : NSObject
/**
 * APDU Class. Also flags for secure messaging.
 */
@property(nonatomic) Byte cla;

/**
 * APDU Instruction
 */
@property(nonatomic) Byte ins;

/**
 * Parameter one
 */
@property(nonatomic) Byte p1;

/**
 * Parameter two
 */
@property(nonatomic) Byte p2;

/**
 * Expected length of response
 */
@property(nonatomic) Byte lengthExpected;

/**
 * APDU Payload
 */
@property(nonatomic, strong) NSData *payloadData;

/**
 * Enable always appending Le byte to APDU command
 */
@property(nonatomic) BOOL usesLengthExpected;

/**
 * Initialize the APDU command.
 *
 * @param cla class byte
 * @param ins instruction
 * @param p1 parameter one
 * @param p2 parameter two
 * @return an instantiated ApduCommand
 */
- (instancetype)initWithClass:(Byte)cla instruction:(Byte)ins param1:(Byte)p1 param2:(Byte)p2;

/**
 * Parse a raw data blob consisting of a APDU header, payload and a optional Le / length expected Byte
 * @param data The raw data of the APDU
 * @return an instantiated ApduCommand
 */
- (instancetype)initWithRawData:(NSData *)data;

/**
 * Extracts the full APDU data
 * @return a NSData * containing the APDU Bytes
 */
- (NSData *)toBytes;

/**
 * Extracts the APDu Header
 * @return the four header bytes
 */
- (NSData *)header;

/**
 * Turns on Secure Messaging for the APDU. Will set the secure messaging bits of the APDU Class byte
 */
- (void)enableSecureMessaging;

/**
 * Turns on chaining for the APDU. Will set the chaining bit of the APDU Class byte.
 */
- (void)enableChaining;

/**
 * Check if the APDU uses secure messaging
 * @return YES if the secure messaging flags are set on the APDU Class byte
 */
- (BOOL)usesSecureMessaging;

/**
 * Check if the APDU uses command chaining
 * @return YES if the chaining flag are set on the APDU Class byte
 */
- (BOOL)usesChaining;

/**
 * Certain APDU commands are always sent in clear (e.g. getChallenge etc)
 * @return NO if this APDU always gets sent in clear
 */
-(BOOL) supportsSecureMessaging;


/**
 * Copy the header, optionally setting the APDU Class flags for secureMessaging and chaining.
 * @param secureMessaging If YES, set the secureMessaging flags
 * @param chaining If YES, set the Chaining flags
 * @return A copy of the APDU without payload, with the requested Header flags set.
 */
- (MobileKeysApduCommand *)copyHeaderWithSecureMessaging:(BOOL)secureMessaging chaining:(BOOL)chaining;

- (BOOL)validateWithError:(NSError **)error;
@end
