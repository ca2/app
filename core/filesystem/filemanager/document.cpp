#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif

#include "aura/update.h"
#include "base/user/user/tab_pane.h"


namespace filemanager
{


   document::document()
   {

      m_bInitialized = false;

      m_filewatchid = -1;

      m_bFullBrowse = false;

      //m_pfilewatcherlistenerthread = nullptr;

      //command_signalid id;

      add_command_prober("levelup", this, &document::_001OnUpdateLevelUp);
      add_command_handler("levelup", this, &document::_001OnLevelUp);
      add_command_prober("add_location", this, &document::_001OnUpdateAddLocation);
      add_command_handler("add_location", this, &document::_001OnAddLocation);
      add_command_prober("replace_text_in_file_system", this, &document::_001OnUpdateReplaceText);
      add_command_handler("replace_text_in_file_system", this, &document::_001OnReplaceText);
      add_command_prober("edit_paste", this, &document::_001OnUpdateEditPaste);
      add_command_handler("edit_paste", this, &document::_001OnEditPaste);
      add_command_prober("file_save", this, &document::_001OnUpdateFileSaveAs);
      add_command_handler("file_save", this, &document::_001OnFileSaveAs);
      add_command_prober("cancel", this, &document::_001OnUpdateEditPaste);
      add_command_handler("cancel", this, &document::_001OnEditPaste);
      add_command_prober("new_manager", this, &document::_001OnUpdateNewManager);
      add_command_handler("new_manager", this, &document::_001OnNewManager);
      add_command_prober("del_manager", this, &document::_001OnUpdateDelManager);
      add_command_handler("del_manager", this, &document::_001OnDelManager);
      add_command_prober("new_folder", this, &document::_001OnUpdateNewFolder);
      add_command_handler("new_folder", this, &document::_001OnNewFolder);

   }


   document::~document()
   {

   }

   bool document::do_prompt_file_name(::payload & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocumentOther)
   {

      __UNREFERENCED_PARAMETER(nIDSTitle);
      __UNREFERENCED_PARAMETER(lFlags);
      __UNREFERENCED_PARAMETER(ptemplate);

      ASSERT(bOpenFileDialog == false);

      __pointer(document) pdocument = this;

      tab_view * pview = pdocument->get_typed_view < tab_view >();

//#ifdef WINDOWS_DESKTOP
//      oswindow oswindowDesktop = ::get_desktop_window();
//      ::rectangle_i32 rectangleOpen;
//      ::GetWindowRect(oswindowDesktop, rectangleOpen);
//      i32 iWidth = rectangleOpen.width();
//      i32 iHeight = rectangleOpen.width();
//      rectangleOpen.deflate(iWidth / 5, iHeight / 5);
//      pview->get_parent_frame()->order(e_zorder_top);
//      pview->get_parent_frame()->place(rectangleOpen);
//      pview->get_parent_frame()->display();
//
//#endif
      pview->set_current_tab_by_id(1);
      pview->get_parent_frame()->set_need_redraw();
      pview->get_parent_frame()->RunModalLoop();
      varFile = pdocument->m_strTopic;
      pview->get_parent_frame()->destroy_window();
      return true;

   }


   bool document::browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      if (m_pfsset->m_spafsdata.is_empty())
      {

         m_pfsset->m_spafsdata.erase_all();

         auto psession = get_session();

         m_pfsset->m_spafsdata.add(psession->fs());

         ::file::listing listing;

         m_pfsset->root_ones(listing);

      }

      string strOldPath;

      if (m_pitem.is_set())
      {

         strOldPath = m_pitem->m_filepathUser;

      }

      try
      {

         m_pitem = __new(::file::item(*pitem));

         OnFileManagerBrowse(context + ::e_source_sync);

      }
      catch (string & str)
      {

         if (str == "uifs:// You have not logged in!")
         {

            output_error_message("You have not logged in! Cannot access your User Intelligent File System - uifs://");

            // assume can resume at least from this exception one time

            auto pcontext = get_context();

            m_pitem = __new(::file::item(pcontext->m_papexcontext->defer_process_path(strOldPath), strOldPath));

            OnFileManagerBrowse(context + ::e_source_sync);

         }

         return false;

      }

