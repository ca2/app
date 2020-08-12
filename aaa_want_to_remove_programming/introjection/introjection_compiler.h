#pragma once


namespace introjection
{


   class CLASS_DECL_PROGRAMMING library:
      virtual public ::object
   {
   public:


      __pointer(::aura::library)                m_plibrary;
      ::file::path                              m_pathScript;
      ::string_stream                               m_memfileError;
      string                                    m_strError;
      file_time                                 m_filetime;


      library(::object * pobject);
      virtual ~library();


   };



   class CLASS_DECL_PROGRAMMING compiler:
      virtual public ::object
   {
   public:


#ifdef WINDOWS_DESKTOP

      string                                    m_strVs;
      string                                    m_strVsTools;
      string                                    m_strVCVersion;

#endif

      ::file::path                              m_pathProjectDir;
      string                                    m_strDynamicSourceConfiguration;
      ::file::path                              m_strDynamicSourceStage;
      ::file::path                              m_strDynamicSourceStageFolder;
      string                                    m_strFramework;

      string                                    m_strApp;
      string                                    m_strProjectName;
      string                                    m_strRepos;

      string                                    m_strLibPlatform;


      string_array                                   m_straSync;
      string                                    m_strLibsLibs;
      string                                    m_strEnv;
      string                                    m_strSdk1;
      string                                    m_strPlatform;
      string                                    m_strStagePlatform;

      string                                    m_strPlat1;
      string                                    m_strPlat2;
      ::file::path                              m_strTime;


      ::mutex                                     m_mutex;

      ::mutex                                     m_mutexLibrary;

      string_map < __pointer(library) >                m_lib;


      compiler();
      virtual ~compiler();

      virtual ::estatus initialize(::object* pobjectContext) override;

      void initialize_compiler(const char * pszRepos, const char * pszApp, const char * pszProjectName);
      void prepare1(const char * lpcszSource,const char * lpcszDest);
      void prepare_compile_and_link_environment();

      ::aura::library * compile(string str,bool bNew);


   };



} // namespace dynamic_source


