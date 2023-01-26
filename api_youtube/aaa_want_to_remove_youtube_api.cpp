#include "framework.h"



#define DEBUG_THROTTLE 0
#define PARALLEL_UPDATE_USER 1


namespace youtube
{


   api::api(::particle * pparticle, const ::string & pszApiProfile) :
      ::object(pparticle),
      m_strApiProfile(pszApiProfile)
   {

      m_dwApiSleep = 800;

   }


   api::~api()
   {
   }


   string api::youtube_api_authorization(bool bForce)
   {

      string strClientId;
      string strSecret;
      string strRedirectUri;
      string strAuthUri = "https://mixer.com/oauth/authorize";

      if (1)
      {

         strClientId = get_client_id();

         strSecret = get_client_secret();

         strRedirectUri = "https://ca2.software/youtube_resident_callback";

      }

      string strCode;

      string strToken;

      if (!bForce)
      {

         strCode = pcontext->m_papexcontext->file()->as_string(get_local_path() / "youtube_token_" + m_strApiProfile + ".txt");

         if (strCode.has_char())
         {

            return strCode;

         }

      }


      string strRefreshCode = pcontext->m_papexcontext->file()->as_string(get_local_path() / "youtube_refresh_" + m_strApiProfile + ".txt");

      if(strRefreshCode.has_char())
      {

         log("Exchanging code for tokens...");

         string strTokenRequestUri = "https://mixer.com/api/v1/oauth/token";

         property_set setToken;
         setToken["raw_http"] = true;
         setToken["disable_common_name_cert_check"] = true;
         setToken["post"]["code"] = strRefreshCode;
         setToken["post"]["redirect_uri"] = strRedirectUri;
         setToken["post"]["client_id"] = strClientId;
         setToken["post"]["client_secret"] = strSecret;
         setToken["post"]["grant_type"] = "refresh_token";
         setToken["headers"]["accept"] = "application/network_payload";

         string strJson = pcontext->m_papexcontext->http().get(strTokenRequestUri, setToken);

         int iStatusCode = setToken["http_status_code"].i32();

         string strStatus = setToken["http_status"];

         if (iStatusCode == 200)
         {

            ::property_set setResp;

            const char * pszJson = strJson;

            setResp.parse_network_payload(pszJson);

            strToken = setResp["access_token"];

            string strRefresh = setResp["refresh_token"];

            if (strToken.has_char() && strRefresh.has_char())
            {

               pcontext->m_papexcontext->file()->put_contents(get_local_path() / "youtube_token_" + m_strApiProfile + ".txt", strToken);

               pcontext->m_papexcontext->file()->put_contents(get_local_path() / "youtube_refresh_" + m_strApiProfile + ".txt", strRefresh);

               return strToken;

            }

         }

      }

      string strState = randomDataBase64url(32);

      log("redirect URI: " + strRedirectUri);

      string strAuthorizationRequest;

      string strScope = m_strScopes;

      strAuthorizationRequest = strAuthUri + "?response_type=code&scope=" +
                                purl->url_encode(strScope) + "&redirect_uri="
                                +
                                purl->url_encode(strRedirectUri)
                                + "&client_id=" +
                                strClientId
                                + "&state=" +
                                strState;


      string strBrowser;

      if (m_strApiProfile == "bot")
      {

         strBrowser = "ca2bot";

      }
      else
      {

         strBrowser = "native";

      }

      defer_run_thread();

      psystem->open_link(strAuthorizationRequest, strBrowser, "youtube_browser");

      {

         ::property_set set;

         set["raw_http"] = true;

         int iRetry = 100;

         while (::task_get_run() && iRetry > 0 && (strCode = pcontext->m_papexcontext->http().get("https://ca2.software/api/account/get_string?key=" + purl->url_encode("resident_youtube_client." + strState), set)).is_empty())
         {

            sleep(1_s);

            iRetry--;

         }

      }

      if (!::task_get_run())
      {

         return "";

      }

      if (strCode.is_empty())
      {

         return "";

      }

      log("Exchanging code for tokens...");

      string strTokenRequestUri = "https://mixer.com/api/v1/oauth/token";

      property_set setToken;
      setToken["raw_http"] = true;
      setToken["disable_common_name_cert_check"] = true;
      setToken["post"]["code"] = strCode;
      setToken["post"]["redirect_uri"] = strRedirectUri;
      setToken["post"]["client_id"] = strClientId;
      setToken["post"]["client_secret"] = strSecret;
      setToken["post"]["grant_type"] = "authorization_code";
      setToken["headers"]["accept"] = "application/network_payload";

      string strJson = pcontext->m_papexcontext->http().get(strTokenRequestUri, setToken);

      int iStatusCode = setToken["http_status_code"].i32();

      string strStatus = setToken["http_status"];

      if (iStatusCode != 200)
      {

         return "";

      }

      ::property_set setResp;

      const char * pszJson = strJson;

      setResp.parse_network_payload(pszJson);

      strToken = setResp["access_token"];

      string strRefresh = setResp["refresh_token"];

      pcontext->m_papexcontext->file()->put_contents(get_local_path() / "youtube_token_" + m_strApiProfile + ".txt", strToken);

      pcontext->m_papexcontext->file()->put_contents(get_local_path() / "youtube_refresh_" + m_strApiProfile + ".txt", strRefresh);

      return strToken;

   }


