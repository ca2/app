#ifndef __GNUC__
#pragma once
#endif
#ifndef __OBJC__
#include "acme/_start.h"


#include "_.h"


#define __NANO2D_API(api) nvg ## api
#define __NANO2D_TYPE(type) NVG ## type

#define NANO2D_COLOR __NANO2D_TYPE(color)
#define NANO2D_PAINT __NANO2D_TYPE(paint)

#define NANO2D_INCLUDE "nanovg.h"
#define NANO2D_CONTEXT NVGcontext


#include "_nanogui.h"


#include "nano2d/_nano2d.h"


#include "aura/_defer.h"



#endif
