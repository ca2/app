#include "framework.h"
#include "item.h"


namespace data
{


   item::item()
   {
   }

   item::~item()
   {
   }

   string item::data_item_get_text(::particle * pparticle) const
   {
      __UNREFERENCED_PARAMETER(pparticle);
      return "";
   }

   index item::data_item_get_image(::particle * pparticle) const
   {
      __UNREFERENCED_PARAMETER(pparticle);
      return -1;
   }

   image_list * item::data_item_get_image_list(::particle * pparticle) const
   {
      __UNREFERENCED_PARAMETER(pparticle);
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



