// MobileKeysSeosProvider.h
// Copyright (c) 2016 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved

#import "MobileKeysApduConnectionProtocol.h"
#import "MobileKeysSessionParameters.h"

@class MobileKeysSessionParameters;
@class MobileKeysApduResponse;
@class MobileKeysApduCommand;
@class MobileKeysSeosSession;

/**
 * This MobileKeysSeosProvider is the interface to access a Seos instance on a lower level than through the
 * MobileKeysManager.
 *
 * @warning Due to the single threaded nature of Seos, only one session can be opened at once. If
 * you (the integrator) try to open a session while another session is currently open. An error will be set with the error code
 * `MobileKeysErrorCodeSDKBusy`.
 * @note Use the `description` parameter while opening sessions using this provider to gain more insight about it's sessions
 * @note since version 5.0.0
 */
@interface MobileKeysSeosProvider : NSObject

/**
 * Constructs a `MobileKeysSeosProvider` using the selected `MobileKeysApduConnectionProtocol`
 * @param apduConnection    the APDU connection to use in this instance
 * @return                  an instance of `MobileKeysSeosProvider`
 */
- (instancetype)initWithConnection:(id <MobileKeysApduConnectionProtocol>)apduConnection;

/**
 * Check if a session is currently open. This will call the "activeConnection" method of the current session, if one
 * is available.
 * @return YES if session is open.
 */
- (BOOL)isOpen;

/**
 * Check if a session is open, by the specified sessionIdentifier. Can be used before closing a session,
 * to make sure that the session is opened by a specific client.
 * @param sessionIdentifier A mobileKeysSessionIdentifier
 * @return YES if there is an active session, opened by the specified client
 */
- (BOOL)isOpenForClient:(MobileKeysSessionClientIdentifier) sessionIdentifier;

/**
 * If a session is currently open this method will return the current client. The method will return the value
 * "Seos Access API Client" or "Remote Client" if it's currently opened by the integrator (you).
 * If there is no session open this method will return nil.
 * @return the current client of the MobileKeysSeosProvider Seos provider if there is one.
 */
- (NSString *)currentSessionClient;

/**
 * Check if the ongoing session is a remote session.
 * @return YES if a session is open and of type remote session.
 */
- (BOOL)isRemoteSession DEPRECATED_MSG_ATTRIBUTE("No longer used, will always return NO");

/**
 * Use this method to setup a Seos session to a card Seos Instance using a terminal SeosProvider (with an authenticated
 * Seos session) where AKE is used to authenticate. To use AKE to setup a secure connection, the following is required:
 *  1. An active session to a Terminal through a SeosProvider
 *  2. Card side MobileKeysSessionParameters (e.g. [[MobileKeysSessionParameters alloc] initWithMobileKeysSelectionType:MobileKeysSelectionEmptySeos];
 *  3. The Terminal side Key Number (for AKE)
 *  4. The Card side Key Number (for AKE)
 *
 *  This method assumes that the terminal side provider already has an astablished session.
 *
 *  If the session setup fails during seos session key establishement, this method should close the session before exiting.
 *
 *  Please keep in mind that if the cardSideParameters specify a partial OID for card side key selection, this will
 *  select the first matching (undefined order) key, and the session setup will be attempted towards this key.
 *
 * @param terminalSession an established session to the terminal
 * @param cardSideParameters MobileKeysSessionProviders
 * @param cardKeyNumber The card key number used for Reverse AKE
 * @param terminalKeyNumber The Terminal key number used for reverse AKE
 * @return
 */
- (MobileKeysSeosSession *)establishCardSessionUsingTerminalSession:(MobileKeysSeosSession *)terminalSession cardSideParameters:(MobileKeysSessionParameters *)cardSideParameters cardKeyNumber:(MobileKeysKeyNumber)cardKeyNumber terminalKeyNumber:(MobileKeysKeyNumber)terminalKeyNumber withError:(NSError **)error ;

/**
 * Open a session to the Apdu Connection. This method will make sure that only one session is open at a time. The specific
 * session opening mechanics will be specified by the MobileKeysSessionParameters object. Depending on the parameters, this
 * function will perform some or all of the following functions:
 *  - Create a session
 *  - Select the Seos AID
 *  - Select a specific ADF or GDF using provided parameters
 *  - Perform Mutual Authentication to Seos and set up Encryption parameters
 *
 *  The older methods to establish a session (openSessionWithParams...) did return the selected OID. The selected OID is still available
 *  when using this method, but it is now a propery of the returned session. (MobileKeysSeosSession.currentlySelectedOid)
 *
 * @param sessionParameters     the parameters provided for this session. See MobileKeysSessionParameters for a specification
 * @param description           A free-text description (primarily used when debugging, but required notheless)
 * @param error                 if the session failed to open. The error will contain a code, see MobileKeysErrorCode for a description
 * @return                      a MobileKeysSeosSession object.
 */
