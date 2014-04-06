// @file HLConfig_test.m
// @desc CodeViewer configure parser
// @auth hatlonely(hatlonely@foxmail.com)
// @date 2014-3-30

#import <Foundation/Foundation.h>

#import "HLConfig.h"

int main(int argc, const char *argv[]) {
    NSLog (@"hello, objective-c!");
    
    HLConfig *config;
    config = [[HLConfig alloc]
              initWithLanguage: @"/Users/hatlonely/Hatlonely/git_workspace/hatlonely_code_lib/objectivec/codeviewer/config/conf/cpp.language"
              style: @"/Users/hatlonely/Hatlonely/git_workspace/hatlonely_code_lib/objectivec/codeviewer/config/conf/base.style"];
    [config getStyle];
    [config description];
    //[config release];
    NSLog(@"%@", [config description]);

    return 0;
}