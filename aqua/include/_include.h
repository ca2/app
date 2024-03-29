//
//  _include.h
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 2022-09-06 00:05
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//

#pragma once


#undef __spin_namespace


#if defined(__OBJECTIVE_CPP__)


//#include "aqua/include/_c_bridge.h"
//#include "aqua/include/objc.h"
//#include "aqua/include/objcpp.h"


#elif defined(__cplusplus)


#include "aqua/include/_.h"


#elif defined(__OBJECTIVE_C__)


//#include "aqua/include/_c.h"
//#include "aqua/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "aqua/include/_.h"
#include "aqua/include/winrt.h"


#else


#include "aqua/include/_c_bridge.h"


#endif



