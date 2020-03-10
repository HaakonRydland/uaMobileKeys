// MobileKeysMotionRecognizer.h
// Copyright (c) 2013 ASSA ABLOY Mobile Services ( http://assaabloy.com/seos )
//
// All rights reserved.

#import <Foundation/Foundation.h>
#import "MobileKeysReader.h"

/**
 * The client who wishes to receieve callbacks when the Twist and Go motion has been detected.
 */
@protocol MobileKeysMotionRecognizerDelegate <NSObject>
- (void)userMadeUnlockGesture:(MobileKeysOpeningType)openingType;
@end

@protocol MotionRecognizerProtocol

- (void)startTrackingRotation;
- (void)stopTrackingRotation;
-(void) pauseTrackingRotation;
-(void) resumeTrackingRotation;
- (BOOL)isTrackingRotation;
@end
/**
 * Implementation of the ASSA ABLOY patented Twist and Go motion. The user turns his phone in one direction
 * and then back again, simulating turning a door knob.
 *
 * Since version 7.0.0, the usage has changed slightly, the main reason for this is to preserve resources and minimize memory allocation
 * overhead.
 *
 * From version 7.0.0, use -[MobileKeysMotionRecognizer startTrackingRotation] to start the thread that monitors twist & go movements. To pause tracking, use
 * -[MobileKeysMotionRecognizer pauseTrackingRotation] and to resume trtacking use -[MobileKeysMotionRecognizer resumeTrackingRotation].
 *
 * @warning Opening the closest reader using Twist and Go is already supported by the SDK. Simply pass
 * `+[MobileKeysOpeningType MobileKeysOpeningTypeMotion]` as a one of the values in the array of `supportedOpeningTypes`
 * when calling `-[MobileKeysManager startReaderScanInMode:supportedOpeningTypes:lockServiceCodes:error:]`.
 * You (the integrator) should only use this class if the default Twist and Go opening implementation in the SDK does not cover
 * your specific use case.
 *
 * @note to preserve power, please use the `-[MobileKeysMotionRecognizer pauseTrackingRotation]` and
 * `-[MobileKeysMotionRecognizer resumeTrackingRotation]` when your use case does not mandate that the Twist and Go
 * motion pattern shouldn't be detected.
 */
@interface MobileKeysMotionRecognizer : NSObject <MotionRecognizerProtocol>

@property(weak, nonatomic) id <MobileKeysMotionRecognizerDelegate> internalDelegate DEPRECATED_MSG_ATTRIBUTE("This property will be renamed to delegate");
@property(strong, nonatomic) dispatch_queue_t queue;

/**
 * Initializes the `MobileKeysMotionRecognizer`
 * delegate of `MobileKeysMotionRecognizerDelegate` to send callbacks to.
 */
- (instancetype)initWithDelegate:(id<MobileKeysMotionRecognizerDelegate>)delegate NS_DESIGNATED_INITIALIZER;

/**
 * The class overrides `-[NSObject dealloc]` to unregister itself from the `CMMotionManager` upon deallocation
 */
- (void)dealloc;

/**
 * Start the tracker. From version 7.0.0, the tracker will start in "paused" mode. To enable tracking, call the -[MobileKeysMotionRecognizer resumeTrackingRotation] function.
 */
- (void)startTrackingRotation;

/**
 * Stop listening to the gyroscope and free resources. This method is not really needed anymore, to pause tracking use  -[MobileKeysMotionRecognizer pauseTrackingRotation] instead.
 */
- (void)stopTrackingRotation;

/**
 * This will pause the motion tracking. The tread monitoring twist & go will enter a wait state, and should no longer consume processing resources.
 */
-(void) pauseTrackingRotation;
/**
 * This will pause the motion tracking. The tread monitoring twist & go will leave the wait state, and will monitor the gyroscope.
 */
-(void) resumeTrackingRotation;
/**
 * @return YES if the MobileKeysMotionRecognizer is currently listening for callbacks from the `CMMotionManager`, otherwise NO.
 */
- (BOOL)isTrackingRotation;

@end
