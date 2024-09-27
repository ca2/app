// Created by camilo on 2022-01-21 05:05 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "device.h"
#include "window.h"
#include "user.h"
#include "acme/parallelization/task.h"
#include "acme/nano/nano.h"
#include "acme/nano/user/button.h"
#include "acme/nano/user/message_box.h"
#include "acme/nano/user/window.h"
#include "acme/user/user/mouse.h"


bool _c_simple_message_loop_step();

CLASS_DECL_ACME string task_get_name();
CLASS_DECL_ACME void task_set_name(const char* pszName);


class CLASS_DECL_ACME scoped_task_name
{
public:

   ::string       m_strTask;

   scoped_task_name(const ::string& strTask)
   {

      m_strTask = ::task_get_name();

      ::task_set_name(strTask);

   }

   ~scoped_task_name()
   {

      ::task_set_name(m_strTask);

   }


};


namespace windows
{



   namespace nano
   {


      namespace user
      {

         window::window()
         {
            m_bSizeMoveMode = false;
            //      m_bDestroy = false;
            m_hwnd = nullptr;
            m_hmenuSystem = nullptr;

         }


         window::~window()
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

            ::windows::nano::user::window* pwindow = nullptr;

            if (msg == WM_NCCREATE)
            {

               CREATESTRUCT* pcreatestruct = (CREATESTRUCT*)lParam;

               pwindow = (::windows::nano::user::window*)pcreatestruct->lpCreateParams;

               SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pwindow);

               pwindow->m_hwnd = hwnd;

            }
            else
            {

               pwindow = (::windows::nano::user::window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

            }

            if (!pwindow)
            {

               return DefWindowProc(hwnd, msg, wParam, lParam);

            }

            return pwindow->window_procedure(msg, wParam, lParam);

         }



         void window::create()
         {


            if (!g_bNanoWindowClassRegistered)
            {

               register_nano_window_class();

            }

            wstring wstrTitle(m_pinterface->m_strTitle);

            auto hinstanceWndProc = nano_message_box_hinstance();

            m_ptask = ::get_task();

            HWND hwnd = CreateWindowEx(
               m_pinterface->m_bTopMost ? WS_EX_TOPMOST : 0,
               _T(NANO_WINDOW_CLASS),
               wstrTitle,
               WS_POPUP | WS_SYSMENU,
               m_pinterface->m_rectangle.left(),
               m_pinterface->m_rectangle.top(),
               m_pinterface->m_rectangle.width(),
               m_pinterface->m_rectangle.height(),
               NULL, NULL, hinstanceWndProc, this);

            if (hwnd == NULL)
            {
               throw ::exception(error_failed, "Failed to create nano message box window.");
               return;
            }

            nanowindowimplementationa().add(this);

         }


         void window::on_char(int iChar)
         {

            m_pinterface->on_char(iChar);

         }


         void window::_draw(HDC hdc)
         {

            GetWindowRect(m_hwnd, (LPRECT)&m_pinterface->m_rectangle);

            HGDIOBJ hbrushOld = ::GetCurrentObject(hdc, OBJ_BRUSH);
            HGDIOBJ hfontOld = ::GetCurrentObject(hdc, OBJ_FONT);
            HGDIOBJ hpenOld = ::GetCurrentObject(hdc, OBJ_PEN);

            {

               auto pnanodevice = ::place(new ::windows::nano::graphics::device(hdc));

               m_pinterface->draw(pnanodevice);

            }

            ::SelectObject(hdc, hpenOld);
            ::SelectObject(hdc, hfontOld);
            ::SelectObject(hdc, hbrushOld);

         }


         //bool window::is_active()
         //{

         //   return m_pm_bNcActive;

         //}


         //void window::draw_children(HDC hdc)
         //{

         //   for (auto & pchild: m_childa)
         //   {

         //      pchild->on_draw(hdc);

         //   }

         //}

         void window::delete_drawing_objects()
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


         bool window::get_dark_mode()
         {

            return !_is_light_theme();

         }


         void window::create_drawing_objects()
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

         void window::update_drawing_objects()
         {

            delete_drawing_objects();
            create_drawing_objects();


         }


         //::atom window::hit_test(int x, int y)
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

         void window::on_left_button_down(::user::mouse* pmouse)
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


         void window::on_left_button_up(::user::mouse* pmouse)
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

         void window::on_mouse_move(::user::mouse* pmouse)
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


         void window::on_right_button_down(::user::mouse* pmouse)
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


         void window::on_right_button_up(::user::mouse* pmouse)
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



         ::payload window::get_result()
         {

            return m_pinterface->get_result();

         }




         //::nano::user::child * window::hit_test(const ::point_i32 & point, ::user::e_zorder ezorder)
         //{

         //   return m_pinterface->hit_test(point);

         //}


