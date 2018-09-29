#import <Foundation/Foundation.h>
@interface NSData (ImageContentType)
+ (NSString *)sd_contentTypeForImageData:(NSData *)data;
@end
@interface NSData (ImageContentTypeDeprecated)
+ (NSString *)contentTypeForImageData:(NSData *)data __deprecated_msg("Use `sd_contentTypeForImageData:`");
@end
