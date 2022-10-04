//
//  RoundWindowApp.h
//  axis
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 27/09/14.
//
//

//
//  RoundWindowFrameImpact.h
//  RoundWindow
//
//  Created by Matt Gallagher on 12/12/08.
//  Copyright 2008 Matt Gallagher. All rights reserved.
//
//  Permission is given to use this source code file without charge in any
//  project, commercial or otherwise, entirely at your risk, with the condition
//  that any redistribution (in part or whole) of source code must retain
//  this copyright and permission notice. Attribution in compiled projects is
//  appreciated but not required.
//


@interface macos_app : NSObject < NSApplicationDelegate >
{
@public

   void *               m_pApp;
   //NSMenu *             m_menu;
   //NSMutableArray *     m_menuitema;
   //NSMutableArray *     m_menuida;
   
   NSMutableArray *     m_windowcontrollera;

}


//////////////appDelegate->m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];

///////appDelegate->m_menuitema = [[NSMutableArray alloc] init];

////////////appDelegate->m_menuida = [[NSMutableArray alloc] init];

//int iCount = pbridge->_get_notification_area_action_count();

//int iCount = 1;
//
//for(int i = 0; i < iCount; i++)
//{
//
//   //      char * pszName = nullptr;
//   //      char * pszId = nullptr;
//   //      char * pszLabel = nullptr;
//   //      char * pszAccelerator = nullptr;
//   //      char * pszDescription = nullptr;
//   //
//   //      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
//
//   char * pszName = strdup("TransparentFxxx");
//   char * pszId = strdup("transparent_frame");
//   char * pszLabel = strdup("TransparentFxxx");
//   char * pszAccelerator = strdup("TransparentFxxx");
//   char * pszDescription = strdup("TransparentFxxx");
//   NSString * strTitle = nullptr;
//
//   NSString * strId = nullptr;
//
//   NSMenuItem * item = nullptr;
//
//   if(strcasecmp(pszName, "separator") == 0)
//   {
//
//      strTitle = [[NSString alloc] initWithUTF8String: pszName];
//
//      strId = [[NSString alloc] initWithUTF8String: pszName];
//
//      item = [NSMenuItem separatorItem];
//
//   }
//   else
//   {
//
//      strTitle = [[NSString alloc] initWithUTF8String: pszName];
//
//      strId = [[NSString alloc] initWithUTF8String: pszId];
//
//      item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(play:) keyEquivalent:@"" ];
//
//   }
//
//   [item setTarget:appDelegate];
//
//   [appDelegate->m_menu addItem:item];
//
//   [appDelegate->m_menuitema addObject: item];
//
//   [appDelegate->m_menuida addObject: strId];
//
//   if(pszName) free(pszName);
//   if(pszId) free(pszId);
//   if(pszLabel) free(pszLabel);
//   if(pszAccelerator) free(pszAccelerator);
//   if(pszDescription) free(pszDescription);
//
//}

//[appDelegate->m_menu setDelegate:NSApp];

//-(NSMenu *) applicationDockMenu:(NSApplication*)sender;
-(NSWindowController *) addWindow:(NSWindow*)window;
//@property(strong) NSWindowController *m_pwindowcontroller;
//- (void)play:(id)sender;
-(void)fetch_dark_mode;
@end
