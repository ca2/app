#pragma once


#include "application.h"
#include "apex/platform/app_consumer.h"
#include "berg/user/user/document.h"


namespace app_build
{


   class CLASS_DECL_APP_BUILD document :
      virtual public ::app_consumer < application, ::user::document >
   {
   public:


      

      document();
      ~document() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;
      virtual bool on_save_document(::file::file * pwriter) override;

#ifdef _DEBUG
      
      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;

#endif



   };


} // namespace app_build



