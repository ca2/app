#pragma once


//#include "acme/primitive/primitive/matter.h"
//#include "acme/primitive/collection/pointer_array.h"
class image_list;


namespace data
{


   class item_data_array;
   class tree_item;
   class tree;


   class CLASS_DECL_ACME item :
      virtual public matter
   {
   public:


      item();
      ~item() override;

      virtual string data_item_get_text(::particle * pparticle) const;
      virtual index data_item_get_image(::particle * pparticle) const;
      virtual ::image_list * data_item_get_image_list(::particle * pparticle) const;


      virtual void data_item_on_fill_children(::data::tree_item * pitem);


      //virtual stream & write(stream& s) const override;
      //virtual stream & read(stream& s) override;


   };


   class CLASS_DECL_ACME item_array :
      public pointer_array < item >
   {
   public:


   };


} // namespace acme


