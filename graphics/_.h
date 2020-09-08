#pragma once


inline byte clip_byte(int i)
{

   if (i > 255)
   {

      return 255;

   }
   else
   {

      return i;

   }

}


inline byte clip_zero(int i)
{

   if (i < 0)
   {

      return 0;

   }
   else
   {

      return i;

   }

}


/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

#ifndef LAYOUT_LTR
#define LAYOUT_LTR                               0x00000000
#endif

#ifndef NOMIRRORBITMAP
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif
#pragma once

/////////////////////////////////////////////////////////////////////////////
// mirroring support

//WINBUG: some mirroring stuff will be in wingdi.h someday
#ifndef LAYOUT_RTL
#define LAYOUT_RTL                         0x00000001
#define NOMIRRORBITMAP                     0x80000000
#endif

#ifndef LAYOUT_LTR
#define LAYOUT_LTR                               0x00000000
#endif

#ifndef NOMIRRORBITMAP
#define NOMIRRORBITMAP                     0x80000000
#endif

//WINBUG: some mirroring stuff will be in winuser.h someday
#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif




#include "aura/graphics/draw2d/_.h"

#include "aura/graphics/draw3d/_.h"

#include "aura/graphics/graphics/_.h"


