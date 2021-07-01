//
//  NSData+OpeningStatusPayload.h
//  Based on BLE End Node Protocol V2.1 Draft 4
//
//  Created by Hospitality on 2016-09-09.
//  Copyright © 2016 Assa Abloy Hospitality. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger,ReaderResultDataFormat) {
    ReaderResultDataFormatStandard = 0x01,
    ReaderResultDataFormatUnknown = -1
};

typedef NS_ENUM(NSInteger,UnlockReason) {
    UnlockReasonOpenedByGuestKey = 0x01,
    UnlockReasonOpenedByStaffKey = 0x10,
    UnlockReasonOpenedBySpecialKey = 0x20,
    UnlockReasonNotApplicable = -1
} ;

typedef NS_ENUM(NSInteger,DidNotUnlockReason) {
    DidNotUnlockReasonKeyIsOverridden = 0x40,
    DidNotUnlockReasonKeyIsNotValidYet = 0x41,
    DidNotUnlockReasonKeyHasExpired = 0x42,
    DidNotUnlockReasonKeyIsCancelled = 0x43,
    DidNotUnlockReasonKeyGroupIsBlocked = 0x44,
    DidNotUnlockReasonKeyHasNoAccessToThisRoom = 0x45,
    DidNotUnlockReasonKeyHasNoAccessToThisFacility = 0x46,
    DidNotUnlockReasonKeyNotValidAtThisTimeOfDay = 0x47,
    DidNotUnlockReasonKeyBlockedBecauseOfDeadbolt = 0x48,
    DidNotUnlockReasonKeyBlockedBecauseOfRoomPrivacySetting = 0x49,
    DidNotUnlockReasonKeyBlockedBecauseOfDoorBatteryLevel = 0x4a,
    DidNotUnlockReasonKeyBlockedByAntiPassbackFunction = 0x4b,
    DidNotUnlockReasonKeyRefusedBecauseDoorIsNotLocked = 0x4c,
    DidNotUnlockReasonKeyRefusedDueToPINCode = 0x4d,
    DidNotUnlockReasonKeyBlockedByAccessRules = 0x4e,
    DidNotUnlockReasonNotApplicable = -1
};


typedef NS_ENUM(NSInteger,DetailedUnlockReason) {
    // 0x01 Door opened by guest key
    DetailedUnlockReasonOpeningWithGuestCard = 0x0043,
    DetailedUnlockReasonOpeningWithGuestSuiteCard = 0x0044,
    DetailedUnlockReasonOpeningByGuestInCommonRoom = 0x0045,
    DetailedUnlockReasonOpeningWithFutureArrivalCard = 0x0046,
    DetailedUnlockReasonOpeningWithOneTimeCard = 0x0048,
    DetailedUnlockReasonOpeningByGuestInEntranceDoor = 0x0049,
    
    // 0x10 Door opened by staff key
    DetailedUnlockReasonOpeningWithStaffCard = 0x0040,
    
    // 0x20 Door opened by special key
    DetailedUnlockReasonStandOpenSet = 0x0041,
    DetailedUnlockReasonOpeningWithPowerDownCard = 0x0047,
    DetailedUnlockReasonOpeningWithNTimeCard = 0x004a,
    
    DetailedUnlockReasonNotApplicable = -1
};

