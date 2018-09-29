#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
enum  WXErrCode {
    WXSuccess           = 0,    
    WXErrCodeCommon     = -1,   
    WXErrCodeUserCancel = -2,   
    WXErrCodeSentFail   = -3,   
    WXErrCodeAuthDeny   = -4,   
    WXErrCodeUnsupport  = -5,   
};
enum WXScene {
    WXSceneSession  = 0,        
    WXSceneTimeline = 1,        
    WXSceneFavorite = 2,        
};
enum WXAPISupport {
    WXAPISupportSession = 0,
};
enum WXBizProfileType{
    WXBizProfileType_Normal = 0,    
    WXBizProfileType_Device = 1,    
};
typedef NS_ENUM(NSUInteger, WXMiniProgramType){
    WXMiniProgramTypeRelease = 0,       
    WXMiniProgramTypeTest = 1,        
    WXMiniProgramTypePreview = 2,         
};
enum WXMPWebviewType {
    WXMPWebviewType_Ad = 0,        
};
typedef NS_ENUM(UInt64, enAppSupportContentFlag)
{
    MMAPP_SUPPORT_NOCONTENT = 0x0,
    MMAPP_SUPPORT_TEXT      = 0x1,
    MMAPP_SUPPORT_PICTURE   = 0x2,
    MMAPP_SUPPORT_LOCATION  = 0x4,
    MMAPP_SUPPORT_VIDEO     = 0x8,
    MMAPP_SUPPORT_AUDIO     = 0x10,
    MMAPP_SUPPORT_WEBPAGE   = 0x20,
    MMAPP_SUPPORT_DOC  = 0x40,               
    MMAPP_SUPPORT_DOCX = 0x80,               
    MMAPP_SUPPORT_PPT  = 0x100,              
    MMAPP_SUPPORT_PPTX = 0x200,              
    MMAPP_SUPPORT_XLS  = 0x400,              
    MMAPP_SUPPORT_XLSX = 0x800,              
    MMAPP_SUPPORT_PDF  = 0x1000,             
};
typedef NS_ENUM(NSInteger,WXLogLevel){
    WXLogLevelNormal = 0,      
    WXLogLevelDetail = 1,      
};
typedef void(^WXLogBolock)(NSString * log);
#pragma mark - BaseReq
@interface BaseReq : NSObject
@property (nonatomic, assign) int type;
@property (nonatomic, retain) NSString* openID;
@end
#pragma mark - BaseResp
@interface BaseResp : NSObject
@property (nonatomic, assign) int errCode;
@property (nonatomic, retain) NSString *errStr;
@property (nonatomic, assign) int type;
@end
#pragma mark - WXMediaMessage
@class WXMediaMessage;
#ifndef BUILD_WITHOUT_PAY
@interface PayReq : BaseReq
@property (nonatomic, retain) NSString *partnerId;
@property (nonatomic, retain) NSString *prepayId;
@property (nonatomic, retain) NSString *nonceStr;
@property (nonatomic, assign) UInt32 timeStamp;
@property (nonatomic, retain) NSString *package;
@property (nonatomic, retain) NSString *sign;
@end
#endif
#ifndef BUILD_WITHOUT_PAY
#pragma mark - PayResp
@interface PayResp : BaseResp
@property (nonatomic, retain) NSString *returnKey;
@end
#endif
#pragma mark - SendAuthReq
@interface SendAuthReq : BaseReq
@property (nonatomic, retain) NSString* scope;
@property (nonatomic, retain) NSString* state;
@end
#pragma mark - SendAuthResp
@interface SendAuthResp : BaseResp
@property (nonatomic, retain) NSString* code;
@property (nonatomic, retain) NSString* state;
@property (nonatomic, retain) NSString* lang;
@property (nonatomic, retain) NSString* country;
@end
#pragma mark - SendMessageToWXReq
@interface SendMessageToWXReq : BaseReq
@property (nonatomic, retain) NSString* text;
@property (nonatomic, retain) WXMediaMessage* message;
@property (nonatomic, assign) BOOL bText;
@property (nonatomic, assign) int scene;
@end
#pragma mark - SendMessageToWXResp
@interface SendMessageToWXResp : BaseResp
@property(nonatomic, retain) NSString* lang;
@property(nonatomic, retain) NSString* country;
@end
#pragma mark - GetMessageFromWXReq
@interface GetMessageFromWXReq : BaseReq
@property (nonatomic, retain) NSString* lang;
@property (nonatomic, retain) NSString* country;
@end
#pragma mark - GetMessageFromWXResp
@interface GetMessageFromWXResp : BaseResp
@property (nonatomic, retain) NSString* text;
@property (nonatomic, retain) WXMediaMessage* message;
@property (nonatomic, assign) BOOL bText;
@end
#pragma mark - ShowMessageFromWXReq
@interface ShowMessageFromWXReq : BaseReq
@property (nonatomic, retain) WXMediaMessage* message;
@property (nonatomic, retain) NSString* lang;
@property (nonatomic, retain) NSString* country;
@end
#pragma mark - ShowMessageFromWXResp
@interface ShowMessageFromWXResp : BaseResp
@end
#pragma mark - LaunchFromWXReq
@interface LaunchFromWXReq : BaseReq
@property (nonatomic, retain) WXMediaMessage* message;
@property (nonatomic, retain) NSString* lang;
@property (nonatomic, retain) NSString* country;
@end
#pragma mark - OpenTempSessionReq
@interface OpenTempSessionReq : BaseReq
@property (nonatomic, retain) NSString* username;
@property (nonatomic, retain) NSString*  sessionFrom;
@end
#pragma mark - OpenTempSessionResp
@interface OpenTempSessionResp : BaseResp
@end
#pragma mark - OpenWebviewReq
@interface OpenWebviewReq : BaseReq
@property(nonatomic,retain)NSString* url;
@end
#pragma mark - OpenWebviewResp
@interface OpenWebviewResp : BaseResp
@end
#pragma mark - OpenRankListReq
@interface OpenRankListReq : BaseReq
@end
#pragma mark - OpenRanklistResp
@interface OpenRankListResp : BaseResp
@end
#pragma mark - JumpToBizProfileReq
@interface JumpToBizProfileReq : BaseReq
@property (nonatomic, retain) NSString* username;
@property (nonatomic, retain) NSString* extMsg;
@property (nonatomic, assign) int profileType;
@end
#pragma mark - JumpToBizWebviewReq
@interface JumpToBizWebviewReq : BaseReq
@property(nonatomic, assign) int webType;
@property(nonatomic, retain) NSString* tousrname;
@property(nonatomic, retain) NSString* extMsg;
@end
#pragma mark - WXCardItem
@interface WXCardItem : NSObject
@property (nonatomic,retain) NSString* cardId;
@property (nonatomic,retain) NSString* extMsg;
@property (nonatomic,assign) UInt32 cardState;
@property (nonatomic,retain) NSString* encryptCode;
@property (nonatomic,retain) NSString* appID;
@end;
#pragma mark - WXInvoiceItem
@interface WXInvoiceItem : NSObject
@property (nonatomic,retain) NSString* cardId;
@property (nonatomic,retain) NSString* extMsg;
@property (nonatomic,assign) UInt32 cardState;
@property (nonatomic,retain) NSString* encryptCode;
@property (nonatomic,retain) NSString* appID;
@end
#pragma mark - AddCardToWXCardPackageReq
@interface AddCardToWXCardPackageReq : BaseReq
@property (nonatomic,retain) NSArray* cardAry;
@end
#pragma mark - AddCardToWXCardPackageResp
@interface AddCardToWXCardPackageResp : BaseResp
@property (nonatomic,retain) NSArray* cardAry;
@end
#pragma mark - WXChooseCardReq
@interface WXChooseCardReq : BaseReq
@property(nonatomic, strong) NSString *appID;
@property(nonatomic, assign) UInt32 shopID;
@property(nonatomic, assign) UInt32 canMultiSelect;
@property(nonatomic, strong) NSString *cardType;
@property(nonatomic, strong) NSString *cardTpID;
@property(nonatomic, strong) NSString *signType;
@property(nonatomic, strong) NSString *cardSign;
@property(nonatomic, assign) UInt32 timeStamp;
@property(nonatomic, strong) NSString *nonceStr;
@end
#pragma mark - WXChooseCardResp
@interface WXChooseCardResp : BaseResp
@property (nonatomic,retain) NSArray* cardAry;
@end
#pragma mark - WXChooseInvoiceReq
@interface WXChooseInvoiceReq : BaseReq
@property (nonatomic, strong) NSString *appID;
@property (nonatomic, assign) UInt32 shopID;
@property (nonatomic, strong) NSString *signType;
@property (nonatomic, strong) NSString *cardSign;
@property (nonatomic, assign) UInt32 timeStamp;
@property (nonatomic, strong) NSString *nonceStr;
@end
#pragma mark - WXChooseInvoiceResp
@interface WXChooseInvoiceResp : BaseResp
@property (nonatomic, strong) NSArray* cardAry;
@end
#pragma mark - WXSubscriptionReq
@interface WXSubscribeMsgReq : BaseReq
@property (nonatomic, assign) UInt32 scene;
@property (nonatomic, strong) NSString * templateId;
@property (nonatomic, strong) NSString * reserved;
@end
#pragma mark - WXSubscriptionReq
@interface WXSubscribeMsgResp : BaseResp
@property (nonatomic, strong) NSString *templateId;
@property (nonatomic, assign) UInt32 scene;
@property (nonatomic, strong) NSString *action;
@property (nonatomic, strong) NSString * reserved;
@property (nonatomic, strong) NSString * openId;
@end
#pragma mark - WXinvoiceAuthInsertReq
@interface WXInvoiceAuthInsertReq : BaseReq
@property (nonatomic, strong) NSString *urlString;
@end
#pragma mark - WXinvoiceAuthInsertResp
@interface WXInvoiceAuthInsertResp : BaseResp
@property (nonatomic, strong) NSString * wxOrderId;
@end
#pragma mark - WXNontaxPayReq
@interface WXNontaxPayReq:BaseReq
@property (nonatomic, strong) NSString *urlString;
@end
#pragma mark - WXNontaxPayResp
@interface WXNontaxPayResp : BaseResp
@property (nonatomic, strong) NSString *wxOrderId;
@end
#pragma mark - WXPayInsuranceReq
@interface WXPayInsuranceReq : BaseReq
@property (nonatomic, strong) NSString *urlString;
@end
#pragma mark - WXPayInsuranceResp
@interface WXPayInsuranceResp : BaseResp
@property (nonatomic, strong) NSString *wxOrderId;
@end
#pragma mark - WXMediaMessage
#pragma mark - WXMediaMessage
@interface WXMediaMessage : NSObject
+(WXMediaMessage *) message;
@property (nonatomic, retain) NSString *title;
@property (nonatomic, retain) NSString *description;
@property (nonatomic, retain) NSData   *thumbData;
@property (nonatomic, retain) NSString *mediaTagName;
@property (nonatomic, retain) NSString *messageExt;
@property (nonatomic, retain) NSString *messageAction;
@property (nonatomic, retain) id        mediaObject;
- (void) setThumbImage:(UIImage *)image;
@end
#pragma mark - WXImageObject
@interface WXImageObject : NSObject
+(WXImageObject *) object;
@property (nonatomic, retain) NSData    *imageData;
@end
#pragma mark - WXMusicObject
@interface WXMusicObject : NSObject
+(WXMusicObject *) object;
@property (nonatomic, retain) NSString *musicUrl;
@property (nonatomic, retain) NSString *musicLowBandUrl;
@property (nonatomic, retain) NSString *musicDataUrl;
@property (nonatomic, retain) NSString *musicLowBandDataUrl;
@end
#pragma mark - WXVideoObject
@interface WXVideoObject : NSObject
+(WXVideoObject *) object;
@property (nonatomic, retain) NSString *videoUrl;
@property (nonatomic, retain) NSString *videoLowBandUrl;
@end
#pragma mark - WXWebpageObject
@interface WXWebpageObject : NSObject
+(WXWebpageObject *) object;
@property (nonatomic, retain) NSString *webpageUrl;
@end
#pragma mark - WXAppExtendObject
@interface WXAppExtendObject : NSObject
+(WXAppExtendObject *) object;
@property (nonatomic, retain) NSString *url;
@property (nonatomic, retain) NSString *extInfo;
@property (nonatomic, retain) NSData   *fileData;
@end
#pragma mark - WXEmoticonObject
@interface WXEmoticonObject : NSObject
+(WXEmoticonObject *) object;
@property (nonatomic, retain) NSData    *emoticonData;
@end
#pragma mark - WXFileObject
@interface WXFileObject : NSObject
+(WXFileObject *) object;
@property (nonatomic, retain) NSString  *fileExtension;
@property (nonatomic, retain) NSData    *fileData;
@end
#pragma mark - WXLocationObject
@interface WXLocationObject : NSObject
+(WXLocationObject *) object;
@property (nonatomic, assign) double lng; 
@property (nonatomic, assign) double lat; 
@end
@interface WXMiniProgramObject : NSObject
+(WXMiniProgramObject *) object;
@property (nonatomic, strong) NSString *webpageUrl; 
@property (nonatomic, strong) NSString *userName;   
@property (nonatomic, strong) NSString *path;       
@property (nonatomic, strong) NSData *hdImageData;   
@property (nonatomic, assign) BOOL withShareTicket;   
@property (nonatomic, assign) WXMiniProgramType miniProgramType;  
@end
#pragma mark - WXLaunchMiniProgramReq
@interface WXLaunchMiniProgramReq : BaseReq
+(WXLaunchMiniProgramReq *) object;
@property (nonatomic, strong) NSString *userName;   
@property (nonatomic, strong) NSString *path;       
@property (nonatomic, assign) WXMiniProgramType miniProgramType; 
@end
#pragma mark - WXLaunchMiniProgramResp
@interface WXLaunchMiniProgramResp : BaseResp
@property (nonatomic, retain) NSString *extMsg;
@end
#pragma mark - WXTextObject
@interface WXTextObject : NSObject
+(WXTextObject *) object;
@property (nonatomic, retain) NSString *contentText;
@end
