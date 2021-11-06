#pragma once


// GDK, GTK :: C

extern "C"
{


   void linux_g_direct_init();
   void linux_g_direct_term();
   //void * linux_g_direct_app_indicator_new(const ::string & pszId, const ::string & pszIcon, const ::string & pszFolder, struct user_notify_icon_bridge * pbridge);
   void linux_g_direct_step(void * pind);
   //void linux_g_direct_app_indicator_term(void * pind);


} // extern "C"


struct user_notify_icon_bridge
{
public:


   virtual int _get_notification_area_action_count() = 0;
   virtual bool _get_notification_area_action_info(char ** ppszName, char ** ppszId, char ** ppszLabel, char ** ppszAccelerator, char ** ppszDescription, int iIndex) = 0;
   virtual void call_notification_area_action(const ::string & pszId) = 0;


};


#include "gtk_things/gnome_shared.h"




