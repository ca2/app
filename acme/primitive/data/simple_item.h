#pragma once


#include "acme/primitive/data/item.h"


namespace data
{


   class CLASS_DECL_ACME simple_item :
      public item
   {
   public:


      ::data::tree *             m_pdatatree;
      index                      m_iImage;
      index                      m_iImageSelected;
      string                     m_str;


      simple_item(::data::tree * pdatatree);
      virtual ~simple_item();

      virtual string data_item_get_text(::particle * pparticle) const;
      virtual index data_item_get_image(::particle * pparticle) const;
      virtual ::image_list * data_item_get_image_list(::particle * pparticle) const;


   };


} // namespace acme


