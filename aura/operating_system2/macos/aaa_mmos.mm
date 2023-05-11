#include "_mm.h"


void system_call_update_wallpaper_changed();

bool mm2_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz);

//
//void ns_main_async(dispatch_block_t block)
//{
//   
//   //   dispatch_block_t block = ^{
//   //      // Code for the method goes here
//   //   };
//   //
//   
//   if ([NSThread isMainThread])
//   {
//      
//      block();
//      
//   }
//   else
//   {
//      
//      dispatch_async(dispatch_get_main_queue(), block);
//      
//   }
//   
//}





@implementation mmos

-(NSURL *)browse_folder : (NSURL *) directoryURL canCreateDirectories: (bool) bCanCreateDirectories
{
   
   NSOpenPanel * panel = [NSOpenPanel openPanel];
   
   [panel setCanCreateDirectories: bCanCreateDirectories];

   [panel setAllowsMultipleSelection: NO];
   
   [panel setCanChooseDirectories:YES];
   
   [panel setCanChooseFiles:NO];
   
   if(directoryURL != nil)
   {

      panel.directoryURL = directoryURL;
   
   }
   
   if ([panel runModal] != NSFileHandlingPanelOKButton)
   {
      
      return NULL;
      
   }

   return [[panel URLs] lastObject];
   
}


-(NSArray < NSURL *> *)browse_file_open : (NSURL **) startDir multi: (bool) b
{
   
   NSOpenPanel *panel = [NSOpenPanel openPanel];
   
      [panel setAllowsMultipleSelection:b];
   
      [panel setCanChooseDirectories:NO];
   
      [panel setCanChooseFiles:YES];
   
      if(startDir != nil && *startDir !=nil)
      {
         
         panel.directoryURL= *startDir;
   
      }
   
      NSInteger result = [panel runModal];
      
      if(startDir != nil)
      {
         
         *startDir = panel.directoryURL;
         
      }
      
      if(result != NSFileHandlingPanelOKButton)
      {
         
         return NULL;
         
      }


   return [panel URLs];
   
}


+ (id)get
{
   
   static mmos * s_mmos = NULL;
   
   if(s_mmos == NULL)
   {
      
      s_mmos = ([[self alloc] init]);
      
      s_mmos->theLock = [[NSRecursiveLock alloc] init];
      
      s_mmos->m_ppszWallpaper = NULL;
      
      s_mmos->m_llWallpaper = 0;
      
      s_mmos->m_iIcon = 0;
      
      [s_mmos monitorWallpaper];
      
      [s_mmos monitorIconForFile];
      
      [[s_mmos dd_invokeOnMainThreadAndWaitUntilDone: TRUE] deferWallpaper:NULL];
      
   }
   
   return s_mmos;
   
}


- (void)get_user_wallpaper:(void **)charpp forScreen:(NSScreen *) s;
{
   
   char ** ppsz = (char **) charpp;
   
   NSURL * purl = [[NSWorkspace sharedWorkspace] desktopImageURLForScreen:s];
   
   if(purl == NULL)
   {
      
      *ppsz = NULL;
      
   }
   else
   {
   
      *ppsz = strdup([[purl absoluteString] UTF8String]);
                     
   }
   
}


- (void)get_user_wallpaper:(void *)charppp getCount:(void *) llp
{

   long long * pll = (long long *) llp;

   NSArray<NSScreen *> * screenArray = [NSScreen screens];

   *pll = [screenArray count];
   
   char ** p = (char **) malloc(*pll * sizeof(char*));
   
   char *** ppsz = (char ***) charppp;
   
   *ppsz = p;

   for (int i = 0; i < *pll; i++)
   {
   
      NSScreen * screen = [screenArray objectAtIndex: i];
      
      [self get_user_wallpaper: (void **)&p[i] forScreen:screen];
   
   }
   
}


- (void)desktopImageChanged:(NSNotification *)notification
{
   
   system_call_update_wallpaper_changed();
   
}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   if([app.localizedName isEqualToString:@"ScreenSaverEngine"])
   {
      
      system_call_update_wallpaper_changed();
      
   }
   
}


