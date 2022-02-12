#include "framework.h"
#if defined(LINUX) || defined(__APPLE__)
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


   string os_context::get_command_line()
   {

      throw ::interface_only("this is an interface");

      return "";

   }


   void os_context::shutdown(bool bIfPowerOff)
   {
      
      __UNREFERENCED_PARAMETER(bIfPowerOff);

      throw ::interface_only("this is an interface");

      //return false;

   }


   void os_context::reboot()
   {
      
      throw ::interface_only("this is an interface");
      
      //return false;

   }


   void os_context::terminate_processes_by_title(const ::string & lpszName)
   {
      
      __UNREFERENCED_PARAMETER(lpszName);

      throw ::interface_only("this is an interface");

   }


   bool os_context::path_pid(u32& dwPid, const ::string & lpszName)
   {

      __UNREFERENCED_PARAMETER(lpszName);
      __UNREFERENCED_PARAMETER(dwPid);

      throw ::interface_only("this is an interface");

      return false;

   }


   bool os_context::title_pid(u32& dwPid, const ::string & lpszName)
   {

      __UNREFERENCED_PARAMETER(lpszName);
      __UNREFERENCED_PARAMETER(dwPid);
      
      throw ::interface_only("this is an interface");
      return false;

   }


   int os_context::get_pid()
   {
      
      throw ::interface_only("this is an interface");

      return -1;

   }

   
   ::file::path os_context::get_process_path(u32 dwPid)
   {
      
      __UNREFERENCED_PARAMETER(dwPid);

      throw ::interface_only("this is an interface");

      return "";

   }

   
   void os_context::get_all_processes(u32_array & dwa )
   {

      __UNREFERENCED_PARAMETER(dwa);

      throw ::interface_only("this is an interface");

   }


//#ifdef WINDOWS
//
//   ::file::path os_context::get_module_path(HMODULE hmodule)
//   {
//      __UNREFERENCED_PARAMETER(hmodule);
//      throw ::interface_only("this is an interface");
//   }
//
//#endif



   ::payload os_context::connection_settings_get_auto_detect()
   {

      return success;

   }


   ::payload os_context::connection_settings_get_auto_config_url()
   {

      return error_failed;

   }


   void os_context::link_open(const string & strUrl, const string & strProfile)
   {

      file_open(strUrl);
      //{

      //   return error_failed;

      //}

      //return success;

   }


   void os_context::local_machine_set_run(const ::string & pszKey, const ::string & pszCommand, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pszCommand);

      //return false;

   }


   void os_context::local_machine_set_run_once(const ::string & pszKey, const ::string & pszCommand, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pszCommand);

      //return false;

   }

   
   void os_context::current_user_set_run(const ::string & pszKey, const ::string & pszCommand, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pszCommand);

      //return false;

   }

   
   void os_context::current_user_set_run_once(const ::string & pszKey, const ::string & pszCommand, const ::string& pszArguments, bool bSet)
   {

      __UNREFERENCED_PARAMETER(pszKey);
      __UNREFERENCED_PARAMETER(pszCommand);

      //return false;

   }


   void os_context::defer_register_ca2_plugin_for_mozilla()
   {

      //return false;

   }

   
   void os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::string & pszExtension)
   {

      __UNREFERENCED_PARAMETER(straKey);
      __UNREFERENCED_PARAMETER(pszExtension);

      //return false;

   }


   void os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::string & pszExtension)
   {

      __UNREFERENCED_PARAMETER(straCommand);
      __UNREFERENCED_PARAMETER(pszExtension);

      //return false;

   }


   void os_context::file_association_set_default_icon(const ::string & pszExtension, const ::string & pszExtensionNamingClass, const ::string & pszIconPath)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      __UNREFERENCED_PARAMETER(pszIconPath);

      //return false;

   }


   void os_context::file_association_set_shell_open_command(const ::string & pszExtension, const ::string & pszExtensionNamingClass,  const ::string & pszCommand, const ::string & pszParam)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      __UNREFERENCED_PARAMETER(pszCommand);
      __UNREFERENCED_PARAMETER(pszParam);

      //return false;

   }


   void os_context::file_association_get_shell_open_command(const ::string & pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      __UNREFERENCED_PARAMETER(pszExtension);
      __UNREFERENCED_PARAMETER(strExtensionNamingClass);
      __UNREFERENCED_PARAMETER(strCommand);
      __UNREFERENCED_PARAMETER(strParam);

      //return false;

   }


   /// Windows (IE), macOS (Safari), Linux (Firefox, oder...)
   /// Remark: it is not default browser (necessarily)
   void os_context::native_full_web_browser(const ::string & pcsz)

   {

      throw ::not_implemented();

      //return false;

   }

   /// Windows (Edge), fallback to native_full_web_browser
   /// Remark: it is not default browser (necessarily)
   void os_context::native_modern_web_browser(const ::string & pcsz)

   {

      native_full_web_browser(pcsz);


   }


   void os_context::enable_service()
   {


      throw ::interface_only();


      //return false;


   }


   void os_context::disable_service()
   {


      throw ::interface_only();


      //return false;


   }


   void os_context::start_service()
   {


      throw ::interface_only();


      //return false;


   }


   void os_context::stop_service()
   {


      throw ::interface_only();


      //return false;


   }


   void os_context::enable_service(const ::string & strServiceName,const ::string & strDisplayName,const ::string & strCommand,const ::string & strUser,const ::string & strPass)
   {


      throw ::interface_only();


   }


   void os_context::disable_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


   void os_context::start_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


   void os_context::stop_service(const ::string & strServiceName)
   {


      throw ::interface_only();


   }


