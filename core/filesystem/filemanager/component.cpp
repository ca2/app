#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "core/user/user/shell.h"


CLASS_DECL_CORE ::type __form_document_type();

namespace filemanager
{




   int get_manager_id_byte_len()
   {

      return 16;

   }


   int get_manager_id_len()
   {

      return get_manager_id_byte_len() * 2;

   }


   string create_manager_id(::layered * pobjectContext)
   {

      memory mem;

      mem.set_size(get_manager_id_byte_len());

      Sys(__object(pobjectContext)).math().random_bytes(mem.get_data(), mem.get_size());

      return mem.to_hex().uppered();

   }


   bool is_valid_manager_id(const char* psz)
   {

      ::count c = 0;

      while (*psz != '\0')
      {

         if (*psz >= '0' && *psz <= '9')
         {

         }
         else if (*psz >= 'A' && *psz <= 'F')
         {

         }
         else
         {

            return false;

         }

         psz++;

         c++;

         if (c > get_manager_id_len())
         {

            return false;

         }

      }

      return c == get_manager_id_len();

   }


   bool is_valid_filemanager_project_entry(const char* psz)
   {

      ::count c = 0;

      while (*psz != '\0')
      {

         if (*psz >= '0' && *psz <= '9')
         {

         }
         else if (*psz >= 'A' && *psz <= 'F')
         {

         }
         else
         {

            return false;

         }

         psz++;

         c++;

         if (c >= get_manager_id_len())
         {

            if (*psz == ':')
            {

               return true;

            }
            else
            {

               return false;

            }

         }
      }

      return false;

   }


   ::file::path filemanager_project_entry(string& strManagerId, const char* psz, ::context* pcontext)
   {

      if (is_valid_filemanager_project_entry(psz))
      {

         strManagerId = string(psz, get_manager_id_len());

         return psz + get_manager_id_len() + 1;

      }
      else
      {

         strManagerId = create_manager_id(pcontext);

         return psz;

      }

   }

   component::component()
   {

      m_bRestoring = false;

   }


