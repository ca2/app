#pragma once


#include "berg/user/user/document.h"


namespace user
{


   namespace rich_text
   {


      class CLASS_DECL_CORE document :
         virtual public ::user::document
      {
      public:


         document();
         ~document() override;



         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;


         bool on_new_document() override;
         bool on_open_document(const ::payload & payloadFile) override;
         bool on_save_document(::file::file * pfile) override;


#ifdef _DEBUG
         virtual long long increment_reference_count() override;
         virtual long long decrement_reference_count() override;
#endif

         //virtual bool parse_rtf_text(string str);



      };


   } // namespace rich_text


} // namespace user






