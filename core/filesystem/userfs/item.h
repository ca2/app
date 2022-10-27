#pragma once


namespace userfs
{

   class tree;

   class CLASS_DECL_CORE item:
      virtual public ::data::item,
      virtual public ::file::item
   {
   public:


      ::userfs::tree *                    m_ptree;
      i32                                 m_iIdentation;
      string                              m_strFolder;
      i32                                 m_iIndex;


      item(::userfs::tree * ptree);
      virtual ~item();

      virtual string data_item_get_text(::particle * pparticle) const override;
      virtual index data_item_get_image(::particle * pparticle) const override;
      virtual ::image_list * data_item_get_image_list(::particle * pparticle) const override;

      static index CompareArrangeByName(const ::pointer<::data::tree_item>& pitema, const ::pointer<::data::tree_item> pitemb);
      i32 get_index() const;
      bool is_folder() const;

      //void write(binary_stream < FILE > & s) const override;
      //void read(binary_stream < FILE > & s) override;


   };


} // namespace userfs





