#include "framework.h"
#include "api.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/string/base64.h"
#include "acme/operating_system/ansi/datetime_c.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/hyperlink.h"
#include "apex/crypto/crypto.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"
#include "apex/platform/system.h"
#include <time.h>


#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1


#ifdef WINDOWS_DESKTOP
#define timegm _mkgmtime
#endif


namespace api_youtube
{


   api::api()
   {

      defer_create_synchronization();

   }


   api::~api()
   {
      
   }


  // void api::initialize_youtube_api(::object* pparticle, const ::string & pszApiProfile)
  // {

  //    //auto estatus = 
  //    
  //    initialize(pparticle);

  //    //if (!estatus)
  //    //{

  //    //   return estatus;

  //    //}

  //    m_strApiProfile = pszApiProfile;
  //    //      string strTime;

  ////    strTime = as_string(m_timeYoutubeTinyQuotaOkAgain);

  //  //  pcontext->m_papexcontext->file()->put_contents(get_local_path() / "youtube_quota_good_again_" + m_strApiProfile + ".txt", strTime);

  //    m_bYoutubeTinyQuotaExceeded = false;

  //    m_timeApiSleep = 800_ms;

  //    //return estatus;

  // }


   ::particle * api::get_api_mutex()
   {

      return synchronization();

   }


   string api::get_local_path()
   {

      auto pcontext = m_pcontext;

      return pcontext->m_papexcontext->defer_process_matter_path("appconfig://api");

   }


   string api::youtube_api_token(bool bForce)
   {

      string strClientId;
      string strSecret;
      string strRedirectUri;
      string strAuthUri;

      if (1)
      {

#include "youtube_api.txt"

         const char * pszSecret =
#include "youtube_secret!!.txt"
         ;

         strClientId = pszClientId;

         strSecret = pszSecret;

         strAuthUri = pszAuthUri;

         strRedirectUri = pszRedirectUris;

      }

      string strCode;

      string strToken;

      if (!bForce)
      {

         auto pcontext = m_pcontext;

         strCode = pcontext->m_papexcontext->file()->as_string(get_local_path() / "youtube_token_" + m_strProfile + ".txt");

         if (strCode.has_char())
         {

            return strCode;

         }

      }

      string strState = randomDataBase64url(32);
      string strCodeVerifier = randomDataBase64url(32);
      string strCodeChallenge = base64urlencodeNoPadding(sha256(strCodeVerifier));
      string strCodeChallengeMethod = "S256";

      log("redirect URI: " + strRedirectUri);

      string strAuthorizationRequest;

      string strScope = "https://www.googleapis.com/auth/youtube";

      auto psystem = acmesystem();

      auto purl = psystem->url();

      strAuthorizationRequest = strAuthUri + "?response_type=code&scope=" +
                                ::url::encode(strScope) + "&redirect_uri="
                                +
                                ::url::encode(strRedirectUri)
                                + "&client_id=" +
                                strClientId
                                + "&state=" +
                                strState
//      + "&code_verifier=" +
//      strCodeVerifier +
                                + "&code_challenge=" +
                                strCodeChallenge +
                                +"&code_challenge_method=" +
                                strCodeChallengeMethod;


      string strBrowser;

      if (m_strProfile == "bot")
      {

         strBrowser = "ca2bot";

      }
      else
      {

         strBrowser = "native";

      }

      branch();

      auto phyperlink = __create_new < ::hyperlink >();

      phyperlink->m_strLink = strAuthorizationRequest;

      phyperlink->m_strProfile = strBrowser;

      phyperlink->m_strTarget = "youtube_browser";

      branch_procedure(phyperlink);

      {

         int iRetry = 100;

         string strUrl = "https://ca2.software/api/account/get_string?key=" + ::url::encode("youtube_resident." + strState);

         while (::task_get_run() && iRetry > 0)
         {

            {

               ::property_set set;

               set["raw_http"] = true;

               auto pcontext = m_pcontext;

               strCode = pcontext->m_papexcontext->http().get(strUrl, set);

               if (strCode.has_char())
               {

                  break;

               }

            }

            sleep(1_s);

            iRetry--;

         }

      }

      if (!::task_get_run())
      {

         return "";

      }

      log("Exchanging code for tokens...");

      // builds the  request
      string strTokenRequestUri = "https://www.googleapis.com/oauth2/v4/token";
      //string strTokenRequestBody;

      //strTokenRequestBody.format("code=%s&redirect_uri=%s&client_id=%s&code_verifier=%s&client_secret=%s&scope=&grant_type=authorization_code",
      //                           strCode,
      //                           ::url::encode(strRedirectUri),
      //                           strClientId,
      //                           strCodeVerifier,
      //                           strSecret
      //                          );

      property_set setToken;
      setToken["post"]["code"] = strCode;
      setToken["post"]["redirect_uri"] = strRedirectUri;
      setToken["post"]["client_id"] = strClientId;
      setToken["post"]["code_verifier"] = strCodeVerifier;
      setToken["post"]["client_secret"] = strSecret;
      setToken["post"]["grant_type"] = "authorization_code";
      setToken["headers"]["accept"] = "application/network_payload";

      auto pcontext = m_pcontext;

      string strNetworkPayload = pcontext->m_papexcontext->http().get(strTokenRequestUri, setToken);

      ::property_set setResp;

      const char * pszNetworkPayload = strNetworkPayload;

      setResp.parse_network_payload(pszNetworkPayload);

      strToken = setResp["access_token"];

      string strRefresh = setResp["refresh_token"];

      pcontext->m_papexcontext->file()->put_text(get_local_path() / "youtube_token_" + m_strProfile + ".txt", strToken);

      pcontext->m_papexcontext->file()->put_text(get_local_path() / "youtube_refresh_" + m_strProfile + ".txt", strRefresh);

      return strToken;

   }


