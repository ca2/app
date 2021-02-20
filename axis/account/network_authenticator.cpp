//
//  account_network_credentials.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"
#include "network_authenticator.h"
//#include "aqua/xml.h"


namespace account
{


   network_authenticator::network_authenticator(::layered * pobjectContext) :
      ::object(pobjectContext),
      authenticator(pobjectContext)
   {


   }


   network_authenticator::~network_authenticator()
   {

   }


   ::e_status     network_authenticator::pre_authenticate(credentials * pcredentials)
   {

      pcredentials->m_puser->m_strAccountServer.Empty();

      ::e_status     estatus = get_account_server(pcredentials);

      if(::failed(estatus))
      {

         return estatus;

      }

      if(pcredentials->m_puser->m_strSessId.is_empty())
      {

         return error_pre_authentication_missing_sessid;

      }

      if(pcredentials->m_puser->m_strAccountServer.is_empty())
      {

         return error_pre_authentication_missing_account_server;

      }

      return success_pre_authenticated;

   }


   ::e_status  network_authenticator::authenticate(credentials * pcredentials)
   {

      ::e_status     estatus = network_authentication(pcredentials);

      if(estatus != ::success)
      {

         return estatus;

      }

      __throw(todo("xml->json"));

      //xml::document doc;

      //doc.load(pcredentials->m_strResponse);

      //auto proot = doc.root();

      //if(proot->get_name() != "response")
      //{

      //   return error_authentication;

      //}

      //string strDecrypt;

      //string strId = proot->attribute("id");

      //if(strId == "auth")
      //{

      //   auto puser = pcredentials->m_puser;

      //   puser->m_strSessId = proot->attribute("sessid");

      //   puser->m_strUserId = proot->attribute("secureuserid");

      //   puser->m_strLoginStats = proot->attribute("stats");

      //   pcredentials->m_strPasshash = proot->attribute("passhash");

      //   estatus = ::success_authenticated;

      //   if(puser->m_strHost == System.url().get_server(psession->account()->get_default_url()))
      //   {

      //      Context.file().put_contents(Context.dir().appdata()/"database/text/last_good_known_account_com.txt", puser->m_strAccountServer);

      //   }

      //}
      //else if(proot->attribute("id") == "registration_deferred")
      //{

      //   estatus = ::error_registration_deferred;

      //}
      //else if(proot->attribute("id") == "not_auth")
      //{

      //   if(proot->attribute("detail") == "please_finish_registration")
      //   {

      //      estatus = ::error_please_finish_registration;

      //   }
      //   else if(proot->attribute("detail") == "wrong_password_or_login")
      //   {

      //      estatus = error_authentication_wrong_password_or_login;

      //   }
      //   else if(proot->attribute("detail") == "no_login")
      //   {

      //      estatus = error_credentials_no_login;

      //   }
      //   else if(proot->attribute("detail") == "no_password")
      //   {

      //      estatus = error_credentials_no_password;

      //   }
      //   else
      //   {

      //      estatus = error_authentication;

      //   }

      //}
      //else
      //{

      //   estatus = error_authentication;

      //}

      return estatus;

   }


