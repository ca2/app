#include "framework.h"


namespace prompt
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




   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }


   /////////////////////////////////////////////////////////////////////////////
   // document serialization

   /*
   void document::Serialize(CArchive& ar)
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
      string str = pcontext->m_papexcontext->file().as_string(payloadFile);
      //  m_document.load(str);

      update_all_views(nullptr, OPEN_DOCUMENT_UPDATE);

      return true;

   }


} // namespace prompt



