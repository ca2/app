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

      throw ::interface_only("this is an interface");

      return "";

   }


   bool os_context::shutdown(bool bIfPowerOff)
   {
      __UNREFERENCED_PARAMETER(bIfPowerOff);
      throw ::interface_only("this is an interface");
      return false;
   }

   bool os_context::reboot()
   {
      throw ::interface_only("this is an interface");
      return false;
   }

   void os_context::terminate_processes_by_title(const ::string & lpszName)
   {
      __UNREFERENCED_PARAMETER(lpszName);
      throw ::interface_only("this is an interface");
   }

   bool os_context::get_pid_by_path(const ::string & lpszName, unsigned int & dwPid)
   {
      __UNREFERENCED_PARAMETER(lpszName);
      __UNREFERENCED_PARAMETER(dwPid);
      throw ::interface_only("this is an interface");
      return false;
   }

   bool os_context::get_pid_by_title(const ::string & lpszName, unsigned int & dwPid)
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

   ::file::path os_context::get_process_path(unsigned int dwPid)
   {
      __UNREFERENCED_PARAMETER(dwPid);
      throw ::interface_only("this is an interface");
      return "";
   }

   void os_context::get_all_processes(unsigned_int_array & dwa )
   {
      __UNREFERENCED_PARAMETER(dwa);
      throw ::interface_only("this is an interface");
   }

#ifdef WINDOWS

   ::file::path os_context::get_module_path(HMODULE hmodule)
   {
      __UNREFERENCED_PARAMETER(hmodule);
      throw ::interface_only("this is an interface");
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


   void     os_context::link_open(string strUrl)
   {

      if (!file_open(strUrl))
      {

         return error_failed;

      }

      return success;

   }


   bool os_context::local_machine_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      __UNREFERENCED_PARAMETER(scopedstrKey);
      __UNREFERENCED_PARAMETER(scopedstrCommand);

      return false;

   }

   bool os_context::local_machine_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      __UNREFERENCED_PARAMETER(scopedstrKey);
      __UNREFERENCED_PARAMETER(scopedstrCommand);

      return false;

   }

   bool os_context::current_user_set_run(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      __UNREFERENCED_PARAMETER(scopedstrKey);
      __UNREFERENCED_PARAMETER(scopedstrCommand);

      return false;

   }

   bool os_context::current_user_set_run_once(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrCommand, bool bSet)
   {

      __UNREFERENCED_PARAMETER(scopedstrKey);
      __UNREFERENCED_PARAMETER(scopedstrCommand);

      return false;

   }

   bool os_context::defer_register_ca2_plugin_for_mozilla()
   {

      return false;

   }

   bool os_context::file_extension_get_open_with_list_keys(string_array & straKey, const ::scoped_string & scopedstrExtension)
   {

      __UNREFERENCED_PARAMETER(straKey);
      __UNREFERENCED_PARAMETER(scopedstrExtension);

      return false;

   }

   bool os_context::file_extension_get_open_with_list_commands(string_array & straCommand, const ::scoped_string & scopedstrExtension)
   {

      __UNREFERENCED_PARAMETER(straCommand);
      __UNREFERENCED_PARAMETER(scopedstrExtension);

      return false;

   }


   bool os_context::file_association_set_default_icon(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass, const ::scoped_string & scopedstrIconPath)
   {

      __UNREFERENCED_PARAMETER(scopedstrExtension);
      __UNREFERENCED_PARAMETER(scopedstrExtensionNamingClass);
      __UNREFERENCED_PARAMETER(scopedstrIconPath);

      return false;

   }


   bool os_context::file_association_set_shell_open_command(const ::scoped_string & scopedstrExtension, const ::scoped_string & scopedstrExtensionNamingClass,  const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrParam)
   {

      __UNREFERENCED_PARAMETER(scopedstrExtension);
      __UNREFERENCED_PARAMETER(scopedstrExtensionNamingClass);
      __UNREFERENCED_PARAMETER(scopedstrCommand);
      __UNREFERENCED_PARAMETER(scopedstrParam);

      return false;

   }


   bool os_context::file_association_get_shell_open_command(const ::scoped_string & scopedstrExtension, string & strExtensionNamingClass, string & strCommand, string & strParam)
   {

      __UNREFERENCED_PARAMETER(scopedstrExtension);
      __UNREFERENCED_PARAMETER(strExtensionNamingClass);
      __UNREFERENCED_PARAMETER(strCommand);
      __UNREFERENCED_PARAMETER(strParam);

      return false;

   }


   /// Windows (IE), macOS (Safari), Linux (Firefox, oder...)
   /// Remark: it is not default browser (necessarily)
   bool os_context::native_full_web_browser(const ::string & pcsz)

   {

      throw ::not_implemented();

      return false;

   }

   /// Windows (Edge), fallback to native_full_web_browser
   /// Remark: it is not default browser (necessarily)
   bool os_context::native_modern_web_browser(const ::string & pcsz)

   {

      return native_full_web_browser(pcsz);


   }


   void os_context::create_service()
   {


      throw ::interface_only();


      return false;


   }


   void os_context::erase_service()
   {


      throw ::interface_only();


      return false;


   }


   void os_context::start_service()
   {


      throw ::interface_only();


      return false;


   }


   void os_context::stop_service()
   {


      throw ::interface_only();


      return false;


   }


   bool os_context::create_service(const ::scoped_string & scopedstrServiceName, const ::scoped_string & scopedstrDisplayName, const ::scoped_string & scopedstrCommand, const ::scoped_string & scopedstrUser, const ::scoped_string & scopedstrPass)
   {


      throw ::interface_only();


      return false;


   }


   bool os_context::erase_service(const ::scoped_string & scopedstrServiceName)
   {


      throw ::interface_only();


      return false;


   }


   bool os_context::start_service(const ::scoped_string & scopedstrServiceName)
   {


      throw ::interface_only();


      return false;


   }


   bool os_context::stop_service(const ::scoped_string & scopedstrServiceName)
   {


      throw ::interface_only();


      return false;


   }


