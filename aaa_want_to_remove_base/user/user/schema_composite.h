#pragma once


namespace user
{


   class CLASS_DECL_BASE schema_composite :
      virtual public schema_base
   {
   public:
      
      
      using schema_map = ::map < e_schema, e_schema, style_pointer >;
      
      schema_map               m_map;
      
      ::aura::library *       m_plibrary;
      
      ::user::style_pointer        m_puserschema;
      
      schema_composite();
      virtual ~schema_composite();
      

      // these are schema_base pure virtual functions
      // "implementation"
      // these are schema_base pure virtual functions
      // composition
      // these function should be always be a composition
      // based on userschema()
      virtual void initialize_schema_menu() override;
      virtual void initialize_schema_button() override;
      virtual void initialize_schema_menu_button() override;
      virtual void initialize_schema_menu_popup() override;
      virtual void initialize_schema_system_menu_button() override;
      virtual void initialize_schema_system_menu_close() override;
      virtual void initialize_schema_system_menu_popup() override;
      virtual void initialize_schema() override;
      virtual ::user::interaction * create_menu_button() override;
      virtual bool prepare_menu(::user::menu_item * pitem) override;
      virtual bool prepare_menu_button(::user::menu_item * pitem) override;
      
      
      virtual bool _001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame_window * pframe) override;
      virtual void DrawCheck(enum_check echeck, const ::rect & rect, ::draw2d::graphics_pointer & pgraphics) override;
      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics) override;
      virtual bool on_ui_event(e_event eevent, e_object eobject, ::user::interaction * pinteraction) override;
      virtual bool _001TabOnDrawSchema01(::draw2d::graphics_pointer & pgraphics,tab * ptab) override;
      virtual void _001OnTabPaneDrawTitle(::user::tab_pane & pane,::user::tab * ptab,::draw2d::graphics_pointer & pgraphics,LPCRECT lpcrect,::draw2d::brush_pointer & brushText) override;
      virtual bool _001OnTabLayout(::user::tab * ptab) override;
      virtual void _001DrawCheckBox(::draw2d::graphics_pointer & pgraphics, LPCRECT lpcrectClient, ::enum_check echeck) override;
      virtual bool _001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, i32 iItem, ::user::toolbar * ptoolbar) override;
      virtual bool _001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, simple_scroll_bar * pbar) override;
      virtual bool _001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar) override;
      
      virtual bool get_color(COLORREF & cr,e_color ecolor, ::user::interaction * pinteraction) override;
      virtual bool get_font(::draw2d::font_pointer & sp, e_font efont, ::user::interaction * pinteraction) override;
      virtual bool get_translucency(e_translucency & etranslucency, e_element eelement, ::user::interaction * pinteraction) override;
      virtual bool has_flag(::user::e_flag eflag) override;
      virtual rect get_rect(::user::e_rect erect) override;
      virtual int get_int(::user::e_int eint) override;
      
      //virtual e_schema get_schema() override;
      
      
      // these are exception of rule above
//      virtual __pointer(style) & operator[](e_schema eschema) override;
     
      
//      virtual bool impl_get_color(COLORREF & cr, e_color eusercolor) = 0;
//      virtual bool impl_get_font(::draw2d::font_pointer & sp, e_font efont) = 0;
//      virtual bool impl_get_translucency(e_translucency & etranslucency, e_element element) = 0;
//      virtual bool impl_has_flag(e_flag eflag) = 0;
//      virtual rect impl_get_rect(e_rect erect) = 0;
//      virtual int impl_get_int(e_int eint) = 0;

      
      
      // these are utility functions
      // the utility functions should be based on this class functions
      // specially the schema_base pure function overrides
      // that way, if some schemad class overriding any schema_base pure function
      // will affect the return of the utility function.
      // so, it should be very avoided using the m_pschemabase compositor
      // to implement the utility functions
      //virtual bool _001GetMainFrameTranslucency(::user::e_translucency & etranslucency);

      virtual bool select_text_color(::draw2d::graphics_pointer & pgraphics,e_color ecolor = color_text);
      virtual bool select_solid_brush(::draw2d::graphics_pointer & pgraphics,e_color ecolor);
      virtual bool select_font(::draw2d::graphics_pointer & pgraphics, e_font efont = font_default);

      
      
      virtual bool select_text_color(e_color ecolor = color_text);
      virtual bool select_solid_brush(e_color ecolor);
      virtual bool select_font(e_font efont = font_default);

      
      
      virtual COLORREF        _001GetColor(e_color ecolor, COLORREF crDefault);
      virtual COLORREF        _001GetColor(e_color ecolor);
      virtual e_translucency   _001GetTranslucency(e_element eelement = element_none, e_translucency etranslucencyDefault = translucency_undefined);
      
      virtual bool _001IsBackgroundBypass(e_element eelement = element_none);
      virtual bool _001IsTransparent(e_element eelement = element_none);
      virtual bool _001IsTranslucent(e_element eelement = element_none);
      virtual bool _001HasTranslucency(e_element eelement = element_none);
      

      
      
      

      // special utility functions
      // they are very suitable for schema containers that contains that schema
      // by deriving from this schema class
      inline ::user::style * userschema()
      {
         
         return m_puserschema;
         
      }
      

      
      /// schema selection generally done at initialization
      virtual void on_select_userschema();
      virtual ::user::style_base * parent_userschema();
      virtual schema * schema_get(e_schema eschema) = 0;

      
      virtual ::draw2d::graphics * schema_get_graphics();
      
      
      // e_schema composition
      virtual bool schema_color(COLORREF & cr,e_color ecolor);
      virtual bool schema_font(::draw2d::font_pointer & sp, e_font efont);
      virtual bool schema_translucency(e_translucency & etranslucency, e_element eelement);
      virtual bool schema_flag(::user::e_flag eflag);
      virtual rect schema_rect(::user::e_rect erect);
      virtual int schema_int(::user::e_int eint);
      
      
      
   };
   

} // namespace user




