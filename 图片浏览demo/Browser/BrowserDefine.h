#ifndef BrowserDefine_h
#define BrowserDefine_h
#define WINDOW [UIApplication sharedApplication].delegate.window
#define JBScreen_Width  [UIScreen mainScreen].bounds.size.width
#define JBScreen_Height [UIScreen mainScreen].bounds.size.height
#define AnimationDuration 0.75
typedef NS_ENUM(NSInteger,BrowseShowType)
{
    BrowseNoneType = 0,
    BrowsePushType,
    BrowseModalType,
    BrowseZoomType
};
typedef void(^scrollBlock)(NSInteger totalPage,NSInteger currentPage,UIView*pageView);
#endif 