typedef NS_ENUM(NSInteger,DetailedDidNotUnlockReason) {
    // 0x40 Key is overridden
    DetailedDidNotUnlockReasonGuestCardOverridden = 0x0010,
    DetailedDidNotUnlockReasonGuestCardOverridden_v2 = 0x0011,
    
    // 0x41 Key is not valid yet
    DetailedDidNotUnlockReasonCardNotValidYet = 0x0012,
    
    // 0x42 Key has expired
    DetailedDidNotUnlockReasonCardHasExpired = 0x0142,
    
    // 0x43 Key is cancelled
    DetailedDidNotUnlockReasonCardCancelled = 0x0017,
    
    // 0x44 Key group is blocked
    DetailedDidNotUnlockReasonCardUsergroupBlocked = 0x0018,
    
    // 0x45 Key has no access to this room
    DetailedDidNotUnlockReasonNoAccessToThisRoom = 0x0140,
    
    // 0x46 Key has no access to this hotel
    DetailedDidNotUnlockReasonWrongSystemNumberOnCard = 0x0105,
    
    // 0x47 Key not valid at this time of day
    DetailedDidNotUnlockReasonNotValidAtThisTime = 0x0016,
    DetailedDidNotUnlockReasonCardOnlyValidDuringOpeningTime = 0x0020,
    
    // 0x48 Key blocked because of deadbolt
    DetailedDidNotUnlockReasonDoorUnitDeadBolted = 0x0021,
    DetailedDidNotUnlockReasonDoorUnitDeadBoltedGuest = 0x0022,
    DetailedDidNotUnlockReasonDoorUnitDeadBoltedFamily = 0x0023,
    
    // 0x49 Key blocked because of room privacy setting
    DetailedDidNotUnlockReasonNotValidDueToPrivacyStatus = 0x0026,
    DetailedDidNotUnlockReasonNotValidDueToPrivacyStatusSilent = 0x0027,
    DetailedDidNotUnlockReasonNotValidDueToDoNotDisturbStatus = 0x002b,
    
    // 0x4a key blocked because of door battery level
    DetailedDidNotUnlockReasonAccessDeniedDueToBatteryAlarm = 0x0035,
    
    // 0x4b Key blocked by anti passback function
    DetailedDidNotUnlockReasonNotValidDueToAntiPassback = 0x0015,
    
    // 0x4c Key refused because door is not locked
    DetailedDidNotUnlockReasonNotValidDueToDoorNotClosed = 0x0024,
    DetailedDidNotUnlockReasonNotValidDueToOpenStatus = 0x0025,
    
    // 0x4d Key refused due to PIN code
    DetailedDidNotUnlockReasonWrongPIN = 0x0013,
    DetailedDidNotUnlockReasonWrongPIN_v2 = 0x0019,
    
    // 0x4e Blocked by access rules
    DetailedDidNotUnlockReasonCommandNotValidForThisLock = 0x001a,
    DetailedDidNotUnlockReasonCounterValueTooLow = 0x0014,
    DetailedDidNotUnlockReasonNotValidDueToPassageRevoked = 0x0028,
    
    DetailedDidNotUnlockReasonNotApplicable = -1
};

typedef NS_ENUM(NSInteger,ReaderBatteryStatus) {
    ReaderBatteryStatusGood = 0x00,
    ReaderBatteryStatusWarning = 0x01,
    ReaderBatteryStatusCritical = 0x02,
    ReaderBatteryStatusInvalid = -1
};

typedef NS_ENUM(NSInteger,AccessControlSystem) {
    AccessControlSystemVisionline = 0x01,
    AccessControlSystemVostio = 0x02,
    AccessControlSystemUknown = -1
};

@interface NSData (OpeningStatusPayload)

- (BOOL)containsData;
- (BOOL)didUnlock;
- (UnlockReason)unlockReason;
- (DidNotUnlockReason)didNotUnlockReason;
- (DetailedUnlockReason)detailedUnlockReason;
- (DetailedDidNotUnlockReason)detailedDidNotUnlockReason;
- (nonnull NSString *)doorId;
- (ReaderBatteryStatus)readerBatteryStatus;
- (AccessControlSystem)accessControlSystem;
- (nonnull NSString *)firmwareVersionLCU;
- (nonnull NSString *)firmwareVersionBLE;
- (nonnull NSString *)RFU;

- (nonnull NSString*)toStringHex;
+ (nullable NSData*)dataWithHexString:(nonnull NSString*)hexString;
@end
