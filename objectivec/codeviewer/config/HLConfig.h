// @file HLConfig.h
// @desc CodeViewer configure parser
// @auth hatlonely(hatlonely@foxmail.com)
// @date 2014-3-30


#import <Foundation/Foundation.h>

@interface HLConfig: NSObject {
@private
    id language;
    id style;
}

- (id) initWithLanguage: (NSString *) languagePath style: (NSString *) stylePath;
- (id) getLanguage;
- (id) getStyle;
@end  // HLConfig