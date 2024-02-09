//
//  _include.h
//  core
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2022-09-06 00:59.
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#pragma once


#if defined(__OBJECTIVE_CPP__)


//#include "base/include/_c_bridge.h"
//#include "base/include/objc.h"
//#include "base/include/objcpp.h"
//

#elif defined(__cplusplus)


#include "core/include/_.h"


#elif defined(__OBJECTIVE_C__)


#include "core/include/_c.h"
#include "core/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "core/include/_.h"
#include "core/include/winrt.h"


#else


#include "core/include/_c_bridge.h"


#endif



