//
//  macos_os.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "framework.h"



CLASS_DECL_AXIS bool _istlead(i32 ch)
{
   
   return false;
   
}








WINBOOL GetCursorPos(LPPOINT lppointCursor)
{
   
   HIPoint point;
   
   HICoordinateSpace space = kHICoordSpaceScreenPixel;
   
   HIGetMousePosition(space, nullptr, &point);
   
   
   lppointCursor->x = point.x;
   lppointCursor->y = point.y;
   
   
   return TRUE;
   
}

