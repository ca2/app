// Created by camilo on 2026-05-19 16:42 <3ThomasBorregaardSørensen!!
#pragma once



namespace innate_ui
{


   class CLASS_DECL_APEX menu : virtual public ::object
   {
   public:


      menu();
      ~menu() override;


      virtual void load_menu_from_resource(::i32 iMenuResourceId);

      virtual void set_default_menu_item_command_id(::i32 iDefaultMenuItemCommandId);

      virtual void erase_menu_item_by_command_id(::i32 iDefaultMenuItemCommandId);

      
      virtual void track_popup_menu(const ::operating_system::window & operatingsystemwindow, const ::function<void(::i32)> &functionOnActionId);

      virtual void add_item(const ::scoped_string & scopedstr, int iId);
      virtual void add_separator();


   };


} // namespace innate_ui
