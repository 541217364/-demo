#import <Foundation/Foundation.h>
#import "SDWebImageCompat.h"
typedef NS_ENUM(NSInteger, SDImageCacheType) {
    SDImageCacheTypeNone,
    SDImageCacheTypeDisk,
    SDImageCacheTypeMemory
};
typedef void(^SDWebImageQueryCompletedBlock)(UIImage *image, SDImageCacheType cacheType);
typedef void(^SDWebImageCheckCacheCompletionBlock)(BOOL isInCache);
typedef void(^SDWebImageCalculateSizeBlock)(NSUInteger fileCount, NSUInteger totalSize);
@interface SDImageCache : NSObject
@property (assign, nonatomic) BOOL shouldDecompressImages;
@property (assign, nonatomic) BOOL shouldDisableiCloud;
@property (assign, nonatomic) BOOL shouldCacheImagesInMemory;
@property (assign, nonatomic) NSUInteger maxMemoryCost;
@property (assign, nonatomic) NSUInteger maxMemoryCountLimit;
@property (assign, nonatomic) NSInteger maxCacheAge;
@property (assign, nonatomic) NSUInteger maxCacheSize;
+ (SDImageCache *)sharedImageCache;
- (id)initWithNamespace:(NSString *)ns;
- (id)initWithNamespace:(NSString *)ns diskCacheDirectory:(NSString *)directory;
-(NSString *)makeDiskCachePath:(NSString*)fullNamespace;
- (void)addReadOnlyCachePath:(NSString *)path;
- (void)storeImage:(UIImage *)image forKey:(NSString *)key;
- (void)storeImage:(UIImage *)image forKey:(NSString *)key toDisk:(BOOL)toDisk;
- (void)storeImage:(UIImage *)image recalculateFromImage:(BOOL)recalculate imageData:(NSData *)imageData forKey:(NSString *)key toDisk:(BOOL)toDisk;
- (NSOperation *)queryDiskCacheForKey:(NSString *)key done:(SDWebImageQueryCompletedBlock)doneBlock;
- (UIImage *)imageFromMemoryCacheForKey:(NSString *)key;
- (UIImage *)imageFromDiskCacheForKey:(NSString *)key;
- (void)removeImageForKey:(NSString *)key;
- (void)removeImageForKey:(NSString *)key withCompletion:(SDWebImageNoParamsBlock)completion;
- (void)removeImageForKey:(NSString *)key fromDisk:(BOOL)fromDisk;
- (void)removeImageForKey:(NSString *)key fromDisk:(BOOL)fromDisk withCompletion:(SDWebImageNoParamsBlock)completion;
- (void)clearMemory;
- (void)clearDiskOnCompletion:(SDWebImageNoParamsBlock)completion;
- (void)clearDisk;
- (void)cleanDiskWithCompletionBlock:(SDWebImageNoParamsBlock)completionBlock;
- (void)cleanDisk;
- (NSUInteger)getSize;
- (NSUInteger)getDiskCount;
- (void)calculateSizeWithCompletionBlock:(SDWebImageCalculateSizeBlock)completionBlock;
- (void)diskImageExistsWithKey:(NSString *)key completion:(SDWebImageCheckCacheCompletionBlock)completionBlock;
- (BOOL)diskImageExistsWithKey:(NSString *)key;
- (NSString *)cachePathForKey:(NSString *)key inPath:(NSString *)path;
- (NSString *)defaultCachePathForKey:(NSString *)key;
@end
