#pragma once


#include "acme/node/operating_system/windows/_.h"


#include "windowing.h"


inline HWND __hwnd(oswindow oswindow)
{

   return (HWND)oswindow;

}


inline oswindow __oswindow(HWND hwnd)
{

   return (oswindow)hwnd;

}


