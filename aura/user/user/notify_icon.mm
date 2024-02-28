//
//  user_notify_icon.m
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//


#import "notify_icon_mm.h"
#import "notify_icon_mm_bridge.h"


@implementation user_notify_icon


//
// initWithContentRect:styleMask:backing:defer:screen:
//
// Init method for the object.
//
- (id)init:(NSString*)strIconFile bridge:(user_notify_icon_mm_bridge *)pbridge
{
   
   m_pbridge = pbridge;
   
   // http://stackoverflow.com/questions/3409985/how-to-create-a-menubar-application-for-mac
   m_statusitem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
   
   [m_statusitem setHighlightMode: YES];
   
   [m_statusitem setImage: [[NSImage alloc] initByReferencingFile:strIconFile]];
   
   m_menu = [[NSMenu alloc] initWithTitle:@"menubar_menu"];
   
   m_menuitema = [[NSMutableArray alloc] init];
   
   m_menuida = [[NSMutableArray alloc] init];
   
   int iCount = pbridge->_get_notification_area_action_count();
   
   for(int i = 0; i < iCount; i++)
   {
      
      char * pszName = NULL;
      char * pszId = NULL;
      char * pszLabel = NULL;
      char * pszAccelerator = NULL;
      char * pszDescription = NULL;
      
      pbridge->_get_notification_area_action_info(&pszName, &pszId, &pszLabel, &pszAccelerator, &pszDescription, i);
      
      NSString * strTitle = NULL;
      
      NSString * strId = NULL;
      
      NSMenuItem * item = NULL;

      if(strcasecmp(pszName, "separator") == 0)
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [[NSString alloc] initWithUTF8String: pszName];
         
         item = [NSMenuItem separatorItem];
         
      }
      else
      {
         
         strTitle = [[NSString alloc] initWithUTF8String: pszName];
         
         strId = [[NSString alloc] initWithUTF8String: pszId];
         
         item = [[NSMenuItem alloc] initWithTitle:  strTitle action: @selector(play:) keyEquivalent:@"" ];
         
      }
      
      [item setTarget:self];
      
      [m_menu addItem:item];
      
      [m_menuitema addObject: item];
      
      [m_menuida addObject: strId];
      
      if(pszName) free(pszName);
      if(pszId) free(pszId);
      if(pszLabel) free(pszLabel);
      if(pszAccelerator) free(pszAccelerator);
      if(pszDescription) free(pszDescription);

   }
   
   [m_menu setDelegate:self];
   
   [m_statusitem setMenu: m_menu];
   
   [m_statusitem setEnabled:YES];
   
   return self;
   
}


- (void)dealloc
{
   
   m_pbridge = NULL;
   
}


- (void)play:(id)sender
{
   
   NSMenuItem * pitem = (NSMenuItem *) sender;
   
   if(m_pbridge == NULL)
   {
      
      return;
      
   }
   
   for(int i = 0; i < m_pbridge->_get_notification_area_action_count(); i++)
   {
      
      if(pitem == [m_menuitema objectAtIndex:i])
      {
         
         const char * psz = [[m_menuida objectAtIndex:i] UTF8String];
         
         m_pbridge->call_notification_area_action(psz);
         
         return;
         
      }
      
   }
   
}


- (void)close
{
 
   [[NSStatusBar systemStatusBar] removeStatusItem: m_statusitem];
   
}


@end



