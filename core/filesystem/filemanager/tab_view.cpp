#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "aura/update.h"


namespace filemanager
{


   tab_view::tab_view()
   {

   }


   tab_view::~tab_view()
   {

   }


   void tab_view::assert_valid() const
   {
      ::user::tab_view::assert_valid();
   }

   void tab_view::dump(dump_context & dumpcontext) const
   {
      ::user::tab_view::dump(dumpcontext);
   }



   void tab_view::install_message_routing(::channel * pchannel)
   {

      ::user::tab_view::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &tab_view::on_message_create);
      MESSAGE_LINK(e_message_set_focus, pchannel, this, &tab_view::on_message_create);

   }



   void tab_view::on_create_impact(::user::impact_data * pimpactdata)
   {

      if(pimpactdata->m_id.is_null())
      {
         return;
      }
      else if (pimpactdata->m_id == "add_location"
               || pimpactdata->m_id == "replace_name"
               || pimpactdata->m_id == "new_folder")
      {

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = false;

         pcreate->m_puserprimitiveParent = pimpactdata->m_pplaceholder;

         auto puser = user();

         puser->m_pdocumenttemplateForm->do_request(pcreate);

         __pointer(::user::document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         form * pformview = pdocument->get_typed_view < form >();

         auto psubject = subject(BROWSE_ID);

         if (pimpactdata->m_id == "new_folder")
         {

            psubject->payload(FORM_ID) = "matter://filemanager/new_folder.html";

         }
         if (pimpactdata->m_id == "replace_name")
         {

            psubject->payload(FORM_ID) = "matter://filemanager/replace_name_in_file_system.html";

         }
         else if (pimpactdata->m_id == "add_location")
         {

            psubject->payload(FORM_ID) = "matter://filemanager/add_location_1.html";

         }

         pformview->m_idCreator = pimpactdata->m_id;

         pdocument->update_all_views(psubject);

         //psubject->m_pcontext = psubject->context(id_after_browse);

         pdocument->update_all_views(psubject);

         pimpactdata->m_pdocument = pdocument;

      }
      else if(pimpactdata->m_id == "filemanager::operation")
      {

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = false;

         pcreate->m_puserprimitiveParent = this;

         auto puser = user();

         puser->m_pdocumenttemplateOperation->do_request(pcreate);

         __pointer(operation_document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         __pointer(::user::impact) pview = pdocument->get_view(0);

         pimpactdata->m_puserinteraction = pview->get_parent_frame();

         pimpactdata->m_pdocument = pdocument;

      }
      else
      {

         auto pfilemanagerdata  = __new(::filemanager::data);

         pfilemanagerdata->m_pcallback = get_document();

         //pfilemanagerdata->m_pfilemanagertemplate = puser->filemanager();

         pfilemanagerdata->m_bFileSize = true;

         pfilemanagerdata->m_bTransparentBackground = true;

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = true;

         pcreate->m_puserprimitiveParent = pimpactdata->m_pplaceholder;

         pcreate->payload("filemanager::data") = pfilemanagerdata;

         string str = pimpactdata->m_id;

         ::str::begins_eat_ci(str, "verifile://");

         ::file::path pathFolder = str;

         string strVarFile;

         if (get_document()->m_strManagerId.has_char())
         {

            strVarFile = get_document()->m_strManagerId + ":" + pathFolder;

         }

         pcreate->m_pcommandline->m_varFile = strVarFile;

         //puser->filemanager()->m_pdocumenttemplateChild->m_bQueueDocumentOpening = false;

         //puser->filemanager()->m_pdocumenttemplateChild->do_request(pcreate);

         //__pointer(document) pdocument = ::user::__document(pcreate);

         //__pointer(simple_frame_window) puserinteractionTopLevel;
         __pointer(document) pdocument = get_document();

         create_view < view >(pimpactdata);

         auto pcontext = get_context();

         if(pdocument != nullptr)
         {

            m_pfilemanager = pdocument;

//            pdocument->filemanager_data()->m_iTemplate = puser->filemanager()->m_iTemplate;

            //          pdocument->filemanager_data()->m_iDocument = puser->filemanager()->m_iNextDocument++;

            __pointer(::user::impact) pview = pdocument->get_view(0);

            __pointer(simple_frame_window) puserinteraction = (pview->get_parent_frame());

            bool bPathIsDir = false;

            thread_set(id_thread_resolve_alias);

            try
            {

               bPathIsDir = pathFolder.has_char() && pcontext->m_pcontext->dir().is(pathFolder);

            }
            catch (...)
            {

            }

            thread_unset(id_thread_resolve_alias);

            if(bPathIsDir)
            {

               pdocument->filemanager_initialize(true, false);

               pdocument->browse(pathFolder, ::e_source_initialize);

            }
            else
            {

               pdocument->filemanager_initialize(true, true);

            }

            pview->set_need_layout(true);

         }

         set_need_layout();

      }

   }


   void tab_view::on_message_create(::message::message * pmessage)
   {

      pmessage->previous();

      m_pfilemanager = get_document();

   }


   __pointer(document) tab_view::get_document()
   {

      return ::user::impact::get_document();

   }




   void tab_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      impact::on_subject(psubject, pcontext);

      ::user::tab_view::on_subject(psubject, pcontext);

      ////__update(::update)
      {

         if (psubject->id() == id_open_document)
         {

            //if (m_viewmap.get_count() == 0)
            //{

            //   set_cur_tab_by_id(0);

            //}

         }

      }

      ////__update(::update)
      {

         if (psubject->id() == id_initialize)
         {

            //               string str;
            //
            //               str.Format("(%d,%d)",filemanager_document().filemanager_data()->m_iTemplate,filemanager_document().filemanager_data()->m_iDocument);
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
         else if (psubject->id() == id_pop)
         {

            __pointer(::user::frame_window) pframe = get_parent_frame();

            if (pframe.is_set())
            {

               pframe->InitialUpdateFrame(nullptr, true);

               pframe->display(e_display_normal);

               pframe->ActivateFrame(e_display_normal);

            }

         }

      }

      if (psubject->id() == id_add_location)
      {

         set_cur_tab_by_id("add_location");

      }
      else if (psubject->id() == id_replace_name)
      {

         set_cur_tab_by_id("replace_name");

      }
      else if (psubject->id() == id_new_folder)
      {

         set_cur_tab_by_id("new_folder");

      }

   }


} // namespace filemanager



