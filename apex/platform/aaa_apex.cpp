//
// Created by camilo on 2021-03-17 13:37 BRT. <33TBS!!
//

//
// Created by camilo on 2021-03-17 13:37 BRT. <3-<3ThomasBS!!
#include "framework.h"
#include "node.h"

namespace apex
{

   apex::apex()
   {


   }


   apex::~apex()
   {


   }

   
   ::e_status apex::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      return ::error_interface_only;

   }


   ::e_status apex::parallelization_initialize()
   {

      return ::error_interface_only;

   }
   
   
   ::e_status apex::parallelization_finalize()
   {

      return ::error_interface_only;

   }


   ::e_status apex::thread_initialize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status apex::thread_finalize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status apex::node_thread_initialize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   ::e_status apex::node_thread_finalize(::thread* pthread)
   {

      return ::error_interface_only;

   }


   string apex::get_version()
   {

      return "";

   }


   ::e_status apex::_001InitializeShellOpen()
   {

      __throw(::error_interface_only);

      return error_interface_only;

   }


   void apex::show_wait_cursor(bool bShow)
   {

   }


   ::e_status apex::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   {

      __throw(error_interface_only);

      return error_interface_only;

    }


   string apex::multimedia_audio_get_default_library_name()
   {

      return "";

   }


   string apex::multimedia_audio_mixer_get_default_library_name()
   {

      return "";

   }


   string apex::veriwell_multimedia_music_midi_get_default_library_name()
   {

      return "";

   }


   bool apex::is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
   {

      return false;

   }

   bool apex::set_application_installed(const ::file::path& pathExe, string strAppId, const char* pszBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema)
   {


      return false;

   }

   
   bool apex::set_last_run_application_path(string strAppId)
   {

      return false;

   }


} // namespace apex



