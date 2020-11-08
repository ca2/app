#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
//#include "apex/user/_user.h"
#endif
#include "apex/message.h"

#define __msg_entry(x) if(uMessage == (x)) { str = (#x); }

CLASS_DECL_APEX string get_message_text(UINT uMessage, bool bWithNumbers)
{
   string str;
   if (uMessage == -1)
   {
      str = "-1";
   }
   else __msg_entry(WM_NULL)
else __msg_entry(e_message_create)
else __msg_entry(e_message_destroy)
else __msg_entry(e_message_move)
else __msg_entry(e_message_size)
else __msg_entry(e_message_activate)
else __msg_entry(e_message_set_focus)
else __msg_entry(e_message_kill_focus)
else __msg_entry(WM_ENABLE)
else __msg_entry(WM_SETREDRAW)
else __msg_entry(WM_SETTEXT)
else __msg_entry(WM_GETTEXT)
else __msg_entry(WM_GETTEXTLENGTH)
else __msg_entry(WM_PAINT)
else __msg_entry(e_message_close)
else __msg_entry(WM_QUERYENDSESSION)
else __msg_entry(WM_QUERYOPEN)
else __msg_entry(WM_ENDSESSION)
else __msg_entry(e_message_quit)
else __msg_entry(WM_ERASEBKGND)
else __msg_entry(WM_SYSCOLORCHANGE)
else __msg_entry(WM_SHOWWINDOW)
else __msg_entry(WM_WININICHANGE)
else __msg_entry(WM_SETTINGCHANGE)
else __msg_entry(WM_DEVMODECHANGE)
else __msg_entry(WM_ACTIVATEAPP)
else __msg_entry(WM_FONTCHANGE)
else __msg_entry(WM_TIMECHANGE)
else __msg_entry(WM_CANCELMODE)
else __msg_entry(WM_SETCURSOR)
else __msg_entry(WM_MOUSEACTIVATE)
else __msg_entry(WM_CHILDACTIVATE)
else __msg_entry(WM_QUEUESYNC)
else __msg_entry(WM_GETMINMAXINFO)
else __msg_entry(WM_PAINTICON)
else __msg_entry(WM_ICONERASEBKGND)
else __msg_entry(WM_NEXTDLGCTL)
else __msg_entry(WM_SPOOLERSTATUS)
else __msg_entry(WM_DRAWITEM)
else __msg_entry(WM_MEASUREITEM)
else __msg_entry(WM_DELETEITEM)
else __msg_entry(WM_VKEYTOITEM)
else __msg_entry(WM_CHARTOITEM)
else __msg_entry(WM_SETFONT)
else __msg_entry(WM_GETFONT)
else __msg_entry(WM_SETHOTKEY)
else __msg_entry(WM_GETHOTKEY)
else __msg_entry(WM_QUERYDRAGICON)
else __msg_entry(WM_COMPAREITEM)

else __msg_entry(WM_GETOBJECT) // 0x003D 61

else __msg_entry(WM_COMPACTING)
else __msg_entry(WM_COMMNOTIFY)
else __msg_entry(WM_WINDOWPOSCHANGING)
else __msg_entry(WM_WINDOWPOSCHANGED)

else __msg_entry(WM_POWER)// 0x0048




else __msg_entry(WM_COPYDATA)//                     0x004A
else __msg_entry(WM_CANCELJOURNAL) //                0x004B



else __msg_entry(WM_NOTIFY)//    0x004E
else __msg_entry(WM_INPUTLANGCHANGEREQUEST)//    0x0050
else __msg_entry(WM_INPUTLANGCHANGE)//    0x0051
else __msg_entry(WM_TCARD)//    0x0052
else __msg_entry(WM_HELP)//    0x0053
else __msg_entry(WM_USERCHANGED)//    0x0054
else __msg_entry(WM_NOTIFYFORMAT)//    0x0055

else __msg_entry(WM_CONTEXTMENU)
else __msg_entry(WM_STYLECHANGING)
else __msg_entry(WM_STYLECHANGED)
else __msg_entry(WM_DISPLAYCHANGE)
else __msg_entry(WM_GETICON)
else __msg_entry(WM_SETICON)
else __msg_entry(WM_NCCREATE)
else __msg_entry(WM_NCDESTROY)
else __msg_entry(WM_NCCALCSIZE)
else __msg_entry(WM_NCHITTEST)
else __msg_entry(WM_NCPAINT)
else __msg_entry(WM_NCACTIVATE)
else __msg_entry(WM_GETDLGCODE)


else __msg_entry(WM_SYNCPAINT)//)//      0x0088

else __msg_entry(e_message_non_client_mouse_move)//)//      0x00A0
else __msg_entry(WM_NCLBUTTONDOWN)//)//      0x00A1
else __msg_entry(WM_NCLBUTTONUP)//)//      0x00A2
else __msg_entry(WM_NCLBUTTONDBLCLK)//)//      0x00A3
else __msg_entry(WM_NCRBUTTONDOWN)//)//      0x00A4
else __msg_entry(WM_NCRBUTTONUP)//           0x00A5
else __msg_entry(WM_NCRBUTTONDBLCLK)//           0x00A6
else __msg_entry(WM_NCMBUTTONDOWN)//           0x00A7
else __msg_entry(WM_NCMBUTTONUP)//           0x00A8
else __msg_entry(WM_NCMBUTTONDBLCLK)      //           0x00A9

else __msg_entry(e_message_key_first)      //            0x0100
else __msg_entry(e_message_key_down)      //            0x0100
else __msg_entry(e_message_key_up)      //            0x0101
else __msg_entry(e_message_char)      //            0x0102
else __msg_entry(e_message_dead_char)      //            0x0103
else __msg_entry(e_message_sys_key_down)      //            0x0104
else __msg_entry(e_message_sys_key_up)      //            0x0105
else __msg_entry(e_message_sys_char)      //            0x0106
else __msg_entry(e_message_sys_dead_char)      //            0x0107



else __msg_entry(e_message_uni_char)      //            0x0109
else __msg_entry(e_message_key_last)      //            0x0109


else __msg_entry(WM_INITDIALOG)      //             0x0110
else __msg_entry(WM_COMMAND)      //             0x0111
else __msg_entry(WM_SYSCOMMAND)      //             0x0112
else __msg_entry(WM_TIMER)      //             0x0113
else __msg_entry(WM_HSCROLL)      //             0x0114
else __msg_entry(WM_VSCROLL)      //             0x0115
else __msg_entry(WM_INITMENU)      //             0x0116
else __msg_entry(WM_INITMENUPOPUP)      //             0x0117

else __msg_entry(WM_IME_SETCONTEXT) //)//  0x281
else __msg_entry(WM_IME_NOTIFY)
else __msg_entry(WM_IME_CONTROL)
else __msg_entry(WM_IME_COMPOSITIONFULL)
else __msg_entry(WM_IME_SELECT)
else __msg_entry(WM_IME_CHAR)


else __msg_entry(WM_IME_REQUEST) // 0x0288


else __msg_entry(WM_IME_KEYDOWN) // 0x290
else __msg_entry(WM_IME_KEYUP)


else __msg_entry(WM_DWMCOMPOSITIONCHANGED) //        0x031E
else __msg_entry(WM_DWMNCRENDERINGCHANGED)   //     0x031F
else __msg_entry(WM_DWMCOLORIZATIONCOLORCHANGED) //  0x0320
else __msg_entry(WM_DWMWINDOWMAXIMIZEDCHANGE)  //   0x0321

else
{
str.Format("message 0x%04x (%d)", uMessage, uMessage);

return str;

 }
 str.trim();

 if (!bWithNumbers)
 {
    return str;

 }

 string strNumbers;

 strNumbers.Format("%s 0x%04x (%d)", str.c_str(), uMessage, uMessage);

 return strNumbers;

}

