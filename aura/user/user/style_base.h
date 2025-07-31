#pragma once


//#include "acme/prototype/geometry2d/_geome//try2d.h"
#include "acme/constant/element.h"
#include "apex/handler/manager.h"


namespace user
{


   class CLASS_DECL_AURA style_base :
      virtual public ::manager
   {
   public:


      class ::time      m_timeUserStyleBaseDarkMode;
      bool              m_bUserStyleBaseDarkMode;


      style_base();
      ~style_base() override;



#ifdef _DEBUG

      long long increment_reference_count() override;
      long long decrement_reference_count() override;

#endif


      void on_initialize_particle() override; 


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual void increment_update_sequence();


      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style_pointer & pstyle, ::menu::item * pitem) = 0;
      //virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::menu::item * pitem) = 0;
      //virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::menu::item * pitem) = 0;
      //virtual void set_style(enum_style estyle);

      //virtual void set_style(const ::scoped_string & scopedstrStyle);

      //virtual void _on_style_change(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_user_color();

      virtual bool is_dark_mode() const;


      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::interaction * pframe);
      virtual bool draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::int_rectangle & rectangle, ::draw2d::graphics_pointer & pgraphics);

      virtual ::int_rectangle simple_ui_focus_rect_extra_margin(::user::interaction * pinteraction);
      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics);
      virtual bool simple_ui_draw_border(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics);
      //virtual bool on_ui_event(enum_happening ehappening, e_object eobject, ::user::interaction * pinteraction) = 0;
      //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,tab * ptab) = 0;
      //virtual bool _001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * ptab) = 0;
      //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & rectangle,::draw2d::brush_pointer & pbrushText) = 0;

      //virtual bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) = 0;
      //virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox) = 0;
      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar);
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout);



      virtual enum_control_type get_control_type() const;


      virtual ::color::color get_color(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate = ::user::e_state_none);
      virtual bool get_int(::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate = ::user::e_state_none);
      virtual bool get_double(::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate = ::user::e_state_none);


   };


} // namespace user



