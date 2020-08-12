#pragma once


#define SECURITY_WIN32


#include "aura/_.h"

#include <CoreText/CoreText.h>

#define CLASS_DECL_DRAW2D_QUARTZ2D


#include "object.h"
#include "graphics.h"
#include "path.h"
#include "bitmap.h"
#include "image.h"
#include "palette.h"
#include "pen.h"
#include "font.h"
#include "brush.h"
#include "region.h"



#include "factory_exchange.h"

#include "cgcontextcreate.h"





#define COCOA_DC(pgraphics) (dynamic_cast < ::draw2d_quartz2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics)))
#define SP_DC(pgraphics) (dynamic_cast < ::draw2d_quartz2d::graphics * > (( ::draw2d::graphics * )(pgraphics)))
#define COCOA_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_quartz2d::graphics * > (dynamic_cast < ::draw2d::graphics * > (pgraphics))))
#define SP_HDC(pgraphics) ((HDC)*(dynamic_cast < ::draw2d_quartz2d::graphics * > ((::draw2d::graphics *)(pgraphics))))
#define COCOA_DIB(pimage) (dynamic_cast < ::mac::image_pointer * > (dynamic_cast < image >(pimage)))


#include <CoreText/CoreText.h>


