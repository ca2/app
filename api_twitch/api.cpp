// Created by camilo on 2021-11-05 16:34 PM <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "api.h"
////#include "acme/exception/exception.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/file/folder.h"
#include "acme/primitive/primitive/url.h"
#include "acme/primitive/datetime/datetime.h"
#include "acme/primitive/mathematics/mathematics.h"
#include "acme/platform/hyperlink.h"
#include "acme/platform/system.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/application/application.h"
#include "apex/networking/http/context.h"
#include "axis/platform/application.h"
//#include <network_token/network_token.h>


#include <time.h>



#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1

#ifdef WINDOWS_DESKTOP
#define timegm _mkgmtime
#endif


namespace api_twitch
{


   api::api()
   {

      m_bWaitingResponseFromUser = false;

   }


   api::~api()
   {
      
   }


   void api::api_login(const ::string& strConfig, const ::string & strProfile)
   {

      if (m_strToken.is_empty())
      {

         m_bWaitingResponseFromUser = true;

         auto pfolder = file()->resource_folder();

         if (pfolder)
         {

            string strFile = "sensitive/sensitive/api/twitch/" + (strConfig + ".network_payload");

            auto pfile = pfolder->get_file(strFile);

            if (pfile)
            {

               string str;

               string strNetworkPayload;

               pfile->as(strNetworkPayload);

               auto & setConfig = m_setConfig;

               m_strConfig = strConfig;

               m_strProfile = strProfile;

               setConfig.parse_network_payload(strNetworkPayload);

               auto papp = get_app()->m_paxisapplication;

               papp->networking_application()->add_handler("twitch", this);

               //string strScope = "email profile https://www.googleapis.com/auth/cloud-platform";

               string strScope = "chat:read chat:edit user:read:follows";

               string strResponseType = "code";

               string strState;

               generate_random_alphanumeric(strState.get_string_buffer(1080), 1080);

               strState.release_string_buffer(1080);

               m_strState = strState;


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
//
  //             m_strRedirectUri = "http://127.0.0.1:" + as_string(papp->networking_application()->m_iPort) + "/google/redirect_uri";

//#endif

               string strAuthUri = setConfig["installed"]["auth_uri"];

               string strClientId = setConfig["installed"]["client_id"];

               string strPort;

               strPort = ::as_string(papp->networking_application()->wait_get_current_port(1_min));

               m_strRedirectUri = "http://localhost:"+strPort+"/twitch/authorization";
               //m_strRedirectUri = "http://localhost:" + strPort;

               string strUrl;

               strUrl.format("%s?client_id=%s&redirect_uri=%s&response_type=%s&scope=%s&state=%s",
                  strAuthUri.c_str(),
                  ::url::encode(strClientId).c_str(),
                  ::url::encode(m_strRedirectUri).c_str(),
                  ::url::encode(strResponseType).c_str(),
                  ::url::encode(strScope).c_str(),
                  ::url::encode(strState).c_str());

               preempt(2_s);

               auto phyperlink = __create_new <::hyperlink >();

               phyperlink->m_strLink = "http://localhost:"+strPort+"/twitch/start_authorization?profile=" + strProfile + "&authorization=" +::url::encode(strUrl);

               phyperlink->m_strProfile = strProfile;

               phyperlink->run();

               return;

            }

         }

      }

      if (m_strToken.is_empty())
      {

         throw ::exception(error_authentication);

      }

   }


   void api::api_get(::string & strNetworkPayload, const ::string & strUrl, property_set & set)
   {

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      set["headers"]["Authorization"] = "Bearer " + m_strToken;

      strNetworkPayload = m_pcontext->m_papexcontext->http().get(strUrl, set);

      //return ::success;

   }


   //bool comm::twitch_api_get(string strUrl, string& strNetworkPayload, ::payload& payload, i64 iTimeOut, property_set* pset)
   //{

   //   synchronous_lock synchronouslock(m_pmutexApi);

   //   string strCache;


   //   ::property_set set;

   //   if (pset == nullptr)
   //   {

   //      pset = &set;

   //   }
   //   ::property_set& setHttp = *pset;



   //   int iTry = 0;

   //   bool bResult = false;

   //   int iStatusCode = 0;

   //retry:

   //   if (iTimeOut > 0)
   //   {

   //      strCache = strUrl;

   //      strCache.replace(":", "_");

   //      strCache.replace("\\", "_");

   //      strCache.replace("/", "_");

   //      strCache.replace("?", "_");

   //      strCache.replace("&", "_");

   //      strCache = get_room_path() / "cache" / strCache + ".network_payload";

   //      auto pcontext = m_pcontext;

   //      if (pcontext->m_papexcontext->file()->exists(strCache) && !file_modified_timeout(strCache, (int)(iTimeOut)))
   //      {

   //         //::file_time t = ::get_file_time(strCache);

   //         strNetworkPayload = acmefile()->as_string(strCache);

   //         return true;

   //      }

   //   }

   //   setHttp["raw_http"] = true;

   //   setHttp["headers"]["Authorization"] = "Bearer " + m_papi->m_strToken;
   //   setHttp["disable_common_name_cert_check"] = true;

   //   synchronouslock.unlock();

   //   auto pcontext = m_pcontext;

   //   bResult = pcontext->m_papexcontext->http().get(strNetworkPayload, strUrl, setHttp);

   //   sleep(m_timeApiCallDelay);

