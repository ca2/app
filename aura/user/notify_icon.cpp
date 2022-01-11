#include "framework.h"
#include "aura/user/_user.h"


namespace user
{


   notify_icon::notify_icon()
   {

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {


   }


   void notify_icon::create_notify_icon(const ::id & id, ::user::interaction * pinteractionNotify, ::windowing::icon * picon)
   {
      
      throw ::interface_only_exception();
      
      return error_interface_only;

   }


   void notify_icon::destroy_notify_icon()
   {

      return ::success;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if(!m_bCreated)
      {

         return error_failed;

      }

      throw ::interface_only_exception();

      return error_interface_only;

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      m_userinteractionaHidden.add_unique(puserinteraction);

      return ::success;

   }


   void notify_icon::step()
   {

      return ::success;

   }


   int notify_icon::_get_notification_area_action_count()
   {

      //return m_plistener->_get_notification_area_action_count();
      return (int) m_notifyiconitema.get_count();

   }


   const char * notify_icon::_get_notification_area_action_name(int iIndex)
   {

      //return m_plistener->_get_notification_area_action_name(iIndex);
      return m_notifyiconitema[iIndex]->m_strName;

   }


   const char * notify_icon::_get_notification_area_action_id(int iIndex)
   {

      //return m_plistener->_get_notification_area_action_id(iIndex);
      return m_notifyiconitema[iIndex]->m_strId;

   }


   const char * notify_icon::_get_notification_area_action_label(int iIndex)
   {

      //return m_plistener->_get_notification_area_action_label(iIndex);
      return m_notifyiconitema[iIndex]->m_strLabel;

   }


   const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
   {

      //return m_plistener->_get_notification_area_action_accelerator(iIndex);
      return m_notifyiconitema[iIndex]->m_strAccelerator;

   }


   const char * notify_icon::_get_notification_area_action_description(int iIndex)
   {

      //return m_plistener->_get_notification_area_action_description(iIndex);
      return m_notifyiconitema[iIndex]->m_strDescription;

   }


   void notify_icon::call_notification_area_action(const char * pszId)
   {

      ::id id(pszId);

      auto pcommand = __new(::message::command(id));

      route_command(pcommand);

//      m_plistener->call_notification_area_action(pszId);

   }


   void notify_icon::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      m_puserinteractionNotify->route_command(pcommand);

   }


   void notify_icon::on_command(::message::command* pcommand)
   {

      ::channel::on_command(pcommand);

      //if (pcommand->m_id.is_text())
      //{

      //   string strId(pcommand->m_id);

      //   call_notification_area_action(strId);

      //}
      //else
      //{

      //   WARNING("notification area action id is number or enum?!?!");

      //}

//      pcommand->m_bRet = true;

   }


} // namespace user



