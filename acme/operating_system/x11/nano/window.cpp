//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"
#include <X11/Xatom.h>
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>


Window g_windowActive = 0;


unsigned long x11_get_long_property(Display *d, Window w, char *property_name);


Window _x11_get_active_window(Display * pdisplay);


struct MWMHints
{

   unsigned long flags;
   unsigned long functions;
   unsigned long decorations;
   long input_mode;
   unsigned long status;

};


#define MWM_HINTS_DECORATIONS   (1L << 1)


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


//   if (m_hfont)
//   {
//
//      ::DeleteObject(m_hfont);
//
//      m_hfont = nullptr;
//
//   }

   }


   void nano_window::on_initialize_object()
   {

      ::object::on_initialize_object();

   }


   void nano_window::on_char(int iChar)
   {

      m_pinterface->on_char(iChar);

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

      return m_psystem->node()->dark_mode();

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


//{
//
//   XEvent e;
//   const char * msg = "Hello, World!";
//   int s;
//
      m_pdisplay = XOpenDisplay(NULL);

      if (!m_pdisplay)
      {
         //fprintf(stderr,
         //"Cannot open display\n");
        // exit(1);
        throw_status(error_null_pointer);
      }

//
      auto screen = DefaultScreen(m_pdisplay);

      auto windowRoot = RootWindow(m_pdisplay, screen);

      m_window = XCreateSimpleWindow(m_pdisplay, windowRoot,
                         m_pinterface->m_rectangle.left,
                         m_pinterface->m_rectangle.top,
                         m_pinterface->m_rectangle.width(),
                         m_pinterface->m_rectangle.height(), 1,
                        BlackPixel(m_pdisplay, screen), WhitePixel(m_pdisplay, screen));

      if(m_pinterface->m_bStartCentered)
      {

         auto atomWindowType = XInternAtom(m_pdisplay, "_NET_WM_WINDOW_TYPE", true);

         auto atomWindowTypeSplash = XInternAtom(m_pdisplay, "_NET_WM_WINDOW_TYPE_SPLASH", true);

         if (atomWindowType != None && atomWindowTypeSplash != None)
         {

            XChangeProperty(m_pdisplay, m_window,
                            atomWindowType, XA_ATOM, 32, PropModeReplace,
                            (unsigned char *) &atomWindowTypeSplash, 1);

         }

      }

      XSelectInput(m_pdisplay, m_window, ExposureMask | KeyPressMask | VisibilityChangeMask | StructureNotifyMask | ButtonPressMask | ButtonMotionMask | ButtonReleaseMask | LeaveWindowMask);

      XSelectInput(m_pdisplay, windowRoot, PropertyChangeMask);

      create_drawing_objects();

      on_create();

      //XMapWindow(m_pdisplay, m_window);

   }

//::atom nano_window::hit_test(int x, int y)
//{
//
//   for (int i = 0; i < m_iButtonCount; i++)
//   {
//      if (m_buttona[i].m_rectangle.contains(point_i32(x, y)))
//      {
//
//         return m_buttona[i].m_edialogresult;
//
//      }
//
//   }
//
//   return e_dialog_result_none;
//
//}
//

void nano_window::on_left_button_down(int x, int y)
{

   m_pinterface->on_left_button_down(x, y);

}


void nano_window::on_left_button_up(int x, int y)
{

   m_pinterface->on_left_button_up(x, y);
}


void nano_window::on_mouse_move(int x, int y)
{

   m_pinterface->on_mouse_move(x, y);

}


::atom nano_window::get_result()
{

   return m_pinterface->get_result();

}


nano_child * nano_window::hit_test(int x, int y)
{

   return m_pinterface->hit_test(x, y);

}


//LRESULT CALLBACK nano_message_box::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//if (msg == WM_NCCREATE)
//{
//
//   CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
//   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pcreatestruct->lpCreateParams);
//
//}
//nano_message_box * pwindow = (nano_message_box *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
//
//if (!pwindow)
//{
//   return DefWindowProc(hwnd, msg, wParam, lParam);
//}
//return pwindow->window_procedure(msg, wParam, lParam);
//
//}

