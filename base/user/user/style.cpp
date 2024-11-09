#include "framework.h"
#include "style.h"
#include "user.h"
#include "acme/platform/system.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/user/user/interaction.h"
#include "base/platform/session.h"
#include "base/user/menu/interaction.h"
#include "user/menu/item.h"


namespace base
{


   style::style()
   {

      m_plibrary = nullptr;

      construct_fallback_theme();

   }


   style::~style()
   {

   }


   void style::destroy()
   {

      m_plibrary.release();

      ::axis::style::destroy();

   }


   // ::base::application* style::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::base::session* style::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::base::system* style::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }
   //
   //
   // ::base::user* style::user()
   // {
   //
   //
   //
   //    return ::is_set(psession) ? user() : nullptr;
   //
   // }


   ::pointer<::user::menu_interaction>style::create_menu_button(::user::style_pointer& pstyle, ::draw2d::graphics_pointer & pgraphics, ::menu::item* pitem)
   {

      auto puser = user();

      pgraphics->m_puserstyleGraphics = this;

      return puser->create_menu_button(pitem->m_pmenu, pgraphics, pitem);

   }


   void style::construct_fallback_theme()
   {


   }


   void style::initialize_theme()
   {



   }


   bool style::_001TabOnDrawSchema01(::draw2d::graphics_pointer& pgraphics, ::user::tab* ptab)
   {

      return false;

   }


   bool style::_001OnDrawMenuInteraction(::draw2d::graphics_pointer& pgraphics, ::user::menu_interaction* pbutton)
   {

      return false;

   }


   void style::_001OnTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer& pgraphics, const ::int_rectangle& rectangle, ::draw2d::brush_pointer& pbrushText, const ::user::e_state & estate)
   {


   }


   bool style::_001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab* ptab)
   {

      return false;

   }


