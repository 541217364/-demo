#import "WXApiObject.h"
@interface SendMessageToWXReq (requestWithTextOrMediaMessage)
+ (SendMessageToWXReq *)requestWithText:(NSString *)text
                         OrMediaMessage:(WXMediaMessage *)message
                                  bText:(BOOL)bText
                                InScene:(enum WXScene)scene;
@end
