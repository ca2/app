#include "framework.h"


string chunk_split(const string & body,i32 chunklen,const string & end)
{

   strsize pos = 0;
   string strRet;
   strsize iRead;
   while(pos < body.get_length())
   {
      iRead = minimum(chunklen,body.get_length() - pos);
      strRet += body.Mid(pos,iRead);
      strRet += end;
      pos += iRead;
   }

   return strRet;

}


typedef string(*SALT)(__pointer(::aura::application), const char *, string_array &);


namespace account
{


   user::user()
   {

      m_bOpening = false;

      m_estatus = error_authentication_none;

      m_phttpcookies = __new(::http::cookies());

      m_estatus = error_none;

      m_estatusAuthentication = error_none;


   }


   user::~user()
   {

   }


   ::e_status user::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      //if (get_context_session())
      //{

      //   psession->defer_initialize_user_presence();

      //}

      return true;

   }


//   string user::get_sessid(const char * pszText, bool bInteractive)
//   {
//
//      if(::is_null(this))
//      {
//
//         return "";
//
//      }
//
//      if(pszText == nullptr)
//      {
//         pszText = "https://ca2.cc/";
//      }
//      string strText(pszText);
//      if(strText.is_empty())
//      {
//         strText = "https://ca2.cc/";
//      }
//      strText = System.url().get_server(strText);
//      if(strText.is_empty())
//         strText = pszText;
//      string strSessId;
//      if (strText == "api.ca2.cc")
//      {
//         strSessId = psession->account()->m_mapAccountSessId[psession->account()->m_strFirstFontopusServer];
//         if (strSessId.has_char())
//            return strSessId;
//
//      }
//      strSessId = m_sessionidmap[strText];
//      if(strSessId.has_char())
//         return strSessId;
//      string strFontopusServer = psession->account()->get_server(strText, 2);
//      if(strFontopusServer.has_char())
//      {
//
//         strSessId = psession->account()->m_mapFontopusSessId[strFontopusServer];
//
//         if(strSessId.has_char())
//            return strSessId;
//
//      }
//      class validate authuser(get_context_application(), "system\\user\\authenticate.xhtml", true, bInteractive);
//      __pointer(user) puser = authuser.get_user(pszText);
//      if(puser == nullptr)
//         strSessId = "not_auth";
//      else
//      {
//         strSessId = puser->m_strFontopusServerSessId;
//         if(puser->m_strRequestingServer != strText)
//            strSessId = "not_auth";
//         else if(strSessId.is_empty())
//            strSessId = "not_auth";
//      }
//      m_sessionidmap[strText] = strSessId;
//      return strSessId;
//   }
//
//   void user::set_sessid(const char * pszSessid, const char * pszText)
//   {
//      if(pszText == nullptr)
//      {
//         pszText = "https://ca2.cc/";
//      }
//      string strText(pszText);
//      if(strText.is_empty())
//      {
//         strText = "https://ca2.cc/";
//      }
//      strText = System.url().get_server(strText);
//      m_sessionidmap[strText] = pszSessid;
//   }


