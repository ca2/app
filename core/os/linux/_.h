#pragma once


#include "debug.h"

#include "graphics.h"






off_t tell64(int fd);








//int_bool axis_TranslateMessage(const MESSAGE * pmessage);

//LRESULT axis_DispatchMessage(const MESSAGE * pmessage);






#include "windowing.h"


#include "gnome.h"


int_bool gdk_launch_uri(const ::string & pszUri, char * pszError = NULL, int iBufferSize = 0);


//typedef struct _cairo_rectangle_int cairo_rectangle_int_t;
//typedef cairo_rectangle_int_t         GdkRectangle;
//
//void copy(RECTANGLE_I32 * prectTarget, const GdkRectangle * prectSource);
//void copy(GdkRectangle * prectTarget, const RECTANGLE_I32 * prectSource);


namespace os
{

  string os_get_user_theme();
  string get_wallpaper(::index iIndex);

} // namespace os

