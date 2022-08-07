#include "framework.h"


namespace browser
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

      impact * pimpact = get_type_impact < impact >();

      if(pimpact == nullptr)
      {

         return true;

      }

      string strPath = payloadFile.get_file_path();

      payloadFile["url"] = strPath.c_str();
      payloadFile["http_set"]["raw_http"] = true;
      payloadFile["http_set"]["disable_common_name_cert_check"] = true;

      string str;

/*      ::image_pointer pimage = get_image(payloadFile, true);

/*      if(pimage->is_ok())
      {

         {

            synchronous_lock synchronouslock(pimpact->mutex());

/*            pimpact->m_prender->m_pimageImage = pimage;

            pimpact->m_strImage = strPath;

            pimpact->m_prender->m_bImageChanged = true;

         }

         {

            synchronous_lock slText(&pimpact->m_mutexText);

            pimpact->m_strHelloBrowser = "image:" + pimpact->m_strImage + "," + pimpact->m_strHelloBrowser;

         }

      }
      else if(get_type_impact < ::user::plain_edit_impact >() != nullptr
              && pcontext->m_papexcontext->file().exists(payloadFile)
              && (str = pcontext->m_papexcontext->file().as_string(payloadFile)).has_char())
      {

         get_type_impact < ::user::plain_edit_impact >()->_001SetText(str.Left(84),::e_source_user);

      }
      else if(get_type_impact < ::userex::pane_tab_impact >() != nullptr)
      {

         get_type_impact < ::userex::pane_tab_impact >()->set_current_tab_by_id(MAIN_IMPACT);

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


} // namespace browser



