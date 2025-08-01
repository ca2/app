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
::platform::application * get_platform_application();


void ns_main_post(dispatch_block_t block);

void os_system_start();

void application_on_menu_action(::platform::application * papplication, const char * pszCommand);

::platform::system * application_system(::platform::application * papplication);

void system_id_update(::platform::system * psystem, long long iUpdate, long long iPayload);

void node_will_finish_launching(::platform::system * psystem);
void system_on_open_untitled_file(::platform::system * psystem);
void system_on_open_file(::platform::system * psystem, const char * pszFile);

void ios_on_app_changed_occlusion_state();

void set_apex_system_as_thread();

@implementation ios_app


- (id)init
{

   self = [super init];
   
   m_windowcontrollera = [ [ NSMutableArray alloc ] init ];
   
   return self;
   
}


-(void)dealloc
{
   
   
}

-(void)continueInitialization
{
   
}



-(void)applicationActivity:(NSNotification *)notification
{
   
//   UIRunningApplication *app = [[notification userInfo] objectForKey:@"NSWorkspaceApplicationKey"];
//   
//   NSString * strName = app.localizedName;
//   //if([ isEqualToString:@"ScreenSaverEngine"])
//   {
//      printf("NOTIFICATION: %s", [strName UTF8String]);
//
//      // Your code here
//   }
}


//
//-(NSWindowController *) addWindow:(NSWindow*)window
//{
//   
//   NSWindowController * pwindowcontroller = [ [ NSWindowController alloc ] initWithWindow : window ];
//   
//   [ m_windowcontrollera addObject : pwindowcontroller ];
//   
//   return pwindowcontroller;
//   
//}
//
//-(void) removeWindowController:(NSWindowController*)pwindowcontroller
//{
//   
//
//   
//   [ m_windowcontrollera removeObject : pwindowcontroller ];
//   
//}

//-(void) removeWindowController:(NSWindowController*)pwindowcontroller
//{
//   
//   [ m_windowcontrollera removeObject : pwindowcontroller ];
//   
//}


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
//         //m_pbridge->notification_area_action(scopedstr);
//         
//         application_on_menu_action(m_papplication, psz);
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
//         //m_pbridge->notification_area_action(scopedstr);
//         
//         application_on_menu_action(m_papplication, psz);
//         
//         return;
//         
//      //}
//      
//   }
//   
//}


//- (void)applicationWillFinishLaunching:(NSNotification *)notification

- (BOOL)application:(UIApplication *)application
willFinishLaunchingWithOptions:(NSDictionary<UIApplicationLaunchOptionsKey, id> *)launchOptions
{
   
   if(!m_papplication)
   {
      
      m_papplication = get_platform_application();
      
   }
   
   m_pacmenotificationcallback = [ [ acme_notification_callback alloc ]  init ];
   
   m_pacmenotificationcallback->m_papplication = m_papplication;
  
   [m_pacmenotificationcallback fetch_dark_mode];
   

   
   node_will_finish_launching(application_system(m_papplication));

//   NSAppleEventManager *appleEventManager = [NSAppleEventManager sharedAppleEventManager];
//
//   [appleEventManager setEventHandler:self andSelector:@selector(handleGetURLEvent:withReplyEvent:) forEventClass:kInternetEventClass andEventID:kAEGetURL];
   
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
   
   //set_apex_system_as_thread();
   //MessageBox(NULL, "applicationDidFinishLaunching", "applicationDidFinishLaunching", e_message_box_ok);
   
   //defer_run_system();
   
}


- (BOOL)applicationShouldHandleReopen:(UIApplication *)sender hasVisibleWindows:(BOOL)flag
{
   
   //MessageBox(NULL, "applicationShouldHandleReopen", "applicationShouldHandleReopen", e_message_box_ok);
   
   system_id_update(application_system(m_papplication), id_app_activated, 0);

   return NO;
   
}

- (void)applicationDidChangeOcclusionState:(NSNotification *)notification
{
   
   //ios_on_app_changed_occlusion_state();
   
}


- (BOOL)applicationOpenUntitledFile:(UIApplication *)sender
{
   
   //file_put_contents("/eco/001.txt", "applicationOpenUntitledFile");
   
   system_on_open_untitled_file(application_system(m_papplication));
   
   return YES;
   
}



