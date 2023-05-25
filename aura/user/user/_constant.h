// First insertion 2022-08-25 04:50 <3ThomasBorregaardSørensen!!
#pragma once



namespace user
{




   enum enum_interaction
   {

      e_interaction_wfi_up_down_loading = 1 << 0,
      e_interaction_wfi_up_tool_window = 1 << 1,

   };


   enum enum_text_composition_state
   {

      e_text_composition_state_none,
      e_text_composition_state_composing,
      e_text_composition_state_selected,

   };


   enum enum_still
   {


      e_still_none,
      e_still_text,
      e_still_icon,
      e_still_image


   };


   class plain_text_tree;

   enum enum_plain_text_command
   {
      
      e_plain_text_command_none,
      e_plain_text_command_set_sel,
      e_plain_text_command_file,
      e_plain_text_command_group,


   };

} // namespace user





// flags for wParam in the WM_FLOATSTATUS message
enum
{
   FS_SHOW = 0x01, FS_HIDE = 0x02,
   FS_ACTIVATE = 0x04, FS_DEACTIVATE = 0x08,
   FS_ENABLE = 0x10, FS_DISABLE = 0x20,
   FS_SYNCACTIVE = 0x40
};




/////////////////////////////////////////////////////////////////////////////
// Global ID ranges (see Technical note TN020 for more details)

// 8000 -> FFFF command IDs (used for menu items, accelerators and controls)
#define IS_COMMAND_ID(nID)  ((nID) & 0x8000)

// 8000 -> DFFF : ::account::user commands
// E000 -> EFFF : _ commands and other things
// F000 -> FFFF : standard windows commands and other things etc
// E000 -> E7FF standard commands
// E800 -> E8FF control bars (first 32 are special)
// E900 -> EEFF standard interaction_impl controls/components
// EF00 -> EFFF SC_ menu help
// F000 -> FFFF standard strings
#define ID_COMMAND_FROM_SC(sc)  (((sc - 0xF000) >> 4) + __IDS_SCFIRST)

// 0000 -> 7FFF IDR range
// 0000 -> 6FFF : ::account::user resources
// 7000 -> 7FFF : _ (and standard windows) resources
// IDR ranges (NOTE: IDR_ values must be <32768)
#define ASSERT_VALID_IDR(nIDR) ASSERT((nIDR) != 0 && (nIDR) < 0x8000)

/////////////////////////////////////////////////////////////////////////////
// Context sensitive help support (see Technical note TN028 for more details)

// Help ID bases
#define HID_BASE_COMMAND    0x00010000UL        // ID and IDM
#define HID_BASE_RESOURCE   0x00020000UL        // IDR and IDD
#define HID_BASE_PROMPT     0x00030000UL        // IDP
#define HID_BASE_NCAREAS    0x00040000UL
#define HID_BASE_CONTROL    0x00050000UL        // IDC
#define HID_BASE_DISPATCH   0x00060000UL        // IDispatch help codes




#ifndef TBSTYLE_FLAT
#define TBSTYLE_BUTTON          0x0000  // obsolete; use BTNS_BUTTON instead
#define TBSTYLE_SEP             0x0001  // obsolete; use BTNS_SEP instead
#define TBSTYLE_CHECK           0x0002  // obsolete; use BTNS_CHECK instead
#define TBSTYLE_GROUP           0x0004  // obsolete; use BTNS_GROUP instead
#define TBSTYLE_CHECKGROUP      (TBSTYLE_GROUP | TBSTYLE_CHECK)     // obsolete; use BTNS_CHECKGROUP instead
#define TBSTYLE_DROPDOWN        0x0008  // obsolete; use BTNS_DROPDOWN instead
#define TBSTYLE_AUTOSIZE        0x0010  // obsolete; use BTNS_AUTOSIZE instead
#define TBSTYLE_NOPREFIX        0x0020  // obsolete; use BTNS_NOPREFIX instead

#define TBSTYLE_TOOLTIPS        0x0100
#define TBSTYLE_WRAPABLE        0x0200
#define TBSTYLE_ALTDRAG         0x0400
#define TBSTYLE_FLAT            0x0800
#define TBSTYLE_LIST            0x1000
#define TBSTYLE_CUSTOMERASE     0x2000
#define TBSTYLE_REGISTERDROP    0x4000
#define TBSTYLE_TRANSPARENT     0x8000
#endif

/////////////////////////////////////////////////////////////////////////////
// General style bits etc

// ControlBar styles
#define CBRS_ALIGN_LEFT     0x1000L
#define CBRS_ALIGN_TOP      0x2000L
#define CBRS_ALIGN_RIGHT    0x4000L
#define CBRS_ALIGN_BOTTOM   0x8000L
#define CBRS_ALIGN_ANY      0xF000L

#define CBRS_BORDER_LEFT    0x0100L
#define CBRS_BORDER_TOP     0x0200L
#define CBRS_BORDER_RIGHT   0x0400L
#define CBRS_BORDER_BOTTOM  0x0800L
#define CBRS_BORDER_ANY     0x0F00L

#define CBRS_TOOLTIPS       0x0010L
#define CBRS_FLYBY          0x0020L
#define CBRS_FLOAT_MULTI    0x0040L
#define CBRS_BORDER_3D      0x0080L
#define CBRS_HIDE_INPLACE   0x0008L
#define CBRS_SIZE_DYNAMIC   0x0004L
#define CBRS_SIZE_FIXED     0x0002L
#define CBRS_FLOATING       0x0001L

