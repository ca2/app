// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#pragma once


namespace windowing
{


   class CLASS_DECL_AURA simple_ui_display :
      virtual public ::windowing::hook
   {
   public:


      bool m_bOsUserThemeColorModified;
      bool m_bInvalidated;
      string_array_base m_stra;
      string m_strTitle;
      string m_strFontName;

      ::pointer<::windowing::window>m_pwindow;
      ::i32_point m_point;
      ::i32_size m_size;

      ::i32 m_iLineHeight;
      ::i32 m_iTextAscent;

      pointer_array < ::windowing::button > m_buttona;

      ::i32 m_iButtonTop;
      ::i32 m_iButtonHeight;
      ::i32 m_iButtonWidth;

      //XftFont *                        m_pfont;
      //XftDraw *                        m_pdraw;
      //XFontSet                         m_fs;
      //char_pointer *                          m_listMissingCharset;
      //GC                               m_gcText;
      //GC                               m_gcTextHover;
      //GC                               m_gcBar;
//   XftColor                         m_colorButton;
//   XftColor                         m_colorButtonHover;
//   XftColor                         m_colorButtonPress;
//   XftColor                         m_colorBorder;
//   XftColor                         m_colorBorderHover;
//   XftColor                         m_colorBorderPress;
//   XftColor                         m_colorBorderHover1;
//   XftColor                         m_colorBorderHover2;
//   XftColor                         m_colorBorderHover3;

//   Colormap                         m_colormap;
      ::i32 m_iScreen;
//   Visual *                         m_pvisual;
      ::i32 m_iMarginTop;
      ::i32 m_iMarginLeft;
      ::i32 m_iMarginRight;
      ::i32 m_iMarginBottom;
      ::i32 m_iLineSpacing;
      ::i32 m_iButtonHSpacing;
      ::i32 m_iButtonHPadding;
      ::i32 m_iButtonVPadding;
      ::i32 m_iMidSpacing;

//   XftColor                         m_colorBack;
//   XftColor                         m_colorFace;
//   XftColor                         m_colorFore;

//   XftColor                         m_colorFaceHover;
//   XftColor                         m_colorFacePress;

      ::i32 m_iResult;


      simple_ui_display(const ::scoped_string & scopedstrMessage, const ::scoped_string & scopedstrTitle, const ::user::e_message_box &emessagebox);

      ~simple_ui_display();


      virtual ::i64 increment_reference_count();

      virtual ::i64 decrement_reference_count();

      virtual ::i64 release();


      button * new_button(const ::scoped_string & scopedstrLabel, enum_dialog_result edialogresult);


      void common_construct();

      //GC create_gc();

      virtual void invalidate();

      virtual void on_idle(display *pdisplay) override;

      void on_expose(display *pdisplay);

      void call_expose(display *pdisplay);

      virtual void on_subject(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_layout(display *pdisplay);

      void on_colors(display *pdisplay);

      void on_alloc_colors(display *pdisplay);

      void on_free_colors(display *pdisplay);

      virtual bool process_event(display *pdisplay, happening * phappening) override;

      ::i32 show();

      void on_show();

      bool on_click(::i32 iResult);

      virtual void close_window();


   };


} // namespace windowing



