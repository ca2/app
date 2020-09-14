//
//  os_windowing.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


CLASS_DECL_AURA WINBOOL os_init_windowing();

CLASS_DECL_AURA void os_term_windowing();

CLASS_DECL_AURA i64 oswindow_id(oswindow w);


//CLASS_DECL_AURA WINBOOL is_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_focus();
CLASS_DECL_AURA oswindow set_focus(oswindow oswindow);
CLASS_DECL_AURA oswindow get_active_window();
CLASS_DECL_AURA oswindow set_active_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_capture();
CLASS_DECL_AURA oswindow set_capture(oswindow oswindow);
CLASS_DECL_AURA WINBOOL release_capture();
CLASS_DECL_AURA WINBOOL destroy_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_window(oswindow oswindow, int iWindow);
CLASS_DECL_AURA oswindow get_desktop_window();
CLASS_DECL_AURA WINBOOL show_window(oswindow oswindow, int iShow);
CLASS_DECL_AURA WINBOOL set_foreground_window(oswindow oswindow);


#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif



