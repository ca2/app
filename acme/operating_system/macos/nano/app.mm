//
//  RoundWindowApp.m
//  axis
//
//  Created by Camilo Sasuke Tsumanuma on 27/09/14.
//
//
#include "framework.h"
#include "app.h"
#include "acme/constant/id.h"
#include "acme/operating_system/argcargv.h"
//#include "apex/user/menu_shared.h"
void ns_main_async(dispatch_block_t block);
//void on_start_system(void * pSystem);

//void macos_calc_dark_mode();
void os_system_start();
//int file_put_contents(const char * path, const char * contents);
//void file_add_contents_raw(const char * path, const char * psz);

void application_on_menu_action(void * pApplication, const char * pszCommand);
void * application_system(void * pApplication);


void system_id_update(void* pSystem, ::i64 iUpdate, ::i64 iPayload);

void node_will_finish_launching(void * pSystem);
void system_on_open_untitled_file(void * pSystem);
void system_on_open_file(void * pSystem, const char * pszFile);


//void system_call_update_app_activated();
void macos_on_app_changed_occlusion_state();

void set_apex_system_as_thread();

@implementation macos_app

-(NSWindowController *) addWindow:(NSWindow*)window
{
   
   NSWindowController * pwindowcontroller = [ [ NSWindowController alloc ] initWithWindow : window ];
   
   [ m_windowcontrollera addObject : pwindowcontroller ];
   
   return pwindowcontroller;
   
}


//@synthesize m_pwindowcontroller;
- (id)init
{

   self = [super init];
   
//   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
//
   
   m_windowcontrollera = [ [ NSMutableArray alloc ] init ];
   
//   
//   m_menuida = [[NSMutableArray alloc] init];
//   
//   // Monitor menu/dock theme changes...
//   [NSDistributedNotificationCenter.defaultCenter addObserver:self selector:@selector(themeChanged:) name:@"AppleInterfaceThemeChangedNotification" object: nil];
//
//   //int iCount = pbridge->_get_notification_area_action_count();
//   
//   int iCount = 1;
//   
//   for(int i = 0; i < iCount; i++)
//   {
//      
//      //      char * pszName = NULL;
//      //      char * pszId = NULL;
//      //      char * pszLabel = NULL;
//      //      char * pszAccelerator = NULL;
//      //      char * pszDescription = NULL;
//      //
//      //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
//      
//      char * pszName = strdup("TransparentFxxx");
//      char * pszId = strdup("transparent_frame");
//      char * pszLabel = strdup("TransparentFxxx");
//      char * pszAccelerator = strdup("TransparentFxxx");
//      char * pszDescription = strdup("TransparentFxxx");
//      NSString * strTitle = NULL;
//      
//      NSString * strId = NULL;
//      
//      NSMenuItem * item = NULL;
//      
//      if(strcasecmp(pszName, "separator") == 0)
//      {
//         
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//         
//         strId = [[NSString alloc] initWithUTF8String: pszName];
//         
//         item = [NSMenuItem separatorItem];
//         
//      }
//      else
//      {
//         
//         strTitle = [[NSString alloc] initWithUTF8String: pszName];
//         
//         strId = [[NSString alloc] initWithUTF8String: pszId];
//         
//         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(on_os_menu_item:) keyEquivalent:@"" ];
//         
//      }
//      
//      [item setTarget:self];
//      
//      [m_menu addItem:item];
//      
//      [m_menuitema addObject: item];
//      
//      [m_menuida addObject: strId];
//      
//      if(pszName) free(pszName);
//      if(pszId) free(pszId);
//      if(pszLabel) free(pszLabel);
//      if(pszAccelerator) free(pszAccelerator);
//      if(pszDescription) free(pszDescription);
//   }
//   
//   [m_menu setDelegate:self];
//   
//
//      [[[NSWorkspace sharedWorkspace] notificationCenter]
//       addObserver:self
//       selector:@selector(applicationActivity:)
//       name:NSWorkspaceActiveSpaceDidChangeNotification
//       object:nil];
//   
//   


//
//   [[[NSWorkspace sharedWorkspace] notificationCenter]
//    addObserver:self
//    selector:@selector(applicationDidChangeOcclusionState:)
//    name:NSApplicationDidChangeOcclusionStateNotification
//    object:nil];
   return self;
}


