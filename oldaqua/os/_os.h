//
//  os_os.h
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#if defined(MACOS)

#include "aqua/os/apple/_apple.h"
#include "aqua/os/macos/_macos.h"
#include "aqua/os/ansios/_ansios.h"

#elif defined(APPLE_IOS)

#include "aqua/os/apple/_apple.h"
#include "aqua/os/ios/_ios.h"
#include "aqua/os/ansios/_ansios.h"

#elif defined(LINUX)

#include "aqua/os/linux/_linux.h"
#include "aqua/os/linux/_user.h"
#include "aqua/os/ansios/_ansios.h"
#include "aqua/os/cross/windows/windows.h"

#elif defined(_UWP)

#include "aqua/os/ansios/_ansios.h"
#include "aqua/os/uwp/_uwp.h"

#elif defined(WINDOWS_DESKTOP)

#include "aqua/os/windows/_.h"
#include "aqua/os/windows/_windows.h"

#elif defined(ANDROID)

#include "aqua/os/ansios/_ansios.h"
#include "aqua/os/android/_android.h"

#elif defined(SOLARIS)

#include "aqua/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "aqua/os/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif



