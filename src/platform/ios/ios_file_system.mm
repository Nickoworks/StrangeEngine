#import <Foundation/Foundation.h>
#include "ios_file_system.h"

std::string getIOSFilePath(const std::string& filename){
    NSString *file = [NSString stringWithUTF8String:filename.c_str()];

    NSString *path = [[NSBundle mainBundle] pathForResource:[file stringByDeletingPathExtension] 
                                                     ofType:[file pathExtension]
                                              inDirectory:@"Resources"]; 
    
    if (path) {
        return std::string([path UTF8String]);
    }

    NSString *documentsPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) firstObject];
    NSString *fullPath = [documentsPath stringByAppendingPathComponent:file];
    
    if ([[NSFileManager defaultManager] fileExistsAtPath:fullPath]) {
        return std::string([fullPath UTF8String]);
    }

    return ""; 
}


