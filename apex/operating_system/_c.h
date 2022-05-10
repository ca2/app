//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once


CLASS_DECL_ACME const char* executable_get_app_id();


#include "acme/operating_system/_c.h"


#if defined(MACOS)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/apple/_c.h"
#include "apex/operating_system/macos/_c.h"

#elif defined(APPLE_IOS)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/apple/_c.h"
#include "apex/operating_system/ios/_c.h"

#elif defined(LINUX)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/posix/_c.h"
#include "apex/operating_system/linux/_c.h"

#elif defined(FREEBSD)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/posix/_c.h"
#include "apex/operating_system/freebsd/_c.h"

#elif defined(_UWP)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/windows_common/_c.h"
#include "apex/operating_system/universal_windows/_c.h"

#elif defined(WINDOWS_DESKTOP)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/windows_common/_c.h"
#include "apex/operating_system/windows/_c.h"

#elif defined(ANDROID)

#include "apex/operating_system/ansi/_c.h"
#include "apex/operating_system/android/_c.h"

#elif defined(SOLARIS)

#include "apex/os/ansios/_c.h"
#include "apex/os/solaris/_c.h"

#else

#error "The operating system wasn't expected."

#endif



