#include "framework.h"


static ::mutex * s_pmutexDraw2dXlib = nullptr;


::mutex & xlib_mutex()
{

   return *s_pmutexDraw2dXlib;

}


void init_xlib_mutex(::object * pobject)
{

    s_pmutexDraw2dXlib = new ::mutex(pobject);

}
