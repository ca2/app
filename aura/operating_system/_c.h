//  Created by Camilo Sasuke Tsumanuma on 05/01/18.
#pragma once


#include "apex/node/operating_system/_c.h"


#if defined(MACOS)

#include "aura/node/operating_system/ansi/_c.h"
#include "aura/node/operating_system/apple/_c.h"
#include "aura/node/operating_system/macos/_c.h"

#elif defined(APPLE_IOS)

#include "aura/os/ansios/_c.h"
#include "aura/os/apple/_c.h"
#include "aura/os/ios/_c.h"

#elif defined(LINUX)

#include "aura/node/operating_system/cairo/_c.h"
#include "aura/node/operating_system/ansi/_c.h"
#include "aura/node/operating_system/linux/_c.h"

#elif defined(FREEBSD)

#include "aura/node/operating_system/cairo/_c.h"
#include "aura/node/operating_system/ansi/_c.h"
#include "aura/node/operating_system/freebsd/_c.h"

#elif defined(_UWP)

#include "aura/node/operating_system/ansi/_c.h"
#include "aura/node/operating_system/windows_common/_c.h"
#include "aura/node/operating_system/universal_windows/_c.h"

#elif defined(WINDOWS_DESKTOP)

#include "aura/node/operating_system/ansi/_c.h"
#include "aura/node/operating_system/windows_common/_c.h"
#include "aura/node/operating_system/windows/_c.h"

#elif defined(ANDROID)

#include "aura/os/ansios/_c.h"
#include "aura/os/android/_c.h"

#elif defined(SOLARIS)

#include "aura/os/ansios/_c.h"
#include "aura/os/solaris/_c.h"

#else

#error "The operating system wasn't expected."

#endif



