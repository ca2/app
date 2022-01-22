// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_window.h"



nano_window::nano_window()
{

   m_hbrushWindow = nullptr;
   m_hpenBorder = nullptr;
   m_hpenBorderFocus = nullptr;
   m_hfont = nullptr;
   m_hpenNull = (HPEN)GetStockObject(NULL_PEN);
   m_bNcActive = false;

}


nano_window::~nano_window()
{

   delete_drawing_objects();

   if (m_hfont)
   {

      ::DeleteObject(m_hfont);

      m_hfont = nullptr;

   }

}


void nano_window::on_char(int iChar)
{

   if (iChar == '\t' && m_childa.has_element())
   {

      auto iFind = m_childa.find_first(m_pchildFocus);

      iFind++;

      m_pchildFocus = m_childa % iFind;

      redraw();

   }
   else if(m_pchildFocus)
   {

       m_pchildFocus->on_char(iChar);

   }

}

void nano_window::draw(HDC hdc)
{

   GetClientRect(m_hwnd, (LPRECT)&m_rectangleClient);

   HBRUSH hbrushOld = (HBRUSH) ::SelectObject(hdc, m_hbrushWindow);
   HPEN hpenOld = nullptr;
   HFONT hfontOld = (HFONT) ::SelectObject(hdc, m_hfont);

   if (is_active())
   {

      hpenOld = (HPEN) ::SelectObject(hdc, m_hpenBorderFocus);

   }
   else
   {

      hpenOld = (HPEN) ::SelectObject(hdc, m_hpenBorder);

   }

   Rectangle(hdc, 
      m_rectangleClient.left, 
      m_rectangleClient.top, 
      m_rectangleClient.right, 
      m_rectangleClient.bottom);

   on_draw(hdc);

   draw_children(hdc);

   

   ::SelectObject(hdc, hfontOld);
   ::SelectObject(hdc, hbrushOld);
   ::SelectObject(hdc, hpenOld);

}


void nano_window::on_draw(HDC hdc)
{


}

bool nano_window::is_active()
{

   return m_bNcActive;

}


void nano_window::draw_children(HDC hdc)
{

   for(auto & pchild : m_childa)
   {

      pchild->on_draw(hdc);

   }

}
void nano_window::delete_drawing_objects()
{

   if (m_hbrushWindow)
   {

      ::DeleteObject(m_hbrushWindow);

      m_hbrushWindow = nullptr;

   }

   if (m_hpenBorder)
   {

      ::DeleteObject(m_hpenBorder);

      m_hpenBorder = nullptr;

   }

   
   if (m_hpenBorderFocus)
   {

      ::DeleteObject(m_hpenBorderFocus);

      m_hpenBorderFocus = nullptr;

   }

}


bool nano_window::get_dark_mode()
{

   return true;

}


void nano_window::create_drawing_objects()
{

   if (m_hfont == nullptr)
   {

      HDC hdc = ::GetDC(m_hwnd);
      int nHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);
      m_hfont = ::CreateFontW(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_SWISS, L"Segoe UI");
      ::ReleaseDC(m_hwnd, hdc);

   }

   bool bDarkMode = get_dark_mode();

   if (bDarkMode)
   {

      m_crWindow = RGB(0, 0, 0);
      m_crText = RGB(255, 255, 255);
      m_crFocus = RGB(2, 128, 255);

   }
   else
   {

      m_crWindow = RGB(255, 255, 255);
      m_crText = RGB(0, 0, 0);
      m_crFocus = RGB(1, 64, 128);

   }

   m_hbrushWindow = CreateSolidBrush(m_crWindow);
   m_hpenBorder = CreatePen(PS_SOLID, 1, m_crText);
   m_hpenBorderFocus = CreatePen(PS_SOLID, 1, m_crFocus);

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

   SetCapture(m_hwnd);

   m_idLeftButtonDown = hit_test(x, y);

}


void nano_window::on_left_button_up(int x, int y)
{
   
   ReleaseCapture();
   
   m_idLeftButtonUp = hit_test(x, y);

   if (m_idLeftButtonUp == m_idLeftButtonDown && m_idLeftButtonUp != e_dialog_result_none)
   {

      m_idResult = m_idLeftButtonUp;
      
      on_click(m_idResult);

   }

}


::id nano_window::get_result()
{

   return m_idResult;

}







::id nano_window::hit_test(int x, int y)
{

   for (auto & pchild : m_childa)
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
      on_char(wparam);
      return 0;
   }
   break;
   case WM_LBUTTONDOWN:
      on_left_button_down(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
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
         
   while (GetMessage(&msg, NULL, 0, 0) > 0)
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



