#pragma once


namespace user
{


   class CLASS_DECL_AURA style_base :
      virtual public object
   {
   public:


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, menu_item * pitem) = 0;
      //virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;
      //virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) = 0;


      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe) = 0;
      virtual bool draw_check(::enum_check echeck, const ::rect & rect, ::draw2d::graphics_pointer & pgraphics) = 0;

      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics) = 0;
      //virtual bool on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction) = 0;
      //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,tab * ptab) = 0;
      //virtual bool _001OnDrawMenuInteraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * ptab) = 0;
      //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::rect & rect,::draw2d::brush_pointer & brushText) = 0;

      //virtual bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) = 0;
      //virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox) = 0;
      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar) = 0;
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) = 0;
      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) = 0;
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout);



      virtual e_control_type get_control_type() const;


      virtual ::color get_color(const ::user::interaction* pinteraction, ::user::e_element eelement, ::user::estate estate = ::user::e_state_none) const;

   };


} // namespace user