-(void)applicationActivity:(NSNotification *)notification
{
   
   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
   
   NSString * strName = app.localizedName;
   //if([ isEqualToString:@"ScreenSaverEngine"])
   {
      printf("NOTIFICATION: %s", [strName UTF8String]);

      // Your code here
   }
}


//- (void)on_os_menu_item:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   for(int i = 0; i < [m_menuitema count]; i++)
//   {
//      
//      if(pitem == [m_menuitema objectAtIndex:i])
//      {
//         
//         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_pApp, psz);
//         
//         return;
//         
//      }
//      
//   }
//   
//}

//- (void)on_command:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   NSString * str = (NSString *)[pitem representedObject];
//if(str != nil)
//{
//         const char * psz = [str UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_pApp, psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}


- (void)applicationWillFinishLaunching:(NSNotification *)notification
{
   
   //macos_calc_dark_mode();
   
   node_will_finish_launching(application_system(m_pApp));

   NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];

   [appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   //defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
   
   system_id_update(application_system(m_pApp), id_app_activated, 0);

   return NO;
   
}

- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
{
   
   //macos_on_app_changed_occlusion_state();
   
}


- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
{
   
   //file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
   
   system_on_open_untitled_file(application_system(m_pApp));
   
   return YES;
   
}



- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
{
   
   //file_put_contents("/eco/002.txt", "applicationOpenFile");
   //file_put_contents("/eco/003.txt", [filename UTF8String]);

   system_on_open_file(application_system(m_pApp), [filename UTF8String]);
   
   return true;
   
}



- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
{
   
   unsigned long ulCount = [filenames count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[filenames objectAtIndex:ul] UTF8String];
      
      system_on_open_file(application_system(m_pApp), psz);
      
      //psza[ul] = psz;
      
   }
   
//   defer_run_system(psza, (int) ulCount);
//
//
}


- (void)application:(NSApplication *)application open:(NSURL * )url
{
   //file_put_contents("/eco/006.txt", "open");
   //file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_pApp), [[url absoluteString] UTF8String]);
   
}


- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   //file_put_contents("/eco/007.txt", "openFileWithoutUI");
   //file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_pApp), [filename UTF8String]);
   
   return TRUE;
   
}

- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
{
   unsigned long ulCount = [urls count];
   
   if(ulCount <= 0)
   {
      
      return;
      
   }
   
   //char ** psza = (char **) malloc(ulCount * sizeof(char*));
   
   for(unsigned long ul = 0; ul < ulCount; ul++)
   {
      
      const char * psz = [[[urls objectAtIndex:ul] absoluteString] UTF8String];
      
      //psza[ul] = psz;
      
      system_on_open_file(application_system(m_pApp), psz);
      
      //free
      
   }
   
   //defer_run_system(psza, (int) ulCount);
   
   

}



- (void)applicationWillTerminate:(NSNotification *)notification
{
   
   
   
}



//- (void)sendEvent:(NSEvent *)theEvent
//{
//
//   /*
//
//   char szEvent[128];
//
//   ·zero(szEvent);
//
//   if([theEvent type] == NSLeftMouseDown)
//   {
//
//      strcpy(szEvent, "NSLeftMouseDown");
//
//   }
//   else if([theEvent type] == NSLeftMouseUp)
//   {
//
//      strcpy(szEvent, "NSLeftMouseUp");
//
//   }
//
//   if(strlen(szEvent) > 0)
//   {
//
//      char szEventCopy[128];
//
//      strcpy(szEventCopy, szEvent);
//
//      printf("\n%s", szEventCopy);
//
//   }
//
//   */
//
//   [super sendEvent:theEvent];
//
//}
- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
   
   // Extract the URL from the Apple event and handle it here.
   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
   
   system_on_open_file(application_system(m_pApp), [url UTF8String]);
   
}


//-(NSMenu *) applicationDockMenu:(NSApplication*)sender
//{
//
//   return m_menu;
//   
//}


