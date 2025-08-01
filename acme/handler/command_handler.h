//
// Created by camilo on 19/01/2021. <3TBS, Mummi and bilbo!!
//
// From user_notify_icon_bridge to application_menu_callback by
// camilo on 2023-10-30 23:45 <3ThomasBorregaardSorensen!!
//
// Because I love Thomas mate( and Mummi mate and bilbo mate!!)
// and because Thommmi likes handlers...
// application_menu_callback as command_handler on 2024-12-21 02:42 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{

   class activation_token;

}


struct command_handler :
   virtual public ::particle
{
public:


//   virtual int _get_notification_area_action_count() = 0;
//   virtual const_char_pointer _get_notification_area_action_name(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_id(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_label(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_accelerator(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_description(int iIndex) = 0;
   virtual bool handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken) = 0;


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
//   virtual const_char_pointer _get_notification_area_action_name(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_id(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_label(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_accelerator(int iIndex) = 0;
//   virtual const_char_pointer _get_notification_area_action_description(int iIndex) = 0;
//   virtual void call_notification_area_action(const ::scoped_string & scopedstrId) = 0;
//
//
//};
//
//
//
