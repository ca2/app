// Created by camilo on 2024-09-13 15:58 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
#include "windowing.h"
#include "acme/platform/application.h"
#include "acme/user/user/interaction.h"
#include "acme/user/user/mouse.h"


namespace windows
{

      CLASS_DECL_ACME bool pre_process_window_procedure(::lresult &lresult,
                                                     HWND hwnd,
                                                     ::u32 message, ::wparam wparam, ::lparam lparam);



   extern windowing * g_pwindowing;


   window::window()
   {
      m_bMovingNow = false;
      m_bSizeMoveMode = false;
      //m_hwnd = nullptr;
      m_hmenuSystem = nullptr;
      m_bDefaultSystemMenu = true;
      m_wndprocDefault = nullptr;
   }


   window::~window()
   {

   }


   void* window::_WNDPROC_default() const
   {

      return m_wndprocDefault;

   }

   bool window::call_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam)
   {

      if (m_pacmeuserinteraction)
      {

         if (m_pacmeuserinteraction->_on_window_procedure(lresult, message, wparam, lparam))
         {

            return true;

         }

      }

      if (on_window_procedure(lresult, message, wparam, lparam))
      {

         return true;

      }

      if (m_wndprocDefault)
      {

         lresult =  ::CallWindowProcW(m_wndprocDefault, m_windowswindow.as_HWND(), message, wparam.m_wparam, lparam.m_lparam );

         return true;

      }

      return false;

   }


   ::i32 window::_on_non_client_hit_test(const ::i32_point& point)
   {

      auto rc = get_window_rectangle();

      const ::i32 grip = 8;

      bool left = point.x < rc.left + grip;
      bool right = point.x >= rc.right - grip;
      bool top = point.y < rc.top + grip;
      bool bottom = point.y >= rc.bottom - grip;

      if (top && left)
         return HTTOPLEFT;
      if (top && right)
         return HTTOPRIGHT;
      if (bottom && left)
         return HTBOTTOMLEFT;
      if (bottom && right)
         return HTBOTTOMRIGHT;

      if (left)
         return HTLEFT;
      if (right)
         return HTRIGHT;
      if (top)
         return HTTOP;
      if (bottom)
         return HTBOTTOM;
      RECT rcWindow;
      copy(rcWindow, rc);

      auto hwnd = ::as_HWND(this->operating_system_window());
      MapWindowPoints(nullptr, hwnd, (POINT *)&rcWindow, 2);

      ::i32_rectangle rectangleWindow2 = rcWindow;

      information("main_window WM_SIZE MapWindowPoints {}", rectangleWindow2);


      if (point.y < rc.top + abs(rectangleWindow2.top))
         return HTCAPTION;

      return HTCLIENT;


   }


   bool window::on_window_procedure(::lresult & lresult, ::u32 message, ::wparam wparam, ::lparam lparam)
   {

      if (m_iDebugAtom == 123)
      {

         printf_line("::windows::window::window_procedure");

      }

      if (m_pacmeuserinteraction && m_pacmeuserinteraction->m_bDefaultNcHitTest)
      {

         if(message == WM_NCHITTEST || message == WM_NCLBUTTONDOWN || message == WM_LBUTTONDOWN)
         {

            auto hwnd = ::as_HWND(this->operating_system_window());

            auto point = lparam.point();

            if (message == WM_LBUTTONDOWN)
            {

               ClientToScreen(hwnd, (POINT*) & point);

            }

            ::lparam lparamNcHitTest(point);

            ::i32 iHitTest = (::i32) DefWindowProcW(hwnd, WM_NCHITTEST, 0, lparamNcHitTest);

            if (iHitTest == HTCLIENT)
            {

               iHitTest = _on_non_client_hit_test(point);

            }

            //pt.x = GET_X_LPARAM(lparam);
            //pt.y = GET_Y_LPARAM(lparam);

            if (message == WM_NCHITTEST)
            {

               lresult = iHitTest;

               return true;

            }

            lresult = 0;

            if (message == HTCAPTION)
            {


            }
            else if (message == HTCLIENT)
            {

            }
            else
            {
               ::i32 iEdge = 0;
               switch (iHitTest)
               {
                  case HTBOTTOM:
                     iEdge= WMSZ_BOTTOM;
                     break;
                  case HTTOP:
                     iEdge = WMSZ_TOP;
                     break;
                  case HTLEFT:
                     iEdge = WMSZ_LEFT;
                     break;
                  case HTRIGHT:
                     iEdge = WMSZ_RIGHT;
                     break;

                  case HTBOTTOMRIGHT:
                     iEdge = WMSZ_BOTTOMRIGHT;
                     break;
                  case HTTOPRIGHT:
                     iEdge = WMSZ_TOPRIGHT;
                     break;
                  case HTBOTTOMLEFT:
                     iEdge = WMSZ_BOTTOMLEFT;
                     break;
                  case HTTOPLEFT:
                     iEdge = WMSZ_TOPLEFT;
                     break;
               }
               if (iEdge != 0)
               {
                  SendMessage(hwnd, WM_SYSCOMMAND, SC_SIZE | iEdge, 0);
               }
            }

            

         }


      }
      
      if (message == WM_CREATE)
      {

         auto hwnd = ::as_HWND(this->operating_system_window());

         lresult= DefWindowProc(hwnd, message, wparam, lparam);

         if (lresult == -1)
         {

            return true;

         }

         if (!on_window_create(lparam.raw_cast<void *>()))
         {

            lresult = -1;

            return true;

         }

         lresult = 0;

         return true;

      }
      else if (message == WM_SHOWWINDOW)
      {

         if (wparam)
         {

            if (defer_update_system_menu())
            {

               lresult = 1;

               //return true;

            }

         }

         on_window_show(wparam != FALSE, lparam.raw_cast<int>());

      }
      else if (message == WM_SIZE)
      {

         if (m_pacmeuserinteraction)
         {

            HICON hiconBig = (HICON)m_pacmeuserinteraction->m_pHICON_Big;

            HICON hiconSmall = (HICON)m_pacmeuserinteraction->m_pHICON_Small;

            if (hiconBig)
            {

               auto hwnd = ::as_HWND(this->operating_system_window());

               ::SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hiconBig);
            }


            if (hiconSmall)
            {

               auto hwnd = ::as_HWND(this->operating_system_window());

               ::SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hiconSmall);
            }

         }


         on_window_size(lparam.size());
         lresult = 0;
         return true;

      }
      // else
      // {
      //
      //    auto hwnd = ::as_HWND(this->operating_system_window());
      //
      //    lresult = DefWindowProcW(hwnd, message, wparam, lparam);
      //
      //    return true;
      // }


      else if (message == WM_MOUSEACTIVATE)
      {
         ::i32 iResult = 0;

         if (on_window_mouse_activate(iResult, ::as_operating_system_window(wparam.raw_cast<HWND>()),
            lparam.loword(), lparam.hiword()))
         {

            lresult = iResult;

            return true;

         }

      }
      else if (message == WM_ACTIVATE)
      {

         if (on_window_activate(wparam.loword(), wparam.hiword(), ::as_operating_system_window(lparam.raw_cast<HWND>())))
         {

            lresult = 0;

            return true;

         }

      }
      else if (message == WM_ENTERSIZEMOVE)
      {
         m_bSizeMoveMode = true;
         if (get_window_style() & WS_POPUP)
         {

            information("WM_ENTERSIZEMOVE window style has WS_POPUP");

         }
         else
         {

            information("WM_ENTERSIZEMOVE window style doesn't have WS_POPUP");
         }
      }
      if (m_bSizeMoveMode)
      {

         bool bRet = false;

         lresult = 1;
         ::f64 Δx = 0.;
         ::f64 Δy= 0.;

         ::SetCursor(::LoadCursor(nullptr, IDC_SIZEALL));

         if (message == WM_LBUTTONUP)
         {
            m_bSizeMoveMode = false;
            ::ReleaseCapture();
            bRet = true;
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

               auto hwnd =::as_HWND(this->operating_system_window());

               GetWindowRect(hwnd, &r);

               m_bMovingNow = true;

               auto x = (::i32)(r.left + Δx);

               auto y = (::i32)(r.top + Δy);

               SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
               m_bMovingNow = false;
               m_timeLastSizeMove.Now();

               
            }

            {

               auto hwnd = ::as_HWND(this->operating_system_window());

               POINT pointCursor{};
               RECT r{};
               GetWindowRect(hwnd, &r);
               pointCursor.x = r.left + m_pointSizeMoveStart.x;
               pointCursor.y = r.top + m_pointSizeMoveStart.y;
               ::SetCursorPos(pointCursor.x, pointCursor.y);
            }
            bRet = true;

         }
         else if (message == WM_MOUSEMOVE)
         {

            if (m_timeLastSizeMove.elapsed() > 300_ms
               && !m_bMovingNow)
            {

               POINT pointCursor{};
               ::GetCursorPos(&pointCursor);
               auto x = pointCursor.x - m_pointSizeMoveStart.x;
               auto y = pointCursor.y - m_pointSizeMoveStart.y;


               //RECT r;

               //GetWindowRect(m_hwnd, &r);
               m_bMovingNow = true;
               auto hwnd = ::as_HWND(this->operating_system_window());


               SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
               //m_timeLastSizeMove.Now();
               m_bMovingNow = false;
            }
            bRet = true;

         }


         // if (message == WM_WINDOWPOSCHANGED || message == WM_MOUSEMOVE)
         // {
         //
         // }
         // else if (message == WM_WINDOWPOSCHANGING)
         // {
         //
         // }
         // else
         // {
         //
         //    //lresult = DefWindowProc(m_hwnd, message, wparam, lparam);
         //
         // }
         //
         // if (message == WM_MOVE || message == WM_SIZE
         //    || message==WM_WINDOWPOSCHANGED
         //    || message==WM_WINDOWPOSCHANGING
         //    || message==WM_NCCALCSIZE
         //    || message==WM_NCPAINT
         //    || message==WM_NCACTIVATE)
         //    {
         //
         //    return false;
         //
         // }

         if (message == WM_EXITSIZEMOVE)
         {

            m_bSizeMoveMode = false;

            bRet = true;
         }

         if (bRet)
         {
            return true;
         }


      }

      if (m_bDefaultSystemMenu)
      {

         if (message == ::user::e_message_initialize_menu)
         {

            if (_on_default_system_menu_init_menu(lresult, wparam))
            {

               return true;

            }

         }
         else if (message == WM_COMMAND || message == WM_SYSCOMMAND)
         {

            if (_on_default_system_menu_command(lresult, wparam, lparam))
            {

               return true;

            }

         }

      }

      return false;


   }


   bool window::_on_default_system_menu_init_menu(::lresult & lresult, ::wparam wparam)
   {

      auto hmenu = wparam.raw_cast<HMENU>();

      auto hmenuSystem = m_hmenuSystem;

      if (hmenu != hmenuSystem)
      {

         return false;

      }

      auto hwnd = ::as_HWND(this->operating_system_window());

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

            menu_item_info.wID = ID_SHOW_ABOUT_BOX;
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
   

   bool window::_on_default_system_menu_command(::lresult & lresult, ::wparam wparam, ::lparam lparam)
   {

      ::i32 wmId = LOWORD(wparam);

      if (wmId == ID_SHOW_ABOUT_BOX)
      {

         auto puseractiovationtoken = system()->acme_windowing()->get_user_activation_token();

         application()->show_about_box(puseractiovationtoken);

         lresult = 0;

         return true;

      }
      else if (wmId == SC_MOVE)
      {
         m_dVelocity = 0.;

         auto hwnd = ::as_HWND(this->operating_system_window());

         ::SetCapture(hwnd);
         POINT pointCursor{};
         ::GetCursorPos(&pointCursor);
         RECT r{};
         ::GetWindowRect(hwnd, &r);
         m_pointSizeMoveStart.x = pointCursor.x - r.left;
         m_pointSizeMoveStart.y = pointCursor.y - r.top;
         ::SetCursor(::LoadCursor(nullptr, IDC_SIZEALL));
         m_bSizeMoveMode = true;

         //PostMessage(hwnd, WM_SYSCOMMAND, SC_MOVE, 0);
         lresult = 0;
         return true;

      }
      else if (wmId == SC_CLOSE)
      {

         auto hwnd = ::as_HWND(this->operating_system_window());

         PostMessage(hwnd, WM_CLOSE, 0, 0);
         lresult = 0;
         return true;

      }

      return false;

   }


   void window::_defer_show_system_menu(::user::mouse * pmouse)
   {

      auto hwnd = ::as_HWND(this->operating_system_window());

      auto hmenu = GetSystemMenu(hwnd, true);
      m_hmenuSystem = GetSystemMenu(hwnd, false);
      //SetForegroundWindow(hwnd);
      TrackPopupMenu(m_hmenuSystem,
         TPM_LEFTALIGN | TPM_TOPALIGN,
         pmouse->m_pointAbsolute.x,
         pmouse->m_pointAbsolute.y,
         0,
         hwnd, NULL);
      //PostMessage(hwnd, WM_NULL, 0, 0);

   }


   void * window::_HWND() const
   {

      auto hwnd = m_windowswindow.as_HWND();

      return hwnd;

   }


   bool window::is_window_class_registered(const_char_pointer pszWindowClassName)
   {
      auto hinstance = (HINSTANCE) hinstance_from_function(s_window_procedure);
      WNDCLASSEXW wndclassexw{};
      ::wstring wstrWindowClassName(pszWindowClassName);
      if (GetClassInfoExW(hinstance, wstrWindowClassName, &wndclassexw))
      {
         return true;
      } else
         {
         return false;
      }
   }


   bool window::_register_window_class(WNDCLASSEX & wndclassex, const_char_pointer pszWindowClassName)
   {

      ::wstring wstrWindowClassName;

      wstrWindowClassName = pszWindowClassName;

      auto hinstance = (HINSTANCE) hinstance_from_function(s_window_procedure);

      //WNDCLASS wcWindowClass = {0};
      wndclassex.lpfnWndProc = s_window_procedure;
      //wcWindowClass.style = NULL;
      wndclassex.hInstance = hinstance;
      wndclassex.lpszClassName = wstrWindowClassName;

      auto atom = ::RegisterClassExW(&wndclassex);

      if (!atom)
      {

         auto dwLastError = ::GetLastError();

         if (dwLastError == ERROR_CLASS_ALREADY_EXISTS)
         {

            return true;

         }

         return false;
      }

      return true;
   }


   bool window::register_window_class(const_char_pointer pszWindowClassName, ::i32 iWindowClassStyle, void * pHCURSOR, void * pHBRUSH_Background)
   {

      WNDCLASSEXW wndclassexw{};
      wndclassexw.cbSize = sizeof(WNDCLASSEXW);
      wndclassexw.style = iWindowClassStyle;
      wndclassexw.hCursor = (HCURSOR) pHCURSOR;
      wndclassexw.hbrBackground = (HBRUSH)pHBRUSH_Background;

      return _register_window_class(wndclassexw, pszWindowClassName);

   }


   ::operating_system::window window::_create_window_ex(
      ::u32 dwExStyle,
      const ::scoped_string & scopedstrWindowClassName,
      const ::scoped_string & scopedstrWindowName,
      ::u32 dwStyle,
      const ::i32_origin_size & originsize,
      const ::operating_system::window & operatingsystemwindowParent,
      void * pHMENU,
      ::hinstance hinstance,
      void * pLPARAM)
   {

      ::wstring wstrWindowClassName(scopedstrWindowClassName);

      ::wstring wstrWindowName(scopedstrWindowName);

      HWND hwndParent = ::as_HWND(operatingsystemwindowParent);

      HWND hwnd = ::CreateWindowExW(
         dwExStyle,
         wstrWindowClassName,
         wstrWindowName,
         dwStyle,
         originsize.origin.x,
         originsize.origin.y,
         originsize.size.cx,
         originsize.size.cy,
         hwndParent,
         (HMENU)pHMENU,
         (HINSTANCE) hinstance,
         pLPARAM);

      auto operatingsystemwindow = ::as_operating_system_window(hwnd);

      return operatingsystemwindow;

   }


   void window::createWindowEx(
      ::u32 dwExStyle,
      const ::scoped_string & scopedstrWindowClassName,
      const ::scoped_string & scopedstrWindowName,
      ::u32 dwStyle,
      const ::i32_origin_size & originsize,
      const ::operating_system::window & operatingsystemwindowParent ,
      void * pHMENU )
   {

      _create_window_ex(
         dwExStyle,
         scopedstrWindowClassName,
         scopedstrWindowName,
         dwStyle,
         originsize,
         operatingsystemwindowParent,
         pHMENU,
         ::windows::hinstance_from_function(s_window_procedure),
         (void*) (::windows::window *) this);

   }

   // Step 4: the Window Procedure
   LRESULT CALLBACK window::s_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
   {

      ::windows::window * pwindow = nullptr;

      ::lresult lresult = 0;

      if (msg == WM_NCCALCSIZE)
      {

         ::information("windows::window::s_window_procedure WM_NCCALCSIZE");

      }
      else if (msg == WM_SHOWWINDOW)
      {

         ::information("windows::window::s_window_procedure WM_SHOWWINDOW");

      }

      if (::windows::pre_process_window_procedure(lresult, hwnd, msg, wParam, lParam))
      {

         return lresult;

      }

      if (msg == (WM_WINDOWPOSCHANGING))
      {

         //::information() << "WM_WINDOWPOSCHANGING";

      }
      else if (msg == (WM_USER + 123))
      {

         //::information() << "::windows::window_procedure WM_USER + 123";

      }
      else if (msg == (WM_APP + 123))
      {

         //::information() << "::windows::window_procedure WM_APP + 123";

      }

      auto operatingsystemwindow = as_operating_system_window(hwnd);

      if (msg == WM_NCCREATE)
      {

         CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;

         pwindow = (::windows::window *)pcreatestruct->lpCreateParams;

         ///SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pwindow);

         ::windows::g_pwindowing->m_windowmap[hwnd] = pwindow;

         pwindow->m_windowswindow = hwnd;

      }
      else
      {

         pwindow = ::windows::g_pwindowing->m_windowmap[hwnd];

         //pwindow = (::windows::window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

      }

      if (!pwindow)
      {

         LRESULT lresult = DefWindowProc(hwnd, msg, wParam, lParam);

         return lresult;

      }

      if (pwindow->call_window_procedure(lresult, msg, wParam, lParam))
      {

         return lresult;

      }
      else
      {

         lresult = DefWindowProc(hwnd, msg, wParam, lParam);

      }

      return lresult;

   }


   HINSTANCE g_hinstanceWindowProcedureModule = nullptr;


   void set_window_procedure_hinstance(HINSTANCE hinstance)
   {

      g_hinstanceWindowProcedureModule = hinstance; 
   
   }

   HINSTANCE window::s_window_procedure_hinstance()
   {

      if (g_hinstanceWindowProcedureModule)
      {

         return g_hinstanceWindowProcedureModule;

      }

      HINSTANCE hinstanceWndProc = (HINSTANCE) ::GetModuleHandleA("acme.dll");

      if (hinstanceWndProc == nullptr)
      {

         hinstanceWndProc = (HINSTANCE)::GetModuleHandleA(NULL);

      }

      return hinstanceWndProc;

   }

   void window::postMessage(::user::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {

      auto hwnd = m_windowswindow.as_HWND();

      auto message = (::u32) emessage;

      auto wParam = wparam.m_wparam;

      auto lParam = lparam.m_lparam;

      ::PostMessage(hwnd, message, wParam, lParam);

   }


   bool window::is_window_visible()
   {

      auto hwnd = m_windowswindow.as_HWND();

      return ::IsWindowVisible(hwnd);

   }


   bool window::is_window_iconic()
   {

      auto hwnd = m_windowswindow.as_HWND();

      return ::IsIconic(hwnd);

   }


   ::f32 window::get_window_scale()
   {

      auto hwnd = m_windowswindow.as_HWND();

      UINT dpi = GetDpiForWindow(hwnd);

      return (::f32)dpi / 96.0f;


   }


   ::i32_point window::screen_to_window_client(const ::i32_point & point)
   {

      POINT p{point.x, point.y};

      auto hwnd = m_windowswindow.as_HWND();

      ::ScreenToClient(hwnd, &p);

      return {p.x, p.y};

   }


   ::i32_rectangle window::screen_to_window_client(const ::i32_rectangle & rectangle)
   {

      return {screen_to_window_client(rectangle.top_left()), screen_to_window_client(rectangle.bottom_right())};

   }


   ::i32_point window::window_client_to_screen(const ::i32_point & point)
   {

      POINT p{point.x, point.y};

      auto hwnd = m_windowswindow.as_HWND();

      ::ClientToScreen(hwnd, &p);

      return {p.x, p.y};

   }


   ::i32_rectangle window::window_client_to_screen(const ::i32_rectangle & rectangle)
   {

      return {window_client_to_screen(rectangle.top_left()), window_client_to_screen(rectangle.bottom_right())};

   }

   void window::show_window(::i32 iShowFlags)
   {

      auto hwnd = m_windowswindow.as_HWND();

      ::ShowWindow(hwnd, iShowFlags);

   }


   void window::set_window_style(::i32 iShowFlags)
   {

      auto hwnd = m_windowswindow.as_HWND();

      ::SetWindowLongPtrW(hwnd, GWL_STYLE, iShowFlags);

   }


   ::i64 window::get_window_style()
   {

      auto hwnd = m_windowswindow.as_HWND();

      LONG_PTR i = ::GetWindowLongPtrW(hwnd, GWL_STYLE);

      return i;

   }


   void window::post_message(user::enum_message eusermessage, wparam wparam, lparam lparam)
   {

      auto hwnd = m_windowswindow.as_HWND();

      ::PostMessage(hwnd, eusermessage, wparam, lparam);

   }


   void window::set_active_window()
   {

      auto hwnd = m_windowswindow.as_HWND();

      auto hwndOld = ::SetActiveWindow(hwnd);

      ::string strType;

      if (m_pacmeuserinteraction)
      {

         strType = typeid(*m_pacmeuserinteraction).name();

      }

      information("windows::window SetActiveWindow hwndOld={:#08x} {}", (::u64)hwndOld, strType);

   }


   void window::set_window_text(const scoped_string &scopedstr)
   {

      auto hwnd = m_windowswindow.as_HWND();

      ::string strText(scopedstr);

      ::wstring wstrText(strText);

      ::SetWindowTextW(hwnd,wstrText);

   }


   void window::set_window_position(const ::operating_system::window & operatingsystemwindow, const ::i32_point & point, const ::i32_size & size, ::i32 iSetWindowPosFlags)
   {

      auto hwnd = m_windowswindow.as_HWND();

      auto hwndAfter = ::as_HWND(operatingsystemwindow);

      ::SetWindowPos(hwnd, hwndAfter, point.x, point.y, size.cx, size.cy, iSetWindowPosFlags);

   }


   void window::window_invalidate_rect(const i32_rectangle *prectangle, bool bErase)
   {

      auto hwnd = m_windowswindow.as_HWND();

      if (::is_null(prectangle))
      {

         ::InvalidateRect(hwnd, nullptr,  bErase ? TRUE : FALSE);

      }
      else
      {

         RECT rect;

         copy(rect, *prectangle);

         ::InvalidateRect(hwnd, &rect,  bErase ? TRUE : FALSE);

      }

   }

   void window::update_window()
   {

      auto hwnd = m_windowswindow.as_HWND();

      ::UpdateWindow(hwnd);

   }


   void window::redraw_window(const i32_rectangle *prectangle, void *pHRGN, ::i32 iRedrawFlags)
   {

      RECT rect;

      HRGN hrgn = nullptr;

      const RECT * prect = nullptr;

      if (::is_set(prectangle))
      {

         prect = &rect;

         ::copy(rect, *prectangle);

      }

      if (::is_set(pHRGN))
      {

         hrgn = (HRGN) pHRGN;

      }

      auto hwnd = m_windowswindow.as_HWND();

      ::RedrawWindow(hwnd, prect, hrgn, iRedrawFlags);

   }


   void window::window_set_focus()
   {

      auto hwnd = m_windowswindow.as_HWND();

      auto hwndOld = ::SetFocus(hwnd);

      ::string strType;

      if (m_pacmeuserinteraction)
      {

         strType = typeid(*m_pacmeuserinteraction).name();

      }

      information("windows::window SetFocus hwndOld={:#08x} {}", (::i64)hwndOld, strType);

   }


   void window::set_foreground_window(::user::activation_token *puseractivationtoken)
   {

      auto hwnd = m_windowswindow.as_HWND();

      auto bResult = ::SetForegroundWindow(hwnd);

      ::string strType;

      if (m_pacmeuserinteraction)
      {

         strType = typeid(*m_pacmeuserinteraction).name();

      }

      information("windows::window SetForegroundWindow {} {}", bResult, strType);

   }


   ::i32_rectangle window::window_get_client_rect()
   {

      auto hwnd = m_windowswindow.as_HWND();

      RECT rect;

      if (!::GetClientRect(hwnd, &rect))
      {

         return {};

      }

      return rect;

   }


   ::i32_rectangle window::get_window_rect()
   {

      auto hwnd = m_windowswindow.as_HWND();

      RECT rect;

      if (!::GetWindowRect(hwnd, &rect))
      {

         return {};

      }

      return rect;

   }


   bool window::defer_update_system_menu()
   {

      auto hwnd = m_windowswindow.as_HWND();

      if (!m_hmenuSystem || m_hmenuSystem != ::GetSystemMenu(hwnd, false))
      {
         //auto hmenu = GetSystemMenu(hwnd, true);

         auto hwnd =(HWND)  _HWND();

         m_hmenuSystem = GetSystemMenu(hwnd, false);

         WPARAM wparamHere = (WPARAM) m_hmenuSystem;

         LRESULT lresultHere = 1;

         if (_on_default_system_menu_init_menu(lresultHere, wparamHere))
         {

            return true;

         }

      }

      return false;

   }


   void window::dump_operating_system_child_window_hierarchy()
   {

      auto operatingsystemwindow = m_windowswindow.as_operating_system_window();

      ::windows::dump_child_window_hierarchy(operatingsystemwindow);

   }

} // namespace windows


CLASS_DECL_ACME HWND as_HWND(const ::operating_system::window& operatingsystemwindow)
{

   if (operatingsystemwindow.is_null())
   {

      return nullptr;

   }

   ::operating_system::windows_window window(operatingsystemwindow);

   return window.as_HWND();

}


CLASS_DECL_ACME RECT as_RECT(const ::i32_rectangle & rectangle)
{

   return {rectangle.left, rectangle.top, rectangle.right, rectangle.bottom};

}


CLASS_DECL_ACME ::operating_system::window as_operating_system_window(HWND hwnd)
{

   ::operating_system::windows_window window(hwnd);

   return window.as_operating_system_window();

}


CLASS_DECL_ACME ::operating_system::window as_operating_system_window(::uptr u)
{

   if (u == 0)
   {

      return {};

   }

   auto hwnd = (HWND)u;

   auto operatingsystemwindow =  ::as_operating_system_window(hwnd);

   return operatingsystemwindow;

}


CLASS_DECL_ACME ::uptr as_uptr(const ::operating_system::window & operatingsystemwindow)
{

   if (operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_none)
   {

      return 0;

   }

   if (operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_windows)
   {


      return (::uptr) ::as_HWND(operatingsystemwindow);

   }

   return 0;

}


CLASS_DECL_ACME ::uptr as_u64(const ::operating_system::window & operatingsystemwindow)
{

   if (operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_none)
   {

      return 0;

   }

   if (operatingsystemwindow.m_eoperatingambient == ::windowing::e_operating_ambient_windows)
   {


      return (::u64) ::as_HWND(operatingsystemwindow);

   }

   return 0;

}


namespace windows
{


   CLASS_DECL_ACME bool pre_process_window_procedure(::lresult& lresult, HWND hwnd, ::u32 message, ::wparam wparam, ::lparam lparam)
   {

      if (message == (WM_APP + 876))
      {

         ::warning() << "WM_APP + 876  At thread " << ::GetCurrentThreadId();

         if (wparam == 0)
         {

            ::warning() << "WM_APP + 876 wParam is Zero At thread " << ::GetCurrentThreadId();

            ::procedure procedure(lparam);

            try
            {

               procedure();

            }
            catch (...)
            {

            }

            lresult = 0;

            return true;

         }

      }

      return false;

   }



} // namespace windows
 

HWND g_hwndMain;


CLASS_DECL_ACME HWND get_hwnd_main()
{

   return g_hwndMain;

}



WNDPROC g_pwndprocMain;

CLASS_DECL_ACME void set_main_wndproc(void *p)
{

   g_pwndprocMain = (WNDPROC)p;

}

CLASS_DECL_ACME LRESULT CALLBACK RDP_HOST2_WndProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam)
{
   return g_pwndprocMain(hwnd, msg, wParam, lParam);
   // switch (msg)
   // {
   //    case WM_CREATE:
   //    {
   //       g_hwndMain = hwnd;
   //
   //       HRESULT hr = CreateRdpControl(hwnd);
   //
   //       if (FAILED(hr))
   //       {
   //          MessageBoxW(
   //              hwnd,
   //              L"Failed to create RDP ActiveX control",
   //              L"Error",
   //              MB_ICONERROR);
   //
   //          return -1;
   //       }
   //
   //       ConnectRdp();
   //
   //       return 0;
   //    }
   //
   //    case WM_SIZE:
   //    {
   //       ResizeActiveX();
   //       return 0;
   //    }
   //
   //    case WM_DESTROY:
   //    {
   //       CleanupRdp();
   //
   //       PostQuitMessage(0);
   //       return 0;
   //    }
   // }
   //
   // return DefWindowProc(
   //     hwnd,
   //     msg,
   //     wParam,
   //     lParam);
}