      if (m_filewatchid >= 0)
      {

         auto pcontext = get_context();

         pcontext->m_papexcontext->dir().watcher().erase_watch(m_filewatchid);

      }

      try
      {

         auto pcontext = get_context();

         auto& dir = pcontext->m_papexcontext->dir();

         auto& watcher = dir.watcher();

         m_filewatchid = watcher.add_watch(m_pitem->m_filepathFinal, this, false);

      }
      catch (...)
      {

         m_filewatchid = -1;

      }

      return true;

   }


   void document::on_file_manager_open_context_menu_folder(__pointer(::file::item)  item, string_array & straCommand, string_array & straCommandTitle, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_open_context_menu_folder(pfilemanagerdata, item, straCommand, straCommandTitle, context);

      }

   }


   void document::on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_open_context_menu_file(pfilemanagerdata, itema, context);

      }

   }


   void document::on_file_manager_open_context_menu(const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_open_context_menu(pfilemanagerdata, context);

      }

   }


   void document::on_file_manager_open(const ::file::item_array & itema, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->is_topic() && itema.get_count() == 1)
      {

         __pointer(document) pdocument = this;

         ::subject subject(TOPIC_OK_ID);

         subject.payload(DOCUMENT_ID) = pdocument;

         subject.m_pfileitem = itema.get_first_pointer();

         pdocument->update_all_views(&subject);

         pfilemanagerdata->m_pdocumentTopic = nullptr;

      }
      else if (pfilemanagerdata->m_pcallback != nullptr)
      {

         ::payload varFile;

         ::payload varQuery;

         if (itema.get_count() == 2 && m_id == "filemanager::main::left")
         {

            {

               varFile = itema[0]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::left";

               pfilemanagerdata->m_pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

            }

            {

               varFile = itema[1]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::right";

               pfilemanagerdata->m_pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

            }

         }
         else if (itema.get_count() == 2 && m_id == "filemanager::main::right")
         {

            {

               varFile = itema[0]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::right";

               pfilemanagerdata->m_pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

            }

            {

               varFile = itema[1]->get_user_path();

               varQuery["::filemanager::id"] = "filemanager::main::left";

               pfilemanagerdata->m_pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

            }

         }
         else
         {

            varFile = itema.get_var_final_path();

            varQuery = itema.get_var_query();

            varQuery["::filemanager::id"] = m_id;

            auto pcallback = pfilemanagerdata->m_pcallback;

            pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

         }

      }

   }


   void document::on_file_manager_open_folder(__pointer(::file::item)  item, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_open_folder(pfilemanagerdata, item, context);

      }

   }


   void document::on_file_manager_item_update(::message::command * pcommand, const ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_item_update(pfilemanagerdata, pcommand, itema);

      }

   }


   void document::on_file_manager_item_command(const ::string & pszId, const ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pcallback != nullptr);

      if (pfilemanagerdata->m_pcallback != nullptr)
      {

         pfilemanagerdata->m_pcallback->on_file_manager_item_command(pfilemanagerdata, pszId, itema);

      }

   }


   //void document::browse(__pointer(::file::item) item, const ::action_context & context)
   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_document()->browse(item, context);

   //   }

   //}

   //void data::browse(const ::string & pcsz, const ::action_context & context)

   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_document()->browse(pcsz, context);


   //   }

   //}


   void document::browse(const ::string & pszPath, const ::action_context & context)
   {

      ::file::path pathUser = pszPath;

      auto pcontext = get_context();

      ::file::path pathFinal = pcontext->m_papexcontext->defer_process_path(pathUser);

      __pointer(::file::item) pitem = __new(::file::item(pathUser, pathFinal));

      browse(pitem, context);

   }


   void document::FileManagerOneLevelUp(const ::action_context & context)
   {

      if (filemanager_item()->m_filepathUser.is_empty())
      {

         return;

      }

      string strParent = filemanager_item()->m_filepathUser.up();

      browse(strParent, context + ::e_source_sync);

   }


   ::file::item * document::filemanager_item()
   {

      return m_pitem;

   }


   ::filemanager::data * document::filemanager_data()
   {

      return m_pfilemanagerdata;

   }


   ::fs::data * document::fs_data()
   {

      return m_pfsset;

   }


   document * document::get_main_document()
   {

      __pointer(tab_view) ptabview = get_typed_view < tab_view >();

      if (ptabview.is_set())
      {

         for (index i = 0; i < ptabview->get_tab_count(); i++)
         {

            ::user::tab_pane * ptabpane = ptabview->get_tab(i);

            if (ptabpane != nullptr && ptabpane->m_pplaceholder != nullptr)
            {

               __pointer(child_frame) pchildframe = ptabpane->m_pplaceholder->first_child();

               if (pchildframe.is_set())
               {

                  __pointer(document) pdocument = pchildframe->get_active_document();

                  if (pdocument.is_set())
                  {

                     return pdocument;

                  }

               }

            }

         }

      }

      return this;

   }


   bool document::set_filemanager_data(::filemanager::data * pdata)
   {

      m_pfilemanagerdata = pdata;

      return true;

   }


   void document::defer_check_manager_id(string strManagerId)
   {

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      if(puser->m_pathFilemanagerProject.has_char())
      {

         if (!is_valid_manager_id(m_strManagerId) || is_valid_manager_id(strManagerId))
         {

            if (is_valid_manager_id(strManagerId))
            {

               m_strManagerId = strManagerId;

            }
            else
            {

               m_strManagerId = create_manager_id(this);

            }

            //set_data_key_modifier(m_strManagerId);

  /*          __pointer(main_frame) pframe = get_view()->GetTypedParent < main_frame >();

            if (pframe.is_set() && !pframe->m_id.to_string().contains("::frame"))
            {

               pframe->set_data_key_modifier(m_strManagerId);

            }*/

         }

         __pointer(document) pdocument = get_main_document();

         if (pdocument.is_set() && pdocument.m_p != this && pdocument->m_strManagerId != m_strManagerId)
         {

            pdocument->defer_check_manager_id(m_strManagerId);

         }

      }

   }


   //critical_section * document::GetItemIdListCriticalSection()
   //{
   //   return &m_csItemIdListAbsolute;
   //}


   void document::FileManagerTopicOK()
   {

   }


   void document::FileManagerTopicCancel()
   {

   }


   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
      {

         return false;

      }

      defer_check_manager_id();

      if (!m_bInitialized)
      {

         filemanager_initialize(true, true);

      }

      return true;

   }



   bool document::on_open_document(const ::payload & varFile)
   {

      ::file::path path = varFile.get_file_path();

      path.trim();

      defer_check_manager_id();

      if (!m_bInitialized)
      {

         filemanager_initialize(true, false);

      }

      string strManagerId;

      auto pcontext = m_pcontext->m_pauracontext;

      m_path = filemanager_project_entry(strManagerId, varFile.string(), pcontext);

      defer_check_manager_id(strManagerId);

      return true;

   }


   void document::assert_valid() const
   {
      ::user::document::assert_valid();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }


   void document::start_full_browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      if (!fs_data()->is_zero_latency(pitem->m_filepathFinal))
      {

         ::subject subject(SYNCHRONIZE_PATH_ID);

         subject.m_actioncontext = context + ::e_source_sync + ::e_source_system;

         subject.m_pfileitem = pitem;

         update_all_views(&subject);

      }

      fork(__routine([this, pitem, context]()
      {

         full_browse(pitem, context);

      }));

   }


   void document::full_browse(__pointer(::file::item) pitem, const ::action_context & context)
   {

      __task_guard(m_bFullBrowse);

#define DBG_BROWSE_LOOP 1
      for (index i = 0; i < DBG_BROWSE_LOOP; i++)
      {

         ::userfs::document::browse(pitem, context);

      }

      ::subject subject(SYNCHRONIZE_PATH_ID);

      subject.m_actioncontext = context + ::e_source_sync;

      subject.m_pfileitem = pitem;

      update_all_views(&subject);

   }


   void document::OnFileManagerBrowse(const ::action_context & context)
   {

      start_full_browse(m_pitem, context);

      if (context.is_user_source())
      {

         auto pcontext = m_pcontext;
         
         auto psession = pcontext->m_pcoresession;
         
         auto puser = psession->m_puser->m_pcoreuser;

         auto pfilemanagerdata = filemanager_data();

         if (puser->m_pathFilemanagerProject.is_empty())
         {

            pfilemanagerdata->set_last_browse_path(this, m_pitem->m_filepathUser);

         }
         else
         {

            puser->filemanager_save_project();

         }

      }

   }


   void document::OpenSelectionProperties()
   {

      auto psubject = subject(id_open_selection_properties);

      update_all_views(psubject);

   }


   void document::on_command(::message::command * pcommand)
   {

      auto pfilemanagerdata = filemanager_data();

      if (pfilemanagerdata != nullptr)
      {

         if (pcommand->m_id == "levelup")
         {

            FileManagerOneLevelUp(::e_source_user);

            pcommand->m_bRet = true;

            return;

         }

      }

      ::user::document::on_command(pcommand);

   }


   void document::on_command_probe(::message::command * pcommand)
   {
      /*if(pcommand->m_id == filemanager_template()->m_strLevelUp)
      {
      FileManagerOnUpdateLevelUp(pcommand);
      return true;
      }*/
      ::user::document::on_command_probe(pcommand);

   }



   void document::_001OnUpdateNewManager(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewManager(::message::message * pmessage)
   {

      auto pcreate = __create_new <::create>();

      pcreate->finish_initialization();

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->add_filemanager("", pcreate);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateDelManager(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnDelManager(::message::message * pmessage)
   {

      __pointer(document) pdocument = this;

      __pointer(impact) pview = get_typed_view<impact>();

      if (pview.is_set())
      {

         __pointer(tab_view) ptabview = pview->GetTypedParent <tab_view>();

         if (ptabview.is_set())
         {

            pdocument = ptabview->get_document();

         }

      }

      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      puser->erase_filemanager(pdocument.m_p);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateLevelUp(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      if (m_pitem.is_null() || m_pitem->m_filepathUser.is_empty())
      {

         pcommand->enable(false);

      }
      else
      {

         pcommand->enable(true);

      }

      pmessage->m_bRet = true;

   }


   void document::_001OnLevelUp(::message::message * pmessage)
   {
      FileManagerOneLevelUp(::e_source_user);
      pmessage->m_bRet = true;
   }


   void document::_001OnUpdateAddLocation(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnAddLocation(::message::message * pmessage)
   {

      id_update_all_views(id_add_location);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateReplaceText(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnReplaceText(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      id_update_all_views(id_replace_name);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateNewFolder(::message::message * pmessage)
   {

      __pointer(::message::command) pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewFolder(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      id_update_all_views(id_new_folder);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateEditPaste(::message::message * pmessage)
   {
      //      __pointer(::message::command) pcommand(pmessage);

      //         pcommand->enable(psystem->m_strCopy.is_empty());
      pmessage->m_bRet = true;
   }

   void document::_001OnEditPaste(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //pcontext->m_papexcontext->file().paste(pfilemanagerdata->filemanager_item().m_strPath, psystem->m_strCopy);
      //update_all_views(nullptr, 123, nullptr);
      //pmessage->m_bRet = true;
   }

   void document::_001OnUpdateFileSaveAs(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->enable(true);
   }

   void document::_001OnUpdateFileImport(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->enable(true);
   }

   void document::_001OnUpdateFileExport(::message::message * pmessage)
   {
      __pointer(::message::command) pcommand(pmessage);
      pcommand->enable(true);
   }


   void document::_001OnFileSaveAs(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_saving || m_emode == ::userfs::mode_export)
      {

         ::subject subject(id_topic_ok);

         subject.payload(id_document) = this;

         update_all_views(&subject);

      }

      pmessage->m_bRet = true;

   }


   void document::_001OnFileImport(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_import)
      {

         ::subject subject(id_topic_ok);

         subject.payload(id_document) = this;

         update_all_views(&subject);

      }

   }


   void document::_001OnFileExport(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      if (m_emode == ::userfs::mode_saving)
      {

         ::subject subject(id_topic_ok);

         subject.payload(id_document) = this;

         update_all_views(&subject);

      }

   }


   void document::filemanager_initialize(bool bMakeVisible, const ::file::path & path)
   {

      InitializeFileManager("filemanager");

      CreateViews();

      ::subject subject(id_create_bars);

      subject.payload(id_document) = this;

      browse(path, ::e_source_database);

      update_all_views(&subject);

      if (bMakeVisible)
      {

         ::subject subject(id_pop);

         update_all_views(&subject);

      }

   }


   void document::filemanager_initialize(bool bMakeVisible, bool bInitialBrowsePath)
   {

      CreateViews();

      auto psubject = create_subject(id_create_bars);

      psubject->payload(id_document) = this;

      if (bInitialBrowsePath)
      {

         string str;

         auto pfilemanagerdata = filemanager_data();

         auto path = pfilemanagerdata->get_last_browse_path(this, pfilemanagerdata->m_pathDefault);

         browse(path, ::e_source_initialize);

//         if (get_file.data_get({true, "last_browse_folder"}, str))
//         {
//
//            if (str == "machinefs://")
//            {
//
//               id idMachine;
//
//#ifdef LINUX
//               idMachine = "Linux";
//#elif defined(WINDOWS_DESKTOP)
//               idMachine = "WindowsDesktop";
//#elif defined(WINDOWS)
//               idMachine = "Metrowin";
//#elif defined(MACOS)
//               idMachine = "macOS";
//#elif defined(__APPLE__)
//               idMachine = "iOS";
//#endif
//
//               if (papplication->data_get({true, "last_browse_folder." + __str(idMachine)}, str))
//               {
//
//                  browse(str, ::e_source_database);
//
//               }
//               else
//               {
//
//                  browse("", ::e_source_system);
//
//               }
//
//            }
//            else
//            {
//
               //browse(str, ::e_source_database);

//            }

         //}
         //else if (pfilemanagerdata->m_pathDefault.has_char())
         //{

         //   browse(pfilemanagerdata->m_pathDefault, ::e_source_initialize);

         //}
         //else
         //{

         //   browse("", ::e_source_system);

         //}

      }

      //psubject->id() = ;

      //update_all_views(pupdate);

   }


   void document::OpenFolder(::file::item * pitem, const ::action_context & context)
   {

      browse(pitem, context);

   }


   void document::CreateViews()
   {

      {

         auto psubject = create_subject(id_initialize);

         psubject->payload(id_document) = this;

         update_all_views(psubject);

      }

      {

         auto psubject = create_subject(id_synchronize_locations);

         psubject->m_actioncontext = ::e_source_sync;

         psubject->payload(id_document) = this;

         update_all_views(psubject);

      }

   }


   void document::PopViews()
   {

      {

         subject subject(id_create_bars);

         subject.payload(id_document) = this;

         update_all_views(&subject);

      }

      {

         ::subject subject(id_pop);

         update_all_views(&subject);

      }

   }


   bool document::HandleDefaultFileManagerItemCmdMsg(::message::command * pcommand, ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      if (pcommand->is_command_probe())
      {

         if (pfilemanagerdata != nullptr)
         {

            if (pfilemanagerdata->m_pcallback != nullptr)
            {

               if (pfilemanagerdata->m_pcallback->get_file_manager_item_callback(pfilemanagerdata, pcommand->m_id, itema))
               {

                  pfilemanagerdata->m_pcallback->on_file_manager_item_update(pfilemanagerdata, pcommand, itema);

                  return true;

               }

            }

         }

      }
      else if (pcommand->is_command())
      {

         if (pfilemanagerdata != nullptr)
         {

            auto pcallback = pfilemanagerdata->m_pcallback;

            if (::is_set(pcallback))
            {

               if (pcallback->get_file_manager_item_callback(pfilemanagerdata, pcommand->m_id, itema))
               {

                  pcallback->on_file_manager_item_command(pfilemanagerdata, pcommand->m_id, itema);

                  return true;

               }

            }

         }

      }

      return false;

   }


   operation_document * document::get_operation_doc(bool bSwitch)
   {

      //::filemanager::tab_view * ptabview = psession->m_pdocumenttemplateMain->get_document(0)->get_typed_view < ::filemanager::tab_view >();

      //if (ptabview == nullptr)
      //{

      //   return nullptr;

      //}

      //ASSERT(ptabview != nullptr);

      //if (ptabview != nullptr)
      //{

      //   if (bSwitch)
      //   {

      //      ptabview->set_current_tab_by_id("filemanager::operation");

      //   }
      //   else
      //   {

      //      ptabview->create_tab_by_id("filemanager::operation");

      //   }

      //   return dynamic_cast < operation_document * > (ptabview->get("filemanager::operation")->m_pdocument);

      //}

      return nullptr;

   }


   void document::GetActiveViewSelection(::file::item_array & itema)
   {

      ::subject subject(id_get_active_view_selection);

      update_all_views(&subject);

      itema = *subject.cast < ::file::item_array>(id_selected);

   }


   void document::FileManagerSaveAs(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_saving;

      auto pdocumentFilemanager = this;

      {

         auto psubject = create_subject(id_topic_start);

         psubject->payload(id_document) = pdocumentFilemanager;

         pdocumentFilemanager->update_all_views(psubject);

      }

      {

         auto psubject = create_subject(id_create_bars);

         pdocumentFilemanager->update_all_views(psubject);

      }

   }


   void document::FileManagerImport(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_import;

      auto pdocumentFilemanager = this;

      {

         ::subject subject(id_topic_start);

         subject.payload(id_document) = pdocumentFilemanager;

         pdocumentFilemanager->update_all_views(&subject);

      }

      {

         ::subject subject(id_create_bars);

         pdocumentFilemanager->update_all_views(&subject);

      }

   }


   void document::FileManagerExport(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      m_emode = ::userfs::mode_export;

      auto pdocumentFilemanager = this;

      {

         ::subject subject(id_topic_start);

         subject.payload(id_document) = pdocumentFilemanager;

         pdocumentFilemanager->update_all_views(&subject);

      }

      {

         ::subject subject(id_create_bars);

         pdocumentFilemanager->update_all_views(&subject);

      }

   }



   void document::on_create(::create * pcreate)
   {

      ::user::document::on_create(pcreate);

      m_pfilemanagerdata = pcreate->cast < ::filemanager::data >("filemanager::data");
      
      auto pcontext = m_pcontext;
      
      auto psession = pcontext->m_pcoresession;
      
      auto puser = psession->m_puser->m_pcoreuser;

      if (m_pfilemanagerdata.is_null())
      {

         m_pfilemanagerdata = puser->filemanager(pcreate->m_id);

      }
      ASSERT(m_pfilemanagerdata.is_set());

      //if (m_pfilemanagerdata.is_null())
      //{

      //   //__pointer(manager_template) ptemplate = pcreate->prop("filemanager::template").cast < manager_template >();

      //   //if (ptemplate.is_null())
      //   //{

      //   //   ptemplate = puser->filemanager().m_ptemplate;

      //   //}

      //   if (ptemplate.is_null())
      //   {

      //      m_pfilemanagerdata = __new(data(this));

      //   }
      //   else
      //   {

      //      m_pfilemanagerdata = ptemplate->create_file_manager_data(pcreate);

      //   }

      //}

      m_pfilemanagerdata->m_pdocument = this;

   }


   void document::on_request(::create * pcreate)
   {

      //::filemanager::callback::on_request(pcreate);

      auto papplication = get_application();

      papplication->call_request(pcreate);

   }


   __pointer(::filemanager::data) document::create_file_manager_data(::create * pcreate)
   {

      __pointer(::filemanager::data) pfilemanagerdata(__new(data));

      ::filemanager::callback * pcallback = nullptr;

      if (pcreate != nullptr)
      {

         pcallback = pcreate->cast < ::filemanager::callback >("department::callback");

      }

      pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : this;

      pfilemanagerdata->m_bTransparentBackground = pcreate == nullptr ? true : pcreate->m_bTransparentBackground;

      pfilemanagerdata->m_bFileSize = true;

      return pfilemanagerdata;

   }


   ::id document::get_toolbar_id()
   {

      auto pfilemanagerdata = filemanager_data();

      return pfilemanagerdata->m_setToolbar[m_emode];

   }


   void document::handle_file_action(::file::action * paction)
   {

      auto eaction = paction->m_eaction;

      if (eaction == ::file::e_action_delete
            || eaction == ::file::e_action_add
            || eaction == ::file::e_action_modify)
      {

         OnFileManagerBrowse(::e_source_sync);

      }

   }




} // namespace filemanager



