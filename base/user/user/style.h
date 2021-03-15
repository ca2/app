#pragma once


namespace base
{


   class CLASS_DECL_BASE style :
      virtual public ::axis::style
   {
   public:


      __pointer(::apex::library)     m_plibrary;


      style();
      virtual ~style();


      inline ::base::application* get_application() const { return m_papplication ? m_papplication.cast < ::base::application >() : nullptr; }
      inline ::base::session* get_session() const { return m_psession ? m_psession.cast < ::base::session >() : nullptr; }
      inline ::base::system* get_system() const { return ::is_set(m_psystem) ? dynamic_cast <::base::system*> (m_psystem) : nullptr; }
      inline ::base::user* user() const { return get_session() ? get_session()->user() : nullptr; }


      inline auto node() const { return get_system()->node(); }


      virtual void construct_fallback_theme();

      virtual void initialize_theme();

      //virtual void nextstyle(style_context * pcontext) override;

      virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer& pstyle, ::user::menu_item* pitem);
      virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem);
      virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem);


      //virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics, ::user::frame * pframe) override;
      //virtual void DrawCheck(enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics) override;
      //virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics) override;
      //virtual bool on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction) override;
      virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, ::user::tab * ptab);
      virtual bool _001OnDrawMenuInteraction(::draw2d::graphics_pointer & pgraphics, ::user::menu_interaction * pbutton);
      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & brushText);

      virtual bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab);
      //virtual void _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectClient, ::enum_check echeck) override;

      //virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar) override;
      //virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, simple_scroll_bar * pbar) override;
      //virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;


      //virtual bool select_text_color(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
      //virtual bool select_solid_brush(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor);
      //virtual bool set(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);



      //virtual bool select_text_color(::user::interaction * pinteraction, e_color ecolor = color_text);
      //virtual bool select_solid_brush(::user::interaction * pinteraction, e_color ecolor);
      //virtual bool set(::user::interaction * pinteraction, e_font efont = font_default);



      //virtual color32_t           _001GetColor(::user::interaction * pinteraction, e_color ecolor, color32_t crDefault = 0);
      //virtual ::write_text::font_pointer  _001GetFont(::user::interaction * pinteraction, e_font efont, ::write_text::font * pfont = nullptr);
      //virtual enum_translucency     _001GetTranslucency(::user::interaction * pinteraction, enum_element eelement = e_element_none, enum_translucency etranslucencyDefault = e_translucency_undefined);
      //virtual bool               _001GetFlag(::user::interaction * pinteraction, ::user::enum_flag eflag, bool bDefault = false);
      //virtual const rectangle_i32 &               _001GetRect(::user::interaction * pinteraction, ::user::e_rect erect, ::rectangle_i32 rectDefault = nullptr);
      //virtual int                _001GetInt(::user::interaction * pinteraction, ::user::e_int eint, int iDefault = 0);
      //virtual double             _001GetDouble(::user::interaction * pinteraction, ::user::e_double edouble, double dDefault = 0.0);

      //virtual bool _001IsBackgroundBypass(::user::interaction * pinteraction, enum_element eelement = e_element_none);
      //virtual bool _001IsTransparent(::user::interaction * pinteraction, enum_element eelement = e_element_none);
      //virtual bool _001IsTranslucent(::user::interaction * pinteraction, enum_element eelement = e_element_none);
      //virtual bool _001HasTranslucency(::user::interaction * pinteraction, enum_element eelement = e_element_none);






      //virtual ::user::style * userstyle();



      //virtual void on_select_user_style();
      //virtual ::user::style * parent_userstyle();
      //virtual style * style_get(e_schema eschema) = 0;


      //virtual ::draw2d::graphics * style_get_graphics();


      //virtual bool userstyle_color(color32_t & cr, e_color ecolor, ::user::interaction * pinteraction);
      //virtual bool userstyle_font(::write_text::font_pointer & sp, e_font efont, ::user::interaction * pinteraction);
      //virtual bool userstyle_translucency(enum_translucency & etranslucency, enum_element eelement, ::user::interaction * pinteraction);
      //virtual bool userstyle_flag(bool & bSet, ::user::enum_flag eflag, ::user::interaction * pinteraction);
      //virtual bool userstyle_rect(const rectangle_i32 & & rectangle, ::user::e_rect erect, ::user::interaction * pinteraction);
      //virtual bool userstyle_int(int & i, ::user::e_int eint, ::user::interaction * pinteraction);
      //virtual bool userstyle_double(double & d, ::user::e_double edouble, ::user::interaction * pinteraction);


      //virtual bool style_color(color32_t & cr, e_color ecolor, ::user::interaction * pinteraction);
      //virtual bool style_font(::write_text::font_pointer & sp, e_font efont, ::user::interaction * pinteraction);
      //virtual bool style_translucency(enum_translucency & etranslucency, enum_element eelement, ::user::interaction * pinteraction);
      //virtual bool style_flag(bool & bSet, ::user::enum_flag eflag, ::user::interaction * pinteraction);
      //virtual bool style_rect(const rectangle_i32 & & rectangle, ::user::e_rect erect, ::user::interaction * pinteraction);
      //virtual bool style_int(int & i, ::user::e_int eint, ::user::interaction * pinteraction);
      //virtual bool style_double(double & d, ::user::e_double edouble, ::user::interaction * pinteraction);

//      virtual void theme_current_control(e_control econtrol);

   };


} // namespace base




