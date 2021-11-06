#include "framework.h"

//!!!#include <X11/Xatom.h>

/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)

namespace os
{

   map < oswindow, oswindow, simple_ui *, simple_ui * > m_windowmap;

   simple_ui::simple_ui(__pointer(base_application) papp) :
      ::object(pobject),
      interaction(pobject)
   {

      m_w = 840;
      m_h = 284;
      m_window = nullptr;
      m_bShiftKey = false;

      m_bNoDecorations = false;

      __zero(m_size);
      __zero(m_point);


   }

   simple_ui::~simple_ui()
   {

      ::DestroyWindow(m_window);

   }


   bool simple_ui::create_window(const RECTANGLE_I32 * lpcrect)
   {

      single_lock ml(&user_mutex());

      Display *display;

      Window rootwin;

      XEvent e;

      if(!(display = XOpenDisplay(nullptr)))
      {

         fprintf(stderr, "ERROR: Could not open display\n");

         return false;

      }

      xdisplay d(display);

      m_iScreen            =  DefaultScreen(display);

      rootwin              =  RootWindow(display, m_iScreen);

      const char * xserver = getenv( "DISPLAY" ) ;

      if (display == 0)
      {

         printf("Could not establish a connection to X-server '%s'\n", xserver ) ;

         return false;

      }

      // query Visual for "TrueColor" and 32 bits depth (RGBA)
      Visual * vis = DefaultVisual(display, m_iScreen);

      m_iDepth = 0;

      {

         if(XMatchVisualInfo(display, m_iScreen, 32, TrueColor, &m_visualinfo))
         {

            vis = m_visualinfo.draw2d;

         }
         else
         {

            __memset(&m_visualinfo, 0, sizeof(m_visualinfo));

         }

      }

      m_iDepth = m_visualinfo.depth;

      XSetWindowAttributes attr;

      __zero(attr);

      attr.colormap = XCreateColormap( display, rootwin, vis, AllocNone);

      attr.event_mask = ExposureMask | ButtonPressMask | ButtonReleaseMask | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask;

      attr.background_pixmap = None ;

      attr.border_pixmap = None;

      attr.border_pixel = 0 ;

      attr.override_redirect = True;

      Window window = XCreateWindow(
                      display,
                      DefaultRootWindow(display),
                      lpcrect->left,
                      lpcrect->top,
                      width(lpcrect),
                      height(lpcrect),
                      0,
                      m_iDepth,
                      InputOutput,
                      vis,
                      CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel,
                      &attr);



      if (window == 0)
      {

         return false;

      }

      m_point.x = lpcrect.left;
      m_point.y = lpcrect.top;
      m_size.cx = width(lpcrect);
      m_size.cy = height(lpcrect);

      m_rectangleWindow = *lpcrect;
      m_rectangleWindow.deflate(1, 1); // make intentionally different from actual rectangle_i32 to trigger simple_ui on_move and on_size events

      m_window = oswindow_get(display, window, vis, m_iDepth, m_iScreen, attr.colormap);

      return true;

   }


   bool simple_ui::show_window(bool bShow)
   {

      if(!::user::interaction::show_window(bShow))
         return false;

      if(bShow)
      {

         set_window_position(m_window, nullptr, m_point.x, m_point.y, m_size.cx, m_size.cy, SWP_SHOWWINDOW | SWP_NOZORDER);

      }
      else
      {

         ShowWindow(m_window, SW_HIDE);

      }

      return true;

   }



   bool simple_ui::prepare_window(const RECTANGLE_I32 * lpcrect)
   {

      single_lock ml(&user_mutex());

      XGetWindowAttributes(m_window->display(), m_window->window(), &m_attr);

      m_pgraphics = new window_xlib();

      m_bComposite = XGetSelectionOwner(m_window->display(), XInternAtom(m_window->display(), "_NET_WM_CM_S0", True));

      if(m_strText.get_length() > 0)
      {
         XStoreName(m_window->display(), m_window->window(), m_strText);
      }

      m_pmutexGraphics = new ::mutex();

      //on_size(width(lpcrect), height(lpcrect));

      //on_move(lpcrect->left, lpcrect->top);

      xdisplay d(m_window->display());

      XGetWindowAttributes(m_window->display(), m_window->window(), &m_attr);

      m_pgraphics = new window_xlib();

      if(m_bNoDecorations)
      {

         wm_nodecorations(m_window, 0);

      }

      //bool bShow = true;

//      XMoveResizeWindow(m_window->display(), m_window->window(), m_rectangleDesktop.right-m_point.x, m_rectangleDesktop.bottom-m_point.y, m_size.cx, m_size.cy);

      //XMoveResizeWindow(m_window->display(), m_window->window(), 500, 0, 200, 200);


      //if(bShow)
      //{

      // XMapWindow(m_window->display(), m_window->window());

      //}

      d.unlock();

      ml.unlock();

      m_bVisible = true;

      return true;

   }


#define MAX_MAPPED_STRING_LENGTH 500

