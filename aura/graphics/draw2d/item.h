#pragma once


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
      ::rectangle_i32                        rcItem;
      uptr                          itemData;
      
      item();
      ~item();
      
   };


} // namespace draw2d



