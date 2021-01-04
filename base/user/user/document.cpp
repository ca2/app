#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif
#include "aura/message.h"
#include "aura/update.h"
#include "aura/user/wait_cursor.h"


namespace user
{


   document::document()
   {


      m_bAutoDelete = false;
      m_bEmbedded = false;

      m_bCustomOpen = false;

      m_bModified = false;

      m_bNew = true;

      m_bAutoSaveModified = true;

      m_pviewTopic = (::user::impact *) (iptr)0;

      m_pimpactsystem = nullptr;

      m_bEmbedded = FALSE;        // default to file-based document

      defer_create_mutex();

   }


   document::~document()
   {

      // do not call delete_contents here !
#ifdef _DEBUG
      if (is_modified())
      {

         TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: destroying an unsaved document.\n");

      }
#endif

      // there should be no views left!
      disconnect_views();

      ASSERT(m_viewa.is_empty());

      if (m_pimpactsystem != nullptr)
      {

         m_pimpactsystem->remove_document(this);

      }

      ASSERT(m_pimpactsystem == nullptr);     // must be detached

   }


   void document::assert_valid() const
   {
      ::object::assert_valid();

      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {
         __pointer(::user::impact) pview = get_view(index);
         ASSERT_VALID(pview);
      }
   }


   ::user::interaction* document::impact_at(::index iImpact) const
   {

      return m_viewa[iImpact];

   }


   ::count document::impact_count() const
   {

      return m_viewa.get_count();

   }


   ::user::interaction_array document::get_top_level_windows()
   {

      sync_lock sl(mutex());

      ::user::interaction_array uia;

      for (auto & pview : m_viewa)
      {

         uia.add_unique_interaction(pview->GetTopLevel());

      }

      return uia;

   }

   
   ::e_status document::set_finish_composites(::context_object * pcontextobjectFinish)
   {

      bool bStillFinishing = false;

      auto uia = get_top_level_windows();

      for (auto & pui : uia.interactiona())
      {

         auto estatus = pui->finish(pcontextobjectFinish);

         if (estatus == ::error_pending)
         {

            bStillFinishing = true;

         }

      }

      auto estatus = ::user::controller::set_finish_composites(pcontextobjectFinish);

      if (estatus == ::error_pending)
      {

         bStillFinishing = true;

      }

      if (bStillFinishing)
      {

         return ::error_pending;

      }

      return ::success;

   }


   bool document::contains(::user::interaction* pinteraction) const
   {

      for (auto& pimpact : m_viewa)
      {

         if (::is_set(pimpact))
         {

            if (pimpact == pinteraction)
            {

               return true;

            }

            if (pimpact->contains(pinteraction))
            {

               return true;

            }

         }

      }

      return false;

   }


   void document::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

      dumpcontext << "\nm_pDocTemplate = " << (void *)m_pimpactsystem;

      if (dumpcontext.GetDepth() > 0)
      {
         ::count count = get_view_count();
         for (index index = 0; index < count; index++)
         {
            __pointer(::user::impact) pview = get_view(index);
            dumpcontext << "\nwith ::user::impact " << (void *)pview;
         }
      }

