#include "framework.h"
#ifdef LINUX
#include <unistd.h>
#endif

//
//namespace aura
//{


   os_context::os_context()
   {
   }

   os_context::~os_context()
   {
   }


   string os_context::get_command_line()
   {

      __throw(error_interface_only, "this is an interface");

      return "";

   }


   bool os_context::shutdown(bool bIfPowerOff)
   {
      UNREFERENCED_PARAMETER(bIfPowerOff);
      __throw(error_interface_only, "this is an interface");
      return false;
   }

   bool os_context::reboot()
   {
      __throw(error_interface_only, "this is an interface");
      return false;
   }

   void os_context::terminate_processes_by_title(const char * lpszName)
   {
      UNREFERENCED_PARAMETER(lpszName);
      __throw(error_interface_only, "this is an interface");
   }

   bool os_context::get_pid_by_path(const char * lpszName, u32 & dwPid)
   {
      UNREFERENCED_PARAMETER(lpszName);
      UNREFERENCED_PARAMETER(dwPid);
      __throw(error_interface_only, "this is an interface");
      return false;
   }

   bool os_context::get_pid_by_title(const char * lpszName, u32 & dwPid)
   {
      UNREFERENCED_PARAMETER(lpszName);
      UNREFERENCED_PARAMETER(dwPid);
      __throw(error_interface_only, "this is an interface");
      return false;
   }

   int os_context::get_pid()
   {
      __throw(error_interface_only, "this is an interface");
      return -1;
   }

   ::file::path os_context::get_process_path(u32 dwPid)
   {
      UNREFERENCED_PARAMETER(dwPid);
      __throw(error_interface_only, "this is an interface");
      return "";
   }

   void os_context::get_all_processes(u32_array & dwa )
   {
      UNREFERENCED_PARAMETER(dwa);
      __throw(error_interface_only, "this is an interface");
   }

#ifdef WINDOWS

   ::file::path os_context::get_module_path(HMODULE hmodule)
   {
      UNREFERENCED_PARAMETER(hmodule);
      __throw(error_interface_only, "this is an interface");
   }

#endif


   ::payload os_context::connection_settings_get_auto_detect()
   {

      return success;

   }


   ::payload os_context::connection_settings_get_auto_config_url()
   {

      return error_failed;

   }


   ::e_status     os_context::link_open(string strUrl)
   {

      if (!file_open(strUrl))
      {

         return error_failed;

      }

      return success;

   }


   bool os_context::local_machine_set_run(const char * pszKey, const char * pszCommand, bool bSet)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os_context::local_machine_set_run_once(const char * pszKey, const char * pszCommand, bool bSet)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os_context::current_user_set_run(const char * pszKey, const char * pszCommand, bool bSet)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os_context::current_user_set_run_once(const char * pszKey, const char * pszCommand, bool bSet)
   {

      UNREFERENCED_PARAMETER(pszKey);
      UNREFERENCED_PARAMETER(pszCommand);

      return false;

   }

   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {

      return false;

   }

   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straKey);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }

   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const char * pszExtension)
   {

      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(pszExtension);

      return false;

   }


   bool os_context::file_association_set_default_icon(const char * pszExtension, const char * pszExtensionNamingClass, const char * pszIconPath)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszIconPath);

      return false;

   }


   bool os_context::file_association_set_shell_open_command(const char * pszExtension, const char * pszExtensionNamingClass,  const char * pszCommand, const char * pszParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(pszExtensionNamingClass);
      UNREFERENCED_PARAMETER(pszCommand);
      UNREFERENCED_PARAMETER(pszParam);

      return false;

   }


   bool os_context::file_association_get_shell_open_command(const char * pszExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      UNREFERENCED_PARAMETER(pszExtension);
      UNREFERENCED_PARAMETER(strExtensionNamingClass);
      UNREFERENCED_PARAMETER(strCommand);
      UNREFERENCED_PARAMETER(strParam);

      return false;

   }


   /// Windows (IE), macOS (Safari), Linux (Firefox, oder...)
   /// Remark: it is not default browser (necessarily)
   bool os_context::native_full_web_browser(const char * pcsz)

   {

      __throw(error_not_implemented);

      return false;

   }

   /// Windows (Edge), fallback to native_full_web_browser
   /// Remark: it is not default browser (necessarily)
   bool os_context::native_modern_web_browser(const char * pcsz)

   {

      return native_full_web_browser(pcsz);


   }


   ::e_status os_context::create_service()
   {


      ::exception::throw_not_implemented();


      return false;


   }


   ::e_status os_context::erase_service()
   {


      ::exception::throw_not_implemented();


      return false;


   }


   ::e_status os_context::start_service()
   {


      ::exception::throw_not_implemented();


      return false;


   }


   ::e_status os_context::stop_service()
   {


      ::exception::throw_not_implemented();


      return false;


   }


   bool os_context::create_service(const string & strServiceName,const string & strDisplayName,const string & strCommand,const string & strUser,const string & strPass)
   {


      ::exception::throw_not_implemented();


      return false;


   }


   bool os_context::erase_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented();


      return false;


   }


   bool os_context::start_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented();


      return false;


   }


   bool os_context::stop_service(const string & strServiceName)
   {


      ::exception::throw_not_implemented();


      return false;


   }


