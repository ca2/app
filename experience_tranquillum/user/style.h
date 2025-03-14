#pragma once


#include "base/user/user/style.h"


namespace experience_tranquillum
{



   class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM style :
   virtual public ::base::style
   {
   public:


      //::write_text::font_pointer                 m_pfont;
      //::write_text::font_pointer                m_pfontList;


      style();
      ~style() override;

      //virtual long long increment_reference_count() override
      //{

      //   return ::object::increment_reference_count();

      //}

      //virtual long long decrement_reference_count() override
      //{

      //   return ::object::decrement_reference_count();

      //}


      ::color::color get_color(::user::interaction * pinteraction, ::enum_element eelement, ::user::enum_state estate) override;
      
      
         //    virtual bool get_font(::write_text::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
         //  virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pframewindow) override;


         //      virtual bool on_ui_event(::enum_topic etopic, ::user::e_object eobject, ::user::interaction * pframewindow) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::int_rectangle & rectangle,::draw2d::brush_pointer & pbrushText, const ::user::e_state & estate) override;

      bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab) override;

      bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::interaction * pinteraction) override;
      //virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar) override;
      //virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar);
      //virtual void _001DrawTranquillumToolbarItem(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::user::toolbar * ptoolbar);
      bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

      //virtual bool get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      //virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };



} // namespace experience_tranquillum



