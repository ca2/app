#include "framework.h"


namespace calculator
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

      update_all_impacts(nullptr, id_initial_update);

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

   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*void document::Serialize(CArchive& ar)
   {
      if (ar.IsStoring())
      {
         // TODO: add storing code here
      }
      else
      {
         // TODO: add loading code here
      }
   }
   */

   void document::data_on_after_change(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
   }

   bool document::on_open_document(const ::payload & payloadFile)
   {

      string str = file()->as_string(payloadFile);

      update_all_impacts(nullptr, ID_OPEN_DOCUMENT);

      return true;

   }


} // namespace calculator



