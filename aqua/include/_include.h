//
//  _include.h
//  aqua
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 2022-09-06 00:05
//  Copyright © 2022 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//

#pragma once


#undef __spin_namespace


#if defined(__MM)


//#include "aqua/include/_c_bridge.h"
//#include "aqua/include/objc.h"
//#include "aqua/include/objcpp.h"


#elif defined(__cplusplus)


#include "aqua/include/_.h"


#elif defined(__M)


//#include "aqua/include/_c.h"
//#include "aqua/include/objc.h"


#elif defined(__cplusplus_winrt)


//#include "_c.h"
#include "aqua/include/_.h"
#include "aqua/include/winrt.h"


#else


#include "aqua/include/_c_bridge.h"


#endif



