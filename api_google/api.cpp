// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/folder.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/system.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/application/application.h"
#include "apex/networking/http/context.h"
#include "apex/platform/application.h"
#include "aqua/xml/document.h"
#include <time.h>


string reverse_by_separator(const char * pszSeparator, const char * psz)
{

   string_array stra;

   stra.explode(pszSeparator, psz);

   return stra.reverse_implode(pszSeparator);

}

#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1

#ifdef WINDOWS_DESKTOP
#define timegm _mkgmtime
#endif


namespace api_google
{


   api::api()
   {

   }


   api::~api()
   {
      
   }


   void api::api_login(const ::string& strConfigParam, const ::string& strProfile)
   {

      if (m_strToken.is_empty())
      {

         m_bWaitingResponseFromUser = true;

         auto pfolder = file()->resource_folder();

         if (pfolder)
         {

            string strConfig(strConfigParam);
            
            string strScope = "https://www.googleapis.com/auth/cloud-platform";

            string strResponseType = "code";
            
            string strState;

            generate_random_alphanumeric(strState.get_string_buffer(1024), 1024);

            strState.release_string_buffer(1024);

            auto iLen = strlen(strState.c_str());

            m_strState = strState;

            
#ifdef APPLE_IOS
            
            string strAppId = get_app()->m_strAppId;

            auto pfile = pfolder->get_file("sensitive/sensitive/api/google/ios/" + (strAppId + ".plist"));

            auto strXml = pfile->as_string();
            
            auto pxmldocument = __create_new < ::xml::document >();

            pdocument->load(strXml);

            auto pdict = pdocument->get_child("dict");
            
            string strClientId = pdict->plist_get("CLIENT_ID");
            
            string strReversedClientId = pdict->plist_get("REVERSED_CLIENT_ID");

            m_strRedirectUri = strReversedClientId + ":/localhost/redirect";

            
            //string strClientId = "570794839356-6utj32uauvv39h73ulquat6u183pceaf.apps.googleusercontent.com";
            
            
            m_setConfig["installed"]["client_id"] = strClientId;
            
            auto papp = get_app()->m_papexapplication;

            papp->networking_application()->add_handler("redirect", this);
            
            string strUrl;

            strUrl.format("https://accounts.google.com/o/oauth2/v2/auth?scope=%s&response_type=%s&include_granted_scopes=true&state=%s&redirect_uri=%s&client_id=%s",//,&code_challenge=%s&code_challenge_method=%s",
            //strUrl.format("https://accounts.google.com/o/oauth2/v2/auth?scope=%s&response_type=%s&include_granted_scopes=true&state=%s&redirect_uri=%s&client_id=%s&code_challenge=%s&code_challenge_method=%s",
               ::url::encode(strScope).c_str(),
               ::url::encode(strResponseType).c_str(),
               ::url::encode(strState).c_str(),
               ::url::encode(m_strRedirectUri).c_str(),
                          ::url::encode(strClientId).c_str());
                          //,code_challenge.c_str()
                          //,code_challenge_method.c_str());

            auto phyperlink = __create_new <::hyperlink >();

            phyperlink->m_strLink = strUrl;

            phyperlink->m_strProfile = strProfile;

            phyperlink->run();

            m_eventResponse.ResetEvent();

            m_eventResponse.wait();
            
#else
            
#if defined(_UWP)

            string strAppId = get_app()->m_strAppId;

            auto pfile = pfolder->get_file("sensitive/sensitive/api/google/uwp/" + (strAppId + ".network_payload"));

#elif defined(ANDROID)

            string strAppId = get_app()->m_strAppId;

            auto pfile = pfolder->get_file("sensitive/sensitive/api/android/google/" + (strAppId + ".network_payload"));


#else

            auto pfile = pfolder->get_file("sensitive/sensitive/api/google/" + (strConfig + ".network_payload"));

#endif

            if (pfile)
            {

               string str;

               string strNetworkPayload;

               pfile->as(strNetworkPayload);

               ::property_set & setConfig = m_setConfig;

               m_strConfig = strConfig;

               setConfig.parse_network_payload(strNetworkPayload);

//#if !defined(_UWP) && !defined
//
//
//#endif

               //string strScope = "email profile https://www.googleapis.com/auth/cloud-platform";



//#ifdef _UWP
//
//               string strProtocol = papp->m_strAppId;
//
//               strProtocol.replace("/", ".");
//
//               m_strRedirectUri = "11841SUNPlusPlus.STARPlusPlusClockverse://google/redirect_uri";
//               //m_strRedirectUri = "urn:ietf:wg:oauth:2.0:oob";
//               //m_strRedirectUri = "pw.oauth2:/oauth2redirect";
//               //m_strRedirectUri = "urn:ietf:wg:oauth:2.0:oob";
//
//#else

               string strClientId = setConfig["installed"]["client_id"];

#if defined(ANDROID)

               // string strClientId = setConfig["client_id"];

               string strReversedClientId = reverse_by_separator(".", strClientId);

               m_strRedirectUri = strReversedClientId + ":/oauth2redirect";

               auto papp = get_app()->m_papexapplication;

               papp->networking_application()->add_handler("oauth2redirect", this);

#elif defined(_UWP)

               string strApp = get_app()->m_strAppId;

               strApp.find_replace("_", "-");
               strApp.find_replace("/", ".");

               m_strRedirectUri = strApp+ ":/oauth2redirect";

               auto papp = get_app()->m_papexapplication;

               papp->networking_application()->add_handler("oauth2redirect", this);

#else
               auto papp = get_app()->m_papexapplication;

               papp->networking_application()->add_handler("google", this);


               auto iCurrentPort = papp->networking_application()->wait_get_current_port(1_min);

               m_strRedirectUri = "http://127.0.0.1:" + ::as_string(iCurrentPort) + "/google/redirect_uri";

#endif

//#endif


               //string code_verifier = randomDataBase64url(32);
               //string code_challenge = base64urlencodeNoPadding(sha256(code_verifier));
               //const string code_challenge_method = "S256";

               //setConfig["code_verifier"] = code_verifier;

               string strUrl;

               strUrl.format("https://accounts.google.com/o/oauth2/v2/auth?scope=%s&response_type=%s&include_granted_scopes=true&state=%s&redirect_uri=%s&client_id=%s",//,&code_challenge=%s&code_challenge_method=%s",
               //strUrl.format("https://accounts.google.com/o/oauth2/v2/auth?scope=%s&response_type=%s&include_granted_scopes=true&state=%s&redirect_uri=%s&client_id=%s&code_challenge=%s&code_challenge_method=%s",
                  ::url::encode(strScope).c_str(),
                  ::url::encode(strResponseType).c_str(),
                  ::url::encode(strState).c_str(),
                  ::url::encode(m_strRedirectUri).c_str(),
                             ::url::encode(strClientId).c_str());
                             //,code_challenge.c_str()
                             //,code_challenge_method.c_str());

               auto phyperlink = __create_new <::hyperlink >();

               phyperlink->m_strLink = strUrl;

               phyperlink->m_strProfile = strProfile;

               phyperlink->run();
               

               m_eventResponse.ResetEvent();

               m_eventResponse.wait();

            }
#endif

         }

      }

      if (m_strToken.is_empty() || !m_bAuthenticated)
      {

         throw ::exception(error_authentication);

      }

   }