//#ifndef GET_X_LPARAM
//#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
//#endif
//
//
//#ifndef GET_Y_LPARAM
//#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
//#endif
//
////LRESULT nano_window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
//{
//   switch (message)
//   {
//      case WM_CLOSE:
//         DestroyWindow(m_hwnd);
//         break;
//      case WM_DESTROY:
//         PostQuitMessage(0);
//         break;
//      case WM_CREATE:
//      {
//         update_drawing_objects();
//      }
//         break;
//      case WM_CHAR:
//      {
//         on_char((int) wparam);
//         return 0;
//      }
//         break;
//      case WM_LBUTTONDOWN:
//         on_left_button_down(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
//         break;
//      case WM_MOUSEMOVE:
//         on_mouse_move(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
//         break;
//      case WM_LBUTTONUP:
//      {
//         on_left_button_up(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
//
//      }
//
//         break;
//      case WM_PAINT:
//      {
//         PAINTSTRUCT paintstruct{};
//         HDC hdc = BeginPaint(m_hwnd, &paintstruct);
//         draw(hdc);
//         EndPaint(m_hwnd, &paintstruct);
//      }
//         break;
//      case WM_NCACTIVATE:
//      {
//         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
//         m_bNcActive = wparam != 0;
//         redraw();
//
//         return lresult;
//
//      }
//      case WM_ACTIVATE:
//      {
//         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
//
//
//         return lresult;
//
//      }
//      default:
//         return DefWindowProc(m_hwnd, message, wparam, lparam);
//   }
//   return 0;
//}
//
//
//HINSTANCE nano_message_box_hinstance()
//{
//
//   HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");
//
//   if (hinstanceWndProc == nullptr)
//   {
//
//      hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);
//
//   }
//
//   return hinstanceWndProc;
//
//}

//
//void register_nano_window_class()
//{
//
//   if (g_bNanoWindowClassRegistered)
//   {
//
//      return;
//
//   }
//
//   auto hinstanceWndProc = nano_message_box_hinstance();
//
//   WNDCLASSEX wndclassex;
//
//   //Step 1: Registering the Window Class
//   wndclassex.cbSize = sizeof(WNDCLASSEX);
//   wndclassex.style = 0;
//   wndclassex.lpfnWndProc = &message_box_window_procedure;
//   wndclassex.cbClsExtra = 0;
//   wndclassex.cbWndExtra = 0;
//   wndclassex.hInstance = hinstanceWndProc;
//   wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
//   wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
//   wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//   wndclassex.lpszMenuName = NULL;
//   wndclassex.lpszClassName = _T(NANO_MESSAGE_BOX_WINDOW_CLASS);
//   wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
//
//   if (!RegisterClassEx(&wndclassex))
//   {
//
//      throw_status(error_failed, "Failed to register nano message box window class.");
//
//   }
//
//   g_bNanoWindowClassRegistered = true;
//
//}
//

void nano_window::display_synchronously()
{

   _wm_nodecorations(false);

   XMapWindow(m_pdisplay, m_window);

   XRaiseWindow(m_pdisplay, m_window);

   set_active();

   message_loop();

}


void nano_window::set_active()
{

   XEvent xev;

   __zero(xev);

   Window windowRoot = DefaultRootWindow(m_pdisplay);

   Atom atomActiveWindow = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);

   xev.xclient.type = ClientMessage;
   xev.xclient.send_event = True;
   xev.xclient.display = m_pdisplay;
   xev.xclient.window = m_window;
   xev.xclient.message_type = atomActiveWindow;
   xev.xclient.format = 32;
   xev.xclient.data.l[0] = 1;
   xev.xclient.data.l[1] = 0;
   xev.xclient.data.l[2] = 0;
   xev.xclient.data.l[3] = 0;
   xev.xclient.data.l[4] = 0;

   XSendEvent(m_pdisplay, windowRoot, False, SubstructureRedirectMask | SubstructureNotifyMask, &xev);

}





