#include "framework.h"
#include "base/user/user/_user.h"


namespace user
{


   tab_callback::tab_callback()
   {

   }

   tab_callback::~tab_callback()
   {

   }

   bool tab_callback::_001IsAddTab(tab * ptab, ::index iTab)
   {

      UNREFERENCED_PARAMETER(ptab);
      UNREFERENCED_PARAMETER(iTab);

      return false;

   }

   void tab_callback::_001OnTabClick(tab * ptab, ::index iTab)
   {

      ptab->set_current_tab_by_index(iTab);

   }

   void tab_callback::_001OnTabClose(tab * ptab, ::index iTab)
   {

      ptab->_001CloseTab(iTab);

   }

   ::user::interaction * tab_callback::_001GetTabWnd(::index iTab)
   {
      UNREFERENCED_PARAMETER(iTab);
      return nullptr;
   }

   void tab_callback::_001OnShowTab(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001OnDropTab(::index iTab, enum_position eposition)
   {
      UNREFERENCED_PARAMETER(iTab);
      UNREFERENCED_PARAMETER(eposition);
   }

   void tab_callback::_001DropTargetWindowInitialize(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowRelay(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowFinalize(tab * ptab)
   {
      UNREFERENCED_PARAMETER(ptab);
   }


} // namespace base

