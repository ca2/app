#include "framework.h"


#include "acid/_operating_system.h"


float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;



CLASS_DECL_ACID float os_get_dpi()
{

   return g_DPIScaleX;

}


CLASS_DECL_ACID float point_dpi(oswindow hwnd, float points)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return points * g_DPIScaleX / 72.f;

}


CLASS_DECL_ACID float dpiy(oswindow hwnd, float y)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return y * g_DPIScaleY / 96.f;

}


//CLASS_DECL_ACID float dpix(HWND hwnd, float x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x * g_DPIScaleX / 96.f;
//
//}
//
//
//CLASS_DECL_ACID float y_dpi(HWND hwnd, float y)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return y / g_DPIScaleY;
//
//}
//
//
//CLASS_DECL_ACID float x_dpi(HWND hwnd, float x)
//{
//
//   __UNREFERENCED_PARAMETER(hwnd);
//
//   return x / g_DPIScaleX;
//
//}
//
