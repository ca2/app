#include "framework.h"
#include "data.h"
#include "document.h"
#include "file_list.h"
#include "acme/primitive/data/listener.h"
#include "apex/database/_binary_stream.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "acme/handler/request.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/write_text/font.h"
#include "base/user/user/impact.h"
#include "base/user/user/multiple_document_template.h"
#include "core/platform/application.h"


namespace filemanager
{


   data::data()
   {

      m_setToolbar[::userfs::e_mode_normal] = "filemanager_toolbar.xml";
      m_setToolbar[::userfs::e_mode_saving] = "filemanager_saving_toolbar.xml";
      m_setToolbar[::userfs::e_mode_import] = "filemanager_import_toolbar.xml";
      m_setToolbar[::userfs::e_mode_export] = "filemanager_export_toolbar.xml";

      m_bMakeVisible = true;
      m_bTransparentBackground = true;
      m_puserinteractionParent = nullptr;
      m_pcallback = nullptr;

      m_pfilelistcallback = nullptr;

      m_bFileSize                = true;
      m_iIconSize                = 16;
      m_bListText                = true;
      m_bListSelection           = true;
      m_bPassBk                  = false;
      m_bIconImpact                = false;
      m_pholderFileList          = nullptr;
      m_ptreeFileTreeMerge       = nullptr;
      m_pdocumentTopic           = nullptr;
      m_bSetBergedgeTopicFile    = false;
      m_bTransparentBackground   = true;
      m_pdocument                = nullptr;
//      m_pfilemanager             = nullptr;
      m_pcallback                = nullptr;
      m_strLevelUp = "levelup";

      m_bEnableRecursiveFolderSelectionList = true;

   }


   data::~data()
   {

   }


//   void data::assert_ok() const
//   {
//
//
//   }
//
//
//   void data::dump(dump_context& dumpcontext) const
//   {
//
//
//   }


   void data::initialize_filemanager_data(::particle * pparticle)
   {

      //auto estatus = 
      
      ::data::data::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;
      m_typeFileList = __type(file_list);
      //}
      m_pfont.create(this);

      m_pfont->create_font("Verdana", 14px);

      m_strLevelUp.empty();
      m_setToolbar[::userfs::e_mode_normal] = "matter://filemanager_toolbar.xml";
      m_setToolbar[::userfs::e_mode_saving] = "matter://filemanager_saving_toolbar.xml";
      m_setToolbar[::userfs::e_mode_import] = "matter://filemanager_import_toolbar.xml";
      m_setToolbar[::userfs::e_mode_export] = "matter://filemanager_export_toolbar.xml";
      m_strDataKeyStatic = "FileManagerFavoritesList";
      m_strXmlPopup = "matter://department/file_popup.xml";
      m_strFolderPopup = "matter://department/folder_popup.xml";
      m_strPopup = "matter://department/popup.xml";
      m_atomExpandBox = 0;
      m_atomCollapseBox = 0;

      //return true;

   }


   bool data::is_topic()
   {

      return m_pdocumentTopic != nullptr;

   }


   bool data::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      m_pdocumentTopic = pdocument;

      if (m_pdocument == nullptr)
      {

         if (!open())
         {

            return false;

         }

      }

      return m_pdocument->do_prompt_file_name(payloadFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

   }


