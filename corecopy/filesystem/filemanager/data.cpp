#include "framework.h"
#include "_data.h"
#include "core/user/user/_tree.h"
#include "aura/platform/static_start.h"
#include "aura/astr.h"


namespace filemanager
{


   data::data()
   {

      m_setToolbar[::userfs::mode_normal] = "filemanager_toolbar.xml";
      m_setToolbar[::userfs::mode_saving] = "filemanager_saving_toolbar.xml";
      m_setToolbar[::userfs::mode_import] = "filemanager_import_toolbar.xml";
      m_setToolbar[::userfs::mode_export] = "filemanager_export_toolbar.xml";

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
      m_bIconView                = false;
      m_pholderFileList          = nullptr;
      m_ptreeFileTreeMerge       = nullptr;
      m_pdocumentTopic           = nullptr;
      m_bSetBergedgeTopicFile    = false;
      m_bTransparentBackground   = true;
      m_pdocument                = nullptr;
//      m_pfilemanager             = nullptr;
      m_pcallback                = nullptr;
      m_strLevelUp = "levelup";
      m_pfont.create(this);

      m_pfont->create_pixel_font("Verdana",14);

      m_bEnableRecursiveFolderSelectionList = true;

   }


   data::~data()
   {

   }


   ::estatus data::initialize_filemanager_data(::object * pobjectContext)
   {

      auto estatus = ::data::data::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      ::database::client::initialize_data_client(Application.dataserver());

      m_strLevelUp.Empty();
      m_setToolbar[::userfs::mode_normal] = "matter://filemanager_toolbar.xml";
      m_setToolbar[::userfs::mode_saving] = "matter://filemanager_saving_toolbar.xml";
      m_setToolbar[::userfs::mode_import] = "matter://filemanager_import_toolbar.xml";
      m_setToolbar[::userfs::mode_export] = "matter://filemanager_export_toolbar.xml";
      m_dataidStatic = "FileManagerFavoritesList";
      m_strXmlPopup = "matter://department/file_popup.xml";
      m_strFolderPopup = "matter://department/folder_popup.xml";
      m_strPopup = "matter://department/popup.xml";
      m_idExpandBox = 0;
      m_idCollapseBox = 0;

      return true;

   }


   bool data::is_topic()
   {

      return m_pdocumentTopic != nullptr;

   }


   bool data::do_prompt_file_name(var & varFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument)
   {

      m_pdocumentTopic = pdocument;

      if (m_pdocument == nullptr)
      {

         if (!open())
         {

            return false;

         }

      }

      return m_pdocument->do_prompt_file_name(varFile, nIDSTitle, lFlags, bOpenFileDialog, ptemplate, pdocument);

   }


   bool data::open(::aura::application * pappOnBehalfOf, ::file::path path, const ::action_context & context)
   {

      if (::is_null(m_pdocument))
      {

         ::user::interaction * puiParent = m_puserinteractionParent;

         bool bMakeVisible = m_bMakeVisible;

         if (!bMakeVisible && ::is_set(m_pcreate) &&
               m_pcreate->m_bMakeVisible)
         {

            bMakeVisible = true;

         }

         if (::is_null(puiParent))
         {

            if (::is_set(m_pcreate))
            {

               puiParent = dynamic_cast <::user::interaction*> (m_pcreate->m_puserinteractionParent);

            }

         }

         if(::is_null(pappOnBehalfOf))
         {

            if (::is_set(puiParent))
            {

               pappOnBehalfOf = puiParent->get_context_application();

            }
            else if (::is_set(m_pcreate) && ::is_set(m_pcreate->get_context_application()))
            {

               pappOnBehalfOf = m_pcreate->get_context_application();

            }
            else if (::is_set(m_pdocumentTopic) && ::is_set(m_pdocumentTopic->get_context_application()))
            {

               pappOnBehalfOf = m_pdocumentTopic->get_context_application();

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

               __pointer(::filemanager::callback) pcallback = pappOnBehalfOf;

               if (::is_set(pcallback))
               {

                  m_pcallback = pcallback;

               }

            }

         }


         m_pdocument = dynamic_cast < ::filemanager::document * >
                       (m_pdocumenttemplate->open_document_file(pappOnBehalfOf, type_empty,
                             bMakeVisible,
                             puiParent));

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




   void data::defer_update_data_key()
   {

      if(m_datakey.is_empty())
      {

         m_datakey.m_strDataKey.Format("%s", m_id.str().c_str());

      }

   }


   string data::get_last_browse_path(const char * pszDefault)
   {

      string strPath;

      if (Application.data_get({true, "last_browse_folder"}, strPath))
      {

         if (strPath == "machinefs://")
         {

            auto idMachine = get_local_machine_id();

            string strId;

            strId = "last_browse_folder." + __str(idMachine);

            if (!Application.data_get({ true, strId }, strPath))
            {

               strPath.empty();

            }
          
         }

         //Context.dir().mk(strPath);

         if (Context.dir().is(strPath))
         {

            return strPath;

         }

      }

      if (pszDefault != nullptr && strlen(pszDefault) > 0)
      {

         strPath = pszDefault;

      }
      else
      {

         strPath = Context.dir().desktop();

      }

      return "";

   }


   id data::get_local_machine_id()
   {

      id idMachine;

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


   ::estatus data::set_last_browse_path(const ::file::path& path)
   {

      string strPath(path);

      if (::str::begins(path, astr.UifsProtocol)
         || ::str::begins(path, astr.FsProtocol))
      {

         Application.data_set({ true, "last_browse_folder" }, strPath);

      }
      else
      {

         Application.data_set({ true, "last_browse_folder" }, "machinefs://");

         auto idMachine = get_local_machine_id();

         string strId;

         strId = "last_browse_folder." + __str(idMachine);

         Application.data_set({ true, strId }, strPath);

      }

      return ::success;

   }


} // namespace filemanager





