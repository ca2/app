#include "framework.h"


namespace helloworld
{


   document::document(::layered * pobjectContext) :
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

      view * pview = get_typed_view < view >();

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

         get_typed_view < view >()->m_strImage = varFile["url"];

         {

            synchronization_lock slText(get_typed_view < view >() != nullptr  ? &get_typed_view < view >()->m_mutexText : nullptr);

            get_typed_view < view >()->m_strHelloWorld = "image:" + get_typed_view < view >()->m_strImage + "," + get_typed_view < view >()->m_strHelloWorld;

            get_typed_view < view >()->set_need_layout(true);

         }

      }
      else if(get_typed_view < ::user::plain_edit_view >() != nullptr
              && Context.file().exists(varFile)
              && (str = Context.file().as_string(varFile)).has_char())
      {

         get_typed_view < ::user::plain_edit_view >()->_001SetText(str.Left(84),::e_source_user);

      }
      else if(get_typed_view < ::userex::pane_tab_view >() != nullptr)
      {

         get_typed_view < ::userex::pane_tab_view >()->set_cur_tab_by_id(::helloworld::PaneViewHelloWorld);

      }

      return true;

   }


   i64 document::add_ref()
   {

      return  ::user::document::add_ref(OBJ_REF_DBG_ARGS);

   }

   i64 document::dec_ref()
   {

      return  ::user::document::dec_ref(OBJ_REF_DBG_ARGS);

   }



} // namespace helloworld

