   ::e_status     network_authenticator::network_authentication(credentials * pcredentials)
   {

      auto puser = pcredentials->m_puser;

      string strHost = puser->m_strHost;

      if(strHost.is_empty())
      {

         TRACE("Host is missing. Has pre_login been called and succeeded?");

         return error_authentication_missing_host;

      }

      string strSessId;

      string strRsa;

      auto tickGetLoginBeg = ::millis::now();

      strSessId = puser->m_strSessId;

      strRsa = pcredentials->m_strRsa;

      if(strSessId.is_empty())
      {

         return error_pre_authentication_missing_sessid;

      }

      if(strRsa.is_empty())
      {

         return error_pre_authentication_invalid;

      }

      auto tickGetLoginEnd = ::millis::now();

      TRACE("NetLogin: Get Login Millis = " __prtick,__pr(tickGetLoginEnd - tickGetLoginBeg));

      string strPass;

      string strAuth;

      auto tickAuthBeg = ::millis::now();

      string strAuthUrl("https://ca2.cc/api/account/auth3");

      string strDeferRegistration;

      if(puser->m_bDeferRegistration)
      {

         System.url().set_param(strAuthUrl, "defer_registration", "true");

      }

      if(puser->m_bDeferRegistration)
      {

         System.url().set_param(strAuthUrl, "ruri", System.url().url_encode(puser->m_pathRuri));

      }

      System.url().set_param(strAuthUrl, "sessid", puser->m_strSessId);

      property_set set;

      if (pcredentials->m_strPasshash.is_empty())
      {

         set["post"]["entered_pass"] = pcredentials->m_strPassword;

      }
      else
      {

         set["post"]["entered_hash"] = pcredentials->m_strPasshash;

      }

      string strCrypt;

      set["post"]["entered_user"] = puser->m_strLogin;

      set["app"] = get_context_application();

      set["user"] = puser;

      set["cookies"] = puser->m_phttpcookies;

      auto tickTimeProfile1 = ::millis::now();

      auto strResponse = Context.http().get(strAuthUrl, set);

      pcredentials->m_strResponse = strResponse;

      pcredentials->m_estatusHttp = (::e_status    ) set["get_status"].i64();

      TRACE("login_task::NetLogin Total time Context.http().get(\"%s\") : " __prtick, strAuthUrl.c_str(), __pr(tickTimeProfile1.elapsed()));

      TRACE("NetLogin: Authentication Millis = " __prtick, __pr(tickAuthBeg.elapsed()));

      return ::success;

   }


   ::e_status     network_authenticator::get_account_server(credentials * pcredentials)
   {

      ::e_status     estatus = error_failed;

      for(index iTry = 0; iTry < 2; iTry++)
      {

         estatus = _get_account_server(pcredentials);

         if(::succeeded(estatus))
         {

            return estatus;

         }

      }

      return estatus;

   }


