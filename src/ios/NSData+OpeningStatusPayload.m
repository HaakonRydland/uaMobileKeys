//
//  NSData+OpeningStatusPayload.m
//  Based on "Mobile Access Onboarding - Interpretation of Lock Feedback RevB.pdf"
//
//  Created by Hospitality on 2016-09-09.
//  Copyright © 2016 Assa Abloy Hospitality. All rights reserved.
//

#import "NSData+OpeningStatusPayload.h"

@implementation NSData (OpeningStatusPayload)

- (BOOL)containsData {
    return [self length]>0;
}

- (BOOL)didUnlock {

    if (![self containsData]) {
        return NO;
    }
    
    NSString *result = [self partialResultFrom:1 Length:1];
    NSScanner *myScanner = [NSScanner scannerWithString:result];
    unsigned int unlockedStatusValue;
    [myScanner scanHexInt:&unlockedStatusValue];
    if (unlockedStatusValue > 0) {
        return YES;
    } else {
        return NO;
    }
}

- (UnlockReason)unlockReason {
    NSString *result = [self partialResultFrom:2 Length:1];
    UnlockReason reason = UnlockReasonNotApplicable;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case UnlockReasonOpenedByGuestKey:
                case UnlockReasonOpenedBySpecialKey:
                case UnlockReasonOpenedByStaffKey:
                    reason = (UnlockReason)resultAsValue;
                    break;
                default:
                    reason = UnlockReasonNotApplicable;
                    break;
            }
        }
    }
    return reason;
}

- (DidNotUnlockReason)didNotUnlockReason {
    NSString *result = [self partialResultFrom:2 Length:1];
    DidNotUnlockReason reason = DidNotUnlockReasonNotApplicable;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case DidNotUnlockReasonKeyHasExpired:
                case DidNotUnlockReasonKeyIsCancelled:
                case DidNotUnlockReasonKeyIsOverridden:
                case DidNotUnlockReasonKeyIsNotValidYet:
                case DidNotUnlockReasonKeyGroupIsBlocked:
                case DidNotUnlockReasonKeyRefusedDueToPINCode:
                case DidNotUnlockReasonKeyBlockedByAccessRules:
                case DidNotUnlockReasonKeyHasNoAccessToThisRoom:
                case DidNotUnlockReasonKeyNotValidAtThisTimeOfDay:
                case DidNotUnlockReasonKeyBlockedBecauseOfDeadbolt:
                case DidNotUnlockReasonKeyHasNoAccessToThisFacility:
                case DidNotUnlockReasonKeyBlockedByAntiPassbackFunction:
                case DidNotUnlockReasonKeyRefusedBecauseDoorIsNotLocked:
                case DidNotUnlockReasonKeyBlockedBecauseOfDoorBatteryLevel:
                case DidNotUnlockReasonKeyBlockedBecauseOfRoomPrivacySetting:
                    reason = (DidNotUnlockReason)resultAsValue;
                    break;
                default:
                    reason = DidNotUnlockReasonNotApplicable;
                    break;
            }
        }
    }
    return reason;
}

- (DetailedUnlockReason)detailedUnlockReason {
    NSString *result = [self partialResultFrom:9 Length:2];
    DetailedUnlockReason reason = DetailedUnlockReasonNotApplicable;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if ([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case DetailedUnlockReasonOpeningWithGuestCard:
                case DetailedUnlockReasonOpeningWithGuestSuiteCard:
                case DetailedUnlockReasonOpeningByGuestInCommonRoom:
                case DetailedUnlockReasonOpeningWithFutureArrivalCard:
                case DetailedUnlockReasonOpeningWithOneTimeCard:
                case DetailedUnlockReasonOpeningByGuestInEntranceDoor:
                case DetailedUnlockReasonOpeningWithStaffCard:
                case DetailedUnlockReasonStandOpenSet:
                    reason = (DetailedUnlockReason)resultAsValue;
                    break;
                default:
                    reason = DetailedUnlockReasonNotApplicable;
                    break;
            }
        }
    }
    return reason;
}

