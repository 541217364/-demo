#import "AFHTTPRequestOperation.h"
#import "LoginViewController.h"
#import "LogInAndLogOut.h"
#import "APService.h"
static dispatch_queue_t http_request_operation_processing_queue() {
    static dispatch_queue_t af_http_request_operation_processing_queue;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        af_http_request_operation_processing_queue = dispatch_queue_create("com.alamofire.networking.http-request.processing", DISPATCH_QUEUE_CONCURRENT);
    });
    return af_http_request_operation_processing_queue;
}
static dispatch_group_t http_request_operation_completion_group() {
    static dispatch_group_t af_http_request_operation_completion_group;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        af_http_request_operation_completion_group = dispatch_group_create();
    });
    return af_http_request_operation_completion_group;
}
#pragma mark -
@interface AFURLConnectionOperation ()
@property (readwrite, nonatomic, strong) NSURLRequest *request;
@property (readwrite, nonatomic, strong) NSURLResponse *response;
@end
@interface AFHTTPRequestOperation ()<UIAlertViewDelegate>
@property (readwrite, nonatomic, strong) NSHTTPURLResponse *response;
@property (readwrite, nonatomic, strong) id responseObject;
@property (readwrite, nonatomic, strong) NSError *responseSerializationError;
@property (readwrite, nonatomic, strong) NSRecursiveLock *lock;
@end
@implementation AFHTTPRequestOperation
@dynamic lock;
- (instancetype)initWithRequest:(NSURLRequest *)urlRequest {
    self = [super initWithRequest:urlRequest];
    if (!self) {
        return nil;
    }
    self.responseSerializer = [AFHTTPResponseSerializer serializer];
    return self;
}
- (void)setResponseSerializer:(AFHTTPResponseSerializer <AFURLResponseSerialization> *)responseSerializer {
    NSParameterAssert(responseSerializer);
    [self.lock lock];
    _responseSerializer = responseSerializer;
    self.responseObject = nil;
    self.responseSerializationError = nil;
    [self.lock unlock];
}
- (id)responseObject {
    [self.lock lock];
    if (!_responseObject && [self isFinished] && !self.error) {
        NSError *error = nil;
        self.responseObject = [self.responseSerializer responseObjectForResponse:self.response data:self.responseData error:&error];
        if (error) {
            self.responseSerializationError = error;
        }
    }
    [self.lock unlock];
    return _responseObject;
}
- (NSError *)error {
    if (_responseSerializationError) {
        return _responseSerializationError;
    } else {
        return [super error];
    }
}
#pragma mark - AFHTTPRequestOperation
- (void)is404 {
    NSUserDefaults *user1 =[NSUserDefaults standardUserDefaults];
    if (self.response.statusCode == 404 && ![user1 objectForKey:@"is404"]) {
        [user1 setObject:@"1" forKey:@"is404"];
        dispatch_async(dispatch_get_main_queue(), ^{
            RCLAlertView *rclAlerView = [[RCLAlertView alloc]initWithTitle:App_Alert_Notice_Title contentText:@"帐号已在另一设备登录，请重新登录" leftButtonTitle:@"" rightButtonTitle:@"确定"];
            rclAlerView.rightBlock = ^(){
                [LogInAndLogOut logOut:nil];
                [user1 removeObjectForKey:@"is404"];
            };
            [rclAlerView show1];
        });
        return;
    }else if (self.response.statusCode == 401 && ![user1 objectForKey:@"is404"]) {
        [user1 setObject:@"1" forKey:@"is404"];
        dispatch_async(dispatch_get_main_queue(), ^{
            RCLAlertView *rclAlerView = [[RCLAlertView alloc]initWithTitle:App_Alert_Notice_Title contentText:@"您的登陆已失效, 请重新登陆" leftButtonTitle:@"" rightButtonTitle:@"确定"];
            rclAlerView.rightBlock = ^(){
                [LogInAndLogOut logOut:nil];
                [user1 removeObjectForKey:@"is404"];
            };
            [rclAlerView show1];
        });
        return;
    }
}
- (void)setCompletionBlockWithSuccess:(void (^)(AFHTTPRequestOperation *operation, id responseObject))success
                              failure:(void (^)(AFHTTPRequestOperation *operation, NSError *error))failure {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-retain-cycles"
#pragma clang diagnostic ignored "-Wgnu"
    self.completionBlock = ^{
        if (self.completionGroup) {
            dispatch_group_enter(self.completionGroup);
        }
        dispatch_async(http_request_operation_processing_queue(), ^{
            if (self.error) {
                if (failure) {
                    dispatch_group_async(self.completionGroup ?: http_request_operation_completion_group(), self.completionQueue ?: dispatch_get_main_queue(), ^{
                        failure(self, self.error);
                    });
                }
            } else {
                id responseObject = self.responseObject;
                if (self.error) {
                    if (failure) {
                        dispatch_group_async(self.completionGroup ?: http_request_operation_completion_group(), self.completionQueue ?: dispatch_get_main_queue(), ^{
                            [self is404];
                            failure(self, self.error);
                        });
                    }
                } else {
                    if (success) {
                        if ([responseObject isKindOfClass:[NSDictionary class]]) {
                            NSString *status=[NSString stringWithFormat:@"%@",[responseObject valueForKey:@"status"]];
                            if ([status isEqualToString:@"103"]) {
                                dispatch_async(dispatch_get_main_queue(), ^{
                                    if ([SVProgressHUD isVisible]) {
                                        [SVProgressHUD dismiss];
                                    }
                                    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                                        AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
                                        CustomTabBarController *tab = delegate.tabBarController;
                                        [[tab.viewControllers objectAtIndex:tab.selectedIndex] popToRootViewControllerAnimated:NO];
                                        [tab setSelectedIndex:0];
                                    });
                                });
                            }else if([status isEqualToString:@"102"]){
                                dispatch_async(dispatch_get_main_queue(), ^{
                                    if ([SVProgressHUD isVisible]) {
                                        [SVProgressHUD dismiss];
                                    }
                                    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.5 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                                            AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
                                            CustomTabBarController *tab = delegate.tabBarController;
                                            [[tab.viewControllers objectAtIndex:tab.selectedIndex] popViewControllerAnimated:YES];
                                    });
                                });
                            }else if([status isEqualToString:@"-1"]){
                                [LogInAndLogOut logOut:@"登录失败，请重新登录"];
                                dispatch_group_async(self.completionGroup ?: http_request_operation_completion_group(), self.completionQueue ?: dispatch_get_main_queue(), ^{
                                    failure(self, self.error);
                                });
                            }
                            else{
                                dispatch_group_async(self.completionGroup ?: http_request_operation_completion_group(), self.completionQueue ?: dispatch_get_main_queue(), ^{
                                    success(self, responseObject);
                                });
                            }
                        }else{
                            dispatch_group_async(self.completionGroup ?: http_request_operation_completion_group(), self.completionQueue ?: dispatch_get_main_queue(), ^{
                                success(self, responseObject);
                            });
                        }
                    }
                }
            }
            if (self.completionGroup) {
                dispatch_group_leave(self.completionGroup);
            }
        });
    };
