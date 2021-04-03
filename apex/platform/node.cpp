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


   ::e_status node::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      return ::error_interface_only;

   }


   ::e_status node::parallelization_initialize()
   {

      return ::error_interface_only;

   }


   ::e_status node::parallelization_finalize()
   {

      return ::error_interface_only;

   }


   ::e_status node::thread_initialize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status node::thread_finalize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status node::node_thread_initialize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status node::node_thread_finalize(::thread* pthread)
   {

      return ::error_interface_only;

   }


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


   ::e_status node::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   string node::multimedia_audio_get_default_library_name()
   {

      return "";

   }


   string node::multimedia_audio_mixer_get_default_library_name()
   {

      return "";

   }


   string node::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "";

   }


   bool node::is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
   {

      return false;

   }

   bool node::set_application_installed(const ::file::path& pathExe, string strAppId, const char* pszBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
   {


      return false;

   }


   bool node::set_last_run_application_path(string strAppId)
   {

      return false;

   }



   void node::set_application_menu(::apex::application_menu * pmenu, ::apex::application * papplication)
   {

   }


   ::file::path node::get_desktop_file_path(::apex::application * papplication) const
   {

      return "";

   }


   void node::defer_notify_startup_complete()
   {


   }


   ::e_status node::start()
   {

      __pointer(::apex::system) psystem = get_system();

      auto estatus = psystem->on_start();

      if(!estatus)
      {

         return estatus;

      }

      return estatus;


   }



   void node::on_os_dark_mode_change()
   {

      __pointer(::apex::system) psystem = get_system();

      psystem->deliver(id_os_dark_mode);

   }


} // namespace apex



