// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSørensen
#include "framework.h"
#include "acme/operating_system.h"
#include "nano_window.h"

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

   WNDCLASSEX wndclassex;

   //Step 1: Registering the Window Class
   wndclassex.cbSize = sizeof(WNDCLASSEX);
   wndclassex.style = 0;
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

      throw_status(error_failed, "Failed to register nano message box window class.");

   }

   g_bNanoWindowClassRegistered = true;

}



// Step 4: the Window Procedure
LRESULT CALLBACK nano_window_procedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   nano_window * pwindow = nullptr;
   if (msg == WM_NCCREATE)
   {

      CREATESTRUCT * pcreatestruct = (CREATESTRUCT *)lParam;
      pwindow = (nano_window *)pcreatestruct->lpCreateParams;
      SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pwindow);
      pwindow->m_hwnd = hwnd;
   }
   else
   {

      pwindow = (nano_window *)GetWindowLongPtr(hwnd, GWLP_USERDATA);

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

   wstring wstrTitle(m_strTitle);

   auto hinstanceWndProc = nano_message_box_hinstance();
   HWND hwnd = CreateWindowEx(
      0,
      _T(NANO_WINDOW_CLASS),
      wstrTitle,
      WS_POPUP,
      m_rectangle.left,
      m_rectangle.top,
      m_rectangle.width(),
      m_rectangle.height(),
      NULL, NULL, hinstanceWndProc,this);

   if (hwnd == NULL)
   {
      throw_status(error_failed, "Failed to create nano message box window.");
      return;
   }


}
