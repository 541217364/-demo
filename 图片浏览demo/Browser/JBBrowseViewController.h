#import <UIKit/UIKit.h>
#import "BrowserDefine.h"
@interface JBBrowseViewController : UIViewController
+ (instancetype)showInController:(UIViewController*)controller imageDataSource:(NSArray*)imageUrls index:(NSInteger)index;
- (void)customPageView:(UIView*)pageView scrollPageCompletion:(scrollBlock)completion;
@property (nonatomic, strong)UIImage * placeholderImage;
- (void)showAnimationWithType:(BrowseShowType)type;
@end
