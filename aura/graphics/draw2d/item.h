#pragma once



//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace draw2d
{


   class CLASS_DECL_AURA item
   {
   public:
 

      unsigned int                         CtlType;
      unsigned int                         CtlID;
      unsigned int                         itemID;
      unsigned int                         itemAction;
      int                           itemState;
      oswindow                      oswindowItem;
      ::draw2d::graphics_pointer    m_pgraphics;
      ::int_rectangle               rcItem;
      uptr                          itemData;
      

      item();
      ~item();

      
   };


} // namespace draw2d



