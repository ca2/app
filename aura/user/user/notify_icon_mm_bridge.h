//
//  user_notify_icon_mm_bridge.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 3/17/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#ifndef user_notify_icon_mm_bridge_h
#define user_notify_icon_mm_bridge_h


#ifdef __OBJC__
#include "notify_icon_mm.h"
#endif

class user_notify_icon_mm_bridge
{
public:


   void * m_pnotifyicon;




   virtual void notify_icon_init(const char * strIconFile);
   virtual void notify_icon_play(const char * action) = 0;

   virtual void notify_icon_destroy();


   virtual int _get_notification_area_action_count() = 0;
   virtual bool _get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex) = 0;
   virtual void call_notification_area_action(const char * pszId) = 0;


};





#endif /* user_notify_icon_mm_bridge_h */