   bool data::open(::apex::application * pappOnBehalfOfParam, ::file::path path, const ::action_context & context)
   {

      ::pointer<::core::application>pappOnBehalfOf = pappOnBehalfOfParam;

      if (::is_null(m_pdocument))
      {

         ::pointer<::user::interaction>puiParent = m_puserinteractionParent;

         bool bMakeVisible = m_bMakeVisible;

         if (!bMakeVisible && ::is_set(m_prequest) && m_prequest->m_bMakeVisible)
         {

            bMakeVisible = true;

         }

         if (::is_null(puiParent))
         {

            if (::is_set(m_prequest))
            {

               puiParent = m_prequest->m_puserelementParent;

            }

         }

         if(::is_null(pappOnBehalfOf))
         {

            if (::is_set(puiParent))
            {

               pappOnBehalfOf = puiParent->get_app();

            }
            else if (::is_set(m_prequest) && ::is_set(m_prequest->create_get_app(get_app())))
            {

               pappOnBehalfOf = m_prequest->create_get_app(get_app());

            }
            else if (::is_set(m_pdocumentTopic) && ::is_set(m_pdocumentTopic->get_app()))
            {

               pappOnBehalfOf = m_pdocumentTopic->get_app();

            }

         }

         if (::is_null(puiParent))
         {

            if (::is_set(pappOnBehalfOf->m_puiMainContainer))
            {

               puiParent = pappOnBehalfOf->m_puiMainContainer;

            }

         }

         if (::is_null(m_pcallback))
         {

            if (::is_set(pappOnBehalfOf))
            {

               ::pointer<::filemanager::callback>pcallback = pappOnBehalfOf;

               if (::is_set(pcallback))
               {

                  m_pcallback = pcallback;

               }

            }

         }

         m_pdocument = dynamic_cast < ::filemanager::document * >
                       (m_pimpactsystem->open_document_file(pappOnBehalfOf, e_type_empty,
                             bMakeVisible,
                             puiParent,
                          e_window_flag(),
                          m_atom));

      }

      auto pdocument = m_pdocument;

      if (::is_null(pdocument))
      {

         return false;

      }

      if (path.is_empty())
      {

         return true;

      }

      pdocument->browse(path, context);

      return true;

   }




//   void data::defer_update_data_key()
//   {
//
//      if(m_strDataKey.is_empty())
//      {
//
//         m_strDataKey.format("%s", m_atom.str().c_str());
//
//      }
//
//   }


   string data::get_last_browse_path(::particle * pparticle, const ::string & pszDefault)
   {

      string strPath;

      ::pointer<::core::application>papp = pparticle->acmeapplication();

      auto pcontext = m_pcontext;

      if (papp->datastream()->get(m_strDataKey +".last_browse_folder", strPath))
      {

         if (strPath == "machinefs://")
         {

            auto idMachine = get_local_machine_id();

            string strId;

            strId = m_strDataKey+".last_browse_folder." + idMachine;

            if (!papp->datastream()->get(strId, strPath))
            {

               strPath.empty();

            }

         }

         //dir()->create(strPath);

         if (dir()->is(strPath))
         {

            return strPath;

         }

      }

    /*  if (pszDefault != nullptr && strlen(pszDefault) > 0)
      {

         strPath = pszDefault;

      }
      else
      {

         strPath = dir()->desktop();

      }*/

      return strPath;

   }


   atom data::get_local_machine_id()
   {

      atom idMachine;

#ifdef LINUX
      idMachine = "Linux";
#elif defined(WINDOWS_DESKTOP)
      idMachine = "WindowsDesktop";
#elif defined(WINDOWS)
      idMachine = "Metrowin";
#elif defined(MACOS)
      idMachine = "macOS";
#elif defined(__APPLE__)
      idMachine = "iOS";
#endif

      return idMachine;

   }


   void data::set_last_browse_path(::particle * pparticle, const ::file::path& path)
   {

      string strPath(path);

      ::pointer<::core::application>papp = pparticle->acmeapplication();

      if (string_begins(path, "uifs://")
         || string_begins(path, "fs://"))
      {

         papp->datastream()->set(m_strDataKey +".last_browse_folder", strPath);

      }
      else
      {

         papp->datastream()->set(m_strDataKey + ".last_browse_folder", "machinefs://");

         auto idMachine = get_local_machine_id();

         string strId;

         strId = m_strDataKey+".last_browse_folder." + idMachine;

         papp->datastream()->set(strId, strPath);

      }

      //return ::success;

   }


} // namespace filemanager



