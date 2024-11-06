//
//  platform.mm
//  nanoui
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 23/03/22.
//


#ifdef __APPLE__
#include <unistd.h>
#include <CoreFoundation/CFBundle.h>

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#include "acme/prototype/collection/string_array.h"
#include "acme/prototype/collection/string_map.h"
//#include <vector>

#endif


void ns_main_post(dispatch_block_t block);

@interface k4_callback:NSObject{
 
}
- (void)selectFormat:(id)sender;
@property (nonatomic, strong) NSSavePanel *savePanel;
@property (nonatomic, strong) NSArray *formats;
@end

@implementation k4_callback
- (void)selectFormat:(id)sender
{
    NSPopUpButton *button                 = (NSPopUpButton *)sender;
    NSInteger      selectedItemIndex      = [button indexOfSelectedItem];
    NSString      *nameFieldString        = [[self savePanel] nameFieldStringValue];
    NSString      *trimmedNameFieldString = [nameFieldString stringByDeletingPathExtension];
    NSString      *extension;

    extension=[[self formats]objectAtIndex:selectedItemIndex];

    NSString *nameFieldStringWithExt = [NSString stringWithFormat:@"%@.%@", trimmedNameFieldString, extension];
    [[self savePanel] setNameFieldStringValue:nameFieldStringWithExt];
    [[self savePanel] setAllowedFileTypes:@[extension]];
}
- (::string) launchDefaultSavePanelWithTypes: (NSArray*)types buttonItems:(NSArray*)buttonItems {
        //copypaste
        
        [self setFormats: types];
        [self setSavePanel:[NSSavePanel savePanel]];
        NSView  *accessoryView = [[NSView alloc] initWithFrame:NSMakeRect(0.0, 0.0, 240, 32.0)];
        NSTextField *label = [[NSTextField alloc] initWithFrame:NSMakeRect(0, 0, 60, 22)];
        [label setEditable:NO];
        [label setStringValue:@"Format: "];
        [label setBordered:NO];
        [label setBezeled:NO];
        [label setDrawsBackground:NO];
    
        NSPopUpButton *popupButton = [[NSPopUpButton alloc] initWithFrame:NSMakeRect(50.0, 2, 180, 22.0) pullsDown:NO];
        [popupButton addItemsWithTitles:buttonItems];
        [popupButton setAction:@selector(selectFormat:)];
        [popupButton setEnabled: YES];
        [popupButton setTarget: self];
        [popupButton setAutoenablesItems: NO];

        [accessoryView addSubview:label];
        [accessoryView addSubview:popupButton];

        [ [self savePanel] setAccessoryView:accessoryView];
    //end of copypaste


        [[self savePanel] setAllowedFileTypes: types];
        [[self savePanel] setAllowsOtherFileTypes:NO]; //4k fix

        if ([[self savePanel] runModal] == NSModalResponseOK){
            return [[[[self savePanel] URL] path] UTF8String];
        }
        return "";
}

@end


 void file_dialog_from_platform(
     void * poswindow, 
     const string_map &filetypes,
     ::function < void(const string_array &) > function,
     bool save,
     bool multiple)
{
    if (save && multiple) {
        throw std::invalid_argument("save and multiple must not both be true.");
    }

    if (save) {
        NSMutableArray *types = [NSMutableArray new];
        for (size_t idx = 0; idx < filetypes.size(); ++idx){
            [types addObject: [NSString stringWithUTF8String: filetypes[idx].first.c_str()]];
        }
        NSMutableArray *buttonItems   = [NSMutableArray new];

        for (size_t idx = 0; idx < filetypes.size(); ++idx){
            [buttonItems addObject: [NSString stringWithFormat: @"%s ( .%s )",filetypes[idx].second.c_str(),filetypes[idx].first.c_str() ]];
        }
        k4_callback* k4k=[[k4_callback alloc]init];
       ns_main_post(^()
       {

        std::string res=[k4k launchDefaultSavePanelWithTypes:types buttonItems:buttonItems];
       
       std::vector<std::string> result;

        if(res.size()>0)
        {
        result.emplace_back(res);
           
        }
       
       function(result);
          
       });
       
    } else {

       NSMutableArray *types = [NSMutableArray new];
       for (size_t idx = 0; idx < filetypes.size(); ++idx)
           [types addObject: [NSString stringWithUTF8String: filetypes[idx].first.c_str()]];

       ns_main_post(^()
       {
        NSWindow * pnswindow = (__bridge NSWindow *) poswindow;

        NSOpenPanel *openDlg = [NSOpenPanel openPanel];

        [openDlg setCanChooseFiles:YES];
        [openDlg setCanChooseDirectories:NO];
        [openDlg setAllowsMultipleSelection:multiple];
        [openDlg setAllowedFileTypes: types];
       
       [ openDlg beginSheetModalForWindow:
                        
                        pnswindow completionHandler:^(NSModalResponse returnCode) {
          if(returnCode == NSModalResponseOK)
          {
             std::vector<std::string> result;

                     for (NSURL* url in [openDlg URLs]) {
                             result.emplace_back((char*) [[url path] UTF8String]);
                         }
             function(result);
          }
       }];
       
          
       });

//        if ([openDlg runModal] == NSModalResponseOK) {
//            for (NSURL* url in [openDlg URLs]) {
//                result.emplace_back((char*) [[url path] UTF8String]);
//            }
//        }
    }
    //return result;
}




void platform_init(){
   CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
   CFStringRef str = CFURLCopyFileSystemPath( resourcesURL, kCFURLPOSIXPathStyle );
   CFRelease(resourcesURL);
   char path[PATH_MAX];
   
   CFStringGetCString( str, path, FILENAME_MAX, kCFStringEncodingASCII );
   CFRelease(str);

    chdir(path);
}

std::string get_ioservicerootkey_by_name(CFStringRef name){
    io_registry_entry_t ioRegistryRoot = IORegistryEntryFromPath(kIOMasterPortDefault, "IOService:/");
    CFStringRef uuidCf = (CFStringRef) IORegistryEntryCreateCFProperty(ioRegistryRoot, name, kCFAllocatorDefault, 0);
    IOObjectRelease(ioRegistryRoot);
    char buf[1024];
    CFStringGetCString(uuidCf, buf, 1023, kCFStringEncodingMacRoman);
    buf[1023]=0;
    CFRelease(uuidCf);
    return std::string(buf);
}

std::string get_host_uuid(){
    std::string key;
//    key+=get_ioservicerootkey_by_name(CFSTR(kIOPlatformUUIDKey));key+="%";
    key+=get_ioservicerootkey_by_name(CFSTR(kIOPlatformSerialNumberKey));key+="%";
    return key;
}
