//
// Created by camilo on 19/01/2021. --<33ThomasBS!!
//
#include "framework.h"
#include "node.h"


namespace apex
{


   node::node()
   {

      m_papexnode = this;

   }


   node::~node()
   {


   }


#ifdef _DEBUG


   i64 node::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return acme::node::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


   i64 node::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
   {

      return acme::node::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

   }


#endif


   ::e_status node::on_initialize_object()
   {

      auto estatus = ::acme::node::on_initialize_object();

      if (!estatus)
      {

         return estatus;

      }

      m_psystem->m_papexnode = this;

      return estatus;

   }


   ::e_status node::main()
   {
   
      auto psystem = m_psystem;
      
      auto estatus = psystem->main();
      
      if(!estatus)
      {
       
         return estatus;
         
      }
      
      return estatus;
      
   }

   
   string node::system_options_html()
   {

      string strFooter__;

      if (m_psystem->m_bAudio)
      {

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


   ::e_status node::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      return ::error_interface_only;

   }


   // ::e_status node::parallelization_initialize()
   // {

   //    return ::error_interface_only;

   // }


   // ::e_status node::parallelization_finalize()
   // {

   //    return ::error_interface_only;

   // }


   ::e_status node::thread_initialize(::thread * pthread)
   {

      return ::success;

   }


   ::e_status node::thread_finalize(::thread * pthread)
   {

      return ::success;

   }


   // ::e_status node::node_thread_initialize(::thread * pthread)
   // {

   //    return ::error_interface_only;

   // }


   // ::e_status node::node_thread_finalize(::thread * pthread)
   // {

   //    return ::error_interface_only;

   // }


   string node::get_version()
   {

      return "";

   }


   ::e_status node::_001InitializeShellOpen()
   {

      __throw(::error_interface_only);

      return error_interface_only;

   }


   void node::show_wait_cursor(bool bShow)
   {

   }


   ::e_status node::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
   {

      throw ::interface_only_exception();

      return error_interface_only;

   }


//   bool node::is_application_installed(const ::file::path & pathExe, string strAppId, string & strBuild,
//                                       const char * pszPlatform, const char * pszConfiguration,
//                                       const char * pszLocale, const char * pszSchema)
//   {
//
//      return false;
//
//   }
//
//   bool node::set_application_installed(const ::file::path & pathExe, string strAppId, const char * pszBuild,
//                                        const char * pszPlatform, const char * pszConfiguration,
//                                        const char * pszLocale, const char * pszSchema)
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


   ::e_status node::defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId)
   {
      
      return error_interface_only;
      
   }


   void node::set_application_menu(::application_menu * pmenu, ::application * papplication)
   {

   }


   ::file::path node::get_desktop_file_path(::application * papplication) const
   {

      return "";

   }


   void node::defer_notify_startup_complete()
   {


   }


   ::e_status node::start_node()
   {

      auto psystem = get_system()->m_papexsystem;

      auto estatus = psystem->on_start_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;


   }


   void node::on_user_color()
   {

      auto psystem = m_psystem->m_papexsystem;

      psystem->signal(id_user_color);

   }

   
   void node::os_menu_item_enable(void * pitem, bool bEnable)
   {

      throw ::interface_only_exception();
      
   }


   void node::os_menu_item_check(void * pitem, bool bCheck)
   {
   
      throw ::interface_only_exception();
      
   }


} // namespace apex



