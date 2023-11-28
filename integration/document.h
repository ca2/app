#pragma once


#include "base/user/user/document.h"


namespace app_integration
{


   class CLASS_DECL_APP_INTEGRATION document :
      public ::user::document
   {
   public:


      document();
	   ~document() override;


	   // void assert_ok() const override;
	   // void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;

#ifdef _DEBUG
      virtual int64_t increment_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
      virtual int64_t decrement_reference_count(REFERENCING_DEBUGGING_PARAMETERS) override;
#endif

      //virtual ::stream& write(::stream& stream) const override;


   };


} // namespace simple_drawing















