#include "framework.h"


namespace userstack
{


   document::document(::particle * pparticle) :
      ::object(pparticle),
      ::data::data_container_base(pparticle),
      ::user::document(pparticle),
      ::user::document(pparticle)
   {

   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
      {

         return false;

      }
   
      update_all_impacts(nullptr, ID_NEW_DOCUMENT);

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



