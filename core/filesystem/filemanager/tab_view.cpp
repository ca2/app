#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
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

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &tab_view::_001OnCreate);
      IGUI_MSG_LINK(WM_SETFOCUS, pchannel, this, &tab_view::_001OnCreate);

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

         pcreate->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         User.m_pdocumenttemplateForm->do_request(pcreate);

         __pointer(::user::document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         form * pformview = pdocument->get_typed_view < form >();

         auto pupdate = new_update();

         pupdate->m_id = BROWSE_ID;

         if (pimpactdata->m_id == "new_folder")
         {

            pupdate->value(FORM_ID) = "matter://filemanager/new_folder.html";

         }
         if (pimpactdata->m_id == "replace_name")
         {

            pupdate->value(FORM_ID) = "matter://filemanager/replace_name_in_file_system.html";

         }
         else if (pimpactdata->m_id == "add_location")
         {

            pupdate->value(FORM_ID) = "matter://filemanager/add_location_1.html";

         }

         pformview->m_idCreator = pimpactdata->m_id;

         pdocument->update_all_views(pupdate);

         pupdate->m_id = id_after_browse;

         pdocument->update_all_views(pupdate);

         pimpactdata->m_pdocument = pdocument;

      }
      else if(pimpactdata->m_id == "filemanager::operation")
      {

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = false;

         pcreate->m_puserinteractionParent = this;

         User.m_pdocumenttemplateOperation->do_request(pcreate);

         __pointer(operation_document) pdocument = ::user::__document(pcreate);

         if (pdocument == nullptr)
         {

            return;

         }

         __pointer(::user::impact) pview = pdocument->get_view(0);

         pimpactdata->m_puserinteraction = pview->GetParentFrame();

         pimpactdata->m_pdocument = pdocument;

      }
      else
      {

         auto pfilemanagerdata  = __new(::filemanager::data);

         pfilemanagerdata->m_pcallback = get_document();

         //pfilemanagerdata->m_pfilemanagertemplate = User.filemanager();

         pfilemanagerdata->m_bFileSize = true;

         pfilemanagerdata->m_bTransparentBackground = true;

         __pointer(::create) pcreate(e_create);

         pcreate->m_bMakeVisible = true;

         pcreate->m_puserinteractionParent = pimpactdata->m_pplaceholder;

         pcreate->value("filemanager::data") = pfilemanagerdata;

         string str = pimpactdata->m_id;

         ::str::begins_eat_ci(str, "verifile://");

         ::file::path pathFolder = str;

         string strVarFile;

         if (get_document()->m_strManagerId.has_char())
         {

            strVarFile = get_document()->m_strManagerId + ":" + pathFolder;

         }

         pcreate->m_pcommandline->m_varFile = strVarFile;

         //User.filemanager()->m_pdocumenttemplateChild->m_bQueueDocumentOpening = false;

         //User.filemanager()->m_pdocumenttemplateChild->do_request(pcreate);

         //__pointer(document) pdocument = ::user::__document(pcreate);

         //__pointer(simple_frame_window) pwndTopLevel;
         __pointer(document) pdocument = get_document();

         create_view < view >(pimpactdata);

         if(pdocument != nullptr)
         {

            m_pfilemanager = pdocument;

//            pdocument->filemanager_data()->m_iTemplate = User.filemanager()->m_iTemplate;

            //          pdocument->filemanager_data()->m_iDocument = User.filemanager()->m_iNextDocument++;

            __pointer(::user::impact) pview = pdocument->get_view(0);

            __pointer(simple_frame_window) pwnd = (pview->GetParentFrame());

            bool bPathIsDir = false;

            thread_set(id_thread_resolve_alias);

            try
            {

               bPathIsDir = pathFolder.has_char() && Context.dir().is(pathFolder);

            }
            catch (...)
            {

            }

            thread_unset(id_thread_resolve_alias);

            if(bPathIsDir)
            {

               pdocument->filemanager_initialize(true, false);

               pdocument->browse(pathFolder, ::source_initialize);

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


   void tab_view::_001OnCreate(::message::message * pmessage)
   {

      pmessage->previous();

      m_pfilemanager = get_document();

   }


   __pointer(document) tab_view::get_document()
   {

      return ::user::impact::get_document();

   }




   void tab_view::update(::update * pupdate)
   {

      impact::update(pupdate);

      ::user::tab_view::update(pupdate);

      ////__update(::update)
      {

         if (pupdate->m_id == id_open_document)
         {

            //if (m_viewmap.get_count() == 0)
            //{

            //   set_cur_tab_by_id(0);

            //}

         }

      }

      ////__update(::update)
      {

         if (pupdate->m_id == id_initialize)
         {

            //               string str;
            //
            //               str.Format("(%d,%d)",filemanager_document().filemanager_data()->m_iTemplate,filemanager_document().filemanager_data()->m_iDocument);
            //
            //               __pointer(::database::client) pclient = GetParentFrame();
            //
            //               if (pclient.is_set())
            //               {
            //
            //                  pclient->set_data_key_modifier(str);
            //
            //               }

         }
         else if (pupdate->m_id == id_pop)
         {

            __pointer(::user::frame_window) pframe = GetParentFrame();

            if (pframe.is_set())
            {

               pframe->InitialUpdateFrame(nullptr, TRUE);

               pframe->display(display_normal);

               pframe->ActivateFrame(display_normal);

            }

         }


      }

      if (pupdate->m_id == id_add_location)
      {

         set_cur_tab_by_id("add_location");

      }
      else if (pupdate->m_id == id_replace_name)
      {

         set_cur_tab_by_id("replace_name");

      }
      else if (pupdate->m_id == id_new_folder)
      {
         set_cur_tab_by_id("new_folder");
      }

   }


} // namespace filemanager