//- (void) ns_add_menu :(NSMenu *) menuParent withParent: (const char *) pszParent  withSharedMenu : (menu_shared *) pmenushared
//{
//
//   if(!pmenushared)
//   {
//
//      return;
//
//   }
//
//      for(int i = 0; i < pmenushared->m_iCount; i++)
//      {
//
//         if(!strcmp("separator", pmenushared->m_ppszId[i]))
//         {
//
//            NSMenuItem * menuitem = [NSMenuItem separatorItem];
//
//            [menuParent addItem: menuitem];
//
//         }
//         else if(!strcmp(pszParent, pmenushared->m_ppszParent[i]))
//         {
//
//            NSString * strTitle = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszMenu[i]];
//
//            NSMenuItem * menuitem = [[NSMenuItem alloc] initWithTitle:strTitle action:@selector(on_command:) keyEquivalent:@""];
//
//            NSString * strId = [[NSString alloc] initWithUTF8String:pmenushared->m_ppszId[i]];
//
//            pmenushared->m_ositema[i] = (__bridge void * )menuitem;
//
//            [menuitem setTarget: self];
//
//            [menuitem setRepresentedObject: strId];
//
//            [menuParent addItem: menuitem];
//
//         }
//
//      }
//
//
//}

//
//- (void)play:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   for(int i = 0; i < [m_menuitema count]; i++)
//   {
//      
//      if(pitem == [m_menuitema objectAtIndex:i])
//      {
//         
//         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         application_on_menu_action(m_pApp, psz);
//         
//         return;
//         
//      }
//      
//   }
//   
//}
//

-(void)themeChanged:(NSNotification *) notification
{
 
   NSLog (@"%@", notification);
   
   [self fetch_dark_mode];
   
//   system_id_update(application_system(m_pApp), id_user_color, 0);
   
}


-(void) fetch_dark_mode
{
   NSString *interfaceStyle = [NSUserDefaults.standardUserDefaults valueForKey:@"AppleInterfaceStyle"];
   int iDarkMode = [interfaceStyle isEqualToString:@"Dark"];

   system_id_update(application_system(m_pApp), id_set_dark_mode, iDarkMode);

}


@end



void os_menu_item_enable(void * pitem, bool bEnable)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_async(^()
   {

      [pmenuitem setEnabled: bEnable];

   });

}


void os_menu_item_check(void * pitem, bool bCheck)
{

   NSMenuItem * pmenuitem = (__bridge NSMenuItem *) pitem;

   ns_main_async(^()
   {
      
      if(bCheck)
      {

         [pmenuitem setState: NSOnState];
         
      }
      else
      {
         
         [pmenuitem setState: NSOffState];
         
      }

   });

}

//
//void ns_create_main_menu(menu_shared * pmenushared)
//{
//
//   if(pmenushared)
//   {
//
//      menu_shared_increment_reference_count(pmenushared);
//
//   }
//
//   ns_main_async(^{
//   id menuMain = [NSMenu alloc];
//
//   macOSApp * papp = (macOSApp *) [[NSApplication sharedApplication] delegate ];
//
//   {
//
//      id menuitemApp = [NSMenuItem alloc];
//
//      [menuMain addItem: menuitemApp];
//
//      id menuApp = [NSMenu alloc];
//
//      [menuitemApp setSubmenu: menuApp];
//
//      id strAppName = [[NSProcessInfo processInfo] processName];
//
//      id strQuitTitle = [[_("Quit") stringByAppendingString: @" "] stringByAppendingString: strAppName];
//
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//
//      if(pmenushared)
//      {
//      [ papp ns_add_menu : menuApp withParent: "" withSharedMenu: pmenushared];
//
//      }
//
//      [menuApp addItem: menuitemQuit];
//
//   }
//
//
//   {
//
//      id menuitemView = [NSMenuItem alloc];
//
//      [menuMain addItem: menuitemView];
//
//      id menuView = [[NSMenu alloc] initWithTitle:_("View")];
//
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//
//      [menuitemView setSubmenu: menuView];
//
//      id strFxxTitle = _("Transparent Frame");
//
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//
//      if(pmenushared)
//      {
//      [ papp ns_add_menu : menuView withParent: "view" withSharedMenu: pmenushared];
//
//      }
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//
//      [menuView addItem: menuitemFxx];
//
//   }
//
//   [NSApp setMainMenu:menuMain];
//
//      if(pmenushared)
//      {
//
//         menu_shared_release(pmenushared);
//
//      }
//
//   });
//
//
//
//}
//
//
void os_begin_system();


