#pragma once


#include "base/user/user/style.h"


namespace experience_anthill
{


   class CLASS_DECL_APP_EXPERIENCE_ANTHILL style :
      virtual public ::base::style
   {
   public:


      style();
      ~style() override;

      virtual i64 increment_reference_count() override
      {

         return ::object::increment_reference_count();

      }

      virtual i64 decrement_reference_count() override
      {

         return ::object::decrement_reference_count();

      }


      void initialize_theme() override;


      ::color::color get_color(::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate) override;


      //      virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::interaction * pframewindow) override;
            //    virtual bool get_font(::write_text::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
            //  virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pframewindow) override;


      //      virtual bool on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate) override;
      bool _001OnTabLayout(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab) override;

      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::raw::index iItem, ::user::toolbar * ptoolbar) override;
      virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::raw::index iItem, ::user::toolbar * ptoolbar);
      virtual void _001DrawAnthillToolbarItem(::draw2d::graphics_pointer & pgraphics, ::raw::index iItem, ::user::toolbar * ptoolbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

      //      virtual bool get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      //      virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };


} // namespace experience



