// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardS�rensen!!
#include "framework.h"
#include "api.h"
#include "acme/primitive/string/base64.h"


api::api()
{

   m_bAuthenticated = false;
   m_bWaitingResponseFromUser = false;

}


api::~api()
{


}


void api::initialize_api(::object* pobject, const ::file::path & pathProfile)
{

   //auto estatus =
   
   ::object::initialize(pobject);

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

   auto strNetworkPayload = m_pcontext->m_papexcontext->file().as_string(m_pathProfile);

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

   save_profile();

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

   throw interface_only_exception();

   throw ::interface_only_exception();

}


void api::api_get(::payload& payload, const string & strUrl, property_set& set)
{

   string strNetworkPayload;

   //auto estatus = 
      api_get(strNetworkPayload, strUrl, set);

   //if(!estatus)
   //{

   //   return estatus;

   //}

   payload.parse_network_payload(strNetworkPayload);

   //return estatus;

}


void api::api_download(string strGet, const ::file::path& path, property_set& set)
{

   throw interface_only_exception();

   throw ::interface_only_exception();

}


string api::api_token(bool bForce)
{

   throw interface_only_exception();

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

      auto psystem = m_psystem->m_papexsystem;

      auto pcrypto = psystem->crypto();

      pcrypto->sha256(mDst, m);

      return mDst;

   }


   string api::base64urlencodeNoPadding(memory m)
   {

      auto psystem = m_psystem;

      auto pbase64 = psystem->base64();

      string str = pbase64->encode(m);

      // Converts base64 to base64url.
      str.replace("+", "-");
      str.replace("/", "_");
      // Strips padding.
      str.replace("=", "");

      return str;

   }
