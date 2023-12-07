#include "framework.h"
//#include "_filemanager.h"
#include "aura/user/shell.h"


CLASS_DECL_AURA ::type __form_document_type();

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


   string create_manager_id(::object* pparticle)
   {

      memory mem;

      mem.set_size(get_manager_id_byte_len());

      Sys(pparticle).math().random_bytes(mem.get_data(), mem.get_size());

      return mem.to_hex().uppered();

   }


   bool is_valid_manager_id(const ::string & psz)
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


   bool is_valid_filemanager_project_entry(const ::string & psz)
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


   ::file::path filemanager_project_entry(string& strManagerId, const ::string & psz, ::context* pcontext)
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


   void component::initialize_filemanager_component(::particle * pparticle)
   {

      auto estatus = ::object::initialize(pparticle);

      if (!estatus)
      {

         return estatus;

      }

      return ::error_not_implemented;

      //throw ::exception(todo("core"));
      ////add_factory_item <form >();
      ////add_factory_item <document >();
      ////add_factory_item <child_frame >();
      ////add_factory_item <impact >();
      ////add_factory_item <path_impact >();
      ////add_factory_item <save_as_impact >();
      ////add_factory_item <left_impact >();
      ////add_factory_item <main_impact >();
      ////add_factory_item <file_list >();
      ////add_factory_item <thumbnail >();
      ////add_factory_item <main_frame >();
      ////add_factory_item <frame >();
      ////add_factory_item <tab_impact >();
      ////add_factory_item <form_child_frame >();
      ////add_factory_item <::simple_form_impact >();
      ////add_factory_item <folder_selection_list_impact >();
      ////add_factory_item <folder_list_impact >();
      ////add_factory_item <operation_document >();
      ////add_factory_item <operation_child_frame >();
      ////add_factory_item <operation_impact >();
      ////add_factory_item <operation_info_impact >();
      ////add_factory_item <operation_list_impact >();
      ////add_factory_item <save_as_edit_impact >();
      ////add_factory_item <save_as_button>();
      ////add_factory_item <fs::simple::impact >();
      ////add_factory_item <fs::simple::list_impact >();

      ////__construct_new(this, m_pmap);

      //throw ::exception(todo("core"));
      ////psession->userex()->shell()->initialize(&Session);

      ////auto pmulti = __allocate < ::user::multiple_document_template >(
      ////                   "filemanager",
      ////                   __form_document_type(),
      ////                   ::type < form_child_frame >(),
      ////                   ::type < form >()));

      ////__construct(m_pimpactsystemForm, pmulti);

      ////psession->add_document_template(pmulti);

      ////auto psingle = __allocate < ::user::single_document_template >(
      ////                    "filemanager",
      ////                    ::type < operation_document >(),
      ////                    ::type < operation_child_frame >(),
      ////                    ::type < operation_impact >()));
      ////
      ////__construct(m_pimpactsystemOperation, psingle);

      ////psession->add_document_template(psingle);

      //return true;

   }


   void  component::filemanager_finalize()
   {

      if (m_pimpactsystemForm.is_set())
      {

         m_pimpactsystemForm->close_all_documents(false);

      }

      if (m_pimpactsystemOperation.is_set())
      {

         m_pimpactsystemOperation->close_all_documents(false);

      }


   }


   //::pointer<data>component::filemanager_create_data(atom atom)
   //{

   //   if (!is_filemanager(atom))
   //   {

   //      return nullptr;

   //   }

   //   throw ::exception(todo("core"));
   //   //auto pdata = __allocate< data >();

   //   //pdata->initialize_filemanager_data(this);

   //   //pdata->m_atom = atom;

   //   //filemanager_set_data(atom, pdata);

   //   //::pointer<::user::multiple_document_template>pdoctemplate;

   //   //string strTemplateId = atom;

   //   //strTemplateId.replace("::", "/");

   //   //if (is_filemanager_group(atom, TABBED_GROUP))
   //   //{
   //   //   pdoctemplate = __allocate < ::user::multiple_document_template >(
   //   //                       strTemplateId,
   //   //                       ::type < document >(),
   //   //                       ::type < frame >(),       // main SDI frame window
   //   //                       ::type < tab_impact >()));

   //   //}
   //   //else if (is_filemanager_group(atom, LIST_GROUP))
   //   //{

   //   //   pdoctemplate = __allocate < ::user::multiple_document_template >(
   //   //                       strTemplateId,
   //   //                       ::type < document >(),
   //   //                       ::type < main_frame >(),
   //   //                       ::type < file_list >()));

   //   //}
   //   //else if (is_filemanager_group(atom, FOLDER_SELECTION_LIST_GROUP))
   //   //{

   //   //   pdoctemplate = __allocate < ::user::multiple_document_template >(
   //   //                       strTemplateId,
   //   //                       ::type < document >(),
   //   //                       ::type < main_frame >(),
   //   //                       ::type < folder_selection_list_impact >()));

   //   //}
   //   //else
   //   //{

   //   //   pdoctemplate = __allocate < ::user::multiple_document_template >(
   //   //                       strTemplateId,
   //   //                       ::type < document >(),
   //   //                       ::type < frame >(),
   //   //                       ::type < impact >()));
   //   //}

   //   //papp->add_document_template(pdoctemplate);

   //   //pdata->m_pimpactsystem = pdoctemplate;

   //   //return pdata;
   //   return nullptr;

   //}


   void component::filemanager_set_data(atom atom, data * pdata)
   {

      throw ::exception(todo("core"));
      //add_reference(pdata);

      //__construct(datamap()[atom], pdata);

   }


   //void document::OnFileManagerOpenFile(data * pdata, ::file::item_array & itema)
   //{

   //   item_action * pitemaction = dynamic_cast <item_action *> (this);

   //   if (pitemaction != nullptr)
   //   {

   //      if (pitemaction->open_file(pdata, itema))
   //      {

   //         return;

   //      }

   //   }

   //   request_file(itema[0]->m_filepathUser);

   //}


   //void document::InitializeFileManager(const ::string & pszMatter)
   //{

   //   m_pfilemanagerdata->m_pfilelistcallback = this;

   //   filemanager_initialize(0, pszMatter);

   //}


   component::~component()
   {

   }


   void component::filemanager_load_project(const ::file::path & pathFilemanagerProject, ::request * prequest, ::fs::data * pfsdata, callback * pcallback)
   {

      {

         KEEP(m_bRestoring);

         if (pathFilemanagerProject.is_empty() || pcontext->m_papexcontext->dir()->is(pathFilemanagerProject)
               || pathFilemanagerProject.extension().case_insensitive_order("component") != 0)
         {

            m_pathFilemanagerProject =          auto psystem = system();

         auto pacmedirectory = psystem->m_pacmedirectory;

pacmedirectory->localconfig() / "user.component";

         }
         else
         {

            m_pathFilemanagerProject = pathFilemanagerProject;

         }

         string_array stra;

         {

            ::pointer < ::mutex > m(e_create_new, "Local\\ca2-filemanagers");

            synchronous_lock synchronouslock(&m);

            stra.add_lines(pcontext->m_papexcontext->file()->as_string(m_pathFilemanagerProject), true);

         }


         if (pcontext->m_papexcontext->dir()->is(pathFilemanagerProject))
         {

            stra.add(create_manager_id(this) + ":" + pathFilemanagerProject);

         }

         if (stra.is_empty())
         {

            stra.add(create_manager_id(this) + ":");

         }

         string strManagerId;

         ::file::path path;

         for (index i = 0; i < stra.get_size();)
         {

            string str = stra[i];

            auto pFind = str.find(':');

            if (iFind > 0)
            {

               string strPath = str(pFind + 1);

               for (index j = i + 1; j < stra.get_size();)
               {

                  string strOther = stra[j];

                  iFind = strOther.find(':');

                  if (iFind > 0)
                  {

                     string strOtherPath = strOther(pFind + 1);

                     if (strOtherPath.case_insensitive_order(strPath) == 0)
                     {

                        stra.erase_at(j);

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

               stra.erase_at(i);

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

      //for (index i = 0; i < m_pimpactsystemProject->get_document_count(); i++)
      //{

      //   pdocument = m_pimpactsystemProject->get_document(i);

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

      //   ::pointer < ::mutex > m(e_create_new, "Local\\ca2-filemanagers");

      //   synchronous_lock synchronouslock(&m);

      //   pcontext->m_papexcontext->file()->put_contents(m_pathFilemanagerProject, stra.implode("\r\n"));

      //}

   }


   document * component::find_filemanager(::payload payloadFile)
   {

      throw ::exception(todo("core"));
      //::pointer<document>pdocument;

      //for (index i = 0; i < m_pimpactsystemProject->get_document_count(); i++)
      //{

      //   pdocument = m_pimpactsystemProject->get_document(i);

      //   if (pdocument.is_null())
      //   {

      //      continue;

      //   }

      //   pdocument = pdocument->get_main_document();

      //   if (pdocument->m_strManagerId == payloadFile.get_string().left(get_manager_id_len()))
      //   {

      //      return pdocument;

      //   }

      //   if (pdocument->filemanager_item()->m_filepathFinal.is_equal_fast(payloadFile))
      //   {

      //      return pdocument;

      //   }


      //}

      return nullptr;

   }


   document * component::open_filemanager(::payload payloadFile, ::request * prequest, ::fs::data * pfsdata, callback * pcallback)
   {

      //document * pdocument;

      //if (pcreate == nullptr)
      //{

      //   pcreate = __allocate< ::create >(papp->handler(), payloadFile, true);

      //}

      //pcreate->prop("component::template") = this;

      //pcreate->prop("filemanager::data") = pfilemanagerdata;

      //pcreate->prop("component::callback") = pcallback;

      //pcreate->m_payloadFile = payloadFile;

      //m_pimpactsystemProject->m_bQueueDocumentOpening = false;

      //m_pimpactsystemProject->do_request(pcreate);

      //pdocument = ::user::__document(pcreate);

      //if (pdocument.is_null())
      //{

      //   return nullptr;

      //}

      //pdocument->Initialize(pcreate == nullptr ? true : pcreate->m_bMakeVisible, false);

      //tab_impact * ptabimpact = pdocument->get_typed_impact < tab_impact >();

      //if (ptabimpact != nullptr)
      //{

      //   string strManagerId;

      //   ::file::path pathFolder = filemanager_project_entry(strManagerId, payloadFile, get_app());

      //   ptabimpact->set_current_tab_by_id("verifile://" + pathFolder);

      //}

      //return pdocument;

      return nullptr;

   }


   document * component::restore_filemanager(::payload payloadFile, ::request * prequest, ::fs::data * pfsdata, callback * pcallback)
   {

      throw ::exception(todo("core"));
      //filemanager()->m_filepath = payloadFile.get_file_path();

      //filemanager()->m_pcreate = pcreate;

      //filemanager()->m_pfsdata = pfsdata;

      //filemanager()->m_pcallback = pcallback;

      //filemanager()->open(nullptr, payloadFile);

      //return filemanager()->m_pdocument;

      return nullptr;

   }


   document * component::add_filemanager(const ::file::path & pathFolder, ::request * prequest, ::fs::data * pfsdata, callback * pcallback)
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


   bool component::erase_filemanager(::payload payloadFile)
   {

      //document * pdocument = find_manager(payloadFile);

      //m_pimpactsystemProject->erase_document(pdocument);

      //save_filemanager_project();

      //return pdocument.is_set();

      return false;

   }


   bool component::erase_filemanager(document * pdocument)
   {

      //pdocument->close_document();

      ////m_pimpactsystemProject->erase_document(pdocument);

      //save_filemanager_project();

      //return pdocument != nullptr;

      return true;

   }


   data * component::filemanager(::atom atom)
   {

      auto & pdata = datamap()[atom];

      if (pdata)
      {

         return pdata;

      }

      throw ::exception(todo("core"));
 /*     if (!pdata)
      {

         __construct(pdata, filemanager_create_data(atom));

      }*/

      return pdata;

   }



//document * component::open_main(::aura::application * pappOnBehalfOf, ::atom atom, ::request * prequest, ::fs::data * pfsdata, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   ::file::path pathFolder;

//   if (pcreate == nullptr)
//   {

//      pcreate = __allocate< ::create >(pappOnBehalfOf->handler());

//   }
//   else
//   {

//      pcreate->set_object(pappOnBehalfOf);

//   }

//   if (pcreate->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_payloadFile;

//      if (pcontext->m_papexcontext->dir()->is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.empty();

//      }

//   }



//   document * pdocument;

//   if (atom.i64() < -1 || atom.i64() == m_pimpactsystemProject->get_document_count())
//   {

//      pcreate->prop("component::template") = this;

//      pcreate->prop("filemanager::data") = pfilemanagerdata;

//      pcreate->prop("component::callback") = pcallback;

//      m_pimpactsystemProject->do_request(pcreate);

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
//   else if (atom.i64() < m_pimpactsystemProject->get_document_count())
//   {

//      pdocument = m_pimpactsystemProject->get_document((index)atom);

//   }

//   if (pdocument != nullptr)
//   {

//      tab_impact * ptabimpact = pdocument->get_typed_impact < tab_impact >();

//      if (pathFolder.m_iDir == 1)
//      {

//         if (ptabimpact != nullptr)
//         {

//            if (ptabimpact->get_tab_count() <= 0)
//            {

//               ptabimpact->set_current_tab_by_id("verifile://" + pathFolder);

//            }
//            else
//            {

//               ::pointer<::user::frame_window>pframe = ptabimpact->get_pane(0)->m_pholder->get_hold();

//               document * pdocument = pframe->get_active_document();

//               pdocument->FileManagerBrowse(pathFolder, action::e_source_user);

//            }

//         }

//      }
//      else
//      {

//         if (ptabimpact->get_tab_count() <= 0)
//         {

//            ptabimpact->set_current_tab_by_id("0");

//         }

//      }

//   }

//   return pdocument;

//}


//document * component::open(::aura::application * pappOnBehalfOf, atom atom, ::create * pcreateParam, ::fs::data * pfsdata, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   ::file::path pathFolder;

//   ::pointer<::create>pcreate(pcreateParam);

//   if (pcreate.is_null())
//   {

//      pcreate = __allocate< ::create >(pappOnBehalfOf->handler());

//   }
//   else
//   {

//      pcreate->set_object(pappOnBehalfOf);

//   }

//   if (pcreate->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_payloadFile;

//      if (pcontext->m_papexcontext->dir()->is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.empty();

//      }

//   }



//   document * pdocument;

//   if (atom.i64() < -1 || atom.i64() == m_pimpactsystem->get_document_count())
//   {

//      pcreate->prop("component::template") = this;

//      pcreate->prop("filemanager::data") = pfilemanagerdata;

//      pcreate->prop("component::callback") = pcallback;

//      m_pimpactsystem->do_request(pcreate);

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
//   else if (atom.i64() < m_pimpactsystem->get_document_count())
//   {

//      pdocument = m_pimpactsystem->get_document((index)atom);

//   }

//   if (pdocument != nullptr)
//   {

//      if (pathFolder.m_iDir == 1)
//      {

//         pdocument->FileManagerBrowse(pathFolder, ::e_source_user);

//      }

//   }

//   return pdocument;

//}


//document * component::create_new_document(callback * pcallback, ::request * prequest)
//{

//   document * pdocument = (m_pimpactsystem->create_new_document(pcreate));

//   if (pdocument != nullptr)
//   {

//      pdocument->filemanager_data()->m_pcallback = pcallback;
//      pdocument->filemanager_data()->m_pfilemanager = pcallback;
//      pdocument->filemanager_data()->m_pdocument = pdocument;

//      return pdocument;

//   }

//   return nullptr;

//}


//::pointer<data>component::create_data()
//{

//}


//document * component::open_child(bool bMakeVisible, bool bTransparentBackground, ::pointer<::user::interaction>puserinteractionParent, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __allocate< ::filemanager::data >(this);

//   }

//   ::pointer<::create>pcreate(e_create_new, pfilemanagerdata);

//   pcreate->m_bMakeVisible = false;
//   pcreate->m_puserinteractionParent = puserinteractionParent;
//   pcreate->prop("filemanager::data") = pfilemanagerdata;

//   if (pfilemanagerdata->m_pcallback == nullptr || pcallback != nullptr)
//   {

//      pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();

//   }

//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

//   m_pimpactsystemChild->do_request(pcreate);

//   document * pdocument = ::user::__document(pcreate);

//   if (pdocument == nullptr)
//   {

//      return nullptr;

//   }

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}


//document * component::open_child_list(bool bMakeVisible, bool bTransparentBackground, ::pointer<::user::interaction>puserinteractionParent, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   UNREFERENCED_PARAMETER(bMakeVisible);

//   ::pointer<::create>pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = puserinteractionParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __allocate< ::filemanager::data >(this);

//   }

//   pcreate->prop("filemanager::data") = pfilemanagerdata;


//   pfilemanagerdata->m_pfilemanagertemplate = this;
//   pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();
//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;


//   m_pimpactsystemChildList->do_request(pcreate);

//   document * pdocument = ::user::__document(pcreate);

//   if (pdocument == nullptr)
//   {

//      return nullptr;

//   }

//   pdocument->filemanager_data()->m_pdocument = pdocument;

//   if (pdocument->filemanager_data()->m_strDataKey.is_empty())
//   {

//      pdocument->filemanager_data()->m_strDataKey.m_strDataKey.formatf("%s(%d)",
//            psession->component().m_atomFileManager.str(),
//            pdocument->filemanager_data()->m_iDocument);

//   }

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}


//document * component::open_folder_selection_list(bool bMakeVisible, bool bTransparentBackground, ::pointer<::user::interaction>puserinteractionParent, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   UNREFERENCED_PARAMETER(bMakeVisible);

//   ::pointer<::create>pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = puserinteractionParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __allocate< ::filemanager::data >(this);

//   }

//   pcreate->prop("filemanager::data") = pfilemanagerdata;

//   pfilemanagerdata->m_pfilemanagertemplate = this;
//   pfilemanagerdata->m_pcallback = pcallback != nullptr ? pcallback : &psession->component();
//   pfilemanagerdata->m_pfilemanager = &psession->component();
//   pfilemanagerdata->m_iTemplate = m_iTemplate;
//   pfilemanagerdata->m_iDocument = m_iNextDocument++;
//   pfilemanagerdata->m_bTransparentBackground = bTransparentBackground;

//   m_pimpactsystemFolderSelectionList->do_request(pcreate);

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



