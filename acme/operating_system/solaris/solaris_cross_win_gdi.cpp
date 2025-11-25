#include "framework.h"
#include "ca_os_cross_win_gdi_internal.h"


// device_context::device_context()
// {


//    m_display   = nullptr;
//    m_d         = 0;
//    m_gc        = nullptr;
//    m_hwnd      = nullptr;



// }



// HDC GetDC(oswindow hwnd)
// {


//    HDC hdc = ___new device_context();

//    hdc->m_display    = XOpenxDisplay(nullptr);
//    hdc->m_hwnd       = hwnd;
//    hdc->m_d          = (Drawable) (hwnd == nullptr || hwnd->window() == nullptr ? DefaultRootWindow(hdc->m_display) : hwnd->window());
//    hdc->m_gc         = XCreateGC(hdc->m_display, hdc->m_d, 0, 0);

//    return hdc;

// }


// HDC GetWindowDC(oswindow hwnd)
// {

//    return GetDC(hwnd);
// }


// int_bool ReleaseDC(oswindow hwnd, HDC hdc)
// {


//    mutex_lock synchronouslock(user_synchronization(), true);


//    if(hdc == nullptr)
//       return false;

//    XFreeGC(hdc->m_display, hdc->m_gc);
//    XCloseDisplay(hdc->m_display);

//    delete hdc;
//    return true;

// }


// int_bool this->rectangle(oswindow hwnd, ::int_rectangle * lprect)
// {

//    mutex_lock synchronouslock(user_synchronization(), true);

//    XWindowAttributes attrs;

//    /* Fill attribute structure with information about root window */

//    if(XGetWindowAttributes(hwnd->display(), hwnd->window(), &attrs) == 0)
//    {

//       return false;

//    }

//    lprect->left      = 0;
//    lprect->top       = 0;
//    lprect->right     = lprect->left    + attrs.width;
//    lprect->bottom    = lprect->top     + attrs.height;

//    return true;

// }


// int_bool window_rectangle(oswindow hwnd, ::int_rectangle * lprect)
// {



//    mutex_lock synchronouslock(user_synchronization(), true);

//    if(!IsWindow(hwnd))
//       return false;


//    bool bDestroying = hwnd->m_bDestroying;
//    Display * pdisplay = hwnd->display();
//    Window window = hwnd->window();


//    if(pdisplay == nullptr)
//     return false;

//    XWindowAttributes attrs;


//    XSync(hwnd->display(), False);

//    /* Fill attribute structure with information about root window */

//    if(!XGetWindowAttributes(hwnd->display(), hwnd->window(), &attrs))
//    {
//       return false;
//    }

//    int x;
//    int y;
//    Window child;

//    if(!XTranslateCoordinates(hwnd->display(), hwnd->window(), DefaultRootWindow(hwnd->display()), 0, 0, &x, &y, &child))
//    {
//       return false;
//    }

//    lprect->left      = x;
//    lprect->top       = y;
//    lprect->right     = x    + attrs.width;
//    lprect->bottom    = y    + attrs.height;

//    return true;

// }



// int FillRect(HDC hdc, const ::int_rectangle * lprc, HBRUSH hbr)
// {

//    mutex_lock synchronouslock(user_synchronization(), true);


//    XFillRectangle(hdc->m_display, hdc->m_d, hdc->m_gc, lprc->left, lprc->top, lprc->right - lprc->left, lprc->bottom - lprc->top);
//    return 1;
// }


// HDC BeginPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    HDC hdc = GetDC(hwnd);

//    this->rectangle(hwnd, &ps->rcPaint);

//    return hdc;

// }


// int_bool EndPaint(oswindow hwnd, PAINTSTRUCT * ps)
// {

//    return ReleaseDC(hwnd, ps->hdc);

// }


// int_bool GetCursorPos(::int_point * lppointCursor)
// {

//    //mutex_lock synchronouslock(user_synchronization(), true);


//    Window root_return;
//    Window child_return;
//    int win_x_return;
//    int win_y_return;
//    unsigned int mask_return;

//    xdisplay display;

//    display.open(nullptr);

//    if(display == nullptr)
//         return false;

//    XQueryPointer(display, display.default_root_window(), &root_return, &child_return, &lppointCursor->x, &lppointCursor->y, &win_x_return, &win_y_return, & mask_return);

//    return true;

// }



// int_bool set_window_position(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, unsigned int uFlags)
// {

//    mutex_lock synchronouslock(user_synchronization(), true);


//    xdisplay display(hwnd->display());


//    int value_mask = 0;

//    XWindowChanges values;

//    if(!(uFlags & SWP_NOMOVE))
//    {
//       value_mask |= CWX | CWY;
//       values.x = x;
//       values.y = y;
//    }

//    if(!(uFlags & SWP_NOSIZE))
//    {
//       value_mask |= CWWidth | CWHeight;
//       values.width = cx;
//       values.height = cy;
//    }

//    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
//    {
//       value_mask |= CWSibling;
//       values.sibling = hwndInsertAfter->window();
//       values.stack_mode = Above;
//    }

//    XConfigureWindow(hwnd->display(), hwnd->window(), value_mask, &values);

//    if(uFlags & SWP_SHOWWINDOW)
//    {
//       XMapWindow(hwnd->display(), hwnd->window());
//    }

//    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
//    {
//       if(hwndInsertAfter->window() == e_zorder_top || hwndInsertAfter->window() == ZORDER_TOPMOST)
//       {
//          XRaiseWindow(hwnd->display(), hwnd->window());
//       }
//       else if(hwndInsertAfter->window() == ZORDER_BOTTOM)
//       {
//          XLowerWindow(hwnd->display(), hwnd->window());
//       }

//    }

//    //XCloseDisplay(display);

//    return 1;

// }



int _cx_XErrorHandler(Display * display, XErrorEvent * perrorevent)
{
   return 0;
}
