//
//  _include.h
//  core
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2022-09-06 00:59.
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#pragma once


#if defined(__MM)


//#include "base/include/_c_bridge.h"
//#include "base/include/objc.h"
//#include "base/include/objcpp.h"
//

#elif defined(__cplusplus)


#include "core/include/_.h"


#elif defined(__M)


#include "core/include/_c.h"
#include "core/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "core/include/_.h"
#include "core/include/winrt.h"


#else


#include "core/include/_c_bridge.h"


#endif



