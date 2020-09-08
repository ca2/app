//
//  os_windowing.h
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


CLASS_DECL_AQUA WINBOOL os_init_windowing();

CLASS_DECL_AQUA void os_term_windowing();

CLASS_DECL_AQUA i64 oswindow_id(oswindow w);


CLASS_DECL_AQUA WINBOOL is_window(oswindow oswindow);
CLASS_DECL_AQUA oswindow get_focus();
CLASS_DECL_AQUA oswindow set_focus(oswindow oswindow);
CLASS_DECL_AQUA oswindow get_active_window();
CLASS_DECL_AQUA oswindow set_active_window(oswindow oswindow);
CLASS_DECL_AQUA oswindow get_capture();
CLASS_DECL_AQUA oswindow set_capture(oswindow oswindow);
CLASS_DECL_AQUA WINBOOL release_capture();
CLASS_DECL_AQUA WINBOOL destroy_window(oswindow oswindow);
CLASS_DECL_AQUA oswindow get_window(oswindow oswindow, int iWindow);
CLASS_DECL_AQUA oswindow get_desktop_window();
CLASS_DECL_AQUA WINBOOL show_window(oswindow oswindow, int iShow);
CLASS_DECL_AQUA WINBOOL set_foreground_window(oswindow oswindow);


#ifdef WINDOWS_DESKTOP
CLASS_DECL_AQUA bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif



