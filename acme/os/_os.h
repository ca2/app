//
//  os_os.h
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
//
#pragma once


#if defined(MACOS)

#include "acme/os/apple/_apple.h"
#include "acme/os/macos/_macos.h"
#include "acme/os/ansios/_ansios.h"

#elif defined(APPLE_IOS)

#include "acme/os/apple/_apple.h"
#include "acme/os/ios/_ios.h"
#include "acme/os/ansios/_ansios.h"

#elif defined(LINUX)

#include "acme/os/linux/_linux.h"
//#include "acme/os/linux/_user.h"
#include "acme/os/ansios/_ansios.h"
#include "acme/os/cross/_cross.h"

#elif defined(_UWP)

#include "acme/os/ansios/_ansios.h"
#include "acme/os/uwp/_uwp.h"

#elif defined(WINDOWS_DESKTOP)

#include "acme/os/windows/_.h"
#include "acme/os/windows/_windows.h"

#elif defined(ANDROID)

#include "acme/os/ansios/_ansios.h"
#include "acme/os/android/_android.h"

#elif defined(SOLARIS)

#include "acme/os/solaris/solaris_solaris.h"

#elif defined(APPLE_IOS)

#include "os/ansios/ansios.h"
#include "acme/os/ios/ca_os.h"

#else

#error "Currently not supported operating system"

#endif


CLASS_DECL_ACME int __node_is_debugger_attached();



