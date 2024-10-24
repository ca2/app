// Created by camilo on 2021-11-05 16:12 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "api.h"
#include "acme/exception/interface_only.h"
#include "acme/prototype/string/base64.h"
#include "acme/crypto/crypto.h"
#include "acme/filesystem/filesystem/dir_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/prototype/mathematics/mathematics.h"
#include "apex/platform/application.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"


api::api()
{

   m_bAuthenticated = false;
   m_bWaitingResponseFromUser = false;
   //m_bCheckingAuthenticated = false;

}


api::~api()
{


}


void api::initialize_api(::particle * pparticle, const ::file::path & pathProfileFolder, const ::scoped_string & scopedstrBrowserAccount)
{

   load_api(pparticle, pathProfileFolder, scopedstrBrowserAccount);

   initialization_api_call();

}


void api::load_api(::particle* pparticle, const ::file::path& pathProfileFolder, const ::scoped_string& scopedstrBrowserAccount)
{

   ::object::initialize(pparticle);

   m_pathProfileFolder = pathProfileFolder;

   m_strBrowserAccount = scopedstrBrowserAccount;

   load_configuration();

   load_profile();

}


void api::initialization_api_call()
{

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

   ::file::path pathName;

   pathName = m_strImplementation;

   if (m_strService.has_char())
   {

      pathName /= m_strService;

   }

   pathConfiguration = "matter://api" / (strPrefix + pathName + ".network_payload");
   
   information() << "api::load_configuration path : " << pathConfiguration;

   string strNetworkPayload = file()->as_string(pathConfiguration);

   m_setConfiguration.parse_network_payload(strNetworkPayload);

}


void api::load_profile()
{
   
   auto path = m_pathProfileFolder / "profile.network_payload";

   information() << "api::load_profile path : " << path;

   auto strNetworkPayload = file()->safe_get_string(path);
   
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

}


void api::on_login_response()
{

   m_bWaitingResponseFromUser = false;

   fork([this]()
      {

         save_profile();

      });

   if (!m_bAuthenticated)
   {

      m_strToken.empty();

      if (m_papiclient->m_papi == this)
      {

         m_papiclient->m_papi.release();

         m_papiclient.release();

      }

   }
   else
   {

      m_bAuthenticating = false;

   }

   m_eventResponse.SetEvent();

}


void api::save_profile()
{

   m_setProfile["token"] = m_strToken;

   auto strNetworkPayload = m_setProfile.get_network_payload();

   file()->put_text(m_pathProfileFolder / "profile.network_payload", strNetworkPayload);

}


void api::clear_profile()
{

   m_strToken.empty();

   m_setProfile.clear();

   file()->put_text(m_pathProfileFolder / "profile.network_payload", "");

}


void api::ensure_authenticated()
{

   for(int iTry = 0; iTry < 3; iTry++)
   {

      if (m_bAuthenticated)
      {

         return;

      }

      if (!::task_get_run())
      {

         throw_exit_exception();

         return;

      }

      if (m_bAuthenticating)
      {

         m_eventResponse.wait();
         
         information() << "api::defer_api got the response";

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

            load_api(m_pparticleContext, m_pathProfileFolder, m_strBrowserAccount);

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

   throw ::exception(error_failed);

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

      ensure_authenticated();

      _api_get(str, scopedstrUrl, set);

      informationf("_api_get response:\n%s", str.c_str());

      ::payload payload;
      
      bool bOk = false;
      
      try 
      {
         
         payload.parse_network_payload(str);
         
         bOk = true;
         
      } 
      catch (...)
      {
         
         bOk = false;
         
      }

      if (bOk && is_api_get_ok(scopedstrUrl, str, payload, set))
      {

         return payload;

      }

      clear_profile();

      if (iTry >= 3)
      {

         m_bAuthenticated = false;

         m_bAuthenticating = false;

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
      
      //if(payload.is_empty())
      //{

      //   return false;

      //}

      auto iHttpStatusCode = set["http_status_code"].as_i32();

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

      mathematics()->random(m);

      return base64urlencodeNoPadding(m);

   }


   memory api::sha256(string strInput)
   {

      memory m;

      m.from_asc(strInput);

      memory mDst;

      auto psystem = system();

      auto pcrypto = psystem->crypto();

      pcrypto->sha256(mDst, m);

      return mDst;

   }


   string api::base64urlencodeNoPadding(memory m)
   {

      auto psystem = system();

      auto pbase64 = psystem->base64();

      string str = pbase64->encode(m);

      // Converts base64 to base64url.
      str.replace_with("-", "+");
      str.replace_with("_", "/");
      // Strips padding.
      str.replace_with("", "=");

      return str;

   }