   void simple_ui::run_loop()
   {

      m_bRunLoop = true;

      XEvent e;

      char buffer[MAX_MAPPED_STRING_LENGTH];
      int bufsize=MAX_MAPPED_STRING_LENGTH;
      KeySym keysym;
      XComposeStatus compose;

      single_lock synchronouslock(&user_mutex(), false);

      xdisplay x(m_window->display(), false);

      bool bEnableFB = false;

      while(m_bRunLoop)
      {

         {

            synchronouslock.lock();

            x.lock();

            if(XPending(m_window->display()) > 0)
            {

               if(XNextEvent(m_window->display(), &e) == Success)
               {

                  x.unlock();

                  synchronouslock.unlock();

                  if(e.xany.window == m_window->window())
                  {

                     if(e.type==Expose && e.xexpose.count < 1)
                     {

                        bEnableFB = true;

                        //   on_draw_framebuffer();
                     }
                     else if(e.type == ButtonPress || e.type == ButtonRelease)
                     {

                        //                     bRet                 = true;
                        //                     if(bRet)
                        {

                           //                lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                           //                  lpMsg->wParam        = 0;
                           //              lpMsg->lParam        = __MAKE_LONG(e.xbutton.x_root, e.xbutton.y_root);

                        }

                        if(e.xbutton.type == ButtonPress)
                        {
                           if(e.xbutton.button == Button1)
                           {
                              on_lbutton_down(e.xbutton.x, e.xbutton.y);
                           }
                           else if(e.xbutton.button == Button2)
                           {
                              //         lpMsg->message = e_message_middle_button_down;
                           }
                           else if(e.xbutton.button == Button3)
                           {
                              //       lpMsg->message = e_message_right_button_down;
                           }
                           else
                           {
                              //     bRet = false;
                           }

                        }
                        else if(e.xbutton.type == ButtonRelease)
                        {
                           if(e.xbutton.button == Button1)
                           {
                              on_lbutton_up(e.xbutton.x, e.xbutton.y);
                           }
                           else if(e.xbutton.button == Button2)
                           {
                              //lpMsg->message = e_message_middle_button_up;
                           }
                           else if(e.xbutton.button == Button3)
                           {
                              //lpMsg->message = e_message_right_button_up;
                           }
                           else
                           {
                              //bRet = false;
                           }

                        }
                        else
                        {

                           //bRet = false;

                        }



                     }
                     else if(e.type == KeyPress || e.type == KeyRelease)
                     {

                        //oswindow w = oswindow_get(display, e.xexpose.window);

                        //                     bRet                 = true;

                        if(e.xkey.type == KeyPress)
                        {

                           int count = XLookupString(&e.xkey, buffer, bufsize, &keysym, &compose);
                           if(keysym == XK_Tab)
                           {
                              //on_key_down(VK_TAB);
                              on_char(::user::e_key_tab, "");

                           }
                           else if(keysym == XK_Return)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::e_key_return, "");
                           }
                           else if(keysym == XK_BackSpace)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::e_key_back, "");
                           }
                           else if(keysym == XK_Delete)
                           {
                              //on_key_down(VK_RETURN);
                              on_char(::user::e_key_delete, "");
                           }
                           else if(keysym == XK_Shift_L || keysym == XK_Shift_R)
                           {
                              on_key_down(::user::e_key_shift);
                           }
                           else
                           {
                              if(strlen(buffer) > 0)
                              {
                                 on_char(0, buffer);
                                 buffer[0] = '\0';
                              }
                           }
                           // lpMsg->message = e_message_key_down;

                        }
                        else if(e.xkey.type == KeyRelease)
                        {

                           //lpMsg->message = e_message_key_up;
                           if(keysym == XK_Tab)
                           {
                              //on_key_up(VK_TAB);

                           }
                           else if(keysym == XK_Return)
                           {
                              //on_key_up(VK_RETURN);
                           }
                           else if(keysym == XK_Shift_L || keysym == XK_Shift_R)
                           {
                              on_key_up(::user::e_key_shift);
                           }

                        }
                        else
                        {

                           //                        bRet = false;

                        }

                        //lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                        //lpMsg->wParam        = e.xkey.keycode;
                        //lpMsg->lParam        = __MAKE_LONG(0, e.xkey.keycode);



                     }
                     else if(e.type == MotionNotify)
                     {

                        //lpMsg->hwnd          = oswindow_get(display, e.xbutton.window);
                        //lpMsg->message       = e_message_mouse_move;
                        //lpMsg->wParam        = 0;
                        //lpMsg->lParam        = __MAKE_LONG(e.xmotion.x_root, e.xmotion.y_root);

                        on_mouse_move(e.xmotion.x, e.xmotion.y);

                        //bRet                 = true;

                     }
                     else if(e.type == DestroyNotify)
                     {

                        //lpMsg->hwnd          = oswindow_get(display, e.xdestroywindow.window);
                        //lpMsg->message       = e_message_destroy;

                        m_bRunLoop = false;

                        //bRet                 = true;

                     }

                     //if(bPeek && bRet)
                     // XPutBackEvent(display, &e);



                  }


               }

            }
            else
            {

               x.unlock();

               synchronouslock.unlock();

               if(bEnableFB && m_bVisible)
               {

                  on_draw_framebuffer();

               }

               sleep(5_ms);

            }

         }

      }

   }


   void simple_ui::client_to_screen(POINT_I32 * ppt)
   {
      //::client_to_screen(m_window, ppt);
      ::user::interaction::client_to_screen(ppt);
   }

   void simple_ui::screen_to_client(POINT_I32 * ppt)
   {
      //::screen_to_client(m_window, ppt);
      ::user::interaction::screen_to_client(ppt);
   }

   bool simple_ui::on_key_down(u32 uiKey)
   {
      if (uiKey == 12) // VKSHIFT
      {
         m_bShiftKey = true;
      }
      else if (uiKey == 13) // VK_ESCAPE)
      {
         on_action("escape");
      }

      return false;

   }

   bool simple_ui::on_key_up(u32 uiKey)
   {

      string str;
      //unichar wsz[32];

      byte baState[256];

      __zero(baState);
      for (int i = 0; i < 256; i++)
      {
//         baState[i] = (byte)GetAsyncKeyState(i);
      }

      baState[uiKey & 0xff] = 0x80;

      /*if((GetAsyncKeyState(::user::e_key_shift) & 0x80000000) != 0)
      {
      baState[::user::e_key_shift] |= 0x80;
      }
      */
      if (m_bShiftKey)
      {
         baState[VK_SHIFT] |= 0x80;
      }

      char sz[2];


      sz[0] = uiKey;
      sz[1]  = '\0';

      //i32 iRet = ToUnicodeEx((::u32)wparam, 0, baState, wsz, 32, 0, GetKeyboardLayout(GetCurrentThreadId()));
      str = sz;
      on_char(static_cast<::u32>(uiKey), str);

      if (m_bShiftKey && uiKey == VK_SHIFT)
      {
         m_bShiftKey = false;
      }


      return false;

   }



   void simple_ui::get_window_rect(RECTANGLE_I32 * prectangle)
   {

      *prectangle = m_rectangleWindow;

   }
   void simple_ui::get_client_rect(RECTANGLE_I32 * prectangle)
   {

      *prectangle = m_rectangleWindow;

      prectangle->right -= prectangle->left;
      prectangle->bottom -= prectangle->top;
      prectangle->left = 0;
      prectangle->top = 0;

   }


   void simple_ui::on_draw_framebuffer()
   {

      ::rectangle_i32 rectangleWindow;

      ::get_window_rect(m_window, rectangleWindow);

      if(rectangleWindow.size() != m_rectangleWindow.size())
      {

         on_size(rectangleWindow.width(), rectangleWindow.height());

      }

      if(rectangleWindow.top_left() != m_rectangleWindow.top_left())
      {

         on_move(rectangleWindow.left, rectangleWindow.top);

      }

      m_rectangleWindow = rectangleWindow;


/*      if (m_pimage->is_set() && m_pimage->g() != nullptr)
      {

         ::rectangle_i32 rectangleClient = rectangleWindow;

         rectangleClient -= rectangleWindow.top_left();

         ::rectangle_i32 rectangle;

         rectangle = rectangleWindow;

/*         m_pimage->g()->set_alpha_mode(draw2d::e_alpha_mode_set);

/*         m_pimage->g()->SetViewportOrg(0, 0);

/*         m_pimage->g()->FillSolidRect(&rectangleClient, argb(255, 255, 255, 255));

/*         draw(m_pimage->g());

         //m_pimage->map();

/*         m_pimage->fill_channel(255, ::color::e_channel_alpha);

         //m_pimage->Fill(255, 184, 184, 177);

/*         byte *dst = (byte*) m_pimage->get_data();

         i64 size = m_size.cx * m_size.cy;


         // >> 8 instead of / 255 subsequent alpha_blend operations say thanks on true_blend because (255) * (1/254) + (255) * (254/255) > 255


         while (size >= 8)
         {
            dst[0] = __LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
            dst[1] = __LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
            dst[2] = __LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);

            dst[4 + 0] = __LOBYTE(((i32)dst[4 + 0] * (i32)dst[4 + 3]) >> 8);
            dst[4 + 1] = __LOBYTE(((i32)dst[4 + 1] * (i32)dst[4 + 3]) >> 8);
            dst[4 + 2] = __LOBYTE(((i32)dst[4 + 2] * (i32)dst[4 + 3]) >> 8);

            dst[8 + 0] = __LOBYTE(((i32)dst[8 + 0] * (i32)dst[8 + 3]) >> 8);
            dst[8 + 1] = __LOBYTE(((i32)dst[8 + 1] * (i32)dst[8 + 3]) >> 8);
            dst[8 + 2] = __LOBYTE(((i32)dst[8 + 2] * (i32)dst[8 + 3]) >> 8);

            dst[12 + 0] = __LOBYTE(((i32)dst[12 + 0] * (i32)dst[12 + 3]) >> 8);
            dst[12 + 1] = __LOBYTE(((i32)dst[12 + 1] * (i32)dst[12 + 3]) >> 8);
            dst[12 + 2] = __LOBYTE(((i32)dst[12 + 2] * (i32)dst[12 + 3]) >> 8);

            dst[16 + 0] = __LOBYTE(((i32)dst[16 + 0] * (i32)dst[16 + 3]) >> 8);
            dst[16 + 1] = __LOBYTE(((i32)dst[16 + 1] * (i32)dst[16 + 3]) >> 8);
            dst[16 + 2] = __LOBYTE(((i32)dst[16 + 2] * (i32)dst[16 + 3]) >> 8);

            dst[20 + 0] = __LOBYTE(((i32)dst[20 + 0] * (i32)dst[20 + 3]) >> 8);
            dst[20 + 1] = __LOBYTE(((i32)dst[20 + 1] * (i32)dst[20 + 3]) >> 8);
            dst[20 + 2] = __LOBYTE(((i32)dst[20 + 2] * (i32)dst[20 + 3]) >> 8);

            dst[24 + 0] = __LOBYTE(((i32)dst[24 + 0] * (i32)dst[24 + 3]) >> 8);
            dst[24 + 1] = __LOBYTE(((i32)dst[24 + 1] * (i32)dst[24 + 3]) >> 8);
            dst[24 + 2] = __LOBYTE(((i32)dst[24 + 2] * (i32)dst[24 + 3]) >> 8);

            dst[28 + 0] = __LOBYTE(((i32)dst[28 + 0] * (i32)dst[28 + 3]) >> 8);
            dst[28 + 1] = __LOBYTE(((i32)dst[28 + 1] * (i32)dst[28 + 3]) >> 8);
            dst[28 + 2] = __LOBYTE(((i32)dst[28 + 2] * (i32)dst[28 + 3]) >> 8);

            dst += 4 * 8;
            size -= 8;
         }
         while (size--)
         {
            dst[0] = __LOBYTE(((i32)dst[0] * (i32)dst[3]) >> 8);
            dst[1] = __LOBYTE(((i32)dst[1] * (i32)dst[3]) >> 8);
            dst[2] = __LOBYTE(((i32)dst[2] * (i32)dst[3]) >> 8);
            dst += 4;
         }

/*         m_xlib.update_window(m_window, (color32_t *)m_pimage->get_data(), &rectangle, m_pimage->m_iScan);

      }

   }

   bool simple_ui::on_move(i32 x, i32 y)
   {

      m_point.x = x;
      m_point.y = y;

      m_rectangle.left = m_point.x;
      m_rectangle.right = m_point.x + m_size.cx;
      m_rectangle.top = m_point.y;
      m_rectangle.bottom = m_point.y + m_size.cy;

      return true;

   }

   bool simple_ui::on_size(i32 cx, i32 cy)
   {

      m_size.cx = cx;
      m_size.cy = cy;

      m_rectangle.left = m_point.x;
      m_rectangle.right = m_point.x + m_size.cx;
      m_rectangle.top = m_point.y;
      m_rectangle.bottom = m_point.y + m_size.cy;

/*      m_pimage = create_image({get_application()->create_new,  this});
/*      m_pimage = create_image({m_size.cx,  m_size.cy});

      m_xlib.create(m_window, cx, cy);

      on_layout(pgraphics);

      return true;

   }


   void simple_ui::set_capture()
   {

      ::SetCapture(m_window);

   }


   void simple_ui::release_capture()
   {

      ::ReleaseCapture();

   }

   void simple_ui::destroy_window()
   {

      if(m_bRunLoop)
      {

         m_bRunLoop = false;

      }

      ::DestroyWindow(m_window);

      m_window = nullptr;

   }


   bool simple_ui::move_window(i32 x, i32 y)
   {

      ::set_window_position(m_window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      m_rectangle.left = x;
      m_rectangle.top = y;
      m_rectangle.right = x + m_size.cx;
      m_rectangle.bottom = y + m_size.cy;

      m_point.x = x;
      m_point.y = y;

      return true;

   }


   bool simple_ui::set_window_position(i32 x, i32 y, i32 cx, i32 cy, bool bShow)
   {

      ::set_window_position(m_window, nullptr, x, y, cx, cy, SWP_NOZORDER | (bShow ? SWP_SHOWWINDOW : 0));

      return true;

   }



} // namespace os






void wm_nodecorations(oswindow w, int map)
{
   Atom WM_HINTS;
   int set;


   single_lock synchronouslock(&user_mutex(), true);

   xdisplay d(w->display());
   Display * dpy = w->display();
   Window window = w->window();

   int scr=DefaultScreen(dpy);
   Window rootw=RootWindow(dpy, scr);

   WM_HINTS = XInternAtom(dpy, "_MOTIF_WM_HINTS", True);
   if ( WM_HINTS != None )
   {
#define MWM_HINTS_DECORATIONS   (1L << 1)
      struct
      {
         unsigned long flags;
         unsigned long functions;
         unsigned long decorations;
         long input_mode;
         unsigned long status;
      } MWMHints = { MWM_HINTS_DECORATIONS, 0,
                     MWM_DECOR_NONE, 0, 0
                   };
      XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                      PropModeReplace, (unsigned char *)&MWMHints,
                      sizeof(MWMHints)/4);
   }
   WM_HINTS = XInternAtom(dpy, "KWM_WIN_DECORATION", True);
   if ( WM_HINTS != None )
   {
      long KWMHints = KDE_tinyDecoration;
      XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                      PropModeReplace, (unsigned char *)&KWMHints,
                      sizeof(KWMHints)/4);
   }

   WM_HINTS = XInternAtom(dpy, "_WIN_HINTS", True);
   if ( WM_HINTS != None )
   {
      long GNOMEHints = 0;
      XChangeProperty(dpy, window, WM_HINTS, WM_HINTS, 32,
                      PropModeReplace, (unsigned char *)&GNOMEHints,
                      sizeof(GNOMEHints)/4);
   }
   WM_HINTS = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE", True);
   if ( WM_HINTS != None )
   {
      Atom NET_WMHints[2];
      NET_WMHints[0] = XInternAtom(dpy,
                                   "_KDE_NET_WM_WINDOW_TYPE_OVERRIDE", True);
      NET_WMHints[1] = XInternAtom(dpy, "_NET_WM_WINDOW_TYPE_NORMAL", True);
      XChangeProperty(dpy, window,
                      WM_HINTS, XA_ATOM, 32, PropModeReplace,
                      (unsigned char *)&NET_WMHints, 2);
   }
   XSetTransientForHint(dpy, window, rootw);
   if(map)
   {
      XUnmapWindow(dpy, window);
      XMapWindow(dpy, window);

   }
}
