#import <UIKit/UIKit.h>
@protocol PhotoDelegate <NSObject>
- (void)tapHiddenView;
@end
@interface JBImageView : UIView
- (void)setImageUrl:(NSString*)url placeHolderImage:(UIImage*)placeHolder;
@property (nonatomic, assign)id<PhotoDelegate> delegate;
@end
