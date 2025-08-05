#include "framework.h"
#include "document.h"
#include "impact.h"
#include "tab_impact.h"
#include "data.h"
#include "child_frame.h"
#include "filemanager.h"
#include "acme/constant/id.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/file/item_array.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/watcher/action.h"
#include "acme/filesystem/watcher/watcher.h"
#include "acme/handler/request.h"
#include "acme/handler/extended_topic.h"
#include "acme/handler/topic.h"
#include "acme/platform/keep.h"
#include "acme/platform/system.h"
#include "apex/filesystem/fs/set.h"
#include "aura/graphics/image/icon.h"
#include "berg/user/user/tab_pane.h"
#include "core/user/user/user.h"
#include "core/platform/session.h"
#include "core/platform/application.h"


namespace filemanager
{


   document::document()
   {

      m_bInitialized = false;

      //m_pfilewatch = -1;


      //m_pfilewatcherlistenerthread = nullptr;

      //command_signalid atom;

      add_command_prober("levelup", { this,  &document::_001OnUpdateLevelUp });
      add_command_handler("levelup", { this,  &document::_001OnLevelUp });
      add_command_prober("add_location", { this,  &document::_001OnUpdateAddLocation });
      add_command_handler("add_location", { this,  &document::_001OnAddLocation });
      add_command_prober("replace_text_in_file_system", { this,  &document::_001OnUpdateReplaceText });
      add_command_handler("replace_text_in_file_system", { this,  &document::_001OnReplaceText });
      add_command_prober("edit_paste", { this,  &document::_001OnUpdateEditPaste });
      add_command_handler("edit_paste", { this,  &document::_001OnEditPaste });
      add_command_prober("file_save", { this,  &document::_001OnUpdateFileSaveAs });
      add_command_handler("file_save", { this,  &document::_001OnFileSaveAs });
      add_command_prober("cancel", { this,  &document::_001OnUpdateEditPaste });
      add_command_handler("cancel", { this,  &document::_001OnEditPaste });
      add_command_prober("new_manager", { this,  &document::_001OnUpdateNewManager });
      add_command_handler("new_manager", { this,  &document::_001OnNewManager });
      add_command_prober("del_manager", { this,  &document::_001OnUpdateDelManager });
      add_command_handler("del_manager", { this,  &document::_001OnDelManager });
      add_command_prober("new_folder", { this,  &document::_001OnUpdateNewFolder });
      add_command_handler("new_folder", { this,  &document::_001OnNewFolder });

   }


   document::~document()
   {

   }


   // ::core::application * document::get_app()
   // {
   //
   //    auto papplication = application();
   //
   //    return ::is_set(papplication) ? papplication : nullptr;
   //
   // }
   //
   //
   // ::core::session * document::get_session()
   // {
   //
   //    auto pacmesession = session();
   //
   //    return ::is_set(pacmesession) ? pacmesession : nullptr;
   //
   // }
   //
   //
   // ::core::system * document::get_system()
   // {
   //
   //    auto pacmesystem = system();
   //
   //    return ::is_set(pacmesystem) ? pacmesystem : nullptr;
   //
   // }


   bool document::do_prompt_file_name(::payload & payloadFile, const ::scoped_string & scopedstrTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pfilemanagerdataOther)
   {

      __UNREFERENCED_PARAMETER(scopedstrTitle);
      __UNREFERENCED_PARAMETER(lFlags);
      __UNREFERENCED_PARAMETER(ptemplate);

      ASSERT(bOpenFileDialog == false);

      ::pointer<document>pfilemanagerdata = this;

      tab_impact * pimpact = pfilemanagerdata->get_typed_impact < tab_impact >();

      //#ifdef WINDOWS_DESKTOP
      //      oswindow oswindowDesktop = ::get_desktop_window();
      //      ::int_rectangle rectangleOpen;
      //      ::GetWindowRect(oswindowDesktop, rectangleOpen);
      //      int iWidth = rectangleOpen.width();
      //      int iHeight = rectangleOpen.width();
      //      rectangleOpen.deflate(iWidth / 5, iHeight / 5);
      //      pimpact->get_parent_frame()->order(e_zorder_top);
      //      pimpact->get_parent_frame()->place(rectangleOpen);
      //      pimpact->get_parent_frame()->display();
      //
      //#endif
      pimpact->set_current_tab_by_id(1);
      pimpact->parent_frame()->set_need_redraw();
      pimpact->parent_frame()->wait_for_dialog_result();
      payloadFile = pfilemanagerdata->m_strTopic;
      pimpact->parent_frame()->destroy_window();
      return true;

   }



