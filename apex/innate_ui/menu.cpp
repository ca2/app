// Created by camilo on 2026-05-19 16:48 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "menu.h"


namespace innate_ui
{


   menu::menu() {}


   menu::~menu() {}


   void menu::load_menu_from_resource(::i32 iMenuResourceId)
   {

      throw ::interface_only();

   }
   void menu::set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId)
   {

      throw ::interface_only();

   }


   void menu::erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId)
   {

      throw ::interface_only();

   }
   

   void menu::track_popup_menu(const ::operating_system::window &operatingsystemwindow,
                               const ::function<void(::i32)> &functionOnActionId)
   {
      
      throw ::interface_only();
          
   }


   void menu::add_item(const ::scoped_string & scopedstr, int iId)
   {
      
      throw ::interface_only();
      
   }


   void menu::add_separator()
   {

      throw ::interface_only();
      
   }


} // namespace innate_ui