void nano_window::_on_event(XEvent *pevent)
{


   if (pevent->type == ConfigureNotify)
   {

      m_pinterface->m_rectangle.left = pevent->xconfigure.x;

      m_pinterface->m_rectangle.top = pevent->xconfigure.y;

      m_pinterface->m_rectangle.right = pevent->xconfigure.x + pevent->xconfigure.width;

      m_pinterface->m_rectangle.bottom = pevent->xconfigure.y +  pevent->xconfigure.height;

      if (m_psurface)
      {

         cairo_xlib_surface_set_size(m_psurface, m_pinterface->m_rectangle.width(), m_pinterface->m_rectangle.height());

      }

   }
   else if (pevent->type == MapNotify)
   {

      if (!m_psurface)
      {

         rectangle_i32 r;

         get_client_rectangle(r);

         m_psurface = cairo_xlib_surface_create(
            m_pdisplay,
            m_window,
            DefaultVisual(m_pdisplay, DefaultScreen(m_pdisplay)),
            m_pinterface->m_rectangle.width(),
            m_pinterface->m_rectangle.height());

         auto pdc = cairo_create(m_psurface);

         m_pnanodevice = __new(::x11::nano_device(pdc));

      }

      _update_window();

   }
   else if (pevent->type == Expose)
   {

      _update_window();

   }
   else if(pevent->type == PropertyNotify)
   {

      if(pevent->xany.window == DefaultRootWindow(m_pdisplay))
      {

         Atom atom = XInternAtom(m_pdisplay, "_NET_ACTIVE_WINDOW", False);

         if(atom == pevent->xproperty.atom)
         {

            auto windowActive = _x11_get_active_window(m_pdisplay);

            bool bNcActive = windowActive == m_window;

            if(is_different(bNcActive, m_pinterface->m_bNcActive))
            {

               m_pinterface->m_bNcActive = bNcActive;

               redraw();

            }

            g_windowActive = windowActive;

         }

      }

   }
   else if (pevent->type == KeyPress)
   {

      auto keysym = XkbKeycodeToKeysym(m_pdisplay, pevent->xkey.keycode, 0, pevent->xkey.state & ShiftMask ? 1 : 0);

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

         on_left_button_down(pevent->xbutton.x_root, pevent->xbutton.y_root);

      }

   }
   else if (pevent->type == ButtonRelease)
   {

      if (pevent->xbutton.button == Button1)
      {

         on_left_button_up(pevent->xbutton.x_root, pevent->xbutton.y_root);

      }

   }
   else if (pevent->type == MotionNotify)
   {

      on_mouse_move(pevent->xmotion.x_root, pevent->xmotion.y_root);

   }
   else if (pevent->type == LeaveNotify)
   {

      if(m_pinterface->m_pchildHover)
      {

         m_pinterface->m_pchildHover->on_mouse_move(-100000, -10000);

         m_pinterface->m_pchildHover = nullptr;

         m_pinterface->redraw();

      }

   }

}


void nano_window::_update_window()
{

   if(m_pnanodevice && m_psurface)
   {

      cairo_push_group(m_pnanodevice->m_pdc);

      cairo_set_operator(m_pnanodevice->m_pdc, CAIRO_OPERATOR_SOURCE);

      draw(m_pnanodevice);

      cairo_pop_group_to_source(m_pnanodevice->m_pdc);

      cairo_paint(m_pnanodevice->m_pdc);

      cairo_surface_flush(m_psurface);

   }

}


bool nano_window::message_loop_step()
{

   XEvent event;

   XNextEvent(m_pdisplay, &event);

   _on_event(&event);

   return m_pinterface->m_atomResult.is_empty();

}


void nano_window::message_loop()
{

   while(message_loop_step())
   {



   }

   output_debug_string("nano_window::message_loop exit");

}


//
//
//


//   MSG msg;
//
//   while (::task_get_run() && GetMessage(&msg, NULL, 0, 0) > 0)
//   {
//
//      TranslateMessage(&msg);
//
//      DispatchMessage(&msg);
//
//   }
//
//}

//void nano_window::add_child(nano_child * pchild)
//{
//
//   pchild->m_pwindow = m_pinterfacethis;
//
//   m_childa.add(pchild);
//
//}


void nano_window::redraw()
{

   //::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

   _update_window();

}