- (BOOL)application:(UIApplication *)sender openFile:(NSString *)filename
{
   
   //file_put_contents("/eco/002.txt", "applicationOpenFile");
   //file_put_contents("/eco/003.txt", [filename UTF8String]);

   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return true;
   
}



- (void)application:(UIApplication *)sender openFiles:(NSArray<NSString *> *)filenames
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
      
      system_on_open_file(application_system(m_papplication), psz);
      
      //psza[ul] = psz;
      
   }
   
//   defer_run_system(scopedstra, (int) ulCount);
//
//
}


- (void)application:(UIApplication *)application open:(NSURL * )url
{
   //file_put_contents("/eco/006.txt", "open");
   //file_add_contents_raw("/eco/006.txt", [[url absoluteString] UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [[url absoluteString] UTF8String]);
   
}


- (BOOL)application:(id)sender
  openFileWithoutUI:(NSString *)filename;
{
   //file_put_contents("/eco/007.txt", "openFileWithoutUI");
   //file_add_contents_raw("/eco/007.txt", [filename UTF8String]);
   
   //MessageBox(NULL, "application: openFile", "application: openFile", e_message_box_ok);
   
   system_on_open_file(application_system(m_papplication), [filename UTF8String]);
   
   return TRUE;
   
}


- (void)application:(UIApplication *)application openURLs:(NSArray<NSURL *> *)urls
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
      
      system_on_open_file(application_system(m_papplication), psz);
      
      //free
      
   }
   
   //defer_run_system(scopedstra, (int) ulCount);

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
//- (void)handleGetURLEvent:(UIAppleEventDescriptor *)event
//           withReplyEvent:(NSAppleEventDescriptor *)replyEvent {
//   
//   // Extract the URL from the Apple event and handle it here.
//   NSString* url = [[event paramDescriptorForKeyword:keyDirectObject] stringValue];
//   
//   system_on_open_file(application_system(m_papplication), [url UTF8String]);
//   
//}


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
//         else if(!strcmp(scopedstrParent, pmenushared->m_ppszParent[i]))
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
//         //m_pbridge->notification_area_action(scopedstr);
//         
//         application_on_menu_action(m_papplication, psz);
//         
//         return;
//         
//      }
//      
//   }
//   
//}
//



@end



void os_menu_item_enable(void * pitem, bool bEnable)
{

   UIMenuItem * pmenuitem = (__bridge UIMenuItem *) pitem;

   //ns_main_post(^()
//   {
//
//      [pmenuitem setEnabled: bEnable];
//
//   });

}