   ::estatus component::initialize_filemanager_component(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      create_factory <form >();
      create_factory <document >();
      create_factory <child_frame >();
      create_factory <view >();
      create_factory <path_view >();
      create_factory <save_as_view >();
      create_factory <left_view >();
      create_factory <main_view >();
      create_factory <file_list >();
      create_factory <preview >();
      create_factory <main_frame >();
      create_factory <frame >();
      create_factory <tab_view >();
      create_factory <form_child_frame >();
      create_factory <::simple_form_view >();
      create_factory <folder_selection_list_view >();
      create_factory <folder_list_view >();
      create_factory <operation_document >();
      create_factory <operation_child_frame >();
      create_factory <operation_view >();
      create_factory <operation_info_view >();
      create_factory <operation_list_view >();
      create_factory <save_as_edit_view >();
      create_factory <save_as_button>();
      create_factory <fs::simple::view >();
      create_factory <fs::simple::list_view >();

      //__compose_new(this, m_pmap);

      //auto& user = User;

      //auto pshell = user.shell();

      //estatus = pshell->initialize(pobjectContext);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pmulti = __new(::user::multiple_document_template(
                         "filemanager",
                         __form_document_type(),
                         __type(form_child_frame),
                         __type(form)));

      __compose(m_pdocumenttemplateForm, pmulti);

      auto psession = Session;

      psession->add_document_template(pmulti);

      auto psingle = __new(::user::single_document_template(
                          "filemanager",
                          __type(operation_document),
                          __type(operation_child_frame),
                          __type(operation_view)));

      __compose(m_pdocumenttemplateOperation, psingle);

      psession->add_document_template(psingle);

      return true;

   }


   void  component::filemanager_finalize()
   {

      if (m_pdocumenttemplateForm.is_set())
      {

         m_pdocumenttemplateForm->close_all_documents(false);

      }

      if (m_pdocumenttemplateOperation.is_set())
      {

         m_pdocumenttemplateOperation->close_all_documents(false);

      }


   }


   __pointer(data) component::filemanager_create_data(id id)
   {

      if (!is_filemanager(id))
      {

         return nullptr;

      }

      auto pdata = __new(data);

      pdata->initialize_filemanager_data(this);

      pdata->m_id = id;

      filemanager_set_data(id, pdata);

      __pointer(::user::multiple_document_template) pdoctemplate;

      string strTemplateId = id;

      strTemplateId.replace("::", "/");

      if (is_filemanager_group(id, TABBED_GROUP))
      {
         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(frame),       // main SDI frame window
                             __type(tab_view)));

      }
      else if (is_filemanager_group(id, LIST_GROUP))
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(main_frame),
                             __type(file_list)));

      }
      else if (is_filemanager_group(id, FOLDER_SELECTION_LIST_GROUP))
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(main_frame),
                             __type(folder_selection_list_view)));

      }
      else
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(frame),
                             __type(view)));
      }

      auto psession = Session;

      psession->add_document_template(pdoctemplate);

      pdata->m_pdocumenttemplate = pdoctemplate;

      return pdata;

   }


   void component::filemanager_set_data(id id, data * pdata)
   {

      add_reference(pdata);

      __compose(datamap()[id], pdata);

   }


   void document::OnFileManagerOpenFile(data * pdata, ::file::item_array & itema)
   {

      item_action * pitemaction = dynamic_cast <item_action *> (this);

      if (pitemaction != nullptr)
      {

         if (pitemaction->open_file(pdata, itema))
         {

            return;

         }

      }

      request_file(itema[0]->m_filepathUser);

   }


   void document::InitializeFileManager(const char * pszMatter)
   {

      m_pfilemanagerdata->m_pfilelistcallback = this;

      filemanager_initialize(0, pszMatter);

   }


   component::~component()
   {

   }


   void component::filemanager_load_project(const ::file::path & pathFilemanagerProject, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      {

         __keep(m_bRestoring);

         if (pathFilemanagerProject.is_empty() || Context.dir().is(pathFilemanagerProject)
               || pathFilemanagerProject.extension().compare_ci("component") != 0)
         {

            m_pathFilemanagerProject = ::dir::localconfig() / "user.component";

         }
         else
         {

            m_pathFilemanagerProject = pathFilemanagerProject;

         }

         string_array stra;

         {

            ::mutex m(e_create_new, "Local\\ca2-filemanagers");

            sync_lock sl(&m);

            stra.add_lines(Context.file().as_string(m_pathFilemanagerProject), true);

         }

         if (Context.dir().is(pathFilemanagerProject))
         {

            stra.add(create_manager_id(get_context_object()) + ":" + pathFilemanagerProject);

         }

         if (stra.is_empty())
         {

            stra.add(create_manager_id(get_context_object()) + ":");

         }

         string strManagerId;

         ::file::path path;

         for (index i = 0; i < stra.get_size();)
         {

            string str = stra[i];

            strsize iFind = str.find(':');

            if (iFind > 0)
            {

               string strPath = str.Mid(iFind + 1);

               for (index j = i + 1; j < stra.get_size();)
               {

                  string strOther = stra[j];

                  iFind = strOther.find(':');

                  if (iFind > 0)
                  {

                     string strOtherPath = strOther.Mid(iFind + 1);

                     if (strOtherPath.compare_ci(strPath) == 0)
                     {

                        stra.remove_at(j);

                     }
                     else
                     {

                        j++;

                     }

                  }
                  else
                  {

                     j++;

                  }

               }

               i++;

            }
            else
            {

               stra.remove_at(i);

            }

         }

         if (stra.is_empty())
         {

            restore_filemanager("", pcreate, nullptr, pcallback);

         }
         else
         {

            for (auto str : stra)
            {

               restore_filemanager(str, pcreate, nullptr, pcallback);

            }

         }

      }

      filemanager_save_project();

   }


   void component::filemanager_save_project()
   {

      if (m_bRestoring)
      {

         return;

      }

      //string_array stra;

      //document * pdocument;

      //for (index i = 0; i < m_pdocumenttemplateProject->get_document_count(); i++)
      //{

      //   pdocument = m_pdocumenttemplateProject->get_document(i);

      //   if (pdocument.is_null())
      //   {

      //      continue;

      //   }

      //   pdocument->defer_check_manager_id();

      //   pdocument = pdocument->get_main_document();

      //   if (pdocument.is_null())
      //   {

      //      continue;

      //   }

      //   if (pdocument->filemanager_item() == nullptr)
      //   {

      //      continue;

      //   }

      //   stra.add(pdocument->m_strManagerId + ":" + pdocument->filemanager_item()->m_filepathUser);

      //}

      //{

      //   ::mutex m(e_create_new, "Local\\ca2-filemanagers");

      //   sync_lock sl(&m);

      //   Context.file().put_contents(m_pathFilemanagerProject, stra.implode("\r\n"));

      //}

   }


   document * component::find_filemanager(var varFile)
   {

      __pointer(document) pdocument;

      //for (index i = 0; i < m_pdocumenttemplateProject->get_document_count(); i++)
      //{

      //   pdocument = m_pdocumenttemplateProject->get_document(i);

      //   if (pdocument.is_null())
      //   {

      //      continue;

      //   }

      //   pdocument = pdocument->get_main_document();

      //   if (pdocument->m_strManagerId == varFile.get_string().Left(get_manager_id_len()))
      //   {

      //      return pdocument;

      //   }

      //   if (pdocument->filemanager_item()->m_filepathFinal.is_equal_fast(varFile))
      //   {

      //      return pdocument;

      //   }


      //}

      return nullptr;

   }


   document * component::open_filemanager(var varFile, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      //document * pdocument;

      //if (pcreate == nullptr)
      //{

      //   pcreate = __new(::create(Application.handler(), varFile, true));

      //}

      //pcreate->prop("component::template") = this;

      //pcreate->prop("filemanager::data") = pfilemanagerdata;

      //pcreate->prop("component::callback") = pcallback;

      //pcreate->m_pcommandline->m_varFile = varFile;

      //m_pdocumenttemplateProject->m_bQueueDocumentOpening = false;

      //m_pdocumenttemplateProject->do_request(pcreate);

      //pdocument = ::user::__document(pcreate);

      //if (pdocument.is_null())
      //{

      //   return nullptr;

      //}

      //pdocument->Initialize(pcreate == nullptr ? true : pcreate->m_bMakeVisible, false);

      //tab_view * ptabview = pdocument->get_typed_view < tab_view >();

      //if (ptabview != nullptr)
      //{

      //   string strManagerId;

      //   ::file::path pathFolder = filemanager_project_entry(strManagerId, varFile, get_context_application());

      //   ptabview->set_cur_tab_by_id("verifile://" + pathFolder);

      //}

      //return pdocument;

      return nullptr;

   }


   document * component::restore_filemanager(var varFile, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      filemanager()->m_filepath = varFile.get_file_path();

      filemanager()->m_pcreate = pcreate;

      filemanager()->m_pfsdata = pfsdata;

      filemanager()->m_pcallback = pcallback;

      filemanager()->open(nullptr, varFile);

      return filemanager()->m_pdocument;

   }


   document * component::add_filemanager(const ::file::path & pathFolder, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      /*document * pdocument;

      pdocument = open_manager(pathFolder, pcreate, pdata, pfilemanagerdata, pcallback);

      if (pdocument == nullptr)
      {

         return nullptr;

      }

      save_filemanager_project();

      return pdocument;*/
      return nullptr;

   }


   bool component::remove_filemanager(var varFile)
   {

      //document * pdocument = find_manager(varFile);

      //m_pdocumenttemplateProject->remove_document(pdocument);

      //save_filemanager_project();

      //return pdocument.is_set();

      return false;

   }


   bool component::remove_filemanager(document * pdocument)
   {

      //pdocument->close_document();

      ////m_pdocumenttemplateProject->remove_document(pdocument);

      //save_filemanager_project();

      //return pdocument != nullptr;

      return true;

   }


   data * component::filemanager(::id id)
   {

      auto & pdata = datamap()[id];

      if (pdata)
      {

         return pdata;

      }

      if (!pdata)
      {

         __compose(pdata, filemanager_create_data(id));

      }

      return pdata;

   }



