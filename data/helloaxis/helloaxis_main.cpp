#include "framework.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(::object * pobject, HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, ::u32, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, ::u32, WPARAM, LPARAM);

int my_main(::layered * pobjectContext)
{

   HINSTANCE hInstance = Sys(papp).m_hinstance;
   // TODO: Place code here.

   // Initialize global strings
   LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   LoadStringW(hInstance, IDC_WINDOWSPROJECT2, szWindowClass, MAX_LOADSTRING);
   MyRegisterClass(hInstance);

   // Perform application initialization:
   if (!InitInstance(papp, hInstance, e_display_normal))
   {
      return FALSE;
   }

   HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT2));

   MSG msg;

   // Main message loop:
   while (mq_get_message(&msg, nullptr, 0, 0))
   {
      if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      }
   }

   return (int)msg.wParam;
}



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
BOOL InitInstance(::object * pobject, HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, papp);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
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
   ::aura::application * papp;
   if (message == e_message_create)
   {
      papp = (::aura::application *)((LPCREATESTRUCT)lParam)->lpCreateParams;
      SetWindowLongPtr(hWnd, GWL_USERDATA, (LONG_PTR)papp);
   }
   else
   {
      papp = (::aura::application *) GetWindowLongPtr(hWnd, GWL_USERDATA);
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
   case e_message_paint:
   {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hWnd, &ps);
      App(papp).paint(hWnd, hdc);

      EndPaint(hWnd, &ps);
   }
   break;
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
      return (INT_PTR)TRUE;

   case e_message_command:
      if (LOWORD(wParam) == e_dialog_result_ok || LOWORD(wParam) == e_dialog_result_cancel)
      {
         EndDialog(hDlg, LOWORD(wParam));
         return (INT_PTR)TRUE;
      }
      break;
   }
   return (INT_PTR)FALSE;
}
