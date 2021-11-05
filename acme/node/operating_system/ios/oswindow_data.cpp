//
//  oswindow_data.cpp
//  ios_aura
//
//  Created by Camilo Sasuke Tsumanuma on 20/05/20.
//
#include "framework.h"
#include "_ios.h"


bool uiwindow_is_visible(UIWindow * window);
bool uiwindow_is_iconic(UIWindow * window);
bool uiwindow_show_window(UIWindow * window, int iShow);

bool oswindow_data::is_window_visible()
{
   
   return uiwindow_is_visible(window());
   
}


bool oswindow_data::is_iconic()
{
   
   return uiwindow_is_iconic(window());
   
}


bool oswindow_data::show_window(enum_display edisplay)
{
   
   return uiwindow_show_window(window(), edisplay);
   
}


bool oswindow_data::client_to_screen(POINT_I32 *lppoint)
{

   RECTANGLE_I32 rectangle_i32;
   
   get_uiwindow_rect(this, &rectangle);
   
   lppoint->x += rectangle.left;
   
   lppoint->y += rectangle.top;
   
   return true;
   
}


bool oswindow_data::screen_to_client(POINT_I32 *lppoint)
{
   
   RECTANGLE_I32 rectangle_i32;
   
   get_uiwindow_rect(this, &rectangle);
   
   lppoint->x -= rectangle.left;
   
   lppoint->y -= rectangle.top;
   
   return true;
   
}



int_bool SetWindowPos(oswindow hwnd, oswindow hwndInsertAfter, int x, int y, int cx, int cy, ::u32 uFlags)
{
   
   return true;
   
//   //   int   value_mask = 0;
//   bool  bMove = !(uFlags & SWP_NOMOVE);
//   bool  bSize = !(uFlags & SWP_NOSIZE);
//
//   if(bMove && bSize)
//   {
//
//      hwnd->m_x = x;
//      hwnd->m_y = y;
//      hwnd->m_cx = cx;
//      hwnd->m_cy = cy;
//
//   }
//   else if(bSize) // bSize only
//   {
//
//      hwnd->m_cx = cx;
//      hwnd->m_cy = cy;
//
//   }
//   else if(bMove) // bMove only
//   {
//
//      hwnd->m_x = x;
//      hwnd->m_y = y;
//
//   }
//
//   if(!(uFlags & SWP_NOZORDER))
//   {
//
//      iptr iInsertAfter = (iptr) hwndInsertAfter;
//
//      if(iInsertAfter == e_zorder_top || iInsertAfter == ZORDER_TOPMOST)
//      {
//
//         order_front_nswindow(hwnd);
//
//      }
//
//   }
//
//   //   [[hwnd->window() dd_invokeOnMainThreadAndWaitUntilDone:true] display];
//
//
//
//   /*   if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter >= 0)
//    {
//    value_mask |= CWSibling;
//    values.sibling = hwndInsertAfter;
//    values.stack_mode = Above;
//    }
//
//    XConfigureWindow(display, hwnd, value_mask, &values);
//
//    if(uFlags & SWP_SHOWWINDOW)
//    {
//    XMapWindow(display, hwnd);
//    }
//
//    if(!(uFlags & SWP_NOZORDER) && hwndInsertAfter < 0)
//    {
//    if(hwndInsertAfter == e_zorder_top || hwndInsertAfter == ZORDER_TOPMOST)
//    {
//    XRaiseWindow(display, hwnd);
//    }
//    else if(hwndInsertAfter == ZORDER_BOTTOM)
//    {
//    XLowerWindow(display, hwnd);
//    }
//
//    }
//
//    XCloseDisplay(display);*/
//
//   return 1;
   
}