//document * component::open_main(::aura::application * pappOnBehalfOf, ::id id, ::create * pcreate, ::fs::data * pfsdata, ::filemanager::__pointer(data) pdata, callback * pcallback)
//{

//   ::file::path pathFolder;

//   if (pcreate == nullptr)
//   {

//      pcreate = __new(::create(pappOnBehalfOf->handler()));

//   }
//   else
//   {

//      pcreate->set_object(pappOnBehalfOf);

//   }

//   if (pcreate->m_pcommandline->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_pcommandline->m_varFile;

//      if (Context.dir().is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.Empty();

//      }

//   }



//   document * pdocument;

//   if (id.i64() < -1 || id.i64() == m_pdocumenttemplateProject->get_document_count())
//   {

//      pcreate->prop("component::template") = this;

//      pcreate->prop("filemanager::data") = pfilemanagerdata;

//      pcreate->prop("component::callback") = pcallback;

//      m_pdocumenttemplateProject->do_request(pcreate);

//      pdocument = ::user::__document(pcreate);

//      if (pdocument != nullptr)
//      {

//         bool bInitialBrowsePath = true;

//         if (pathFolder.m_iDir == 1)
//         {

//            bInitialBrowsePath = false;

//         }

//         pdocument->Initialize(pcreate == nullptr ? true : pcreate->m_bMakeVisible, bInitialBrowsePath);

