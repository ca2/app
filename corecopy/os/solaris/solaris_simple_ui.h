#pragma once


#include "aura/os/solaris/solaris_window_xlib.h"


namespace os
{


   class CLASS_DECL_CORE simple_ui :
      virtual public ::user::interaction
   {
   public:

      HINSTANCE                  m_hinstance;
      string                     m_strTitle;
      string                     m_strWindowClass;

      int                        m_w;
      int                        m_h;
/*      ::image_pointer           m_pimage;
      SIZE                       m_size;
      POINT                      m_point;
      window_xlib                m_xlib;


      oswindow                   m_window;
      bool                       m_bShiftKey;
      ::rect                     m_rectDesktop;

      XWindowAttributes          m_attr;
      i32                    m_iDepth;
      XVisualInfo                m_visualinfo;
      int                        m_iScreen;


      window_graphics *          m_pgraphics;


      bool                       m_bComposite;

      ::mutex *                    m_pmutexGraphics;
      ::mutex *                    m_pmutexDisplay;

      bool                       m_bRunLoop;

      ::rect                     m_rectWindow;

      bool                       m_bNoDecorations;


      simple_ui(__pointer(base_application) papp);

      virtual ~simple_ui();

      virtual bool create_window(LPCRECT lprect);

      virtual bool prepare_window(LPCRECT lprect);


      using ::user::interaction::_001ClientToScreen;
      virtual void _001ClientToScreen(POINT * ppt);

      using ::user::interaction::_001ScreenToClient;
      virtual void _001ScreenToClient(POINT * ppt);

      virtual void get_window_rect(RECT * prect);
      virtual void get_client_rect(RECT * prect);


      virtual bool show_window(bool bShow = true);

      virtual bool destroy_window();


      virtual bool on_key_down(u32 uiKey);
      virtual bool on_key_up(u32 uiKey);


      virtual bool on_move(i32 x, i32 y);
      virtual bool on_size(i32 cx, i32 cy);


      virtual void run_loop();


      virtual void on_draw_framebuffer();

      virtual void set_capture();
      virtual void release_capture();

      virtual bool move_window(i32 x, i32 y);
      virtual bool set_window_pos(i32 x, i32 y, i32 cx, i32 cy, bool bShow);

   };




} // namespace os



CLASS_DECL_CORE void wm_nodecorations(oswindow w, int map);



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
