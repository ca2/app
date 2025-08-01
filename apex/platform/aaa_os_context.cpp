#include "framework.h"
#include "os_context.h"
#include "acme/exception/interface_only.h"
#include "acme/filesystem/filesystem/link.h"
#include "acme/platform/node.h"
#include "acme/platform/get_file_extension_mime_type.h"
#include "apex/platform/context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/file/set.h"
#if defined(LINUX) || defined(__APPLE__) || defined(FREEBSD)
#include <unistd.h>
#endif

//
//namespace apex
//{


   os_context::os_context()
   {
   }

   os_context::~os_context()
   {
   }

//
//   void os_context::finalize()
//   {
//
//
//   }
//
//   string os_context::get_command_line()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      return "";
//
//   }
//
//
//   void os_context::shutdown(bool bIfPowerOff)
//   {
//
//      __UNREFERENCED_PARAMETER(bIfPowerOff);
//
//      throw ::interface_only("this is an interface");
//
//      //return false;
//
//   }
//
//
//   void os_context::reboot()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      //return false;
//
//   }
//
//
//   void os_context::terminate_processes_by_title(const ::string & lpszName)
//   {
//
//      __UNREFERENCED_PARAMETER(lpszName);
//
//      throw ::interface_only("this is an interface");
//
//   }
//
//
//   ::process_identifier_array os_context::module_path_processes_identifiers(const ::scoped_string & scopedstrName)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrName);
//
//      throw ::interface_only("this is an interface");
//
//      return {};
//
//   }
//
//
//   ::process_identifier_array os_context::title_processes_identifiers(const ::scoped_string & scopedstrName)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrName);
//
//      throw ::interface_only("this is an interface");
//
//      return {};
//
//   }
//
//
//   ::process_identifier os_context::current_process_identifier()
//   {
//
//      throw ::interface_only("this is an interface");
//
//      return -1;
//
//   }
//
//
//   ::file::path os_context::process_identifier_module_path(::process_identifier dwPid)
//   {
//
//      __UNREFERENCED_PARAMETER(dwPid);
//
//      throw ::interface_only("this is an interface");
//
//      return {};
//
//   }
//
//
//   ::process_identifier_array os_context::processes_identifiers()
//   {
//
//      return node()->processes_identifiers();
//
//   }
//
//
////#ifdef WINDOWS
////
////   ::file::path os_context::get_module_path(HMODULE hmodule)
////   {
////      __UNREFERENCED_PARAMETER(hmodule);
////      throw ::interface_only("this is an interface");
////   }
////
////#endif
//
//
//
//   ::payload os_context::connection_settings_get_auto_detect()
//   {
//
//      return success;
//
//   }
//
//
//   ::payload os_context::connection_settings_get_auto_config_url()
//   {
//
//      return error_failed;
//
//   }
//
//
//   void os_context::link_open(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrProfile)
//   {
//
//      node()->open_url(strUrl);
//
////      file_open(strUrl);
//      //{
//
//      //   return error_failed;
//
//      //}
//
//      //return success;
//
//   }
//
//
//   void os_context::local_machine_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrKey);
//      __UNREFERENCED_PARAMETER(pathExecutable);
//
//      //return false;
//
//   }
//
//
//   void os_context::local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrKey);
//      __UNREFERENCED_PARAMETER(pathExecutable);
//
//      //return false;
//
//   }
//
//
//   void os_context::current_user_set_run(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrKey);
//      __UNREFERENCED_PARAMETER(pathExecutable);
//
//      //return false;
//
//   }
//
//
//   void os_context::current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::file::path & pathExecutable, const ::string& pszArguments, bool bSet)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrKey);
//      __UNREFERENCED_PARAMETER(pathExecutable);
//
//      //return false;
//
//   }
//
//
//   void os_context::defer_register_ca2_plugin_for_mozilla()
//   {
//
//      //return false;
//
//   }
//
//
//   void os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::scoped_string & scopedstrExtension)
//   {
//
//      __UNREFERENCED_PARAMETER(straKey);
//      __UNREFERENCED_PARAMETER(scopedstrExtension);
//
//      //return false;
//
//   }
//
//
//   void os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::scoped_string & scopedstrExtension)
//   {
//
//      __UNREFERENCED_PARAMETER(straCommand);
//      __UNREFERENCED_PARAMETER(scopedstrExtension);
//
//      //return false;
//
//   }
//
//
//   void os_context::file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrExtension);
//      __UNREFERENCED_PARAMETER(scopedstrExtensionNamingClass);
//      __UNREFERENCED_PARAMETER(scopedstrIconPath);
//
//      //return false;
//
//   }
//
//
//   void os_context::file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrExtension);
//      __UNREFERENCED_PARAMETER(scopedstrExtensionNamingClass);
//      __UNREFERENCED_PARAMETER(scopedstrCommand);
//      __UNREFERENCED_PARAMETER(scopedstrParam);
//
//      //return false;
//
//   }
//
//
//   void os_context::file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
//   {
//
//      __UNREFERENCED_PARAMETER(scopedstrExtension);
//      __UNREFERENCED_PARAMETER(strExtensionNamingClass);
//      __UNREFERENCED_PARAMETER(strCommand);
//      __UNREFERENCED_PARAMETER(strParam);
//
//      //return false;
//
//   }
//
//
//   /// Windows (IE), macOS (Safari), Linux (Firefox, oder...)
//   /// Remark: it is not default browser (necessarily)
//   void os_context::native_full_web_browser(const ::string & pcsz)
//
//   {
//
//      throw ::not_implemented();
//
//      //return false;
//
//   }
//
//   /// Windows (Edge), fallback to native_full_web_browser
//   /// Remark: it is not default browser (necessarily)
//   void os_context::native_modern_web_browser(const ::string & pcsz)
//
//   {
//
//      native_full_web_browser(pcsz);
//
//
//   }
//
//
//   void os_context::enable_service()
//   {
//
//
//      throw ::interface_only();
//
//
//      //return false;
//
//
//   }
//
//
//   void os_context::disable_service()
//   {
//
//
//      throw ::interface_only();
//
//
//      //return false;
//
//
//   }
//
//
//   void os_context::start_service()
//   {
//
//
//      throw ::interface_only();
//
//
//      //return false;
//
//
//   }
//
//
//   void os_context::stop_service()
//   {
//
//
//      throw ::interface_only();
//
//
//      //return false;
//
//
//   }
//
//
//   void os_context::enable_service(const ::scoped_string & scopedstrServiceName,const ::scoped_string & scopedstrDisplayName,const ::scoped_string & scopedstrCommand,const ::scoped_string & scopedstrUser,const ::scoped_string & scopedstrPass)
//   {
//
//
//      throw ::interface_only();
//
//
//   }
//
//
//   void os_context::disable_service(const ::scoped_string & scopedstrServiceName)
//   {
//
//
//      throw ::interface_only();
//
//
//   }
//
//
//   void os_context::start_service(const ::scoped_string & scopedstrServiceName)
//   {
//
//
//      throw ::interface_only();
//
//
//   }
//
//
//   void os_context::stop_service(const ::scoped_string & scopedstrServiceName)
//   {
//
//
//      throw ::interface_only();
//
//
//   }
//
//
////#ifdef WINDOWS
////
////   DECLSPEC_NO_RETURN void os_context::raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags)
////   {
////
////
////   }
////
////#endif
//
//
//   bool os_context::is_remote_session()
//   {
//
//      return false;
//
//   }
//
//
//   void os_context::set_file_status(const ::file::path & path, const ::file::file_status& status)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   //void os_context::edit_link_target(const ::file::path & path, const ::file::path & pathLink)
//   //{
//
//   //   throw ::exception(error_interface_only);
//
//   //}
//
//
//   //void os_context::edit_link_folder(const ::file::path & path, const ::file::path & pathLink)
//   //{
//
//   //   throw ::exception(error_interface_only);
//
//   //}
//
//
//   //void os_context::edit_link_icon(const ::file::path& path, int iIcon, const ::file::path& pathLink)
//   //{
//
//   //   throw ::exception(error_interface_only);
//
//   //}
//
//
////   ::pointer < ::file::link > os_context::resolve_link(const ::file::path & path, ::file::e_link elink)
////   {
////
////      if(path.case_insensitive_ends(".desktop"))
////      {
////
////         auto stra = file()->lines(path);
////
////         stra.case_insensitive_filter_begins("exec=");
////
////         if(stra.get_size() <= 0)
////         {
////
////            return nullptr;
////
////         }
////
////         auto plink = __create_new < ::file::link >();
////
////         string strLink = stra[0];
////
////         strLink.case_insensitive_begins_eat("exec=");
////
////         while(true)
////         {
////
////            bool bAte = false;
////
////            if(strLink.case_insensitive_ends_eat("%u"))
////            {
////
////               bAte = true;
////
////            }
////
////            if(!bAte)
////            {
////
////               break;
////
////            }
////
////         }
////
////         strLink.trim();
////
////         strLink.trim("\"");
////
////         strLink.trim("\'");
////
////         plink->m_pathFolder = ::file::path(strLink).folder();
////
////         plink->m_pathTarget = strLink;
////
////         return plink;
////
////      }
////      else
////      {
////
////
////#ifndef WINDOWS
////
////
////#if 0
////
////
////
////      if (::is_null(scopedstr))
////      {
////
////         return false;
////
////      }
////
////
////
////
////      char* pszRealPath = ::realpath(scopedstr, NULL);
////
////      if (scopedstrRealPath == NULL)
////      {
////
////         return false;
////
////      }
////
////      if (strcmp(scopedstr, pszRealPath) == 0)
////      {
////
////         ::free(scopedstrRealPath);
////
////         return false;
////
////      }
////
////      try
////      {
////
////         path = pszRealPath;
////
////      }
////      catch (...)
////      {
////
////      }
////
////      ::free(scopedstrRealPath);
////
////      return true;
////
////   }
////
////#else
////
////         auto plink = __create_new < ::file::link >();
////
////         string strLink;
////
////         char * psz = strLink.get_buffer(4096);
////
////         int count = (int) readlink(path, psz, 4096);
////
////         if (count < 0)
////         {
////
////            strLink.release_buffer(0);
////
////            if (elink & ::file::e_link_target)
////            {
////
////               plink->m_pathTarget = path;
////
////            }
////
////            if(elink & ::file::e_link_folder)
////            {
////
////               plink->m_pathFolder = ::file::path(strLink).folder();
////
////            }
////
////            return plink;
////
////         }
////
////         strLink.release_buffer(count);
////
////         if (elink & ::file::e_link_target)
////         {
////
////            plink->m_pathTarget = path;
////
////         }
////
////         if (elink & ::file::e_link_folder)
////         {
////
////            plink->m_pathFolder = ::file::path(strLink).folder();
////
////         }
////
////         return plink;
////
////#endif
////
////#endif
////
////      }
////
////      return nullptr;
////
////   }
//
//
//   bool os_context::has_alias_in_path(const ::scoped_string & scopedstr, bool bNoUI, bool bNoMount)
//   {
//
//      ::file::path pathSource(scopedstr);
//
//      ::file::path_array patha;
//
//      ///::file::path_array pathaRelative;
//
//      ascendants_path(pathSource, patha, nullptr);
//
//      for (::collection::index i = 0; i < patha.get_count(); i++)
//      {
//
//         ::file::path path = patha[i];
//
//         if (is_alias(path))
//         {
//
//            return true;
//
//         }
//
//      }
//
//      return false;
//
//   }
//
//
//   bool os_context::is_alias(const ::file::path & path)
//   {
//
//      return m_papplication->os_is_alias(path);
//
//   }
//
//
//   void os_context::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
//   {
//
//      ::string_array stra;
//
//      //stra.add("_inheaven_1920x1080_o.JPG");
//      //stra.add("02209_stratosphere_1920x1080_o.JPG");
//      //stra.add("Bamboo Weathered Standard.jpg");
//
//      stra.add("bambu1.jpg");
//      stra.add("bambu2.jpg");
//      stra.add("bambu3.jpg");
//      stra.add("bambu33.png");
//      stra.add("bambu4.jpg");
//
//      ::file::path pathFolder;
//
//      pathFolder = "https://ca2.network/image/cc/ca2core/bkimageoftheday/common/";
//
//      pfileset->m_listingAddUp.m_eflag = ::file::e_flag_file;
//
//      for (auto & str : stra)
//      {
//
//         ::file::path path = pathFolder / (str + string("?sessid=noauth"));
//
//         path.m_iDir = 0;
//
//         pfileset->m_listingAddUp.defer_add(path);
//
//      }
//
//      //return true;
//
//   }
//
//
//   void os_context::set_dark_mode(bool bDarkMode)
//   {
//
//      //throw ::interface_only();
//
//      node()->set_dark_mode(bDarkMode);
//
//   }
//
//
//   void os_context::file_open(const ::file::path & pathTarget, const ::scoped_string & scopedstrParams, const ::file::path & pathFolder)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   void os_context::hidden_start(const ::file::path& pathTarget, const ::scoped_string & scopedstrParams, const ::file::path& pathFolder)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   void os_context::hidden_run(const class time & timeWait, const ::file::path& pathTarget, const ::scoped_string & scopedstrParams, const ::file::path& pathFolder)
//   {
//
//      throw ::interface_only();
//
//   }
//
//
//   string os_context::get_default_browser()
//   {
//
//      string strId;
//
//      ::file::path path;
//
//      string strParam;
//
//      get_default_browser(strId, path, strParam);
//
//      //if (!)
//      //{
//
//      //   return "";
//
//      //}
//
//      return strId;
//
//   }
//
//
//   void os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
//   {
//
//      __UNREFERENCED_PARAMETER(strId);
//      __UNREFERENCED_PARAMETER(path);
//      __UNREFERENCED_PARAMETER(strParam);
//
//      //return false;
//
//   }
//
//
//   void os_context::set_default_browser()
//   {
//
//      //return false;
//
//   }
//
//
//   void os_context::set_file_extension_mime_type(::get_file_extension_mime_type * pgetfileextensionmimetype)
//   {
//
//      string_array straExtension;
//
//      string_array straMimeType;
//
//      pgetfileextensionmimetype->file_extension_mime_type(straExtension, straMimeType);
//
//      set_file_extension_mime_type(straExtension, straMimeType);
//
//   }
//
//
//   void os_context::set_file_extension_mime_type(string_array & straExtension, string_array & straMimeType)
//   {
//
//      __UNREFERENCED_PARAMETER(straExtension);
//      __UNREFERENCED_PARAMETER(straMimeType);
//
//      //return false;
//
//   }
//
//
//   void os_context::register_user_auto_start(const ::scoped_string & scopedstrAppId, const ::file::path & pathExecutable, const ::scoped_string & scopedstrArguments, bool bRegister)
//   {
//
//      throw interface_only();
//
//   }
//
//
//   bool os_context::is_user_auto_start(const ::scoped_string & scopedstrAppId)
//   {
//
//      throw interface_only();
//
//      return false;
//
//   }
//
//
//   ::file::path os_context::get_app_path(const ::scoped_string & scopedstrApp)
//   {
//
//      return strApp;
//
//   }
//
//
//   void os_context::on_process_request(::request * prequest)
//   {
//
//      request(prequest);
//
//   }
//
//
//   //void os_context::browse_file_open(::property_set & set)
//   //{
//
//   //   throw ::interface_only();
//
//   //   //return false;
//
//   //}
//
//
//   //void os_context::browse_file_save(::property_set & set)
//   //{
//
//   //   throw ::interface_only();
//
//   //   //return false;
//
//   //}
//
//
//   //void os_context::browse_folder(::property_set & set)
//   //{
//
//   //   throw ::interface_only();
//
//   //   //return false;
//
//   //}
//
//   //
//   //void os_context::browse_file_or_folder(::property_set & set)
//   //{
//
//   //   throw ::interface_only();
//
//   //   //return false;
//
//   //}
//
//
//   void os_context::list_process(::file::path_array& patha, ::process_identifier_array& uaPid)
//   {
//
//      ASSERT(sizeof(unsigned int) == sizeof(unsigned int));
//
//      uaPid = this->processes_identifiers();
//
//      patha.set_size(uaPid.get_count());
//
//      for (::collection::index i = 0; i < uaPid.get_count(); i++)
//      {
//
//         patha[i] = process_identifier_module_path(uaPid[i]);
//
//      }
//
//   }
//
//
//   ::file::path_array os_context::list_process_path()
//   {
//
//      ::file::path_array patha;
//
//      ::process_identifier_array uaPid;
//
//      list_process(patha, uaPid);
//
//      return patha;
//
//   }
//
//
//void os_context::broadcast_environment_variable_change()
//{
//
//   //return ::success_none;
//
//}
//
//
//void os_context::set_this_application_as_default_for_file_extension(const ::scoped_string & scopedstrExtension)
//{
//
//
//}
//
//
//string os_context::get_file_extension_mime_type(const ::scoped_string & scopedstrExtension)
//{
//
//   if (strExtension == "iso")
//   {
//      return "application/octetstream";
//   }
//   else if (strExtension == "mp3")
//   {
//      return "audio/mpeg";
//   }
//   else if (strExtension == "exe")
//   {
//      return "application/x-msdownload";
//   }
//   else if (strExtension == "spa")
//   {
//      return "application/x-spa";
//   }
//   else if (strExtension == "mid")
//   {
//      return "audio/midi";
//   }
//   else if (strExtension == "js")
//   {
//      return "text/javascript";
//   }
//   else if (strExtension == "css")
//   {
//      return "text/css";
//   }
//   else if (strExtension == "xpi")
//   {
//      return "application/x-xpinstall";
//   }
//   else if (strExtension == "ttf")
//   {
//      return "font/ttf";
//   }
//   else if (strExtension == "ogv")
//   {
//      return "video/ogg";
//   }
//   else if (strExtension == "mp4")
//   {
//      return "video/mp4";
//   }
//   else if (strExtension == "webm")
//   {
//      return "video/webm";
//   }
//   else if (strExtension == "zip")
//   {
//      return "application/x-zip-compressed";
//   }
//   else if (strExtension == "crx")
//   {
//      return "application/x-chrome-extension";
//   }
//   else if (strExtension == "swf")
//   {
//      return "application/x-shockwave-flash";
//   }
//   else if (strExtension == "cab")
//   {
//      return "application/vnd.ms-cab-compressed";
//   }
//   else if (strExtension == "jar")
//   {
//      return "application/x-jar";
//   }
//   else if (strExtension == "jpg")
//   {
//      return "image/jpeg";
//   }
//   else if (strExtension == "png")
//   {
//      return "image/png";
//   }
//   else if (strExtension == "gif")
//   {
//      return "image/gif";
//   }
//   else if (strExtension == "svg")
//   {
//      return "image/svg+xml";
//   }
//   else if (strExtension == "ttf")
//   {
//      return "application/x-font-ttf";
//   }
//   else if (strExtension == "otf")
//   {
//      return "application/x-font-opentype";
//   }
//   else if (strExtension == "woff")
//   {
//      return "application/x-font-woff";
//   }
//   else if (strExtension == "eot")
//   {
//      return "application/vnd.ms-fontobject";
//   }
//   else if (strExtension == "md5")
//   {
//      return "text/plain";
//   }
//   else if (strExtension == "html")
//   {
//      return "text/html";
//   }
//   else if (strExtension == "htm")
//   {
//      return "text/html";
//   }
//   else if (strExtension == "rdf")
//   {
//      return "application/rdf+xml";
//   }
//   else
//   {
//      return "";
//   }
//
//}




