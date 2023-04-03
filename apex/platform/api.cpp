// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"
#include "acme/exception/interface_only.h"
#include "acme/primitive/string/base64.h"
#include "apex/crypto/crypto.h"
#include "apex/filesystem/filesystem/dir_context.h"
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


void api::initialize_api(::particle * pparticle, const ::file::path & pathProfileFolder, const ::scoped_string & scopedstrBrowserAccount)
{

   //auto estatus =
   
   ::object::initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   m_pathProfileFolder = pathProfileFolder;

   m_strBrowserAccount = scopedstrBrowserAccount;
   
   load_configuration();

   load_profile();

   //return estatus;

}


void api::load_configuration()
{

   ::file::path pathConfiguration;

   string strPrefix;

#ifdef UNIVERSAL_WINDOWS

   if (m_strImplementation.case_insensitive_equals("google"))
   {

      strPrefix = "uwp/";

   }

#endif

   pathConfiguration = "matter://api" / (strPrefix + m_strImplementation + ".network_payload");

   string strNetworkPayload = file()->as_string(pathConfiguration);

   m_setConfiguration.parse_network_payload(strNetworkPayload);

}


void api::load_profile()
{

   auto strNetworkPayload = file()->safe_get_string(m_pathProfileFolder / "profile.network_payload");

   try
   {

      m_setProfile.parse_network_payload(strNetworkPayload);

   }
   catch (...)
   {

      return;

   }

   m_strToken = m_setProfile["token"];

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

      m_strToken.empty();

      if (m_papiclient->m_papi == this)
      {

         m_papiclient->m_papi.release();

         m_papiclient.release();

      }

   }


}


void api::save_profile()
{

   m_setProfile["token"] = m_strToken;

   auto strNetworkPayload = m_setProfile.get_network_payload();

   file()->put_text(m_pathProfileFolder / "profile.network_payload", strNetworkPayload);

   //return ::success;

}


void api::clear_profile()
{

   m_strToken.empty();

   m_setProfile.clear();

   file()->put_text(m_pathProfileFolder / "profile.network_payload", "");

}


void api::defer_api()
{

   if (!m_bAuthenticated)
   {

      if (m_bAuthenticating)
      {

         m_eventResponse.wait();

      }
      else
      {

         m_bAuthenticating = true;

         if (m_pathProfileFolder.is_empty())
         {

            auto pathAppData = dir()->appdata();

            m_pathProfileFolder = pathAppData / "api" / m_strImplementation;

         }

         try
         {

            initialize_api(m_pparticleContext, m_pathProfileFolder, m_strBrowserAccount);

         }
         catch (...)
         {

            throw ::exception(error_failed);

         }

         if (!m_bAuthenticated)
         {

            //m_papi->api_login(m_strApiClientConfig, m_strBrowserProfile);

            api_login();

         }

      }

   }

}


void api::switch_profile_folder(const ::file::path & pathFolder)
{

   file()->copy(pathFolder, m_pathProfileFolder);

   m_pathProfileFolder = pathFolder;

}


void api::api_login()
{

   //m_strConfig = strConfig;

   //m_strProfile = strProfile;

   save_profile();

   m_bAuthenticated = true;

   //return ::success;
   //
}


void api::_api_get(::string & strNetworkPayload, const ::scoped_string & scopedstrUrl, ::property_set & set)
{

   throw ::interface_only();

}


::payload api::api_get(const ::scoped_string & scopedstrUrl, ::property_set & set)
{

   int iTry = 0;

   while (true)
   {

      ::string str;

      iTry++;

      defer_api();

      _api_get(str, scopedstrUrl, set);

      ::payload payload;

      payload.parse_network_payload(str);

      if (is_api_get_ok(scopedstrUrl, str, payload, set))
      {

         return payload;

      }

      clear_profile();

      if (iTry >= 3)
      {

         throw exception(error_failed);

      }

   }

   return {};

}


::memory api::api_memory(const ::scoped_string & scopedstrUrl, ::property_set & set)
{

   throw ::interface_only();

   return {};

}


   string api::api_token(bool bForce)
   {

      throw ::interface_only();

      return "";

   }


   bool api::is_api_get_ok(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstr, const ::payload& payload, ::property_set & set)
   {

      if (scopedstr().trim().is_empty())
      {

         return false;

      }
      
      if(payload.is_empty())
      {

         return false;

      }

      int iHttpStatusCode = set["http_status_code"];

      if (!is_http_status_ok(scopedstrUrl, scopedstr, payload, set, iHttpStatusCode))
      {

         return false;

      }

      return true;

   }


   bool api::is_http_status_ok(const ::scoped_string& scopedstrUrl, const ::scoped_string& scopedstr, const ::payload& payload, ::property_set& set, int iHttpStatusCode)
   {

      if (iHttpStatusCode != 200)
      {

         return false;

      }

      return true;

   }


   void api::on_login_authentication_failed()
   {

      m_strToken.empty();

      save_profile();

      //api_login(m_strConfig, m_strProfile);

      api_login();

   }


   string api::randomDataBase64url(u32 length)
   {

      memory m;

      m.set_size(length);

      generate_random_bytes(m.data(), m.get_length());

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
