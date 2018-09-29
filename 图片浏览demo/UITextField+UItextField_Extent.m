#import "UITextField+UItextField_Extent.h"
@implementation UITextField (UItextField_Extent)
-(void)initWithHideBar{
        [self createNavigationView];
}
- (void)createNavigationView
{
    UIButton *btnT=[[UIButton alloc] initWithFrame:CGRectMake(0, 0, [UIScreen mainScreen].bounds.size.width, 33)];
    btnT.backgroundColor=[UIColor grayColor];
    [btnT setTitle:@"轻触此处可隐藏键盘" forState:UIControlStateNormal];
    btnT.titleLabel.font=[UIFont systemFontOfSize:14];
    [btnT setTitleColor:[UIColor darkGrayColor] forState:UIControlStateNormal];
    [btnT addTarget:self action:@selector(missKeyBoard) forControlEvents:UIControlEventTouchUpInside];
    self.inputAccessoryView = btnT;
}
-(void)missKeyBoard{
    [self endEditing:YES];
    NSLog(@"11111111");
}
@end
