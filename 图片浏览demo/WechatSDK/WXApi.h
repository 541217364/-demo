#import <Foundation/Foundation.h>
#import "WXApiObject.h"
#pragma mark - WXApiDelegate
@protocol WXApiDelegate <NSObject>
@optional
-(void) onReq:(BaseReq*)req;
-(void) onResp:(BaseResp*)resp;
@end
#pragma mark - WXApiLogDelegate
@protocol WXApiLogDelegate <NSObject>
-(void) onLog:(NSString*)log logLevel:(WXLogLevel)level;
@end
#pragma mark - WXApi
@interface WXApi : NSObject
+(BOOL) registerApp:(NSString *)appid;
+(BOOL) registerApp:(NSString *)appid enableMTA:(BOOL)isEnableMTA;
+(void) registerAppSupportContentFlag:(UInt64)typeFlag;
+(BOOL) handleOpenURL:(NSURL *) url delegate:(id<WXApiDelegate>) delegate;
+(BOOL) isWXAppInstalled;
+(BOOL) isWXAppSupportApi;
+(NSString *) getWXAppInstallUrl;
+(NSString *) getApiVersion;
+(BOOL) openWXApp;
+(BOOL) sendReq:(BaseReq*)req;
+(BOOL) sendAuthReq:(SendAuthReq*)req viewController:(UIViewController*)viewController delegate:(id<WXApiDelegate>)delegate;
+(BOOL) sendResp:(BaseResp*)resp;
+(void) startLogByLevel:(WXLogLevel)level logBlock:(WXLogBolock)logBlock;
+ (void)startLogByLevel:(WXLogLevel)level logDelegate:(id<WXApiLogDelegate>)logDelegate;
+ (void)stopLog;
@end