void acme_macos_application_main(void * pApplication, int argc, char *argv[])
{
   
   NSApplication * application = [NSApplication sharedApplication];
   
   macos_app * appDelegate = [[macos_app alloc] init];
   
   appDelegate->m_pApp = pApplication;
   
   [application setDelegate:appDelegate];
   
   [appDelegate fetch_dark_mode];
   
   //[m_statusitem setEnabled:YES];
   
   [NSApplication sharedApplication];
   
   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");
//   
//   if(bNoDock)
//   {
//      
//      nsapp_activation_policy_accessory();
//      
//   }

   [NSApp activateIgnoringOtherApps:YES];
   
   [NSApp run];
   
}


//-(void)applicationActivity:(NSNotification *)notification
//{
//   NSRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
//   
//   NSString * strName = app.localizedName;
//   //if([ isEqualToString:@"ScreenSaverEngine"])
//   {
//      printf("NOTIFICATION: %s", [strName UTF8String]);
//
//      // Your code here
//   }
//}
//
//
//
//- (void)on_command:(id)sender
//{
//   
//   NSMenuItem * pitem = (NSMenuItem *) sender;
//   
//   NSString * str = (NSString *)[pitem representedObject];
//if(str != nil)
//{
//         const char * psz = [str UTF8String];
//         
//         //m_pbridge->notification_area_action(psz);
//         
//         on_application_menu_action(psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}
//- (void)applicationWillFinishLaunching:(NSNotification *)notification
//{
//NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];// 1
//[appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
//   
//}
//
//- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
//{
//   
//   set_apex_system_as_thread();
//   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
//   
//   defer_run_system();
//   
//}
//
//
//- (BOOL)applicationShouldHandleReopen:(NSApplication *)sender hasVisibleWindows:(BOOL)flag
//{
//   
//   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
//   
//   system_call_update_app_activated();
//
//   return NO;
//   
//}
//
//- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
//{
//   
//   //macos_on_app_changed_occlusion_state();
//   
//}
//
//
//- (BOOL)applicationOpenUntitledFile:(NSApplication *)sender
//{
//   
//   file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
//   //MessageBox(NULL, "applicationOpenUntitledFile", "applicationOpenUntitledFile", e_message_box_ok);
//   
//   defer_run_system();
//   
//   //__start_system_with_file(NULL);
//   
//   return YES;
//   
//}
//
//
//
//- (BOOL)application:(NSApplication *)sender openFile:(NSString *)filename
//{
//   
//   file_put_contents("/eco/002.txt", "applicationOpenFile");
//   file_put_contents("/eco/003.txt", [filename UTF8String]);
//
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//   
//   return true;
//   
//}
//
//
//
//- (void)application:(NSApplication *)sender openFiles:(NSArray<NSString *> *)filenames
//{
//   
//   unsigned long ulCount = [filenames count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[filenames objectAtIndex:ul] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//}
//- (void)application:(NSApplication *)application open:(NSURL * )url
//{
//   file_put_contents("/eco/006.txt", "open");
//   file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([[url absoluteString] UTF8String]);
//}
//
//- (BOOL)application:(id)sender
//  openFileWithoutUI:(NSString *)filename;
//{
//   file_put_contents("/eco/007.txt", "openFileWithoutUI");
//   file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
//   
//   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
//   
//   defer_run_system([filename UTF8String]);
//}
//
//- (void)application:(NSApplication *)application openURLs:(NSArray<NSURL *> *)urls
//{
//   unsigned long ulCount = [urls count];
//   
//   if(ulCount <= 0)
//   {
//      
//      return;
//      
//   }
//   
//   char ** psza = (char **) malloc(ulCount * sizeof(char*));
//   
//   for(unsigned long ul = 0; ul < ulCount; ul++)
//   {
//      
//      char * psz = strdup([[[urls objectAtIndex:ul] absoluteString] UTF8String]);
//      
//      psza[ul] = psz;
//      
//   }
//   
//   defer_run_system(psza, (int) ulCount);
//   
//   
//
//}
//
//
////- (void)sendEvent:(NSEvent *)theEvent
////{
////
////   /*
////   
////   char szEvent[128];
////   
////   ·zero(szEvent);
////   
////   if([theEvent type] == NSLeftMouseDown)
////   {
////   
////      strcpy(szEvent, "NSLeftMouseDown");
////      
////   }
////   else if([theEvent type] == NSLeftMouseUp)
////   {
////     
////      strcpy(szEvent, "NSLeftMouseUp");
////      
////   }
////   
////   if(strlen(szEvent) > 0)
////   {
////   
////      char szEventCopy[128];
////   
////      strcpy(szEventCopy, szEvent);
////      
////      printf("\n%s", szEventCopy);
////      
////   }
////   
////   */
////   
////   [super sendEvent:theEvent];
////   
////}
//- (void)handleGetURLEvent:(NSAppleEventDescriptor *)event
//           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
//   
//   // Extract the URL from the Apple event and handle it here.
//   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
//   
//   defer_run_system([url UTF8String]);
//   
//}
//-(NSMenu *) applicationDockMenu:(NSApplication*)sender
//{
//
//   
//   return m_menu;
//   
//}
//
////[appDelegate->m_menu setDelegate:NSApp];
//
//
//@end

