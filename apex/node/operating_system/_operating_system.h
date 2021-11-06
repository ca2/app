//
//  os_os.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#include "acme/node/operating_system/_operating_system.h"


#if defined(MACOS)

#include "apex/node/operating_system/ansi/_ansi.h"
#include "apex/node/operating_system/apple/_apple.h"
#include "apex/node/operating_system/macos/_macos.h"

#elif defined(APPLE_IOS)

#include "apex/os/apple/_apple.h"
#include "apex/os/ios/_ios.h"
#include "apex/os/ansios/_ansios.h"

#elif defined(LINUX)


#include "apex/node/operating_system/ansi/_ansi.h"
#include "apex/node/operating_system/posix/_posix.h"
#include "apex/node/operating_system/linux/_linux.h"
#include "apex/node/operating_system/linux/_user.h"

#elif defined(_UWP)

#include "apex/node/operating_system/ansi/_ansi.h"
#include "apex/node/operating_system/windows_common/_windows_common.h"
#include "apex/node/operating_system/universal_windows/_universal_windows.h"

#elif defined(WINDOWS_DESKTOP)

#include "apex/node/operating_system/windows_common/_windows_common.h"
#include "apex/node/operating_system/windows/_windows.h"

#elif defined(ANDROID)

#include "apex/os/ansios/_ansios.h"
#include "apex/os/android/_android.h"

#elif defined(SOLARIS)

#include "apex/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "apex/os/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif



