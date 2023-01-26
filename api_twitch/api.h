// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/networking/application/application_handler.h"
#include "apex/platform/api.h"


namespace api_twitch
{


   class CLASS_DECL_API_TWITCH api :
      virtual public ::api,
      virtual public ::networking::application_handler
   {
   public:


      string                           m_strApiProfile;

      class ::time                       m_timeApiSleep;

      ::earth::time                 m_timeYoutubeTinyQuotaOkAgain;

      bool                             m_bYoutubeTinyQuotaExceeded;
      string                           m_strState;
      string                           m_strRedirectUri;
      bool                             m_bWaitingResponseFromUser;
      property_set                     m_setConfig;

      api();
      ~api() override;



      virtual void api_login(const ::string& strConfig, const ::string & strProfile);


      void api_get(::string & strNetworkPayload, const ::string& strUrl, property_set& set) override;

      //void api_get(::payload & payload, const ::string & strUrl, property_set & set) override;


      void api_download(string strGet, const ::file::path& path, property_set& set);


      ::e_status on_html_response(string & strHtml, const ::string& strUrl, const ::property_set& setPost) override;


   };


} // namespace CLASS_DECL_APP_CORE_API_GOOGLE



