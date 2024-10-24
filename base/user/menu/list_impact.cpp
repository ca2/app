#include "framework.h"
#include "list_impact.h"
#include "acme/constant/timer.h"


namespace user
{


   menu_list_impact::menu_list_impact()
   {

      m_bAutoClose = false;
      m_bExtendOnParentHostingArea = true;

   }


   menu_list_impact::~menu_list_impact()
   {


   }


   void menu_list_impact::install_message_routing(::channel * pchannel)
   {

      BASE::install_message_routing(pchannel);

   }


   bool menu_list_impact::pre_create_window(::user::system * pusersystem)
   {

      return ::user::impact::pre_create_window(pusersystem);

   }


   void menu_list_impact::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      ::pointer<::user::interaction>puserinteractionNotify;

      if (::is_set(m_pchannelNotify)
            && m_pchannelNotify != this
            && (
               !puserinteractionNotify
               || !puserinteractionNotify->is_ascendant_of(this, true)))
      {

         m_pchannelNotify->route_command(pcommand);

         if(pcommand->m_bRet)
         {

            return;

         }

      }

      return impact::route_command(pcommand);

   }


   void menu_list_impact::destroy()
   {

      ::user::menu_list_window::destroy();

   }


} // namespace user



