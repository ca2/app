// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "api.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
#include "apex/networking/application/application.h"
#include "apex/networking/http/context.h"
#include "axis/platform/application.h"


#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1

#ifdef WINDOWS_DESKTOP
#define timegm _mkgmtime
#endif
CLASS_DECL_ACME void generate_random_alphanumeric(void * p, memsize s);

namespace api_ca2
{


   api::api()
   {

   }


   api::~api()
   {

   }


   string api::get_name_for_profile()
   {

      return "ca2";

   }


   //void api::api_login(const ::string& strConfigParam, const ::string& strProfile)
   void api::api_login()
   {

      //if (m_strToken.is_empty())
      {

         m_bWaitingResponseFromUser = true;

         string str;

         string strAppLogin;

         strAppLogin = get_app_login();

         if (strAppLogin.is_empty())
         {

            throw ::exception(error_failed);

         }

         m_strState = strAppLogin;

         //#ifdef SANDBOXED_PLATFORM
         //
         //         generate_random_alphanumeric(m_strAppState.get_buffer(256), 256);
         //
         //         m_strAppState.release_buffer(256);
         //
         //      string strUrl = ::string("http://camilothomas.com/account/?platform=" PLATFORM_STRING "&applogin=cloud_database&appstate=") + m_strAppState;
         //
         //#else
         string strUrl = ::string("http://camilothomas.com/account/?platform=" PLATFORM_STRING "&applogin=") + ::url::encode(strAppLogin);

         //#ifdef APPLE_IOS
         //
         //         strUrl += "&redirect_uri=" + system()->url()->::url::encode(strAppLogin + "localhost/redirect");
         //
         //#endif

         //#endif

         auto phyperlink = __create_new <::hyperlink >();

         phyperlink->m_strLink = strUrl;

         phyperlink->m_strBrowserAccount = m_strBrowserAccount;

         phyperlink->run();

         m_eventResponse.ResetEvent();
         //
         //#ifdef SANDBOXED_PLATFORM
         //         property_set set;
         //         while(!defer_account_token(m_strAppState))
         //         {
         //         string strSessid = m_pcontext->http().get("https://camilothomas.com/get_sessid?appstate=" + m_strAppState, set);
         //            if(strSessid=="(Empty)")
         //            {
         //
         //            }
         //            preempt(5s);
         //               }
         //
         //#else
         //

         auto bOk = m_eventResponse.wait(1_min);

         if (!bOk)
         {

            throw ::exception(error_failed);

         }


         //#endif

      }

      if (m_strToken.is_empty() || !m_bAuthenticated)
      {

         throw ::exception(error_failed);

      }

   }


   void api::_api_get(::string & strNetworkPayload, const ::scoped_string & scopedstrUrl, ::property_set & set)
   {

      int iRetry = 0;

      while (iRetry < 3)
      {

         m_papiclient->defer_api();

         set["raw_http"] = true;

         set["disable_common_name_cert_check"] = true;

         set["headers"]["Authorization"] = "Bearer " + m_strToken;
         set["headers"]["appstate"] = m_setProfile["appstate"];
         set["headers"]["applogin"] = m_setProfile["applogin"];

         m_pcontext->m_papexcontext->http().get(strNetworkPayload, scopedstrUrl, set);

         int iStatusCode = set["http_status_code"].as_i32();

         if (iStatusCode >= 400 && iStatusCode <= 499)
         {

            m_bAuthenticated = false;

            m_strToken.empty();

            m_setProfile["appstate"] = e_type_new;

            m_setProfile["applogin"] = e_type_new;

            save_profile();

            continue;

         }

         break;

      }

   }


   ::e_status api::on_html_response(::string & strHtml, const ::string & strUrl, const ::property_set & setPost)
   {

      //auto psystem = system();

      //auto pdatetime = psystem->datetime();

      strHtml += "<html>";
      strHtml += "<head>";
      strHtml += "<meta charset=\"UTF-8\">";
      // <from https://thomasbs.com/ <3tbs!!>
      strHtml += "<link href=\"https://fonts.ca2apis.com/css?family=Fira+Code&display=swap\" rel=\"stylesheet\">";
      // </from https://thomasbs.com/ <3tbs!!>
      strHtml += "</head>";
      strHtml += "<body style=\"font-family:'Fira Code', monospace;\">";

      string strAppState = system()->url()->get_param(strUrl, "appstate");

      if (defer_account_token(strAppState))
      {

         strHtml += "<h1>";
         strHtml += "Login successful";
         strHtml += "</h1>";

      }

      strHtml += "<h4>The login process has completed successfully.</h4>";
      strHtml += "<h5>You can return to the application.</h5>";
      strHtml += "</body>";
      strHtml += "</html>";

      on_login_response();

      return ::success;

   }

   bool api::defer_account_token(const ::string & strAppState)
   {
      //::property_set & setConfig = m_setConfig;

      //::property_set set;

      //code = 4 / P7q7W91a - oMsCeLvIaQm6bTrgtp7 &
         //client_id = your_client_id &
         //client_secret = your_client_secret &
         //redirect_uri = urn % 3Aietf % 3Awg % 3Aoauth % 3A2.0 % 3Aoob % 3Aauto &
         //grant_type = authorization_code

      //set["headers"]["accept"] = "application/ssml+xml";

      string strAppLogin = get_app_login();

      string strClientId = m_setConfiguration["installed"]["client_id"];

      string strClientSecret = m_setConfiguration["installed"]["client_secret"];

      string strRedirectUri = m_strRedirectUri;

      property_set set;

      set["headers"]["User-Agent"] = get_app()->m_strAppId;
      set["post"]["applogin"] = strAppLogin;
      set["post"]["appstate"] = strAppState;

      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

      string strGet = "https://camilothomas.com/account/token";

      string strResponse = m_pcontext->m_papexcontext->http().get(strGet, set);

      if (strResponse.case_insensitive_begins_eat("token://"))
      {

         m_setProfile["applogin"] = strAppLogin;

         m_setProfile["appstate"] = strAppState;

         m_strToken = strResponse;

         m_bAuthenticated = true;

         return true;

      }

      return false;

   }


   ::memory api::api_memory(const ::scoped_string & scopedstrUrl, property_set & set)
   {

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      set["headers"]["Authorization"] = "Bearer " + m_strToken;

      auto pmemoryfile = create_memory_file();

      m_pcontext->m_papexcontext->http().download(scopedstrUrl, pmemoryfile, set);

      return pmemoryfile->memory();

   }


   string api::get_app_login()
   {

#ifdef APPLE_IOS

      auto papp = get_app()->m_paxisapplication;

      papp->networking_application()->add_handler("redirect", this);

      string strGuessedBundleIdentifier = papp->m_strAppId;

      strGuessedBundleIdentifier.find_replace("/", ".");

      return strGuessedBundleIdentifier + "://localhost/";

#else


      int iCurrentPort = 0;

      auto papp = get_app()->m_paxisapplication;

      string strAppId = papp->m_strAppId;

      papp->networking_application()->add_handler(strAppId + "/redirect", this);

      iCurrentPort = papp->networking_application()->wait_get_current_port(1_min);

      if (iCurrentPort < 0)
      {

         return "";

      }

      string strAppLogin;

      strAppLogin.formatf("http://127.0.0.1:%d/%s/", iCurrentPort, strAppId.c_str());

      return strAppLogin;

#endif

   }


} // namespace api_ca2



