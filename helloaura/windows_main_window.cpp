#include "framework.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(::helloaura::render * prender, HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, ::u32, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, ::u32, WPARAM, LPARAM);


namespace helloaura
{

   int main_window(::helloaura::render * prender)
   {

      HINSTANCE hInstance = Sys(prender->get_context_application()).m_hinstance;
      // TODO: Place code here.

      // Initialize global strings
      LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
      LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
      MyRegisterClass(hInstance);

      // Perform application initialization:
      if (!InitInstance(prender, hInstance, e_display_normal))
      {
         return false;
      }

      HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

      MSG msg;

      // Main message loop:
      while (GetMessage(&msg, nullptr, 0, 0))
      {
         if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
         {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
         }
      }

      return (int)msg.wParam;
   }

} // namespace helloaura

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
   WNDCLASSEXW wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);

   wcex.style = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc = WndProc;
   wcex.cbClsExtra = 0;
   wcex.cbWndExtra = 0;
   wcex.hInstance = hInstance;
   wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
   wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
   wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
   wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
   wcex.lpszClassName = szWindowClass;
   wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

   return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(::helloaura::render * prender, HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, prender);

   if (!hWnd)
   {
      return false;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return true;
}

//
//  FUNCTION: WndProc(HWND, ::u32, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  e_message_command  - process the application menu
//  e_message_paint    - Paint the main window
//  e_message_destroy  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, const ::id & id, WPARAM wParam, LPARAM lParam)
{

   ::helloaura::render * prender;

   if (message == e_message_create)
   {

      prender = (::helloaura::render *)((LPCREATESTRUCT)lParam)->lpCreateParams;

      SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)prender);

      prender->begin();

      SetTimer(hWnd, 123, 50, nullptr);

   }
   else
   {

      prender = (::helloaura::render *) GetWindowLongPtr(hWnd, GWL_USERDATA);

   }

   switch (message)
   {
   case e_message_command:
   {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_ABOUT:
         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
         break;
      case IDM_EXIT:
         DestroyWindow(hWnd);
         break;
      default:
         return DefWindowProc(hWnd, message, wParam, lParam);
      }
   }
   break;
   case e_message_timer:
   {
      if (wParam == 123)
      {

         set_need_redraw(hWnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
      }
   }
   break
   ;
   case e_message_erase_background:
      return 1;
   case e_message_paint:
   {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);

      ::draw2d::graphics_pointer g(prender->create_new, this);

      g->Attach(hdc);

      auto & pimage = prender->m_pimageWindow;

/*      if (pimage->is_set() && pimage->m_pcolorref != nullptr)
      {

/*         pimage->get_graphics()->FillSolidRect(prender->m_rectClient, ARGB(255, 255, 255, 255));

/*         prender->_006OnDraw(pimage->get_graphics());

      }

/*      g->BitBlt(0, 0, pimage->width(), pimage->height(), prender->m_pimageWindow->get_graphics());

      ::GdiFlush();

      EndPaint(hWnd, &ps);

   }
   break;
   case e_message_size:
   {

      ::get_client_rect(hWnd, prender->m_rectClient);

      prender->m_pimageWindow->alloc(prender->create_new, this);

      if (prender->m_pimageWindow->is_set())
      {

/*         prender->m_pimageWindow = create_image(prender->m_rectClient->size());

      }

      prender->m_bNewLayout = true;

      prender->m_bFast = true;

   } break;
   case e_message_destroy:
      PostQuitMessage(0);
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, const ::id & id, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   switch (message)
   {
   case WM_INITDIALOG:
      return (INT_PTR)true;

   case e_message_command:
      if (LOWORD(wParam) == e_dialog_result_ok || LOWORD(wParam) == e_dialog_result_cancel)
      {
         EndDialog(hDlg, LOWORD(wParam));
         return (INT_PTR)true;
      }
      break;
   }
   return (INT_PTR)false;
}
