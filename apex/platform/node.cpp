//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "get_file_extension_mime_type.h"
#include "node.h"
#include "acme/constant/character_set.h"
#include "acme/constant/id.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_system_options.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/filesystem/filesystem/listing.h"
#include "acme/exception/interface_only.h"
#include "acme/windowing/windowing.h"
#include "acme/prototype/string/international.h"
#include "apex/filesystem/file/set.h"
#include "apex/input/input.h"
#include "apex/platform/application.h"
#include "apex/platform/node.h"
//#include "apex/platform/os_context.h"

#include "apex/platform/system.h"


namespace apex
{


   node::node()
   {

      //m_papexnode = this;

   }


   node::~node()
   {


   }


#ifdef _DEBUG


   huge_integer node::increment_reference_count()
   {

      return ::platform::node::increment_reference_count();

   }


   huge_integer node::decrement_reference_count()
   {

      return ::platform::node::decrement_reference_count();

   }


#endif


   void node::on_initialize_particle()
   {

      //auto estatus =
      
      ::platform::node::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}


      //return estatus;

   }


   void node::destroy()
   {

      ::platform::node::destroy();

      ::channel::destroy();

   }


   void node::main()
   {
   
      auto psystem = system();
      
      //auto estatus = 
      
      psystem->main();
      
      //if(!estatus)
      //{
      // 
      //   return estatus;
      //   
      //}
      //
      //return estatus;
      
   }


   string node::system_options_html()
   {

      string strFooter__;

      if (application()->m_bAudio)
      {

         ::payload payload;

         ::property_set propertyset;

         propertyset["handler_library"] = "user_text_to_speech";

         ::string strObject = "pane_tab_impact";

         ::string strMember = "add_pane_tab_impact_handler_library";

         application()->_handle_call(payload, strObject, strMember, propertyset);

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

         strFooter__ += "<h2>Text to Speech</h2>";

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" id=\"text_to_speech_azure.checkbox\" />";
         strFooter__ += "&nbsp;Azure";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" id=\"text_to_speech_google.checkbox\" />";
         strFooter__ += "&nbsp;Google";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

#ifdef WINDOWS_DESKTOP

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" id=\"text_to_speech_sapi.checkbox\" />";
         strFooter__ += "&nbsp;Microsoft Speech API";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

#elif defined(UNIVERSAL_WINDOWS)

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" id=\"text_to_speech_speech_synthesis.checkbox\" />";
         strFooter__ += "&nbsp;Speech Synthesis";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

#endif

      }
      else
      {

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

         strFooter__ += "(No Audio)";

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

      }

      strFooter__ += system_options_main_body();

      strFooter__ += "</body>";
      strFooter__ += "</html>";

      return strFooter__;

   }


   string node::system_options_main_body()
   {

      return "";

   }


   void node::set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype)
   {

      string_array straExtension;

      string_array straMimeType;

      pgetfileextensionmimetype->file_extension_mime_type(straExtension, straMimeType);

      set_file_extension_mime_type(straExtension, straMimeType);

   }


   void node::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
   {

      ::string_array stra;

      //stra.add("_inheaven_1920x1080_o.JPG");
      //stra.add("02209_stratosphere_1920x1080_o.JPG");
      //stra.add("Bamboo Weathered Standard.jpg");

      stra.add("bambu1.jpg");
      stra.add("bambu2.jpg");
      stra.add("bambu3.jpg");
      stra.add("bambu33.png");
      stra.add("bambu4.jpg");

      ::file::path pathFolder;

      pathFolder = "https://ca2.network/image/cc/ca2core/bkimageoftheday/common/";

      pfileset->m_listingAddUp.m_eflag = ::file::e_flag_file;

      for (auto & str : stra)
      {

         ::file::path path = pathFolder / (str + string("?sessid=noauth"));

         path.set_existent_file();

         pfileset->m_listingAddUp.defer_add(path);

      }

      //return true;

   }



//   void node::defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId)
//   {
//
//      //throw ::interface_only();
//
//   }


//   void node::set_application_menu(::apex::ication_menu * pmenu, ::apex::application * papp)
//   {
//
//   }


   ::file::path node::get_desktop_file_path(::apex::application * papp)
   {

      return "";

   }


   // void node::defer_notify_startup_complete()
   // {
   //
   //
   // }


   void node::start_node()
   {

      auto psystem = system();

      //auto estatus = 
      psystem->on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;


   }