   bool api::api_get(string strGet, ::payload & payload, property_set * pset)
   {

      synchronous_lock synchronouslock(get_api_mutex());

      ::property_set setHttp;

      if (pset == nullptr)
      {

         pset = &setHttp;

      }

      ::property_set &set = *pset;

      bool bForce = false;

      string strResponse;

retry:

      set["raw_http"] = true;

      set["disable_common_name_cert_check"] = true;

      string strApiProfile = m_strApiProfile;

      string strToken = youtube_api_authorization(bForce);

      set["headers"]["Authorization"] = "Bearer " + strToken;

      set["headers"]["accept"] = "application/network_payload";

      if (!string_begins_ci(strGet, "https://"))
      {

         strGet = "https://mixer.com/api/v1" + strGet;

      }

      strResponse = pcontext->m_papexcontext->http().get(strGet, set);

      int iStatusCode = set["http_status_code"].i32();

      if (pset != nullptr)
      {

         *pset = set;

      }

      if (iStatusCode == 429 || DEBUG_THROTTLE != 0)
      {

         string strDetail = payload["detail"];

         if (strDetail.case_insensitive_find("throttled") >= 0 || DEBUG_THROTTLE != 0)
         {

            output_debug_string(strDetail);

#if DEBUG_THROTTLE != 0

            double iMillis = DEBUG_THROTTLE * 1000;

#else
            strsize iFind = strDetail.case_insensitive_find("second");

            iFind--;
            while (iFind >= 0 && (ansi_char_isspace(strDetail[iFind])))
            {
               iFind--;
            }
            while (iFind >= 0 && (isdigit_dup(strDetail[iFind]) || strDetail[iFind] == '.'))
            {
               iFind--;
            }

            string strSeconds = strDetail.substr(iFind);

            ::duration ::duration = (::i64) (atof(strSeconds) * 1500.0 + 5000.0);

#endif

            papp->prop("seconds") = 0;
            papp->prop("total_seconds") = __i64(::duration) / 1000;

            bForce = false;
            
            auto tickStart = ::duration::now();

            while (tickStart.elapsed() < ::duration)
            {

               sleep(25_ms);

               papp->prop("seconds") = __i64(::duration - tickStart.elapsed()) / 1000;

            }


            papp->prop("seconds") = 0.0;
            papp->prop("total_seconds") = 0.0;

            goto retry;

         }

      }

      if (iStatusCode == 400)
      {

         TRACE("%s", strResponse.c_str());

         if (strResponse.is_empty())
         {

            if (!bForce)
            {

               bForce = true;

               goto retry;

            }
            else
            {
               return false;

            }

         }

      }
      else if (iStatusCode == 404)
      {

         TRACE("%s", strResponse.c_str());

      }
      else if (iStatusCode != 200 || strResponse.is_empty())
      {

         if (!bForce)
         {

            bForce = true;

            goto retry;

         }
         else
         {
            return false;

         }

      }

      const char * pszJson = strResponse;

      payload.parse_network_payload(pszJson);

      sleep(m_dwApiSleep);

      return true;

   }


   void api::log(string str)
   {

      TRACE("resident_youtube_api: %s", str.c_str());

   }


   string api::randomDataBase64url(u32 length)
   {

      memory m;

      m.random_bytes(length);

      return base64urlencodeNoPadding(m);

   }


   memory api::sha256(string strInput)
   {

      memory m;

      m.from_asc(strInput);

      memory mDst;

      psystem->crypto().sha256(mDst, m);

      return mDst;

   }


   string api::base64urlencodeNoPadding(memory m)
   {

      string str = pbase64->encode(m);

      // Converts base64 to base64url.
      str.replace("+", "-");
      str.replace("/", "_");
      // Strips padding.
      str.replace("=", "");

      return str;

   }


} // namespace resident_youtube



