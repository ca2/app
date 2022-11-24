#include "framework.h"


#include "acme/_operating_system.h"


float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;



CLASS_DECL_ACME float os_get_dpi()
{

   return g_DPIScaleX;

}


CLASS_DECL_ACME float point_dpi(oswindow hwnd, float points)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return points * g_DPIScaleX / 72.f;

}


CLASS_DECL_ACME float dpiy(oswindow hwnd, float y)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return y * g_DPIScaleY / 96.f;

}


//CLASS_DECL_ACME float dpix(HWND hwnd, float x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x * g_DPIScaleX / 96.f;
//
//}
//
//
//CLASS_DECL_ACME float y_dpi(HWND hwnd, float y)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return y / g_DPIScaleY;
//
//}
//
//
//CLASS_DECL_ACME float x_dpi(HWND hwnd, float x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x / g_DPIScaleX;
//
//}
//
