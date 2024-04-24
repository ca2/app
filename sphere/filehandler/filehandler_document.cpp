#include "framework.h"


namespace filehandler
{


   document::document(::particle * pparticle) :
      ::object(pparticle),
      ::data::data_container_base(pparticle),
      ::user::document(pparticle),
      ::user::document(pparticle),
      form_document(pparticle)
   {

   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
      {

         return false;

      }

      return true;

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {
      return true;
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



} // namespace filehandler





