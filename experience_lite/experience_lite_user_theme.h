#pragma once


namespace lite

{


   class CLASS_DECL_APP_EXPERIENCE_LITE theme:
      virtual public ::user::theme
   {
   public:




      theme(::object * pobject);
      virtual ~theme();

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {

         return ::object::add_ref(OBJ_REF_DBG_ARGS);

      }

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {

         return ::object::dec_ref(OBJ_REF_DBG_ARGS);

      }


//      virtual bool get_color(color32_t & color32, ::user::e_color ecolor, ::user::interaction * pframewindow) override;
      //    virtual bool get_font(::write_text::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
      //  virtual bool get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::interaction * pframewindow) override;


      virtual bool on_ui_event(::user::e_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const RECTANGLE_I32 * lpcrect,::draw2d::brush_pointer & brushText) override;
      bool _001OnTabLayout(::user::tab * ptab) override;

      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar) override;
      virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar);
      virtual void _001DrawLiteToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

      virtual bool get_font(::write_text::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };


} // namespace lite




