#pragma once


#include "acme/operating_system/windows/_c.h"


inline HWND as_hwnd(oswindow oswindow)
{

   return (HWND)oswindow;

}


inline oswindow __oswindow(HWND hwnd)
{

   return (oswindow)hwnd;

}


