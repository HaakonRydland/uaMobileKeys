// MobileKeysApduConnectionProtocol.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>

/**
 * Interface for sending APDU commands to, and receiving APDU responses from a Seos card.
 *
 * How implementations of this interface would look depends on where the API is used,
 * for instance the local file system, Bluetooth, NFC, USB or WIFI, etc.
 * @note since version 5.0.0
 */
@protocol MobileKeysApduConnectionProtocol <NSObject>

/**
 * To check if there is already an ongoing connection using this ApduConnection
 * @return YES if there is an already open connection
 * @since 6.0.0
 */
-(BOOL) activeConnection;
/**
 * For APDUConnections that require special setup before apdu processing is initiated, you can implement this
 * protocol method to do such processing.
 * Examples of this could be that the APDU Connetion could connect to an external Seos Implementation, or load state
 * from file, or anything that needs to be performed before the Seos Implementation is ready to start accepting
 * APDU Commands.
 * @param contactLess = YES if the session is made over the contactless inteface
 * @param error if something went wrong this parameter is set, otherwise nil.
 * @deprecated since 5.1.5
 * @return YES if everything went OK.
 */
- (BOOL)preSessionSetup:(BOOL)contactLess withError:(NSError *_Nullable*_Nullable)error __attribute__ ((deprecated));

/**
 * For APDUConnections that require special setup before apdu processing is initiated, you can implement this
 * protocol method to do such processing.
 * Examples of this could be that the APDU Connetion could connect to an external Seos Implementation, or load state
 * from file, or anything that needs to be performed before the Seos Implementation is ready to start accepting
 * APDU Commands.
 * @param options A NSDictionary of implementation specific options.
 * @param contactLess = YES if the session is made over the contactless inteface
 * @param error if something went wrong this parameter is set, otherwise nil.
 * @return YES if everything went OK.
 */
- (BOOL)preSessionSetupWithOptions:( NSDictionary *_Nullable)options contactless:(BOOL)contactLess withError:(NSError *_Nullable*_Nullable)error;


/**
 * For APDUConnections that require special processing when the session has been closed, you can implement this optional
 * protocol method to do such processing. Examples of this could be tearing down TCP sessions, encrypting and storing state etc.
 * @param error if something went wrong, otherwise nil.
 * @return YES if everything went OK
 */
- (BOOL)postSessionTearDown:(NSError *_Nullable*_Nullable)error __attribute__ ((deprecated));
/**
 * For APDUConnections that require special processing when the session has been closed, you can implement this optional
 * protocol method to do such processing. Examples of this could be tearing down TCP sessions, encrypting and storing state etc.
 * @param options A NSDictionary of implementation specific options.
 * @param error if something went wrong, otherwise nil.
 * @return YES if everything went OK
 */
- (BOOL)postSessionTearDownWithOptions:( NSDictionary *_Nullable)options withError:(NSError *_Nullable*_Nullable)error;

/**
 * Sends an APDU command and receives a response from the Seos applet. This is a raw APDU processing interface.
 *
 * @param data The data command to send.
 * @return The result from Seos processing the command.
 */
- (NSData *_Nonnull)processApdu:(NSData *_Nonnull)data;

/**
 * Indicate to the Apdu Connection protocol that it should use test vectors.
 * @param enableTestVectors
 */
- (void)enableTestVectors:(BOOL)enableTestVectors;

@end
