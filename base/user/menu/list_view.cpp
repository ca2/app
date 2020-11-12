#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/menu/_menu.h"
#endif


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





   bool menu_list_view::pre_create_window(::user::create_struct & cs)
   {

      return ::user::impact::pre_create_window(cs);

   }


   void menu_list_view::route_command_message(::user::command * pcommand)
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


   //bool menu_list_view::add_menu(::xml::node * pnode, ::user::interaction * puiNotify, ::u32 uCallbackMessage)
   //{

   //   destroy_menu();

   //   m_bAutoClose = false;

   //   if (!menu_list_window::add_menu(pnode))
   //      return false;

   //   //menu_fill(GetParentFrame(), this);

   //   m_puiMenuNotify = puiNotify;

   //   return true;

   //}


   void menu_list_view::PostNcDestroy()
   {

      ::user::menu_list_window::PostNcDestroy();

   }

} // namespace user


