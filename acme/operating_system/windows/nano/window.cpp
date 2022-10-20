// Created by camilo on 2022-01-21 05:05 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/user/nano/_nano.h"
#include "_nano.h"
#include "acme/user/user/mouse.h"


namespace windows
{


   nano_window::nano_window()
   {

      m_bDestroy = false;

   }


   nano_window::~nano_window()
   {

      delete_drawing_objects();

   }


   bool g_bNanoWindowClassRegistered = false;



   LRESULT CALLBACK nano_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


#define NANO_WINDOW_CLASS "nano_window_class"





   HINSTANCE nano_message_box_hinstance()
   {

      HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");

      if (hinstanceWndProc == nullptr)
      {

         hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);

      }

      return hinstanceWndProc;

   }


   void register_nano_window_class()
   {

      if (g_bNanoWindowClassRegistered)
      {

         return;

      }

      auto hinstanceWndProc = nano_message_box_hinstance();

      WNDCLASSEX wndclassex{};

      //Step 1: Registering the Window Class
      wndclassex.cbSize = sizeof(WNDCLASSEX);
      wndclassex.style = CS_DBLCLKS;
      wndclassex.lpfnWndProc = &nano_window_procedure;
      wndclassex.cbClsExtra = 0;
      wndclassex.cbWndExtra = 0;
      wndclassex.hInstance = hinstanceWndProc;
      wndclassex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
      wndclassex.hCursor = LoadCursor(NULL, IDC_ARROW);
      wndclassex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wndclassex.lpszMenuName = NULL;
      wndclassex.lpszClassName = _T(NANO_WINDOW_CLASS);
      wndclassex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

      if (!RegisterClassEx(&wndclassex))
      {

         throw ::exception(error_failed, "Failed to register nano message box window class.");

      }

      g_bNanoWindowClassRegistered = true;

   }



   // Step 4: the Window Procedure
   LRESULT CALLBACK nano_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {

      ::windows::nano_window * pwindow = nullptr;

      if (msg == WM_NCCREATE)
      {

         CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;

         pwindow = (::windows::nano_window *)pcreatestruct->lpCreateParams;

         SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pwindow);

         pwindow->m_hwnd = hwnd;

      }
      else
      {

         pwindow = (::windows::nano_window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      }

      if (!pwindow)
      {

         return DefWindowProc(hwnd, msg, wParam, lParam);

      }

      return pwindow->window_procedure(msg, wParam, lParam);

   }



   void nano_window::create()
   {


      if (!g_bNanoWindowClassRegistered)
      {

         register_nano_window_class();

      }

      wstring wstrTitle(m_pinterface->m_strTitle);

      auto hinstanceWndProc = nano_message_box_hinstance();

      HWND hwnd = CreateWindowEx(
         m_pinterface->m_bTopMost ? WS_EX_TOPMOST : 0,
         _T(NANO_WINDOW_CLASS),
         wstrTitle,
         WS_POPUP,
         m_pinterface->m_rectangle.left,
         m_pinterface->m_rectangle.top,
         m_pinterface->m_rectangle.width(),
         m_pinterface->m_rectangle.height(),
         NULL, NULL, hinstanceWndProc, this);

      if (hwnd == NULL)
      {
         throw ::exception(error_failed, "Failed to create nano message box window.");
         return;
      }


   }


   void nano_window::on_char(int iChar)
   {

      m_pinterface->on_char(iChar);

   }


   void nano_window::_draw(HDC hdc)
   {

      GetWindowRect(m_hwnd, (LPRECT) & m_pinterface->m_rectangle);

      HGDIOBJ hbrushOld = ::GetCurrentObject(hdc, OBJ_BRUSH);
      HGDIOBJ hfontOld = ::GetCurrentObject(hdc, OBJ_FONT);
      HGDIOBJ hpenOld = ::GetCurrentObject(hdc, OBJ_PEN);

      {

         auto pnanodevice = __new(::windows::nano_device(hdc));

         m_pinterface->draw(pnanodevice);

      }

      ::SelectObject(hdc, hpenOld);
      ::SelectObject(hdc, hfontOld);
      ::SelectObject(hdc, hbrushOld);

   }


   //bool nano_window::is_active()
   //{

   //   return m_pm_bNcActive;

   //}


   //void nano_window::draw_children(HDC hdc)
   //{

   //   for (auto & pchild: m_childa)
   //   {

   //      pchild->on_draw(hdc);

   //   }

   //}

   void nano_window::delete_drawing_objects()
   {

      //if (m_hbrushWindow)
      //{

      //   ::DeleteObject(m_hbrushWindow);

      //   m_hbrushWindow = nullptr;

      //}

      //if (m_hpenBorder)
      //{

      //   ::DeleteObject(m_hpenBorder);

      //   m_hpenBorder = nullptr;

      //}


      //if (m_hpenBorderFocus)
      //{

      //   ::DeleteObject(m_hpenBorderFocus);

      //   m_hpenBorderFocus = nullptr;

      //}

      m_pinterface->delete_drawing_objects();

   }


   bool nano_window::get_dark_mode()
   {

      return !_is_light_theme();

   }


   void nano_window::create_drawing_objects()
   {

      //if (m_hfont == nullptr)
      //{

      //   HDC hdc = ::GetDC(m_hwnd);
      //   int nHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);
      //   m_hfont = ::CreateFontW(nHeight, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
      //                           CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_SWISS, L"Segoe UI");
      //   ::ReleaseDC(m_hwnd, hdc);

      //}

      //bool bDarkMode = get_dark_mode();

      //if (bDarkMode)
      //{

      //   m_crWindow = RGB(0, 0, 0);
      //   m_crText = RGB(255, 255, 255);
      //   m_crFocus = RGB(2, 128, 255);

      //} else
      //{

      //   m_crWindow = RGB(255, 255, 255);
      //   m_crText = RGB(0, 0, 0);
      //   m_crFocus = RGB(1, 64, 128);

      //}

      //m_hbrushWindow = CreateSolidBrush(m_crWindow);
      //m_hpenBorder = CreatePen(PS_SOLID, 1, m_crText);
      //m_hpenBorderFocus = CreatePen(PS_SOLID, 1, m_crFocus);

      m_pinterface->create_drawing_objects();

   }

   void nano_window::update_drawing_objects()
   {

      delete_drawing_objects();
      create_drawing_objects();


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

      //SetCapture(m_hwnd);

      //m_atomLeftButtonDown = hit_test(x, y);

      //if (m_pdragmove && m_atomLeftButtonDown == e_dialog_result_none)
      //{

      //   m_pdragmove->m_bLButtonDown = true;

      //   m_pdragmove->m_bDrag = false;

      //   point_i32 pointCursor(x, y);

      //   pointCursor += m_rectangle.origin();

      //   m_pdragmove->m_pointLButtonDown = pointCursor;

      //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

      //   return;

      //}

      m_pinterface->on_left_button_down(pmouse);

   }


   void nano_window::on_left_button_up(::user::mouse * pmouse)
   {

      //ReleaseCapture();

      //if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
      //{

      //   m_pdragmove->m_bLButtonDown = false;

      //   m_pdragmove->m_bDrag = false;

      //   return;

      //}

      //m_atomLeftButtonUp = hit_test(x, y);

      //if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
      //{

      //   m_atomResult = m_atomLeftButtonUp;

      //   on_click(m_atomResult);

      //}

      m_pinterface->on_left_button_up(pmouse);

   }

   void nano_window::on_mouse_move(::user::mouse * pmouse)
   {

      //if (m_pdragmove && m_pdragmove->m_bLButtonDown)
      //{

      //   ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

      //   if (!m_pdragmove->m_bDrag)
      //   {

      //      m_pdragmove->m_bDrag = true;

      //      point_i32 pointCursor(x, y);

      //      pointCursor += m_rectangle.origin();

      //      auto point = pointCursor - m_pdragmove->m_sizeLButtonDownOffset;

      //      move_to(pmouse);

      //      m_pdragmove->m_bDrag = false;

      //   }

      //   return;

      //}

      m_pinterface->on_mouse_move(pmouse);

   }


   void nano_window::on_right_button_down(::user::mouse * pmouse)
   {

      //SetCapture(m_hwnd);

      //m_atomLeftButtonDown = hit_test(x, y);

      //if (m_pdragmove && m_atomLeftButtonDown == e_dialog_result_none)
      //{

      //   m_pdragmove->m_bLButtonDown = true;

      //   m_pdragmove->m_bDrag = false;

      //   point_i32 pointCursor(x, y);

      //   pointCursor += m_rectangle.origin();

      //   m_pdragmove->m_pointLButtonDown = pointCursor;

      //   m_pdragmove->m_sizeLButtonDownOffset = m_pdragmove->m_pointLButtonDown - m_rectangle.origin();

      //   return;

      //}

      m_pinterface->on_right_button_down(pmouse);

   }


   void nano_window::on_right_button_up(::user::mouse * pmouse)
   {

      //ReleaseCapture();

      //if (m_pdragmove && (m_pdragmove->m_bLButtonDown || m_pdragmove->m_bDrag))
      //{

      //   m_pdragmove->m_bLButtonDown = false;

      //   m_pdragmove->m_bDrag = false;

      //   return;

      //}

      //m_atomLeftButtonUp = hit_test(x, y);

      //if (m_atomLeftButtonUp == m_atomLeftButtonDown && m_atomLeftButtonUp != e_dialog_result_none)
      //{

      //   m_atomResult = m_atomLeftButtonUp;

      //   on_click(m_atomResult);

      //}

      m_pinterface->on_right_button_up(pmouse);

   }



   ::atom nano_window::get_result()
   {

      return m_pinterface->get_result();

   }




   //nano_child * nano_window::hit_test(const ::point_i32 & point)
   //{

   //   return m_pinterface->hit_test(point);

   //}


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


   bool nano_window::_is_light_theme() 
   {

      DWORD dwBuffer;

      DWORD dwSize = sizeof(dwBuffer);

      auto res = RegGetValueW(
         HKEY_CURRENT_USER,
         L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
         L"AppsUseLightTheme",
         RRF_RT_REG_DWORD, // expected value type
         nullptr,
         &dwBuffer,
         &dwSize);

      if (res != ERROR_SUCCESS) 
      {

         throw ::exception(error_failed);

      }

      return dwBuffer != FALSE;

   }


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

            on_create();

         }
            break;
         case WM_CHAR:
         {
            on_char((int) wparam);
            return 0;
         }
            break;
         case WM_LBUTTONDOWN:
         {
            
            POINT point{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
            
            ::ClientToScreen(m_hwnd, &point);

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = point;

            on_left_button_down(pmouse);

         }
            break;
         case WM_MOUSEMOVE:
         {

            POINT point{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            ::ClientToScreen(m_hwnd, &point);

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = point;

            on_mouse_move(pmouse);

         }
            break;
         case WM_LBUTTONUP:
         {

            POINT point{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            ::ClientToScreen(m_hwnd, &point);

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = point;

            on_left_button_up(pmouse);

         }
            break;
         case WM_RBUTTONDOWN:
         {

            POINT point{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            ::ClientToScreen(m_hwnd, &point);

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = point;

            on_right_button_down(pmouse);

         }
         break;
         case WM_RBUTTONUP:
         {

            POINT point{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

            ::ClientToScreen(m_hwnd, &point);

            auto pmouse = __create_new < ::user::mouse >();

            pmouse->m_point = point;

            on_right_button_up(pmouse);

         }
         break;
         case WM_ERASEBKGND:
            return 1;
         case WM_PAINT:
            {
               PAINTSTRUCT paintstruct{};
               HDC hdcWindow = BeginPaint(m_hwnd, &paintstruct);

               HDC hdc = ::CreateCompatibleDC(hdcWindow);

               ::rectangle_i32 rectangleClient;

               ::GetClientRect(m_hwnd, (LPRECT) &rectangleClient);

               HBITMAP hbitmap = ::CreateCompatibleBitmap(hdcWindow, rectangleClient.width(), rectangleClient.height());

               HGDIOBJ hbitmapOld = ::SelectObject(hdc, hbitmap);

               _draw(hdc);


               ::BitBlt(hdcWindow, 0, 0, rectangleClient.width(), rectangleClient.height(),
                  hdc, 0, 0, SRCCOPY);

               hbitmapOld = ::SelectObject(hdc, hbitmapOld);

               ::DeleteDC(hdc);
               EndPaint(m_hwnd, &paintstruct);
            }
            break;
         case WM_NCACTIVATE:
         {
            LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
            m_pinterface->m_bNcActive = wparam != 0;
            redraw();

            return lresult;

         }
         case WM_ACTIVATE:
         {

            LRESULT lresult = DefWindowProc(m_hwnd, message, wparam, lparam);

            return lresult;

         }
         case WM_FONTCHANGE:
         {

            redraw();

         }
         break;
         case WM_SETTINGCHANGE:
         {

            string strLparamString;

            if (wparam == 0)
            {

               strLparamString = (const WCHAR *)(LPARAM(lparam));

            }

            if(strLparamString == "ImmersiveColorSet")
            {

               update_drawing_objects();

               redraw();

            }
            else if (wparam == SPI_SETWORKAREA)
            {

               redraw();

            }

         }
         break;

         default:
         {

            return DefWindowProc(m_hwnd, message, wparam, lparam);

         }

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

      ShowWindow(m_hwnd, SW_SHOW);

      UpdateWindow(m_hwnd);

   }


   void nano_window::message_loop()
   {

      MSG msg;

      while (::task_get_run() && GetMessage(&msg, NULL, 0, 0) > 0)
      {

         TranslateMessage(&msg);

         DispatchMessage(&msg);

         if (m_bDestroy)
         {

            ::DestroyWindow(m_hwnd);

            while (PeekMessage(&msg, NULL, 0, 0, TRUE))
            {

               TranslateMessage(&msg);

               DispatchMessage(&msg);

            }

            break;

         }

      }

   }

   void nano_window::add_child(nano_child * pchild)
   {

      m_pinterface->add_child(pchild);

   }


   void nano_window::redraw()
   {

      ::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

   }


   void nano_window::destroy()
   {

      m_bDestroy = true;

      PostMessage(m_hwnd, WM_ENTERIDLE, 0, 0);

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


   void nano_window::on_click(const ::atom & atomParam, ::user::mouse * pmouse)
   {

      auto atom = atomParam;

      //fork([this, atom, pmouse]()
         //{
         
            m_pinterface->on_click(atom, pmouse);

         //}, { pmouse });

   }


   void nano_window::on_right_click(const ::atom & atomParam, ::user::mouse * pmouse)
   {

      auto atom = atomParam;

      //fork([this, atom, pmouse]()
        // {

            m_pinterface->on_right_click(atom, pmouse);

         //}, {pmouse});


   }


   void nano_window::move_to(const ::point_i32 & point)
   {

      ::SetWindowPos(m_hwnd, nullptr, point.x, point.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

      ::GetWindowRect(m_hwnd, (RECT * ) & m_pinterface->m_rectangle);

   }


   void nano_window::get_client_rectangle(::rectangle_i32 & rectangle)
   {

      ::GetClientRect(m_hwnd, (LPRECT) & rectangle);

   }


   void nano_window::get_window_rectangle(::rectangle_i32 & rectangle)
   {

      ::GetWindowRect(m_hwnd, (LPRECT)&rectangle);

   }


   void nano_window::set_capture()
   {

      SetCapture(m_hwnd);

   }


   bool nano_window::has_capture() const
   {

      return ::GetCapture() == m_hwnd;

   }


   void nano_window::release_capture()
   {

      ReleaseCapture();

   }


   void nano_window::set_cursor(enum_cursor ecursor)
   {

      if(ecursor == e_cursor_move)
      {

         ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

      }

   }



   ::size_i32 nano_window::get_main_screen_size()
   {

      HWND hwndDesktop = ::GetDesktopWindow();

      if (!hwndDesktop)
      {

         return nano_window_implementation::get_main_screen_size();

      }

      RECT r;

      ::GetWindowRect(hwndDesktop, &r);

      return { r.right -r.left, r.bottom - r.top };


   }

   


} // namespace windows



