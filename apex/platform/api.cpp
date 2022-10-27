// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/string/base64.h"
#include "apex/crypto/crypto.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


api::api()
{

   m_bAuthenticated = false;
   m_bWaitingResponseFromUser = false;

}


api::~api()
{


}


void api::initialize_api(::object* pparticle, const ::file::path & pathProfile)
{

   //auto estatus =
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_pathProfile = pathProfile;

   load_profile();

   //return estatus;

}


void api::load_profile()
{

   auto strNetworkPayload = m_pcontext->m_papexcontext->file().safe_get_string(m_pathProfile);

   try
   {

      m_setConfig.parse_network_payload(strNetworkPayload);

   }
   catch (...)
   {

      return;

   }

   m_strToken = m_setConfig["token"];

   if (m_strToken.has_char())
   {

      m_bAuthenticated = true;

   }

   //return ::success;

}


void api::on_login_response()
{

   m_bWaitingResponseFromUser = false;

   fork([this]()
      {

         save_profile();

      });


   m_eventResponse.SetEvent();

   if (!m_bAuthenticated)
   {

      m_strToken.Empty();

      if (m_papiclient->m_papi == this)
      {

         m_papiclient->m_papi.release();

         m_papiclient.release();

      }

   }


}


void api::save_profile()
{

   m_setConfig["token"] = m_strToken;

   auto strNetworkPayload = m_setConfig.get_network_payload();

   m_pcontext->m_papexcontext->file().put_text(m_pathProfile, strNetworkPayload);

   //return ::success;

}


void api::api_login(const ::string & strConfig, const ::string & strProfile)
{

   m_strConfig = strConfig;

   m_strProfile = strProfile;

   save_profile();

   m_bAuthenticated = true;

   //return ::success;
   //
}


void api::api_get(string& strNetworkPayload, const string& strUrl, property_set& set)
{

   throw ::interface_only();

}


void api::api_get(::payload& payload, const string & strUrl, property_set& set)
{

   string strNetworkPayload;

   api_get(strNetworkPayload, strUrl, set);

   payload.parse_network_payload(strNetworkPayload);

}


void api::api_download(string strGet, const ::file::path & path, property_set& set)
{

   throw ::interface_only();

}


   string api::api_token(bool bForce)
   {

      throw ::interface_only();

      return "";

   }


   void api::on_login_authentication_failed()
   {

      m_strToken.Empty();

      save_profile();

      api_login(m_strConfig, m_strProfile);

   }


   string api::randomDataBase64url(u32 length)
   {

      memory m;

      m.set_size(length);

      generate_random_bytes(m.get_data(), m.get_length());

      return base64urlencodeNoPadding(m);

   }


   memory api::sha256(string strInput)
   {

      memory m;

      m.from_asc(strInput);

      memory mDst;

      auto psystem = acmesystem()->m_papexsystem;

      auto pcrypto = psystem->crypto();

      pcrypto->sha256(mDst, m);

      return mDst;

   }


   string api::base64urlencodeNoPadding(memory m)
   {

      auto psystem = acmesystem();

      auto pbase64 = psystem->base64();

      string str = pbase64->encode(m);

      // Converts base64 to base64url.
      str.replace_with("-", "+");
      str.replace_with("_", "/");
      // Strips padding.
      str.replace_with("", "=");

      return str;

   }
