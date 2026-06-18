#pragma once


#include "acme/handler/command_handler.h"
#include "acme/platform/application_menu.h"


namespace user
{


   class CLASS_DECL_AURA notify_icon_listener :
      virtual public ::particle,
      virtual public ::command_handler
   {
   public:





      //class CLASS_DECL_AURA item :
      //   virtual public ::particle
      //{
      //public:

      //   string m_strName;
      //   string m_strId;
      //   string m_strLabel;
      //   string m_strAccelerator;
      //   string m_strDescription;
      //   bool  m_bStockItem = false;

      //   item();

      //   item(const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId = "", const ::scoped_string & scopedstrLabel = "", const ::scoped_string & scopedstrAccelerator = "", const ::scoped_string & scopedstrDescription = "");

      //   virtual ~item();

      //};


      //pointer_array < item >      m_notifyiconitema;

      ::pointer < class ::application_menu >    m_papplicationmenu;


      notify_icon_listener();
      ~notify_icon_listener() override;


      virtual class ::application_menu * menu();


      //virtual void OnNotifyIconMessage(::u32 uNotifyIcon, ::u32 message);
      //virtual void OnNotifyIconContextMenu(::u32 uNotifyIcon);
      //virtual void OnNotifyIconLButtonDblClk(::u32 uNotifyIcon);
      //virtual void OnNotifyIconLButtonDown(::u32 uNotifyIcon);


      //virtual ::i32 _get_notification_area_action_count();
      //virtual const_char_pointer _get_notification_area_action_name(::i32 iIndex);
      //virtual const_char_pointer _get_notification_area_action_id(::i32 iIndex);
      //virtual const_char_pointer _get_notification_area_action_label(::i32 iIndex);
      //virtual const_char_pointer _get_notification_area_action_accelerator(::i32 iIndex);
      //virtual const_char_pointer _get_notification_area_action_description(::i32 iIndex);
      bool handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;


      //virtual bool notify_icon_insert_item(bool bStockItem, ::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId = "", const ::scoped_string & scopedstrLabel = "", const ::scoped_string & scopedstrAccelerator = "", const ::scoped_string & scopedstrDescription = "");


   };


} // namespace user