- (DetailedDidNotUnlockReason)detailedDidNotUnlockReason {
    NSString *result = [self partialResultFrom:9 Length:2];
    DetailedDidNotUnlockReason reason = DetailedDidNotUnlockReasonNotApplicable;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if ([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case DetailedDidNotUnlockReasonGuestCardOverridden:
                case DetailedDidNotUnlockReasonGuestCardOverridden_v2:
                case DetailedDidNotUnlockReasonCardNotValidYet:
                case DetailedDidNotUnlockReasonCardHasExpired:
                case DetailedDidNotUnlockReasonCardCancelled:
                case DetailedDidNotUnlockReasonCardUsergroupBlocked:
                case DetailedDidNotUnlockReasonNoAccessToThisRoom:
                case DetailedDidNotUnlockReasonWrongSystemNumberOnCard:
                case DetailedDidNotUnlockReasonNotValidAtThisTime:
                case DetailedDidNotUnlockReasonCardOnlyValidDuringOpeningTime:
                case DetailedDidNotUnlockReasonDoorUnitDeadBolted:
                case DetailedDidNotUnlockReasonDoorUnitDeadBoltedGuest:
                case DetailedDidNotUnlockReasonDoorUnitDeadBoltedFamily:
                case DetailedDidNotUnlockReasonNotValidDueToPrivacyStatus:
                case DetailedDidNotUnlockReasonNotValidDueToPrivacyStatusSilent:
                case DetailedDidNotUnlockReasonNotValidDueToDoNotDisturbStatus:
                case DetailedDidNotUnlockReasonAccessDeniedDueToBatteryAlarm:
                case DetailedDidNotUnlockReasonNotValidDueToAntiPassback:
                case DetailedDidNotUnlockReasonNotValidDueToDoorNotClosed:
                case DetailedDidNotUnlockReasonNotValidDueToOpenStatus:
                case DetailedDidNotUnlockReasonWrongPIN:
                case DetailedDidNotUnlockReasonWrongPIN_v2:
                case DetailedDidNotUnlockReasonCommandNotValidForThisLock:
                case DetailedDidNotUnlockReasonCounterValueTooLow:
                case DetailedDidNotUnlockReasonNotValidDueToPassageRevoked:
                    reason = (DetailedDidNotUnlockReason)resultAsValue;
                    break;
                default:
                    reason = DetailedDidNotUnlockReasonNotApplicable;
                    break;
            }
        }
    }
    return reason;
}

