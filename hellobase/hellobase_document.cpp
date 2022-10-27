#include "framework.h"


namespace hellobase
{


   document::document(::particle * pparticle) :
      object(pparticle),
      ::data::data_container_base(pparticle),
      ::user::document(pparticle),
      ::user::document(pparticle)
   {

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


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pimpact = get_typed_impact < impact >();

      if(pimpact == nullptr)
      {

         return true;

      }

      string strPath = payloadFile.get_file_path();

      payloadFile["url"] = strPath;

      payloadFile["http_set"]["raw_http"] = true;
      payloadFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

      if(pimpact->m_prender->m_pimageImage->load_image(payloadFile))
      {

         get_typed_impact < impact >()->m_strImage = payloadFile["url"];

         {

            synchronous_lock slText(get_typed_impact < impact >() != nullptr  ? &get_typed_impact < impact >()->m_pmutexText : nullptr);

            get_typed_impact < impact >()->m_strHelloBase = "image:" + get_typed_impact < impact >()->m_strImage + "," + get_typed_impact < impact >()->m_strHelloBase;

            get_typed_impact < impact >()->set_need_layout(true);

         }

      }
      else if(get_typed_impact < ::user::plain_edit_impact >() != nullptr
              && pcontext->m_papexcontext->file().exists(payloadFile)
              && (str = pcontext->m_papexcontext->file().as_string(payloadFile)).has_char())
      {

         get_typed_impact < ::user::plain_edit_impact >()->_001SetText(str.Left(84),::e_source_user);

      }

      return true;

   }


   i64 document::increment_reference_count()
   {

      return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }

   i64 document::decrement_reference_count()
   {

      return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }



} // namespace hellobase

















