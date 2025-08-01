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


      //virtual void OnNotifyIconMessage(unsigned int uNotifyIcon, unsigned int message);
      //virtual void OnNotifyIconContextMenu(unsigned int uNotifyIcon);
      //virtual void OnNotifyIconLButtonDblClk(unsigned int uNotifyIcon);
      //virtual void OnNotifyIconLButtonDown(unsigned int uNotifyIcon);


      //virtual int _get_notification_area_action_count();
      //virtual const_char_pointer _get_notification_area_action_name(int iIndex);
      //virtual const_char_pointer _get_notification_area_action_id(int iIndex);
      //virtual const_char_pointer _get_notification_area_action_label(int iIndex);
      //virtual const_char_pointer _get_notification_area_action_accelerator(int iIndex);
      //virtual const_char_pointer _get_notification_area_action_description(int iIndex);
      bool handle_command(const ::atom & atom, ::user::activation_token * puseractivationtoken) override;


      //virtual bool notify_icon_insert_item(bool bStockItem, ::collection::index & iIndex, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrId = "", const ::scoped_string & scopedstrLabel = "", const ::scoped_string & scopedstrAccelerator = "", const ::scoped_string & scopedstrDescription = "");


   };


} // namespace user



