#pragma once



#ifndef _UWP




::u32 get_current_process_id(void);




#include "windows_guid_def.h"
#include "windows_winnt.h"
#include "windows_error.h"
#include "windows_errno.h"
#include "windows_base_tsd.h"
#include "windows_defs.h"
#include "windows_base.h"
#include "windows_crtdefs.h"
#include "windows_nls.h"
#include "windows_crt.h"
#include "windows_types.h"
#include "windows_gdi.h"
#endif


#include "windows_user.h"
#include "parallelization.h"



#ifndef _UWP
#include "windows_ole_automation.h"
#include "windows_shared_memory.h"
#endif



#include "windows_time.h"

#include "windows_common_controls.h"


#include "windows_wincon.h"


#ifndef _UWP
#include "windows_base_tsd.h"
#endif



#include "windows_internals.h"


#ifndef _UWP
#include "windows_file.h"
#include "windows_ntstatus.h"
#include "windows_mmeapi.h"
#include "windows_mmsystem.h"




#define _swab swab


#endif






