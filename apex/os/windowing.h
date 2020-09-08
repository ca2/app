//
//  os_windowing.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


CLASS_DECL_APEX WINBOOL os_init_windowing();

CLASS_DECL_APEX void os_term_windowing();

CLASS_DECL_APEX i64 oswindow_id(oswindow w);


CLASS_DECL_APEX WINBOOL is_window(oswindow oswindow);
CLASS_DECL_APEX oswindow get_focus();
CLASS_DECL_APEX oswindow set_focus(oswindow oswindow);
CLASS_DECL_APEX oswindow get_active_window();
CLASS_DECL_APEX oswindow set_active_window(oswindow oswindow);
CLASS_DECL_APEX oswindow get_capture();
CLASS_DECL_APEX oswindow set_capture(oswindow oswindow);
CLASS_DECL_APEX WINBOOL release_capture();
CLASS_DECL_APEX WINBOOL destroy_window(oswindow oswindow);
CLASS_DECL_APEX oswindow get_window(oswindow oswindow, int iWindow);
CLASS_DECL_APEX oswindow get_desktop_window();
CLASS_DECL_APEX WINBOOL show_window(oswindow oswindow, int iShow);
CLASS_DECL_APEX WINBOOL set_foreground_window(oswindow oswindow);


#ifdef WINDOWS_DESKTOP
CLASS_DECL_APEX bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif



