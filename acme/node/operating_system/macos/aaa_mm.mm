///
//  macos_mm.m
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 3/8/16.
//
//
#import "_mm.h"


char * ns_get_default_browser_path()
{
   
    /*
   CFURLRef appURL = LSCopyDefaultApplicationURLForURL((__bridge CFURLRef)[NSURL URLWithString: @"http:"], kLSRolesAll, NULL);
   
   CFStringRef str = CFURLGetString(appURL);
   r
   char * psz = strdup([(__bridge NSString *)str UTF8String]);
   
   CFRelease(appURL);r
   
   //CFRelease(str);
   
     */
    
    char * psz = strdup("");
     
   return psz;
   
}


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



void node_launch_app(const char * psz, const char ** argv, int iFlags)
{
   
   return ns_launch_app(psz, argv, iFlags);
   
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


void ns_Sleep(unsigned int uiMillis)
{

   [NSThread sleepForTimeInterval: ((double) uiMillis / 1000.0) ];

}



//https://stackoverflow.com/questions/14699604/replacements-for-getmacosstatuserrorstring-getmacosstatuscommentstring

//11
//down vote
//accepted
//You can use [NSError errorWithDomain:NSOSStatusErrorDomain code:errorCode userInfo:nil] to get an NSError representing the OSStatus of errorCode. NSError provides the ability to get a localized error message from the error code (-localizedDescription), or a regular unlocalized one for debugging purposes (-description).

// GetMacOSStatusErrorString and GetMacOSStatusCommentString







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



char * macos_get_version()
{

   NSString *appVersion = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
 
   return strdup([appVersion UTF8String]);
   
}



