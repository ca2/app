// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace launch_store
{


   class application
   {
   public:


      int m_iExitCode;
      const char * m_pszDistro;
      char * m_pszVersion;
      const char * m_pszBranch;

      application();
      ~application();


      void run();


      char * get_download_url();

      bool check_http_ok(const char * pszUrl);


      void log_system(const char * psz);
      void install_dependencies();


   };



} // namespace launch_store



