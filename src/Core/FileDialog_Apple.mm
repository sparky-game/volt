#if defined(__APPLE__) && defined(__MACH__)

#include <Cocoa/Cocoa.h>
#include "FileDialog.hh"

namespace volt::core {
  std::string FileDialog::Open(std::vector<std::string> &filter) {
    @autoreleasepool {
      NSOpenPanel *panel = [NSOpenPanel openPanel];
      panel.canChooseFiles = YES;
      panel.canChooseDirectories = NO;
      panel.allowsMultipleSelection = NO;
      if (not filter.empty()) {
        NSMutableArray *file_types = [NSMutableArray array];
        for (const auto &i : filter) {
          [file_types addObject:[NSString stringWithUTF8String:filter.c_str()]];
        }
        panel.allowedFileTypes = file_types;
      }
      if ([panel runModal] == NSModalResponseOK) {
        NSURL *file_url = [[panel URLs] objectAtIndex:0];
        return [[file_url path] UTF8String];
      }
    }
    return {};
  }

  std::string FileDialog::Save(std::vector<std::string> &filter) {
    @autoreleasepool {
      NSSavePanel *panel = [NSSavePanel savePanel];
      panel.canCreateDirectories = YES;
      if (not filter.empty()) {
        NSMutableArray *file_types = [NSMutableArray array];
        for (const auto &i : filter) {
          [file_types addObject:[NSString stringWithUTF8String:filter.c_str()]];
        }
        panel.allowedFileTypes = file_types;
      }
      if ([panel runModal] == NSModalResponseOK) {
        NSURL *file_url = [panel URL];
        return [[file_url path] UTF8String];
      }
    }
    return {};
  }
}

#endif  // defined(__APPLE__) && defined(__MACH__)
