// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSorensen!!
#pragma once


namespace integration
{


   class CLASS_DECL_ACME context :
      virtual public ::object
   {
   public:



      bool              m_bMsys;


      ::file::path      m_pathProjectDir;


      ::string          m_strVs;
      ::file::path      m_pathOperatingSystemIncludeFolder;
      ::file::path      m_pathOperatingSystemStorageFolder;
      ::file::path      m_pathDownloadURL;
      ::string_array    m_straOutput;
      ::file::path      m_pathFolder;
      ::file::path      m_pathBase;
      ::file::path      m_pathPlatformConfiguration;
      ::file::path      m_pathSource;
      ::file::path      m_pathPrefix;
      ::string          m_strRelease;
      //::string          m_strContext;
      //::string          m_strSdk1;
      //::string          m_strStagePlatform;
      ::string          m_strStagePlatform;
      ::string          m_strPlatform;
      //::string          m_strPlatform2;
      ::string          m_strConfiguration;
      ::string          m_strName;


      ::pointer < ::particle >                  m_pmutexLines;


      context();
      ~context() override;

      
      void initialize(::particle* pparticle) override;


      virtual void prepare();

      virtual ::file::path get_source_folder_path(const ::scoped_string& strRelative = {});

      virtual void create_source_directory(const ::scoped_string& strRelative = {});
      virtual void change_to_source_directory(const ::scoped_string& strRelative = {});

      virtual void prepare_compile_and_link_environment();

      virtual void prepare_compilation_script(::string & str);
      virtual void prepare_linking_script(::string & str);

      virtual ::i32 command_system(const ::scoped_string & scopedstr);

      virtual void clean();

      virtual void download_and_uncompress();
      virtual void git_clone();
      virtual ::i32 bash(const ::scoped_string & scopedstr);
      virtual ::i32 zsh(const ::scoped_string & scopedstr);

      void untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent = 0);


      virtual ::string prepare_path(const ::file::path & path);


   };


} // namespace integration



