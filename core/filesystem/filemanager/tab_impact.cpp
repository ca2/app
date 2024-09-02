#include "framework.h"
#include "tab_impact.h"
#include "form.h"
#include "operation/document.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/parallelization/task_flag.h"
#include "acme/handler/request.h"
#include "aura/user/user/frame.h"
#include "aura/platform/session.h"
#include "base/user/user/frame_window.h"
#include "base/user/user/multiple_document_template.h"
#include "core/platform/application.h"
#include "core/filesystem/filemanager/filemanager.h"
#include "core/user/user/user.h"


namespace filemanager
{


   tab_impact::tab_impact()
   {

   }


   tab_impact::~tab_impact()
   {

   }


//   void tab_impact::assert_ok() const
//   {
//      ::user::tab_impact::assert_ok();
//   }
//
//   void tab_impact::dump(dump_context & dumpcontext) const
//   {
//      ::user::tab_impact::dump(dumpcontext);
//   }



   void tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &tab_impact::on_message_create);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_impact::on_message_create);

   }



   void tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      if(pimpactdata->m_atom.is_null())
      {

         return;

      }
      //else if (pimpactdata->m_atom == "add_location"
      //         || pimpactdata->m_atom == "replace_name"
      //         || pimpactdata->m_atom == "new_folder")
      //{

      //   ::pointer<::request>prequest(e_create, this);

      //   prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

      //   prequest->m_puserelementParent = pimpactdata->m_pplaceholder;

      //   auto pcontext = m_pcontext;
      //   
      //   auto psession = pcontext->m_pacmesession->m_paurasession;
      //   
      //   auto puser = psession->m_puser->m_pcoreuser;

      //   puser->m_pimpactsystemForm->request(prequest);

      //   ::pointer<::user::document>pdocument = ::user::__document(prequest);

      //   if (pdocument == nullptr)
      //   {

      //      return;

      //   }

      //   form * pformview = pdocument->get_typed_impact < form >();

      //   auto ptopic = create_topic(ID_BROWSE);

      //   if (pimpactdata->m_atom == "new_folder")
      //   {

      //      ptopic->payload(ID_FORM) = "matter://filemanager/new_folder.html";

      //   }
      //   if (pimpactdata->m_atom == "replace_name")
      //   {

      //      ptopic->payload(ID_FORM) = "matter://filemanager/replace_name_in_file_system.html";

      //   }
      //   else if (pimpactdata->m_atom == "add_location")
      //   {

      //      ptopic->payload(ID_FORM) = "matter://filemanager/add_location_1.html";

      //   }

      //   ptopic->payload("creator") = pimpactdata->m_atom;

      //   pdocument->update_all_impacts(ptopic);

      //   //ptopic->m_pcontext = ptopic->context(id_after_browse);

      //   ptopic->m_atom = id_after_browse;

      //   pdocument->update_all_impacts(ptopic);

      //   pimpactdata->m_pdocument = pdocument;

      //}
      //else if(pimpactdata->m_atom == "filemanager::operation")
      //{

      //   ::pointer<::request>prequest(e_create, this);

      //   prequest->m_egraphicsoutputpurpose -= ::graphics::e_output_purpose_screen;

      //   prequest->m_puserelementParent = this;

      //   auto pcontext = m_pcontext;
      //   
      //   auto psession = pcontext->m_pacmesession->m_paurasession;
      //   
      //   auto puser = psession->m_puser->m_pcoreuser;

      //   puser->m_pimpactsystemOperation->request(prequest);

      //   ::pointer<operation_document>pdocument = ::user::__document(prequest);

      //   if (pdocument == nullptr)
      //   {

      //      return;

      //   }

      //   auto pimpact = pdocument->get_impact(0);

      //   pimpactdata->m_puserinteraction = pimpact->parent_frame();

      //   pimpactdata->m_pdocument = pdocument;

      //}
      //else
      {

         auto pfilemanagerdata = application()->m_pcoreapplication->
            filemanager()->create_filemanager_data();

         application()->m_pcoreapplication->
            filemanager()->impact_system()->create_subdocument(
               pimpactdata,
               pfilemanagerdata);

//         auto pdocument  = ::place(new ::filemanager::data());
//
//         pdocument->m_pcallback = get_document();
//
//         //pdocument->m_pfilemanagertemplate = puser->filemanager();
//
//         pdocument->m_bFileSize = true;
//
//         pdocument->m_bTransparentBackground = true;
//
//         ::pointer<::request>prequest(e_create, this);
//
//         prequest->m_egraphicsoutputpurpose |= ::graphics::e_output_purpose_screen;
//
//         prequest->m_puserelementParent = pimpactdata->m_pplaceholder;
//
//         prequest->payload("filemanager::data") = pdocument;
//
//         string str = pimpactdata->m_atom;
//
//         str.case_insensitive_begins_eat("verifile://");
//
//         ::file::path pathFolder = str;
//
//         string strVarFile;
//
//         if (get_document()->m_strManagerId.has_char())
//         {
//
//            strVarFile = get_document()->m_strManagerId + ":" + pathFolder;
//
//         }
//
//         prequest->m_payloadFile = strVarFile;
//
//         //puser->filemanager()->m_pimpactsystemChild->m_bQueueDocumentOpening = false;
//
//         //puser->filemanager()->m_pimpactsystemChild->do_request(pcreate);
//
//         //::pointer<document>pdocument = ::user::__document(pcreate);
//
//         //::pointer<simple_frame_window>puserinteractionTopLevel;
//
//         ::pointer<document>pdocument = get_document();
//
//         create_impact < impact >(pimpactdata);
//
//         auto pcontext = get_context();
//
//         if(pdocument != nullptr)
//         {
//
//            m_mapFileManager[pimpactdata->m_atom] = pdocument;
//
////            pdocument->get_document()->m_iTemplate = puser->filemanager()->m_iTemplate;
//
//            //          pdocument->get_document()->m_iDocument = puser->filemanager()->m_iNextDocument++;
//
//            ::pointer<::user::impact>pimpact = pdocument->get_impact(0);
//
//            auto pframe = (pimpact->parent_frame());
//
//            bool bPathIsDir = false;
//
//            task_flag().set(e_task_flag_resolve_alias);
//
//            try
//            {
//
//               bPathIsDir = pathFolder.has_char() && dir()->is(pathFolder);
//
//            }
//            catch (...)
//            {
//
//            }
//
//            task_flag().clear(e_task_flag_resolve_alias);
//
//            if(bPathIsDir)
//            {
//
//               //pdocument->filemanager_initialize(true, false);
//
//               pdocument->browse(pathFolder, ::e_source_initialize);
//
//            }
//            else
//            {
//
//               pdocument->browse_initial_path(::e_source_initialize);
//
//            }
//            // else
//            // {
//            //
//            //    pdocument->filemanager_initialize(true, true);
//            //
//            // }
//
//            pimpact->set_need_layout();
//
//         }
//
//         set_need_layout();

      }

   }


   void tab_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      // = get_document();

   }


   ::pointer<document>tab_impact::get_document()
   {

      return ::user::impact::get_document();

   }




   void tab_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      impact::handle(ptopic, pcontext);

      ::user::tab_impact::handle(ptopic, pcontext);

      ////__update(::update)
      {

         if (ptopic->m_atom == id_incoming_document)
         {

            //if (m_impactmap.get_count() == 0)
            //{

            //   set_current_tab_by_id(0);

            //}

         }

      }

      ////__update(::update)
      {

         if (ptopic->m_atom == id_initialize)
         {

            //               string str;
            //
            //               str.formatf("(%d,%d)",filemanager_document().get_document()->m_iTemplate,filemanager_document().get_document()->m_iDocument);
            //
            //               ::pointer<::database::client>pclient = get_parent_frame();
            //
            //               if (pclient.is_set())
            //               {
            //
            //                  pclient->set_data_key_modifier(str);
            //
            //               }

         }
         else if (ptopic->m_atom == id_pop)
         {

            auto pframe = parent_frame();

            if (::is_null(pframe))
            {

               pframe->m_puserframewindow->prepare_frame(nullptr, true);

               pframe->display(e_display_normal);

               pframe->ActivateFrame(e_display_normal);

            }

         }

      }

      if (ptopic->m_atom == id_add_location)
      {

         set_current_tab_by_id("add_location");

      }
      else if (ptopic->m_atom == id_replace_name)
      {

         set_current_tab_by_id("replace_name");

      }
      else if (ptopic->m_atom == id_new_folder)
      {

         set_current_tab_by_id("new_folder");

      }

   }


} // namespace filemanager