//      }

//   }
//   else if (id.i64() < m_pdocumenttemplateProject->get_document_count())
//   {

//      pdocument = m_pdocumenttemplateProject->get_document((index)id);

//   }

//   if (pdocument != nullptr)
//   {

//      tab_view * ptabview = pdocument->get_typed_view < tab_view >();

//      if (pathFolder.m_iDir == 1)
//      {

//         if (ptabview != nullptr)
//         {

//            if (ptabview->get_tab_count() <= 0)
//            {

//               ptabview->set_cur_tab_by_id("verifile://" + pathFolder);

//            }
//            else
//            {

//               __pointer(::user::frame_window) pframe = ptabview->get_pane(0)->m_pholder->get_hold();

//               document * pdocument = pframe->GetActiveDocument();

//               pdocument->FileManagerBrowse(pathFolder, action::source_user);

//            }

//         }

//      }
//      else
//      {

//         if (ptabview->get_tab_count() <= 0)
//         {

//            ptabview->set_cur_tab_by_id("0");

//         }

//      }

//   }

//   return pdocument;

//}


//document * component::open(::aura::application * pappOnBehalfOf, id id, ::create * pcreateParam, ::fs::data * pfsdata, ::filemanager::__pointer(data) pdata, callback * pcallback)
//{

//   ::file::path pathFolder;

//   __pointer(::create) pcreate(pcreateParam);

//   if (pcreate.is_null())
//   {

//      pcreate = __new(::create(pappOnBehalfOf->handler()));

//   }
//   else
//   {

//      pcreate->set_object(pappOnBehalfOf);

//   }

//   if (pcreate->m_pcommandline->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_pcommandline->m_varFile;

//      if (Context.dir().is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.Empty();

//      }

//   }



//   document * pdocument;

//   if (id.i64() < -1 || id.i64() == m_pdocumenttemplate->get_document_count())
//   {

//      pcreate->prop("component::template") = this;

//      pcreate->prop("filemanager::data") = pfilemanagerdata;

//      pcreate->prop("component::callback") = pcallback;

//      m_pdocumenttemplate->do_request(pcreate);

//      pdocument = ::user::__document(pcreate);

//      if (pdocument != nullptr)
//      {

//         bool bInitialBrowsePath = true;

