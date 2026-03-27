#pragma once


#include "berg/user/user/document.h"


namespace coding
{


   class CLASS_DECL_CODING document :
      public ::user::document
   {
   public:



      document();
      ~document() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      bool on_open_document(const ::payload & payloadFile) override;
      bool on_save_document(::file::file * pwriter) override;

      #ifdef _DEBUG

      long long increment_reference_count() override;

      long long decrement_reference_count() override;

      #endif



   };


} // namespace coding



