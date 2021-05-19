//
// Created by camilo on 19/01/2021. <3TBS, Mummi and bilbo!!
//
#pragma once


struct user_notify_icon_bridge :
   virtual public ::matter
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



