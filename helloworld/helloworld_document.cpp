#include "framework.h"


namespace helloworld
{


   document::document(::object * pobject) :
      object(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject),
      ::user::document(pobject)
   {

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


   bool document::on_new_document()
   {

      return ::user::document::on_new_document();

   }


   bool document::on_open_document(const ::payload & payloadFile)
   {

      impact * pview = get_typed_view < impact >();

      if(pview == nullptr)
      {

         return true;

      }

      string strPath = payloadFile.get_file_path();

      payloadFile["url"] = strPath;

      payloadFile["http_set"]["raw_http"] = true;
      payloadFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

/*      if(pview->m_prender->m_pimageImage->load_image(payloadFile))
      {

         get_typed_view < impact >()->m_strImage = payloadFile["url"];

         {

            synchronous_lock slText(get_typed_view < impact >() != nullptr  ? &get_typed_view < impact >()->m_mutexText : nullptr);

            get_typed_view < impact >()->m_strHelloWorld = "image:" + get_typed_view < impact >()->m_strImage + "," + get_typed_view < impact >()->m_strHelloWorld;

            get_typed_view < impact >()->set_need_layout(true);

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != nullptr
              && pcontext->m_papexcontext->file().exists(payloadFile)
              && (str = pcontext->m_papexcontext->file().as_string(payloadFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::e_source_user);

      }
      else if(get_typed_view < ::userex::pane_tab_view >() != nullptr)
      {

         get_typed_view < ::userex::pane_tab_view >()->set_current_tab_by_id(::helloworld::PaneViewHelloWorld);

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



} // namespace helloworld

















