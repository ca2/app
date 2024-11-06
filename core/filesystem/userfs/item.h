#pragma once


#include "acme/filesystem/file/item.h"
#include "acme/prototype/data/item.h"


namespace userfs
{

   
   class tree_data;


   class CLASS_DECL_CORE item:
      virtual public ::data::item,
      virtual public ::file::item
   {
   public:


      ::userfs::tree_data *               m_ptreedata;
      int                                 m_iIdentation;
      string                              m_strFolder;
      int                                 m_iIndex;


      item(::userfs::tree_data * ptree);
      virtual ~item();

      virtual string data_item_get_text(::particle * pparticle) const override;
      virtual ::collection::index data_item_get_image(::particle * pparticle) const override;
      virtual ::image::image_list * data_item_get_image_list(::particle * pparticle) const override;

      static ::std::strong_ordering CompareArrangeByName(const ::pointer<::data::tree_item>& pitema, const ::pointer<::data::tree_item> pitemb);
      int get_index() const;
      bool is_folder() const;

      //void write(binary_stream & s) const override;
      //void read(binary_stream & s) override;


   };


} // namespace userfs





