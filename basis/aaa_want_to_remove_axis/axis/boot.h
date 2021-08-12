#pragma once


#include "axis/axis/axis.h"


#ifndef __cplusplus
   #error ca API requires C++ compilation (use a .cpp suffix)
#endif


#ifdef _BOOT_STATIC
   #define CLASS_DECL_BOOT
#elif defined(_BOOT_LIBRARY)
   #define CLASS_DECL_BOOT  CLASS_DECL_EXPORT
#else
   #define CLASS_DECL_BOOT  CLASS_DECL_IMPORT
#endif


class application;


#if defined(APPLEOS)
#include "boot/macos/ca_os_internal.h"
#elif defined(LINUX)
#include "boot/linux/ca_os_internal.h"
#elif defined(_UWP)
#include "boot/_UWP/ca_os_internal.h"
#elif defined(WINDOWS)
#include "boot/windows/ca_os_internal.h"
#elif defined(ANDROID)
#include "boot/android/ca_os_internal.h"
#endif





#include "boot/vms/vms.h"


#include "boot_cpu_architecture.h"


#include "boot_libc.h"


#include "boot_number.h"


#include "boot_debug.h"


#include "boot_printf.h"
#include "boot_sprintf.h"



#include "boot_math.h"


//#include "boot_library.h"


#include "boot_file_watcher.h"
#include "boot_file_watcher_impl.h"



/*#ifndef WINDOWS
#define VK_TAB 1
#define VK_RETURN 2
#define VK_BACK 3
#define VK_DELETE 6
#define VK_SPACE 9
#endif*/

#include "boot_os.h"

//#include "boot/cross/cross.h"




#include "boot_simple_shell_launcher.h"



#include "boot_file_watcher_thread.h"
#include "boot_file_watcher_listener_thread.h"
#include "boot_async.h"


//#include "boot/hotplugin/hotplugin.h"




#include "boot_message_loop.h"

#include "boot_url.h"

#include "boot_international.h"



#define return_(y, x) {y = x; return;}


extern "C"
{


   i32 _c_lock_is_active(const ::string & pszName);
   i32 _c_lock(const ::string & pszName, void ** pdata);
   i32 _c_unlock(void ** pdata);


}


CLASS_DECL_BOOT string _ca_get_file_name(const ::string & psz, bool bCreate = false, i32 * pfd = nullptr);

CLASS_DECL_AXIS string get_last_error_message(u32 dwError);


#include "boot_simple_app.h"


