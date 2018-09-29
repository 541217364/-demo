#import <UIKit/UIKit.h>
#import "SDWebImageManager.h"
@interface UIView (WebCacheOperation)
- (void)sd_setImageLoadOperation:(id)operation forKey:(NSString *)key;
- (void)sd_cancelImageLoadOperationWithKey:(NSString *)key;
- (void)sd_removeImageLoadOperationWithKey:(NSString *)key;
@end
