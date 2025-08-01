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



//unsigned int get_tick();




#define _fileno   fileno
#define _unlink   unlink




//CLASS_DECL_APEX unsigned int get_last_error();
//CLASS_DECL_APEX void set_last_error(unsigned int dw);


CLASS_DECL_APEX bool _istlead(int ch);




bool c_xstart();

extern oswindow g_oswindowDesktop;



CLASS_DECL_APEX bool main_initialize();
CLASS_DECL_APEX bool main_finalize();

/*
bool os_on_start_application(::particle * pparticle);
::file::path app_desktop_file_path(::particle * pparticle);
::file::path app_desktop_file_path(::particle * pparticle, const ::scoped_string & scopedstrAppId);
bool linux_prepare_app_desktop_file(::particle * pparticle);
bool linux_prepare_app_desktop_file(::particle * pparticle, const ::scoped_string & scopedstrAppId);
*/

#include "x11.h"

#include "gtk_things/gnome_gnome.h"

#include "linux.inl"




