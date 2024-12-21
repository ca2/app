#include "framework.h"
#include "notify_icon.h"
#include "acme/exception/interface_only.h"


namespace user
{


   notify_icon::notify_icon()
   {

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {


   }


   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * pinteractionNotify, ::windowing::icon * picon)
   {
      
      //throw ::interface_only();
      
      //throw ::interface_only();

   }


   void notify_icon::destroy_notify_icon()
   {

      //return ::success;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if(!m_bCreated)
      {

         //return error_failed;

         throw ::exception(error_exception);

      }

      throw ::interface_only();

      //throw ::interface_only();

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      m_userinteractionaHidden.add_unique(puserinteraction);

      //return ::success;

   }


   bool notify_icon::notify_icon_step()
   {

   //   //return ::success;

      return true;

   }


   //int notify_icon::_get_notification_area_action_count()
   //{

   //   //return m_plistener->_get_notification_area_action_count();
   //   return (int) m_notifyiconitema.get_count();

   //}


   //const char * notify_icon::_get_notification_area_action_name(int iIndex)
   //{

   //   //return m_plistener->_get_notification_area_action_name(iIndex);
   //   return m_notifyiconitema[iIndex]->m_strName;

   //}


   //const char * notify_icon::_get_notification_area_action_id(int iIndex)
   //{

   //   //return m_plistener->_get_notification_area_action_id(iIndex);
   //   return m_notifyiconitema[iIndex]->m_strId;

   //}


   //const char * notify_icon::_get_notification_area_action_label(int iIndex)
   //{

   //   //return m_plistener->_get_notification_area_action_label(iIndex);
   //   return m_notifyiconitema[iIndex]->m_strLabel;

   //}


   //const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
   //{

   //   //return m_plistener->_get_notification_area_action_accelerator(iIndex);
   //   return m_notifyiconitema[iIndex]->m_strAccelerator;

   //}


   //const char * notify_icon::_get_notification_area_action_description(int iIndex)
   //{

   //   //return m_plistener->_get_notification_area_action_description(iIndex);
   //   return m_notifyiconitema[iIndex]->m_strDescription;

   //}


   bool notify_icon::on_application_menu_command(const ::atom &atom)
   {

      auto pcommand = __allocate ::message::command(atom);

      route_command(pcommand);

//      m_plistener->call_notification_area_action(pszId);

      return pcommand->m_bRet;

   }


   void notify_icon::route_command(::message::command* pcommand, bool bRouteToKeyDescendant)
   {

      m_puserinteractionNotify->route_command(pcommand);

   }


   void notify_icon::on_command(::message::command* pcommand)
   {

      ::channel::on_command(pcommand);

      //if (pcommand->m_atom.is_text())
      //{

      //   string strId(pcommand->m_atom);

      //   call_notification_area_action(strId);

      //}
      //else
      //{

      //   warning() <<"notification area action atom is number or enum?!?!";

      //}

//      pcommand->m_bRet = true;

   }


} // namespace user



