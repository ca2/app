//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "window.h"
#include "display.h"
#include "acme/operating_system/cairo/nano/device.h"
#include "acme/user/user/mouse.h"
#include "acme/user/nano/child.h"
#include "acme/user/nano/window.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include <X11/Xatom.h>
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>
#include <X11/Xutil.h>
#include <cairo-xlib.h>


::user::enum_desktop _get_edesktop();


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};

#define MWM_HINTS_FUNCTIONS     (1L << 0)
#define MWM_HINTS_DECORATIONS   (1L << 1)


#define MWM_FUNC_ALL            (1L << 0)
#define MWM_FUNC_RESIZE         (1L << 1)
#define MWM_FUNC_MOVE           (1L << 2)
#define MWM_FUNC_MINIMIZE       (1L << 3)
#define MWM_FUNC_MAXIMIZE       (1L << 4)
#define MWM_FUNC_CLOSE          (1L << 5)

/* MWM decorations values */
#define MWM_DECOR_NONE          0
#define MWM_DECOR_ALL           (1L << 0)
#define MWM_DECOR_BORDER        (1L << 1)
#define MWM_DECOR_RESIZEH       (1L << 2)
#define MWM_DECOR_TITLE         (1L << 3)
#define MWM_DECOR_MENU          (1L << 4)
#define MWM_DECOR_MINIMIZE      (1L << 5)
#define MWM_DECOR_MAXIMIZE      (1L << 6)


namespace x11
{


   nano_window::nano_window()
   {

      m_psurface = nullptr;
      m_iDepth = -1;
      m_pvisual = nullptr;
      zero(m_visualinfo);
      m_colormap = 0;

   }


   nano_window::~nano_window()
   {

      delete_drawing_objects();

      m_pnanodevice.release();

      if(m_psurface != nullptr)
      {

         cairo_surface_destroy(m_psurface);

         m_psurface = nullptr;

      }

   }


   ::nano::display * nano_window::get_display()
   {

      if (!m_pdisplay)
      {

         m_pdisplay = ::x11::display::get(this);

         if (!m_pdisplay)
         {

            throw ::exception(error_null_pointer);

         }

      }

      return m_pdisplay;

   }


   void nano_window::on_initialize_particle()
   {

      ::object::on_initialize_particle();

   }


   void nano_window::on_char(int iChar)
   {

      fork([this, iChar]()
      {

         m_pinterface->on_char(iChar);

      });

   }


   void nano_window::_draw(nano_device * pnanodevice)
   {

      m_pinterface->draw(pnanodevice);

   }


   bool nano_window::is_active()
   {

      return m_pinterface->is_active();

   }


   void nano_window::delete_drawing_objects()
   {

      m_pinterface->delete_drawing_objects();

   }


   bool nano_window::get_dark_mode()
   {

      return acmenode()->dark_mode();

   }


   void nano_window::create_drawing_objects()
   {

      m_pinterface->create_drawing_objects();

   }


   void nano_window::update_drawing_objects()
   {

      m_pinterface->update_drawing_objects();

   }