//
//   void style::nextstyle(style_context * pcontext)
//   {
//
//      if (pcontext->m_econtroltype != control_none
//            && m_map.lookup(pcontext->m_econtroltype, pcontext->pstyle))
//      {
//
//         return;
//
//      }
//
//      pcontext->pstyle = this;
//
//   }
//
//   void style::initialize_theme()
//   {
//
//      theme_current_control(control_menu);
//
//      create_int(int_menu_check_padding, 3);
//      create_int(int_button_draw_text_flags, e_align_center | DT_SINGLELINE);
//      create_int(int_menu_item_draw_text_flags, e_align_left_center | DT_SINGLELINE);
//
//      create_rect_coord(rect_menu_margin, 4, 4, 4, 4);
//      create_rect_coord(rect_menu_border, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_padding, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_item_margin, 0, 0, 0, 1);
//      create_rect_coord(rect_menu_item_border, 0, 0, 0, 0);
//      create_rect_coord(rect_menu_item_padding, 2, 2, 2, 2);
//
//
//
//      theme_current_control(e_control_type_button);
//
//      create_point_font(font_default, pnode->font_name(e_font_sans), 11.0);
//
//      create_opaque_color(color_text_normal, ::color_black);
//      create_session_default_opaque_color(color_text_press, COLOR_HIGHLIGHT);
//      create_opaque_color(color_text_disabled, ::color_gray);
//      create_session_default_opaque_color(color_text_hover, COLOR_HIGHLIGHT);
//      create_session_default_opaque_color(color_background, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_press, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_disabled, COLOR_3DFACE);
//      create_session_default_opaque_color(color_background_hover, COLOR_3DFACE);
//      create_flag(flag_border);
//      create_translucency(e_element_none, ::user::e_translucency_none);
//
//
//
//      theme_current_control(control_menu_button);
//
//      create_point_font(font_default, pnode->font_name(e_font_sans), 12.0);
//
//      create_color(color_text_normal, color_with_byte_opacity(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, color_with_byte_opacity(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_color(color_background, argb(100, 180, 192, 255));
//      create_color(color_background_press, argb(200, 180, 192, 255));
//      create_color(color_background_disabled, argb(100, 180, 192, 255));
//      create_color(color_background_hover, argb(125, 180, 192, 255));
//      create_flag(flag_border);
//      create_translucency(e_element_none, ::user::e_translucency_present);
//
//
//
//      theme_current_control(control_menu_popup);
//
//      create_point_font(font_default, pnode->font_name(e_font_sans), 9.0, e_font_weight_bold);
//      create_color(color_text_normal, color_with_byte_opacity(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, color_with_byte_opacity(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_press, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DHIGHLIGHT);
//      create_session_default_color(color_background_hover, 200, COLOR_3DHIGHLIGHT);
//      create_flag(flag_border, false);
//      create_translucency(e_element_none, ::user::e_translucency_present);
//
//
//
//      theme_current_control(control_system_menu_button);
//
//      create_point_font(font_default, "Marlett", 11.0);
//
//      create_color(color_text_normal, color_with_byte_opacity(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, color_with_byte_opacity(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
//      create_flag(flag_border, false);
//      create_translucency(e_element_none, ::user::e_translucency_present);
//
//
//      theme_current_control(control_system_menu_close);
//
//      create_point_font(font_default, "Marlett", 11.0);
//      create_color(color_text_normal, argb(200, 200, 100, 80));
//      create_color(color_text_press, argb(225, 255, 0, 0));
//      create_color(color_text_disabled, argb(200, 127, 127, 127));
//      create_color(color_text_hover, argb(200, 255, 50, 50));
//      create_color(color_background, argb(200, 210, 192, 192));
//      create_color(color_background_press, argb(225, 255, 192, 192));
//      create_color(color_background_disabled, argb(200, 192, 192, 192));
//      create_color(color_background_hover, argb(200, 223, 192, 192));
//      create_flag(flag_border, false);
//      create_translucency(e_element_none, ::user::e_translucency_present);
//
//
//      theme_current_control(control_system_menu_popup);
//
//      create_point_font(font_default, "Marlett", 11.0);
//
//      create_color(color_text_normal, color_with_byte_opacity(200, ::color_black));
//      create_session_default_color(color_text_press, 200, COLOR_HIGHLIGHT);
//      create_color(color_text_disabled, color_with_byte_opacity(200, ::color_gray));
//      create_session_default_color(color_text_hover, 200, COLOR_HIGHLIGHT);
//      create_session_default_color(color_background, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_press, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_disabled, 200, COLOR_3DFACE);
//      create_session_default_color(color_background_hover, 200, COLOR_3DFACE);
//      create_flag(flag_border, false);
//      create_translucency(e_element_none, ::user::e_translucency_present);
//
//
//   }
//
//   //virtual ::user::menu_interaction * create_menu_button(::user::style_pointer & pstyle, ::menu::item * pitem) override;

   bool style::prepare_menu(::draw2d::graphics_pointer& pgraphics, ::menu::item* pitem)
   {

         return true;

      }

   bool style::prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::menu::item* pitem)
   {

      return true;

}
//
//
//   //virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame_interaction * pframe) override;
//   //virtual void DrawCheck(enum_check echeck, const ::int_rectangle & rectangle, ::draw2d::graphics_pointer & pgraphics) override;
//   //virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics) override;
//   //virtual bool on_ui_event(enum_happening ehappening, e_object eobject, ::user::interaction * pinteraction) override;
//   //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, tab * ptab) override;
//   //virtual bool _001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * pbutton) override;
//   //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText) override;

//   //virtual bool _001OnTabLayout(::user::tab * ptab) override;
//   //virtual void _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangleX, ::enum_check echeck) override;

