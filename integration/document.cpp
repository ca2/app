#include "framework.h"
#include "document.h"
//#include "impact.h"
#include "application.h"


namespace app_integration
{


   document::document()
   {

   }


   document::~document()
   {

   }


//   void document::assert_ok() const
//   {
//
//      ::user::document::assert_ok();
//
//   }
//
//
//   void document::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::document::dump(dumpcontext);
//
//   }


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

     /* impact * pimpact = get_typed_impact < impact >();

      if(pimpact == NULL)
      {

         return true;

      }

      string strPath = payloadFile.as_file_path();*/

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


   //stream& document::write(::stream& stream) const
   //{

   //   return stream;

   //}


} // namespace simple_drawing



