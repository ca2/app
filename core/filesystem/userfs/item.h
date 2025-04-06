#pragma once


#include "acme/filesystem/file/item.h"


namespace userfs
{

   
   class tree_data;


   class CLASS_DECL_CORE item:
      virtual public ::file::item
   {
   public:


      ::userfs::tree_data *               m_ptreedata;
      int                                 m_iIdentation;
      string                              m_strFolder;
      int                                 m_iIndex;


      item(::userfs::tree_data * ptree);
      virtual ~item();

      string get_item_text(::user::item_base * pitemstate, ::collection::index iSubItem = 0) override;
      ::collection::index get_item_image(::user::item_base  * pitemstate, ::collection::index iSubItem = 0) override;
      ::image::image_list * get_item_image_list(::user::item_base * pitemstate, ::collection::index iSubItem = 0) override;

      //static ::std::strong_ordering CompareArrangeByName(const ::pointer<::data::tree_item<item>>& pitema, const ::pointer<::data::tree_item<item>> pitemb);
      int get_index() const;
      bool is_folder() const;

      //void write(binary_stream & s) const override;
      //void read(binary_stream & s) override;


   };


} // namespace userfs





