#pragma once




CLASS_DECL_AQUA wstring windows_register_window_class(::object * pobject, UINT nClassStyle, HCURSOR hCursor = 0, HBRUSH hbrBackground = 0, HICON hIcon = 0);
CLASS_DECL_AQUA bool windows_register_class(WNDCLASSEXW* pwndclass);

CLASS_DECL_AQUA wstring windows_calc_icon_window_class(::user::interaction * pinteraction, u32 dwDefaultStyle, const char * pszMatter);
CLASS_DECL_AQUA wstring windows_get_user_interaction_window_class(::user::interaction * pinteraction);
CLASS_DECL_AQUA bool windows_register_with_icon(WNDCLASSEXW* pwndclass, const unichar * pszClassName, UINT nIDIcon);

CLASS_DECL_AQUA void window_create_caret(oswindow oswindow, HBITMAP hbitmap);
CLASS_DECL_AQUA void window_create_solid_caret(oswindow oswindow, i32 nWidth, i32 nHeight);
CLASS_DECL_AQUA void window_create_gray_caret(oswindow oswindow, i32 nWidth, i32 nHeight);

/// from top to bottom
CLASS_DECL_AQUA __pointer(::user::oswindow_array) get_top_level_windows(bool bDesktop = true, bool bVisible = true);



