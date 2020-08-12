#pragma once



namespace xml
{


   class CLASS_DECL_AURA data :
      public ::xml::document,
      virtual public ::data::data
   {
   public:


      data(::xml::parse_info * pparseinfo = nullptr);
      virtual ~data();


      virtual void edit(edit * pedit);


      virtual ::estatus validate_edit(::xml::edit* pedit);

      virtual ::stream & write(::stream & stream) const override;
      virtual ::stream & read(::stream & stream) override;


   };


} // namespace xml





