//
//  os_os.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#include "apex/node/operating_system/_operating_system.h"


#if defined(MACOS)

#include "aura/os/apple/_apple.h"
#include "aura/os/macos/_macos.h"
#include "aura/os/ansios/_ansios.h"

#elif defined(APPLE_IOS)

#include "aura/os/apple/_apple.h"
#include "aura/os/ios/_ios.h"
#include "aura/os/ansios/_ansios.h"

#elif defined(LINUX)

#include "aura/node/operating_system/ansi/_ansi.h"
#include "aura/node/operating_system/linux/_linux.h"
#include "aura/node/operating_system/linux/_user.h"

#elif defined(_UWP)

#include "aura/os/ansios/_ansios.h"
#include "aura/os/uwp/_uwp.h"
#include "aura/os/windows_common/_windows_common.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/node/operating_system/windows/_.h"
#include "aura/node/operating_system/windows/_windows.h"

#elif defined(ANDROID)

#include "aura/os/ansios/_ansios.h"
#include "aura/os/android/_android.h"

#elif defined(SOLARIS)

#include "aura/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "aura/os/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif



