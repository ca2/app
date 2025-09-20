// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "launch/application.h"


namespace store
{


   class application :
    virtual public ::launch::application
   {
   public:


      //int m_argc;
      //char ** m_argv;
      //int m_iExitCode;
      //const_char_pointer m_pszDistro;
      //char * m_pszVersion;
      //const_char_pointer m_pszBranch;
      //char * m_pszAppRoot;
      //char * m_pszAppName;

      //application(int argc, char * argv[]);
      application();
      ~application();

      //void parse_app_root_and_app_name();

      //void run();


      //char * get_download_url(const_char_pointer pszRoot, const_char_pointer pszName);

      //bool check_http_ok(const_char_pointer pszUrl);


      //void log_system(const_char_pointer psz);
      //void install_dependencies();


   };



} // namespace launch



