//
//  MobileKeysEndpointUpdateSummary.h
//  SeosMobileKeysSDK
//
//  Created by David Ahlard on 2018-02-16.
//  Copyright © 2018 ASSA ABLOY Mobile Services. All rights reserved.
//
/**
 * This class represents a overview summary of the Seos Vault changes that were detected for an Update.
 */
@interface MobileKeysEndpointUpdateSummary : NSObject {
}

/**
 * NSDate representing when this TSM update started
 */
@property(nonatomic, strong) NSDate *updateDate;
/**
 * NSTimeInterval representing the internal time the TSM updat took
 */
@property(nonatomic) NSTimeInterval  updateDuration;

/**
 * Number of issued keys in the update
 */
@property(nonatomic) NSUInteger keyIssuedCount;
/**
 * Number of revoked keys in the update
 */
@property(nonatomic) NSUInteger keyRevokedCount;
/**
 * Number of updated keys in the update
 */
@property(nonatomic) NSUInteger keyUpdatedCount;

/**
 * Used internally by the SDK to count keys issued
 */
- (void)addKeyIssued;
/**
 * Used internally by the SDK to count keys revoked
 */
- (void)addKeyRevoked;
/**
 * Used internally by the SDK to count keys updated
 */
- (void)addKeyUpdated;
@end