//         if (pathFolder.m_iDir == 1)
//         {

//            bInitialBrowsePath = false;

//         }

//         pdocument->Initialize(pcreate == nullptr ? true : pcreate->m_bMakeVisible, bInitialBrowsePath);

//      }

//   }
//   else if (id.i64() < m_pdocumenttemplate->get_document_count())
//   {

//      pdocument = m_pdocumenttemplate->get_document((index)id);

//   }

//   if (pdocument != nullptr)
//   {

//      if (pathFolder.m_iDir == 1)
//      {

//         pdocument->FileManagerBrowse(pathFolder, ::source_user);

//      }

//   }

//   return pdocument;

//}


//document * component::create_new_document(callback * pcallback, ::create * pcreate)
//{

//   document * pdocument = (m_pdocumenttemplate->create_new_document(pcreate));

//   if (pdocument != nullptr)
//   {

//      pdocument->filemanager_data()->m_pcallback = pcallback;
//      pdocument->filemanager_data()->m_pfilemanager = pcallback;
//      pdocument->filemanager_data()->m_pdocument = pdocument;

//      return pdocument;

//   }

//   return nullptr;

//}


//__pointer(data) component::create_data()
//{

//}


//document * component::open_child(bool bMakeVisible, bool bTransparentBackground, __pointer(::user::interaction) pwndParent, ::filemanager::__pointer(data) pdata, callback * pcallback)
//{

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(get_object()));

//   }

//   __pointer(::create) pcreate(e_create_new, pfilemanagerdata);

//   pcreate->m_bMakeVisible = false;
//   pcreate->m_puserinteractionParent = pwndParent;
//   pcreate->prop("filemanager::data") = pfilemanagerdata;

//   if (pfilemanagerdata->m_pcallback == nullptr || pcallback != nullptr)
//   {

//      pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();

//   }

//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

//   m_pdocumenttemplateChild->do_request(pcreate);

//   document * pdocument = ::user::__document(pcreate);

//   if (pdocument == nullptr)
//   {

//      return nullptr;

//   }

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}


//document * component::open_child_list(bool bMakeVisible, bool bTransparentBackground, __pointer(::user::interaction) pwndParent, ::filemanager::__pointer(data) pdata, callback * pcallback)
//{

//   UNREFERENCED_PARAMETER(bMakeVisible);

//   __pointer(::create) pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = pwndParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(get_object()));

//   }

//   pcreate->prop("filemanager::data") = pfilemanagerdata;


//   pfilemanagerdata->m_pfilemanagertemplate = this;
//   pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();
//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;


//   m_pdocumenttemplateChildList->do_request(pcreate);

//   document * pdocument = ::user::__document(pcreate);

//   if (pdocument == nullptr)
//   {

//      return nullptr;

//   }

//   pdocument->filemanager_data()->m_pdocument = pdocument;

//   if (pdocument->filemanager_data()->m_datakey.is_empty())
//   {

//      pdocument->filemanager_data()->m_datakey.m_strDataKey.Format("%s(%d)",
//            psession->component().m_idFileManager.str(),
//            pdocument->filemanager_data()->m_iDocument);

//   }

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}


//document * component::open_folder_selection_list(bool bMakeVisible, bool bTransparentBackground, __pointer(::user::interaction) pwndParent, ::filemanager::__pointer(data) pdata, callback * pcallback)
//{

//   UNREFERENCED_PARAMETER(bMakeVisible);

//   __pointer(::create) pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = pwndParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(get_object()));

//   }

//   pcreate->prop("filemanager::data") = pfilemanagerdata;

//   pfilemanagerdata->m_pfilemanagertemplate = this;
//   pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();
//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

//   m_pdocumenttemplateFolderSelectionList->do_request(pcreate);

//   document * pdocument = ::user::__document(pcreate);

//   if (pdocument == nullptr)
//   {

//      return nullptr;

//   }

//   pdocument->filemanager_data()->m_pdocument = pdocument;

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}



} // namespace filemanager



