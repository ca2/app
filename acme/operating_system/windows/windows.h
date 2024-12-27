// From windowing_win32/window_win32.cpp by camilo on 2024-12-27 5:00 <3ThomasBorregaardSorensen!!
#pragma once


namespace windows
{


   CLASS_DECL_ACME HWND get_mouse_capture(itask_t itask);
   CLASS_DECL_ACME bool set_mouse_capture(itask_t itask, HWND hwnd);
   CLASS_DECL_ACME bool defer_release_mouse_capture(itask_t itask, HWND hwnd);


} // namespace windows



