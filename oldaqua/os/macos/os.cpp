//
//  macos_os.cpp
//  aqua
//
//  Created by Camilo Sasuke Tsumanuma on 2013-09-17.
//
//
#include "framework.h"



CLASS_DECL_AQUA bool _istlead(i32 ch)
{

   return false;

}








WINBOOL GetCursorPos(LPPOINT ppointCursor)

{

   HIPoint point;

   HICoordinateSpace space = kHICoordSpaceScreenPixel;

   HIGetMousePosition(space, nullptr, &point);


   ppointCursor->x = point.x;

   ppointCursor->y = point.y;



   return TRUE;

}






char * mm_browse_folder(const char * pszStartDir, bool bCanCreateDirectories);


string apple_browse_folder(const char * pszStartDir, bool bCanCreateDirectories)
{

   return ::str::from_strdup(mm_browse_folder(pszStartDir, bCanCreateDirectories));

}



char** mm_browse_file_open(const char ** pszStartDir, bool bMulti);



string_array apple_browse_file_open(const char ** pszStartDir, bool bMulti)
{



   return ::stra::from_strdup(mm_browse_file_open(pszStartDir, bMulti));

}
