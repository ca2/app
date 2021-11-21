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




CLASS_DECL_ACME ::e_status get_last_status();
CLASS_DECL_ACME void set_last_status(::e_status estatus);


CLASS_DECL_ACME bool _istlead(i32 ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_ACME bool main_initialize();
CLASS_DECL_ACME bool main_finalize();

/*
bool os_on_start_application(::matter * pobject);
::file::path app_desktop_file_path(::matter * pobject);
::file::path app_desktop_file_path(::matter * pobject, string strAppId);
bool linux_prepare_app_desktop_file(::matter * pobject);
bool linux_prepare_app_desktop_file(::matter * pobject, string strAppId);
*/

#include "x11.h"

#include "gtk_things/gnome_gnome.h"

#include "linux.inl"




