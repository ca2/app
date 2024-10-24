// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/application.h"


namespace launch
{


   class application :
      virtual public ::platform::application
   {
   public:


      //int            m_argc;
      //char **        m_argv;
      //int            m_iExitCode;

      ::string       m_strDistro;
      ::string       m_strBranch;
      ::string       m_strRelease;


      ::string       m_strLaunchAppId;


      ::string       m_strAppRoot;
      ::string       m_strAppName;


      ::file::path   m_pathLog;
      ::file::path   m_pathX64;


      application();
      ~application() override;


      void calculate_distro__branch_and_release();

      void parse_app_root_and_app_name();


      void run() override;


      ::string calculate_download_url();

      //bool check_http_ok(const char * pszUrl);


      //void log_system(const char * psz);
      void install_dependencies();


   };



} // namespace launch



