// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/networking/application/application_handler.h"
#include "apex/platform/api.h"


namespace api_ca2
{


   class CLASS_DECL_API_CA2 api :
      virtual public ::api,
      virtual public ::networking::application_handler
   {
   public:


      string                           m_strApiProfile;
      class ::time                       m_timeApiSleep;
      ::earth::time                 m_timeYoutubeTinyQuotaOkAgain;
      bool                             m_bYoutubeTinyQuotaExceeded;
      string                           m_strRedirectUri;
      string                           m_strScriptNotifyOnPreLoginScreen;
      class ::time                     m_timeLastNotifyOnPreLoginScreen;
      
      string m_strAppState;


      api();
      ~api() override;


      string get_name_for_profile() override;
      

      //void api_login(const ::string& strConfig, const ::string& strProfile) override;

      void api_login() override;


      virtual bool user_seems_to_be_on_pre_login_screen() const;

      void _api_get(string & strNetworkPayload, const ::scoped_string & scopedstrUrl, ::property_set & set) override;


      ::memory api_memory(const ::scoped_string & scopedstrUrl, ::property_set& set) override;


      ::e_status on_html_response(::networking::application_socket * psocket, ::string & strHtml, const ::string& strUrl, const ::property_set& setPost) override;

      virtual bool defer_account_token(const ::string & strAppState);
      
      virtual string get_app_login();


   };


} // namespace CLASS_DECL_APP_CORE_API_CA2



