#include "framework.h"
#include "user.h"
#include "department.h"
#include "credentials.h"
#include "authenticator.h"
#include "acme/constant/timer.h"
////#include "acme/exception/exception.h"
#include "acme/platform/keep.h"
#include "apex/networking/http/cookie.h"
#include "axis/platform/session.h"


string chunk_split(const string & body,int chunklen,const string & end)
{

   character_count pos = 0;
   string strRet;
   character_count iRead;
   while(pos < body.length())
   {
      iRead = minimum(chunklen,body.length() - pos);
      strRet += body.substr(pos,iRead);
      strRet += end;
      pos += iRead;
   }

   return strRet;

}


//typedef string(*SALT)(::pointer<::aura::application> const ::scoped_string & scopedstr, string_array_base &);


namespace account
{


   user::user()
   {

      m_bOpening = false;

      m_estatus = error_authentication_none;

      m_phttpcookies = øallocate ::http::cookies();

      m_estatus = error_none;

      m_estatusAuthentication = error_none;


   }


   user::~user()
   {

   }


   void user::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::particle::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (get_session())
      //{

      //   psession->defer_initialize_user_presence();

      //}

//      return true;

   }


//   string user::get_sessid(const ::scoped_string & scopedstrText, bool bInteractive)
//   {
//
//      if(::is_null(this))
//      {
//
//         return "";
//
//      }
//
//      if(scopedstrText == nullptr)
//      {
//         pszText = "https://ca2.network/";
//      }
//      string strText(scopedstrText);
//      if(strText.is_empty())
//      {
//         strText = "https://ca2.network/";
//      }
//      strText = purl->get_server(strText);
//      if(strText.is_empty())
//         strText = pszText;
//      string strSessId;
//      if (strText == "api.ca2.network")
//      {
//         strSessId = psession->account()->m_mapAccountSessId[psession->account()->m_strFirstFontopusServer];
//         if (strSessId.has_character())
//            return strSessId;
//
//      }
//      strSessId = m_sessionidmap[strText];
//      if(strSessId.has_character())
//         return strSessId;
//      string strFontopusServer = psession->account()->get_server(strText, 2);
//      if(strFontopusServer.has_character())
//      {
//
//         strSessId = psession->account()->m_mapFontopusSessId[strFontopusServer];
//
//         if(strSessId.has_character())
//            return strSessId;
//
//      }
//      class validate authuser(get_app(), "system\\user\\authenticate.xhtml", true, bInteractive);
//      ::pointer<user>puser = authuser.get_user(scopedstrText);
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
//   void user::set_sessid(const ::scoped_string & scopedstrSessid, const ::scoped_string & scopedstrText)
//   {
//      if(scopedstrText == nullptr)
//      {
//         pszText = "https://ca2.network/";
//      }
//      string strText(scopedstrText);
//      if(strText.is_empty())
//      {
//         strText = "https://ca2.network/";
//      }
//      strText = purl->get_server(strText);
//      m_sessionidmap[strText] = pszSessid;
//   }


