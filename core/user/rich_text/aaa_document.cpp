#include "framework.h"
//#include "document.h"
//#include "edit_impl.h"
//#include "text_format.h"
//#include "acme/filesystem/file/file.h"
//#include "acme/filesystem/filesystem/file_context.h"
//#include "acme/platform/system.h"
//
//
//namespace user
//{
//
//
//   namespace rich_text
//   {
//
//
//      document::document()
//      {
//
//         m_strSaveFileExtension = "rtf";
//
//      }
//
//
//      document::~document()
//      {
//
//      }
//
//
//
//
//
////      void document::assert_ok() const
////      {
////
////         ::user::document::assert_ok();
////
////      }
////
////
////      void document::dump(dump_context & dumpcontext) const
////      {
////
////         ::user::document::dump(dumpcontext);
////
////      }
//
//
//      bool document::on_new_document()
//      {
//
//         return ::user::document::on_new_document();
//
//      }
//
//
//      bool document::on_open_document(const ::payload & payloadFile)
//      {
//
//         auto path = payloadFile.as_file_path();
//
//         auto extension = path.final_extension();
//
//         if (extension.case_insensitive_order("rtf") == 0)
//         {
//
//            auto preader = file()->get_reader(payloadFile);
//
//            //parse_rtf_text(str);
//
//            //if (parse_rtf_text(str))
//            //{
//
//            auto pedit = get_typed_impact<::user::rich_text::edit_impl>();
//
//            auto pdata = pedit->m_pdata;
//
//            auto pfactory = system()->factory("text_format", "rtf");
//
//            auto ptextformat = __create< ::user::rich_text::text_format >(pfactory);
//
//            ptextformat->text_format_load(pdata, preader);
//
//            id_update_all_impacts(ID_INCOMING_DOCUMENT);
//
//            //}
//
//         }
//
//
//         return true;
//
//      }
//
//
//      bool document::on_save_document(::file:: file * pfile)
//      {
//
//         auto pedit = get_typed_impact<::user::rich_text::edit_impl>();
//
//         auto pdata = pedit->m_pdata;
//
//         auto pfactory = system()->factory("text_format", "rtf");
//
//         auto ptextformat = __create< ::user::rich_text::text_format >(pfactory);
//
//         ptextformat->text_format_save(pfile, pdata);
//
//         return true;
//
//      }
//
//
//
////      bool document::parse_rtf_text(string str)
////      {
////
//////         papp->m_ppaneimpact->set_current_tab_by_id(::impact_rich_edit);
////
////         return true;
////
////      }
//
//#ifdef _DEBUG
//
//      i64 document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//      {
//
//         return  ::user::document::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//      }
//
//      i64 document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS_DEF)
//      {
//
//         return  ::user::document::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//
//      }
//
//#endif
//
//   
//   } // namespace rich_text
//
//
//} // namespace user
//
//
//
