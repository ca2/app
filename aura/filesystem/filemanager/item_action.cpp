#include "framework.h"
#include "item_action.h"


namespace filemanager
{


   item_action::item_action()
   {

   }


   item_action::~item_action()
   {

   }


   bool item_action::open_file(::filemanager::data * pdata, ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(itema);
      return false;
   }


} // namespace filemanager
