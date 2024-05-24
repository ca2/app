//
// Created by camilo on 11/04/2022. 11:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include <X11/Xlib-xcb.h>


xcb_connection_t * x11_display_xcb_connection(void * pX11Display)
{

   Display * pdisplay = (Display *) pX11Display;

   auto pconnection = XGetXCBConnection(pdisplay);

   return pconnection;

}