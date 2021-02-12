#include "framework.h"


// typedef ::u32 FN_GetDpiForWindow(HWND hwnd);


// float g_DPIScaleX = 1.0f;
// float g_DPIScaleY = 1.0f;


// ::u32 legacy_get_dpi_for_system()
// {

//    HDC hdc = ::GetDC(nullptr);

//    ::u32 dpiX = 72;

//    ::u32 dpiY = 72;

//    if (hdc)
//    {

//       dpiX = static_cast<::u32>(::GetDeviceCaps(hdc, LOGPIXELSX));

//       dpiY = static_cast<::u32>(::GetDeviceCaps(hdc, LOGPIXELSY));

//       ::ReleaseDC(nullptr, hdc);

//    }

//    return maximum(dpiX, dpiY);

// }


// void dpi_os_initialize()
// {

//    ::u32 uDpi = legacy_get_dpi_for_system();

//    g_DPIScaleX = uDpi / 72.0f;

//    g_DPIScaleY = uDpi / 72.0f;

// }


// ::u32 get_dpi_for_window(oswindow hwnd)
// {

//    static auto pfn_get_dpi_for_window = ::windows::api < FN_GetDpiForWindow* >::get_address("User32.dll", "GetDPiForWindow");

//    if (pfn_get_dpi_for_window)
//    {

//       return pfn_get_dpi_for_window(hwnd);

//    }

//    return legacy_get_dpi_for_system();

// }


// CLASS_DECL_AURA float point_dpi(oswindow hwnd, float points)
// {

//    float fDpi = (float)get_dpi_for_window(hwnd);

//    return points * fDpi / 72.f;

// }


// CLASS_DECL_AURA float dpiy(oswindow hwnd, float y)
// {

//    float fDpi = (float)get_dpi_for_window(hwnd);

//    return y * fDpi / 96.f;

// }


// CLASS_DECL_AURA float dpix(HWND hwnd, float x)
// {

//    float fDpi = (float)get_dpi_for_window(hwnd);

//    return x * fDpi / 96.f;

// }


// CLASS_DECL_AURA float y_dpi(HWND hwnd, float y)
// {

//    float fDpi = (float)get_dpi_for_window(hwnd);

//    return y / fDpi;

// }


// CLASS_DECL_AURA float x_dpi(HWND hwnd, float x)
// {

//    float fDpi = (float)get_dpi_for_window(hwnd);

//    return x / fDpi;

// }

