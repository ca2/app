#pragma once




class simple_ui_display :
   virtual public ::x11_hook
{
public:


   bool                             m_bDarkModeModified;
   bool                             m_bInvalidated;
   string_array                     m_stra;
   string                           m_strTitle;
   string                           m_strFontName;

   Window                           m_window;
   ::point                          m_point;
   ::size                           m_size;

   __pointer_array(x11_button)      m_buttona;

   int                              m_iButtonTop;
   int                              m_iButtonHeight;
   int                              m_iMargin;

   XftFont *                        m_pfont;
   XftDraw *                        m_pdraw;
   //XFontSet                         m_fs;
   char **                          m_listMissingCharset;
   GC                               m_gcText;
   GC                               m_gcTextHover;
   //GC                               m_gcBar;
   XftColor                         m_colorButton;
   XftColor                         m_colorButtonHover;
   XftColor                         m_colorButtonPress;
   XftColor                         m_colorBorder;
   XftColor                         m_colorBorderHover;
   XftColor                         m_colorBorderPress;
   XftColor                         m_colorBorderHover1;
   XftColor                         m_colorBorderHover2;
   XftColor                         m_colorBorderHover3;

   Colormap                         m_colormap;
   int                              m_iScreen;
   Visual *                         m_pvisual;
   int                              m_iMarginTop;
   int                              m_iMarginLine;

   XftColor                         m_colorBack;
   XftColor                         m_colorFace;
   XftColor                         m_colorFore;

   XftColor                         m_colorFaceHover;
   XftColor                         m_colorFacePress;

   ::future                         m_future;


   simple_ui_display(const string & strMessage, const string & strTitle, ::emessagebox emessagebox, ::future future);

   ~simple_ui_display();

   void common_construct();

   GC create_gc();

   virtual void invalidate();

   virtual void on_idle(Display * pdisplay) override;

   void on_expose(Display * pdisplay);

   void call_expose(Display * pdisplay);

   virtual void update(::update * pupdate) override;

   void on_layout(Display * pdisplay);

   void on_colors(Display * pdisplay);

   void on_alloc_colors(Display * pdisplay);

   void on_free_colors(Display * pdisplay);

   virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie) override;

   ::estatus show();

   void on_show();

   bool on_click(const char * pszResult);

};


