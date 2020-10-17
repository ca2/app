#pragma once


class image_list;


namespace data
{


   class item_data_array;
   class tree_item;
   class tree;


   class CLASS_DECL_APEX item :
      virtual public matter
   {
   public:


      item();
      virtual ~item();

      virtual string data_item_get_text(::object * pobject) const;
      virtual index data_item_get_image(::object* pobject) const;
      virtual ::image_list * data_item_get_image_list(::object* pobject) const;


      virtual void data_item_on_fill_children(::data::tree_item * pitem);


      virtual stream & write(stream& s) const override;
      virtual stream & read(stream& s) override;


   };


   class CLASS_DECL_ACME item_array :
      public __pointer_array(item)
   {
   public:


   };


} // namespace acme


