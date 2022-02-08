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

   
   void apex::shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco, int iIcon)
   {

      throw ::interface_only();

   }


   // void apex::parallelization_initialize()
   // {

   //    throw ::interface_only();

   // }
   
   
   // void apex::parallelization_finalize()
   // {

   //    throw ::interface_only();

   // }


   void apex::thread_initialize(::thread* pthread)
   {

      throw ::interface_only();

   }


   void apex::thread_finalize(::thread* pthread)
   {

      throw ::interface_only();

   }


   // void apex::node_thread_initialize(::thread* pthread)
   // {

   //    throw ::interface_only();

   // }


   // void apex::node_thread_finalize(::thread* pthread)
   // {

   //    throw ::interface_only();

   // }


   string apex::get_version()
   {

      return "";

   }


   void apex::_001InitializeShellOpen()
   {

      throw ::exception(::error_interface_only);

      throw ::interface_only();

   }


//   void apex::show_wait_cursor(bool bShow)
//   {
//
//   }


   void apex::get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory)
   {

      throw ::interface_only();

      throw ::interface_only();

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