//   void node::application_handle(huge_integer l, void * p)
//   {
//   
//   }


   // void node::on_operating_system_user_theme_change()
   // {
   //
   //    auto psystem = system();
   //
   //    psystem->signal(id_operating_system_user_theme_change);
   //
   // }


   // void node::on_operating_system_user_color_change()
   // {
   //
   //    bool bOperatingSystemDarkMode = this->dark_mode();
   //
   //    system()->set_dark_mode(bOperatingSystemDarkMode);
   //    auto psystem = system();
   //
   //    psystem->signal(id_operating_system_user_color_change);
   //
   //
   // }


   // void node::on_operating_system_font_list_change()
   // {
   //
   //    auto psystem = system();
   //
   //    psystem->signal(id_operating_system_font_list_change);
   //
   // }


   void node::defer_innate_ui()
   {

      auto strToolkit = ::windowing::get_user_toolkit_id();

      if(strToolkit.has_character())
      {

         auto pfactory = system()->factory("innate_ui", strToolkit);

         pfactory->merge_to_global_factory();

      }

   }


   void node::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      throw ::interface_only();

   }


   bool node::shell_link_target(::file::path & pathTarget, const ::file::path & pathLnk)
   {

      throw ::interface_only();

      return false;

   }


   bool node::shell_link_icon(::file::path& pathIcon, int& iIcon, const ::file::path& pathLnk)
   {

      throw ::interface_only();

      return false;

   }


   // void node::parallelization_initialize()
   // {

   //    throw ::interface_only();

   // }


   // void node::parallelization_finalize()
   // {

   //    throw ::interface_only();

   // }


   bool node::has_ip4_internet()
   {

      return true;

   }

   
   bool node::has_ip6_internet()
   {

      return true;

   }


   void node::thread_initialize(::thread * pthread)
   {

      //return ::success;

   }


   //void node::thread_finalize(::thread * pthread)
   //{

   //   return ::success;

   //}


   // void node::node_thread_initialize(::thread * pthread)
   // {

   //    throw ::interface_only();

   // }


   // void node::node_thread_finalize(::thread * pthread)
   // {

   //    throw ::interface_only();

   // }


   string node::get_version()
   {

      return "";

   }


   void node::_001InitializeShellOpen()
   {

      throw ::interface_only();

   }


   /*void node::shell_open(const ::file::path & path, const ::string & strParams, const ::file::path & pathFolder)
   {

      node()->file_open(path, strParams, pathFolder);

   }*/


   void node::show_wait_cursor(bool bShow)
   {

   }


   void node::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
   {

      throw ::interface_only();

   }


