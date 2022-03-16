#include "framework.h"
#include "acme/id.h"
#include "acme/exception/parsing.h"


namespace app_core_build
{


   document::document()
   {

      m_bCustomOpen = true;

   }


   document::~document()
   {

   }





   void document::assert_ok() const
   {

      ::user::document::assert_ok();

   }


   void document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   

   bool document::on_save_document(::file::file * pwriter)
   {

      return true;

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pimpact = get_type_impact < impact >();

      if(pimpact == nullptr)
      {

         return true;

      }

      return true;

   }


#ifdef _DEBUG


   i64 document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
   {

      return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


} // namespace app_core_build



