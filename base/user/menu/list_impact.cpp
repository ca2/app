#include "framework.h"
#include "base/user/menu/_menu.h"
#include "acme/timer.h"


namespace user
{


   menu_list_impact::menu_list_impact()
   {

      m_bAutoClose = false;

   }



   menu_list_impact::~menu_list_impact()
   {

   }


   void menu_list_impact::assert_ok() const
   {
      
      impact::assert_ok();
      
   }


   void menu_list_impact::dump(dump_context & dumpcontext) const
   {
      
      impact::dump(dumpcontext);
      
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

      __pointer(::user::interaction) puserinteractionNotify;

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


   void menu_list_impact::post_non_client_destroy()
   {

      ::user::menu_list_window::post_non_client_destroy();

   }


   void tab_impact::creatimpact_menu(::user::impact_data * pimpactdata)
   {

      ::user::impact::create_view < ::user::menu_list_impact >(pimpactdata);

   }



} // namespace user



