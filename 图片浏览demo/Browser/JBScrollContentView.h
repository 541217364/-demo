typedef void(^selectBlock)(int index);
typedef void(^tapBlock)(void);
#import <UIKit/UIKit.h>
#import "BrowserDefine.h"
@interface JBScrollContentView : UIView
- (void)loadImageUrls:(NSArray*)images defaultIndex:(NSInteger)index currentSelectIndex:(selectBlock)indexBlock;
- (void)tapViewBlock:(tapBlock)handleBlock;
@property (nonatomic,strong)UIImage * placeholderImage;
@end