   void nano_window::create()
   {

      get_display();

      m_pdisplay->display_send([this]()
      {

         auto display = m_pdisplay->m_pdisplay;

         m_pvisual = DefaultVisual(display, DefaultScreen(display));

         zero(m_visualinfo);

         if (XMatchVisualInfo(display, DefaultScreen(display), 32, TrueColor, &m_visualinfo))
         {

            m_pvisual = m_visualinfo.visual;

         }
         else
         {

            zero(m_visualinfo);

         }

         m_iDepth = m_visualinfo.depth;

         auto screen = DefaultScreen(display);

         m_windowRoot = RootWindow(display, screen);

         if(m_colormap)
         {

            XFreeColormap(display, m_colormap);

         }

         m_colormap = XCreateColormap(display, m_windowRoot, m_pvisual, AllocNone);

         m_pdisplay->add_listener(this);

         m_pdisplay->add_window(this);

         XSetWindowAttributes attr{};

         attr.colormap = m_colormap;

         attr.event_mask =
            PropertyChangeMask | ExposureMask | ButtonPressMask | ButtonReleaseMask
            | KeyPressMask | KeyReleaseMask | PointerMotionMask | StructureNotifyMask
            | FocusChangeMask | LeaveWindowMask | EnterWindowMask;

         attr.background_pixmap = None;

         attr.border_pixmap = None;

         attr.border_pixel = 0;

         attr.override_redirect = False;

         int x = m_pinterface->m_rectangle.left;
         int y = m_pinterface->m_rectangle.top;
         int w = m_pinterface->m_rectangle.width();
         int h = m_pinterface->m_rectangle.height();

         m_window = XCreateWindow(display, m_windowRoot,
            x, y, w, h,
            0,
            m_iDepth,
            InputOutput,
            m_pvisual,
            CWColormap | CWEventMask | CWBackPixmap | CWBorderPixel | CWOverrideRedirect,
            &attr
         );

         if(!m_window)
         {

            m_pdisplay->erase_listener(this);

            m_pdisplay->erase_window(this);

            throw exception(error_failed);

         }

         if(m_pinterface->m_bStartCentered)
         {

            auto atomWindowType = XInternAtom(display, "_NET_WM_WINDOW_TYPE", true);

            auto atomWindowTypeDialog = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DIALOG", true);

            if (atomWindowType != None && atomWindowTypeDialog != None)
            {

               XChangeProperty(display, m_window,
                               atomWindowType, XA_ATOM, 32, PropModeReplace,
                               (unsigned char *) &atomWindowTypeDialog, 1);

            }

            auto atomNormalHints = m_pdisplay->intern_atom("WM_NORMAL_HINTS", false);

            XSizeHints hints{};

            hints.flags = PWinGravity;

            hints.win_gravity = CenterGravity;

            XSetWMSizeHints(display, m_window, &hints, atomNormalHints);

         }

         if(m_pinterface->m_bArbitraryPositioning)
         {

            XSetWindowAttributes attributes;

            attributes.override_redirect = True;

            XChangeWindowAttributes(display, m_window,
                             CWOverrideRedirect,
                             &attributes);

         }

         nano_window_on_create();

      });

   }


