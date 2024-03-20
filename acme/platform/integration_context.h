// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/listing.h"
#include "shell.h"


namespace integration
{


   class CLASS_DECL_ACME context :
      virtual public ::acme::shell
   {
   public:


      boolean           m_bOnlyInstall;
      boolean           m_bBuildDependencies;


      ::file::path      m_pathBaseIntegrationFolder;
      ::file::path      m_pathProjectFolder;
      ::file::path      m_pathBuildFolder;


      ::string          m_strVs;
      ::file::path      m_pathOperatingSystemIncludeFolder;
      ::file::path      m_pathOperatingSystemStorageFolder;
      ::file::path      m_pathDownloadURL;
      ::string          m_strGitCloneBranch;
      ::string_array    m_straOutput;
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


      ::pointer < ::particle >                  m_pmutexLines;


      ::file::listing   m_listingBuild;


      context();
      ~context() override;

      
      void initialize(::particle* pparticle) override;


      virtual void prepare();

      virtual ::file::path get_source_folder_path(const ::scoped_string& strRelative = {});
      virtual ::file::path get_build_folder_path(const ::scoped_string& strRelative = {});

      virtual void create_source_directory(const ::scoped_string& strRelative = {});
      virtual void change_to_source_directory(const ::scoped_string& strRelative = {});

      virtual void prepare_compile_and_link_environment();

      virtual void prepare_compilation_script(::string & str);
      virtual void prepare_linking_script(::string & str);

      using ::acme::shell::command_system;
      int command_system(const ::scoped_string& scopedstr, const class ::time& timeOut = 12_h) override;

      virtual void clean();

      virtual void download_and_uncompress();
      virtual void git_clone();
      virtual ::i32 bash(const ::scoped_string & scopedstr, const class ::time & timeTimeout);
      virtual ::i32 zsh(const ::scoped_string & scopedstr, const class ::time & timeTimeout);

      void untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent = 0);


      virtual ::string prepare_path(const ::file::path & path);


      virtual void list_host_builds();


      virtual ::file::path base_integration_folder();

      virtual ::file::path host_integration_folder();

      //virtual ::file::path integration_folder();

      virtual void defer_nasm();

      virtual void defer_yasm();

      virtual void defer_has_unix_shell_command(const ::scoped_string & scopedstr);

#ifdef WINDOWS_DESKTOP


      virtual void set_msys2(bool bSet = true);


#endif


   };


} // namespace integration



