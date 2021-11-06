//
//  os_os.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#if defined(MACOS)

#include "acme/node/operating_system/apple/_apple.h"
#include "acme/node/operating_system/macos/_macos.h"
#include "acme/node/operating_system/ansi/_ansi.h"

#elif defined(APPLE_IOS)

#include "acme/node/operating_system/apple/_apple.h"
#include "acme/node/operating_system/ios/_ios.h"
#include "acme/node/operating_system/ansi/_ansi.h"

#elif defined(LINUX)

#include "acme/node/operating_system/ansi/_ansi.h"
#include "acme/node/operating_system/posix/_posix.h"
#include "acme/node/operating_system/linux/_linux.h"

#elif defined(_UWP)

#include "acme/node/operating_system/ansi/_ansi.h"
#include "acme/node/operating_system/windows_common/_windows_common.h"
#include "acme/node/operating_system/universal_windows/_universal_windows.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/node/operating_system/windows_common/_windows_common.h"
#include "acme/node/operating_system/windows/_windows.h"

#elif defined(ANDROID)

#include "acme/node/operating_system/ansi/_ansi.h"
#include "acme/node/operating_system/android/_android.h"

#elif defined(SOLARIS)

#include "acme/node/operating_system/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "acme/node/operating_system/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif


CLASS_DECL_ACME int __node_is_debugger_attached();



