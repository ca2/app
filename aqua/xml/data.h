#pragma once


#include "document.h"
#include "acme/prototype/data/data.h"


namespace xml
{


   class CLASS_DECL_AQUA data :
      virtual public ::xml::document,
      virtual public ::data::data
   {
   public:


      data(::xml::parse_info * pparseinfo = nullptr);
      ~data() override;


      void initialize(::particle * pparticle) override;


      virtual void edit(edit * pedit);


      virtual void validate_edit(::xml::edit* pedit);

      //virtual ::stream & write(::stream & stream) const override;
      //virtual ::stream & read(::stream & stream) override;


   };


} // namespace xml





