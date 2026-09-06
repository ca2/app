// From windowing_win32/window_win32.cpp by camilo on 2024-12-27 5:00 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/operating_system/windows/window_util.h"


namespace windows
{

   CLASS_DECL_ACME ::u32 get_windows_build_number();
   CLASS_DECL_ACME bool is_windows_11();
   CLASS_DECL_ACME bool is_windows_10();

   CLASS_DECL_ACME HWND get_mouse_capture(itask itask);
   CLASS_DECL_ACME bool set_mouse_capture(itask itask, HWND hwnd);
   CLASS_DECL_ACME bool defer_release_mouse_capture(itask itask, HWND hwnd);



   CLASS_DECL_ACME ::i32 message_box_to_windows_message_box(const ::user::e_message_box & emessagebox);
   CLASS_DECL_ACME ::i32 message_box_to_windows_message_box_type(const ::user::e_message_box & emessagebox);
   CLASS_DECL_ACME ::i32 message_box_to_windows_message_box_icon(const ::user::e_message_box & emessagebox);
   CLASS_DECL_ACME ::i32 message_box_to_windows_message_box_default_button(const ::user::e_message_box & emessagebox);
 

   CLASS_DECL_ACME::enum_dialog_result windows_message_box_result_to_dialog_result(::i32 iResult);

   CLASS_DECL_ACME ::pointer<::windows::hwnd_array>get_top_level_windows(bool bDesktop = true, bool bVisible = true);


} // namespace windows



