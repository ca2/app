#include "framework.h"
#include "tab_callback.h"
#include "tab.h"


namespace user
{


   tab_callback::tab_callback()
   {

   }

   tab_callback::~tab_callback()
   {

   }

   bool tab_callback::_001IsAddTab(tab * ptab, ::collection::index iTab)
   {

      __UNREFERENCED_PARAMETER(ptab);
      __UNREFERENCED_PARAMETER(iTab);

      return false;

   }


   void tab_callback::_001OnTabClick(tab * ptab, ::collection::index iTab)
   {

      ptab->set_current_tab_by_index(iTab);

   }


   void tab_callback::_001OnTabClose(tab * ptab, ::collection::index iTab)
   {

      ptab->_001CloseTab(iTab);

   }

   ::user::interaction * tab_callback::_001GetTabWnd(::collection::index iTab)
   {
      __UNREFERENCED_PARAMETER(iTab);
      return nullptr;
   }

   void tab_callback::_001OnShowTab(tab * ptab)
   {
      __UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001OnDropTab(::collection::index iTab, enum_position eposition)
   {
      __UNREFERENCED_PARAMETER(iTab);
      __UNREFERENCED_PARAMETER(eposition);
   }

   void tab_callback::_001DropTargetWindowInitialize(tab * ptab)
   {
      __UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowRelay(tab * ptab)
   {
      __UNREFERENCED_PARAMETER(ptab);
   }

   void tab_callback::_001DropTargetWindowFinalize(tab * ptab)
   {
      __UNREFERENCED_PARAMETER(ptab);
   }


} // namespace base

