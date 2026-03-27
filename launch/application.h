// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include <acme/operating_system/summary.h>

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


      ::pointer < ::operating_system::summary > m_poperatingsystemsummary;

      ::string       m_strSystem;
      ::string       m_strSystemFamily;
      ::string       m_strBranch;
      ::string       m_strRelease;
      ::string       m_strArchitecture;

      ::string       m_strLaunchAppId;


      ::string       m_strAppRoot;
      ::string       m_strAppName;


      ::file::path   m_pathLog;
      ::file::path   m_pathBinaryFolder;


      application();
      ~application() override;


      void calculate_distro__branch_and_release();

      void parse_app_root_and_app_name();


      void run() override;


      ::string calculate_download_url();

      //bool check_http_ok(const_char_pointer pszUrl);


      //void log_system(const_char_pointer psz);
      void install_dependencies();


   };



} // namespace launch



