// Created by camilo on 2026-05-19 16:42 <3ThomasBorregaardSørensen!!
#pragma once



namespace innate_ui
{


   class CLASS_DECL_APEX menu : virtual public ::object
   {
   public:


      menu();
      ~menu() override;


      virtual void load_menu_from_resource(int iMenuResourceId);

      virtual void set_default_menu_item_command_id(int iDefaultMenuItemCommandId);

      virtual void erase_menu_item_by_command_id(int iDefaultMenuItemCommandId);

      
      virtual void track_popup_menu(const ::operating_system::window & operatingsystemwindow, const ::function<void(int)> &functionOnActionId);




   };


} // namespace innate_ui
