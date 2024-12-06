// Created by camilo on 2024-09-13 15:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
#include "windowing.h"
#include "acme/platform/application.h"
#include "acme/user/user/mouse.h"


namespace windows
{


   extern windowing * g_pwindowing;


   window::window()
   {
      m_bMovingNow = false;
      m_bSizeMoveMode = false;
      m_hwnd = nullptr;
      m_hmenuSystem = nullptr;
      m_bDefaultSystemMenu = true;
   }


   window::~window()
   {

   }

   bool window::on_window_procedure(LRESULT & lresult, UINT message, WPARAM wparam, LPARAM lparam)
   {

      if (m_iDebugAtom == 123)
      {

         printf_line("123");

      }

      if (message == WM_ENTERSIZEMOVE)
      {
         m_bSizeMoveMode = true;
      }
      if (m_bSizeMoveMode)
      {

         lresult = 1;
         double Δx = 0.;
         double Δy= 0.;

         ::SetCursor(::LoadCursor(nullptr, IDC_SIZEALL));

         if (message == WM_LBUTTONUP)
         {
            m_bSizeMoveMode = false;
            ::ReleaseCapture();

         }
         else if (message == WM_KEYDOWN)
         {

            if (wparam == VK_ESCAPE)
            {

               m_bSizeMoveMode = false;
               ::ReleaseCapture();

            }
            else if(wparam == VK_RIGHT)
            {
               Δx = 1.0;
            }
            else if (wparam == VK_LEFT)
            {
               Δx = -1.0;
            }
            else if (wparam == VK_UP)
            {
               Δy = -1.0;
            }
            else if (wparam == VK_DOWN)
            {
               Δy = 1.0;
            }

            if (Δx || Δy)
            {

               if (m_timeLastSizeMove.elapsed() < 300_ms)
               {

                  if (m_dVelocity >= 8.0)
                  {

                     m_dVelocity = 8.0;

                  }
                  else
                  {

                     m_dVelocity += 0.1;

                  }

               }
               else
               {

                  m_dVelocity = 1.0;

               }
               Δx *= m_dVelocity;
               Δy *= m_dVelocity;

               RECT r;

               GetWindowRect(m_hwnd, &r);

               m_bMovingNow = true;

               auto x = (int)(r.left + Δx);

               auto y = (int)(r.top + Δy);

               SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
               m_bMovingNow = false;
               m_timeLastSizeMove.Now();

               
            }

            {
               POINT pointCursor{};
               RECT r{};
               GetWindowRect(m_hwnd, &r);
               pointCursor.x = r.left + m_pointSizeMoveStart.x();
               pointCursor.y = r.top + m_pointSizeMoveStart.y();
               ::SetCursorPos(pointCursor.x, pointCursor.y);
            }


         }
         else if (message == WM_MOUSEMOVE)
         {

            if (m_timeLastSizeMove.elapsed() > 300_ms
               && !m_bMovingNow)
            {

               POINT pointCursor{};
               ::GetCursorPos(&pointCursor);
               auto x = pointCursor.x - m_pointSizeMoveStart.x();
               auto y = pointCursor.y - m_pointSizeMoveStart.y();


               //RECT r;

               //GetWindowRect(m_hwnd, &r);
               m_bMovingNow = true;
               SetWindowPos(m_hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
               //m_timeLastSizeMove.Now();
               m_bMovingNow = false;
            }


         }


         if (message == WM_WINDOWPOSCHANGED || message == WM_MOUSEMOVE)
         {

         }
         else if (message == WM_WINDOWPOSCHANGING)
         {

         }
         else
         {

            //lresult = DefWindowProc(m_hwnd, message, wparam, lparam);

         }

         if (message == WM_MOVE || message == WM_SIZE || message==WM_WINDOWPOSCHANGED)
         {

            return false;

         }

         if (message == WM_EXITSIZEMOVE)
         {

            m_bSizeMoveMode = false;

         }

         return true;


      }

      if (m_bDefaultSystemMenu)
      {

         if (message == WM_INITMENU)
         {

            if (_on_default_system_menu_init_menu(lresult, wparam))
            {

               return true;

            }

         }
         else if (message == WM_COMMAND)
         {

            if (_on_default_system_menu_command(lresult, wparam, lparam))
            {

               return true;

            }

         }

      }

      return false;


   }

   bool window::_on_default_system_menu_init_menu(LRESULT & lresult, WPARAM wparam)
   {

      auto hmenu = (HMENU)wparam;

      auto hmenuSystem = m_hmenuSystem;

      if (hmenu != hmenuSystem)
      {

         return false;

      }

      auto hwnd = m_hwnd;

      hmenuSystem = hmenu;

      //::DefWindowProc(m_hwnd, WM_INITMENU, wparam, 0);

      auto cMenuItemCount = ::GetMenuItemCount(hmenu);

      auto iLast = ::GetMenuItemCount(hmenuSystem) - 1;

      auto idLast = GetMenuItemID(hmenuSystem, iLast);

      //if (idLast == -1)
      //{

      //   hmenuSystem = GetSubMenu(hmenu, 0);

      //   cMenuItemCount = ::GetMenuItemCount(hmenuSystem);

      //   iLast = ::GetMenuItemCount(hmenuSystem) - 1;

      //   idLast = GetMenuItemID(hmenuSystem, iLast);

      //}

      auto iOneBeforeLast = iLast - 1;

      auto idOneBeforeLast = GetMenuItemID(hmenuSystem, iOneBeforeLast);

      if (idLast == SC_CLOSE && idOneBeforeLast == 0)
      {

         // Seems like System Menu

         {

            MENUITEMINFOW menu_item_info{};
            menu_item_info.cbSize = sizeof(MENUITEMINFO);

            menu_item_info.fMask = MIIM_TYPE;
            menu_item_info.fType = MFT_SEPARATOR;

            //menu_item_info.hSubMenu = submenu.handle();

            //menu_item_info.dwTypeData = const_cast<wchar_t *>(L"About...");
            //menu_item_info.cch = wcslen(const_cast<wchar_t *>(menu_item_info.dwTypeData));

            InsertMenuItemW(hmenuSystem, iOneBeforeLast, TRUE, &menu_item_info);

         }

         {

            MENUITEMINFOW menu_item_info{};
            menu_item_info.cbSize = sizeof(MENUITEMINFO);

            menu_item_info.fMask = MIIM_TYPE | MIIM_ID;
            menu_item_info.fType = MFT_STRING;

            //menu_item_info.hSubMenu = submenu.handle();

            menu_item_info.wID = 123;
            menu_item_info.dwTypeData = const_cast<wchar_t *>(L"About...");
            menu_item_info.cch = (UINT)wcslen(const_cast<wchar_t *>(menu_item_info.dwTypeData));

            InsertMenuItemW(hmenuSystem, iOneBeforeLast + 1, TRUE, &menu_item_info);

         }

         if (!(GetWindowLong(hwnd, GWL_STYLE) & WS_MINIMIZEBOX))
         {

            ::DeleteMenu(hmenuSystem, SC_MINIMIZE, MF_BYCOMMAND);

         }

         if (!(GetWindowLong(hwnd, GWL_STYLE) & WS_MAXIMIZEBOX))
         {

            ::DeleteMenu(hmenuSystem, SC_MAXIMIZE, MF_BYCOMMAND);

         }

         if (!(GetWindowLong(hwnd, GWL_STYLE) & WS_MINIMIZEBOX)
            && !(GetWindowLong(hwnd, GWL_STYLE) & WS_MAXIMIZEBOX))
         {

            ::DeleteMenu(hmenuSystem, SC_RESTORE, MF_BYCOMMAND);

         }

         if (!(GetWindowLong(hwnd, GWL_STYLE) & WS_THICKFRAME))
         {

            ::DeleteMenu(hmenuSystem, SC_SIZE, MF_BYCOMMAND);

         }

         lresult = 0;

         return true;

      }

      return false;

   }
   

   bool window::_on_default_system_menu_command(LRESULT & lresult,WPARAM wparam, LPARAM lparam)
   {

      int wmId = LOWORD(wparam);

      if (wmId == 123)
      {

         application()->show_about_box();

         lresult = 0;

         return true;

      }
      else if (wmId == SC_MOVE)
      {
         m_dVelocity = 0.;
         ::SetCapture(m_hwnd);
         POINT pointCursor{};
         ::GetCursorPos(&pointCursor);
         RECT r{};
         ::GetWindowRect(m_hwnd, &r);
         m_pointSizeMoveStart.x() = pointCursor.x - r.left;
         m_pointSizeMoveStart.y() = pointCursor.y - r.top;
         ::SetCursor(::LoadCursor(nullptr, IDC_SIZEALL));
         m_bSizeMoveMode = true;

         //PostMessage(m_hwnd, WM_SYSCOMMAND, SC_MOVE, 0);
         lresult = 0;
         return true;

      }
      else if (wmId == SC_CLOSE)
      {

         SendMessage(m_hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
         lresult = 0;
         return true;

      }

      return false;

   }


   void window::_defer_show_system_menu(::user::mouse * pmouse)
   {

      auto hmenu = GetSystemMenu(m_hwnd, true);
      m_hmenuSystem = GetSystemMenu(m_hwnd, false);
      //SetForegroundWindow(hwnd);
      TrackPopupMenu(m_hmenuSystem,
         TPM_LEFTALIGN | TPM_TOPALIGN,
         pmouse->m_pointAbsolute.x(),
         pmouse->m_pointAbsolute.y(),
         0,
         m_hwnd, NULL);
      //PostMessage(hwnd, WM_NULL, 0, 0);

   }


   // Step 4: the Window Procedure
   LRESULT CALLBACK window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {

      ::windows::window * pwindow = nullptr;

      if (msg == WM_NCCREATE)
      {

         CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;

         pwindow = (::windows::window *)pcreatestruct->lpCreateParams;

         ///SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pwindow);

         ::windows::g_pwindowing->m_windowmap[(::oswindow)hwnd] = pwindow;

         pwindow->m_hwnd = hwnd;

      }
      else
      {

         pwindow = ::windows::g_pwindowing->m_windowmap[(::oswindow)hwnd];

         //pwindow = (::windows::window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      }

      if (!pwindow)
      {

         return DefWindowProc(hwnd, msg, wParam, lParam);

      }

      LRESULT lresult = 0;

      if (pwindow->on_window_procedure(lresult, msg, wParam, lParam))
      {

         return lresult;

      }
      else
      {

         lresult = DefWindowProc(hwnd, msg, wParam, lParam);

      }

      return lresult;

   }


   CLASS_DECL_ACME HINSTANCE get_window_procedure_hinstance()
   {

      HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");

      if (hinstanceWndProc == nullptr)
      {

         hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);

      }

      return hinstanceWndProc;

   }



} // namespace windows


