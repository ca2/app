#pragma once

// linux.h
// Linux : C++

#include <wchar.h>


#include "graphics.h"
#include "process.h"
//#include "cross_win_gdi.h"
#include "cross_win_file.h"
#include "desktop_file.h"
#include "file.h"



#define ENABLE_BINRELOC



//::u32 get_tick();




#define _fileno   fileno
#define _unlink   unlink




//CLASS_DECL_CORE ::u32 get_last_error();
//CLASS_DECL_CORE void set_last_error(::u32 dw);


CLASS_DECL_CORE bool _istlead(i32 ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_CORE bool main_initialize();
CLASS_DECL_CORE bool main_finalize();

/*
bool os_on_start_application(::object * pobject);
::file::path app_desktop_file_path(::object * pobject);
::file::path app_desktop_file_path(::object * pobject, string strAppId);
bool linux_prepare_app_desktop_file(::object * pobject);
bool linux_prepare_app_desktop_file(::object * pobject, string strAppId);
*/

#include "x11.h"

#include "gtk_things/gnome_gnome.h"

#include "linux.inl"