      dumpcontext << "m_strTitle = " << m_strTitle;
      dumpcontext << "\nm_path = " << m_path;
      dumpcontext << "\nm_bModified = " << m_bModified;
      dumpcontext << "\n";


   }


   //void document::route_command_message(::user::command * pcommand)
   //{

   //   channel::route_command_message(pcommand);

   //   if (pcommand->m_bRet)
   //      return;

   //   if (m_pimpactsystem != nullptr)
   //   {

   //      m_pimpactsystem->route_command_message(pcommand);

   //      if (pcommand->m_bRet)
   //         return;

   //   }

   //}


   //void document::route_command_message(::user::command* pcommand)
   //{

   //   on_command_message(pcommand);

   //   if (pcommand->m_bRet)
   //   {

   //      return;

   //   }

   //   auto pdocument = get_document();

   //   if (pdocument)
   //   {

   //      pdocument->on_command_message(pcommand);

   //      if (pcommand->m_bRet)
   //      {

   //         return;

   //      }

   //   }

   //   //for (auto& pinteraction : m_interactionaCommandHandlers)
   //   //{

   //   //   if (pinteraction && pinteraction != GetActiveView())
   //   //   {

   //   //      pinteraction->on_command_message(pcommand);

   //   //      if (pcommand->m_bRet)
   //   //      {

   //   //         return;

   //   //      }

   //   //   }

   //   //}

   //   // then pump through parent
   //   __pointer(::user::interaction) puiParent = GetParent();
   //   while (puiParent)
   //   {

   //      puiParent->on_command_message(pcommand);

   //      if (pcommand->m_bRet)
   //      {

   //         return;

   //      }

   //   }

   //   // last but not least, pump through cast
   //   ::aura::application* papp = get_context_application();

   //   if (papp != nullptr)
   //   {

   //      papp->on_command_message(pcommand);

   //      if (pcommand->m_bRet)
   //      {

   //         return;

   //      }

   //   }

   //   __pointer(channel) ptarget = psession->get_keyboard_focus();

   //   if (ptarget != nullptr && ptarget != this && ptarget != GetActiveView()
   //      && !m_interactionaCommandHandlers.contains(ptarget))
   //   {

   //      ptarget->on_command_message(pcommand);

   //      if (pcommand->m_bRet)
   //      {

   //         return;

   //      }

   //   }

   //}


   bool document::on_create_bars(::user::frame_window * pframe)
   {

        return true;

   }


   void document::on_create(::create * pcreate)
   {

      run_property("on_create");

      call_routine(CREATE_ROUTINE);

      //::database::client::initialize_data_client(Application.dataserver());

   }


   ::id document::get_topic_view_id()
   {

      auto psubject = subject(id_get_topic_view_id);

      update_all_views(psubject);

      return psubject->value(id_id);

   }


   bool document::set_topic_view_by_id(::id id)
   {

      auto psubject = subject(id_get_topic_view_id);

      psubject->value(id_id) = id;

      update_all_views(psubject);

      return psubject->m_bRet;

   }


   void document::update_title()
   {

      string str = Application.m_strAppName;

      str += " : ";

      if (get_file_path().has_char())
      {

         str += get_file_path();

      }

      auto pview = get_view(0);

      if (pview)
      {

         __pointer(::user::frame_window) pframe = pview->GetParentFrame();

         while (pframe.is_set())
         {

            pframe->set_window_text(str);

            pframe = pframe->GetParentFrame();

         }

      }

   }


   void document::on_final_release()
   {

      on_close_document();  // may 'delete this'

   }


   void document::disconnect_views()
   {

      sync_lock sl(mutex());

      for (index index = 0; index < m_viewa.get_count(); index++)
      {

         __pointer(::user::impact) pview = m_viewa[index];

         ASSERT_VALID(pview);

         ASSERT_KINDOF(::user::impact, pview);

         pview->__release(pview->m_pdocument);

      }

      m_viewa.remove_all();

   }


   void document::set_title(const char * pszTitle)
   {

      m_strTitle = pszTitle;

      update_frame_counts();        // will cause name machine in views

   }


   void document::delete_contents()
   {

      if (!m_bCustomOpen)
      {

         m_path.Empty();

         m_datamap.remove_all();

      }

   }


   __pointer(::user::impact) document::get_view(index index) const
   {

      sync_lock sl(((document *)this)->mutex());

      if (index < 0 || index >= m_viewa.get_count())
      {

         return nullptr;

      }

      __pointer(::user::impact) pview = m_viewa[index];

      ASSERT_KINDOF(::user::impact, pview);

      return pview;

   }



   //void document::send_update(__pointer(::user::impact) pSender, LPARAM lHint, ::object * pHint)
   //// walk through all views
   //{
   //   ASSERT(pSender == nullptr || !m_viewa.is_empty());
   //   // must have views if sent by one of them

   //   update * ptask;
   //   ::count count = get_view_count();
   //   for (index index = 0; index < count; index++)
   //   {
   //      __pointer(::user::impact) pview = get_view(index);

   //      ptask = new update;
   //      ptask->m_pSender = pSender;
   //      ptask->m_lHint = lHint;
   //      ptask->m_pHint = pHint;
   //      if (pview != pSender)
   //         pview->send_message(WM_VIEW, 0, (LPARAM)ptask);
   //   }
   //}


   bool document::is_new_document()
   {

      return m_bNew;

   }


   __pointer(::user::impact) document::get_typed_view(::type info, index indexFind)
   {

      single_lock sl(mutex(), true);

      ::count countView = get_view_count();

      ::count countFind = 0;

      __pointer(::user::impact) pview;

      for (index index = 0; index < countView; index++)
      {

         pview = get_view(index);

         if (info == ::str::demangle(pview->type_name()))
         {

            if (indexFind == countFind)
            {

               return pview;

            }
            else
            {

               countFind++;

            }

         }

      }

      return nullptr;

   }


   __pointer(::user::impact) document::get_typed_view_with_id(::type info, id id)
   {
      single_lock sl(mutex(), true);
      ::count countView = get_view_count();
      ::count countFind = 0;
      __pointer(::user::impact) pview;
      for (index index = 0; index < countView; index++)
      {
         pview = get_view(index);
         if (info == ::str::demangle(pview->type_name()))
         {
            if (id == pview->m_id)
               return pview;
            else
               countFind++;
         }
      }

      return nullptr;

   }


   void document::show_all_frames(::u32 nCmdShow)
   {
      ::count count = get_view_count();
      for (index index = 0; index < count; index++)
      {

         __pointer(::user::impact) pview = get_view(index);

         enum_activation eactivation = e_activation_default;

         auto edisplay = windows_show_window_to_edisplay(nCmdShow, eactivation);

         pview->GetParentFrame()->display(edisplay, eactivation);

      }
   }


   // document
   const string & document::get_title() const
   {

      ASSERT(::is_set(this));

      return m_strTitle;

   }


   string document::get_save_file_extension()
   {

      return m_strSaveFileExtension;

   }


   const ::file::path & document::get_file_path() const
   {

      ASSERT(::is_set(this));

      return m_path;

   }


   impact_system * document::get_document_template() const
   {

      ASSERT(::is_set(this));
      return m_pimpactsystem;

   }


   bool document::is_modified()
   {

      ASSERT(::is_set(this));

      return m_bModified || has(e_object_property_set_modified);

   }


   void document::set_modified_flag(bool bModified)
   {

      ASSERT(::is_set(this));

      m_bModified = bModified;

   }


   void document::set_new(bool bNew)
   {
      ASSERT(::is_set(this));
      m_bNew = bNew;
   }

   /////////////////////////////////////////////////////////////////////////////
   // File/Path commands

   void document::set_path_name(payload varFile, bool bAddToMRU)
   {
      UNREFERENCED_PARAMETER(bAddToMRU);
      string strPathName;
      if (varFile.get_type() == ::e_type_propset && varFile.propset()["url"].get_string().has_char())
      {
         strPathName = varFile.propset()["url"];
      }
      else if (varFile.cast < ::file::file>() != nullptr)
      {
         strPathName = System.datetime().international().get_gmt_date_time() + "." + get_document_template()->find_string("default_extension");
      }
      else
      {
         strPathName = varFile;
      }
      // store the path fully qualified
      //char szFullPath[_MAX_PATH];
      //if ( lstrlen(pszPathName) >= _MAX_PATH )

      //{
      //   ASSERT(FALSE);
      // aura API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
      //   ::aura::ThrowFileException(::file::exception::badPath);
      //}

      //   if( ::aura::FullPath(szFullPath, pszPathName) == FALSE )

      //   {
      //      ASSERT(FALSE);
      // aura API requires paths with length < _MAX_PATH
      // No other way to handle the error from a void function
      //      ::aura::ThrowFileException(::file::exception::badPath);
      //   }

      // store the path fully qualified
      ::file::path strFullPath;
      //      System.file_system().FullPath(strFullPath, strPathName);
      strFullPath = strPathName;
      m_path = Context.defer_process_path(m_path);
      //m_filepathEx = strFullPath;
      //!m_strPathName.is_empty());       // must be set to something
      m_bEmbedded = FALSE;

      // set the document_interface title based on path name
      set_title(strFullPath.title());

      //string strPathName;
      //::str::international::Utf8ToAcp(strPathName, m_wstrPathName);
      // add it to the file MRU list
      /* xxx if (bAddToMRU)
      guserbase::get(get_object())->AddToRecentFileList(pszPathName);*/


      /*   ASSERT_VALID(this);
      m_bNew = false;


      m_strPathName = pszPathName;

      ASSERT(!m_strPathName.is_empty());       // must be set to something
      m_bEmbedded = FALSE;
      ASSERT_VALID(this);

      // set the document_interface title based on path name
      string strTitle = Context.file().title_(m_strPathName);
      set_title(strTitle);


      ASSERT_VALID(this);

      m_bNew = false;*/
   }

   ::count document::get_view_count() const
   {
      return m_viewa.get_count();
   }

   /////////////////////////////////////////////////////////////////////////////
   // Closing documents or views

   void document::on_changed_view_list()
   {

      // if no more views on the document_interface, delete ourself
      // not called if directly closing the document_interface or terminating the cast
      if (m_viewa.is_empty() && m_bAutoDelete)
      {

         on_close_document();

         return;

      }

      // update the frame counts as needed
      update_frame_counts();

   }


   bool document::new_document()
   {

      delete_contents();

      m_bNew = true;

      m_bModified = false;

      m_path.Empty();

      m_strTitle.Empty();

      if (!on_new_document())
      {

         m_bNew = false;

         m_bModified = false;

         m_path.Empty();

         m_strTitle.Empty();

      }

      return true;

   }


   bool document::open_document(const payload & varFile)
   {

      delete_contents();

      if (!on_open_document(varFile))
      {

         m_bNew = false;

         m_bModified = false;

         m_path.Empty();

         m_strTitle.Empty();

      }
      else
      {

         m_bNew = false;

         m_bModified = false;

         m_path = varFile;

         m_strTitle = varFile.get_file_path().name();

      }

      return true;

   }


   bool document::defer_save_document()
   {

      if (!is_modified())
      {

         return false;

      }

      fork([this]()
         {

            save_document();

         });

      return true;

   }


   bool document::save_document()
   {

      if (m_path.is_empty())
      {

         return false;

      }

      if (!on_save_document(m_path))
      {

         return false;

      }

      m_bNew = false;

      m_bModified = false;

      return true;

   }


   bool document::on_new_document()
   {

      return true;

   }


   bool document::open_document(::create * pcreate)
   {

      __keep(m_pcreate, pcreate);

      if (!open_document(pcreate->m_pcommandline->m_varFile))
      {

         return false;

      }

      return true;

   }


   bool document::on_open_document(const payload & varFile)
   {

      auto preader = Context.file().get_reader(varFile, ::file::e_open_read | ::file::e_open_share_deny_write | ::file::e_open_binary);

      if (!preader)
      {

         report_load_exception(varFile, preader, "__IDP_FAILED_TO_OPEN_DOC");

         return false;

      }

      try
      {

         if (!on_open_document(preader.m_p))
         {

            return false;

         }

         preader->close();

      }
      catch (const ::exception_pointer & pexception)
      {

         report_load_exception(varFile, pexception, "__IDP_FAILED_TO_OPEN_DOC");

      }

      return true;

   }


   bool document::on_open_document(::file::file * pfile)
   {

      ::binary_stream reader(pfile);

      read(reader);

      return true;

   }


   bool document::on_save_document(const payload & varFile)
   {

      auto pwriter = Context.file().get_writer(varFile, ::file::e_open_defer_create_directory | ::file::e_open_create | ::file::e_open_read | ::file::e_open_write | ::file::e_open_share_exclusive);

      if(!pwriter)
      {

         ::file::path path = varFile.get_file_path();

         TRACE("Failed to save document : file path : %s", path.c_str());

         //report_save_exception(varFile, pwriter, "__IDP_INVALID_FILENAME");

         return false;

      }

      try
      {

         if (!on_save_document(pwriter.m_p))
         {

            return false;

         }

         pwriter->close();

      }
      catch (const ::exception_pointer & pexception)
      {

         report_save_exception(varFile, pexception, "__IDP_FAILED_TO_OPEN_DOC");

      }

      return true;

   }



   bool document::on_save_document(::file::file * pfile)
   {

      ::binary_stream writer(pfile);

      write(writer);

      return true;

   }

   void document::on_close_document()
   {

      pre_close_document();

      __pointer(::object) pthis = this;

      __pointer_array(::user::frame_window) frameptra;

      {

         sync_lock sl(mutex());

         for (auto & pview : m_viewa.ptra())
         {

            __pointer(::user::frame_window) pframe = pview->GetParentFrame();

            if (pframe.is_set())
            {

               pframe->value("hold_impact_system") = m_pimpactsystem;

               frameptra.add_unique(pframe);

            }

         }

      }

      for (auto & pframe : frameptra.ptra())
      {

         pre_close_frame(pframe);

         pframe->finish(get_context());

      }

      {

         sync_lock sl(mutex());

         m_viewa.remove_all();

      }

      delete_contents();

   }


   void document::pre_close_document()
   {

      __pointer(::object) pthis = this;

      sync_lock sl(mutex());

      auto viewptra = m_viewa;

      sl.unlock();

      for(auto & pview : viewptra.ptra())
      {

         __pointer(::user::frame_window) pframe = pview->GetParentFrame();

         if (pframe.is_set())
         {

            pframe->display(e_display_none);

            pframe->child_post_quit("prodevian");

         }

      }

      for(auto & pview : viewptra.ptra())
      {

         __pointer(::user::frame_window) pframe = pview->GetParentFrame();

         if (pframe.is_set())
         {

            pframe->display(e_display_none);

            pframe->child_post_quit_and_wait("prodevian", seconds(5));

         }

      }

      update_all_views(nullptr, PRE_CLOSE_DOCUMENT_UPDATE);

   }


   void document::close_document()
   {

      try
      {

         on_close_document();

         if (m_pimpactsystem != nullptr)
         {

            m_pimpactsystem->remove_document(this);

         }

      }
      catch(...)
      {

      }

      run_property("on_destroy");

   }


   void document::report_load_exception(const payload & varFile, file_result presult, const char * pszDefault)
   {

      report_save_load_exception(varFile, presult, false, pszDefault);

   }


   void document::report_save_exception(const payload & varFile, file_result presult, const char * pszDefault)
   {

      report_save_load_exception(varFile, presult, true, pszDefault);

   }


   void document::report_save_load_exception(const payload & varFile, file_result presult, bool bSave, const char * pszDefault)
   {

      try
      {

         UNREFERENCED_PARAMETER(bSave);

         string strPrompt(pszDefault);

         //string prompt;

         //if (e != nullptr)
         //{
         //   if (base_class < user_exception >::bases(e))
         //      return; // already reported

         //   /*if (base_class < CArchiveException >::bases(e))
         //   {
         //   switch (((CArchiveException*)e)->m_cause)
         //   {
         //   case CArchiveException::badSchema:
         //   case CArchiveException::badClass:
         //   case CArchiveException::badIndex:
         //   case CArchiveException::endOfFile:
         //   nIDP = __IDP_FAILED_INVALID_FORMAT;
         //   break;
         //   default:
         //   break;
         //   }
         //   }
         //   else*/ if (base_class < ::file::exception >::bases(e))
         //   {
         //      ::file::exception * pfe = dynamic_cast <::file::exception *> (e);
         //      // ::exception::throw_not_implemented();
         //      TRACE(trace_category_appmsg, e_trace_level_warning, "Reporting file I/O exception on Save/Load with lOsError = $%lX.\n",
         //         pfe->m_lOsError);

         //      if (pfe->m_strFileName.is_empty())
         //      {

         //         pfe->m_strFileName = pszPathName;


         //      }

         //      if (!pfe->get_error_message(prompt))
         //      {
         //         /*               switch (((::aura::file_exception_pointer*)e)->m_cause)
         //         {
         //         case ::file::exception::fileNotFound:
         //         case ::file::exception::badPath:
         //         nIDP = __IDP_FAILED_INVALID_PATH;
         //         break;
         //         case ::file::exception::diskFull:
         //         nIDP = __IDP_FAILED_DISK_FULL;
         //         break;
         //         case ::file::exception::accessDenied:
         //         nIDP = bSaving ? __IDP_FAILED_ACCESS_WRITE :
         //         __IDP_FAILED_ACCESS_READ;
         //         break;

         //         case ::file::exception::badSeek:
         //         case ::file::exception::matter:
         //         case ::file::exception::tooManyOpenFiles:
         //         case ::file::exception::invalidFile:
         //         case ::file::exception::hardIO:
         //         case ::file::exception::directoryFull:
         //         break;

         //         default:
         //         break;*/
         //         //     }
         //      }
         //      prompt.release_string_buffer();
         //   }
         //}

         //if (prompt.is_empty())
         //{
         //   string strTitle = ::file::path(pszPathName).title();

         //   //::exception::throw_not_implemented();
         //   /*
         //   ::aura::FormatString1(prompt, nIDP, strTitle);*/
         //}

         //System.message_box(prompt, e_message_box_icon_exclamation, nHelpContext);
         message_box(strPrompt, nullptr, e_message_box_icon_exclamation);

      }
      catch (...)
      {

      }

   }


   bool document::can_close_frame(::user::frame_window * pframeParam)
   // permission to close all views using this frame
   //  (at least one of our views must be in this frame)
   {

      sync_lock sl(mutex());

      ASSERT_VALID(pframeParam);

      //UNUSED(pframeParam);   // unused in release builds

      ::count count = get_view_count();

      for (index index = 0; index < count; index++)
      {

         __pointer(::user::impact) pview = get_view(index);

         ASSERT_VALID(pview);

         __pointer(::user::frame_window) pframe = pview->GetParentFrame();

         // assume frameless views are ok to close
         if (pframe != nullptr)
         {

            // assumes 1 document_interface per frame
            ASSERT_VALID(pframe);

            if (pframe->m_nWindow > 0)
               return true;        // more than one frame refering to us

         }

      }

      sl.unlock();

      // otherwise only one frame that we know about
      return save_modified();

   }


   bool document::save_modified()
   {

      if (!is_modified())
      {

         return true;        // ok to continue

      }

      // get name/title of document_interface
      string strName;

      if (m_path.is_empty())
      {

         strName = m_strTitle;

         if (strName.is_empty())
         {

            strName = Application.load_string("Untitled");

         }

      }

      string prompt;

      prompt = _("MessageBoxChangedFileAskToSave");

      prompt.replace("%1", strName);

      if (m_bAutoSaveModified)
      {

         // If so, either Save or Update, as appropriate
         if (!do_file_save())
         {

            return false;       // don't continue

         }
      }
      else
      {


         INFO("Unsaved Document");

         return false;       // don't continue


      }

      //switch (Application.message_box(nullptr, prompt, MB_YESNOCANCEL))
      //{
      //case e_dialog_result_cancel:
      //{

      //   return false;       // don't continue

      //}

      //case e_dialog_result_yes:
      //{



      //   break;

      //}

      //case e_dialog_result_no:
      //{

      //   // If not saving changes, revert the document_interface
      //   break;

      //}

      //default:
      //{

      //   ASSERT(FALSE);
      //   break;

      //}

      //}
      return true;    // keep going

   }


   void document::pre_close_frame(::user::frame_window * pframe)
   {

      // default does nothing

   }


   bool document::on_filemanager_open(::filemanager::document * pmanager, payload varFile)
   {

      return on_open_document(varFile);

   }


   bool document::on_filemanager_save(::filemanager::document * pmanager, payload varFile, bool bReplace)
   {

      return do_save(varFile, bReplace);

   }


   bool document::do_save(payload varFile, bool bReplace)
   // Save the document_interface data to a file
   // pszPathName = path name where to save document_interface file

   // if pszPathName is nullptr then the ::account::user will be prompted (SaveAs)

   // note: pszPathName can be different than 'm_strPathName'

   // if 'bReplace' is TRUE will machine file name if successful (SaveAs)
   // if 'bReplace' is FALSE will not machine path name (SaveCopyAs)
   {

      payload newName = varFile;

      if (newName.is_empty())
      {

         __pointer(impact_system) ptemplate = get_document_template();

         ASSERT(ptemplate != nullptr);

         newName = m_path;

         if (bReplace && newName.is_empty())
         {

            newName = m_strTitle;
            // check for dubious filename
            strsize iBad = newName.get_string().FindOneOf(":/\\");
            if (iBad != -1)
               newName = newName.get_string().Left(iBad);

            // append the default suffix if there is one
            string strExt;
            if (ptemplate->GetDocString(strExt, impact_system::filterExt) &&
                  !strExt.is_empty())
            {
               ASSERT(strExt[0] == '.');
               strsize iStart = 0;
               newName += strExt.Tokenize(";", iStart);
            }
         }

         //if (!Application.do_prompt_file_name(newName, __str("Save ") + newName, 0 /*OFN_HIDEREADONLY | OFN_PATHMUSTEXIST */, FALSE, ptemplate, this))
           // return FALSE;       // don't even attempt to save

      }

      wait_cursor wait(get_context_object());

      if (!on_save_document(newName))
      {
         if (varFile.is_empty())
         {

            // be sure to delete the file

            try
            {

               Context.file().del(newName);

            }
            catch (const ::exception_pointer & pe)
            {

               TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: failed to delete file after failed SaveAs.\n");

               ::exception_pointer esp(pe);

            }

         }
         return FALSE;
      }

      // reset the title and machine the document_interface name
      if (bReplace)
         set_path_name(newName);

      return TRUE;        // success
   }


   bool document::do_file_save()
   {

      if (is_new_document() || Context.file().is_read_only(m_path))
      {

         // we do not have read-write access or the file does not (now) exist

         if (!do_save(payload(::e_type_empty)))
         {

            TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: File save with new name failed.\n");

            return FALSE;

         }

      }
      else
      {

         if (!do_save(m_path))
         {

            TRACE(trace_category_appmsg, e_trace_level_warning, "Warning: File save failed.\n");

            return false;

         }

      }

      return true;

   }


   void document::update_frame_counts()
   // assumes 1 doc per frame
   {

      // walk all frames of views (mark and sweep approach)
      ::count count = get_view_count();

      index index;

      for (index = 0; index < count; index++)
      {

         ::user::impact * pview = get_view(index);

         ASSERT_VALID(pview);

         if (pview->is_window_visible())
         {

            __pointer(::user::frame_window) pframe = pview->GetParentFrame();

            if (pframe != nullptr)
            {

               pframe->m_nWindow = -1;

            }

         }

      }

      // now do it again counting the unique ones
      i32 nFrames = 0;

      count = get_view_count();

      for (index = 0; index < count; index++)
      {

         ::user::impact * pview = get_view(index);

         ASSERT_VALID(pview);

         if (pview->is_window_visible())
         {

            __pointer(::user::frame_window) pframe = pview->GetParentFrame();

            if (pframe != nullptr && pframe->m_nWindow == -1)
            {

               ASSERT_VALID(pframe);

               // not yet counted (give it a 1 based number)
               pframe->m_nWindow = ++nFrames;

            }

         }

      }

      // lastly walk the frames and update titles (assume same order)
      // go through frames updating the appropriate one
      i32 iFrame = 1;

      count = get_view_count();

      for (index = 0; index < count; index++)
      {

         ::user::impact * pview = get_view(index);

         ASSERT_VALID(pview);

         if (pview->is_window_visible())   // Do not ::count invisible windows.
         {

            __pointer(::user::frame_window) pframe = pview->GetParentFrame();

            if (pframe != nullptr && pframe->m_nWindow == iFrame)
            {

               ASSERT_VALID(pframe);

               if (nFrames == 1)
                  pframe->m_nWindow = 0;      // the only one of its kind

               pframe->post_simple_command(simple_command_update_frame_title, (LPARAM) TRUE);

               iFrame++;

            }

         }

      }

   }


#ifdef WINDOWS_DESKTOP


   HMENU document::GetDefaultMenu()
   {

      return nullptr;    // just use original default

   }


   HACCEL document::GetDefaultAccelerator()
   {

      return nullptr;    // just use original default

   }


#endif


   void document::on_idle()
   {
      // default does nothing
   }

   /////////////////////////////////////////////////////////////////////////////
   // ::user::impact operations


   ::e_status document::add_view(::user::impact * pview)
   {

      single_lock sl(mutex(), true);

      ASSERT_VALID(pview);

      if (pview->m_pdocument)
      {

         return ::error_invalid_argument;// must not be already attached

      }

      if (!m_viewa.add_unique(pview))
      {

         return ::error_already_added;// must not be already added

      }

      pview->initialize_view(this);

      on_changed_view_list();    // must be the last thing done to the document

      return ::success;

   }


   ::e_status document::remove_view(::user::impact * pview)
   {

      sync_lock sl(mutex());

      ASSERT_VALID(pview);

      if(pview->get_document() != this)
      {

         return ::error_invalid_argument; // must be attached to us

      }

      if (m_viewa.remove(pview) < 0)
      {

         return ::error_not_found;

      }

      pview->__release(pview->m_pdocument);

      on_changed_view_list();    // must be the last thing done to the document

      return ::success;

   }


   void document::on_file_save()
   {

      do_file_save();

   }


   void document::on_request(::create * pcreate)
   {

      if(!on_open_document(pcreate->m_pcommandline->m_varFile))
         return;

      pcreate->m_pcommandline->m_varQuery["document"] = this;

   }


   //void document::on_before_navigate(::form_data * pdata,payload & varFile,u32 nFlags,const char * pszTargetFrameName,byte_array& baPostedData,const char * pszHeaders,bool* pbCancel)
   //{

   //   UNREFERENCED_PARAMETER(pdata);
   //   string strUrl(varFile);
   //   if(::str::begins_eat(strUrl,"ext://"))
   //   {
   //      Application.open_link(strUrl,"", pszTargetFrameName);

   //      /*         ::aura::shell_launcher launcher(nullptr, "open", strUrl, "", "", SW_SHOWNORMAL);
   //      launcher.execute();*/

   //      *pbCancel = true;
   //      return;
   //   }
   //   if(::str::begins_eat(strUrl,"hist://"))
   //   {
   //      System.hist_hist(strUrl);
   //      *pbCancel = true;
   //      return;
   //   }

   //}


   void document::form_document_set_property_set(const property_set & set)
   {
      UNREFERENCED_PARAMETER(set);
   }


   property_set * document::form_document_get_property_set()
   {

      return nullptr;

   }

   property_set & document::form_document_property_set()
   {

      return *form_document_get_property_set();

   }









   __pointer(::user::document) __document(::create * pcreate)
   {

      if (pcreate == nullptr)
      {

         return nullptr;

      }

      if (pcreate->m_pcommandline.is_null())
      {

         return nullptr;

      }


      return pcreate->m_pcommandline->m_varQuery["document"].cast < ::user::document >();


   }


   void document::id_update_all_views(const ::id & id)
   {

      update_all_views(nullptr, id);

   }


   void document::update_all_views(::promise::subject * psubject)
   {

      ASSERT(psubject->m_psender == nullptr || !m_viewa.is_empty());

      for (auto & pview : m_viewa.ptra())
      {

         ASSERT_VALID(pview);

         if (pview != psubject->m_psender)
         {

            pview->on_subject(psubject, nullptr);

            if(psubject->m_bRet)
            {

               break;

            }

         }

      }

   }


   void document::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      update_all_views(psubject);

   }


   void document::update_all_views(impact * pimpact, const ::id & id)
   {

      auto psubject = subject(id);

      psubject->m_psender = pimpact;

      update_all_views(psubject);

   }


   void document::call_initial_update()
   {

      id_update_all_views(INITIAL_UPDATE);

   }


} // namespace base






