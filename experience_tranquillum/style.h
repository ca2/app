#pragma once


namespace experience
{


   namespace tranquillum
   {


      class CLASS_DECL_APP_EXPERIENCE_TRANQUILLUM style :
      virtual public ::base::style
      {
      public:


         //::draw2d::font_pointer                 m_font;
         //::draw2d::font_pointer                m_fontList;


         style();
         virtual ~style();

         //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
         //{

         //   return ::object::add_ref(OBJ_REF_DBG_ARGS);

         //}

         //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
         //{

         //   return ::object::dec_ref(OBJ_REF_DBG_ARGS);

         //}


         virtual ::color get_color(const ::user::interaction * pinteraction, ::user::e_element eelement, ::user::estate estate) const override;
      
      
         //    virtual bool get_font(::draw2d::font_pointer & font, ::user::e_font efont, ::user::interaction * pframewindow) override;
         //  virtual bool get_translucency(::user::e_translucency & etranslucency, ::user::e_element eelement, ::user::interaction * pframewindow) override;


         //      virtual bool on_ui_event(::user::enum_event eevent, ::user::e_object eobject, ::user::interaction * pframewindow) override;

      bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,::user::tab * ptab) override;
      void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,const ::rect & rect,::draw2d::brush_pointer & brushText) override;

      virtual bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab) override;

      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame * pframe) override;
      //virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar) override;
      //virtual void _001DrawSimpleToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
      //virtual void _001DrawTranquillumToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar);
      virtual bool _001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout) override;

      //virtual bool get_font(::draw2d::font_pointer & sp, ::user::e_font efont, ::user::style_context * pcontext) override;
      //virtual bool get_double(double & d, ::user::e_double edouble, ::user::style_context * pcontext) override;


   };



} // namespace tranquillum


   } // namespace experience



