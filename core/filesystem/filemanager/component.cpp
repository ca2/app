﻿#include "framework.h"
#include "aura/graphics/image/icon.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "fs_simple_tree.h"
#include "aura/user/user/shell.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "form.h"
#include "child_frame.h"
#include "impact.h"
#include "path_impact.h"
#include "save_as_name_impact.h"
#include "left_impact.h"
#include "main_impact.h"
#include "main_frame.h"
#include "frame.h"
#include "tab_impact.h"
#include "child_frame.h"
#include "form_child_frame.h"
#include "core/user/simple/form_impact.h"
#include "folder_selection_list_impact.h"
#include "operation_document.h"
#include "operation_info_impact.h"
#include "operation_list_impact.h"
#include "operation_child_frame.h"
#include "operation_impact.h"
#include "data.h"
#include "document.h"
#include "file_list.h"
#include "fs_simple_list_impact.h"
#include "fs_simple_impact.h"
#include "folder_list_impact.h"
#include "thumbnail.h"
#include "base/user/user/multiple_document_template.h"
#include "core/platform/session.h"
//#include "aura/_defer.h"


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


   string create_manager_id(::object * pobject)
   {

      memory mem;

      mem.set_size(get_manager_id_byte_len());

      auto pmathematics = ::mathematics::mathematics();

      pmathematics->random_bytes(mem.get_data(), mem.get_size());

      return mem.to_hex().uppered();

   }


   bool is_valid_manager_id(const ::string & strParam)
   {

      const char * psz = strParam;

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


   bool is_valid_filemanager_project_entry(const ::string & strParam)
   {

      const char * psz = strParam;

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


   ::file::path filemanager_project_entry(string& strManagerId, const ::string & psz, ::aura::context* pcontext)
   {

      if (is_valid_filemanager_project_entry(psz))
      {

         strManagerId = string(psz, get_manager_id_len());

         return psz.c_str() + get_manager_id_len() + 1;

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


   void component::initialize_filemanager_component(::object * pobject)
   {

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      ::factory::add_factory_item <form >();
      ::factory::add_factory_item <document >();
      ::factory::add_factory_item <child_frame >();
      ::factory::add_factory_item <impact >();
      ::factory::add_factory_item <path_impact >();
      ::factory::add_factory_item <save_as_impact >();
      ::factory::add_factory_item <left_impact >();
      ::factory::add_factory_item <main_impact >();
      ::factory::add_factory_item <file_list >();
      ::factory::add_factory_item <thumbnail >();
      ::factory::add_factory_item <main_frame >();
      ::factory::add_factory_item <frame >();
      ::factory::add_factory_item <tab_impact >();
      ::factory::add_factory_item <form_child_frame >();
      ::factory::add_factory_item <::simple_form_impact >();
      ::factory::add_factory_item <folder_selection_list_impact >();
      ::factory::add_factory_item <folder_list_impact >();
      ::factory::add_factory_item <operation_document >();
      ::factory::add_factory_item <operation_child_frame >();
      ::factory::add_factory_item <operation_impact >();
      ::factory::add_factory_item <operation_info_impact >();
      ::factory::add_factory_item <operation_list_impact >();
      ::factory::add_factory_item <save_as_edit_impact >();
      ::factory::add_factory_item <save_as_button>();
      ::factory::add_factory_item <fs::simple::impact >();
      ::factory::add_factory_item <fs::simple::list_impact >();
      ::factory::add_factory_item <fs::simple::tree >();

      //__construct_new(this, m_pmap);

      //auto& user = User;

      //auto pshell = user.shell();

      //estatus = pshell->initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pmulti = __new(::user::multiple_document_template(
                         "filemanager",
                         __form_document_type(),
                         __type(form_child_frame),
                         __type(form)));

      __construct(m_pdocumenttemplateForm, pmulti);

      auto psession = get_session();

      psession->add_document_template(pmulti);

      auto psingle = __new(::user::multiple_document_template(
                          "filemanager",
                          __type(operation_document),
                          __type(operation_child_frame),
                          __type(operation_impact)));

      __construct(m_pdocumenttemplateOperation, psingle);

      psession->add_document_template(psingle);

      //return true;

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


   ::pointer<data>component::filemanager_create_data(atom atom)
   {

      if (!is_filemanager(atom))
      {

         return nullptr;

      }

      auto pdata = __new(data);

      pdata->initialize_filemanager_data(this);

      pdata->m_atom = atom;

      filemanager_set_data(atom, pdata);

      ::pointer<::user::multiple_document_template>pdoctemplate;

      string strTemplateId = atom;

      strTemplateId.find_replace("::", "/");

      if (is_filemanager_group(atom, TABBED_GROUP))
      {
         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(frame),       // main SDI frame window
                             __type(tab_impact)));

      }
      else if (is_filemanager_group(atom, LIST_GROUP))
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(main_frame),
                             __type(file_list)));

      }
      else if (is_filemanager_group(atom, FOLDER_SELECTION_LIST_GROUP))
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(main_frame),
                             __type(folder_selection_list_impact)));

      }
      else
      {

         pdoctemplate = __new(::user::multiple_document_template(
                             strTemplateId,
                             __type(document),
                             __type(frame),
                             __type(impact)));
      }

      auto psession = get_session();

      psession->add_document_template(pdoctemplate);

      pdata->m_pdocumenttemplate = pdoctemplate;

      return pdata;

   }


   void component::filemanager_set_data(atom atom, data * pdata)
   {

      add_reference(pdata);

      __construct(datamap()[atom], pdata);

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

      //request_file(itema[0]->m_filepathUser);

   }


   void document::InitializeFileManager(const ::string & strMatter)
   {

      m_pfilemanagerdata->m_pfilelistcallback = this;

      filemanager_initialize(0, (const ::file::path &) strMatter);

   }


   component::~component()
   {

   }


   void component::filemanager_load_project(const ::file::path & pathFilemanagerProject, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      {

         __keep(m_bRestoring);

         auto pcontext = get_context();

         if (pathFilemanagerProject.is_empty() || pcontext->m_papexcontext->dir().is(pathFilemanagerProject)
               || pathFilemanagerProject.final_extension().compare_ci("component") != 0)
         {

            m_pathFilemanagerProject = m_psystem->m_pacmedirectory->localconfig() / "user.component";

         }
         else
         {

            m_pathFilemanagerProject = pathFilemanagerProject;

         }

         string_array stra;

         {

            ::mutex m(e_create_new, "Local\\ca2-filemanagers");

            synchronous_lock synchronouslock(&m);

            stra.add_lines(pcontext->m_papexcontext->file().as_string(m_pathFilemanagerProject), true);

         }

         if (pcontext->m_papexcontext->dir().is(pathFilemanagerProject))
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

      //   synchronous_lock synchronouslock(&m);

      //   pcontext->m_papexcontext->file().put_contents(m_pathFilemanagerProject, stra.implode("\r\n"));

      //}

   }


   document * component::find_filemanager(::payload payloadFile)
   {

      ::pointer<document>pdocument;

      //for (index i = 0; i < m_pdocumenttemplateProject->get_document_count(); i++)
      //{

      //   pdocument = m_pdocumenttemplateProject->get_document(i);

      //   if (pdocument.is_null())
      //   {

      //      continue;

      //   }

      //   pdocument = pdocument->get_main_document();

      //   if (pdocument->m_strManagerId == payloadFile.get_string().Left(get_manager_id_len()))
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


   document * component::open_filemanager(::payload payloadFile, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      //document * pdocument;

      //if (pcreate == nullptr)
      //{

      //   pcreate = __new(::create(papp->handler(), payloadFile, true));

      //}

      //pcreate->prop("component::template") = this;

      //pcreate->prop("filemanager::data") = pfilemanagerdata;

      //pcreate->prop("component::callback") = pcallback;

      //pcreate->m_payloadFile = payloadFile;

      //m_pdocumenttemplateProject->m_bQueueDocumentOpening = false;

      //m_pdocumenttemplateProject->do_request(pcreate);

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


   document * component::restore_filemanager(::payload payloadFile, ::create * pcreate, ::fs::data * pfsdata, callback * pcallback)
   {

      filemanager()->m_filepath = payloadFile.file_path();

      filemanager()->m_pcreate = pcreate;

      filemanager()->m_pfsdata = pfsdata;

      filemanager()->m_pcallback = pcallback;

      filemanager()->open(nullptr, payloadFile);

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


   bool component::erase_filemanager(::payload payloadFile)
   {

      //document * pdocument = find_manager(payloadFile);

      //m_pdocumenttemplateProject->erase_document(pdocument);

      //save_filemanager_project();

      //return pdocument.is_set();

      return false;

   }


   bool component::erase_filemanager(document * pdocument)
   {

      //pdocument->close_document();

      ////m_pdocumenttemplateProject->erase_document(pdocument);

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

      if (!pdata)
      {

         filemanager_create_data(atom);

         // filemanager_create_data should had set pdata.
         ASSERT(pdata);

      }

      return pdata;

   }



//document * component::open_main(::aura::application * pappOnBehalfOf, ::atom atom, ::create * pcreate, ::fs::data * pfsdata, ::filemanagerpointer< data > pdata, callback * pcallback)
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

//   if (pcreate->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_payloadFile;

//      if (pcontext->m_papexcontext->dir().is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.Empty();

//      }

//   }



//   document * pdocument;

//   if (atom.i64() < -1 || atom.i64() == m_pdocumenttemplateProject->get_document_count())
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
//   else if (atom.i64() < m_pdocumenttemplateProject->get_document_count())
//   {

//      pdocument = m_pdocumenttemplateProject->get_document((index)atom);

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

//      pcreate = __new(::create(pappOnBehalfOf->handler()));

//   }
//   else
//   {

//      pcreate->set_object(pappOnBehalfOf);

//   }

//   if (pcreate->m_ecommand == ::command_line::command_file_open)
//   {

//      pathFolder = pcreate->m_payloadFile;

//      if (pcontext->m_papexcontext->dir().is(pathFolder))
//      {

//         pathFolder.m_iDir = 1;

//      }
//      else
//      {

//         pathFolder.Empty();

//      }

//   }



//   document * pdocument;

//   if (atom.i64() < -1 || atom.i64() == m_pdocumenttemplate->get_document_count())
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
//   else if (atom.i64() < m_pdocumenttemplate->get_document_count())
//   {

//      pdocument = m_pdocumenttemplate->get_document((index)atom);

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


//::pointer<data>component::create_data()
//{

//}


//document * component::open_child(bool bMakeVisible, bool bTransparentBackground, ::pointer<::user::interaction>puserinteractionParent, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(this));

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

//   m_pdocumenttemplateChild->do_request(pcreate);

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

//   __UNREFERENCED_PARAMETER(bMakeVisible);

//   ::pointer<::create>pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = puserinteractionParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(this));

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

//      pdocument->filemanager_data()->m_datakey.m_strDataKey.format("%s(%d)",
//            psession->component().m_atomFileManager.str(),
//            pdocument->filemanager_data()->m_iDocument);

//   }

//   pdocument->Initialize(bMakeVisible);

//   return pdocument;

//}


//document * component::open_folder_selection_list(bool bMakeVisible, bool bTransparentBackground, ::pointer<::user::interaction>puserinteractionParent, ::filemanagerpointer< data > pdata, callback * pcallback)
//{

//   __UNREFERENCED_PARAMETER(bMakeVisible);

//   ::pointer<::create>pcreate(e_create);

//   pcreate->m_bMakeVisible = false;

//   pcreate->m_puserinteractionParent = puserinteractionParent;

//   if (pfilemanagerdata == nullptr)
//   {

//      pfilemanagerdata = __new(::filemanager::data(this));

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



   ::core::session * component::get_session() const
   {

      return m_pcontext ? m_pcontext->m_pcoresession : nullptr;

   }


} // namespace filemanager



