// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/platform/application.h"


namespace launch
{


   class application :
      virtual public ::acme::application
   {
   public:


      int            m_argc;
      char **        m_argv;
      int            m_iExitCode;

      ::string       m_strDistro;
      ::string       m_strVersion;
      ::string       m_strBranch;


      ::string       m_strLaunchAppId;


      ::string       m_strAppRoot;
      ::string       m_pszAppName;


      application();
      ~application() override;


      void parse_app_root_and_app_name();


      void run();


      char * get_download_url(const char * pszRoot, const char * pszName);

      bool check_http_ok(const char * pszUrl);


      void log_system(const char * psz);
      void install_dependencies();


   };



} // namespace launch



