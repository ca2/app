#include "framework.h"



namespace console
{


   prompt_document::prompt_document(::object * pobject) :
      ::object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject)
   {

   }


   bool prompt_document::on_new_document()
   {

      if(!::user::document::on_new_document())
         return false;

      update_all_views(nullptr, NEW_DOCUMENT_UPDATE);

      return true;

   }


   prompt_document::~prompt_document()
   {

   }




   void prompt_document::assert_valid() const
   {

      ::user::document::assert_valid();

   }


   void prompt_document::dump(dump_context & dumpcontext) const
   {

      ::user::document::dump(dumpcontext);

   }


   void prompt_document::data_on_after_change(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

   }


   bool prompt_document::on_open_document(const ::payload & payloadFile)
   {

      string str = pcontext->m_papexcontext->file().as_string(payloadFile);
      //  m_prompt_document.load(str);


      return true;

   }


} // namespace prompt