   void nano_window::on_left_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_down(pmouse);

   }


   void nano_window::on_left_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_left_button_up(pmouse);

   }


   void nano_window::on_right_button_down(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_down(pmouse);

   }


   void nano_window::on_right_button_up(::user::mouse * pmouse)
   {

      m_pinterface->on_right_button_up(pmouse);

   }


   void nano_window::on_mouse_move(::user::mouse * pmouse)
   {

      m_pinterface->on_mouse_move(pmouse);

   }


   ::atom nano_window::get_result()
   {

      return m_pinterface->get_result();

   }


   nano_child * nano_window::hit_test(::user::mouse * pmouse)
   {

      return m_pinterface->hit_test(pmouse);

   }



   void nano_window::display()
   {

      _wm_nodecorations(false);

      XMapWindow(m_pdisplay->m_pdisplay, m_window);

      XRaiseWindow(m_pdisplay->m_pdisplay, m_window);

      set_active();

   }


   void nano_window::set_active()
   {

      XEvent xev;

      zero(xev);

      Window windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);

      Atom atomActiveWindow = XInternAtom(m_pdisplay->m_pdisplay, "_NET_ACTIVE_WINDOW", False);

      xev.xclient.type = ClientMessage;
      xev.xclient.send_event = True;
      xev.xclient.display = m_pdisplay->m_pdisplay;
      xev.xclient.window = m_window;
      xev.xclient.message_type = atomActiveWindow;
      xev.xclient.format = 32;
      xev.xclient.data.l[0] = 1;
      xev.xclient.data.l[1] = 0;
      xev.xclient.data.l[2] = 0;
      xev.xclient.data.l[3] = 0;
      xev.xclient.data.l[4] = 0;

      XSendEvent(m_pdisplay->m_pdisplay, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

   }


   bool nano_window::_on_event(XEvent *pevent)
   {

      if(m_window == None)
      {

         return false;

      }

      if (pevent->xany.window != m_window)
      {

         return false;

      }

      auto event_type = pevent->type;

      if (event_type == ConfigureNotify)
      {

         m_pinterface->m_rectangle.left = pevent->xconfigure.x;

         m_pinterface->m_rectangle.top = pevent->xconfigure.y;

         m_pinterface->m_rectangle.right = pevent->xconfigure.x + pevent->xconfigure.width;

         m_pinterface->m_rectangle.bottom = pevent->xconfigure.y + pevent->xconfigure.height;

         if (m_psurface)
         {

            cairo_xlib_surface_set_size(m_psurface, m_pinterface->m_rectangle.width(),
                                        m_pinterface->m_rectangle.height());

         }

      }
      else if (pevent->type == UnmapNotify)
      {

         output_debug_string("UnmapNotify");

      }
      else if (pevent->type == MapNotify)
      {

         if (!m_psurface)
         {

            rectangle_i32 r;

            get_client_rectangle(r);

            auto display = m_pdisplay->m_pdisplay;

            auto window = m_window;

            auto w = m_pinterface->m_rectangle.width();

            auto h = m_pinterface->m_rectangle.height();

            m_psurface = cairo_xlib_surface_create(
                    display,
                    window,
                    m_pvisual,
                    w, h);

            auto pdc = cairo_create(m_psurface);

            m_pnanodevice = __new(::cairo::nano_device(pdc));

         }

         _update_window();

      }
      else if (pevent->type == Expose)
      {

         _update_window();

      }
      else if (pevent->type == PropertyNotify)
      {

         output_debug_string("PropertyNotify");

      }
      else if (pevent->type == KeyPress)
      {

         auto keysym = XkbKeycodeToKeysym(m_pdisplay->m_pdisplay, pevent->xkey.keycode, 0, pevent->xkey.state & ShiftMask ? 1 : 0);

         int iChar = xkb_keysym_to_utf32(keysym);

         on_char(iChar);

      }
      else if (pevent->type == KeyRelease)
      {

      }
      else if (pevent->type == ButtonPress)
      {

         if (pevent->xbutton.button == Button1)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pevent->xbutton.x_root, pevent->xbutton.y_root};

            on_left_button_down(pmouse);

         }
         else if (pevent->xbutton.button == Button3)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pevent->xbutton.x_root, pevent->xbutton.y_root};

            on_right_button_down(pmouse);

         }

      }
      else if (pevent->type == ButtonRelease)
      {

         if (pevent->xbutton.button == Button1)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pevent->xbutton.x_root, pevent->xbutton.y_root};

            on_left_button_up(pmouse);

         }
         else if (pevent->xbutton.button == Button3)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pevent->xbutton.x_root, pevent->xbutton.y_root};

            on_right_button_up(pmouse);

         }

      }
      else if (pevent->type == MotionNotify)
      {

         auto pmouse = __create_new < ::user::mouse >();

         pmouse->m_point = {pevent->xmotion.x_root, pevent->xmotion.y_root};

         on_mouse_move(pmouse);

      }
      else if (pevent->type == LeaveNotify)
      {

         if (m_pinterface->m_pchildHover)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {-100'000, -100'000};

            m_pinterface->m_pchildHover->on_mouse_move(pmouse);

            m_pinterface->m_pchildHover = nullptr;

            m_pinterface->redraw();

         }

      }

      return true;

   }


   void nano_window::_update_window()
   {

      if(m_pnanodevice && m_psurface)
      {

         m_pnanodevice->on_begin_draw();

         draw(m_pnanodevice);

         m_pnanodevice->on_end_draw();

         cairo_surface_flush(m_psurface);

      }

   }


   void nano_window::redraw()
   {

      //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

      _update_window();

   }


   void nano_window::destroy()
   {

      XUnmapWindow(m_pdisplay->m_pdisplay, m_window);

      XDestroyWindow(m_pdisplay->m_pdisplay, m_window);

      if(m_colormap)
      {

         XFreeColormap(m_pdisplay->m_pdisplay, m_colormap);

      }

      m_pdisplay->erase_listener(this);

      m_pdisplay->erase_window(this);

      m_window = 0;

      //XCloseDisplay(m_pdisplay->m_pdisplay);

      m_eventEnd.SetEvent();

   }


   void nano_window::on_click(const ::atom & atomParam, ::user::mouse * pmouse)
   {

      atom atom(atomParam);

      fork([this, atom, pmouse]()
           {

              m_pinterface->on_click(atom, pmouse);

           }, {pmouse});

   }


   void nano_window::on_right_click(const ::atom & atomParam, ::user::mouse * pmouse)
   {

      atom atom(atomParam);

      fork([this, atom, pmouse]()
           {

              m_pinterface->on_right_click(atom, pmouse);

           }, {pmouse});

   }


   void nano_window::move_to(const ::point_i32 & point)
   {

      ::XMoveWindow(m_pdisplay->m_pdisplay, m_window, point.x, point.y);

   }


   void nano_window::set_capture()
   {

      if (XGrabPointer(m_pdisplay->m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                       GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
      {

         throw ::exception(error_exception);

      }

   }


   void nano_window::release_capture()
   {

      int bRet = XUngrabPointer(m_pdisplay->m_pdisplay, CurrentTime);

   }


   void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
   {

      rectangle.left = 0;
      rectangle.top = 0;

      Window windowRoot = 0;
      int x = 0;
      int y = 0;
      unsigned int w = 0;
      unsigned int h = 0;
      unsigned int border = 0;
      unsigned int depth = 0;

      auto status = XGetGeometry(m_pdisplay->m_pdisplay, m_window, &windowRoot, &x, &y, &w,
                          &h, &border, &depth);

      if(status == BadDrawable)
      {

         throw ::exception(error_exception);

      }

      rectangle.right = w;
      rectangle.bottom = h;


   }


   void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
   {

      Window windowRoot = 0;
      int x = 0;
      int y = 0;
      unsigned int w = 0;
      unsigned int h = 0;
      unsigned int border = 0;
      unsigned int depth = 0;

      auto status = XGetGeometry(m_pdisplay->m_pdisplay, m_window, &windowRoot, &x, &y, &w,
                                 &h, &border, &depth);

      if(status == BadDrawable)
      {

         throw ::exception(error_exception);

      }

      rectangle.left = x;
      rectangle.top = y;
      rectangle.right = x + w;
      rectangle.bottom = y + h;


   }


   void nano_window::_wm_nodecorations(int iMap)
   {

      auto windowRoot = DefaultRootWindow(m_pdisplay->m_pdisplay);

      bool bCreateAtom = false;

      Atom atomMotifHints = XInternAtom(m_pdisplay->m_pdisplay, "_MOTIF_WM_HINTS", bCreateAtom ? True : False);

      if (atomMotifHints != None)
      {

         MWMHints hints = {};

         hints.flags = MWM_HINTS_DECORATIONS;
         hints.decorations = MWM_DECOR_NONE;

         //XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
         //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
         XChangeProperty(m_pdisplay->m_pdisplay, m_window, atomMotifHints, atomMotifHints, 32, PropModeReplace,
                         (unsigned char *) &hints, sizeof(hints) / 4);

      }

      if (iMap)
      {

         XUnmapWindow(m_pdisplay->m_pdisplay, m_window);

         XMapWindow(m_pdisplay->m_pdisplay, m_window);

      }

      windowing_output_debug_string("\n::wm_nodecorations 2");

   }


//   ::size_i32 nano_window::get_main_screen_size()
//   {
//
//      return m_pdisplay->get_main_screen_size();
//
//   }


} // namespace x11


#define MAXSTR 1000


CLASS_DECL_ACME ::acme::system * get_system();


void x11_asynchronous(::procedure function)
{

   auto psystem = ::get_system();

   auto pdisplay = ::x11::display::get(psystem);

   if (!pdisplay)
   {

      throw ::exception(error_null_pointer);

   }

   pdisplay->display_post([function]()
                                    {

                                       function();

                                    });

}