//   bool node::is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild,
//                                       const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration,
//                                       const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
//   {
//
//      return false;
//
//   }
//
//   bool node::set_application_installed(const ::file::path & pathExe, string strAppId, const ::scoped_string & scopedstrBuild,
//                                        const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrConfiguration,
//                                        const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema)
//   {
//
//
//      return false;
//
//   }
//
//
//   bool node::set_last_run_application_path(string strAppId)
//   {
//
//      return false;
//
//   }


   void node::on_start_application(::apex::application *papplication)
   {


   }


   void node::on_create_app_shortcut(::platform::application * papplication)
   {

   }


   void node::defer_create_app_shortcut(::platform::application* papplication)
   {

      auto pathShortcut = app_shortcut_path(papplication);

      auto path = file_system()->module();

      ::file::path pathTarget;

      ::file::path pathIcon;

      int iIcon = -1;

      auto plink = path_system()->resolve_link(pathShortcut);

      // Enough condition to create shortcut
      bool bEnoughCondition1 = !plink;
      bool bEnoughCondition2 = plink && !(plink->m_elink & ::file::e_link_target);
      bool bEnoughCondition3 = plink && !path_system()->real_path_is_same(plink->m_pathTarget, path);
      bool bEnoughCondition4 = plink && !(plink->m_elink & ::file::e_link_icon);
      bool bEnoughCondition5 = plink && (plink->m_pathIcon.trimmed().is_empty() || !file_system()->exists(plink->m_pathIcon));

      //bool bAtLeastIsPossibleHandlerForPossibleFileAssociations = true; // todo

      bool bAtLeastIsPossibleHandlerForPossibleFileAssociations = false;

      bool bEnoughCondition6 = bAtLeastIsPossibleHandlerForPossibleFileAssociations;

      //if (!file_system()->exists(pathCreatedShortcut)
      if (bEnoughCondition1
         || bEnoughCondition2
         || bEnoughCondition3
         || bEnoughCondition4
         || bEnoughCondition5
         || bEnoughCondition6
         )
      {

         create_app_shortcut(papplication);

      }

   }


   ::file::path node::app_shortcut_path(::platform::application* papplication)
   {

      //::file::path pathShortcut;

      ////#ifdef WINDOWS_DESKTOP

      //pathShortcut = directory_system()->roaming() / "Microsoft/Windows/Start Menu/Programs" / strRoot / (strAppName + ".lnk");

      ////#else
      ////
      ////      ::string strDesktopFileName;
      ////
      ////      strDesktopFileName = m_strAppId;
      ////
      ////      strDesktopFileName.find_replace("/", ".");
      ////
      ////      pathShortcut = directory_system()->home() / ".local/share/applications" / (strDesktopFileName + ".desktop");
      ////
      ////#endif

      return {};

   }


   ::string node::get_host_name()
   {

      return {};

   }


   void node::load_character_set_default_sample_text()
   {

      if (m_mapCharacterSetEnum.is_empty())
      {

         for (int i = 0; i < e_character_set_count; i++)
         {

            auto echaracterset = (enum_character_set)i;

            m_mapCharacterSetEnum[enum_character_set_text(echaracterset)] = echaracterset;

         }

      }

      auto lines = file()->lines("matter://character_set_default_sample_text.txt");

      for (auto line : lines)
      {

         ::string_array stra;

         stra.explode("=", line);

         if (stra.size() == 2)
         {

            ::string strEnum = stra[0].trimmed();

            ::string strSampleText = stra[1].trimmed();
            
            m_mapCharacterSetDefaultSampleText[m_mapCharacterSetEnum[strEnum]] = strSampleText;

         }

      }

   }


   ::pointer < ::input::input > node::create_input()
   {

      return __øcreate < ::input::input > ();

   }

   
   bool node::is_key_pressed(bool * pbPressed, ::user::enum_key ekey)
   {

      return false;

   }


   void node::root_ones(::file::listing &listing)
   {
      
      auto pfilesystemoptions = application()->m_pfilesystemoptions;
      
      if(pfilesystemoptions->m_bOperatingSystemRootOnes)
      {
         
         directory()->root_ones(listing);
         
      }
      
      if(pfilesystemoptions->m_bDropbox)
      {
         
         ::file::path pathDropbox = m_papplication->defer_process_matter_path("dropbox://");
         
         if(pathDropbox.has_character() && directory()->is(pathDropbox))
         {
            
            ::file::path & path = listing.insert_at(0, "dropbox://");
            
            path.set_existent_folder();
            
            listing.m_straTitle.insert_at(0, unitext("Dropbox"));
            
         }
         
         ::file::path pathDropboxApp = m_papplication->defer_process_matter_path("dropbox-app://");
         
         if(pathDropboxApp.m_epath == ::e_path_file && directory()->is(pathDropboxApp))
         {
            
            ::file::path & path = listing.insert_at(0, "dropbox-app://");
            
            path.set_existent_folder();
            
            listing.m_straTitle.insert_at(0, unitext("Dropbox-App"));
            
         }
         
      }
      
      if(pfilesystemoptions->m_bOneDrive)
      {
         
         ::file::path pathOneDrive = m_papplication->defer_process_matter_path("onedrive://");
         
         if(pathOneDrive.m_epath == ::e_path_file && directory()->is(pathOneDrive))
         {
            
            ::file::path & path = listing.insert_at(0, "onedrive://");
            
            path.set_existent_folder();
            
            listing.m_straTitle.insert_at(0, unitext("OneDrive"));
            
         }
         
      }
      
      if(pfilesystemoptions->m_b_iCloudContainer)
      {
         
         if(directory_system()->has_icloud_container())
         {
            
            ::string pathContainer;
            
            pathContainer = directory_system()->icloud_container_documents();
            
            ::string strContainerName;
            
            strContainerName = application()->m_pfilesystemoptions->m_str_iCloudContainerName;
            
            auto iInsert = listing.size();
            
            ::file::path & path = listing.insert_at(iInsert, pathContainer);
            
            path.set_existent_folder();
            
            listing.m_straTitle.insert_at(iInsert, strContainerName);
            
         }
         
      }
      
      if(pfilesystemoptions->m_bVideo)
      {

         ::file::path & path = listing.insert_at(0, "video://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Video"));

      }
      
      if(pfilesystemoptions->m_bImage)
      {

         ::file::path & path = listing.insert_at(0, "image://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Image"));

      }
      
      if(pfilesystemoptions->m_bMusic)
      {

         ::file::path & path = listing.insert_at(0, "music://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Music"));

      }

      if(pfilesystemoptions->m_bDownload)
      {

         ::file::path & path = listing.insert_at(0, "download://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Download"));

      }

      if(pfilesystemoptions->m_bDocument)
      {

         ::file::path & path = listing.insert_at(0, "document://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Document"));

      }

      if(pfilesystemoptions->m_bDesktop)
      {

         ::file::path & path = listing.insert_at(0, "desktop://");

         path.set_existent_folder();

         listing.m_straTitle.insert_at(0, unitext("Desktop"));

      }

//#ifdef WINDOWS_DESKTOP
//
//      ::file::path strDesktopFolder;
//
//      ::windows::shell_get_special_folder_path(
//         nullptr,
//         strDesktopFolder,
//         CSIDL_DESKTOP,
//         false);
//
//      ::file::path & path = listing.insert_at(0,strDesktopFolder);
//      path.m_iDir = 1;
//      listing.m_straTitle.insert_at(0,unitext("Desktop"));
//
//#endif

      
   }





//   bool node::defer_enumerate_protocol(::file::listing& listing)
//   {
//      
//      return false;
//      
//   }


} // namespace apex



