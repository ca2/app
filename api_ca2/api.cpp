// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "api.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/system.h"
#include "acme/primitive/datetime/datetime.h"
#include "apex/networking/application/application.h"
#include "apex/networking/application/application_socket.h"
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


   bool api::user_seems_to_be_on_pre_login_screen() const
   {

      return m_timeLastNotifyOnPreLoginScreen.elapsed() < 1_min;

   }


   void api::api_login()
   {

      if (m_bAuthenticated) 
      {

         return;

      }

      string str;

      m_strAppLogin = get_app_login();

      if (m_strAppLogin.is_empty())
      {

         throw ::exception(error_failed);

      }

      m_strState = system()->mathematics()->random_alphanumeric(64);

      string strUrl = ::string("http://ca2.network/account/?platform=" PLATFORM_STRING);

      strUrl += "&applogin=" + ::url::encode(m_strAppLogin);

      strUrl += "&appstate=" + ::url::encode(m_strState);

      m_phyperlinkPreLoginScreen = __create_new <::hyperlink >();

      m_phyperlinkPreLoginScreen->m_strLink = strUrl;

      m_phyperlinkPreLoginScreen->m_strBrowserAccount = m_strBrowserAccount;

      m_bWaitingResponseFromUser = true;

      m_timeLastNotifyOnPreLoginScreen.Now();

      m_phyperlinkPreLoginScreen->run();

      m_eventResponse.ResetEvent();

      while (::task_get_run())
      {

         auto bOk = m_eventResponse.wait(2_s);

         if (bOk)
         {

            break;

         }

         if (!user_seems_to_be_on_pre_login_screen())
         {

            m_timeLastNotifyOnPreLoginScreen.Now();

            m_phyperlinkPreLoginScreen->run();

         }

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


   ::e_status api::on_html_response(::networking::application_socket * psocket, ::string & strHtml, const ::string & strUrl, const ::property_set & setPost)
   {

      if (::is_set(psocket))
      {

         ::string strSecFetchMode = psocket->inheader("sec-fetch-mode");

         ::string strScript = system()->url()->get_script(strUrl);

         if (strSecFetchMode.case_insensitive_equals("cors"))
         {

            ::string strOrigin = psocket->inheader("origin");

            ::string strOriginHost = system()->url()->get_server(strOrigin);

            string_array straAllowedOrigin;

            straAllowedOrigin.add("ca2.software");
            straAllowedOrigin.add("ca2.network");
            straAllowedOrigin.add("ca2.store");

            bool bAllowedOrigin = false;

            for (auto & strAllowedOrigin : straAllowedOrigin)
            {

               if (strOriginHost.case_insensitive_ends("." + strAllowedOrigin) || strOriginHost.case_insensitive_order(strAllowedOrigin) == 0)
               {

                  bAllowedOrigin = true;

                  break;

               }

            }

            if (!bAllowedOrigin)
            {

               strHtml.formatf("Not allowed Origin: \"%s\"", strOrigin.c_str());

               return ::success;

            }

            psocket->outheader("access-control-allow-origin") = strOrigin;

         }

         if (strScript == m_strScriptNotifyOnPreLoginScreen)
         {

            m_timeLastNotifyOnPreLoginScreen.Now();

            strHtml = "Waiting for Authentication";

            return ::success;

         }

      }

      m_timeLastNotifyOnPreLoginScreen.Now();

      strHtml += "<html>";
      strHtml += "<html>";
      strHtml += "<head>";
      strHtml += "<meta charset=\"UTF-8\">";
      // <from https://thomasbs.com/ <3tbs!!>
      strHtml += "<link href=\"https://fonts.ca2apis.com/css?family=Fira+Code&display=swap\" rel=\"stylesheet\">";
      // </from https://thomasbs.com/ <3tbs!!>
      strHtml += "</head>";
      strHtml += "<body style=\"font-family:'Fira Code', monospace;\">";

      string strAppState = system()->url()->get_param(strUrl, "appstate");

      string strAppCode = system()->url()->get_param(strUrl, "appcode");

      if (check_authenticated(strAppState, strAppCode))
      {

         strHtml += "<h1>";
         strHtml += "Login successful";
         strHtml += "</h1>";
         strHtml += "<h4>The login process has completed successfully.</h4>";
         strHtml += "<h5>You can return to the application.</h5>";

      }
      else
      {

         strHtml += "<h1>";
         strHtml += "Login failed";
         strHtml += "</h1>";
         strHtml += "<h4>The login process has failed.</h4>";
         strHtml += "<h5>You should be redirected to the login page.</h5>";

      }

      strHtml += "</body>";
      strHtml += "</html>";

      on_login_response();

      return ::success;

   }


   bool api::check_authenticated(const ::string & strAppState, const ::string & strAppCode)
   {

      string strAppLogin = get_app_login();

      string strClientId = m_setConfiguration["installed"]["client_id"];

      string strClientSecret = m_setConfiguration["installed"]["client_secret"];

      string strRedirectUri = m_strRedirectUri;

      property_set set;

      set["headers"]["User-Agent"] = get_app()->m_strAppId;
      set["post"]["applogin"] = strAppLogin;
      set["post"]["appstate"] = strAppState;
      set["post"]["appcode"] = strAppCode;

      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

      string strGet = "https://ca2.network/account/token";

      string strResponse = m_pcontext->m_papexcontext->http().get(strGet, set);

      if (!strResponse.case_insensitive_begins_eat("token://"))
      {

         m_setProfile.unset("applogin");

         m_setProfile.unset("appstate");

         m_strToken.empty();

         m_bAuthenticated = false;

         return false;

      }

      m_setProfile["applogin"] = strAppLogin;

      m_setProfile["appstate"] = strAppState;

      m_strToken = strResponse;

      m_bAuthenticated = true;

      return true;

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

      papp->networking_application()->add_handler(strAppId + "/notify_on_pre_login_screen", this);

      m_strScriptNotifyOnPreLoginScreen = "/" + strAppId + "/notify_on_pre_login_screen";

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



