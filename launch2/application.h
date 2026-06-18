// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


namespace launch
{


   class application
   {
   public:


      ::i32 m_argc;
      char_pointer * m_argv;
      ::i32 m_iExitCode;
      const_char_pointer m_pszDistro;
      char_pointer m_pszVersion;
      const_char_pointer m_pszBranch;
      char_pointer m_pszAppRoot;
      char_pointer m_pszAppName;

      application(::i32 argc, char_pointer argv[]);
      ~application();

      void parse_app_root_and_app_name();

      void run();


      char_pointer get_download_url(const_char_pointer pszRoot, const_char_pointer pszName);

      bool check_http_ok(const_char_pointer pszUrl);


      void log_system(const_char_pointer psz);
      void install_dependencies();


   };



} // namespace launch



