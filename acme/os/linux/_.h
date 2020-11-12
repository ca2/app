#pragma once


#include "debug.h"

//#include "graphics.h"






off_t tell64(int fd);








//int_bool axis_TranslateMessage(const MESSAGE * pmessage);

//LRESULT axis_DispatchMessage(const MESSAGE * pmessage);






//#include "windowing.h"


//#include "gnome.h"


//int_bool gdk_launch_uri(const char * pszUri, char * pszError = NULL, int iBufferSize = 0);

::estatus os_defer_init_gtk();

#include "gdk.h"


typedef struct _cairo_rectangle_int cairo_rectangle_int_t;
typedef cairo_rectangle_int_t         GdkRectangle;

void copy(RECT32 * prectTarget, const GdkRectangle * prectSource);
void copy(GdkRectangle * prectTarget, const RECT32 * prectSource);


namespace os
{

    string get_os_desktop_theme();
    string get_wallpaper(::index iIndex);

} // namespace os