//
//void ns_create_main_menu()
//{
//   
//   
//   id menuMain = [NSMenu alloc];
//   
//   {
//      
//      id menuitemApp = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemApp];
//      
//      id menuApp = [NSMenu alloc];
//      
//      [menuitemApp setSubmenu: menuApp];
//      
//      id strAppName = [[NSProcessInfo processInfo] processName];
//      
//      id strQuitTitle = [[_("Quit") stringByAppendingString: @" "] stringByAppendingString: strAppName];
//      
//      id menuitemQuit = [[NSMenuItem alloc] initWithTitle:strQuitTitle
//                                                   action:@selector(terminate:) keyEquivalent:@"q"];
//      
//      [menuApp addItem: menuitemQuit];
//      
//   }
//   
//   {
//      
//      id menuitemView = [NSMenuItem alloc];
//      
//      [menuMain addItem: menuitemView];
//      
//      id menuView = [[NSMenu alloc] initWithTitle:_("View")];
//      
//      [menuView setDelegate: [ [NSApplication sharedApplication] delegate ] ];
//      
//      [menuitemView setSubmenu: menuView];
//      
//      id strFxxTitle = _("Trasparentt(snowballeffect_smallerror>>>)Fxx");
//      
//      NSMenuItem * menuitemFxx = [[NSMenuItem alloc] initWithTitle:strFxxTitle
//                                                            action:@selector(on_command:) keyEquivalent:@"f"];
//      
//      [menuitemFxx setRepresentedObject: @"transparent_frame"];
//      
//      [menuView addItem: menuitemFxx];
//      
//   }
//   
//   [NSApp setMainMenu:menuMain];
//   
//   
//}




//void apex_application_main(int argc, char *argv[])
//{
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   macOSApp * appDelegate = [[macOSApp alloc] init];
//
//   [application setDelegate:appDelegate];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_paramater(argc, argv, "no_dock");
//
//   if(bNoDock)
//   {
//
//      nsapp_activation_policy_accessory();
//
//   }
////   else
////   {
////
////      nsapp_activation_policy_regular();
////
////   }
//
//
//   [NSApp activateIgnoringOtherApps:YES];
//
//   [NSApp run];
//
//}
//
//
//


//
//namespace user
//{
//
//
//
//
//   bool is_dark_mode()
//   {
//      
//         
//      return g_bMacosDarkMode;
//      
//   }
//
//
//} // namespace user


CLASS_DECL_ACME void ns_get_main_screen_size(int & cx, int & cy)
{
   
   auto frame = [[NSScreen mainScreen] frame];
   
   cx = frame.size.width;
   
   cy = frame.size.height;
   
}


bool g_bNsAppRunning = false;


void ns_app_set_running(bool bRunning)
{
   
   g_bNsAppRunning = bRunning;
   
}


bool ns_app_is_running()
{
   
   return g_bNsAppRunning;
   
}


void ns_app_run()
{
   
   ns_app_set_running(true);
   
   [ [ NSApplication sharedApplication ] run ];
   
   ns_app_set_running(false);
   
   
}


void ns_app_stop()
{
   
   [ [ NSApplication sharedApplication ] stop:nil ];
   NSEvent* event = [NSEvent otherEventWithType: NSApplicationDefined
                                                        location: NSMakePoint(0,0)
                                                  modifierFlags: 0
                                                      timestamp: 0.0
                                                   windowNumber: 0
                                                        context: nil
                                                        subtype: 0
                                                          data1: 0
                                                          data2: 0];
                   [[ NSApplication sharedApplication ] postEvent: event atStart: FALSE];
}



