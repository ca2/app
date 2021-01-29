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
      string_array m_stra;
      string m_strTitle;
      string m_strFontName;

      __pointer(::windowing::window) m_pwindow;
      ::point m_point;
      ::size m_size;

      int m_iLineHeight;
      int m_iTextAscent;

      __pointer_array(::windowing::button) m_buttona;

      int m_iButtonTop;
      int m_iButtonHeight;
      int m_iButtonWidth;

      //XftFont *                        m_pfont;
      //XftDraw *                        m_pdraw;
      //XFontSet                         m_fs;
      //char **                          m_listMissingCharset;
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
      int m_iScreen;
//   Visual *                         m_pvisual;
      int m_iMarginTop;
      int m_iMarginLeft;
      int m_iMarginRight;
      int m_iMarginBottom;
      int m_iLineSpacing;
      int m_iButtonHSpacing;
      int m_iButtonHPadding;
      int m_iButtonVPadding;
      int m_iMidSpacing;

//   XftColor                         m_colorBack;
//   XftColor                         m_colorFace;
//   XftColor                         m_colorFore;

//   XftColor                         m_colorFaceHover;
//   XftColor                         m_colorFacePress;

      int m_iResult;


      simple_ui_display(const string &strMessage, const string &strTitle, const ::e_message_box &emessagebox);

      ~simple_ui_display();


      virtual i64 add_ref(OBJ_REF_DBG_PARAMS);

      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS);

      virtual i64 release(OBJ_REF_DBG_PARAMS);


      button * new_button(const char * pszLabel, enum_dialog_result edialogresult);


      void common_construct();

      //GC create_gc();

      virtual void invalidate();

      virtual void on_idle(display *pdisplay) override;

      void on_expose(display *pdisplay);

      void call_expose(display *pdisplay);

      virtual void on_subject(::promise::subject *psubject, ::promise::context *pcontext) override;

      void on_layout(display *pdisplay);

      void on_colors(display *pdisplay);

      void on_alloc_colors(display *pdisplay);

      void on_free_colors(display *pdisplay);

      virtual bool process_event(display *pdisplay, event * pevent) override;

      int show();

      void on_show();

      bool on_click(int iResult);

      virtual void close_window();


   };


} // namespace windowing



