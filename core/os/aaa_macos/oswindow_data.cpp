//
//  oswindow_data.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 18/05/20.
//
#include "framework.h"
#include "oswindow_data.h"


bool nswindow_is_visible(NSWindow * window);
bool nswindow_is_iconic(NSWindow * window);
bool nswindow_iconify(NSWindow * window);
bool nswindow_show_window(NSWindow * window, int iShow);




bool oswindow_data::is_window_visible()
{
   
   return nswindow_is_visible(window());
   
}


bool oswindow_data::is_iconic()
{
   
   return nswindow_is_iconic(window());
   
}


bool oswindow_data::iconify()
{
   
   return nswindow_iconify(window());
   
}


bool is_visible(enum_display);

bool oswindow_data::show_window(int iShow)
{
   
   return nswindow_show_window(window(), iShow);
   
}


bool oswindow_data::client_to_screen(POINT32 *lppoint)
{

   RECT32 rectangle;
   
   get_nswindow_rect(this, &rectangle);
   
   lppoint->x += rectangle.left;
   
   lppoint->y += rectangle.top;
   
   return true;
   
}


bool oswindow_data::screen_to_client(POINT32 *lppoint)
{
   
   RECT32 rectangle;
   
   get_nswindow_rect(this, &rectangle);
   
   lppoint->x -= rectangle.left;
   
   lppoint->y -= rectangle.top;
   
   return true;
   
}



