#include "framework.h"



namespace console
{


   prompt_document::prompt_document(::particle * pparticle) :
      ::object(pparticle),
      ::data::data_container_base(pparticle),
      ::user::document(pparticle),
      ::user::document(pparticle)
   {

   }


   bool prompt_document::on_new_document()
   {

      if(!::user::document::on_new_document())
         return false;

      update_all_impacts(nullptr, ID_NEW_DOCUMENT);

      return true;

   }


   prompt_document::~prompt_document()
   {

   }




   void prompt_document::assert_ok() const
   {

      ::user::document::assert_ok();

   }


   void prompt_document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   void prompt_document::data_on_after_change(::message::message * pmessage)
   {

      UNREFERENCED_PARAMETER(pmessage);

   }


   bool prompt_document::on_open_document(const ::payload & payloadFile)
   {

      string str = pcontext->m_papexcontext->file()->as_string(payloadFile);
      //  m_prompt_document.load(str);


      return true;

   }


} // namespace prompt



