#include "framework.h"


namespace data
{


   item::item()
   {
   }

   item::~item()
   {
   }

   string item::data_item_get_text(::object * pobject) const
   {
      __UNREFERENCED_PARAMETER(pobject);
      return "";
   }

   index item::data_item_get_image(::object * pobject) const
   {
      __UNREFERENCED_PARAMETER(pobject);
      return -1;
   }

   image_list * item::data_item_get_image_list(::object * pobject) const
   {
      __UNREFERENCED_PARAMETER(pobject);
      return nullptr;
   }


   void item::data_item_on_fill_children(::data::tree_item * pitem)
   {

   }


   //::stream & item::write(::stream& s) const
   //{

   //   return s;

   //}


   //::stream & item::read(::stream& s)
   //{

   //   return s;

   //}


} // namespace data



