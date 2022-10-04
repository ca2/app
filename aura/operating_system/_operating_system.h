//
//  os_os.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/01/18.
//
#pragma once


#include "apex/operating_system/_operating_system.h"


#if defined(MACOS)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/apple/_apple.h"
#include "aura/operating_system/macos/_macos.h"

#elif defined(APPLE_IOS)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/apple/_apple.h"
#include "aura/operating_system/ios/_ios.h"

#elif defined(LINUX)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/linux/_linux.h"
#include "aura/operating_system/linux/_user.h"

#elif defined(FREEBSD)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/freebsd/_freebsd.h"
#include "aura/operating_system/freebsd/_user.h"

#elif defined(_UWP)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/windows_common/_windows_common.h"
#include "aura/operating_system/universal_windows/_universal_windows.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/operating_system/windows/_.h"
#include "aura/operating_system/windows/_windows.h"

#elif defined(ANDROID)

#include "aura/operating_system/ansi/_ansi.h"
#include "aura/operating_system/android/_android.h"

#elif defined(SOLARIS)

#include "aura/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "aura/os/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif



