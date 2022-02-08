#include "framework.h"


namespace userstack
{


   document::document(::object * pobject) :
      ::object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject)
   {

   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
      {

         return false;

      }
   
      update_all_views(nullptr, NEW_DOCUMENT_UPDATE);

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


} // namespace userstack



