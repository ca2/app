//
//  os_windowing.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 10/12/17.
//
#pragma once


#ifndef WINDOWS


/*
* e_message_size message wParam values
*/
#define SIZE_RESTORED       0
#define SIZE_MINIMIZED      1
#define SIZE_MAXIMIZED      2
#define SIZE_MAXSHOW        3
#define SIZE_MAXHIDE        4


/*
* Identifiers for the e_message_show_window message
*/
#define SW_PARENTCLOSING    1
#define SW_OTHERZOOM        2
#define SW_PARENTOPENING    3


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
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_non_client_calcsize */
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
#define SWP_FRAMECHANGED    0x0020  /* The frame changed: send e_message_non_client_calcsize */
#define SWP_SHOWWINDOW      0x0040
#define SWP_HIDEWINDOW      0x0080
#define SWP_NOCOPYBITS      0x0100
#define SWP_NOOWNERZORDER   0x0200  /* Don't do owner Z ordering */
#define SWP_NOSENDCHANGING  0x0400  /* Don't send e_message_window_position_changing */

#define SWP_DRAWFRAME       SWP_FRAMECHANGED
#define SWP_NOREPOSITION    SWP_NOOWNERZORDER
#define SWP_DEFERERASE      0x2000
#define SWP_ASYNCWINDOWPOS  0x4000


#endif


struct SIZEPARENTPARAMS
{

   RECTANGLE_I32  rectangle;     // parent client rectangle (trim as appropriate)
   SIZE_I32       sizeTotal;     // total size on each side as on_layout proceeds
   bool           bStretch;      // should stretch to fill all space

};


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
