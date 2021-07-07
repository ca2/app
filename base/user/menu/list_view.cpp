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


   void menu_list_view::route_command_message(::message::command * pcommand)
   {

      if (m_puiMenuNotify != nullptr
            && m_puiMenuNotify != this
            && !m_puiMenuNotify->is_ascendant_of(this, true))
      {

         m_puiMenuNotify->route_command_message(pcommand);

         //if(pcommand->m_bRet)
         {

            return;

         }

      }

      return impact::route_command_message(pcommand);

   }


   void menu_list_view::PostNcDestroy()
   {

      ::user::menu_list_window::PostNcDestroy();

   }


} // namespace user



