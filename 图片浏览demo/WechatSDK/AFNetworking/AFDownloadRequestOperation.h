#import "AFHTTPRequestOperation.h"
#define kAFNetworkingIncompleteDownloadFolderName @"Incomplete"
@interface AFDownloadRequestOperation : AFHTTPRequestOperation
@property (strong) NSString *targetPath;
@property (assign, readonly) BOOL shouldResume;
@property (assign, getter=isDeletingTempFileOnCancel) BOOL deleteTempFileOnCancel;
@property (assign, readonly) long long totalContentLength;
@property (assign, readonly) long long offsetContentLength;
- (id)initWithRequest:(NSURLRequest *)urlRequest targetPath:(NSString *)targetPath shouldResume:(BOOL)shouldResume;
- (BOOL)deleteTempFileWithError:(NSError **)error;
- (NSString *)tempPath;
- (void)setProgressiveDownloadProgressBlock:(void (^)(NSInteger bytesRead, long long totalBytesRead, long long totalBytesExpected, long long totalBytesReadForFile, long long totalBytesExpectedToReadForFile))block;
@end
