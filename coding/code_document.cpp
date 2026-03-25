#include "framework.h"
#include "code_document.h"
#include "acme/constant/id.h"


namespace coding
{


   document::document()
   {

   }


   document::~document()
   {

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


      return true;

   }


#ifdef _DEBUG


   long long document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count();

   }


   long long document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count();

   }

#endif


} // namespace coding



