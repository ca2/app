#pragma once


#define __NANO2D_API(api) nvg ## api
#define __NANO2D_TYPE(type) NVG ## type

#define NANO2D_COLOR __NANO2D_TYPE(color)
#define NANO2D_PAINT __NANO2D_TYPE(paint)

#define NANO2D_INCLUDE "nanovg.h"
#define NANO2D_CONTEXT NVGcontext



