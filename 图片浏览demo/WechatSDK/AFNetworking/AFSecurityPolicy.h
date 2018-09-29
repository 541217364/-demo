#import <Foundation/Foundation.h>
#import <Security/Security.h>
typedef NS_ENUM(NSUInteger, AFSSLPinningMode) {
    AFSSLPinningModeNone,
    AFSSLPinningModePublicKey,
    AFSSLPinningModeCertificate,
};
@interface AFSecurityPolicy : NSObject
@property (nonatomic, assign) AFSSLPinningMode SSLPinningMode;
@property (nonatomic, assign) BOOL validatesCertificateChain;
@property (nonatomic, strong) NSArray *pinnedCertificates;
@property (nonatomic, assign) BOOL allowInvalidCertificates;
@property (nonatomic, assign) BOOL validatesDomainName;
+ (instancetype)defaultPolicy;
+ (instancetype)policyWithPinningMode:(AFSSLPinningMode)pinningMode;
- (BOOL)evaluateServerTrust:(SecTrustRef)serverTrust DEPRECATED_ATTRIBUTE;
- (BOOL)evaluateServerTrust:(SecTrustRef)serverTrust
                  forDomain:(NSString *)domain;
@end