- (MobileKeysSeosSession *)establishSessionWithParams:(MobileKeysSessionParameters *)sessionParameters description:(NSString *)description withError:(NSError **)error;

/**
 * Open a session to the Apdu Connection. This method will make sure that only one session is open at a time. The specific
 * session opening mechanics will be specified by the MobileKeysSessionParameters object. Depending on the parameters, this
 * function will perform some or all of the following functions:
 *  - Create a session
 *  - Select the Seos AID
 *  - Select a specific ADF or GDF using provided parameters
 *  - Perform Mutual Authentication to Seos and set up Encryption parameters
 * At this time, this class acts both as a session manager and a session itself.
 *
 * @param sessionParameters     the parameters provided for this session. See MobileKeysSessionParameters for a specification
 * @param error                 if the session failed to open. The error will contain a code, see MobileKeysErrorCode for a description
 * @return                      selected OID or nil if something went wrong
 */
- (NSData *)openSessionWithParams:(MobileKeysSessionParameters *)sessionParameters withError:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use MobileKeysSeosProvider:establishSessionWithParams instead");

/**
 * Open a session to the Apdu Connection. This method will make sure that only one session is open at a time. The specific
 * session opening mechanics will be specified by the MobileKeysSessionParameters object. Depending on the parameters, this
 * function will perform some or all of the following functions:
 *  - Create a session
 *  - Select the Seos AID
 *  - Select a specific ADF or GDF using provided parameters
 *  - Perform Mutual Authentication to Seos and set up Encryption parameters
 * At this time, this class acts both as a session manager and a session itself.
 *
 * @param sessionParameters     the parameters provided for this session. See MobileKeysSessionParameters for a specification
 * @param description           a description about why the session was opened provided by you (the integrator)
 * @param error                 if the session failed to open. The error will contain a code, see MobileKeysErrorCode for a description
 * @return                      selected OID or nil if something went wrong
 */
- (NSData *)openSessionWithParams:(MobileKeysSessionParameters *)sessionParameters description:(NSString *)description withError:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use MobileKeysSeosProvider:establishSessionWithParams instead");

/**
 * Open a session to the Apdu Connection without performing any additional session opening mechanics. This is meant to
 * be used when the other side of the communication is driving the conversation and initiates the authentication. For example
 * a reader at the door.
 *
 * Pass YES as the parameter to requireSelectAid to automatically select the Seos AID when the session opens. Effectively
 * eliminating the need to do it over the air. Please note that these type of sessions will always be considered contactless.
 *
 * @param requireSelectAid      whether or not the MobileKeysSeosProvider should automatically select the Seos AID when the session opens
 * @param error                 if the session failed to open. The error will contain a code, see MobileKeysErrorCode for a description
 * @return                      YES if everything went OK or NO if something went wrong
 */
- (BOOL)openRemoteSessionWithSelectAid:(BOOL)requireSelectAid withError:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use establishSessionWithParams instead");

/**
 * Open a session to the Apdu Connection without performing any additional session opening mechanics. This is meant to
 * be used when the other side of the communication is driving the conversation and initiates the authentication. For example
 * a reader at the door.
 *
 * Pass YES as the parameter to requireSelectAid to automatically select the Seos AID when the session opens. Effectively
 * eliminating the need to do it over the air. Please note that these type of sessions will always be considered contactless.
 *
 * @param shouldSelectAid       whether or not the MobileKeysSeosProvider should automatically select the Seos AID when the session opens
 * @param description           a description about why the session was opened provided by you (the integrator)
 * @param error                 if the session failed to open. The error will contain a code, see MobileKeysErrorCode for a description
 * @return                      YES if everything went OK or NO if something went wrong
 */
- (BOOL)openRemoteSessionWithSelectAid:(BOOL)shouldSelectAid description:(NSString *)description withError:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use establishSessionWithParams instead");

/**
 * Close the current session to the APDU Connection. This will call the "closeSession:" method of the currently open session.
 *
 * @param error                 if something went wrong this parameter is set, otherwise nil.
 * @return                      YES if everything went OK, NO if something went wrong
 */
- (BOOL)closeSeosSession:(NSError **)error DEPRECATED_MSG_ATTRIBUTE("Use [MobileKeysSeosSession closeSessionWithError:] instead");

- (NSData *)reselectWithParams:(MobileKeysSessionParameters *)sessionParameters withError:(NSError **)error;

/**
 * Sends an APDU command and receives a response from the Seos applet.
 *
 * @param apduCommand           the data command to send.
 * @param error                 if something went wrong this parameter is set, otherwise nil.
 * @return                      the response from Seos processing the command or nil if something went wrong
 */
- (MobileKeysApduResponse *)processApduCommand:(MobileKeysApduCommand *)apduCommand withError:(NSError **)error;


@end
