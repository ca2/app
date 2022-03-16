#include "framework.h"
#include "core/user/rich_text/_rich_text.h"
#include "aura/update.h"


namespace user
{


   namespace rich_text
   {


      document::document()
      {

         m_strSaveFileExtension = "rtf";

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


      bool document::on_open_document(::file::file * pfile)
      {

         string str;

         pfile->full_read_string(str);

         parse_rtf_text(str);

         return true;

      }


      bool document::on_save_document(::file:: file * pfile)
      {

         auto pedit = get_type_impact<::user::rich_text::edit_impl>();

         auto pdata = pedit->m_pdata;

         auto ptextformat = __id_create< ::user::rich_text::text_format >("text_format::rtf");

         ptextformat->text_format_save(pfile, pdata);

         return true;

      }



      bool document::parse_rtf_text(string str)
      {

//         papp->m_ppaneimpact->set_current_tab_by_id(::impact_rich_edit);

         return true;

      }

#ifdef _DEBUG

      i64 document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
      {

         return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

      i64 document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
      {

         return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

#endif

   
   } // namespace rich_text


} // namespace user



