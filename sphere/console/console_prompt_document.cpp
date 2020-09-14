#include "framework.h"



namespace console
{


   prompt_document::prompt_document(::layered * pobjectContext) :
      ::object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject)
   {

   }


   bool prompt_document::on_new_document()
   {

      if(!::user::document::on_new_document())
         return FALSE;

      update_all_views(nullptr, NEW_DOCUMENT_UPDATE);

      return TRUE;

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

      UNREFERENCED_PARAMETER(pmessage);

   }


   bool prompt_document::on_open_document(const var & varFile)
   {

      string str = Context.file().as_string(varFile);
      //  m_prompt_document.load(str);


      return true;

   }


} // namespace prompt



