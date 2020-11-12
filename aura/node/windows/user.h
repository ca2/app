#pragma once


#include "interaction_impl.h"


CLASS_DECL_AURA const unichar * __register_window_class(::object * pobject, ::u32 nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);

CLASS_DECL_AURA bool windows_register_class(WNDCLASSW * pwndclass);



//CLASS_DECL_AURA WNDPROC __get_window_procedure();
//#define __window_procedure (*__get_window_procedure())
extern CLASS_DECL_AURA const unichar gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_AURA const unichar gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_AURA const unichar gen_WndMDIFrame[];
extern CLASS_DECL_AURA const unichar gen_WndFrameOrView[];
extern CLASS_DECL_AURA const unichar gen_WndOleControl[];
CLASS_DECL_AURA bool __is_combo_box_control(oswindow oswindow, ::u32 nStyle);
CLASS_DECL_AURA bool __check_center_dialog(const char * pszResource);

CLASS_DECL_AURA bool __compare_class_name(oswindow oswindow, const char * pszClassName);

CLASS_DECL_AURA oswindow __child_window_from_point(oswindow, const point &);
CLASS_DECL_AURA bool hook_window_create(::windows::interaction_impl * pwindow);
CLASS_DECL_AURA bool unhook_window_create();
CLASS_DECL_AURA void reset_message_cache();




