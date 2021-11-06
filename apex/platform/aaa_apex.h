//
// Created by camilo on 2021-03-17 13:33 BRT. <33TBS!!
//

//
// Created by camilo on 2021-03-17 13:33 BRT. <3-<3ThomasBS!!
//
#pragma once
#define virtaul virtual


namespace apex
{


   class CLASS_DECL_APEX apex :
      virtual public ::acme::department
   {
   public:


      apex();
      virtaul ~apex();


      virtual ::e_status shell_create_link(::file::path pathObj, ::file::path pathLnk, string strDesc, ::file::path pathIco="", int iIcon=-1);


      //virtual ::e_status parallelization_initialize();
      //virtual ::e_status parallelization_finalize();

      virtual ::e_status thread_initialize(::thread * pthread);
      virtual ::e_status thread_finalize(::thread* pthread);

      // virtual ::e_status node_thread_initialize(::thread* pthread);
      // virtual ::e_status node_thread_finalize(::thread* pthread);

      virtual string get_version();
      
      virtual ::e_status _001InitializeShellOpen();


      //virtual void show_wait_cursor(bool bShow = true);

      virtual ::e_status get_firefox_installation_info(string& strPathToExe, string& strInstallDirectory);

      virtual string multimedia_audio_get_default_library_name();
      virtual string multimedia_audio_mixer_get_default_library_name();
      virtual string veriwell_multimedia_music_midi_get_default_library_name();


      virtual bool is_application_installed(const ::file::path& pathExe, string strAppId, string& strBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema);

      virtual bool set_application_installed(const ::file::path& pathExe, string strAppId, const char* pszBuild, const char* pszPlatform, const char* pszConfiguration, const char* pszLocale, const char* pszSchema);

      virtual bool set_last_run_application_path(string strAppId);


   };


} // namespace apex