#define CBRS_GRIPPER        0x00400000L
#define CBRS_LEAVEONFULLSCREEN     0x10000000L

#define CBRS_ORIENT_HORZ    (CBRS_ALIGN_TOP|CBRS_ALIGN_BOTTOM)
#define CBRS_ORIENT_VERT    (CBRS_ALIGN_LEFT|CBRS_ALIGN_RIGHT)
#define CBRS_ORIENT_ANY     (CBRS_ORIENT_HORZ|CBRS_ORIENT_VERT)

#define CBRS_ALL            0x0040FFFFL
//#define CBRS_ALL            0x1140FFFFL

// the CBRS_ style is made up of an alignment style and a draw border style
//  the alignment styles are mutually exclusive
//  the draw border styles may be combined
#define CBRS_NOALIGN        0x00000000L
#define CBRS_LEFT           (CBRS_ALIGN_LEFT|CBRS_BORDER_RIGHT)
#define CBRS_TOP            (CBRS_ALIGN_TOP|CBRS_BORDER_BOTTOM)
#define CBRS_RIGHT          (CBRS_ALIGN_RIGHT|CBRS_BORDER_LEFT)
#define CBRS_BOTTOM         (CBRS_ALIGN_BOTTOM|CBRS_BORDER_TOP)


// Frame interaction_impl styles
#define FWS_ADDTOTITLE  0x00008000L // modify title based on content
#define FWS_PREFIXTITLE 0x00004000L // show document name before cast name
#define FWS_SNAPTOBARS  0x00002000L // snap size_i32 to size_i32 of contained bars




#define SWP_CHANGEVIEWPORTOFFSET  0x100000


#define TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION 256
#define TEXT_COMPOSITION_MESSAGE_UPDATE_CARET 512



#define USER_TIMER 50000




#ifndef LAYOUT_LTR
#define LAYOUT_LTR                         0x00000000
#endif


enum enum_show_window
{

   e_show_window_parent_closing = 1,// SW_PARENTCLOSING
   e_show_window_other_zoom = 2,// SW_OTHERZOOM
   e_show_window_parent_opening = 3,// SW_PARENTOPENING

};


namespace user
{

   /*
   * e_message_size message wParam values
   */
//#define SIZE_RESTORED       0
//#define SIZE_MINIMIZED      1
//#define SIZE_MAXIMIZED      2
//#define SIZE_MAXSHOW        3
//#define SIZE_MAXHIDE        4

   enum enum_size
   {

      e_size_restored = 0,
      e_size_minimized = 1,
      e_size_maximized = 2,
      e_size_maxshow = 3,
      e_size_maxhide = 4,

   };

} // namespace user


#ifndef WINDOWS_DESKTOP




///*
//* Identifiers for the e_message_show_window message
//*/
//#define SW_PARENTCLOSING    1
//#define SW_OTHERZOOM        2
//#define SW_PARENTOPENING    3


#define GWL_STYLE           (-16)
#define GWL_EXSTYLE         (-20)


#define MK_LBUTTON          0x0001
#define MK_RBUTTON          0x0002
#define MK_SHIFT            0x0004
#define MK_CONTROL          0x0008
#define MK_MBUTTON          0x0010

#define MK_XBUTTON1         0x0020
#define MK_XBUTTON2         0x0040


#define WS_CHILD            0x40000000L
#define WS_VISIBLE          0x10000000L
#define WS_EX_LAYERED       0x00080000


#define WHEEL_DELTA         120


/*
* set_window_position Flags
*/
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_non_client_calc_size */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send e_message_window_position_changing */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER

//#if(WINVER >= 0x0400)
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000
//#endif /* WINVER >= 0x0400 */





/*
* set_window_position Flags
*/
#define SWP_NOSIZE          0x0001
#define SWP_NOMOVE          0x0002
#define SWP_NOZORDER        0x0004
#define SWP_NOREDRAW        0x0008
#define SWP_NOACTIVATE      0x0010
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_non_client_calc_size */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send e_message_window_position_changing */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000


#endif // !defined(WINDOWS)





//CLASS_DECL_ACME i64 oswindow_id(oswindow w);


//CLASS_DECL_ACME int_bool is_window(oswindow oswindow);
//CLASS_DECL_ACME oswindow get_focus();
//CLASS_DECL_ACME oswindow set_focus(oswindow oswindow);
//CLASS_DECL_ACME oswindow get_active_window();
//CLASS_DECL_ACME oswindow set_active_window(oswindow oswindow);
//CLASS_DECL_ACME oswindow get_capture();
//CLASS_DECL_ACME oswindow set_capture(oswindow oswindow);
//CLASS_DECL_ACME int_bool release_capture();
//CLASS_DECL_ACME int_bool destroy_window(oswindow oswindow);
//CLASS_DECL_ACME oswindow get_window(oswindow oswindow, int iWindow);
//CLASS_DECL_ACME oswindow get_desktop_window();
//CLASS_DECL_ACME int_bool show_window(oswindow oswindow, int iShow);
//CLASS_DECL_ACME int_bool set_foreground_window(oswindow oswindow);
//
//
//#ifdef WINDOWS_DESKTOP
//CLASS_DECL_ACME bool get_gui_thread_info(PGUITHREADINFO pinfo);
//#endif
//
//
//