//
//LRESULT nano_window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
//{
//   switch (message)
//   {
//   case WM_CLOSE:
//      DestroyWindow(m_hwnd);
//      break;
//   case WM_DESTROY:
//      PostQuitMessage(0);
//      break;
//   case WM_CREATE:
//   {
//      update_drawing_objects();
//   }
//   break;
//   case WM_LBUTTONDOWN:
//      on_left_button_down(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
//      break;
//   case WM_LBUTTONUP:
//   {
//      on_left_button_up(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
//   }
//
//   break;
//   case WM_PAINT:
//   {
//      PAINTSTRUCT paintstruct{};
//      HDC hdc = BeginPaint(m_hwnd, &paintstruct);
//      draw(hdc);
//      EndPaint(m_hwnd, &paintstruct);
//   }
//   break;
//   default:
//      return DefWindowProc(m_hwnd, message, wparam, lparam);
//   }
//   return 0;
//}

   void nano_window::destroy()
   {

      XUnmapWindow(m_pdisplay, m_window);

      XDestroyWindow(m_pdisplay, m_window);

      XCloseDisplay(m_pdisplay);

   }

   void nano_window::on_click(const ::atom & atom)
   {

      m_pinterface->on_click(atom);

   }


   void nano_window::move_to(int x, int y)
   {

      ::XMoveWindow(m_pdisplay, m_window, x, y);

   }


   void nano_window::set_capture()
   {

      if (XGrabPointer(m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
                       GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
      {

         throw_status(error_exception);

      }

   }


   void nano_window::release_capture()
   {

      int bRet = XUngrabPointer(m_pdisplay, CurrentTime);

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

      auto status = XGetGeometry(m_pdisplay, m_window, &windowRoot, &x, &y, &w,
                          &h, &border, &depth);

      if(status == BadDrawable)
      {

         throw_status(error_exception);

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

      auto status = XGetGeometry(m_pdisplay, m_window, &windowRoot, &x, &y, &w,
                                 &h, &border, &depth);

      if(status == BadDrawable)
      {

         throw_status(error_exception);

      }

      rectangle.left = x;
      rectangle.top = y;
      rectangle.right = x + w;
      rectangle.bottom = y + h;


   }


   void nano_window::_wm_nodecorations(int iMap)
   {

      auto windowRoot = DefaultRootWindow(m_pdisplay);

      bool bCreateAtom = false;

      Atom atomMotifHints = XInternAtom(m_pdisplay, "_MOTIF_WM_HINTS", bCreateAtom ? True : False);

      if (atomMotifHints != None)
      {

         MWMHints hints = {};

         hints.flags = MWM_HINTS_DECORATIONS;
         hints.decorations = MWM_DECOR_NONE;

         //XChangeProperty(Display(), Window(), atomMotifHints, atomMotifHints, 32, PropModeReplace,
         //              (unsigned char *) &hints, sizeof(MWMHints) / 4);
         XChangeProperty(m_pdisplay, m_window, atomMotifHints, atomMotifHints, 32, PropModeReplace,
                         (unsigned char *) &hints, sizeof(hints) / 4);

      }

      if (iMap)
      {

         XUnmapWindow(m_pdisplay, m_window);

         XMapWindow(m_pdisplay, m_window);

      }

      windowing_output_debug_string("\n::wm_nodecorations 2");

   }


} // namespace x11


void x11_check_status(int status, unsigned long window)
{

   if (status == BadWindow)
   {

      printf("window atom # 0x%lx does not exists!", window);

      throw_status(error_exception);

   }

   if (status != Success)
   {

      printf("XGetWindowProperty failed!");

      throw_status(error_exception);

   }

}


#define MAXSTR 1000


unsigned char* x11_get_string_property(Display * display, Window window, char* property_name)
{

   unsigned char * prop;
   Atom actual_type, filter_atom;
   int actual_format, status;
   unsigned long nitems, bytes_after;

   filter_atom = XInternAtom(display, property_name, True);

   status = XGetWindowProperty(display, window, filter_atom, 0, MAXSTR, False, AnyPropertyType,
                               &actual_type, &actual_format, &nitems, &bytes_after, &prop);

   x11_check_status(status, window);

   return prop;

}


unsigned long x11_get_long_property(Display *d, Window w, char *property_name)
{

   unsigned char *prop = x11_get_string_property(d, w, property_name);

   unsigned long long_property = prop[0] + (prop[1] << 8) + (prop[2] << 16) + (prop[3] << 24);

   return long_property;

}


Window _x11_get_active_window(Display * pdisplay)
{

   int screen = XDefaultScreen(pdisplay);

   Window windowRoot = RootWindow(pdisplay, screen);

   Window window = x11_get_long_property(pdisplay, windowRoot, (char*) "_NET_ACTIVE_WINDOW");

   return window;

}



