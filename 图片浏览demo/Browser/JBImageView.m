#import "JBImageView.h"
#import "UIImageView+WebCache.h"
#define Screen_Width  [UIScreen mainScreen].bounds.size.width
#define Screen_Height [UIScreen mainScreen].bounds.size.height
@interface JBImageView()<UIScrollViewDelegate>
@property (nonatomic, strong)UIImageView * imageView;
@property (nonatomic, strong)UIScrollView * contentView;
@end
@implementation JBImageView
- (void)dealloc
{
}
- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        self.contentView = [[UIScrollView alloc]initWithFrame:self.bounds];
        _contentView.showsVerticalScrollIndicator = NO;
        _contentView.showsHorizontalScrollIndicator = NO;
        _contentView.maximumZoomScale = 3;
        _contentView.minimumZoomScale = 1;
        _contentView.pagingEnabled = YES;
        _contentView.delegate = self;
        [_contentView setZoomScale:1];
        [self addSubview:self.contentView];
        self.imageView = [[UIImageView alloc]initWithFrame:self.bounds];
        self.imageView.contentMode = UIViewContentModeScaleAspectFit;
        self.imageView.userInteractionEnabled = YES;
        [self.contentView addSubview:self.imageView];
        UITapGestureRecognizer * tap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(handleSingleTap:)];
        tap.numberOfTapsRequired = 1;
        tap.numberOfTouchesRequired =1;
        [self addGestureRecognizer:tap];
        UITapGestureRecognizer * doubleTap = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(handleDoubleTap:)];
        doubleTap.numberOfTapsRequired = 2;
        [self.imageView addGestureRecognizer:doubleTap];
        UITapGestureRecognizer * doubleFinger = [[UITapGestureRecognizer alloc]initWithTarget:self action:@selector(handleTwoFingerTap:)];
        doubleFinger.numberOfTouchesRequired = 2;
        [self.imageView addGestureRecognizer:doubleFinger];
        [tap requireGestureRecognizerToFail:doubleTap];
    }
    return self;
}
- (void)handleSingleTap:(UITapGestureRecognizer*)single
{
    if (single.numberOfTapsRequired==1)
    {
        if (self.delegate&&[self.delegate respondsToSelector:@selector(tapHiddenView)])
        {
            [self.delegate tapHiddenView];
        }
    }
}
- (void)handleDoubleTap:(UITapGestureRecognizer*)doubleTap
{
    if (doubleTap.numberOfTapsRequired==2)
    {
        if (_contentView.zoomScale==1)
        {
            float newScale = [_contentView zoomScale]*2;
            CGRect zoomRect = [self zoomRectForScale:newScale withCenter:[doubleTap locationInView:doubleTap.view]];
            [_contentView zoomToRect:zoomRect animated:YES];
        }
        else
        {
            float newScale = [_contentView zoomScale]/2;
            CGRect zoomRect = [self zoomRectForScale:newScale withCenter:[doubleTap locationInView:doubleTap.view]];
            [_contentView zoomToRect:zoomRect animated:YES];
        }
    }
}
- (void)handleTwoFingerTap:(UITapGestureRecognizer*)gesture
{
    float newScale = [_contentView zoomScale]/2;
    CGRect zoomRect = [self zoomRectForScale:newScale withCenter:[gesture locationInView:gesture.view]];
    [_contentView zoomToRect:zoomRect animated:YES];
}
- (void)setImageUrl:(NSString *)url placeHolderImage:(UIImage *)placeHolder
{
    if ([url hasPrefix:@"http:"]||[url hasPrefix:@"https:"])
    {
        __weak typeof(self) weakSelf = self;
        [self.imageView sd_setImageWithURL:[NSURL URLWithString:url] placeholderImage:placeHolder  completed:^(UIImage * _Nullable image, NSError * _Nullable error, SDImageCacheType cacheType, NSURL * _Nullable imageURL)
         {
             UIImage * newImage = [weakSelf scaleSizeForImage:image];
             [weakSelf updateIGVFrameForImage:newImage];
         }];
    }
    else
    {
        UIImage * image = [UIImage imageNamed:url];
        UIImage * newImage = [self scaleSizeForImage:image];
        [self updateIGVFrameForImage:newImage];
        self.imageView.image = newImage;
    }
}
- (UIImage*)scaleSizeForImage:(UIImage*)sourceImage
{
    CGFloat scale = 1;
    if (Screen_Height>Screen_Width)
    {
        scale = Screen_Width/sourceImage.size.width;
    }
    else
    {
        scale = Screen_Height/sourceImage.size.height;
    }
    CGFloat imageWidth = sourceImage.size.width * scale;
    CGFloat imageHeight = sourceImage.size.height * scale;
    CGSize size = CGSizeMake(imageWidth, imageHeight);
    UIImage * newImage = nil;
    if (CGSizeEqualToSize(sourceImage.size, size)==NO)
    {
        UIGraphicsBeginImageContext(size);
        CGRect thumbnailRect = CGRectZero;
        thumbnailRect.size.width = imageWidth;
        thumbnailRect.size.height = imageHeight;
        [sourceImage drawInRect:thumbnailRect];
        newImage = UIGraphicsGetImageFromCurrentImageContext();
        UIGraphicsEndImageContext();
    }
    return newImage;
}
- (void)updateIGVFrameForImage:(UIImage*)image
{
    CGRect imageViewRect = self.imageView.frame;
    imageViewRect.size = image.size;
    imageViewRect.origin.y = (self.frame.size.height-image.size.height)*0.5;
    self.imageView.frame = imageViewRect;
}
- (UIView*)viewForZoomingInScrollView:(UIScrollView *)scrollView
{
    return self.imageView;
}
- (void)scrollViewDidEndZooming:(UIScrollView *)scrollView withView:(UIView *)view atScale:(CGFloat)scale
{
    [scrollView setZoomScale:scale+0.01f animated:NO];
    [scrollView setZoomScale:scale animated:NO];
}
- (void)scrollViewDidZoom:(UIScrollView *)scrollView
{
    CGFloat offsetX = (_contentView.bounds.size.width>_contentView.contentSize.width)?(_contentView.bounds.size.width-_contentView.contentSize.width)*0.5:0;
    CGFloat offsetY = (_contentView.bounds.size.height>_contentView.contentSize.height)?(_contentView.bounds.size.height-_contentView.contentSize.height)*0.5:0;
    self.imageView.center = CGPointMake(_contentView.contentSize.width*0.5+offsetX, _contentView.contentSize.height*0.5+offsetY);
}
- (CGRect)zoomRectForScale:(CGFloat)scale withCenter:(CGPoint)center
{
    CGRect zoomRect;
    zoomRect.size.height = _contentView.frame.size.height/scale;
    zoomRect.size.width = _contentView.frame.size.width/scale;
    zoomRect.origin.x = center.x - zoomRect.size.width/2;
    zoomRect.origin.y = center.y - zoomRect.size.height/2;
    return zoomRect;
}
@end