   void api::api_get(::payload& payload, const ::string& strUrlParam, property_set& set)
   {

      if (m_bYoutubeTinyQuotaExceeded)
      {

         auto timeNow = ::earth::time::now();

         if (timeNow < m_timeYoutubeTinyQuotaOkAgain)
         {

            return;

         }

      }

      synchronous_lock synchronouslock(get_api_mutex());

      string strResponse;

      bool bForce = false;

retry:

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strApiProfile = m_strProfile;

      string strToken = youtube_api_token(bForce);

      set["headers"]["Authorization"] = "Bearer " + strToken;

      set["headers"]["accept"] = "application/network_payload";

      ::string strUrl(strUrlParam);

      //if (!string_begins_ci(strUrl, "https://"))
      //{

      //   strUrl = "https://www.googleapis.com" + strUrl;

      //}

      auto pcontext = m_pcontext;

      strResponse = pcontext->m_papexcontext->http().get(strUrl, set);

      int iStatusCode = set["http_status_code"].as_i32();

      if (iStatusCode == 429 || DEBUG_THROTTLE != 0)
      {

         string strDetail = payload["detail"];

         if (strDetail.case_insensitive_contains("throttled") || DEBUG_THROTTLE != 0)
         {

            output_debug_string(strDetail);

#if DEBUG_THROTTLE != 0

            double iMillis = DEBUG_THROTTLE * 1000;

#else
            strsize iFind = strDetail.case_insensitive_find_index("second");

            iFind--;

            while (iFind >= 0 && (ansi_char_isspace(strDetail[iFind])))
            {

               iFind--;

            }

            while (iFind >= 0 && (ansi_char_isdigit(strDetail[iFind]) || strDetail[iFind] == '.'))
            {

               iFind--;

            }

            string strSeconds = strDetail.substr(iFind);

            class time time = (integral_millisecond) ((::i64) (atof(strSeconds) * 1500.0 + 5000.0));


#endif

            auto papp = get_app();

            papp->payload("seconds") = 0;

            papp->payload("total_time") = time;

            bForce = false;

            auto timeStart = ::time::now();

            while (timeStart.elapsed() < time)
            {

               sleep(25_ms);

               papp->payload("seconds") = (time - timeStart.elapsed()) / 1000.0;

            }

            papp->payload("seconds") = 0.0;

            papp->payload("total_time") = 0.0;

            goto retry;

         }

      }

      if (iStatusCode == 400)
      {

         FORMATTED_TRACE("%s", strResponse.c_str());

         m_bYoutubeTinyQuotaExceeded = false;

      }
      else if (iStatusCode == 403)
      {

         const char * pszNetworkPayload = strResponse;

         output_debug_string(pszNetworkPayload);

         payload.parse_network_payload(pszNetworkPayload);

         string strReason = payload["error"]["errors"].at(0)["reason"];

         if (strReason.case_insensitive_order("quotaExceeded") == 0 || strReason.case_insensitive_order("dailyLimitExceeded") == 0)
         {

            m_bYoutubeTinyQuotaExceeded = true;

            auto timeNow = ::earth::time::now();

            struct tm timeinfo;

            gmtime_r(&timeNow.m_time, &timeinfo);

            timeinfo.tm_hour = 7;
            timeinfo.tm_min = 0;
            timeinfo.tm_sec = 0;

            auto timeQuotaPacifist = ::earth::time(timegm(&timeinfo));

            ASSERT(timeQuotaPacifist > timeNow);

            m_timeYoutubeTinyQuotaOkAgain = timeQuotaPacifist;

            string strTime;

            strTime = ::as_string((::i64)m_timeYoutubeTinyQuotaOkAgain.m_time);

            pcontext->m_papexcontext->file()->put_text(get_local_path() / "youtube_quota_good_again_" + m_strProfile + ".txt", strTime);

//            return false;
            throw exception(error_failed, "quota exceeded");

         }

         if (!bForce)
         {

            bForce = true;

            goto retry;

         }
         else
         {
            
            throw exception(error_failed);

         }


      }
      else if (iStatusCode != 200 || strResponse.is_empty())
      {

         m_bYoutubeTinyQuotaExceeded = false;

         if (!bForce)
         {

            bForce = true;

            goto retry;

         }
         else
         {

            throw exception(error_failed, "bad http response");

         }

      }

      const char * pszNetworkPayload = strResponse;

      payload.parse_network_payload(pszNetworkPayload);

      sleep(m_timeApiSleep);

      //return true;

   }


   void api::log(string str)
   {

      FORMATTED_TRACE("resident_youtube_api: %s", str.c_str());

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
      str.find_replace("+", "-");
      str.find_replace("/", "_");
      // Strips padding.
      str.find_replace("=", "");

      return str;

   }


} // namespace api_youtube



