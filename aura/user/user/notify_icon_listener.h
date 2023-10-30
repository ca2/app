#pragma once


//#include "acme/primitive/collection/pointer_array.h"
#include "apex/platform/application_menu.h"
#include "apex/user/user/notify_icon_bridge.h"


namespace user
{


   class CLASS_DECL_AURA notify_icon_listener :
      //virtual public ::user_notify_icon_bridge
      virtual public ::particle
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

      //   item(string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");

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


      //virtual int _get_notification_area_action_count();
      //virtual const char * _get_notification_area_action_name(int iIndex);
      //virtual const char * _get_notification_area_action_id(int iIndex);
      //virtual const char * _get_notification_area_action_label(int iIndex);
      //virtual const char * _get_notification_area_action_accelerator(int iIndex);
      //virtual const char * _get_notification_area_action_description(int iIndex);
      virtual void call_notification_area_action(const ::scoped_string & pszId);


      //virtual bool notify_icon_insert_item(bool bStockItem, index & iIndex, string strName, string strId = "", string strLabel = "", string strAccelerator = "", string strDescription = "");


   };


} // namespace user



