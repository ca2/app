#include "framework.h"
#include "base/user/menu/_menu.h"


namespace user
{


   menu_list_view::menu_list_view()
   {

      m_bAutoClose = false;

   }


   void menu_list_view::install_message_routing(::channel * pchannel)
   {

      BASE::install_message_routing(pchannel);

   }


   menu_list_view::~menu_list_view()
   {

   }


   void menu_list_view::assert_valid() const
   {
      
      impact::assert_valid();
      
   }


   void menu_list_view::dump(dump_context & dumpcontext) const
   {
      
      impact::dump(dumpcontext);
      
   }


   bool menu_list_view::pre_create_window(::user::system * pusersystem)
   {

      return ::user::impact::pre_create_window(pusersystem);

   }


   void menu_list_view::route_command(::message::command * pcommand, bool bRouteToKeyDescendant)
   {

      __pointer(::user::interaction) puserinteractionNotify;

      if (::is_set(m_pchannelNotify)
            && m_pchannelNotify != this
            && (
               !puserinteractionNotify
               || !puserinteractionNotify->is_ascendant_of(this, true)))
      {

         m_pchannelNotify->route_command(pcommand);

         //if(pcommand->m_bRet)
         {

            return;

         }

      }

      return impact::route_command(pcommand);

   }


   void menu_list_view::post_non_client_destroy()
   {

      ::user::menu_list_window::post_non_client_destroy();

   }


   void tab_view::create_impact_menu(::user::impact_data * pimpactdata)
   {

      ::user::impact::create_view < ::user::menu_list_view >(pimpactdata);

   }


} // namespace user



