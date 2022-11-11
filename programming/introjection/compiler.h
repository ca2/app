#pragma once


#include "app/programming/programming/compiler.h"


namespace introjection
{


   class CLASS_DECL_APP_PROGRAMMING compiler:
      virtual public ::programming::compiler
   {
   protected:

      using ::object::initialize;
      using programming::compiler::initialize_programming_compiler;

   public:

//
//#ifdef WINDOWS
//
//      string                                    m_strVs;
//      string                                    m_strVsTools;
//      string                                    m_strVCVersion;
//
//#endif

      //::file::path                              m_pathProjectDir;
      //string                                    m_strDynamicSourceConfiguration;
      //::file::path                              m_strDynamicSourceStage;
      //::file::path                              m_strDynamicSourceStageFolder;
      string                                    m_strFramework;

      string                                    m_strApp;
      string                                    m_strProjectName;
      string                                    m_strRepos;

      //string                                    m_strLibPlatform;


      string_array                                   m_straSync;
      string                                    m_strLibsLibs;
      //string                                    m_strEnv;
      //string                                    m_strSdk1;
      //string                                    m_strPlatform;
      //string                                    m_strStagePlatform;

      //string                                    m_strPlat1;
      //string                                    m_strPlat2;
      ::file::path                              m_strTime;


      ::pointer < ::mutex >                                     m_pmutex;

      ::pointer < ::mutex >                                     m_pmutexLibrary;

      string_map < ::pointer<library >>               m_lib;


      compiler();
      ~compiler() override;

      virtual void initialize_introjection_compiler(::particle * pparticle, const ::string& pszRepos, const ::string& pszApp, const ::string& pszProjectName);

      //void initialize_compiler();
      //void prepare1(const ::string & lpcszSource, const ::string & lpcszDest);
      //void prepare_compile_and_link_environment();

      ::acme::library * compile(const ::file::path & path, bool bNew);


   };



} // namespace introjection


