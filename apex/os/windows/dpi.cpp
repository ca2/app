#include "framework.h"


typedef UINT FN_GetDpiForWindow(HWND hwnd);


float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;


UINT legacy_get_dpi_for_system()
{

   HDC hdc = ::GetDC(nullptr);

   UINT dpiX = 72;

   UINT dpiY = 72;

   if (hdc)
   {

      dpiX = static_cast<UINT>(::GetDeviceCaps(hdc, LOGPIXELSX));

      dpiY = static_cast<UINT>(::GetDeviceCaps(hdc, LOGPIXELSY));

      ::ReleaseDC(nullptr, hdc);

   }

   return max(dpiX, dpiY);

}


void dpi_os_initialize()
{

   UINT uDpi = legacy_get_dpi_for_system();

   g_DPIScaleX = uDpi / 72.0f;

   g_DPIScaleY = uDpi / 72.0f;

}


::u32 get_dpi_for_window(oswindow hwnd)
{

   static auto pfn_get_dpi_for_window = ::windows::api < FN_GetDpiForWindow* >::get_address("User32.dll", "GetDPiForWindow");

   if (pfn_get_dpi_for_window)
   {

      return pfn_get_dpi_for_window(hwnd);

   }

   return legacy_get_dpi_for_system();

}


CLASS_DECL_APEX float point_dpi(oswindow hwnd, float points)
{

   float fDpi = (float)get_dpi_for_window(hwnd);

   return points * fDpi / 72.f;

}


CLASS_DECL_APEX float dpiy(oswindow hwnd, float y)
{

   float fDpi = (float)get_dpi_for_window(hwnd);

   return y * fDpi / 96.f;

}


CLASS_DECL_APEX float dpix(HWND hwnd, float x)
{

   float fDpi = (float)get_dpi_for_window(hwnd);

   return x * fDpi / 96.f;

}


CLASS_DECL_APEX float y_dpi(HWND hwnd, float y)
{

   float fDpi = (float)get_dpi_for_window(hwnd);

   return y / fDpi;

}


CLASS_DECL_APEX float x_dpi(HWND hwnd, float x)
{

   float fDpi = (float)get_dpi_for_window(hwnd);

   return x / fDpi;

}

