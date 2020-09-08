//
//  os_os.h
//  apex
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#if defined(MACOS)

#include "apex/os/apple/_apple.h"
#include "apex/os/macos/_macos.h"
#include "apex/os/ansios/_ansios.h"

#elif defined(APPLE_IOS)

#include "apex/os/apple/_apple.h"
#include "apex/os/ios/_ios.h"
#include "apex/os/ansios/_ansios.h"

#elif defined(LINUX)

#include "apex/os/linux/_linux.h"
#include "apex/os/linux/_user.h"
#include "apex/os/ansios/_ansios.h"
#include "apex/os/cross/windows/windows.h"

#elif defined(_UWP)

#include "apex/os/ansios/_ansios.h"
#include "apex/os/uwp/_uwp.h"

#elif defined(WINDOWS_DESKTOP)

#include "apex/os/windows/_.h"
#include "apex/os/windows/_windows.h"

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