   void api::api_get(::string & strNetworkPayload, const ::string & strUrl, property_set & set)
   {

      int iRetry = 0;

      while (iRetry < 3)
      {

         m_papiclient->defer_api();

         set["raw_http"] = true;

         set["disable_common_name_cert_check"] = true;

         set["headers"]["Authorization"] = "Bearer " + m_strToken;

         m_pcontext->m_papexcontext->http().get(strNetworkPayload, strUrl, set);

         int iStatusCode = set["http_status_code"].as_i32();

         if (iStatusCode >= 400 && iStatusCode <= 499)
         {

            m_bAuthenticated = false;

            m_strToken.empty();

            save_profile();

            continue;

         }

         break;

      }

   }


   ::e_status api::on_html_response(::string & strHtml, const ::string& strUrl, const ::property_set& setPost)
   {

      auto psystem = acmesystem();

      auto pdatetime = psystem->datetime();

      strHtml += "<html>";
      strHtml += "<head>";
      strHtml += "<meta charset=\"UTF-8\">";
      // <from https://thomasbs.com/ <3tbs!!>
      strHtml += "<link href=\"https://fonts.googleapis.com/css?family=Fira+Code&display=swap\" rel=\"stylesheet\">";
      // </from https://thomasbs.com/ <3tbs!!>
      strHtml += "</head>";
      strHtml += "<body style=\"font-family:'Fira Code', monospace;\">";

      string strResponseState = acmesystem()->url()->get_param(strUrl, "state");

      string strResponse;

      if (m_strState != strResponseState)
      {

         return error_failed;

      }

      string strCode = acmesystem()->url()->get_param(strUrl, "code");

      ::property_set & setConfig = m_setConfig;

      ::property_set set;

      //code = 4 / P7q7W91a - oMsCeLvIaQm6bTrgtp7 &
         //client_id = your_client_id &
         //client_secret = your_client_secret &
         //redirect_uri = urn % 3Aietf % 3Awg % 3Aoauth % 3A2.0 % 3Aoob % 3Aauto &
         //grant_type = authorization_code

      //set["headers"]["accept"] = "application/ssml+xml";
      
      
      string strClientId = setConfig["installed"]["client_id"];
      
      string strClientSecret = setConfig["installed"]["client_secret"];
      
      string strRedirectUri = m_strRedirectUri;
      
      set["headers"]["User-Agent"] = get_app()->m_strAppId;
      set["post"]["code"] = strCode;
      set["post"]["client_id"] = strClientId;
      if(strClientSecret.has_char())
      {
         set["post"]["client_secret"] = strClientSecret;
      }
      set["post"]["redirect_uri"] = strRedirectUri;
      set["post"]["grant_type"] = "authorization_code";


      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

/*       set["headers"]["Authorization"] = "Bearer " + m_strToken;*/


      string strGet = "https://oauth2.googleapis.com/token";

      strResponse = m_pcontext->m_papexcontext->http().get(strGet, set);

      ::property_set setResponse;

      setResponse.parse_network_payload(strResponse);

      if (!setResponse.has_property("access_token"))
      {

         strHtml += "<h2>Some error (2)</h2>";

         m_strToken.empty();

      }
      else
      {

         string strToken = setResponse["access_token"];

         string strIdToken = setResponse["id_token"];

         if (strIdToken.has_char())
         {

//               auto decoded = ::network_token::decode(strIdToken.c_str());
//
//               auto claims = decoded.get_payload_claims();
//
//               for (auto& e : claims)
//               {
//
//                  std::cout << e.first << " = " << e.second << std::endl;
//
//               }
//
//               string strEmail = claims["email"].as_string().c_str();

         }

         m_strToken = strToken;

         m_bAuthenticating = false;

         m_bAuthenticated = true;

         strHtml += "<h1>";
         strHtml += "🌌 🌍 [ ca2/C++/Windows ] api_google";
         strHtml += "</h1>";

      }

      strHtml += "<h4><a href=\"https://ca2.software/camilo\">cs</a><a href=\"https://ca2.io\">&lt;3</a><a href=\"https://thomasbs.com/\">tbs</a>!!</h4>";
      strHtml += "&lt;3TBS - ∞ - " + pdatetime->international().get_date_time() + "- +∞ - CA2(THWOASONE)";
      strHtml += "</body>";
      strHtml += "</html>";

      on_login_response();

      return ::success;

   }


   void api::api_download(string strGet, const ::file::path& path, property_set& set)
   {

      set["raw_http"] = true;
      set["disable_common_name_cert_check"] = true;

      set["headers"]["Authorization"] = "Bearer " + m_strToken;

      m_pcontext->m_papexcontext->http().download(strGet, path, set);

      //return ::success;

   }


} // namespace hi5



