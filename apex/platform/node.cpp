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


   void node::on_initialize_object()
   {

      //auto estatus =
      
      ::acme::node::on_initialize_object();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_psystem->m_papexnode = this;

      //return estatus;

   }


   void node::main()
   {
   
      auto psystem = m_psystem;
      
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

      if (m_psystem->m_bAudio)
      {

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

         strFooter__ += "<h2>Text to Speech</h2>";

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" atom=\"text_to_speech_azure.checkbox\" />";
         strFooter__ += "&nbsp;Azure";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" atom=\"text_to_speech_google.checkbox\" />";
         strFooter__ += "&nbsp;Google";
         strFooter__ += "<br/>";
         strFooter__ += "<br/>";

#ifdef WINDOWS_DESKTOP

         strFooter__ += "<br/>";
         strFooter__ += "<br/>";
         strFooter__ += "<input type=\"checkbox\" atom=\"text_to_speech_sapi.checkbox\" />";
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


   void node::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      throw ::interface_only();

   }


   // void node::parallelization_initialize()
   // {

   //    throw ::interface_only();

   // }


   // void node::parallelization_finalize()
   // {

   //    throw ::interface_only();

   // }


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

      throw ::exception(::error_interface_only);

      throw ::interface_only();

   }


   void node::show_wait_cursor(bool bShow)
   {

   }


   void node::get_firefox_installation_info(string & strPathToExe, string & strInstallDirectory)
   {

      throw ::interface_only();

      throw ::interface_only();

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


   void node::defer_create_main_menu(const string_array & straParent, const string_array & straMenu, const string_array & straId)
   {
      
      //throw ::interface_only();
      
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


   void node::start_node()
   {

      auto psystem = get_system()->m_papexsystem;

      //auto estatus = 
      psystem->on_start_system();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;


   }


   void node::on_operating_system_user_theme_change()
   {

      auto psystem = m_psystem->m_papexsystem;

      psystem->signal(id_operating_system_user_theme_change);

   }


   void node::on_operating_system_user_color_change()
   {

      auto psystem = m_psystem->m_papexsystem;

      psystem->signal(id_operating_system_user_color_change);

   }


   void node::on_operating_system_font_list_change()
   {

      auto psystem = m_psystem->m_papexsystem;

      psystem->signal(id_operating_system_font_list_change);

   }


   void node::os_menu_item_enable(void * pitem, bool bEnable)
   {

      throw ::interface_only();
      
   }


   void node::os_menu_item_check(void * pitem, bool bCheck)
   {
   
      throw ::interface_only();
      
   }


} // namespace apex



