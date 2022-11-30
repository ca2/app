//
//  mm.mm
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 18/08/21.
//  Copyright © 2021 Camilo Sasuke Tsumanuma. All rights reserved.
//

#import <Foundation/Foundation.h>


void ns_main_sync(dispatch_block_t block);

void ns_launch_app_at_url(NSURL * url, const char ** argv, int iFlags);

//
//void _openURL(const char * psz);
//
//
//void _openURL(const char * psz)
//{
//   CFURLRef url = CFURLCreateWithBytes(
//                  nullptr,                        // allocator
//                  (const ::u8*)psz,     // URLBytes
//                  strlen(psz),            // length
//                  kCFStringEncodingASCII,      // encoding
//                  nullptr                         // baseURL
//                  );
//   LSOpenCFURLRef(url,0);
//   CFRelease(url);
//}
//


bool is_main_thread();


//void ns_do_main_loop(double dSeconds)
//{
//
//   if(is_main_thread())
//   {
//
//   [ [ NSRunLoop mainRunLoop ] runUntilDate : [ [ NSDate date ] dateByAddingTimeInterval : dSeconds ] ];
//
//
//   }
//
//}


bool ns_open_url(const char * psz)
{
   
   NSString * str = [NSString stringWithUTF8String:psz];
   
   if(str == NULL)
   {
      
      return false;
      
   }
   
   NSURL * url = [[NSURL alloc] initWithString: str];
   
   if(url == NULL)
   {
      
      return false;
      
   }
   
   if(![[NSWorkspace sharedWorkspace] openURL: url])
   {
      
      return false;
      
   }
   
   return true;
   
}



bool ns_open_file(const char * psz)
{
   
   NSString * path = [NSString stringWithUTF8String:psz];
   
   if(path == NULL)
   {
      
      return false;
      
   }
   
   if(![[NSWorkspace sharedWorkspace] openFile: path])
   {
      
      return false;
      
   }
   
   return true;
   
}


void ns_launch_bundle(const char * pszBundle, const char ** argv)
{

   NSString * bundle = [[NSString alloc] initWithUTF8String:pszBundle];
   
   NSURL * url = [[NSWorkspace sharedWorkspace] URLForApplicationWithBundleIdentifier:bundle];

   ns_launch_app_at_url(url, argv, 0x00010000 | 0x00080000);
                        
}


void os_post_quit()
{
   
   ns_main_sync(^()
   {
   
      [NSApp terminate:nil];
      
   });
   
}


void library_launch(const char *psz)
{
   NSString *path =  [NSString stringWithUTF8String:psz];
   NSWorkspace *ws=[NSWorkspace sharedWorkspace];
   NSURL* url = [NSURL fileURLWithPath:path isDirectory:YES];
   
   NSMutableDictionary* dict = [[NSMutableDictionary alloc] init];
   [ws launchApplicationAtURL:url
                      options:NSWorkspaceLaunchDefault
                configuration:dict
                        error:nil];
   
   
}


void ns_launch_app_at_url(NSURL * url, const char ** argv, int iFlags)
{

   NSWorkspace * workspace = [NSWorkspace sharedWorkspace];

   NSMutableDictionary * dict = [[NSMutableDictionary alloc] init];

   if(argv != NULL)
   {

      NSMutableArray * array = [[NSMutableArray alloc] init];

      while(*argv != NULL)
      {

         [array addObject: [[NSString alloc] initWithUTF8String: *argv]];

         argv++;

      }

      [dict setObject:array forKey:NSWorkspaceLaunchConfigurationArguments];

   }

   //NSWorkspaceLaunchWithoutActivation
   //NSWorkspaceLaunchNewInstance
   //NSWorkspaceLaunchDefault

   [workspace launchApplicationAtURL:url options: iFlags configuration:dict error:nil];


}



