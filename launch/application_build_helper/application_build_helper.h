// Created by camilo on 2021-12-17 21:01 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/collection/string_map.h"


namespace application_build_helper
{


   class package_reference
   {
   public:


      string            m_strPackage;
      ::file::path      m_pathReference;
      int               m_iLine;


   };


   using package_reference_array = ::array < package_reference >;


   class application_build_helper :
      virtual public ::particle
   {
   public:


      application *                       m_papplication;


      string                              m_strProjectId;


      bool                                m_bSoftBuild = false;

      string                              m_strApplication;

      string                              m_strLog;

      string                              m_strOperatingSystem2;
      string                              m_strSystemAmbientRelease;
      package_reference_array             m_packagereferencea;
      string_array                        m_straIgnorePackage;


      ::string                            m_strInstallerType;


      string                              m_strProjectName;

      ::file::path                        m_pathBaseDir;
      ::file::path                        m_pathGroup;
      ::file::path                        m_pathFolder;
      ::file::path                        m_pathOperatingSystem;
      ::file::path                        m_pathPort;
      ::file::path                        m_pathSource;
      //::file::path                        m_pathOutput;

      string                              m_strUnderscoreAppId;
      string                              m_strBase;
      string                              m_strRoot;
      string                              m_strItem;
      ::pointer<::handle::ini>            m_piniPackageMap;

      string                              m_strBuildPlatform;
      string                              m_strBuildConfiguration;

      bool                                m_bTranslateDependency;


      string_map < string_to_string >     m_mapBinaryToProject;
      string_map < string_to_string >     m_mapProjectToBinary;

      int                                 m_iExitCode;


      application_build_helper(application * papplication);
      ~application_build_helper() override;


      bool set_project_id(const ::scoped_string & strProjectId);


      void prepare_application();

#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)

      void posix_create_matter_object();

#endif

      void create_package_list();

      void translate_package_list();


      void add_package(package_reference & packagereference);
      void add_package_dependencies(const package_reference & packagereference);
      string_array get_lines(const ::file::path & path, bool bNoExceptionIfNotFound = true);
      package_reference_array get_package_list(const ::scoped_string & scopedstrList, const ::scoped_string & scopedstrPackage);
      package_reference_array get_package_references(const ::scoped_string & scopedstrPackage);
      package_reference_array get_package_dependencies(const ::scoped_string & scopedstrPackage);
      package_reference_array get_package_extensions(const ::scoped_string & scopedstrPackage);
      package_reference_array get_all_package_dependencies(const ::scoped_string & scopedstrPackage);


      void package();


      void copy_icon_ico();
      void generate__main();
      void defer_matter();
      void zip_matter();


      void prepare_project();
      void generate_deployment_rc();


      void translate_items(const ::scoped_string & scopedstrFileDst, const ::scoped_string & scopedstrFileSrc);
      //void static_factory(const ::scoped_string & scopedstrFileDst, const ::scoped_string & scopedstrFileFactory, const ::scoped_string & scopedstrFileSrc);
      void static_factory(const ::scoped_string & scopedstrFileDst, const ::scoped_string & scopedstrFileSrc);
      string defer_translate_dependency(string strDependency);
      string defer_binary_to_project(string strBinary);
      string defer_project_to_binary(string strProject);


      void load_map(string_to_string & map, string strMap, string strRoot);

      string defer_translate_application_name(string strDependency);

#ifdef LINUX

      void build_deb();

      void build_rpm();

      void release_store_installer();

#endif


   };



} // namespace application_build_helper