void os_menu_item_check(void * pitem, bool bCheck)
{

   UIMenuItem * pmenuitem = (__bridge UIMenuItem *) pitem;

//   ns_main_post(^()
//   {
//      
//      if(bCheck)
//      {
//
//         [pmenuitem setState: NSOnState];
//
//      }
//      else
//      {
//         
//         [pmenuitem setState: NSOffState];
//         
//      }
//
//   });

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
//   ns_main_post(^{
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



void apple_set_application_delegate(::platform::application * papplication, void * pDelegate);

void ns_apple_set_application_delegate(::platform::application * papplication, ios_app * pappdelegate)
{
   
   UIApplication * application = [UIApplication sharedApplication];
   
   pappdelegate->m_papplication = papplication;
   
   [ application setDelegate: pappdelegate ];
   
   apple_set_application_delegate(papplication, (__bridge void *) pappdelegate);
   
   [ pappdelegate continueInitialization ];
   
   //[m_statusitem setEnabled:YES];
   
   [UIApplication sharedApplication];
   
//   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");

   
}


void * apple_get_application_delegate(::platform::application * papplication);


void defer_create_acme_application_delegate(::platform::application * papplication)
{
   
   ios_app * pappdelegate = (__bridge ios_app *) apple_get_application_delegate(papplication);

   if(pappdelegate == nullptr)
   {
      
      pappdelegate = [ [ ios_app alloc ] init ];
      
      ns_apple_set_application_delegate(papplication, pappdelegate);
      
   }
   
}


//
//
//void acme_ios_application_init(::platform::application * papplication, int argc, char *argv[])
//{
//
////   auto argc = psystem->m_psubsystem->m_argc;
////
////   auto argv = psystem->m_psubsystem->m_argv;
////
////   auto papp = psystem->m_pacmeapplication;
////
////   ::platform::application * papplication = (void *) (::acme::application *) papp;
////
//////      acme_ios_application_main(pApplication, argc, argv);
////
////      //return psystem->m_estatus;
////
//////   }
//   ///
//   ///
//   ///
//   defer_create_acme_application_delegate(pApplication);
//
//
//   ios_app * pappdelegate = (ios_app *) apple_get_application_delegate(pApplication);
//
//
//   void apple_set_application_delegate(::platform::application * papplication, void * pDelegate)
//
//
//   NSApplication * application = [NSApplication sharedApplication];
//
//   piosapp->m_papplication = pApplication;
//
//   [application setDelegate: piosapp];
//
//   [appDelegate fetch_dark_mode];
//
//   //[m_statusitem setEnabled:YES];
//
//   [NSApplication sharedApplication];
//
//   bool bNoDock = argcargv_contains_parameter(argc, argv, "no_dock");
//
//}


//
//void acme_ios_application_init(::platform::application * papplication, int argc, char *argv[])
//{
//
//   //   auto argc = psystem->m_psubsystem->m_argc;
//   //
//   //   auto argv = psystem->m_psubsystem->m_argv;
//   //
//   //   auto papp = psystem->m_pacmeapplication;
//   //
//   //   ::platform::application * papplication = (void *) (::acme::application *) papp;
//   //
//   ////      acme_ios_application_main(pApplication, argc, argv);
//   //
//   //      //return psystem->m_estatus;
//   //
//   ////   }
//   ///
//   ///void defer_create_ios_app()
//
//   ios_app * piosapp = [[ios_app alloc] init];
//
//   acme_ios_application_prepare(piosapp, pApplication, argc, argv);
//
//}


void acme_ios_application_main(::platform::application * papplication, int argc, char *argv[])
{
   
//
//   if(bNoDock)
//   {
//      
//      nsapp_activation_policy_accessory();
//      
//   }

//   [[UIApplication sharedApplication]  activateIgnoringOtherApps:YES];
   
   //[[UIApplication sharedApplication] run];
   UIApplicationMain(argc, argv, nil, NSStringFromClass([ios_app class]));
   
   
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
//         //m_pbridge->notification_area_action(scopedstr);
//         
//         on_application_menu_action(scopedstr);
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
//   //ios_on_app_changed_occlusion_state();
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
//   defer_run_system(scopedstra, (int) ulCount);
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
//   defer_run_system(scopedstra, (int) ulCount);
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
   
   auto frame = [[UIScreen mainScreen] nativeBounds];
   
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



void ui_application_main(int argc, char * argv[], const char * pszCommandLine, NSString * strDelegateClass)
{
   
//   NSString * strDelegateClass = [ [ NSString alloc ] initWithUTF8String: pszDelegateClass ];
   
   UIApplicationMain(argc, argv, nil, strDelegateClass);
   //NSStringFromClass([iosApp class])
}


void ns_acme_application_main(int argc, char * argv[], const char * pszCommandLine)
{
                              
   ui_application_main(argc, argv, pszCommandLine, NSStringFromClass([ios_app class]));
   
}
//
//
//void ns_app_run2()
//{
//   
//   ns_app_set_running(true);
//   
//   ui_application_main(, <#char **argv#>, <#const char *pszCommandLine#>)[ [ NSApplication sharedApplication ] run ];
//   
//   ns_app_set_running(false);
//   
//   
//}

//
//void ns_app_stop()
//{
//   
//   [ [ NSApplication sharedApplication ] stop:nil ];
//   NSEvent* event = [NSEvent otherEventWithType: NSApplicationDefined
//                                                        location: NSMakePoint(0,0)
//                                                  modifierFlags: 0
//                                                      timestamp: 0.0
//                                                   windowNumber: 0
//                                                        context: nil
//                                                        subtype: 0
//                                                          data1: 0
//                                                          data2: 0];
//                   [[ NSApplication sharedApplication ] postEvent: event atStart: FALSE];
//}
//


