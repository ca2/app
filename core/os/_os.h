//
//  os_os.h
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#if defined(MACOS)

#include "aura/os/apple/_apple.h"
#include "aura/os/macos/_macos.h"
#include "aura/os/ansios/_ansios.h"

#elif defined(APPLE_IOS)

#include "aura/os/apple/_apple.h"
#include "aura/os/ios/_ios.h"
#include "aura/os/ansios/_ansios.h"

#elif defined(LINUX)

#include "aura/os/linux/_linux.h"
#include "aura/os/linux/_user.h"
#include "aura/os/ansios/_ansios.h"
#include "aura/os/cross/windows/windows.h"

#elif defined(_UWP)

#include "aura/os/ansios/_ansios.h"
#include "aura/os/universal_windows/_uwp.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/os/windows/_.h"
#include "aura/os/windows/_windows.h"

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



