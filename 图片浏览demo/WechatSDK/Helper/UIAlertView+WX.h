#import <UIKit/UIKit.h>
typedef void(^WXAlertSureBlock)(UIAlertView *alertView,NSString *text);
@interface UIAlertView (WX)<UIAlertViewDelegate>
+ (void)requestWithTitle:(NSString *)title
                 message:(NSString *)message
             defaultText:(NSString *)defaultText
                    sure:(WXAlertSureBlock)sure;
+ (void)showWithTitle:(NSString *)title
              message:(NSString *)message
                 sure:(WXAlertSureBlock)sure;
@end
