#pragma once


#include "acme/operating_system/solaris/solaris_window_xlib.h"


namespace os
{


   class CLASS_DECL_ACME simple_ui :
      virtual public ::user::interaction
   {
   public:

      HINSTANCE                  m_hinstance;
      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
/*      ::image::image_pointer           m_pimage;
      ::int_size                       m_size;
      ::int_point                      m_point;
      window_xlib                m_xlib;


      oswindow                   m_window;
      bool                       m_bShiftKey;
      ::int_rectangle                     m_rectangleDesktop;

      XWindowAttributes          m_attr;
      int                    m_iDepth;
      XVisualInfo                m_visualinfo;
      int                        m_iScreen;


      window_graphics *          m_pgraphics;


      bool                       m_bComposite;

      ::pointer< ::mutex >                    m_pmutexGraphics;
      ::pointer< ::mutex >                    m_pmutexDisplay;

      bool                       m_bRunLoop;

      ::int_rectangle                     m_rectangleWindow;

      bool                       m_bNoDecorations;


      simple_ui(::pointer<base_application>papp);

      virtual ~simple_ui();

      virtual bool create_window(const ::int_rectangle * lprect);

      virtual bool prepare_window(const ::int_rectangle * lprect);


      using ::user::interaction::client_to_screen;
      virtual void client_to_screen(::int_point * ppt);

      using ::user::interaction::screen_to_client;
      virtual void screen_to_client(::int_point * ppt);

      virtual void window_rectangle(::int_rectangle * prectangle);
      virtual void this->rectangle(::int_rectangle * prectangle);


      virtual bool show_window(bool bShow = true);

      virtual bool destroy_window();


      virtual bool on_key_down(unsigned int uiKey);
      virtual bool on_key_up(unsigned int uiKey);


      virtual bool on_move(int x, int y);
      virtual bool on_size(int cx, int cy);


      virtual void run_loop();


      virtual void on_draw_framebuffer();

      virtual void set_mouse_capture();
      virtual void release_mouse_capture();

      virtual bool move_window(int x, int y);
      virtual bool set_window_position(int x, int y, int cx, int cy, bool bShow);

   };




} // namespace os



CLASS_DECL_ACME void wm_nodecorations(oswindow w, int map_base);



/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)

/* KDE decoration values */
enum
{
   KDE_noDecoration = 0,
   KDE_normalDecoration = 1,
   KDE_tinyDecoration = 2,
   KDE_noFocus = 256,
   KDE_standaloneMenuBar = 512,
   KDE_desktopIcon = 1024,
   KDE_staysOnTop = 2048
};
