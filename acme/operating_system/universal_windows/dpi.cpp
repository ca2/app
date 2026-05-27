#include "framework.h"


#include "acme/_operating_system.h"


::f32 g_DPIScaleX = 1.0f;
::f32 g_DPIScaleY = 1.0f;



CLASS_DECL_ACME ::f32 os_get_dpi()
{

   return g_DPIScaleX;

}


CLASS_DECL_ACME ::f32 point_dpi(oswindow hwnd, ::f32 points)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return points * g_DPIScaleX / 72.f;

}


CLASS_DECL_ACME ::f32 dpiy(oswindow hwnd, ::f32 y)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return y * g_DPIScaleY / 96.f;

}


//CLASS_DECL_ACME ::f32 dpix(HWND hwnd, ::f32 x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x * g_DPIScaleX / 96.f;
//
//}
//
//
//CLASS_DECL_ACME ::f32 y_dpi(HWND hwnd, ::f32 y)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return y / g_DPIScaleY;
//
//}
//
//
//CLASS_DECL_ACME ::f32 x_dpi(HWND hwnd, ::f32 x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x / g_DPIScaleX;
//
//}
//
