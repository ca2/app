#include "framework.h"


#if !defined(__ANDROID__) && !defined(WINDOWS_DESKTOP)
#include "ansios_serial.cpp"
#include "ansios_base.cpp"
#endif

#include "ansios_file_std.cpp"

#if !defined(WINDOWS_DESKTOP)

#include "ansios_message_loop.cpp"
#if !defined(UNIVERSAL_WINDOWS)
#include "ansios_base_file.cpp"
#include "ansios_cross_win.cpp"
#include "ansios_cross_windows_user.cpp"
#include "ansios_cross_win_file.cpp"

#include "ansios_local_memory_map.cpp"
#include "ansios_multitasking.cpp"
#include "ansios_process.cpp"
#include "ansios_time.cpp"
#endif

#endif

