//
// Created by camilo on 19/01/2021. <3TBS, Mummi and bilbo!!
//
// From user_notify_icon_bridge to application_menu_callback by
// camilo on 2023-10-30 23:45 <3ThomasBorregaardSorensen!!
#pragma once


struct application_menu_callback :
   virtual public ::particle
{
public:


//   virtual int _get_notification_area_action_count() = 0;
//   virtual const char * _get_notification_area_action_name(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_id(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_label(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_accelerator(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_description(int iIndex) = 0;
   virtual bool on_application_menu_action(const ::atom & atom) = 0;


};

//
//
//
//struct user_notify_icon_bridge :
//   virtual public ::particle
//{
//public:
//
//
//   virtual int _get_notification_area_action_count() = 0;
//   virtual const char * _get_notification_area_action_name(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_id(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_label(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_accelerator(int iIndex) = 0;
//   virtual const char * _get_notification_area_action_description(int iIndex) = 0;
//   virtual void call_notification_area_action(const ::scoped_string & scopedstrId) = 0;
//
//
//};
//
//
//
