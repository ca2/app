#include "framework.h"
#include "document.h"
#include "impact.h"
#include "application.h"



namespace cube
{


   document::document()
   {

   }


   document::~document()
   {

   }


   //void document::assert_ok() const
   //{

   //   ::user::document::assert_ok();

   //}


   //void document::dump(dump_context & dumpgpucontext) const
   //{

   //   ::user::document::dump(dumpgpucontext);

   //}


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pimpact = get_typed_impact < impact >();

      if(pimpact == nullptr)
      {

         return false;

      }

      return true;

   }


   long long document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count();

   }

   long long document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count();

   }



} // namespace cube



