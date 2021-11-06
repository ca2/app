#include "framework.h"
//#include "_filemanager.h"


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
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(itema);
      return false;
   }


} // namespace filemanager
