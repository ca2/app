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


   bool document::on_open_document(const ::payload & varFile)
   {

      impact * pview = get_typed_view < impact >();

      if(pview == nullptr)
      {

         return true;

      }

      string strPath = varFile.get_file_path();

      varFile["url"] = strPath;

      varFile["http_set"]["raw_http"] = true;
      varFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

/*      if(pview->m_prender->m_pimageImage->load_image(varFile))
      {

         get_typed_view < impact >()->m_strImage = varFile["url"];

         {

            synchronous_lock slText(get_typed_view < impact >() != nullptr  ? &get_typed_view < impact >()->m_mutexText : nullptr);

            get_typed_view < impact >()->m_strHelloWorld = "image:" + get_typed_view < impact >()->m_strImage + "," + get_typed_view < impact >()->m_strHelloWorld;

            get_typed_view < impact >()->set_need_layout(true);

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != nullptr
              && pcontext->m_papexcontext->file().exists(varFile)
              && (str = pcontext->m_papexcontext->file().as_string(varFile)).has_char())
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

















