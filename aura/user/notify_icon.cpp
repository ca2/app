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


   ::e_status notify_icon::create_notify_icon(::u32 uId, notify_icon_listener * plistener, ::windowing::icon * picon)
   {
      
      __throw(error_interface_only);
      
      return error_interface_only;

   }


   ::e_status notify_icon::destroy_notify_icon()
   {

      return ::success;

   }


   ::e_status notify_icon::modify_icon(::windowing::icon * picon)
   {

      if(!m_bCreated)
      {

         return error_failed;

      }

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::e_status notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      m_userinteractionaHidden.add_unique(puserinteraction);

      return ::success;

   }


   ::e_status notify_icon::step()
   {

      return ::success;

   }


   int notify_icon::_get_notification_area_action_count()
   {

      return m_plistener->_get_notification_area_action_count();

   }


   const char * notify_icon::_get_notification_area_action_name(int iIndex)
   {

      return m_plistener->_get_notification_area_action_name(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_id(int iIndex)
   {

      return m_plistener->_get_notification_area_action_id(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_label(int iIndex)
   {

      return m_plistener->_get_notification_area_action_label(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_accelerator(int iIndex)
   {

      return m_plistener->_get_notification_area_action_accelerator(iIndex);

   }


   const char * notify_icon::_get_notification_area_action_description(int iIndex)
   {

      return m_plistener->_get_notification_area_action_description(iIndex);

   }


   void notify_icon::call_notification_area_action(const char * pszId)
   {

      m_plistener->call_notification_area_action(pszId);

   }


} // namespace user



