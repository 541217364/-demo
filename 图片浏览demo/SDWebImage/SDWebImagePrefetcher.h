#import <Foundation/Foundation.h>
#import "SDWebImageManager.h"
@class SDWebImagePrefetcher;
@protocol SDWebImagePrefetcherDelegate <NSObject>
@optional
- (void)imagePrefetcher:(SDWebImagePrefetcher *)imagePrefetcher didPrefetchURL:(NSURL *)imageURL finishedCount:(NSUInteger)finishedCount totalCount:(NSUInteger)totalCount;
- (void)imagePrefetcher:(SDWebImagePrefetcher *)imagePrefetcher didFinishWithTotalCount:(NSUInteger)totalCount skippedCount:(NSUInteger)skippedCount;
@end
typedef void(^SDWebImagePrefetcherProgressBlock)(NSUInteger noOfFinishedUrls, NSUInteger noOfTotalUrls);
typedef void(^SDWebImagePrefetcherCompletionBlock)(NSUInteger noOfFinishedUrls, NSUInteger noOfSkippedUrls);
@interface SDWebImagePrefetcher : NSObject
@property (strong, nonatomic, readonly) SDWebImageManager *manager;
@property (nonatomic, assign) NSUInteger maxConcurrentDownloads;
@property (nonatomic, assign) SDWebImageOptions options;
@property (nonatomic, assign) dispatch_queue_t prefetcherQueue;
@property (weak, nonatomic) id <SDWebImagePrefetcherDelegate> delegate;
+ (SDWebImagePrefetcher *)sharedImagePrefetcher;
- (id)initWithImageManager:(SDWebImageManager *)manager;
- (void)prefetchURLs:(NSArray *)urls;
- (void)prefetchURLs:(NSArray *)urls progress:(SDWebImagePrefetcherProgressBlock)progressBlock completed:(SDWebImagePrefetcherCompletionBlock)completionBlock;
- (void)cancelPrefetching;
@end