UINT g_puiaMessageMouseMove[] =
{

   e_message_mouse_move,
   WM_SETCURSOR,
   WM_NCHITTEST,
   e_message_non_client_mouse_move,
   (UINT)-1
};

UINT g_puiaMessageWindowDeactivating[] =
{
   // 2019-06-28-00-28
   WM_NCACTIVATE,
   e_message_activate,
   WM_ACTIVATEAPP,
   e_message_kill_focus,
   WM_IME_SETCONTEXT,
   WM_IME_NOTIFY,
   (UINT)-1
};

UINT g_puiaMessageWindowActivating[] =
{
   // 2019-06-28-00-33
   WM_WINDOWPOSCHANGING,
   WM_WINDOWPOSCHANGED,
   WM_ACTIVATEAPP,
   WM_NCACTIVATE,
   WM_SYSCOMMAND,
   e_message_activate,
   WM_IME_SETCONTEXT,
   WM_IME_NOTIFY,
   e_message_set_focus,


   (UINT)-1
};

UINT f[] =
{
   // IME, Input Method Editor Client : ca2 Framework
   // Viagem da Mummi... : Yakissoba delicioso!!
   // 2019-06-27-22-36
   WM_GETMINMAXINFO,
   WM_NCCREATE,
   WM_NCCALCSIZE,
   e_message_create,
   WM_SETICON,
   WM_SETTEXT,
   e_message_size,
   e_message_move,
   WM_SHOWWINDOW,
   WM_WINDOWPOSCHANGING,
   WM_ACTIVATEAPP,
   WM_NCACTIVATE,
   e_message_activate,
   WM_IME_SETCONTEXT,
   WM_IME_NOTIFY,
   e_message_set_focus,
   WM_NCPAINT,
   WM_ERASEBKGND,
   WM_WINDOWPOSCHANGED,
   WM_GETICON,
   WM_DWMNCRENDERINGCHANGED,
   WM_PAINT,
   e_message_redraw,
   (UINT)-1
};


UINT g_puiaMessageWindowCreated[] =
{
   WM_GETICON,
   (UINT)-1
};


UINT g_puiaMessageInputLanguageChange[] =
{
   // IME, Input Method Editor Client : ca2 Framework
   // Mummi no �nibus... already missing!!
   // Twitch Streamers Vibe : Denzel@RB.TV, jitspoe, FearItSelf, WildN00b, AndyMilonakis
   // 2019-06-27-23-19
   // 2019-06-38-00-06 Talk2meGooseman
   WM_INPUTLANGCHANGE,
   WM_IME_NOTIFY,
   e_message_key_up,
   (UINT)-1
};



