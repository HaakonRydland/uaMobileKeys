#import <Foundation/Foundation.h>
#import <SeosMobileKeysSDK/SeosMobileKeysSDK.h>
#import "KeyViewController.h"
#import "RegistrationViewController.h"

@class UIRefreshControl;
@class UITableView;

@interface UaMobileKeys : NSObject <MobileKeysManagerDelegate, KeyViewControllerDelegate, RegistrationViewControllerDelegate>

- (void)start;

@end