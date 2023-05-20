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
#include <xkbcommon/xkbcommon.h>
#include <X11/XKBlib.h>
#include <cairo-xcb.h>


//unsigned long xcb_get_long_property(Display *d, Window w, char *property_name);


//Window _xcb_get_active_window(Display * pdisplay);


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


namespace xcb
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


   ::nano::display * nano_window::get_display()
   {

      if (!m_pdisplay)
      {

         m_pdisplay = ::xcb::display::get(this);

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

      ::u32 uEventMask =       XCB_EVENT_MASK_PROPERTY_CHANGE
                             | XCB_EVENT_MASK_EXPOSURE
                             | XCB_EVENT_MASK_BUTTON_PRESS
                             | XCB_EVENT_MASK_BUTTON_RELEASE
                             | XCB_EVENT_MASK_KEY_PRESS
                             | XCB_EVENT_MASK_KEY_RELEASE
                             | XCB_EVENT_MASK_POINTER_MOTION
                             | XCB_EVENT_MASK_STRUCTURE_NOTIFY
                             | XCB_EVENT_MASK_FOCUS_CHANGE
                             | XCB_EVENT_MASK_LEAVE_WINDOW
                             | XCB_EVENT_MASK_ENTER_WINDOW
      ;

      auto colormap = m_pdisplay->m_colormap;

      auto windowRoot = m_pdisplay->m_windowRoot;

      xcb_window_t window = xcb_generate_id(m_pdisplay->m_pconnection);

      int x = m_pinterface->m_rectangle.left;
      int y = m_pinterface->m_rectangle.top;
      int cx = m_pinterface->m_rectangle.width();
      int cy = m_pinterface->m_rectangle.height();

      ::u32 uaValueList[5];

      uaValueList[0] = 0; // XCB_CW_BACK_PIXMAP
      uaValueList[1] = 0; // XCB_CW_BORDER_PIXEL
      uaValueList[2] = 1; // XCB_CW_OVERRIDE_REDIRECT
      uaValueList[3] = uEventMask; // XCB_CW_EVENT_MASK
      uaValueList[4] = colormap; // XCB_CW_COLORMAP

      auto cookie = xcb_create_window(
         m_pdisplay->m_pconnection,
         m_pdisplay->m_pdepth->depth,
         window,
         m_pdisplay->m_windowRoot,
         x, y,
         cx, cy,
         0,
         XCB_WINDOW_CLASS_INPUT_OUTPUT,
         m_pdisplay->m_pvisualtype->visual_id,
         XCB_CW_BACK_PIXMAP
         | XCB_CW_BORDER_PIXEL
         | XCB_CW_OVERRIDE_REDIRECT
         | XCB_CW_EVENT_MASK
         | XCB_CW_COLORMAP,
         uaValueList);

      auto estatus = m_pdisplay->_request_check(cookie);

      if(!estatus)
      {

         throw exception(estatus);

      }

      m_window = window;

      m_pdisplay->add_listener(this);

      m_pdisplay->add_window(this);

#if 0

      // _NET_WM_WINDOW_TYPE_SPLASH
      // KDE seems to close this type of window when it is clicked

      if(m_pinterface->m_bStartCentered)
      {

         auto atomWindowType = XInternAtom(m_pdisplay->m_pdisplay, "_NET_WM_WINDOW_TYPE", true);

         auto atomWindowTypeSplash = XInternAtom(m_pdisplay->m_pdisplay, "_NET_WM_WINDOW_TYPE_SPLASH", true);

         if (atomWindowType != None && atomWindowTypeSplash != None)
         {

            XChangeProperty(m_pdisplay->m_pdisplay, m_window,
                            atomWindowType, XA_ATOM, 32, PropModeReplace,
                            (unsigned char *) &atomWindowTypeSplash, 1);

         }

      }

#endif

//         if(m_pinterface->m_bArbitraryPositioning)
//         {
//
//            XSetWindowAttributes attributes;
//
//            attributes.override_redirect = True;
//
//            XChangeWindowAttributes(m_pdisplay->m_pdisplay, m_window,
//                             CWOverrideRedirect,
//                             &attributes);
//
//   //      MWMHints mwm_hints;
//   //
//   //      Atom MotifHints = XInternAtom(m_pdisplay->m_pdisplay, "_MOTIF_WM_HINTS", 0);
//   //
//   //      mwm_hints.flags = MWM_HINTS_FUNCTIONS;
//   //      mwm_hints.functions=  MWM_FUNC_MOVE;
//   //
//   //      XMapWindow(m_pdisplay->m_pdisplay, m_window);
//   //      XChangeProperty(m_pdisplay->m_pdisplay, m_window, MotifHints, MotifHints, 32, PropModeReplace, (unsigned char *)&mwm_hints, 5);
//
//         }

      //m_pdisplay->XSelectInput(m_pdisplay->m_pdisplay, m_window, ExposureMask | KeyPressMask | VisibilityChangeMask | StructureNotifyMask | ButtonPressMask | PointerMotionMask | ButtonMotionMask | ButtonReleaseMask | LeaveWindowMask);

      nano_window_on_create();

      //XMapWindow(m_pdisplay->m_pdisplay, m_window);

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


nano_child * nano_window::hit_test(::user::mouse * pmouse, ::user::e_zorder ezorder)
{

   return m_pinterface->hit_test(pmouse, ezorder);

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
//      throw ::exception(error_failed, "Failed to register nano message box window class.");
//
//   }
//
//   g_bNanoWindowClassRegistered = true;
//
//}
//

   void nano_window::display()
   {

   //   if(is_main_thread())
   //   {
   //
   //      // Cannot display synchronously in user/main thread.
   //
   //      // Cannot show user interface on break of user/main thread.
   //
   //      debug_break();
   //
   //      return;
   //
   //   }

      _wm_nodecorations(false);

      //XMapWindow(m_pdisplay->m_pdisplay, m_window);

      _map_window();

      _raise_window();

      //XRaiseWindow(m_pdisplay->m_pdisplay, m_window);

      set_active();

      xcb_flush(m_pdisplay->m_pconnection);

   //   m_eventEnd.wait();

   }


   ::e_status nano_window::_map_window()
   {

      auto estatus = m_pdisplay->_map_window(m_window);

      return estatus;

   }


   ::e_status nano_window::_unmap_window()
   {

      auto estatus = m_pdisplay->_unmap_window(m_window);

      return estatus;

   }


   ::e_status nano_window::_raise_window()
   {

      auto estatus = m_pdisplay->_raise_window(m_window);

      return estatus;

   }


   void nano_window::set_active()
   {

      auto estatus = m_pdisplay->_set_active_window(m_window);

   }


   bool nano_window::_on_event(xcb_generic_event_t *pevent)
   {

      if(m_window == None)
      {

         return false;

      }

      auto event_type = pevent->response_type;

      if (event_type == XCB_CONFIGURE_NOTIFY)
      {

         auto pconfigure = (xcb_configure_notify_event_t *) pevent;

         if (pconfigure->window != m_window)
         {

            return false;

         }

         m_pinterface->m_rectangle.left = pconfigure->x;

         m_pinterface->m_rectangle.top = pconfigure->y;

         m_pinterface->m_rectangle.right = pconfigure->x + pconfigure->width;

         m_pinterface->m_rectangle.bottom = pconfigure->y + pconfigure->height;

         if (m_psurface)
         {

            cairo_xcb_surface_set_size(m_psurface, m_pinterface->m_rectangle.width(),
                                        m_pinterface->m_rectangle.height());

         }

      }
      else if (event_type == XCB_UNMAP_NOTIFY)
      {

         auto punmap = (xcb_unmap_notify_event_t *) pevent;

         if (punmap->window != m_window)
         {

            return false;

         }


         output_debug_string("UnmapNotify");

      }
      else if (event_type == XCB_MAP_NOTIFY)
      {

         auto pmap = (xcb_map_notify_event_t *) pevent;

         if (pmap->window != m_window)
         {

            return false;

         }


      }
      else if (event_type == XCB_EXPOSE)
      {

         auto pexpose = (xcb_expose_event_t *) pevent;

         if (pexpose->window != m_window)
         {

            return false;

         }

         if (!m_psurface)
         {

            rectangle_i32 rectangleClient;

            get_client_rectangle(rectangleClient);

            m_psurface = cairo_xcb_surface_create(
               m_pdisplay->m_pconnection,
               m_window,
               m_pdisplay->m_pvisualtype,
               rectangleClient.width(),
               rectangleClient.height());

            auto pdc = cairo_create(m_psurface);

            m_pnanodevice = __new(::cairo::nano_device(pdc));

         }

         _update_window();

      }
      else if (event_type == XCB_PROPERTY_NOTIFY)
      {

         auto pproperty = (xcb_property_notify_event_t *) pevent;

         if (pproperty->window != m_window)
         {

            return false;

         }

         //output_debug_string("PropertyNotify");

      }
      else if (event_type == XCB_KEY_PRESS)
      {

         auto pkey = (xcb_key_press_event_t *) pevent;

         if (pkey->event != m_window)
         {

            return false;

         }

         auto keysym = XkbKeycodeToKeysym((Display *) m_pdisplay->m_pX11Display, pkey->detail, 0, pkey->state & ShiftMask ? 1 : 0);

         int iChar = xkb_keysym_to_utf32(keysym);

         on_char(iChar);

      }
      else if (event_type == XCB_KEY_RELEASE)
      {

         auto pkey = (xcb_key_release_event_t *) pevent;

         if (pkey->event != m_window)
         {

            return false;

         }


      }
      else if (event_type == XCB_BUTTON_PRESS)
      {

         auto pbutton = (xcb_button_press_event_t *) pevent;

         if (pbutton->event != m_window)
         {

            return false;

         }

         if (pbutton->detail == XCB_BUTTON_INDEX_1)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pbutton->root_x, pbutton->root_y};

            on_left_button_down(pmouse);

         }
         else if (pbutton->detail == XCB_BUTTON_INDEX_3)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pbutton->root_x, pbutton->root_y};

            on_right_button_down(pmouse);

         }

      }
      else if (event_type == XCB_BUTTON_RELEASE)
      {

         auto pbutton = (xcb_button_release_event_t *) pevent;

         if (pbutton->event != m_window)
         {

            return false;

         }


         if (pbutton->detail == XCB_BUTTON_INDEX_1)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pbutton->root_x, pbutton->root_y};

            on_left_button_up(pmouse);

         }
         else if (pbutton->detail == XCB_BUTTON_INDEX_3)
         {

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = {pbutton->root_x, pbutton->root_y};

            on_right_button_up(pmouse);

         }

      }
      else if (event_type == MotionNotify)
      {

         auto pmotion = (xcb_motion_notify_event_t *) pevent;

         if (pmotion->event != m_window)
         {

            return false;

         }

         auto pmouse = __create_new < ::user::mouse >();

         pmouse->m_point = {pmotion->root_x, pmotion->root_y};

         on_mouse_move(pmouse);

      }
      else if (event_type == LeaveNotify)
      {

         auto pleave = (xcb_leave_notify_event_t *) pevent;

         if (pleave->event != m_window)
         {

            return false;

         }

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




//void nano_window::message_loop()
//{
//
//   while(message_loop_step())
//   {
//
//      acmesystem()->m_pnode->run_posted_routines();
//
//   }
//
//   output_debug_string("nano_window::message_loop exit");
//
//}


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

      _unmap_window();

      m_pdisplay->_destroy_window(m_window);

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

      m_pdisplay->_move_window(m_window, point.x, point.y);

      m_pinterface->m_rectangle.move_to(point);

   }


   void nano_window::set_capture()
   {


      auto estatus = m_pdisplay->_set_mouse_capture(m_window);

//      if (XGrabPointer(m_pdisplay->m_pdisplay, m_window, False, ButtonPressMask | ButtonReleaseMask | PointerMotionMask,
//                       GrabModeAsync, GrabModeAsync, None, None, CurrentTime) != GrabSuccess)
//      {
//
//         throw ::exception(error_exception);
//
//      }


//      auto pdisplay = xcb_display();
//
//      if(pdisplay)
//      {
//
//         pdisplay->_on_capture_changed_to(this);
//
//      }



   }


   void nano_window::release_capture()
   {

      //int bRet = XUngrabPointer(m_pdisplay->m_pdisplay, CurrentTime);

      m_pdisplay->_release_mouse_capture();

   }


   void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
   {

      xcb_get_geometry_reply_t geometry;

      _get_geometry(&geometry);

      rectangle.left = 0;
      rectangle.top = 0;
      rectangle.right = geometry.width;
      rectangle.bottom = geometry.height;

   }


   void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
   {

      xcb_get_geometry_reply_t geometry;

      _get_geometry(&geometry);

      rectangle.left = geometry.x;
      rectangle.top = geometry.y;
      rectangle.right = geometry.x + geometry.width;
      rectangle.bottom = geometry.y + geometry.height;

   }


   void nano_window::_wm_nodecorations(int iMap)
   {

      m_pdisplay->_set_nodecorations(m_window, iMap);

   }


   void nano_window::_get_geometry(xcb_get_geometry_reply_t * pgeometry)
   {

      m_pdisplay->_get_window_geometry(pgeometry, m_window);


   }


//   ::size_i32 nano_window::get_main_screen_size()
//   {
//
//      return m_pdisplay->get_main_screen_size();
//
//   }


} // namespace xcb




