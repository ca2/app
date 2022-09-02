#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "tab_impact.h"
#include "core/user/user/user.h"
#include "form.h"
#include "operation_document.h"
#include "data.h"
#include "document.h"
#include "base/user/user/multiple_document_template.h"
#include "aura/user/user/frame.h"
#include "base/user/user/frame_window.h"


namespace filemanager
{


   tab_impact::tab_impact()
   {

   }


   tab_impact::~tab_impact()
   {

   }


   void tab_impact::assert_ok() const
   {
      ::user::tab_impact::assert_ok();
   }

   void tab_impact::dump(dump_context & dumpcontext) const
   {
      ::user::tab_impact::dump(dumpcontext);
   }



   void tab_impact::install_message_routing(::channel * pchannel)
   {

      ::user::tab_impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_impact::on_message_create);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_impact::on_message_create);

   }



   void tab_impact::on_create_impact(::user::impact_data * pimpactdata)
   {

      if(pimpactdata->m_atom.is_null())
      {
         return;
      }
      else if (pimpactdata->m_atom == "add_location"
               || pimpactdata->m_atom == "replace_name"
               || pimpactdata->m_atom == "new_folder")
      {

         __pointer(::create) pcreate(e_create, this);

         pcreate->m_bMakeVisible = false;

         pcreate->m_puserprimitiveParent = pimpactdata->m_pplaceholder;

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_paurasession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         puser->m_pdocumenttemplateForm->do_request(pcreate);

         __pointer(::user::document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         form * pformview = pdocument->get_type_impact < form >();

         auto ptopic = create_topic(BROWSE_ID);

         if (pimpactdata->m_atom == "new_folder")
         {

            ptopic->payload(FORM_ID) = "matter://filemanager/new_folder.html";

         }
         if (pimpactdata->m_atom == "replace_name")
         {

            ptopic->payload(FORM_ID) = "matter://filemanager/replace_name_in_file_system.html";

         }
         else if (pimpactdata->m_atom == "add_location")
         {

            ptopic->payload(FORM_ID) = "matter://filemanager/add_location_1.html";

         }

         ptopic->payload("creator") = pimpactdata->m_atom;

         pdocument->update_all_impacts(ptopic);

         //ptopic->m_pcontext = ptopic->context(id_after_browse);

         ptopic->m_atom = id_after_browse;

         pdocument->update_all_impacts(ptopic);

         pimpactdata->m_pdocument = pdocument;

      }
      else if(pimpactdata->m_atom == "filemanager::operation")
      {

         __pointer(::create) pcreate(e_create, this);

         pcreate->m_bMakeVisible = false;

         pcreate->m_puserprimitiveParent = this;

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_paurasession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         puser->m_pdocumenttemplateOperation->do_request(pcreate);

         __pointer(operation_document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         auto pimpact = pdocument->get_impact(0);

         pimpactdata->m_puserinteraction = pimpact->parent_frame();

         pimpactdata->m_pdocument = pdocument;

      }
      else
      {

         auto pfilemanagerdata  = __new(::filemanager::data);

         pfilemanagerdata->m_pcallback = get_document();

         //pfilemanagerdata->m_pfilemanagertemplate = puser->filemanager();

         pfilemanagerdata->m_bFileSize = true;

         pfilemanagerdata->m_bTransparentBackground = true;

         __pointer(::create) pcreate(e_create, this);

         pcreate->m_bMakeVisible = true;

         pcreate->m_puserprimitiveParent = pimpactdata->m_pplaceholder;

         pcreate->payload("filemanager::data") = pfilemanagerdata;

         string str = pimpactdata->m_atom;

         ::str().begins_eat_ci(str, "verifile://");

         ::file::path pathFolder = str;

         string strVarFile;

         if (get_document()->m_strManagerId.has_char())
         {

            strVarFile = get_document()->m_strManagerId + ":" + pathFolder;

         }

         pcreate->m_payloadFile = strVarFile;

         //puser->filemanager()->m_pdocumenttemplateChild->m_bQueueDocumentOpening = false;

         //puser->filemanager()->m_pdocumenttemplateChild->do_request(pcreate);

         //__pointer(document) pdocument = ::user::__document(pcreate);

         //__pointer(simple_frame_window) puserinteractionTopLevel;
         __pointer(document) pdocument = get_document();

         create_impact < impact >(pimpactdata);

         auto pcontext = get_context();

         if(pdocument != nullptr)
         {

            m_mapFileManager[pimpactdata->m_atom] = pdocument;

//            pdocument->filemanager_data()->m_iTemplate = puser->filemanager()->m_iTemplate;

            //          pdocument->filemanager_data()->m_iDocument = puser->filemanager()->m_iNextDocument++;

            __pointer(::user::impact) pimpact = pdocument->get_impact(0);

            auto pframe = (pimpact->parent_frame());

            bool bPathIsDir = false;

            task_flag().set(e_task_flag_resolve_alias);

            try
            {

               bPathIsDir = pathFolder.has_char() && pcontext->m_papexcontext->dir().is(pathFolder);

            }
            catch (...)
            {

            }

            task_flag().clear(e_task_flag_resolve_alias);

            if(bPathIsDir)
            {

               pdocument->filemanager_initialize(true, false);

               pdocument->browse(pathFolder, ::e_source_initialize);

            }
            else
            {

               pdocument->filemanager_initialize(true, true);

            }

            pimpact->set_need_layout(true);

         }

         set_need_layout();

      }

   }


   void tab_impact::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      // = get_document();

   }


   __pointer(document) tab_impact::get_document()
   {

      return ::user::impact::get_document();

   }




   void tab_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      impact::handle(ptopic, pcontext);

      ::user::tab_impact::handle(ptopic, pcontext);

      ////__update(::update)
      {

         if (ptopic->m_atom == id_open_document)
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
            //               str.format("(%d,%d)",filemanager_document().filemanager_data()->m_iTemplate,filemanager_document().filemanager_data()->m_iDocument);
            //
            //               __pointer(::database::client) pclient = get_parent_frame();
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

               pframe->display(e_display_restored);

               pframe->ActivateFrame(e_display_restored);

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