//   //virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar) override;
//   //virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, simple_scroll_bar * pbar) override;
//   //virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;
//
//
//   //virtual bool select_text_color(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
//   //virtual bool select_solid_brush(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor);
//   //virtual bool set(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);
//
//
//
//   //virtual bool select_text_color(::user::interaction * pinteraction, e_color ecolor = color_text);
//   //virtual bool select_solid_brush(::user::interaction * pinteraction, e_color ecolor);
//   //virtual bool set(::user::interaction * pinteraction, e_font efont = font_default);
//
//
//
//   //virtual ::color::color           _001GetColor(::user::interaction * pinteraction, e_color ecolor, ::color::color crDefault = 0);
//   //virtual ::write_text::font_pointer  _001GetFont(::user::interaction * pinteraction, e_font efont, ::write_text::font * pfont = nullptr);
//   //virtual enum_translucency     _001GetTranslucency(::user::interaction * pinteraction, enum_element eelement = e_element_none, enum_translucency etranslucencyDefault = e_translucency_undefined);
//   //virtual bool               _001GetFlag(::user::interaction * pinteraction, ::user::enum_flag eflag, bool bDefault = false);
//   //virtual const int_rectangle &               _001GetRect(::user::interaction * pinteraction, ::user::e_rect erect, ::int_rectangle rectangleDefault = nullptr);
//   //virtual int                _001GetInt(::user::interaction * pinteraction, ::user::e_int eint, int iDefault = 0);
//   //virtual double             _001GetDouble(::user::interaction * pinteraction, ::user::e_double edouble, double dDefault = 0.0);
//
//   //virtual bool _001IsBackgroundBypass(::user::interaction * pinteraction, enum_element eelement = e_element_none);
//   //virtual bool _001IsTransparent(::user::interaction * pinteraction, enum_element eelement = e_element_none);
//   //virtual bool _001IsTranslucent(::user::interaction * pinteraction, enum_element eelement = e_element_none);
//   //virtual bool _001HasTranslucency(::user::interaction * pinteraction, enum_element eelement = e_element_none);
//
//
//
//
//
//
//   //virtual ::user::style * userstyle() = 0;
//
//
//
//   //virtual void on_select_user_style();
//   //virtual ::user::style * parent_userstyle();
//   //virtual style * style_get(e_schema eschema) = 0;
//
//
//   //virtual ::draw2d::graphics * style_get_graphics();
//
//
//   //virtual bool userstyle_color(::color::color & color32, e_color ecolor, ::user::interaction * pinteraction);
//   //virtual bool userstyle_font(::write_text::font_pointer & sp, e_font efont, ::user::interaction * pinteraction);
//   //virtual bool userstyle_translucency(enum_translucency & etranslucency, enum_element eelement, ::user::interaction * pinteraction);
//   //virtual bool userstyle_flag(bool & bSet, ::user::enum_flag eflag, ::user::interaction * pinteraction);
//   //virtual bool userstyle_rect(const int_rectangle & & rectangle, ::user::e_rect erect, ::user::interaction * pinteraction);
//   //virtual bool userstyle_int(int & i, ::user::e_int eint, ::user::interaction * pinteraction);
//   //virtual bool userstyle_double(double & d, ::user::e_double edouble, ::user::interaction * pinteraction);
//
//
//   //virtual bool style_color(::color::color & color32, e_color ecolor, ::user::interaction * pinteraction);
//   //virtual bool style_font(::write_text::font_pointer & sp, e_font efont, ::user::interaction * pinteraction);
//   //virtual bool style_translucency(enum_translucency & etranslucency, enum_element eelement, ::user::interaction * pinteraction);
//   //virtual bool style_flag(bool & bSet, ::user::enum_flag eflag, ::user::interaction * pinteraction);
//   //virtual bool style_rect(const int_rectangle & & rectangle, ::user::e_rect erect, ::user::interaction * pinteraction);
//   //virtual bool style_int(int & i, ::user::e_int eint, ::user::interaction * pinteraction);
//   //virtual bool style_double(double & d, ::user::e_double edouble, ::user::interaction * pinteraction);
//
//   void style::theme_current_control(e_control econtrol)
//   {
//
//      if (econtrol == control_none)
//      {
//
//         pstyle = this;
//
//         return;
//
//      }
//
//      style_pointer & pstyle = m_map[econtrol];
//
//      if (pstyle.is_null())
//      {
//
//         pstyle = __allocate style(this);
//
//      }
//
//      pstyle = pstyle;
//
//   }
//
//
//   //::user::style * style::userstyle()
//   //{
//
//   //   return m_puserstyleThemeCurrentSchema;
//
//   //}
//
//
} // namespace base



