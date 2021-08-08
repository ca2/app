#pragma once


//#include <shellapi.h>
//#include <wincrypt.h>

#include "parallelization.h"
#include "utils.h"
//#include "graphics.h"




CLASS_DECL_ACME char get_drive_letter(const char * pDevicePath);


CLASS_DECL_ACME void set_main_hthread(htask_t htask);
CLASS_DECL_ACME void set_main_ithread(itask_t itask);


CLASS_DECL_ACME htask_t get_main_hthread();
CLASS_DECL_ACME itask_t get_main_ithread();


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd);
//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle();
//CLASS_DECL_ACME bool GetPrimaryMonitorRect(RECTANGLE_I32 * prectangle);





//#define MESSAGE MSG
//#define MESSAGE * LPMSG



