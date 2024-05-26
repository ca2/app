// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace launch
{


   class application
   {
   public:


      int m_argc;
      char ** m_argv;
      int m_iExitCode;
      const char * m_pszDistro;
      char * m_pszVersion;
      const char * m_pszBranch;
      char * m_pszAppRoot;
      char * m_pszAppName;

      application(int argc, char * argv[]);
      ~application();

      void parse_app_root_and_app_name();

      void run();


      char * get_download_url(const char * pszRoot, const char * pszName);

      bool check_http_ok(const char * pszUrl);


      void log_system(const char * psz);
      void install_dependencies();


   };



} // namespace launch



