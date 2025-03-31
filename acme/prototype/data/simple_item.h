#pragma once


#include "acme/handler/item.h"
#include "acme/prototype/data/tree.h"


namespace data
{


   class CLASS_DECL_ACME simple_item :
      public ::item
   {
   public:


      ::data::tree < ::item > *              m_pdatatree;
      ::collection::index                    m_iImage;
      ::collection::index                    m_iImageSelected;
      string                                 m_str;


      simple_item(::data::tree < ::item > * pdatatree);
      ~simple_item() override;


      string get_item_text(::user::item_base * puseritembase, ::collection::index iSubItem = 0) override;
      ::collection::index get_item_image(::user::item_base * puseritembase, ::collection::index iSubItem = 0);
      ::image::image_list * get_item_image_list(::user::item_base * puseritembase, ::collection::index iSubItem = 0);


   };


} // namespace acme


