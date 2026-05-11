#pragma once



//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"


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
      ::acme::windowing::window * m_pacmewindowingwindowItem;
      ::draw2d::graphics_pointer    m_pgraphics;
      ::i32_rectangle               rcItem;
      uptr                          itemData;
      

      item();
      ~item();

      
   };


} // namespace draw2d



