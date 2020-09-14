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



//DWORD get_tick();




#define _fileno   fileno
#define _unlink   unlink




CLASS_DECL_AXIS DWORD get_last_error();
CLASS_DECL_AXIS void set_last_error(DWORD dw);


CLASS_DECL_AXIS bool _istlead(i32 ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_AXIS bool main_initialize();
CLASS_DECL_AXIS bool main_finalize();

/*
bool os_on_start_application(::layered * pobjectContext);
::file::path app_desktop_file_path(::layered * pobjectContext);
::file::path app_desktop_file_path(::object * pobject, string strAppId);
bool linux_prepare_app_desktop_file(::layered * pobjectContext);
bool linux_prepare_app_desktop_file(::object * pobject, string strAppId);
*/

#include "x11.h"

#include "gnome_gnome.h"

#include "linux.inl"




