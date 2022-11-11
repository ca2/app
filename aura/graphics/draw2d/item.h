#pragma once


#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/pointer.h"


namespace draw2d
{


   class CLASS_DECL_AURA item
   {
   public:
 

      ::u32                         CtlType;
      ::u32                         CtlID;
      ::u32                         itemID;
      ::u32                         itemAction;
      int                           itemState;
      oswindow                      oswindowItem;
      ::draw2d::graphics_pointer    m_pgraphics;
      ::RECTANGLE_I32               rcItem;
      uptr                          itemData;
      

      item();
      ~item();

      
   };


} // namespace draw2d



