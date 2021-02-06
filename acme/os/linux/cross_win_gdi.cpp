#include "framework.h"
#include "_user.h"

//!!!
//!!!//device_context::device_context()
//{
//
//
//   m_pdisplay     = nullptr;
//   m_drawable     = None;
//   m_gc           = None;
//   m_pixmap       = None;
//   m_window       = None;
//   m_point.x         = 0;
//   m_point.y         = 0;
//   m_pointOffset.x   = 0;
//   m_pointOffset.y   = 0;
//   m_iScreen      = 0;
//   m_iDepth       = 0;
//   m_fontset      = None;
//
//
//
//}
//
////
////
////
////// HDC GetDC(oswindow hwnd)
////// {
////
////
//////    HDC hdc = new device_context;
////
//////    hdc->m_pdisplay      = hwnd->display();
//////    hdc->m_window        = hwnd->window();
//////    hdc->m_drawable      = (Drawable) (hwnd == nullptr || hwnd->window() == nullptr ? DefaultRootWindow(hdc->m_pdisplay) : hwnd->window());
//////    hdc->m_gc            = XCreateGC(hdc->m_pdisplay, hdc->m_drawable, 0, 0);
////
//////    return hdc;
//
//// }
//
//
//// HDC CreateCompatibleDC(HDC hdcParam)
//// {
//
////    HDC hdc = new device_context;
//
////    return hdc;
//
//// }
//
//
//// HDC GetWindowDC(oswindow hwnd)
//// {
//
////    return GetDC(hwnd);
//// }
//
//
//// int_bool ReleaseDC(oswindow hwnd, HDC hdc)
//// {
//
//
////    //single_lock sl(&user_mutex(), true);
//
//
////    if(hdc == nullptr)
////       return false;
//
////    XFreeGC(hdc->m_pdisplay, hdc->m_gc);
////    XCloseDisplay(hdc->m_pdisplay);
//
////    delete hdc;
////    return true;
//
//// }
//
//
//
//
//// i32 FillRect(HDC hdc, const ::rectangle_i32 & prc, HBRUSH hbr)
//
//// {
//
////    //single_lock sl(&user_mutex(), true);
//
//
////    XFillRectangle(hdc->m_pdisplay, hdc->m_drawable, hdc->m_gc, prc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
//
////    return 1;
//// }
//
//
//// HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
//// {
//
////    HDC hdc = GetDC(hwnd);
//
////    get_client_rect(hwnd, &ps->rcPaint);
//
////    return hdc;
//
//// }
//
//
//// int_bool EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
//// {
//
////    return ReleaseDC(hwnd, ps->hdc);
//
//// }
//
//
//
//
//
//
//
//
//
//
//