//   string user::get_ca2_server(const ::scoped_string & scopedstrPrefix)
//   {
//
//      string strPrefix(scopedstrPrefix);
//      string strDomain(".ca2.network");
//
//      string_array_base straServer;
//
//      straServer.add(strPrefix + strDomain);
//      straServer.add("eu-" + strPrefix + strDomain);
//      straServer.add("asia-" + strPrefix + strDomain);
//
//      for(int i = 0; i < 3; i++)
//      {
//
//         for(int j = 0; j < straServer.get_size(); j++)
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

      KEEP(m_bOpening);

      int iRetry = bInteractive ? 3 : 1;

      m_estatusAuthentication = error_authentication;

      while(true)
      {

         try
         {

            do_logon(pathUrl, bInteractive);

            break;

         }
         catch(const ::exception & exception)
         {

            m_estatusAuthentication = exception.m_estatus;

            if (m_estatusAuthentication == error_credentials_user_cancelled)
            {

               return;

            }

         }

         iRetry--;

         if(iRetry <= 0 || !::task_get_run())
         {

            return;

         }

      }

      if(!is_authenticated())
      {

         error() <<"User not logged in!";

         return;

      }

      auto psession = m_papplication->m_psession;

      psession->account()->on_user_logon(this);

      m_timeAuthentication = ::earth::time::now();

   }


   void user::do_logon(::file::path pathUrl, bool bInteractive)
   {

      m_timeAuthenticationRequest = ::earth::time::now();

      m_bDeferRegistration = bInteractive;

      ::pointer<credentials>pcredentials = øallocate credentials();

      auto psession = session();

      pcredentials->initialize_account_credentials(this, psession->account()->storage());

      pcredentials->      m_bInteractive = bInteractive;

      m_pathUrl = pathUrl;

      try
      {

         psession->account()->authenticator()->pre_authenticate(pcredentials);

         m_estatusAuthentication = ::success_pre_authenticated;

      }
      catch(const ::exception & exception)
      {

         m_estatusAuthentication = exception.m_estatus;
      
         m_estatusAuthentication.defer_failed(error_pre_authentication);

         throw exception;

      }

      //string strPassword;

      //string strUsername;

      //m_pcredentials->m_pathUrl

      //m_pcredentials->m_strToken = m_strRequestingHost;

      //      m_eresult = papp->interactive_credentials(thisget_app(), m_pathUrl, nullptr, strUsername, strPassword, m_strRequestingHost, "ca2", m_bInteractive);

      try
      {

         pcredentials->get_credentials();

         m_estatusAuthentication = ::success_credentials;

      }
      catch (const ::exception& exception)
      {

         m_estatusAuthentication = exception.m_estatus;

      }

      if(m_estatusAuthentication != ::success_credentials || !pcredentials->is_ok())
      {

         if(m_estatusAuthentication == ::success_credentials)
         {

            m_estatusAuthentication = pcredentials->m_estatus;

         }

         m_estatusAuthentication.defer_failed(error_credentials);

         throw ::exception(m_estatusAuthentication);

      }

      auto pauthenticator = psession->account()->authenticator();

      try
      {

          pauthenticator->authenticate(pcredentials);

          m_estatusAuthentication = success_authenticated;

      }
      catch (const ::exception& exception)
      {

         m_estatusAuthentication = exception.m_estatus;
         
         m_estatusAuthentication.defer_failed(error_authentication);

         pcredentials->m_strPassword.empty();

         throw exception;

      }

      pcredentials->save_to_storage();

      pcredentials->save_status_to_storage(m_estatusAuthentication);

      //}
      //else
      //{

      // ::account::set_cred(get_app(), "ca2", "", "");

      //::account::set_cred_ok(get_app(), "ca2", false);

      //}

      //return m_puser;

      //return m_estatusAuthentication;

   }


//   string user::get_session_secret()
//   {
//
//      return m_strSecret;
//
//   }


   void user::logon_local(const ::scoped_string & scopedstrAccount)
   {

      m_strLogin = scopedstrAccount;

      m_strSessId = "local";

      m_estatus = ::success;

      m_estatusAuthentication = ::success_none;

   }



   void user::not_auth(const ::scoped_string & scopedstrServer)
   {

      m_strSessId = "not_auth";

   }

   bool user::is_ok()
   {

      if(m_estatus.failed())
      {

         return false;

      }

      return true;

   }


   bool user::is_authenticated()
   {

      on_clock(e_timer_slow);

      if(m_estatusAuthentication != ::success_authenticated)
      {

         return false;

      }

      if(m_strLogin.length() <= 3)
      {

         m_estatusAuthentication = error_credentials_invalid_login;

         return false;

      }

      if(m_strSessId.length() < 16)
      {

         m_estatusAuthentication = error_authentication_invalid_sessid;

         return false;

      }

      return true;

   }


   void user::on_clock(enum_timer etimer)
   {

      if(etimer == e_timer_slow)
      {

         if(m_estatusAuthentication == ::success_authenticated)
         {

            auto authenticationRequestElapsed = ::earth::time::now() - m_timeAuthenticationRequest;

            auto authenticationDoneElapsed = ::earth::time::now() - m_timeAuthentication;

            auto authenticationElapsed = minimum(authenticationRequestElapsed, authenticationDoneElapsed);

            auto psession = session();

            auto authenticationTimeout = psession->account()->get_session_timeout();

            if(authenticationElapsed > authenticationTimeout)
            {

               m_estatusAuthentication = error_authentication_session_expired;

            }

         }

      }

   }




} // namespace account