   void document::on_file_manager_open_context_menu_folder(::pointer<::file::item> item, string_array & straCommand, string_array & straCommandTitle, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open_context_menu_folder(pfilemanagerdata, item, straCommand, straCommandTitle, context);

      }

   }


   void document::on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open_context_menu_file(pfilemanagerdata, itema, context);

      }

   }


   void document::on_file_manager_open_context_menu(const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open_context_menu(pfilemanagerdata, context);

      }

   }


   void document::on_file_manager_open(const ::file::item_array & itema, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      //ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->is_topic() && itema.get_count() == 1)
      {

         ::pointer<document>pdocument = this;

         auto ptopic = create_topic(id_topic_ok);

         ptopic->payload(id_document) = pfilemanagerdata;

         ptopic->_extended_topic()->m_pfileitem = itema.get_first_pointer();

         pdocument->update_all_impacts(ptopic);

         pfilemanagerdata->m_pdocumentTopic = nullptr;

      }
      else if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         //::payload payloadFile;

         //::payload varQuery;

         //if (itema.get_count() == 2 && id() == "filemanager::main::left")
         //{

         //   {

         //      //payloadFile = itema[0]->get_user_path();

         //      //varQuery["::filemanager::atom"] = "filemanager::main::left";

         //      pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open(pfilemanagerdata, itema, context);

         //   }

         //   {

         //      //payloadFile = itema[1]->get_user_path();

         //      //varQuery["::filemanager::atom"] = "filemanager::main::right";

         //      pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open(pfilemanagerdata, itema, context);

         //   }

         //}
         //else if (itema.get_count() == 2 && id() == "filemanager::main::right")
         //{

         //   {

         //      //payloadFile = itema[0]->get_user_path();

         //      //varQuery["::filemanager::atom"] = "filemanager::main::right";

         //      pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open(pfilemanagerdata, itema, context);

         //   }

         //   {

         //      //payloadFile = itema[1]->get_user_path();

         //      //varQuery["::filemanager::atom"] = "filemanager::main::left";

         //      pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open(pfilemanagerdata, itema, context);

         //   }

         //}
         //else
         //{

         //   //payloadFile = itema.get_var_final_path();

         //   //varQuery = itema.get_var_query();

         //   //varQuery["::filemanager::atom"] = id();

         auto pcallback = pfilemanagerdata->m_pfilemanagercallback;

         pcallback->on_file_manager_open(pfilemanagerdata, itema, context);

         //         }

      }
      else if(itema.has_element())
      {

         auto prequest = __create_new <::request>();

         prequest->m_payloadFile = itema[0]->user_path();
         
         prequest->m_ecommand = ::e_command_file_open;

         application()->request(prequest);

      }

   }


   void document::on_file_manager_open_folder(::pointer<::file::item> item, const ::action_context & context)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_open_folder(pfilemanagerdata, item, context);

      }

   }


   void document::on_file_manager_item_update(::message::command * pcommand, const ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_item_update(pfilemanagerdata, pcommand, itema);

      }

   }


   void document::on_file_manager_item_command(const ::scoped_string & scopedstrId, const ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      ASSERT(pfilemanagerdata->m_pfilemanagercallback != nullptr);

      if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
      {

         pfilemanagerdata->m_pfilemanagercallback->on_file_manager_item_command(pfilemanagerdata, scopedstrId, itema);

      }

   }


   //void document::browse(::pointer<::file::item>item, const ::action_context & context)
   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_data()->browse(item, context);

   //   }

   //}

   
   //void data::browse(const ::file::path & path, const ::action_context & context)
   //{

   //   ASSERT(filemanager_document() != nullptr);

   //   if (filemanager_document() != nullptr)
   //   {

   //      filemanager_data()->browse(pcsz, context);


   //   }

   //}


   void document::browse(const ::file::path & path, const ::action_context & context)
   {

       filemanager_data()->browse(path, context);

   }


   //void document::browse(const ::file::path & pathUser, const ::action_context & context)
   //{

   //   // auto pcontext = get_context();

   //   ::file::path pathFinal = m_papplication->defer_process_matter_path(pathUser);

   //   ::pointer<::file::item>pitem = __allocate ::file::item(pathUser, pathFinal);

   //   browse(pitem, context);

   //}


   bool document::browse(::pointer<::file::item>pitem, const ::action_context & context)
   {

      if (m_pfilewatch)
      {

         // auto pcontext = get_context();

         file_watcher()->erase_watch(m_pfilewatch);

      }

      if (!::userfs::document::browse(pitem, context))
      {

         return false;

      }



      return true;

   }


   void document::on_update_data(::data::data * pdata, ::topic * ptopic, const ::action_context & context)
   {

      if (ptopic->id() == id_browse)
      {

         OnFileManagerBrowse(::e_source_sync);

         update_all_impacts(ptopic);

      }

   }


   //   void document::assert_ok() const
   //   {
   //
   //      ::user::document::assert_ok();



   void document::FileManagerOneLevelUp(const ::action_context & context)
   {

      if (filemanager_item()->user_path().is_empty())
      {

         return;

      }

      auto pathParent = filemanager_item()->user_path().parent();

      browse(pathParent, context + ::e_source_sync);

   }


   ::file::item * document::filemanager_item()
   {

      return filemanager_data()->m_pitem;

   }


   ::filemanager::data * document::filemanager_data()
   {

      return m_pfilemanagerdata;

   }


   //::fs::data * document::fs_data()
   //{

   //   return m_pfsset;

   //}


   document * document::get_main_document()
   {

      ::pointer<tab_impact>ptabimpact = get_typed_impact < tab_impact >();

      if (ptabimpact.is_set())
      {

         for (::collection::index i = 0; i < ptabimpact->get_tab_count(); i++)
         {

            ::user::tab_pane * ptabpane = ptabimpact->get_tab(i);

            if (ptabpane != nullptr && ptabpane->m_pplaceholder != nullptr)
            {

               ::pointer<child_frame>pchildframe = ptabpane->m_pplaceholder->first_child();

               if (pchildframe.is_set())
               {

                  ::pointer<document>pfilemanagerdata = pchildframe->get_active_document();

                  if (pfilemanagerdata.is_set())
                  {

                     return pfilemanagerdata;

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


   // void document::defer_check_manager_id(const ::scoped_string & scopedstrManagerId)
   // {

   //    auto pcontext = m_papplication;
   //    
   //    auto psession = pcontext->m_psession;
   //    
   //    auto puser = psession->m_puser;

   //    if(puser->m_pathFilemanagerProject.has_character())
   //    {

   //       if (!is_valid_manager_id(m_strManagerId) || is_valid_manager_id(strManagerId))
   //       {

   //          if (is_valid_manager_id(strManagerId))
   //          {

   //             m_strManagerId = strManagerId;

   //          }
   //          else
   //          {

   //             m_strManagerId = create_manager_id(this);

   //          }

   //          //set_data_key_modifier(m_strManagerId);

   ///*          ::pointer<main_frame>pframe = get_impact()->get_typed_parent < main_frame >();

   //          if (pframe.is_set() && !pframe->id().to_string().contains("::frame"))
   //          {

   //             pframe->set_data_key_modifier(m_strManagerId);

   //          }*/

   //       }

   //       ::pointer<document>pfilemanagerdata = get_main_document();

   //       if (pfilemanagerdata.is_set() && pfilemanagerdata.m_p != this && pfilemanagerdata->m_strManagerId != m_strManagerId)
   //       {

   //          pfilemanagerdata->defer_check_manager_id(m_strManagerId);

   //       }

   //    }

   // }


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

      information() << "filemanager::document::on_new_document";

      if (!::user::document::on_new_document())
      {

         return false;

      }


      auto pfilemanagerdata = get_app()->filemanager()->create_filemanager_data();

      if (!open_data(pfilemanagerdata))
      {

         return false;

      }

      return true;

      //defer_check_manager_id();

      //if (!m_bInitialized)
      //{

        // information() << "filemanager::document::on_new_document not yet initialized";

      //*browse_initial_path(e_source_initialize);

      //if (bMakeVisible)
      //{

        // auto ptopic = create_topic(id_pop);

         //update_all_impacts(ptopic);

      //}

      //}

      //return true;

   }



   bool document::on_open_data(::data::data * pdata)
   {

      information() << "filemanager::document::on_open_data";

      if (!::userfs::document::on_open_data(pdata))
      {

         return false;

      }

      //auto path = payloadFile.as_file_path();

      //path.trim();

      //defer_check_manager_id();

      //if (!m_bInitialized)
      //{

        // filemanager_initialize();

      //}

      //string strManagerId;

      //auto papplication = m_papplication;

      //m_path = filemanager_project_entry(strManagerId, path, pcontext);

      //    defer_check_manager_id(strManagerId);
    ////
      //return true;

   //}

      m_pfilemanagerdata = pdata;

      m_pfilemanagerdata->m_pfilemanagerdocument = this;

      if (!m_pfilemanagerdata->m_pitem)
      {

         browse_initial_path(::e_source_initialize);

      }
      else
      {

         browse(m_pfilemanagerdata->m_pitem, ::e_source_initialize);

      }

      auto pfilemanagerdata = filemanager_data();

      if (pfilemanagerdata->m_emode == ::userfs::e_mode_saving)
      {

         auto pfilemanagerdataFilemanager = this;

         {

            auto pextendedtopic = create_topic(id_topic_start);

            pextendedtopic->payload(id_document) = pfilemanagerdataFilemanager;

            pfilemanagerdataFilemanager->update_all_impacts(pextendedtopic);

         }

         {

            auto pextendedtopic = create_topic(id_create_bars);

            pfilemanagerdataFilemanager->update_all_impacts(pextendedtopic);

         }

      }

      return true;

   }


   void document::browse_initial_path(const ::action_context & actioncontext)
   {

      defer_initialize_filemanager();

      filemanager_data()->browse_initial_path(actioncontext);

      //id_update_all_impacts(id_browse);

   }

   //   void document::assert_ok() const
   //   {
   //      ::user::document::assert_ok();
   //   }
   //
   //   void document::dump(dump_context & dumpcontext) const
   //   {
   //      ::user::document::dump(dumpcontext);
   //   }



   void document::OnFileManagerBrowse(const ::action_context & context)
   {

      information() << "filemanager::document::OnFileManagerBrowse";

      //browse(filemanager_data()->m_pitem, context);

      if (context.is_user_source())
      {

         //auto pcontext = m_papplication;
         //
         //auto psession = pcontext->m_psession;
         //
         //auto puser = psession->m_puser;

         auto pfilemanagerdata = filemanager_data();

         //         if (puser->m_pathFilemanagerProject.is_empty())
         {

            pfilemanagerdata->set_last_browse_path(this, pfilemanagerdata->m_pitem->user_path());

         }
         //else
         //{

         //   puser->filemanager_save_project();

         //}

      }


      try
      {

         // auto pcontext = get_context();

         auto pdir = directory();

         //auto & watcher = pdir->watcher();

         //m_pfilewatch = watcher.add_watch(filemanager_data()->m_pitem->final_path(), this, false);

      }
      catch (...)
      {

         m_pfilewatch = nullptr;

      }


   }


   void document::OpenSelectionProperties()
   {

      auto pextendedtopic = create_topic(id_open_selection_properties);

      update_all_impacts(pextendedtopic);

   }


   void document::on_command(::message::command * pcommand)
   {

      auto pfilemanagerdata = filemanager_data();

      if (pfilemanagerdata != nullptr)
      {

         if (pcommand->command_id() == "levelup")
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
      /*if(pcommand->m_atomCommand == filemanager_template()->m_strLevelUp)
      {
      FileManagerOnUpdateLevelUp(pcommand);
      return true;
      }*/
      ::user::document::on_command_probe(pcommand);

   }



   void document::_001OnUpdateNewManager(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewManager(::message::message * pmessage)
   {

      //auto prequest = __create_new <::request>();

      //prequest->finish_initialization();

      //auto pcontext = m_papplication;
      //
      //auto psession = pcontext->m_psession;
      //
      //auto puser = psession->m_puser;

      //puser->add_filemanager("", prequest);

      //pmessage->m_bRet = true;

   }


   void document::_001OnUpdateDelManager(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnDelManager(::message::message * pmessage)
   {

      //::pointer<document>pfilemanagerdata = this;

      //::pointer<impact>pimpact = get_typed_impact<impact>();

      //if (pimpact.is_set())
      //{

      //   ::pointer<tab_impact>ptabimpact = pimpact->get_typed_parent <tab_impact>();

      //   if (ptabimpact.is_set())
      //   {

      //      pfilemanagerdata = ptabimpact->get_document();

      //   }

      //}

      //auto pcontext = m_papplication;
      //
      //auto psession = pcontext->m_psession;
      //
      //auto puser = psession->m_puser;

      //puser->erase_filemanager(pfilemanagerdata.m_p);

      //pmessage->m_bRet = true;

   }


   void document::_001OnUpdateLevelUp(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      if (filemanager_data()->m_pitem.is_null() || filemanager_data()->m_pitem->user_path().is_empty())
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

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnAddLocation(::message::message * pmessage)
   {

      id_update_all_impacts(id_add_location);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateReplaceText(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnReplaceText(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      id_update_all_impacts(id_replace_name);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateNewFolder(::message::message * pmessage)
   {

      ::pointer<::message::command>pcommand(pmessage);

      pcommand->enable(true);

      pmessage->m_bRet = true;

   }


   void document::_001OnNewFolder(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      id_update_all_impacts(id_new_folder);

      pmessage->m_bRet = true;

   }


   void document::_001OnUpdateEditPaste(::message::message * pmessage)
   {
      //      ::pointer<::message::command>pcommand(pmessage);

      //         pcommand->enable(psystem->m_strCopy.is_empty());
      pmessage->m_bRet = true;
   }

   void document::_001OnEditPaste(::message::message * pmessage)
   {
      __UNREFERENCED_PARAMETER(pmessage);
      //file()->paste(pfilemanagerdata->filemanager_item().m_strPath, psystem->m_strCopy);
      //update_all_impacts(nullptr, 123, nullptr);
      //pmessage->m_bRet = true;
   }

   void document::_001OnUpdateFileSaveAs(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      pcommand->enable(true);
   }

   void document::_001OnUpdateFileImport(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      pcommand->enable(true);
   }

   void document::_001OnUpdateFileExport(::message::message * pmessage)
   {
      ::pointer<::message::command>pcommand(pmessage);
      pcommand->enable(true);
   }


   void document::_001OnFileSaveAs(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto emode = filemanager_data()->m_emode;

      if (emode == ::userfs::e_mode_saving || emode == ::userfs::e_mode_export)
      {

         auto ptopic = create_topic(id_topic_ok);

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

      pmessage->m_bRet = true;

   }


   void document::_001OnFileImport(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto emode = filemanager_data()->m_emode;

      if (emode == ::userfs::e_mode_import)
      {

         auto ptopic = create_topic(id_topic_ok);

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

   }


   void document::_001OnFileExport(::message::message * pmessage)
   {

      __UNREFERENCED_PARAMETER(pmessage);

      auto emode = filemanager_data()->m_emode;

      if (emode == ::userfs::e_mode_saving)
      {

         auto ptopic = create_topic(id_topic_ok);

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

   }


   void document::defer_initialize_filemanager()
   {

      if (m_bInitialized)
      {

         return;

      }

      m_bInitialized = true;

      information() << "filemanager::document::filemanager_initialize";

      InitializeFileManager("filemanager");

      CreateImpacts();

      auto ptopic = create_topic(id_create_bars);

      ptopic->payload(id_document) = this;

      update_all_impacts(ptopic);

      // browse(path, ::e_source_database);
      //
      // update_all_impacts(ptopic);
      //
      // if (bMakeVisible)
      // {
      //
      //    ::topic topic(id_pop);
      //
      //    update_all_impacts(&topic);
      //
      // }

   }


   //    void document::filemanager_initialize(bool bMakeVisible, const ::file::path & path)
   //    {
   //
   //       filemanager_initialize();
   //
   //       //InitializeFileManager("filemanager");
   //
   //       //CreateImpacts();
   //
   //       //auto ptopic = create_topic(id_create_bars);
   //
   //       //ptopic->payload(id_document) = this;
   //
   //       browse(path, ::e_source_database);
   //
   // //      update_all_impacts(ptopic);
   //
   //       // if (bMakeVisible)
   //       // {
   //       //
   //       //    auto ptopic = create_topic(id_pop);
   //       //
   //       //    update_all_impacts(ptopic);
   //       //
   //       // }
   //
   //    }


//   void document::browse_initial_path(const ::action_context & action_context)
//   {
//
//      //CreateImpacts();
//
//      //auto ptopic = create_topic(id_create_bars);
//
//      //ptopic->payload(id_document) = this;
//
//      //::file::path pathInitialBrowse;
//
//      //if (bInitialBrowsePath)
//      //{
//
//         //string str;
//
//      auto pfilemanagerdata = filemanager_data();
//
//      auto pathInitialBrowse = pfilemanagerdata->get_last_browse_path(this, pfilemanagerdata->m_pathDefault);
//
//      //browse(path, ::e_source_initialize);
//
////         if (get_file.datastream()->get({true, "last_browse_folder"}, str))
////         {
////
////            if (str == "machinefs://")
////            {
////
////               atom idMachine;
////
////#ifdef LINUX
////               idMachine = "Linux";
////#elif defined(WINDOWS_DESKTOP)
////               idMachine = "WindowsDesktop";
////#elif defined(WINDOWS)
////               idMachine = "Metrowin";
////#elif defined(MACOS)
////               idMachine = "macOS";
////#elif defined(__APPLE__)
////               idMachine = "iOS";
////#endif
////
////               if (papp->datastream()->get({true, "last_browse_folder." + as_string(idMachine)}, str))
////               {
////
////                  browse(str, ::e_source_database);
////
////               }
////               else
////               {
////
////                  browse("", ::e_source_system);
////
////               }
////
////            }
////            else
////            {
////
//               //browse(str, ::e_source_database);
//
////            }
//
//         //}
//         //else if (pfilemanagerdata->m_pathDefault.has_character())
//         //{
//
//         //   browse(pfilemanagerdata->m_pathDefault, ::e_source_initialize);
//
//         //}
//         //else
//         //{
//
//         //   browse("", ::e_source_system);
//
//         //}
//
//      //}
//
//      browse(pathInitialBrowse, action_context);
//
//      //ptopic->id() = ;
//
//      //update_all_impacts(pupdate);
//
//   }


   //void document::OpenFolder(::file::item * pitem, const ::action_context & context)
   //{

   //   browse(pitem, context);

   //}


   void document::CreateImpacts()
   {

      {

         auto ptopic = create_topic(id_initialize);

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

      {

         auto ptopic = create_topic(id_synchronize_locations);

         ptopic->m_actioncontext = ::e_source_sync;

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

   }


   void document::PopImpacts()
   {

      {

         auto ptopic = create_topic(id_create_bars);

         ptopic->payload(id_document) = this;

         update_all_impacts(ptopic);

      }

      {

         ::topic topic(id_pop);

         update_all_impacts(&topic);

      }

   }


   bool document::HandleDefaultFileManagerItemCmdMsg(::message::command * pcommand, ::file::item_array & itema)
   {

      auto pfilemanagerdata = filemanager_data();

      if (pcommand->is_command_probe())
      {

         if (pfilemanagerdata != nullptr)
         {

            if (pfilemanagerdata->m_pfilemanagercallback != nullptr)
            {

               if (pfilemanagerdata->m_pfilemanagercallback->get_file_manager_item_callback(pfilemanagerdata, pcommand->command_id(), itema))
               {

                  pfilemanagerdata->m_pfilemanagercallback->on_file_manager_item_update(pfilemanagerdata, pcommand, itema);

                  return true;

               }

            }

         }

      }
      else if (pcommand->is_command())
      {

         if (pfilemanagerdata != nullptr)
         {

            auto pcallback = pfilemanagerdata->m_pfilemanagercallback;

            if (::is_set(pcallback))
            {

               if (pcallback->get_file_manager_item_callback(pfilemanagerdata, pcommand->command_id(), itema))
               {

                  pcallback->on_file_manager_item_command(pfilemanagerdata, pcommand->command_id(), itema);

                  return true;

               }

            }

         }

      }

      return false;

   }


   operation_document * document::get_operation_doc(bool bSwitch)
   {

      //::filemanager::tab_impact * ptabimpact = psession->m_pimpactsystemMain->get_document(0)->get_typed_impact < ::filemanager::tab_impact >();

      //if (ptabimpact == nullptr)
      //{

      //   return nullptr;

      //}

      //ASSERT(ptabimpact != nullptr);

      //if (ptabimpact != nullptr)
      //{

      //   if (bSwitch)
      //   {

      //      ptabimpact->set_current_tab_by_id("filemanager::operation");

      //   }
      //   else
      //   {

      //      ptabimpact->create_tab_by_id("filemanager::operation");

      //   }

      //   return dynamic_cast < operation_document * > (ptabimpact->get("filemanager::operation")->m_pfilemanagerdata);

      //}

      return nullptr;

   }


   void document::GetActiveImpactSelection(::file::item_array & itema)
   {

      auto ptopic = create_topic(id_get_active_impact_selection);

      update_all_impacts(ptopic);

      itema = *ptopic->cast < ::file::item_array>(id_selected);

   }


   void document::FileManagerSaveAs(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      pfilemanagerdata->m_emode = ::userfs::e_mode_saving;

      {

         auto pextendedtopic = create_topic(id_topic_start);

         pextendedtopic->payload(id_document) = this;

         update_all_impacts(pextendedtopic);

      }

      {

         auto pextendedtopic = create_topic(id_create_bars);

         pextendedtopic->payload(id_document) = this;

         update_all_impacts(pextendedtopic);

      }

   }


   void document::FileManagerImport(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      pfilemanagerdata->m_emode = ::userfs::e_mode_import;

      auto pfilemanagerdataFilemanager = this;

      {

         auto ptopic = create_topic(id_topic_start);

         ptopic->payload(id_document) = pfilemanagerdataFilemanager;

         pfilemanagerdataFilemanager->update_all_impacts(ptopic);

      }

      {

         ::topic topic(id_create_bars);

         pfilemanagerdataFilemanager->update_all_impacts(&topic);

      }

   }


   void document::FileManagerExport(::user::document * pdocument)
   {

      auto pfilemanagerdata = filemanager_data();

      pfilemanagerdata->m_pdocumentTopic = pdocument;

      pfilemanagerdata->m_emode = ::userfs::e_mode_export;

      auto pfilemanagerdataFilemanager = this;

      {

         auto ptopic = create_topic(id_topic_start);

         ptopic->payload(id_document) = pfilemanagerdataFilemanager;

         pfilemanagerdataFilemanager->update_all_impacts(ptopic);

      }

      {

         ::topic topic(id_create_bars);

         pfilemanagerdataFilemanager->update_all_impacts(&topic);

      }

   }



   //void document::on_create(::request * prequest)
   //{

   //   ::user::document::on_create(prequest);

   //   //m_pfilemanagerdata = prequest->cast < ::filemanager::data >("filemanager::data");
   //   //
   //   //auto pcontext = m_papplication;
   //   //
   //   //auto psession = pcontext->m_psession;
   //   //
   //   //auto puser = psession->m_puser;

   //   //if (!m_pfilemanagerdata)
   //   //{

   //   //   m_pfilemanagerdata = puser->filemanager(prequest->id());

   //   //}

   //   //ASSERT(m_pfilemanagerdata.is_set());

   //   //if (m_pfilemanagerdata.is_null())
   //   //{

   //   //   //::pointer<manager_template>ptemplate = pcreate->prop("filemanager::template").cast < manager_template >();

   //   //   //if (ptemplate.is_null())
   //   //   //{

   //   //   //   ptemplate = puser->filemanager().m_ptemplate;

   //   //   //}

   //   //   if (ptemplate.is_null())
   //   //   {

   //   //      m_pfilemanagerdata = __allocate data(this);

   //   //   }
   //   //   else
   //   //   {

   //   //      m_pfilemanagerdata = ptemplate->create_file_manager_data(pcreate);

   //   //   }

   //   //}

   //   //m_pfilemanagerdata->m_pfilemanagerdata = this;

   //}


   void document::on_request(::request * prequest)
   {

      auto papp = get_app();

      papp->request(prequest);

   }


   ::pointer<::filemanager::data>document::create_file_manager_data(::request * prequest)
   {

      ::pointer<::filemanager::data>pfilemanagerdata(__allocate data());

      ::filemanager::callback * pcallback = nullptr;

      if (prequest != nullptr)
      {

         pcallback = prequest->cast < ::filemanager::callback >("department::callback");

      }

      pfilemanagerdata->m_pfilemanagercallback = pcallback != nullptr ? pcallback : this;

      pfilemanagerdata->m_bTransparentBackground = prequest == nullptr ? true : prequest->m_bTransparentBackground;

      pfilemanagerdata->m_bFileSize = true;

      return pfilemanagerdata;

   }


   bool document::has_toolbar()
   {

      auto pfilemanagerdata = filemanager_data();

      return !pfilemanagerdata->m_setToolbar[pfilemanagerdata->m_emode].is_empty();

   }


   ::atom document::get_toolbar_id()
   {

      auto pfilemanagerdata = filemanager_data();

      return pfilemanagerdata->m_setToolbar[pfilemanagerdata->m_emode];

   }


   void document::operator()(::file::action * paction)
   {

      auto eaction = paction->m_eaction;

      if (eaction == ::file::e_action_delete
            || eaction == ::file::e_action_add
            || eaction == ::file::e_action_modify)
      {

         OnFileManagerBrowse(::e_source_sync);

      }

   }


   void document::_001Refresh()
   {

      browse(filemanager_item(), ::e_source_sync);

   }


} // namespace filemanager