//#ifdef WINDOWS
//
//   DECLSPEC_NO_RETURN void os_context::raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags)
//   {
//
//
//   }
//
//#endif


   bool os_context::is_remote_session()
   {

      return false;

   }


   void os_context::set_file_status(const ::string & pszFileName, const ::file::file_status& status)

   {

      throw ::interface_only();

   }


   void os_context::edit_link_target(const ::file::path & path, const ::file::path & pathLink)
   {

      throw ::exception(error_interface_only);

   }


   void os_context::edit_link_folder(const ::file::path & path, const ::file::path & pathLink)
   {

      throw ::exception(error_interface_only);

   }


   bool os_context::resolve_link(::file::path & path, const ::string & strSource, string * pstrDirectory, string * pstrParams)
   {

      if(::str::ends_ci(strSource, ".desktop"))
      {

         string str = m_pcontext->m_papexcontext->file().as_string(strSource);

         string_array stra;

         stra.add_lines(str);

         stra.filter_begins_ci("exec=");

         if(stra.get_size() <= 0)
         {

            return false;

         }

         string strLink = stra[0];

         strLink.begins_eat_ci("exec=");

         while(true)
         {

            bool bAte = false;

            if(strLink.ends_eat_ci("%u"))
            {

               bAte = true;

            }

            if(!bAte)
            {

               break;

            }

         }

         strLink.trim();

         strLink.trim("\"");

         strLink.trim("\'");

         if (::is_set(pstrDirectory))
         {

            *pstrDirectory = ::file::path(strLink).folder();

         }

         path = strLink;

         return true;

      }
      else
      {


#ifndef WINDOWS

         string strLink;

         char * psz = strLink.get_string_buffer(4096);

         int count = (int) readlink(strSource, psz, 4096);

         if (count < 0)
         {

            strLink.release_string_buffer(0);

            strLink = strSource;

            if(pstrDirectory != nullptr)
            {

               *pstrDirectory = ::file::path(strLink).folder();

            }

            path = strLink;

            return true;

         }

         strLink.release_string_buffer(count);

         if(pstrDirectory != nullptr)
         {

            *pstrDirectory = ::file::path(strLink).folder();

         }

         path = strLink;

         return true;

#endif

      }

      return false;

   }

   
   bool os_context::has_alias_in_path(const char * psz, bool bNoUI, bool bNoMount)
   {

      throw interface_only();

      return false;

   }


   bool os_context::is_alias(const char * psz)
   {

      throw interface_only();

      return false;

   }


   void os_context::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
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

      pathFolder = "https://server.ca2.software/image/cc/ca2core/bkimageoftheday/common/";

      for (auto & str : stra)
      {

         ::file::path path = pathFolder / (str + string("?sessid=noauth"));

         pfileset->m_listingAddUp.add(path);

      }

      //return true;

   }


   void os_context::set_dark_mode(bool bDarkMode)
   {

      throw ::interface_only();

      throw ::interface_only();

   }


   void os_context::file_open(::file::path strSrc, string strParams, string strFolder)
   {

      //return false;

   }


   string os_context::get_default_browser()
   {

      string strId;

      ::file::path path;

      string strParam;

      get_default_browser(strId, path, strParam);

      //if (!)
      //{

      //   return "";

      //}

      return strId;

   }


   void os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      __UNREFERENCED_PARAMETER(strId);
      __UNREFERENCED_PARAMETER(path);
      __UNREFERENCED_PARAMETER(strParam);

      //return false;

   }


   void os_context::set_default_browser()
   {

      //return false;

   }


   void os_context::add_default_program(string_array & straExtension, string_array & straMimeType)
   {

      __UNREFERENCED_PARAMETER(straExtension);
      __UNREFERENCED_PARAMETER(straMimeType);

      //return false;

   }


   void os_context::register_user_auto_start(const string & strId, const string & strCommand, const string & strArguments, bool bRegister)
   {

      //return false;

   }


   bool os_context::is_user_auto_start(string strId)
   {

      return false;

   }


   ::file::path os_context::get_app_path(const ::string & strApp)
   {

      return strApp;

   }


   void os_context::on_process_command(::create * pcommand)
   {

      __UNREFERENCED_PARAMETER(pcommand);

   }


   void os_context::browse_file_open(property_set & set)
   {

      throw ::interface_only();

      //return false;

   }


   void os_context::browse_file_save(property_set & set)
   {

      throw ::interface_only();

      //return false;

   }


   void os_context::browse_folder(property_set & set)
   {

      throw ::interface_only();

      //return false;

   }

   
   void os_context::browse_file_or_folder(property_set & set)
   {

      throw ::interface_only();

      //return false;

   }


   void os_context::list_process(::file::patha & patha, u32_array & uaPid)
   {


   }


   ::file::patha os_context::list_process_path()
   {

      ::file::patha patha;

      u32_array uaPid;

      list_process(patha, uaPid);

      return patha;

   }


void os_context::broadcast_environment_variable_change()
{

   //return ::success_none;

}



