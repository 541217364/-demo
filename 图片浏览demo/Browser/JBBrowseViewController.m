#import "JBBrowseViewController.h"
#import "JBScrollContentView.h"
@interface JBBrowseViewController ()<UIScrollViewDelegate,CAAnimationDelegate>
@property (nonatomic, weak)UIViewController * currentVC;
@property (nonatomic, weak)NSArray * imageUrls;
@property (nonatomic, strong)JBScrollContentView * scrollView;
@property (nonatomic, assign)BrowseShowType showType;
@property (nonatomic, assign)NSInteger defaultIndex;
@property (nonatomic, copy)scrollBlock handleBlock;
@property (nonatomic, weak)UIView * pageView;
@end
@implementation JBBrowseViewController
- (JBScrollContentView*)scrollView
{
    if (!_scrollView)
    {
        _scrollView = [[JBScrollContentView alloc]initWithFrame:CGRectMake(0, 0,JBScreen_Width, JBScreen_Height)];
        _scrollView.backgroundColor = [UIColor orangeColor];
    }
    return _scrollView;
}
- (void)viewDidLoad {
    [super viewDidLoad];
    self.view.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:self.scrollView];
}
- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES];
}
- (void)hiddenCurrentVC
{
    if (self.currentVC)
    {
        UINavigationController * nav = self.currentVC.navigationController;
        switch (self.showType) {
            case BrowsePushType:
            {
                if (nav)
                { 
                    [self.navigationController popViewControllerAnimated:YES];
                }
                else
                {
                    [self transitionWithDisappearType:BrowsePushType];
                }
            }
                break;
            case BrowseModalType:
            {
                [nav dismissViewControllerAnimated:YES completion:nil];
            }
                break;
            case BrowseZoomType:
                [self zoomDisappearAnimation];
                break;
            case BrowseNoneType:
                [self.view removeFromSuperview];
                [self removeFromParentViewController];
                break;
            default:
                break;
        }
    }
    else
    {
        [self transitionWithDisappearType:self.showType];
    }
}
- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
}
+ (instancetype)showInController:(UIViewController*)controller imageDataSource:(NSArray*)imageUrls index:(NSInteger)index
{
    JBBrowseViewController * browseVC = [[JBBrowseViewController alloc]init];
    browseVC.currentVC = controller;
    browseVC.imageUrls = imageUrls;
    browseVC.defaultIndex = index;
    return browseVC;
}
- (void)customPageView:(UIView*)pageView scrollPageCompletion:(scrollBlock)completion
{
    if (pageView)
    {
        self.pageView = pageView;
        [self.scrollView addSubview:pageView];
    }
    self.handleBlock = completion;
}
- (void)showAnimationWithType:(BrowseShowType)type;
{
    self.showType = type;
    if (self.currentVC)
    {
        UINavigationController * nav = self.currentVC.navigationController;
        switch (type) {
            case BrowsePushType:
            {
                if (nav)
                {
                    [nav pushViewController:self animated:YES];
                }
                else
                {
                    [WINDOW addSubview:self.view];
                    [WINDOW.rootViewController addChildViewController:self];
                    [self transitionWithShowType:BrowsePushType];
                }
            }
                break;
            case BrowseModalType:
            {
                [nav presentViewController:self animated:YES completion:nil];
            }
                break;
            case BrowseZoomType:
                [WINDOW addSubview:self.view];
                [self.currentVC addChildViewController:self];
                [self zoomAnimation];
                break;
            case BrowseNoneType:
                [WINDOW addSubview:self.view];
                [self.currentVC addChildViewController:self];
                break;
            default:
                break;
        }
    }
    else
    {
        [WINDOW addSubview:self.view];
        [WINDOW.rootViewController addChildViewController:self];
        [self transitionWithShowType:type];
    }
    __weak typeof(self) weakSelf = self;
    [self.scrollView loadImageUrls:self.imageUrls defaultIndex:self.defaultIndex currentSelectIndex:^(int index) {
        if (weakSelf.handleBlock)
        {
            weakSelf.handleBlock(weakSelf.imageUrls.count, index, weakSelf.pageView);
        }
    }];
    [self.scrollView tapViewBlock:^{
        [weakSelf hiddenCurrentVC];
    }];
}
- (void)zoomAnimation
{
    CAKeyframeAnimation * keyFrame = [CAKeyframeAnimation animationWithKeyPath:@"transform.scale"];
    keyFrame.values = @[@(0.1),@(0.3),@(0.5),@(0.7),@(0.9),@(1)];
    keyFrame.removedOnCompletion = YES;
    keyFrame.duration = AnimationDuration;
    [self.scrollView.layer addAnimation:keyFrame forKey:nil];
}
- (void)zoomDisappearAnimation
{
    CAKeyframeAnimation * keyFrame = [CAKeyframeAnimation animationWithKeyPath:@"transform.scale"];
    keyFrame.values = @[@(0.9),@(0.7),@(0.5),@(0.3),@(0.1),@(0)];
    keyFrame.removedOnCompletion = YES;
    keyFrame.delegate = self;
    keyFrame.duration = AnimationDuration;
    [self.scrollView.layer addAnimation:keyFrame forKey:nil];
}
- (void)transitionWithShowType:(BrowseShowType)type
{
    if (type==BrowsePushType||type==BrowseModalType)
    {
        CATransition * tran = [CATransition animation];
        tran.duration = AnimationDuration;
        tran.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
        tran.type = kCATransitionPush;
        if (type==BrowsePushType)
        {
            tran.subtype = kCATransitionFromRight;
        }
        else
        {
            tran.subtype = kCATransitionFromTop;
        }
        [self.scrollView.layer addAnimation:tran forKey:nil];
    }
    else if (type==BrowseZoomType)
    {
        [self zoomAnimation];
    }
    else
    {
    }
}
- (void)transitionWithDisappearType:(BrowseShowType)type
{
    if (type==BrowsePushType||type==BrowseModalType)
    {
        [UIView animateWithDuration:AnimationDuration animations:^{
            CGRect scrollRect = self.scrollView.frame;
            if (type==BrowsePushType)
            {
               scrollRect.origin.x = CGRectGetWidth(self.scrollView.frame);
            }
            else
            {
               scrollRect.origin.y = CGRectGetHeight(self.scrollView.frame);
            }
            self.scrollView.frame = scrollRect;
        } completion:^(BOOL finished) {
            [self.scrollView removeFromSuperview];
            [self.view removeFromSuperview];
            [self removeFromParentViewController];
        }];
    }
    else if(type==BrowseZoomType)
    {
        [self zoomDisappearAnimation];
    }
    else
    {
        [self.scrollView removeFromSuperview];
        [self.view removeFromSuperview];
        [self removeFromParentViewController];
    }
}
- (void)animationDidStop:(CAAnimation *)anim finished:(BOOL)flag
{
    if (flag)
    {
        self.scrollView.hidden = YES;
        [self.scrollView removeFromSuperview];
        [self.view removeFromSuperview];
        [self removeFromParentViewController];
    }
}
#pragma mark setter方法
- (void)setPlaceholderImage:(UIImage *)placeholderImage
{
    _placeholderImage = placeholderImage;
    self.scrollView.placeholderImage = placeholderImage;
}
@end
