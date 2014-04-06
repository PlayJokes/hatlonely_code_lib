// @file HLConfig.m
// @desc CodeViewer configure parser
// @auth hatlonely(hatlonely@foxmail.com)
// @date 2014-3-30

#import "HLConfig.h"

@implementation HLConfig

- (id) getLanguage {
    return language;
}

- (id) getStyle {
    return style;
}

- (id) initWithLanguage: (NSString *) languagePath style: (NSString *) stylePath {
    if (self = [super init]) {
        NSData *languageData = [[NSData alloc] initWithContentsOfFile: languagePath];
        NSData *styleData = [[NSData alloc] initWithContentsOfFile: stylePath];
        NSError *languageError;
        NSError *styleError;
        language = [NSJSONSerialization
                    JSONObjectWithData: languageData
                    options: NSJSONReadingMutableContainers
                    error: &languageError];
        style = [NSJSONSerialization
                 JSONObjectWithData: styleData
                 options: NSJSONReadingMutableContainers
                 error: &styleError];
        if (languageError) {
            NSLog(@"%@", [languageError localizedDescription]);
        }
        if (styleError) {
            NSLog(@"%@", [styleError localizedDescription]);
        }
    }
    return self;
}

- (NSString *) description {
    NSString *desc = [[NSString alloc] init];
    for (NSString *key in [language allKeys]) {
        desc = [desc stringByAppendingFormat: @"%@ => %@\n", key, [language objectForKey: key]];
    }
    for (NSString *key in [style allKeys]) {
        desc = [desc stringByAppendingFormat: @"%@ => %@\n", key, [style objectForKey: key]];
    }
    return desc;
}
@end  // HLConfig