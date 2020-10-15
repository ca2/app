#pragma once


// GDK, GTK :: C

extern "C"
{


   void linux_g_direct_init();
   void linux_g_direct_term();
   //void * linux_g_direct_app_indicator_new(const char * pszId, const char * pszIcon, const char * pszFolder, struct user_notify_icon_bridge * pbridge);
   void linux_g_direct_step(void * pind);
   //void linux_g_direct_app_indicator_term(void * pind);


} // extern "C"


struct user_notify_icon_bridge
{
public:


   virtual int _get_notification_area_action_count() = 0;
   virtual const char * _get_notification_area_action_name(int iIndex) = 0;
   virtual const char * _get_notification_area_action_id(int iIndex) = 0;
   virtual const char * _get_notification_area_action_label(int iIndex) = 0;
   virtual const char * _get_notification_area_action_accelerator(int iIndex) = 0;
   virtual const char * _get_notification_area_action_description(int iIndex) = 0;
   virtual void call_notification_area_action(const char * pszId) = 0;


};


#include "gnome_shared.h"




