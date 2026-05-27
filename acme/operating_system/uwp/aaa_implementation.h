#pragma once

//#define __defer_register_class(fClass) __end_defer_register_class(fClass)

//CLASS_DECL_ACME bool __end_defer_register_class(::i32 fToRegister, const_char_pointer * ppszClass);


// Temporary ::map management (locks temp ::map on current thread)
//CLASS_DECL_ACME void ::ca2::LockTempMaps(::particle * pparticle);
//CLASS_DECL_ACME bool ::ca2::UnlockTempMaps(::particle * pparticle, bool bDeleteTemps = true);



// from wincore.cpp
extern CLASS_DECL_ACME const ::i8 gen_Wnd[];           // simple child windows/controls
extern CLASS_DECL_ACME const ::i8 gen_WndControlBar[]; // controls with gray backgrounds
extern CLASS_DECL_ACME const ::i8 gen_WndMDIFrame[];
extern CLASS_DECL_ACME const ::i8 gen_WndFrameOrView[];
extern CLASS_DECL_ACME const ::i8 gen_WndOleControl[];


/////////////////////////////////////////////////////////////////////////////
// Special helpers

CLASS_DECL_ACME void __cancel_modes(oswindow hWndRcvr);
CLASS_DECL_ACME bool __help_enabled();  // determine if ID_HELP handler exists
CLASS_DECL_ACME bool __custom_log_font(::u32 nIDS, LOGFONT* pLogFont);
CLASS_DECL_ACME bool __get_prop_sheet_font(string & strFace, ::u16& wSize, bool bWizard);

CLASS_DECL_ACME bool __is_combo_box_control(oswindow hWnd, ::u32 nStyle);
CLASS_DECL_ACME bool __check_center_dialog(const_char_pointer pszResource);
CLASS_DECL_ACME bool __compare_class_name(oswindow hWnd, const_char_pointer pszClassName);
CLASS_DECL_ACME oswindow __child_window_from_point(oswindow, POINT32);

// for determining version of COMCTL32.DLL
#define VERSION_WIN4    make_int(0, 4)
#define VERSION_IE3             make_int(70, 4)
#define VERSION_IE4             make_int(71, 4)
#define VERSION_IE401   make_int(72, 4)
#define VERSION_6      make_int(0, 6)
extern ::i32 gen_ComCtlVersion;
::u32 __get_common_controls_version();
