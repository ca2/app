#pragma once


#undef new


#include <gdiplus.h>

#define MAX_LOADSTRING 100

#define new ACME_NEW

#include "windows_window_gdi.h"


namespace os
{


   class CLASS_DECL_AURA simple_ui :
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
      window_gdi                 m_gdi;


      oswindow                   m_window;
      bool                       m_bShiftKey;
      ::rect                     m_rectDesktop;

      bool                       m_bNoDecorations;




      simple_ui(::layered * pobjectContext);

      virtual ~simple_ui();

      static LRESULT CALLBACK s_window_prodecure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


      virtual bool create_window(LPCRECT lprect);

      virtual ATOM register_window_class(HINSTANCE hInstance);

      virtual bool prepare_window(LPCRECT lprect);

      virtual bool show_window(bool bShow = true);

      virtual bool destroy_window();

      virtual void _001ClientToScreen(POINT * ppt);

      virtual void _001ScreenToClient(POINT * ppt);

      virtual LRESULT message_handler(UINT message, WPARAM wParam, LPARAM lParam);

      virtual void get_window_rect(RECT * prect);
      virtual void get_client_rect(RECT * prect);



      virtual bool on_windows_key_down(WPARAM wparam, LPARAM lparam);
      virtual bool on_windows_key_up(WPARAM wparam, LPARAM lparam);

      virtual void on_windows_gdi_draw_framebuffer();

      virtual bool on_windows_move(i32 x, i32 y);
      virtual bool on_windows_size(i32 cx, i32 cy);

      virtual void set_capture();
      virtual void release_capture();


      virtual bool run_loop();

      bool move_window(i32 x, i32 y);
      bool set_window_pos(i32 x, i32 y, i32 cx, i32 cy, bool bShow);



   };




} // namespace os





CLASS_DECL_AURA LRESULT layered_window_nc_calc_size(WPARAM wparam, LPARAM lparam);
