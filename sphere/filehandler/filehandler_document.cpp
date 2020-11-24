#include "framework.h"


namespace filehandler
{


   document::document(::layered * pobjectContext) :
      ::object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject),
      form_document(pobject)
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


   bool document::on_open_document(const payload & varFile)
   {
      return TRUE;
   }


   document::~document()
   {
   }




   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }



} // namespace filehandler





