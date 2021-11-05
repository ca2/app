#pragma once



#ifndef WINDOWS

#ifdef cplusplus

class event;

#endif

//struct oswindow_data;
//
//typedef struct oswindow_data * oswindow;

#endif



/*
 * Defines for the fVirt field of the Accelerator table structure.
 */
#define WIN_FVIRTKEY  true          /* Assumed to be == true */
#define WIN_FNOINVERT 0x02
#define WIN_FSHIFT    0x04
#define WIN_FCONTROL  0x08
#define WIN_FALT      0x10




#ifndef WINDOWS_DESKTOP

#ifdef LINUX
#undef inline
#endif

#ifndef _UWP

#include "windows/windows_thread.h"

#endif

#endif


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID) || defined(SOLARIOS)

//#include "ansios/ansios_file_raw.h"

#else

//#include "ansios/ansios.h"

#endif



