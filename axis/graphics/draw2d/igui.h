#pragma once


namespace draw2d
{


   class CLASS_DECL_AURA item
   {
   public:
 

      UINT              CtlType;
      UINT              CtlID;
      UINT              itemID;
      UINT              itemAction;
      INT               itemState;
      oswindow          oswindowItem;
      ::draw2d::graphics_pointer        m_pgraphics;
      ::rect          rcItem;
      uptr              itemData;
      
      
   };


} // namespace draw2d



