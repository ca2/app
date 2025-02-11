#pragma once


namespace lite

{


   class CLASS_DECL_APP_EXPERIENCE_LITE theme:
      virtual public ::user::theme
   {
   public:




      theme(::particle * pparticle);
      virtual ~theme();

      virtual long long increment_reference_count() override
      {

         return ::object::increment_reference_count();

      }

      virtual long long decrement_reference_count() override
      {

         return ::object::decrement_reference_count();

      }


//      virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::interaction * pframewindow) override;
      //    virtual bool get_font(::write_text::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
      //  virtual bool get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pframewindow) override;


      virtual bool on_ui_event(::user::e_happening ehappening, ::user::e_object eobject, ::user::interaction * pframewindow) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::int_rectangle * lpcrect,::draw2d::brush_pointer & pbrushText) override;
      bool _001OnTabLayout(::user::tab * ptab) override;

      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar) override;
      virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar);
      virtual void _001DrawLiteToolbarItem(::draw2d::graphics_pointer & pgraphics, int iItem, ::user::toolbar * ptoolbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

      virtual bool get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };


} // namespace lite