- (nonnull NSString *)doorId {
    NSString *result = [self partialResultFrom:3 Length:4];
    NSString *doorIdResult = @"";
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if ([myScanner scanHexInt:&resultAsValue]) {
            doorIdResult = [NSString stringWithFormat:@"%ld", (long)resultAsValue];
        }
    }
    return doorIdResult;
}
- (ReaderBatteryStatus)readerBatteryStatus {
    NSString *result = [self partialResultFrom:7 Length:1];
    ReaderBatteryStatus status = ReaderBatteryStatusInvalid;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if ([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case ReaderBatteryStatusGood:
                case ReaderBatteryStatusWarning:
                case ReaderBatteryStatusCritical:
                    status = (ReaderBatteryStatus)resultAsValue;
                    break;
                default:
                    status = ReaderBatteryStatusInvalid;
                    break;
            }
        }
    }
    return status;
}
- (AccessControlSystem)accessControlSystem {
    NSString *result = [self partialResultFrom:8 Length:1];
    AccessControlSystem system = AccessControlSystemUknown;
    if (result) {
        NSScanner *myScanner = [NSScanner scannerWithString:result];
        unsigned int resultAsValue;
        if ([myScanner scanHexInt:&resultAsValue]) {
            switch (resultAsValue) {
                case AccessControlSystemVisionline:
                case AccessControlSystemVostio:
                    system = (AccessControlSystem)resultAsValue;
                    break;
                default:
                    system = AccessControlSystemUknown;
                    break;
            }
        }
    }
    return system;
}
- (nonnull NSString *)firmwareVersionLCU {
    NSString *result = [self partialResultFrom:11 Length:4];
    NSString *resMajor = [result substringWithRange:NSMakeRange(0, 1*2)];
    NSString *resMinor = [result substringWithRange:NSMakeRange(1*2, 1*2)];
    NSString *resRevision = [result substringWithRange:NSMakeRange(2*2, 1*2)];
    NSString *resBuild = [result substringWithRange:NSMakeRange(3*2, 1*2)];
    
    NSMutableString *stringResult = [NSMutableString string];

    [stringResult appendFormat:@"%@.%@.%@ (%@)", resMajor, resMinor, resRevision, resBuild];
    
    return [stringResult copy];
}
- (nonnull NSString *)firmwareVersionBLE {
    NSString *result = [self partialResultFrom:15 Length:2];
    NSString *resMajor = [result substringWithRange:NSMakeRange(0, 1*2)];
    NSString *resMinor = [result substringWithRange:NSMakeRange(1*2, 1*2)];
    
    NSMutableString *stringResult = [NSMutableString string];
    
    [stringResult appendFormat:@"%@.%@", resMajor, resMinor];
    
    return [stringResult copy];
}
- (nonnull NSString *)RFU {
    return @"";
}

- (nonnull NSString*)toStringHex {
    return [self openingStatusPayloadAsString:self];
}

+ (nullable NSData*) dataWithHexString:(nonnull NSString*)hexString
{
    
    NSData *data;
    if (hexString) {
        const char *inputBytes = [hexString cStringUsingEncoding:NSASCIIStringEncoding];
        if (inputBytes) {
            size_t bytesLength = sizeof(char) * (strlen(inputBytes) / 2);
            char *buf = malloc(bytesLength);    // buffer to place the output data
            
            for (int i = 0; i < bytesLength; i++, inputBytes+=2) {
                sscanf(inputBytes, "%2hhx", buf+i);
            }
            
            // We could use NSMutableData and -[appendBytes] for this method, but it
            // is a bit slower and not much less code.
            data = [NSData dataWithBytes:buf length:bytesLength];
            free(buf);
        } else {
            data = [NSData data];
        }
    }
    return data;
}

#pragma mark - private methods
// Fetch substring from result
- (NSString *)partialResultFrom:(NSInteger)location Length:(NSInteger)length {
    NSString *dataAsString = [self openingStatusPayloadAsString:self];
    NSRange aRange = NSMakeRange(location*2, length*2);
    
    NSRange formatRange = NSMakeRange(0, 1*2);
    
    NSString *aResult = @"";
    
    if (dataAsString.length>=aRange.location + aRange.length) {
        NSString *dataFormat = [dataAsString substringWithRange:formatRange];
        NSString *formatStandard = [NSString stringWithFormat:@"%02lx", (long)ReaderResultDataFormatStandard];
        if ([dataFormat isEqualToString:formatStandard]) {
            aResult = [dataAsString substringWithRange:aRange];
        }
    }
    return aResult;
}

// Convert NSData to NSString.
- (NSString *)openingStatusPayloadAsString:(NSData *)data {
    NSMutableString* resultAsHexBytes = [NSMutableString string];
    
    [data enumerateByteRangesUsingBlock:^(const void *bytes,
                                          NSRange byteRange,
                                          BOOL *stop) {
        
        //To print raw byte values as hex
        for (NSUInteger i = 0; i < byteRange.length; ++i) {
            [resultAsHexBytes appendFormat:@"%02x", ((uint8_t*)bytes)[i]];
        }
    }];
    
    return resultAsHexBytes;
}
@end