   ::e_status     network_authenticator::_get_account_server(credentials * pcredentials)
   {

      auto puser = pcredentials->m_puser;

      //auto pinteractive = pcredentials->m_pinteractive;

      puser->m_strHost = System.url().get_server(puser->m_pathUrl);

      string strGetFontopus;

      strGetFontopus = "https://ca2.cc/get_account_login";

      System.url().set_param(strGetFontopus,strGetFontopus,"lang",Context.get_locale());

      System.url().set_param(strGetFontopus,strGetFontopus,"styl",Context.get_schema());

      string strNode;

      i32 iRetry = 2;

      try
      {

         millis tickStart = ::millis::now();

         ::property_set set;

         set["timeout"] = 30'000;

         set["try"] = iRetry <= 1 ? 2 : 1;

         set["raw_http"] = true;

         strNode = Context.http().get(strGetFontopus, set);

         if(::failed(set["get_status"]))
         {

            return set["get_status"];

         }

         millis tickEnd = ::millis::now();

         TRACE( "get_account_login HTTP GET time = %dms", set["http_get_serial"].i64(),  (tickEnd - tickStart).m_i);

      }
      catch(...)
      {

      }

      strNode.trim();

      if(strNode.is_empty())
      {

         return error_failed;

      }

      __throw(todo("xml->js"));

      //::xml::document doc;

      //if(!doc.load(strNode))
      //{

      //   return error_failed;

      //}

      //auto proot = doc.root();

      //if(proot->get_name() != "login")
      //{

      //   return error_failed;

      //}

      //string strSessId = proot->attribute("sessid");

      //if(strSessId.get_length() < 16)
      //{

      //   return error_failed;

      //}

      //string strAccountServer = proot->attribute("account_server");

      //if(strAccountServer.is_empty())
      //{

      //   return error_failed;

      //}

      //string strRsa;

      //strRsa = proot->attribute("rsa_modulus");

      //if(strRsa.length() < 32)
      //{

      //   return error_failed;

      //}

      //puser->m_strSessId = strSessId;

      //puser->m_strAccountServer = strAccountServer;

      //pcredentials->m_strRsa = strRsa;

      //string strSibling;

      //strSibling = proot->attribute("some_brothers_and_sisters");

      //puser->m_straSiblingServers.explode(";", strSibling);

      //::xml::node * pnodeForm = proot->get_child("form");

      //if(pnodeForm != nullptr)
      //{

      //   pcredentials->m_strLabel_user = pnodeForm->attribute("email");

      //   pcredentials->m_strLabel_pass = pnodeForm->attribute("senha");

      //   pcredentials->m_strLabel_open = pnodeForm->attribute("abrir");

      //}

      ////m_mapFontopusServer.set_at(strHost, strFontopusServer);

      return ::success;

   }


//string department::get_server(::file::path pathUrl, i32 iRetry)
//{
//
//   string strHost(System.url().get_server(pszUrl));
//
//   if(iRetry <= 0)
//   {
//
//      iRetry = 1;
//
//   }
//   else if(iRetry > 5)
//   {
//
//      iRetry = 5;
//
//   }
//
//retry:
//
//   iRetry--;
//
//   if(iRetry < 0)
//   {
//
//      return "";
//
//   }
//
//   string strGetFontopus;
//
//   strGetFontopus = "http://ca2.cc/get_account_login";
//
//   System.url().set_param(strGetFontopus,strGetFontopus,"lang",psession->get_locale());
//
//   System.url().set_param(strGetFontopus,strGetFontopus,"styl",psession->get_schema());
//
//   __pointer(::sockets::http_session) psession;
//
//   string strNode;
//
//   try
//   {
//
//      ::u32 dwBeg= ::millis::now();
//
//      ::property_set set;
//
//      set["timeout"] = 3000;
//
//      set["try"] = iRetry <= 1 ? 2 : 1;
//
//      set["raw_http"] = true;
//
//      strNode = Context.http().get(strGetFontopus, set);
//
//      ::u32 tickEnd= ::millis::now();
//
//      TRACE("get_account_login HTTP GET time = %dms",tickEnd - dwBeg);
//
//   }
//   catch(...)
//   {
//
//   }
//
//   strNode.trim();
//
//   if(strNode.is_empty())
//   {
//
//      goto retry;
//
//   }
//
//   ::xml::document doc(get_object());
//
//   if(!doc.load(strNode))
//   {
//
//      goto retry;
//
//   }
//
//   if(doc.get_name() != "login")
//   {
//
//      goto retry;
//
//   }
//
//   string strSessId = doc.attribute("sessid");
//
//   if(strSessId.is_empty())
//   {
//
//      goto retry;
//
//   }
//
//   string strAccountServer = doc.attribute("account_server");
//
//   if(strFontopusServer.is_empty())
//   {
//
//      goto retry;
//
//   }
//
//   string strRsaModulus;
//
//   strRsaModulus = doc.attribute("rsa_modulus");
//
//   if(strRsaModulus.length() < 32)
//   {
//
//      goto retry;
//
//   }
//
//   string strSomeBrothersAndSisters;
//
//   strSomeBrothersAndSisters = doc.attribute("some_brothers_and_sisters");
//
//   synchronizationlock.lock();
//
//   if(strSomeBrothersAndSisters.has_char())
//   {
//
//      string_array straSomeBrothersAndSisters;
//
//      straSomeBrothersAndSisters.explode(";",strSomeBrothersAndSisters);
//
//      for (index i = 0; i < straSomeBrothersAndSisters.get_count(); i++)
//      {
//
//         string strX = straSomeBrothersAndSisters[i];
//
//         m_mapFontopusServer.set_at(straSomeBrothersAndSisters[i], strFontopusServer);
//
//         strX.replace("-api.ca2.cc", "-account.ca2.cc");
//
//         m_mapSomeBrothersAndSisters[strFontopusServer].add_unique(strX);
//
//         //System.sockets().net().m_mapCache.set_at(straSomeBrothersAndSisters[i],item);
//
//      }
//
//   }
//
//   ::xml::node * pnodeForm = doc.get_child("form");
//
//   if(pnodeForm != nullptr)
//   {
//
//      m_mapLabelUser[strFontopusServer] = pnodeForm->attribute("email");
//
//      m_mapLabelPass[strFontopusServer] = pnodeForm->attribute("senha");
//
//      m_mapLabelOpen[strFontopusServer] = pnodeForm->attribute("abrir");
//
//   }
//
//   if(m_mapFontopusSessId[strFontopusServer].is_empty())
//   {
//
//      m_mapFontopusSessId.set_at(strFontopusServer,strSessId);
//
//      m_mapFontopusRsa.set_at(strFontopusServer,strRsaModulus);
//
//      m_mapFontopusServer.set_at(strFontopusServer,strFontopusServer);
//
//   }
//
//   m_mapFontopusServer.set_at(strHost, strFontopusServer);
//
//   return strFontopusServer;
//
//}


} // namespace account



