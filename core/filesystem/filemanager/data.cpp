#include "framework.h"
#include "aura/graphics/draw2d/image.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif

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


   void data::assert_valid() const
   {


   }


   void data::dump(dump_context& dumpcontext) const
   {


   }


   ::e_status data::initialize_filemanager_data(::object * pobject)
   {

      auto estatus = ::data::data::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

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


   bool data::open(::application * pappOnBehalfOf, ::file::path path, const ::action_context & context)
   {

      __pointer(::core::application) papplicationOnBehalfOf = pappOnBehalfOf;

      if (::is_null(m_pdocument))
      {

         __pointer(::user::interaction) puiParent = m_puserinteractionParent;

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

               puiParent = m_pcreate->m_puserprimitiveParent;

            }

         }

         if(::is_null(papplicationOnBehalfOf))
         {

            if (::is_set(puiParent))
            {

               pappOnBehalfOf = puiParent->get_application();

            }
            else if (::is_set(m_pcreate) && ::is_set(m_pcreate->create_get_application(get_application())))
            {

               papplicationOnBehalfOf = m_pcreate->create_get_application(get_application());

            }
            else if (::is_set(m_pdocumentTopic) && ::is_set(m_pdocumentTopic->get_application()))
            {

               papplicationOnBehalfOf = m_pdocumentTopic->get_application();

            }

         }

         if (::is_null(puiParent))
         {

            if (::is_set(papplicationOnBehalfOf->m_puiMainContainer))
            {

               puiParent = papplicationOnBehalfOf->m_puiMainContainer;

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
                       (m_pdocumenttemplate->open_document_file(pappOnBehalfOf, e_type_empty,
                             bMakeVisible,
                             puiParent,
                          ewindowflag(),
                          m_id));

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
//      if(m_datakey.is_empty())
//      {
//
//         m_datakey.m_strDataKey.format("%s", m_id.str().c_str());
//
//      }
//
//   }


   string data::get_last_browse_path(::object * pobject, const ::string & pszDefault)
   {

      string strPath;

      __pointer(::core::application) papplication = pobject->get_application();

      auto pcontext = m_pcontext;

      if (papplication->data_get({m_datakey.m_bLocalData, m_datakey.m_strDataKey+".last_browse_folder"}, strPath))
      {

         if (strPath == "machinefs://")
         {

            auto idMachine = get_local_machine_id();

            string strId;

            strId = m_datakey.m_strDataKey +".last_browse_folder." + __string(idMachine);

            if (!papplication->data_get({ m_datakey.m_bLocalData, strId }, strPath))
            {

               strPath.empty();

            }

         }

         //pcontext->m_papexcontext->dir().mk(strPath);

         if (pcontext->m_papexcontext->dir().is(strPath))
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

         strPath = pcontext->m_papexcontext->dir().desktop();

      }*/

      return strPath;

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


   ::e_status data::set_last_browse_path(::object * pobject, const ::file::path& path)
   {

      string strPath(path);

      __pointer(::core::application) papplication = pobject->get_application();

      if (::str::begins(path, astr.UifsProtocol)
         || ::str::begins(path, astr.FsProtocol))
      {

         papplication->data_set({ m_datakey.m_bLocalData, m_datakey.m_strDataKey +".last_browse_folder" }, strPath);

      }
      else
      {

         papplication->data_set({ m_datakey.m_bLocalData, m_datakey.m_strDataKey + ".last_browse_folder" }, "machinefs://");

         auto idMachine = get_local_machine_id();

         string strId;

         strId = m_datakey.m_strDataKey+".last_browse_folder." + __string(idMachine);

         papplication->data_set({ m_datakey.m_bLocalData, strId }, strPath);

      }

      return ::success;

   }


} // namespace filemanager