      //LRESULT CALLBACK ::nano::user::message_box::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
      //{
      //if (msg == WM_NCCREATE)
      //{
      //
      //   CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
      //   SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pcreatestruct->lpCreateParams);
      //
      //}
      //::nano::user::message_box * pwindow = (::nano::user::message_box *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
      //
      //if (!pwindow)
      //{
      //   return DefWindowProc(hwnd, msg, wParam, lParam);
      //}
      //return pwindow->window_procedure(msg, wParam, lParam);
      //
      //}



         bool window::_is_light_theme()
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


         LRESULT window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
         {

            {

               LRESULT lresult = 0;

               if (on_window_procedure(lresult, message, wparam, lparam))
               {

                  return lresult;

               }

            }

            switch (message)
            {
            case WM_COMMAND:
            {
              /* ::pointer < ::windows::nano::user::user > pnanouser = nano()->user();

               LRESULT lresult = 0;

               if (pnanouser->_on_command(lresult, m_hwnd, wparam, lparam))
               {

                  return lresult;

               }*/

               return DefWindowProc(m_hwnd, message, wparam, lparam);

            }

            break;
            case WM_SYSCOMMAND:
            {

               return DefWindowProc(m_hwnd, message, wparam, lparam);

            }

            break;
            case WM_CLOSE:
               //DestroyWindow(m_hwnd);
               m_pinterface->on_click(e_dialog_result_cancel, nullptr);
               return 0;
               break;
            case WM_NCDESTROY:
               break;
            //case WM_INITMENU:
            //   {
            //   ::pointer < ::windows::nano::user::user > pnanouser = nano()->user();

            //   LRESULT lresult = 0;

            //   if (pnanouser->_on_default_system_menu_init_menu(lresult, m_hwnd, m_hmenuSystem, wparam))
            //   {

            //      return lresult;

            //   }

            //   }
            //   break;
            case WM_DESTROY:
               //PostQuitMessage(0);
               nanowindowimplementationa().erase(this);
               break;
            case WM_CREATE:
            {
               update_drawing_objects();

               on_create();

            }
            break;
            case WM_CHAR:
            {
               on_char((int)wparam);
               return 0;
            }
            break;
            case WM_LBUTTONDOWN:
            {

               POINT point{ i32_x(lparam), i32_y(lparam) };

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = { point.x, point.y };

               ::ClientToScreen(m_hwnd, &point);

               pmouse->m_pointAbsolute = { point.x, point.y };

               on_left_button_down(pmouse);

            }
            break;
            case WM_MOUSEMOVE:
            {

               POINT point{ i32_x(lparam), i32_y(lparam) };

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = { point.x, point.y };

               ::ClientToScreen(m_hwnd, &point);

               pmouse->m_pointAbsolute = { point.x, point.y };

               on_mouse_move(pmouse);

            }
            break;
            case WM_LBUTTONUP:
            {

               POINT point{ i32_x(lparam), i32_y(lparam) };

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = { point.x, point.y };

               ::ClientToScreen(m_hwnd, &point);

               pmouse->m_pointAbsolute = { point.x, point.y };

               on_left_button_up(pmouse);

            }
            break;
            case WM_RBUTTONDOWN:
            {

               POINT point{ i32_x(lparam), i32_y(lparam) };

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = { point.x, point.y };

               ::ClientToScreen(m_hwnd, &point);

               pmouse->m_pointAbsolute = { point.x, point.y };

               on_right_button_down(pmouse);

            }
            break;
            case WM_RBUTTONUP:
            {

               POINT point{ i32_x(lparam), i32_y(lparam) };

               auto pmouse = __create_new < ::user::mouse >();

               pmouse->m_pointHost = { point.x, point.y };

               ::ClientToScreen(m_hwnd, &point);

               pmouse->m_pointAbsolute = { point.x, point.y };

               on_right_button_up(pmouse);

            }
            break;
            case WM_ERASEBKGND:
               return 1;
            case WM_MOUSEACTIVATE:
               return MA_ACTIVATE;
            case WM_PAINT:
            {

               PAINTSTRUCT paintstruct{};

               HDC hdcWindow = BeginPaint(m_hwnd, &paintstruct);

               HDC hdc = ::CreateCompatibleDC(hdcWindow);

               ::rectangle_i32 rectangleX;

               ::GetClientRect(m_hwnd, (LPRECT)&rectangleX);

               HBITMAP hbitmap = ::CreateCompatibleBitmap(hdcWindow, rectangleX.width(), rectangleX.height());

               HGDIOBJ hbitmapOld = ::SelectObject(hdc, hbitmap);

               _draw(hdc);


               ::BitBlt(hdcWindow, 0, 0, rectangleX.width(), rectangleX.height(),
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

               if (wparam > 0)
               {

                  ::SetFocus(m_hwnd);

               }

               return 0;

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

                  strLparamString = (const WCHAR*)(LPARAM(lparam));

               }

               if (strLparamString == "ImmersiveColorSet")
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

         void window::display()
         {

            ::ShowWindow(m_hwnd, SW_SHOW);

            ::UpdateWindow(m_hwnd);

            ::BringWindowToTop(m_hwnd);

         }



         void window::add_child(::nano::user::child* pchild)
         {

            m_pinterface->add_child(pchild);

         }


         void window::redraw()
         {

            ::RedrawWindow(m_hwnd, nullptr, nullptr, RDW_UPDATENOW | RDW_INVALIDATE);

         }


         //void window::_destroy_window()
         //{
         //
         //}


         void window::destroy()
         {

            user_post([this]()
               {

                  //::ShowWindow(m_hwnd, SW_HIDE);

                  ::DestroyWindow(m_hwnd);

                  process_messages();

               });

         }


         //
         //LRESULT window::window_procedure(UINT message, WPARAM wparam, LPARAM lparam)
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
         //      on_left_button_down(i32_x(lparam), i32_y(lparam));
         //      break;
         //   case WM_LBUTTONUP:
         //   {
         //      on_left_button_up(i32_x(lparam), i32_y(lparam));
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


         void window::on_click(const ::payload& payloadParam, ::user::mouse* pmouse)
         {

            auto payload = payloadParam;

            //fork([this, atom, pmouse]()
               //{

            m_pinterface->on_click(payload, pmouse);

            //}, { pmouse });

         }


         void window::on_right_click(const ::payload& payloadParam, ::user::mouse* pmouse)
         {

            auto payload = payloadParam;

            //fork([this, atom, pmouse]()
              // {

            m_pinterface->on_right_click(payload, pmouse);

            //}, {pmouse});


         }


         void window::move_to(const ::point_i32& point)
         {

            ::SetWindowPos(m_hwnd, nullptr, point.x(), point.y(), 0, 0, SWP_NOSIZE | SWP_NOZORDER);

            ::GetWindowRect(m_hwnd, (RECT*)&m_pinterface->m_rectangle);

         }


         ::point_i32 window::try_absolute_mouse_position(const ::point_i32& point)
         {

            return point;

         }


         void window::get_client_rectangle(::rectangle_i32& rectangle)
         {

            ::GetClientRect(m_hwnd, (LPRECT)&rectangle);

         }


         void window::get_window_rectangle(::rectangle_i32& rectangle)
         {

            ::GetWindowRect(m_hwnd, (LPRECT)&rectangle);

         }


         void window::set_capture()
         {

            SetCapture(m_hwnd);

         }


         bool window::has_capture() const
         {

            return ::GetCapture() == m_hwnd;

         }


         void window::release_capture()
         {

            ReleaseCapture();

         }


         void window::set_cursor(enum_cursor ecursor)
         {

            if (ecursor == e_cursor_move)
            {

               ::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));

            }

         }



         ::size_i32 window::get_main_screen_size()
         {

            HWND hwndDesktop = ::GetDesktopWindow();

            if (!hwndDesktop)
            {

               return ::nano::user::window_implementation::get_main_screen_size();

            }

            RECT r;

            ::GetWindowRect(hwndDesktop, &r);

            return { r.right - r.left, r.bottom - r.top };

         }


         void window::user_post(const ::procedure& procedure)
         {

            if (m_ptask)
            {

               m_ptask->post_procedure(procedure);

            }
            else
            {

               ::nano::user::window_implementation::user_post(procedure);

            }


         }


         void window::implementation_message_loop_step()
         {

            _c_simple_message_loop_step();

         }


         void window::defer_show_system_menu(const ::point_i32 & pointAbsolute)
         {

            //::pointer < ::windows::nano::user::user > pnanouser = nano()->user();

            //pnanouser->_defer_show_system_menu(m_hwnd, &m_hmenuSystem, pointAbsolute);

            _defer_show_system_menu(pointAbsolute);
            

         }


         void process_messages(bool bWait)
         {

            auto strThreadName = ::task_get_name();

            //auto pmessagebox = m_pinterface.cast < ::nano::user::message_box >();

            //::string strAbbreviation("window");

            //if (strType.contains("message_box"))
            //if (pmessagebox)
            //{
               //auto pmessagebox = m_pinterface.cast<nano::me
               /// @brief ////////123456789012345
               //strAbbreviation = "msgbx:" + pmessagebox->m_strMessage.left(20);

              // strAbbreviation = "msgbx:" + pmessagebox->m_strMessage;

            //}

            //scoped_task_name scopedtaskname(strAbbreviation);

            //::task_set_name("nanownd");

            MSG msg;

            while (bWait ? (::GetMessage(&msg, NULL, 0, 0) > 0) :
               (::PeekMessage(&msg, NULL, 0, 0, TRUE)))
            {

               TranslateMessage(&msg);

               DispatchMessage(&msg);

            }

         }


      } // namespace user


   } // namespace nano

} // namespace windows



