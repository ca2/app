#include "framework.h"


float g_DPIScaleX = 1.0f;
float g_DPIScaleY = 1.0f;


void dpi_os_initialize()
{

   //::wait(::winrt::Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(::winrt::Windows::UI::Core::CoreDispatcherPriority::Normal, ref memory_new ::winrt::Windows::UI::Core::DispatchedHandler([]()
     // {

         ::winrt::Windows::Graphics::Display::DisplayInformation^ displayinformation = ::winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentImpact();

         g_DPIScaleX = displayinformation->LogicalDpi;
         g_DPIScaleY = displayinformation->LogicalDpi;

      //})));

}


CLASS_DECL_APEX float os_get_dpi()
{

   return g_DPIScaleX;

}


CLASS_DECL_APEX float point_dpi(oswindow hwnd, float points)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return points * g_DPIScaleX / 72.f;

}


CLASS_DECL_APEX float dpiy(oswindow hwnd, float y)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return y * g_DPIScaleY / 96.f;

}


CLASS_DECL_APEX float dpix(HWND hwnd, float x)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return x * g_DPIScaleX / 96.f;

}


CLASS_DECL_APEX float y_dpi(HWND hwnd, float y)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return y / g_DPIScaleY;

}


CLASS_DECL_APEX float x_dpi(HWND hwnd, float x)
{

   __UNREFERENCED_PARAMETER(hwnd);

   return x / g_DPIScaleX;

}