#ifdef WINDOWS

   DECLSPEC_NO_RETURN void os_context::raise_exception(u32 dwExceptionCode, u32 dwExceptionFlags)
   {


   }

#endif


   bool os_context::is_remote_session()
   {

      return false;

   }


   void os_context::set_file_status(const char * pszFileName, const ::file::file_status& status)

   {

      ::exception::throw_interface_only();

   }


   bool os_context::resolve_link(::file::path & path, const string & strSource, string * pstrDirectory, string * pstrParams, ::user::primitive * puiMessageParentOptional)
   {

      if(::str::ends_ci(strSource, ".desktop"))
      {

         string str = pcontext->m_papexcontext->file().as_string(strSource);

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


   bool os_context::initialize_wallpaper_fileset(::file::set* pfileset, bool bAddSearch)
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

      pathFolder = "https://server.ca2.cc/image/cc/ca2core/bkimageoftheday/common/";

      for (auto & str : stra)
      {

         ::file::path path = pathFolder / (str + string("?sessid=noauth"));

         pfileset->m_straFileAddUp.add(path);

      }

      return true;

   }


   bool os_context::file_open(::file::path strSrc, string strParams, string strFolder)
   {

      return false;

   }


   string os_context::get_default_browser()
   {

      string strId;

      ::file::path path;

      string strParam;

      if (!get_default_browser(strId, path, strParam))
      {

         return "";

      }

      return strId;

   }


   bool os_context::get_default_browser(string & strId, ::file::path & path, string & strParam)
   {

      UNREFERENCED_PARAMETER(strId);
      UNREFERENCED_PARAMETER(path);
      UNREFERENCED_PARAMETER(strParam);

      return false;

   }


   bool os_context::set_default_browser()
   {

      return false;

   }


   bool os_context::add_default_program(string_array & straExtension, string_array & straMimeType)
   {

      UNREFERENCED_PARAMETER(straExtension);
      UNREFERENCED_PARAMETER(straMimeType);

      return false;

   }


   bool os_context::register_user_auto_start(string strId, string strCommand, bool bRegister)
   {

      return false;

   }


   bool os_context::is_user_auto_start(string strId)
   {

      return false;

   }


   ::file::path os_context::get_app_path(const string & strApp)
   {

      return strApp;

   }


   void os_context::on_process_command(::create * pcommand)
   {

      UNREFERENCED_PARAMETER(pcommand);

   }


   bool os_context::browse_file_open(::user::interaction* pinteraction, property_set & set)
   {

      __throw(error_interface_only);

      return false;

   }


   bool os_context::browse_file_save(::user::interaction* pinteraction, property_set & set)
   {

      __throw(error_interface_only);

      return false;

   }


   bool os_context::browse_folder(::user::interaction* pinteraction, property_set & set)
   {

      __throw(error_interface_only);

      return false;

   }

   bool os_context::browse_file_or_folder(::user::interaction* pinteraction, property_set & set)
   {

      __throw(error_interface_only);

      return false;

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


   ::icon_result os_context::load_icon(const ::payload & varFile)
   {


      return error_failed;

   }

//
//} // namespace aura
//
//

   void os_context::enum_draw2d_fonts(::write_text::font_enum_item_array& itema)
   {


   }