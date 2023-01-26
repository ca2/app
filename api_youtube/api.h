// From youtube project to api_youtbe on 2022-06-22 21:34 BRT <3ThomasBorregaardS�rensen!!
#pragma once


#include "apex/platform/api.h"


namespace api_youtube
{


   class CLASS_DECL_API_YOUTUBE api :
      virtual public ::api
   {
   public:


      //string                  m_strApiProfile;

      class ::time                 m_timeApiSleep;

      ::earth::time              m_timeYoutubeTinyQuotaOkAgain;

      bool                       m_bYoutubeTinyQuotaExceeded;


      api();
      ~api() override;


      virtual ::particle * get_api_mutex();

      virtual string get_local_path();

      virtual string youtube_api_token(bool bForce);

      virtual void log(string strOutput);

      virtual string randomDataBase64url(u32 uiLength);

      virtual memory sha256(string str);

      virtual string base64urlencodeNoPadding(memory m);

      virtual void api_get(::payload& payload, const ::string& strUrl, property_set& set);


   };


} // namespace youtube



