//
// Created by camilo on 31/01/2022 15:37 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "nano_window.h"


namespace x11
{


   nano_window::nano_window()
   {

      enable_drag_move();

      //m_pbrushWindow = nullptr;
      //m_hpenBorder = nullptr;
      //m_hpenBorderFocus = nullptr;
      //m_hfont = nullptr;
      //m_hpenNull = (HPEN) GetStockObject(NULL_PEN);
      m_bNcActive = false;

   }


//{
//
//   Display * d;
//   Window w;
//   XEvent e;
//   const char * msg = "Hello, World!";
//   int s;
//
//   d = XOpenDisplay(NULL);
//   if (d == NULL)
//{
//   fprintf(stderr,
//   "Cannot open display\n");
//   exit(1);
//}
//
//s = DefaultScreen(d);
//w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 1,
//                        BlackPixel(d, s), WhitePixel(d, s));
//XSelectInput(d, w, ExposureMask
//| KeyPressMask);
//XMapWindow(d, w
//);
//
//while (1) {
//XNextEvent(d, & e
//);
//if (e.type == Expose) {
//XFillRectangle(d, w, DefaultGC(d, s),
//20, 20, 10, 10);
//XDrawString(d, w, DefaultGC(d, s),
//10, 50, msg,
//strlen(msg)
//);
//}
//if (e.type == KeyPress)
//break;
//}
//
//XCloseDisplay(d);
//return 0;
//
//}
//
//
//

nano_window::~nano_window()
{

   delete_drawing_objects();

//   if (m_hfont)
//   {
//
//      ::DeleteObject(m_hfont);
//
//      m_hfont = nullptr;
//
//   }

}


void nano_window::on_char(int iChar)
{

   if (iChar == '\t' && m_childa.has_element())
   {

      auto iFind = m_childa.find_first(m_pchildFocus);

      iFind++;

      m_pchildFocus = m_childa % iFind;

      redraw();

   } else if (m_pchildFocus)
   {

      m_pchildFocus->on_char(iChar);

   }

}


void nano_window::_draw(nano_device * pnanodevice)
{

   draw(pnanodevice);

}


//void nano_window::on_draw(HDC hdc)
//{
//
//
//}

bool nano_window::is_active()
{

   return m_bNcActive;

}


//void nano_window::draw_children(HDC hdc)
//{
//
//   for (auto & pchild: m_childa)
//   {
//
//      pchild->on_draw(hdc);
//
//   }
//
//}

void nano_window::delete_drawing_objects()
{

   m_pbrushWindow.release();

   m_ppenBorder.release();

   m_ppenBorder.release();

}


bool nano_window::get_dark_mode()
{

   return true;

}


void nano_window::create_drawing_objects()
{

   if (!m_pfont)
   {

      __construct(m_pfont);

      m_pfont->m_iFontSize = 14;

      m_pfont->m_strFontName = m_psystem->node()->font_name(e_font_sans);

      m_pfont->create();

   }

   bool bDarkMode = get_dark_mode();

   if (bDarkMode)
   {

      m_colorWindow = rgb(0, 0, 0);
      m_colorText = rgb(255, 255, 255);
      m_colorFocus = rgb(2, 128, 255);

   }
   else
   {

      m_colorWindow = rgb(255, 255, 255);
      m_colorText = rgb(0, 0, 0);
      m_colorFocus = rgb(1, 64, 128);

   }

   m_pbrushWindow = ::nano::create_solid_brush(this, m_colorWindow);

   m_ppenBorder = ::nano::create_pen(this, 1, m_colorText);

   m_ppenBorderFocus =  ::nano::create_pen(this, 1, m_colorFocus);

}


void nano_window::update_drawing_objects()
{

   delete_drawing_objects();
   create_drawing_objects();

}


//::id nano_window::hit_test(int x, int y)
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

   set_capture();

   m_idLeftButtonDown = hit_test(x, y);