//
//CLASS_DECL_ACME::user::e_key_state wm_mouse_wparam_to_user_key_state(::wparam wparam)
//{
//
//   using namespace ::user;
//
//   auto keyboardstate = e_key_state_none;
//
//   if (wparam & MK_LBUTTON)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_left_button);
//   }
//
//   if (wparam & MK_RBUTTON)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_right_button);
//   }
//
//   if (wparam & MK_SHIFT)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_shift);
//
//      if (::GetKeyState(VK_LSHIFT) & 0x8000)
//      {
//
//         keyboardstate = (e_key_state)(keyboardstate | e_key_state_left_shift);
//      }
//
//      if (::GetKeyState(VK_RSHIFT) & 0x8000)
//      {
//
//         keyboardstate = (e_key_state)(keyboardstate | e_key_state_right_shift);
//      }
//   }
//
//   if (wparam & MK_CONTROL)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_control);
//
//      if (::GetKeyState(VK_LCONTROL) & 0x8000)
//      {
//
//         keyboardstate = (e_key_state)(keyboardstate | e_key_state_left_control);
//      }
//
//      if (::GetKeyState(VK_RCONTROL) & 0x8000)
//      {
//
//         keyboardstate = (e_key_state)(keyboardstate | e_key_state_right_control);
//      }
//   }
//
//   if (wparam & MK_MBUTTON)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_middle_button);
//   }
//
//#ifdef MK_XBUTTON1
//   if (wparam & MK_XBUTTON1)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_x1_button);
//   }
//#endif
//
//#ifdef MK_XBUTTON2
//   if (wparam & MK_XBUTTON2)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_x2_button);
//   }
//#endif
//
//   if (::GetKeyState(VK_LMENU) & 0x8000)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_left_alt);
//   }
//
//   if (::GetKeyState(VK_RMENU) & 0x8000)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_right_alt);
//   }
//
//#ifdef VK_LWIN
//   if (::GetKeyState(VK_LWIN) & 0x8000)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_left_command);
//   }
//#endif
//
//#ifdef VK_RWIN
//   if (::GetKeyState(VK_RWIN) & 0x8000)
//   {
//
//      keyboardstate = (e_key_state)(keyboardstate | e_key_state_right_command);
//   }
//#endif
//
//   return keyboardstate;
//}
