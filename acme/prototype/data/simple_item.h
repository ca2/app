#pragma once


#include "acme/prototype/data/tree_item.h"


namespace data
{


   class CLASS_DECL_ACME simple_item :
      public item
   {
   public:


      ::data::tree < ::data::item > *        m_pdatatree;
      ::collection::index                    m_iImage;
      ::collection::index                    m_iImageSelected;
      string                                 m_str;


      simple_item(::data::tree < ::data::item > * pdatatree);
      virtual ~simple_item();

      virtual string data_item_get_text(::particle * pparticle) const;
      virtual ::collection::index data_item_get_image(::particle * pparticle) const;
      virtual ::image::image_list * data_item_get_image_list(::particle * pparticle) const;


   };


} // namespace acme


