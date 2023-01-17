// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSørensen!!
#pragma once


namespace integration
{


   class CLASS_DECL_APEX context :
      virtual public ::particle
   {
   public:


      ::string          m_strVs;
      ::file::path      m_pathSourceFolder;
      ::file::path      m_pathStorageFolder;
      ::file::path      m_pathDownloadURL;
      ::string_array    m_straOutput;
      ::file::path      m_pathFolder;
      ::file::path      m_path;
      ::string          m_strRelease;
      ::string          m_strPlatform;
      ::string          m_strConfiguration;
      ::string          m_strName;


      context();
      ~context() override;


      virtual void prepare_compile_and_link_environment();


      virtual int command_system(const ::scoped_string & scopedstr);


      virtual void download_and_uncompress();
      virtual void git_clone();
      virtual void bash(const ::scoped_string & scopedstr);

      void untar(const ::file::path & pathFolder, const ::payload & payloadTar, int iStripComponent = 0);


      virtual ::string prepare_path(const ::file::path & path);


   };


} // namespace integration



