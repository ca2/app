//
//  os.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 05/01/18.
//

// 

// CLASS_DECL_AURA int_bool os_is_alias(const ::string & psz);

// 


// C-includes


#if defined(ANDROID)
#include "aura/os/ansios/_c.h"
#include "aura/os/android/_c.h"
#elif defined(MACOS)
#include "aura/os/ansios/_c.h"
#include "aura/os/macos/_c.h"
#elif defined(LINUX)
#include "aura/os/ansios/_c.h"
#include "aura/os/linux/_c.h"
#elif defined(UNIVERSAL_WINDOWS)
#include "aura/os/windows_common/_c.h"
#include "aura/os/universal_windows/_.h"
#elif defined(WINDOWS_DESKTOP)
#include "aura/os/windows_common/_c.h"
#include "aura/os/windows/_c.h"
#elif defined(SOLARIS)
#include "aura/os/solaris/solaris.h"
#elif defined(APPLE_IOS)
#include "aura/os/ansios/_c.h"
#include "aura/os/ios/_c.h"
#else
#error Not Supported Operational ::auraacmesystem()
#endif
