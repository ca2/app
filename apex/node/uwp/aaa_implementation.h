#pragma once

//#define __defer_register_class(fClass) __end_defer_register_class(fClass)

//CLASS_DECL_APEX bool __end_defer_register_class(::i32 fToRegister, const char ** ppszClass);


// Temporary ::map management (locks temp ::map on current thread)
//CLASS_DECL_APEX void ::ca2::LockTempMaps(::object * pobject);
//CLASS_DECL_APEX bool ::ca2::UnlockTempMaps(::object * pobject, bool bDeleteTemps = true);



// from wincore.cpp
extern CLASS_DECL_APEX const char gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_APEX const char gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_APEX const char gen_WndMDIFrame[];
extern CLASS_DECL_APEX const char gen_WndFrameOrView[];
extern CLASS_DECL_APEX const char gen_WndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_APEX void __cancel_modes(oswindow hWndRcvr);
CLASS_DECL_APEX bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_APEX bool __custom_log_font(::u32 nIDS, LOGFONT* pLogFont);
CLASS_DECL_APEX bool __get_prop_sheet_font(string & strFace, ::u16& wSize, bool bWizard);

CLASS_DECL_APEX bool __is_combo_box_control(oswindow hWnd, ::u32 nStyle);
CLASS_DECL_APEX bool __check_center_dialog(const char * lpszResource);
CLASS_DECL_APEX bool __compare_class_name(oswindow hWnd, const char * lpszClassName);
CLASS_DECL_APEX oswindow __child_window_from_point(oswindow, POINT32);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    __MAKE_LONG(0, 4)
#define VERSION_IE3             __MAKE_LONG(70, 4)
#define VERSION_IE4             __MAKE_LONG(71, 4)
#define VERSION_IE401   __MAKE_LONG(72, 4)
#define VERSION_6      __MAKE_LONG(0, 6)
extern int gen_ComCtlVersion;
::u32 __get_common_controls_version();
