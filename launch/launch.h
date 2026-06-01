// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
// From launch/application.h by camilo on 2026-06-01 23:28 BRT <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once




namespace launch
{


   class CLASS_DECL_LAUNCH launch :
      virtual public ::particle
   {
   public:


      ::i32 m_iExitCode;

      ::launch::application* m_plaunchapplication = nullptr;

      //::i32            m_argc;
      //char_pointer *        m_argv;
      //::i32            m_iExitCode;


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


      launch();
      ~launch() override;


      void calculate_distro__branch_and_release();

      void parse_app_root_and_app_name();


      virtual void do_launch();


      ::string calculate_download_url();

      //bool check_http_ok(const_char_pointer pszUrl);


      //void log_system(const_char_pointer psz);
      void install_dependencies();


   };



} // namespace launch