//   string user::get_ca2_server(const char * pszPrefix)
//   {
//
//      string strPrefix(pszPrefix);
//      string strDomain(".ca2.cc");
//
//      string_array straServer;
//
//      straServer.add(strPrefix + strDomain);
//      straServer.add("eu-" + strPrefix + strDomain);
//      straServer.add("asia-" + strPrefix + strDomain);
//
//      for(i32 i = 0; i < 3; i++)
//      {
//
//         for(i32 j = 0; j < straServer.get_size(); j++)
//         {
//
//            string strSessId = psession->account()->get_sessid(straServer[j]);
//
//            if(strSessId != "not_auth")
//            {
//
//               return straServer[j];
//
//            }
//
//         }
//
//      }
//
//      return straServer[0];
//
//   }


   void user::logon(::file::path pathUrl, bool bInteractive)
   {

      if(m_bOpening)
      {

         return;

      }

      __keep(m_bOpening);

      i32 iRetry = bInteractive ? 3 : 1;

      m_estatusAuthentication = error_authentication;

      while(true)
      {

         try
         {

            m_estatusAuthentication = do_logon(pathUrl, bInteractive);

            if(m_estatusAuthentication == ::success_authenticated)
            {

               break;

            }

            if(m_estatusAuthentication == error_credentials_user_cancelled)
            {

               return;

            }

         }
         catch(...)
         {

         }

         iRetry--;

         if(iRetry <= 0 || !::thread_get_run())
         {

            return;

         }

      }

      if(!is_authenticated())
      {

         TRACE(trace_category_general, e_trace_level_error, "User not logged in!");

         return;

      }

      auto psession = Session;

      psession->account()->on_user_logon(this);

      m_timeAuthentication = ::datetime::time::get_current_time();

   }


   ::e_status  user::do_logon(::file::path pathUrl, bool bInteractive)
   {

      auto psession = Session;

      m_timeAuthenticationRequest = ::datetime::time::get_current_time();

      m_bDeferRegistration = bInteractive;

      __pointer(credentials) pcredentials = __new(credentials);

      pcredentials->initialize_account_credentials(this, psession->account()->storage());

      pcredentials->      m_bInteractive = bInteractive;


      m_pathUrl = pathUrl;

      m_estatusAuthentication = psession->account()->authenticator()->pre_authenticate(pcredentials);

      if(m_estatusAuthentication != ::success_pre_authenticated)
      {

         defer_failed(m_estatusAuthentication, error_pre_authentication);

         return m_estatus;

      }

      //string strPassword;

      //string strUsername;

      //m_pcredentials->m_pathUrl

      //m_pcredentials->m_strToken = m_strRequestingHost;

      //      m_eresult = Application.interactive_credentials(thisget_app(), m_pathUrl, nullptr, strUsername, strPassword, m_strRequestingHost, "ca2", m_bInteractive);

      m_estatusAuthentication = pcredentials->get_credentials();

      if(m_estatusAuthentication != ::success_credentials || !pcredentials->is_ok())
      {

         if(m_estatusAuthentication == ::success_credentials)
         {

            m_estatusAuthentication = pcredentials->m_estatus;

         }

         defer_failed(m_estatusAuthentication, error_credentials);

         return m_estatusAuthentication;

      }

      auto pauthenticator = psession->account()->authenticator();

      m_estatusAuthentication = pauthenticator->authenticate(pcredentials);

      if(m_estatusAuthentication != ::success_authenticated)
      {

         defer_failed(m_estatusAuthentication, error_authentication);

         pcredentials->m_strPassword.Empty();

      }

      pcredentials->save_to_storage();

      pcredentials->save_status_to_storage(m_estatusAuthentication);

      //}
      //else
      //{

      // ::account::set_cred(get_context_application(), "ca2", "", "");

      //::account::set_cred_ok(get_context_application(), "ca2", false);

      //}

      //return m_puser;

      return m_estatusAuthentication;

   }


//   string user::get_session_secret()
//   {
//
//      return m_strSecret;
//
//   }


   void user::logon_local(string strAccount)
   {

      m_strLogin = strAccount;

      m_strSessId = "local";

      m_estatus = ::success;

      m_estatusAuthentication = ::success_none;

   }



   void user::not_auth(string strServer)
   {

      m_strSessId = "not_auth";

   }

   bool user::is_ok()
   {

      if(::failed(m_estatus))
      {

         return false;

      }

      return true;

   }


   bool user::is_authenticated()
   {

      on_clock(e_clock_slow);

      if(m_estatusAuthentication != ::success_authenticated)
      {

         return false;

      }

      if(m_strLogin.get_length() <= 3)
      {

         m_estatusAuthentication = error_credentials_invalid_login;

         return false;

      }

      if(m_strSessId.get_length() < 16)
      {

         m_estatusAuthentication = error_authentication_invalid_sessid;

         return false;

      }

      return true;

   }


   void user::on_clock(enum_clock eclock)
   {

      if(eclock == e_clock_slow)
      {

         if(m_estatusAuthentication == ::success_authenticated)
         {

            auto authenticationRequestElapsed = ::datetime::time::get_current_time() - m_timeAuthenticationRequest;

            auto authenticationDoneElapsed = ::datetime::time::get_current_time() - m_timeAuthentication;

            auto authenticationElapsed = minimum(authenticationRequestElapsed, authenticationDoneElapsed);

            auto psession = Session;

            auto authenticationTimeout = psession->account()->get_session_timeout();

            if(authenticationElapsed > authenticationTimeout)
            {

               m_estatusAuthentication = error_authentication_session_expired;

            }

         }

      }

   }




} // namespace account



