// Created by camilo on 2023-02-17 03:45 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "ace/platform/application.h"
#include "ace/primitive/string/string.h"


namespace launch
{


   class application :
      virtual public ::ace::application
   {
   public:


      ::ace::string        m_strAppRoot;
      ::ace::string        m_strAppName;

      application();
      ~application();

      void parse_app_root_and_app_name();

      void run() override;


      ::ace::string get_download_url(const char * pszRoot, const char * pszName);

      //bool check_http_ok(const char * pszUrl);


      void log_system(const char * psz);
      void install_dependencies();


   };



} // namespace launch



