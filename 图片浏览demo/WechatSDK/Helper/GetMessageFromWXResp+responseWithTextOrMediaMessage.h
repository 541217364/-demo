#import "WXApiObject.h"
@interface GetMessageFromWXResp (responseWithTextOrMediaMessage)
+ (GetMessageFromWXResp *)responseWithText:(NSString *)text
                            OrMediaMessage:(WXMediaMessage *)message
                                     bText:(BOOL)bText;
@end
