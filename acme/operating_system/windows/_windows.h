#pragma once


#include "_c.h"
#include "acme/parallelization/types.h"
#include "acme/operating_system/windows/_.h"


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include <windowsx.h>


CLASS_DECL_ACME ::operating_system::window as_operating_system_window(HWND hwnd);
CLASS_DECL_ACME HWND as_HWND(const ::operating_system::window & operatingsystemwindow);


CLASS_DECL_ACME void copy(MESSAGE& message, const MSG &msg);
CLASS_DECL_ACME void copy(MSG& msg, const MESSAGE& message);


inline ::i32 width(RECT & r) { return r.right - r.left; }

inline ::i32 height(RECT & r) { return r.bottom - r.top; }


inline ::i32_point lparam_as_point(LPARAM lparam)
{

   return ::i32_point(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));

}


inline HANDLE as_HANDLE(const htask &htask) { return (HANDLE)htask.m_h; }



