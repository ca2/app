#pragma once


namespace user
{


   class CLASS_DECL_AURA style :
      virtual public style_base
   {
   public:


      ::index                                m_iUpdate;
      __pointer(::acme::library)             m_plibrary;
      map < ::user::enum_control_type, __pointer(control_style) > m_controlstyle;
      //__pointer(::user::plain_edit_style)    m_pplaineditstyel;

      ::write_text::font_pointer                 m_pfont;
      ::write_text::font_pointer                 m_pfontMenu;
      ::write_text::font_pointer                 m_pfontButton;
      ::write_text::font_pointer                 m_pfontList;
      ::write_text::font_pointer                 m_pfontTree;
      ::write_text::font_pointer                 m_pfontStill;
      ::write_text::font_pointer                 m_pfontEdit;
      ::write_text::font_pointer                 m_pfontCombo;
      enum_translucency                         m_etranslucency;
      enum_translucency                         m_etranslucencyButton;
      //::color::color                                m_colorBackground;
      //::color::color                                m_colorText;
      //__pointer(color_map)                 m_mapColor;
      //__pointer(font_map)                  m_mapFont;
      //__pointer(translucency_map)          m_mapTranslucency;
      //__pointer(flag_map)                  m_mapFlag;
      //__pointer(rect_map)                  m_mapRect;
      //__pointer(::user::i32_map)           m_mapInt;
      //__pointer(::user::double_map)        m_mapDouble;

      __pointer(::user::style)               m_puserstyle;

      //__pointer(::aura::node)                m_pnode;

      ::draw2d::graphics *                   m_pgraphics;

      ::draw2d::pen_pointer                  m_ppenFocusRect0;
      ::draw2d::pen_pointer                  m_ppenFocusRect1;
      ::draw2d::pen_pointer                  m_ppenFocusRect2;
      ::draw2d::pen_pointer                  m_ppenFocusRect3;
      ::draw2d::pen_pointer                  m_ppenFocusRect4;
      ::draw2d::pen_pointer                  m_ppenFocusRect5;
      ::draw2d::pen_pointer                  m_ppenFocusRect6;
      ::draw2d::pen_pointer                  m_ppenFocusRect7;
      ::draw2d::pen_pointer                  m_ppenFocusRect8;
      ::draw2d::pen_pointer                  m_ppenFocusRect9;



      style();
      //style(::object * pobject);
      virtual ~style();


      //inline auto node() const { return m_pnode; }


      ::e_status initialize(::object * pobject) override;


      void default_style_construct();

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, menu_item * pitem) override;
      //virtual bool prepare_menu(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) override;
      //virtual bool prepare_menu_button(::draw2d::graphics_pointer& pgraphics, ::user::menu_item * pitem) override;

      virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox);

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual ::e_status initialize_style();

      //virtual ::user::plain_edit_internal * get_plain_edit_internal();

      virtual ::color::color get_style_moveable_border_color(enum_style estyle);

      template < typename CONTROL_STYLE >
      void get(__pointer(CONTROL_STYLE) & pcontrolstyleImpl, ::draw2d::graphics_pointer & pgraphics, ::user::interaction * pinteraction);

      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe) override;

      virtual bool draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics) override;



      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool on_ui_event(enum_event eevent, e_object eobject, ::user::interaction * pinteraction) override;

      //virtual bool _001OnDrawMen::u32eraction(::draw2d::graphics_pointer & pgraphics, menu_interaction * pbutton) override;

      //virtual bool _001OnTabLayout(::draw2d::graphics_pointer& pgraphics, ::user::tab * ptab) override;

      //virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics, tab * ptab) override;

      //virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText) override;


      //      virtual bool _001GetMainFrameTranslucency(::user::enum_translucency & etranslucency) override;

      //virtual bool _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, ::user::check_box * pcheckbox) override;

      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar) override;

      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;

      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;


      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the style_base pure function overrides
      // that way, if some styled class overriding any style_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pstylebase compositor
      // to implement the utility functions
      //virtual bool _001GetMainFrameTranslucency(::user::enum_translucency & etranslucency);

      //virtual bool select_text_color(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor = color_text);
      //virtual bool select_solid_brush(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_color ecolor);
      //virtual bool set(::user::interaction * pinteraction, ::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);



      //virtual bool select_text_color(::user::interaction * pinteraction, e_color ecolor = color_text);
      //virtual bool select_solid_brush(::user::interaction * pinteraction, e_color ecolor);
      //virtual bool set(::user::interaction * pinteraction, e_font efont = font_default);


      //virtual ::color::color           _001GetColor(e_color ecolor, ::color::color crDefault = 0);
      //virtual ::write_text::font_pointer  _001GetFont(e_font efont, ::write_text::font * pfont = nullptr);
      //virtual enum_translucency     _001GetTranslucency(enum_element eelement = e_element_none, enum_translucency etranslucencyDefault = e_translucency_undefined);
      //virtual bool               _001GetFlag(::user::enum_flag eflag, bool bDefault = false);
      //virtual ::rectangle_i32             _001GetRect(::user::e_rect erect, ::rectangle_i32 rectangleDefault = nullptr);
      //virtual int                _001GetInt(::user::e_int eint, int iDefault = 0);
      //virtual double             _001GetDouble(::user::e_double edouble, double dDefault = 0.0);


      //virtual bool _001IsBackgroundBypass(enum_element eelement = e_element_none);
      //virtual bool _001IsTransparent(enum_element eelement = e_element_none);
      //virtual bool _001IsTranslucent(enum_element eelement = e_element_none);
      //virtual bool _001HasTranslucency(enum_element eelement = e_element_none);


      virtual ::color::color get_color(const ::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const override;
      virtual bool get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate = ::user::e_state_none) const override;
      virtual bool get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double eint, ::user::enum_state estate = ::user::e_state_none) const override;
      //virtual bool get_font(::write_text::font_pointer & sp, e_font efont, style_context * pcontext) override;
      //virtual bool get_translucency(enum_translucency & etranslucency, enum_element matter, style_context * pcontext) override;
      //virtual bool get_flag(bool & bSet, enum_flag eflag, style_context * pcontext) override;
      //virtual bool get_rect(style_rect & rectangle, e_rect erect, style_context * pcontext) override;
      //virtual bool get_int(int & i, e_int eint, style_context * pcontext) override;
      //virtual bool get_double(double & d, e_double edouble, style_context * pcontext) override;


      virtual void select(::draw2d::graphics_pointer & pgraphics);

      virtual enum_control_type get_control_type() const override;

      virtual ::draw2d::graphics * style_get_graphics();

      virtual style * userstyle();


   };

   
   inline bool control_style::is_up_to_date(::user::style * pstyle) const
   {

      return m_iUpdate == pstyle->m_iUpdate;

   }


} // namespace user