   if (m_pdragmove && m_idLeftButtonDown == e_dialog_result_none)
   {

      m_pdragmove->m_bLButtonDown = true;

      m_pdragmove->m_bDrag = false;

      point_i32 pointCursor(x, y);

      pointCursor += m_rectangle.origin();

      m_pdragmove->m_pointLButtonDown = pointCursor;

      m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

      return;

   }


}


void nano_window::on_left_button_up(int x, int y)
{

   ReleaseCapture();

   if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
   {

      m_pdragmove->m_bLButtonDown = false;

      m_pdragmove->m_bDrag = false;

      return;

   }

   m_idLeftButtonUp = hit_test(x, y);

   if (m_idLeftButtonUp == m_idLeftButtonDown && m_idLeftButtonUp != e_dialog_result_none)
   {

      m_idResult = m_idLeftButtonUp;

      on_click(m_idResult);

   }

}

void nano_window::on_mouse_move(int x, int y)
{

   if (m_pdragmove && m_pdragmove->m_bLButtonDown)
   {

      ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

      if (!m_pdragmove->m_bDrag)
      {

         m_pdragmove->m_bDrag = true;

         point_i32 pointCursor(x, y);

         pointCursor += m_rectangle.origin();

         auto point = pointCursor - m_pdragmove->m_sizeLButtonDownOffset;

         move_to(point.x, point.y);

         m_pdragmove->m_bDrag = false;

      }

      return;

   }


}


::id nano_window::get_result()
{

   return m_idResult;

}


::id nano_window::hit_test(int x, int y)
{

   for (auto & pchild: m_childa)
   {

      if (pchild->m_rectangle.contains(point_i32(x, y)))
      {

         return pchild->m_id;

      }

   }

   return e_dialog_result_none;

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

#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lparam)                          ((i32)(i16)LOWORD(lparam))
#endif


#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lparam)                          ((i32)(i16)HIWORD(lparam))
#endif

LRESULT nano_window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
{
   switch (message)
   {
      case WM_CLOSE:
         DestroyWindow(m_hwnd);
         break;
      case WM_DESTROY:
         PostQuitMessage(0);
         break;
      case WM_CREATE:
      {
         update_drawing_objects();
      }
         break;
      case WM_CHAR:
      {
         on_char((int) wparam);
         return 0;
      }
         break;
      case WM_LBUTTONDOWN:
         on_left_button_down(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
         break;
      case WM_MOUSEMOVE:
         on_mouse_move(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
         break;
      case WM_LBUTTONUP:
      {
         on_left_button_up(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));

      }

         break;
      case WM_PAINT:
      {
         PAINTSTRUCT paintstruct{};
         HDC hdc = BeginPaint(m_hwnd, &paintstruct);
         draw(hdc);
         EndPaint(m_hwnd, &paintstruct);
      }
         break;
      case WM_NCACTIVATE:
      {
         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
         m_bNcActive = wparam != 0;
         redraw();

         return lresult;

      }
      case WM_ACTIVATE:
      {
         LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);


         return lresult;

      }
      default:
         return DefWindowProc(m_hwnd, message, wparam, lparam);
   }
   return 0;
}
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
   ShowWindow(m_hwnd, SW_SHOW);

   UpdateWindow(m_hwnd);

   message_loop();

}

void nano_window::message_loop()
{

   MSG msg;

   while (::task_get_run() && GetMessage(&msg, NULL, 0, 0) > 0)
   {

      TranslateMessage(&msg);

      DispatchMessage(&msg);

   }

}

void nano_window::add_child(nano_child * pchild)
{

   pchild->m_pwindow = this;

   m_childa.add(pchild);

}


void nano_window::redraw()
{

   ::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

}


void nano_window::destroy()
{

   ::DestroyWindow(m_hwnd);

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


void nano_window::on_click(const ::id & id)
{


}


void nano_window::move_to(int x, int y)
{

   ::SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

   ::GetWindowRect(m_hwnd, (RECT * ) & m_rectangle);

}



} // namespace x11
