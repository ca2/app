#pragma once


namespace data
{


   class CLASS_DECL_APEX simple_item :
      public item
   {
   public:


      ::data::tree *             m_pdatatree;
      index                      m_iImage;
      index                      m_iImageSelected;
      string                     m_str;


      simple_item(::data::tree * pdatatree);
      virtual ~simple_item();

      virtual string data_item_get_text(generic * pobject) const;
      virtual index data_item_get_image(generic * pobject) const;
      virtual ::image_list * data_item_get_image_list(generic * pobject) const;


   };


} // namespace acme