#ifdef WINDOWS

   DECLSPEC_NO_RETURN void os_context::raise_exception(unsigned int dwExceptionCode, unsigned int dwExceptionFlags)
   {


   }

#endif


   bool os_context::is_remote_session()
   {

      return false;

   }


   void os_context::set_file_status(const ::scoped_string & scopedstrFileName, const ::file::file_status& status)

   {

      throw ::interface_only();

   }


   bool os_context::resolve_link(::file::path & path, const ::scoped_string & scopedstrSource, string * pstrDirectory, string * pstrParams, ::user::interaction_base * puiMessageParentOptional)
   {

      if(case_insensitive_string_ends(strSource, ".desktop"))
      {

         string str = file()->as_string(strSource);

         string_array stra;

         stra.add_lines(str);

         stra.case_insensitive_filter_begins("exec=");

         if(stra.get_size() <= 0)
         {

            return false;

         }

         string strLink = stra[0];

         strLink.case_insensitive_begins_eat("exec=");

         while(true)
         {

            bool bAte = false;

            if(strLink.case_insensitive_ends_eat("%u"))
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

         char * psz = strLink.get_buffer(4096);

         int count = (int) readlink(strSource, psz, 4096);

         if (count < 0)
         {

            strLink.release_buffer(0);

            strLink = strSource;

            if(pstrDirectory != nullptr)
            {

               *pstrDirectory = ::file::path(strLink).folder();

            }

            path = strLink;

            return true;

         }

         strLink.release_buffer(count);

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

      pathFolder = "https://ca2.network/image/cc/ca2core/bkimageoftheday/common/";

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

      __UNREFERENCED_PARAMETER(strId);
      __UNREFERENCED_PARAMETER(path);
      __UNREFERENCED_PARAMETER(strParam);

      return false;

   }


   bool os_context::set_default_browser()
   {

      return false;

   }


   bool os_context::add_default_program(string_array & straExtension, string_array & straMimeType)
   {

      __UNREFERENCED_PARAMETER(straExtension);
      __UNREFERENCED_PARAMETER(straMimeType);

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


   ::file::path os_context::get_app_path(const ::scoped_string & scopedstrApp)
   {

      return strApp;

   }


   void os_context::on_process_command(::create * pcommand)
   {

      __UNREFERENCED_PARAMETER(pcommand);

   }


   bool os_context::browse_file_open(::user::interaction* pinteraction, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }


   bool os_context::browse_file_save(::user::interaction* pinteraction, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }


   bool os_context::browse_folder(::user::interaction* pinteraction, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }

   bool os_context::browse_file_or_folder(::user::interaction* pinteraction, ::property_set & set)
   {

      throw ::interface_only();

      return false;

   }


   void os_context::list_process(::file::path_array & patha, unsigned_int_array & uaPid)
   {


   }


   ::file::path_array os_context::list_process_path()
   {

      ::file::path_array patha;

      unsigned_int_array uaPid;

      list_process(patha, uaPid);

      return patha;

   }


   ::icon_pointer os_context::load_icon(const ::payload & payloadFile)
   {


      return error_failed;

   }

//
//} // namespace aura
//
//

   void os_context::enum_draw2d_fonts(::write_text::font_enumeration_item_array& itema)
   {


   }
