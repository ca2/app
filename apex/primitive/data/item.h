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

      virtual string data_item_get_text(::context_object * pcontextobject) const;
      virtual index data_item_get_image(::context_object* pcontextobject) const;
      virtual ::image_list * data_item_get_image_list(::context_object* pcontextobject) const;


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