#pragma clang diagnostic pop
}
#pragma mark - AFURLRequestOperation
- (void)pause {
    [super pause];
    u_int64_t offset = 0;
    if ([self.outputStream propertyForKey:NSStreamFileCurrentOffsetKey]) {
        offset = [(NSNumber *)[self.outputStream propertyForKey:NSStreamFileCurrentOffsetKey] unsignedLongLongValue];
    } else {
        offset = [(NSData *)[self.outputStream propertyForKey:NSStreamDataWrittenToMemoryStreamKey] length];
    }
    NSMutableURLRequest *mutableURLRequest = [self.request mutableCopy];
    if ([self.response respondsToSelector:@selector(allHeaderFields)] && [[self.response allHeaderFields] valueForKey:@"ETag"]) {
        [mutableURLRequest setValue:[[self.response allHeaderFields] valueForKey:@"ETag"] forHTTPHeaderField:@"If-Range"];
    }
    [mutableURLRequest setValue:[NSString stringWithFormat:@"bytes=%llu-", offset] forHTTPHeaderField:@"Range"];
    self.request = mutableURLRequest;
}
#pragma mark - NSSecureCoding
+ (BOOL)supportsSecureCoding {
    return YES;
}
- (id)initWithCoder:(NSCoder *)decoder {
    self = [super initWithCoder:decoder];
    if (!self) {
        return nil;
    }
    self.responseSerializer = [decoder decodeObjectOfClass:[AFHTTPResponseSerializer class] forKey:NSStringFromSelector(@selector(responseSerializer))];
    return self;
}
- (void)encodeWithCoder:(NSCoder *)coder {
    [super encodeWithCoder:coder];
    [coder encodeObject:self.responseSerializer forKey:NSStringFromSelector(@selector(responseSerializer))];
}
#pragma mark - NSCopying
- (id)copyWithZone:(NSZone *)zone {
    AFHTTPRequestOperation *operation = [super copyWithZone:zone];
    operation.responseSerializer = [self.responseSerializer copyWithZone:zone];
    operation.completionQueue = self.completionQueue;
    operation.completionGroup = self.completionGroup;
    return operation;
}
@end