   //   iStatusCode = setHttp["http_status_code"].i32();

   //   if (!bResult || iStatusCode != 200)
   //   {

   //      string strStatusCode = setHttp["http_status"];

   //      FORMATTED_WARNING("twitch_get failed with \"%s\" (%d)", strStatusCode.c_str(), iStatusCode);

   //      if (iTry < 3)
   //      {

   //         iTry++;

   //         goto retry;

   //      }

   //      return false;

   //   }

   //   if (strNetworkPayload.is_empty())
   //   {

   //      return false;

   //   }
   //   auto tickStart = ::time::now();

   //   const char* p = strNetworkPayload;

   //   try
   //   {

   //      payload.parse_network_payload(p);

   //   }
   //   catch (...)
   //   {

   //   }

   //   //      if (0)
   //   //      {
   //   //
   //   //         for (int i = 0; i < 20; i++)
   //   //         {
   //   //
   //   //            {
   //   //
   //   //               property_set set;
   //   //
   //   //               set.parse_network_payload(strNetworkPayload);
   //   //
   //   //            }
   //   //
   //   //
   //   //         }
   //   //
   //   //         MessageBox(nullptr, "parse_network_payload?", "parse_network_payload?", e_message_box_ok);
   //   //
   //   //      }
   //   auto tickEnd = ::time::now();

   //   auto tickSpan = tickEnd - tickStart;

   //   try
   //   {

   //      INFORMATION("network_payload parse at comm::twitch_get with url=\"" << strUrl << "\" took " << tickSpan.integral_millisecond());

   //   }
   //   catch (...)
   //   {


   //   }

   //   synchronouslock.lock();

   //   if (iTimeOut > 0)
   //   {

   //      acmefile()->put_contents(strCache, strNetworkPayload);

   //   }


   //   return true;

   //}


   ::e_status api::on_html_response(string & strHtml, const ::string& strUrl, const ::property_set& setPost)
   {

      auto strObject = acmesystem()->url()->get_script(strUrl);

      if (strObject == "/twitch/start_authorization")
      {

         string strAuthUrl = acmesystem()->url()->get_param(strUrl, "authorization");
         strHtml += "<html>\n";
         strHtml += "<head>\n";
         strHtml += "<meta charset=\"UTF-8\">\n";
         // <from https://thomasbs.com/ <3tbs!!>
         strHtml += "<link href=\"https://fonts.googleapis.com/css?family=Fira+Code&display=swap\" rel=\"stylesheet\">\n";
         // </from https://thomasbs.com/ <3tbs!!>
         strHtml += "</head>\n";
         strHtml += "<body style=\"font-family:'Fira Code', monospace;\">\n";
         strHtml += "\t<h1>" + m_strProfile + "</h1>\n";
         strHtml += "\t<h2><a href=\"" + strAuthUrl + "\">Start Authorization</a></h1>\n";
         strHtml += "</body>\n";
         strHtml += "</html>\n";


      }
      else if (strObject == "/twitch/authorization")
      {

         string strResponseState = acmesystem()->url()->get_param(strUrl, "state");

         string strResponse;

         if (m_strState != strResponseState)
         {

            return error_not_found;

         }

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

         string strCode = acmesystem()->url()->get_param(strUrl, "code");

         auto & setConfig = m_setConfig;

         ::property_set set;


         //code = 4 / P7q7W91a - oMsCeLvIaQm6bTrgtp7 &
            //client_id = your_client_id &
            //client_secret = your_client_secret &
            //redirect_uri = urn % 3Aietf % 3Awg % 3Aoauth % 3A2.0 % 3Aoob % 3Aauto &
            //grant_type = authorization_code

         //set["headers"]["accept"] = "application/ssml+xml";
         set["headers"]["User-Agent"] = get_app()->m_strAppId;
         set["post"]["code"] = strCode;
         set["post"]["client_id"] = setConfig["installed"]["client_id"];
         set["post"]["client_secret"] = setConfig["installed"]["client_secret"];
         set["post"]["redirect_uri"] = m_strRedirectUri;
         set["post"]["grant_type"] = "authorization_code";




         set["raw_http"] = true;
         set["disable_common_name_cert_check"] = true;

         /*       set["headers"]["Authorization"] = "Bearer " + m_strToken;*/


         string strGet = setConfig["installed"]["token_uri"];

         strResponse = m_pcontext->m_papexcontext->http().get(strGet, set);

         ::property_set setResponse;

         setResponse.parse_network_payload(strResponse);

         if (!setResponse.has_property("access_token"))
         {

            strHtml += "<h2>Some error (2)</h2>";

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

            ::api::api_login(m_strConfig, m_strProfile);

            strHtml += "<h1>";
            strHtml += "🌌 🌍 [ ca2/C++/Windows ] api_twitch";
            strHtml += "</h1>";

         }



         //}

         m_bWaitingResponseFromUser = false;

         strHtml += "<h4><a href=\"https://ca2.software/camilo\">cs</a><a href=\"https://ca2.io\">&lt;3</a><a href=\"https://thomasbs.com/\">tbs</a>!!</h4>";
         strHtml += "&lt;3TBS - ∞ - " + pdatetime->international().get_date_time() + "- +∞ - CA2(THWOASONE)";
         strHtml += "</body>";
         strHtml += "</html>";

         //return strHtml;

      }

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


} // namespace api_twitch



