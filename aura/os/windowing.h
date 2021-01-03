//
//  os_windowing.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


CLASS_DECL_AURA int_bool os_init_windowing();

CLASS_DECL_AURA void os_term_windowing();

CLASS_DECL_AURA i64 oswindow_id(oswindow w);

CLASS_DECL_AURA int_bool is_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_focus();
CLASS_DECL_AURA oswindow set_focus(oswindow oswindow);
CLASS_DECL_AURA bool remove_focus(oswindow oswindow);
CLASS_DECL_AURA bool clear_focus();
CLASS_DECL_AURA oswindow get_active_window();
CLASS_DECL_AURA oswindow set_active_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_capture();
CLASS_DECL_AURA oswindow set_capture(oswindow oswindow);
CLASS_DECL_AURA int_bool release_capture();
CLASS_DECL_AURA int_bool destroy_window(oswindow oswindow);
CLASS_DECL_AURA oswindow get_window(oswindow oswindow, enum_relative erelative);
CLASS_DECL_AURA oswindow get_desktop_window();
CLASS_DECL_AURA int_bool show_window(oswindow oswindow, const ::e_display & edisplay, const ::e_activation & eactivation = e_activation_default);
CLASS_DECL_AURA int_bool set_foreground_window(oswindow oswindow);

CLASS_DECL_AURA int GetMainScreenRect(LPRECT32 lprect);


#ifdef WINDOWS_DESKTOP
CLASS_DECL_AURA bool get_gui_thread_info(PGUITHREADINFO pinfo);
#endif



