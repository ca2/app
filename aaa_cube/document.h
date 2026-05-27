#pragma once


#include "berg/user/user/document.h"


namespace cube
{


   class CLASS_DECL_AURA document :
      virtual public ::user::document
   {
   public:


      document();
	   ~document() override;

      
	   // void assert_ok() const override;
	   // void dump(dump_context & dumpgpucontext) const override;

      bool on_new_document() override;
      bool on_open_document(const ::payload & payloadFile) override;

      ::i64 increment_reference_count() override;

      ::i64 decrement_reference_count() override;


   };


} // namespace graphics3d