-(void)monitorWallpaper
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferWallpaper:)];
   
   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];
   
   [inv setTarget: self];
   
   [inv setSelector: @selector(deferWallpaper:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1
                                    invocation:inv
                                       repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)runRunnableOnMainThread:(generic *)prunnable
{
   
   [[self dd_invokeOnMainThread] runRunnable: prunnable];
   
}


-(void)runRunnable:(generic *)prunnable
{
   
   prunnable->call();
   
}


-(void)deferWallpaper:(NSTimer *)timer
{
   
   char ** ppsz = NULL;
   
   long long ll;
   
   [self get_user_wallpaper: (void *) &ppsz getCount: (void *) &ll];
   
   [self->theLock lock];
   
   char ** ppszOld = self->m_ppszWallpaper;
   
   long long llOld = self->m_llWallpaper;
   
   if(ppsz != NULL)
   {
      
      self->m_ppszWallpaper = ppsz;
      
      self->m_llWallpaper = ll;
      
      for(long long i = 0; i < llOld; i++)
      {
         
         free(ppszOld[i]);
         
      }
      
      free(ppszOld);
      
   }

   [self->theLock unlock];
   
}


-(void)monitorIconForFile
{
   
   NSRunLoop* myRunLoop = [NSRunLoop mainRunLoop];
   
   NSMethodSignature *sgn = [self methodSignatureForSelector:@selector(deferIconForFile:)];

   NSInvocation *inv = [NSInvocation invocationWithMethodSignature: sgn];

   [inv setTarget: self];

   [inv setSelector:@selector(deferIconForFile:)];
   
   NSTimer *t = [NSTimer timerWithTimeInterval: 0.1 invocation:inv repeats:YES];
   
   [myRunLoop addTimer:t forMode:NSDefaultRunLoopMode];
   
}


-(void)deferIconForFile:(NSTimer *)timer
{

   if(self->m_iIcon != 1)
   {
      
      return;
      
   }
      
   if(self->m_pszIcon == NULL)
   {
      
      self->m_iIcon = 0;
      
      return;
      
   }
   
   mm2_get_file_image(self->m_picon, self->m_cxIcon, self->m_cyIcon, self->m_iScanIcon, self->m_pszIcon);
   
   self->m_iIcon = 0;
   
}


@end


bool mm1a_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const char * psz)
{
   
   mmos * os = [mmos get];
   
   if(os->m_iIcon == 0)
   {

      os->m_pszIcon = psz;

      os->m_picon = pcr;

      os->m_cxIcon = cx;

      os->m_cyIcon = cy;

      os->m_iScanIcon = iScan;

      os->m_iIcon = 1;

      while(os->m_iIcon != 0)
      {
         
         millis_sleep(5);
         
      }

   }
   
   return true;
      
}


void ns_set_this_process_binary_default_browser()
{
   
   CFBundleRef bundle = CFBundleGetMainBundle();
   
   CFURLRef url = CFBundleCopyBundleURL(bundle);
   
   LSRegisterURL(url, true);
   
   CFStringRef identifier = CFBundleGetIdentifier(bundle);
   
   LSSetDefaultHandlerForURLScheme(CFSTR("http"), identifier);
   
}


void ns_log(const char * pszLog)
{
 
   NSString * strLog = [[NSString alloc]initWithUTF8String:pszLog];
   
   NSLog(@"%@", strLog);
   
}





char * mm_browse_folder(const char * pszStartDir, bool bCanCreateDirectories)
{
   
   __block char * p = NULL;
   
   ns_main_sync(^
   {
      
      mmos * pos = [mmos get];
      
      NSURL * startDir = NULL;
      
      if(pszStartDir != NULL)
      {
         
         NSString * str = [[NSString alloc] initWithUTF8String:pszStartDir];
       
         startDir = [[NSURL alloc]initWithString :str];
         
      }

      NSURL * url = [pos browse_folder:startDir canCreateDirectories:bCanCreateDirectories];
      
      p = __strdup( [url absoluteString]);
      
   });
            
   return p;

}


char** mm_browse_file_open(const char ** pszStartDir, bool bMulti)
{
   
   __block char ** pp = NULL;
   
   ns_main_sync(^
   {
   
      mmos * pos = [mmos get];
      
      NSURL * startDir = NULL;
      
      if(pszStartDir != NULL && *pszStartDir != NULL)
      {
         
         NSString * str = [[NSString alloc] initWithUTF8String:*pszStartDir];
         
         startDir = [[NSURL alloc]initWithString :str];
         
      }
      
      NSArray < NSURL * > * urla = [pos browse_file_open:&startDir multi:bMulti];

      pp = (char **)malloc((urla.count + 1) * sizeof(char*));
      
      int i = 0;
      
      for(; i < urla.count; i++)
      {
         
         pp[i] = __strdup([[urla objectAtIndex:i] absoluteString]);
         
      }
      
      pp[i] = NULL;
      
      *pszStartDir = __strdup([startDir absoluteString]);
                   
   });
   
   return pp;
   
}







