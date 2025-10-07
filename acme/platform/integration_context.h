// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/listing.h"
#include "shell.h"
#include "acme/constant/integration.h"


namespace integration
{


   class CLASS_DECL_ACME context :
      virtual public ::acme::shell
   {
   public:


      ::logic::boolean  m_bOnlyInstall;
      ::logic::boolean  m_bBuildDependencies;


      ::file::path      m_pathBaseIntegrationFolder;
      ::file::path      m_pathProjectFolder;
      ::file::path      m_pathBuildFolder;


      ::string          m_strBuildIndexStagePrefix;

      ::string          m_strVs;
      ::file::path      m_pathOperatingSystemIncludeFolder;
      ::file::path      m_pathOperatingSystemStorageFolder;
      ::file::path      m_pathDownloadURL;
      ::string          m_strGitCloneBranch;
      ::string_array_base    m_straOutput;
      ::file::path      m_pathFolder;
      ::file::path      m_pathBase;
      ::file::path      m_pathPlatformConfiguration;
      ::file::path      m_pathSource;
      ::file::path      m_pathPrefix;
      ::file::path      m_pathStaticPrefix;
      ::string          m_strRelease;
      ::file::path      m_pathBuild;
      //::string          m_strContext;
      //::string          m_strSdk1;
      //::string          m_strStagePlatform;
      ::string          m_strStagePlatform;
      ::string          m_strPlatform;
      //::string          m_strPlatform2;
      ::string          m_strConfiguration;
      ::string          m_strName;


      ::particle_pointer                  m_pmutexLines;


      ::file::listing_base   m_listingBuild;


      context();
      ~context() override;

      
      void initialize(::particle* pparticle) override;


      virtual void prepare(const ::scoped_string & scopedstrOperatingSystem);

      virtual ::file::path get_source_folder_path(const ::scoped_string& strRelative = {});
      virtual ::file::path get_build_folder_path(const ::scoped_string& strRelative = {});

      virtual void create_source_directory(const ::scoped_string& strRelative = {});
      virtual void change_to_source_directory(const ::scoped_string& strRelative = {});

      virtual void prepare_compile_and_link_environment();

      virtual void prepare_compilation_script(::string & str);
      virtual void prepare_linking_script(::string & str);

      using ::acme::shell::command_system;
      int command_system(const ::scoped_string& scopedstr, const class ::time& timeOut = 12_h, const ::file::path& pathWorkingDirectory = {}, ::e_display edisplay = e_display_none) override;

      virtual void clean();

      virtual void download_and_uncompress();
      virtual void git_clone();
      virtual int git_bash(const ::scoped_string& scopedstr, const class ::time& timeTimeout);
      virtual int bash(const ::scoped_string & scopedstr, const class ::time & timeTimeout);
      virtual int zsh(const ::scoped_string & scopedstr, const class ::time & timeTimeout);

      void untar(const ::file::path& pathFolder, const ::payload& payloadTar, int iStripComponent = 0, ::function<void(const ::scoped_string& scopedstr)> = {});


      virtual ::string prepare_path(const ::file::path & path);


      virtual void list_host_builds();


      virtual ::file::path base_integration_folder();

      virtual ::file::path host_integration_folder();

      //virtual ::file::path integration_folder();

      virtual void defer_nasm();

      virtual void defer_yasm();

      virtual void defer_has_posix_shell_command(const ::scoped_string & scopedstr, const ::scoped_string & scopedstrInstallHintPackage = {}, enum_posix_shell eposixshell = e_posix_shell_system_default);

#ifdef WINDOWS_DESKTOP


      virtual void set_msys2(bool bSet = true);


#endif

      virtual ::string current_integration();

      virtual ::string integration_main_status(const ::scoped_string& scopedstrSlashed);
      virtual ::string integration_main_status();
      virtual bool integration_is_any_running();
      virtual ::string integration_can_start(const ::scoped_string& scopedstrIntegration);
      virtual ::string integration_one_that_is_building();


      virtual ::string build_index_stage_prefix();
      virtual ::string build_index_radix(::integration::enum_index eindex);


   };


} // namespace integration



