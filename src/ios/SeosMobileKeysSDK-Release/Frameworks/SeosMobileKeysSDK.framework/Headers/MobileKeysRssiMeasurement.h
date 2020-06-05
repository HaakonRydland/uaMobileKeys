//
//  MobileKeysRssiMeasurement.h
//  SeosMobileKeys
//
//  Created by David Ahlard on 2014-09-30.
//  Copyright (c) 2014 AssaAbloy. All rights reserved.
//

@class AMSClock;

/*
* Represents One RSSI Value Sample
*/
@interface MobileKeysRssiMeasurement : NSObject

@property(nonatomic, assign, readonly) NSInteger rssiValue;

@property(nonatomic, assign, readonly) NSTimeInterval measuredAtIntervalSince1970;

/**
* Will construct a new measurement, setting the measuredAtIntervalSince1970 to current time
*/
+ (MobileKeysRssiMeasurement *)fromRssiValue:(NSInteger)rssiValue withClock:(AMSClock*)clock;

@end
