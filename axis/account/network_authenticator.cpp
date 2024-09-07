//
//  account_network_credentials.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#include "framework.h"
#include "network_authenticator.h"
#include "credentials.h"
#include "user.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/primitive/url.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"
#include "apex/networking/http/context.h"
#include "apex/platform/context.h"


#include "acme/primitive/time/_text_stream.h"


namespace account
{


   network_authenticator::network_authenticator()
   {

   }


   network_authenticator::~network_authenticator()
   {

   }


   void network_authenticator::pre_authenticate(credentials * pcredentials)
   {

      pcredentials->m_puser->m_strAccountServer.empty();

      get_account_server(pcredentials);

      if(pcredentials->m_puser->m_strSessId.is_empty())
      {

         throw ::exception(error_pre_authentication_missing_sessid);

      }

      if(pcredentials->m_puser->m_strAccountServer.is_empty())
      {

         throw ::exception(error_pre_authentication_missing_account_server);

      }

      //return success_pre_authenticated;

   }


   void  network_authenticator::authenticate(credentials * pcredentials)
   {

      network_authentication(pcredentials);

      throw ::exception(todo, "xml->network_payload");

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

      //   if(puser->m_strHost == purl->get_server(psession->account()->get_default_url()))
      //   {

      //      file()->put_contents(dir()->appdata()/"database/text/last_good_known_account_com.txt", puser->m_strAccountServer);

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

      //return estatus;

   }


   void network_authenticator::network_authentication(credentials * pcredentials)
   {

      auto puser = pcredentials->m_puser;

      string strHost = puser->m_strHost;

      if(strHost.is_empty())
      {

         informationf("Host is missing. Has pre_login been called and succeeded?");

         throw ::exception(error_authentication_missing_host);

      }

      string strSessId;

      string strRsa;

      auto tickGetLoginBeg = ::time::now();

      strSessId = puser->m_strSessId;

      strRsa = pcredentials->m_strRsa;

      if(strSessId.is_empty())
      {

         throw ::exception(error_pre_authentication_missing_sessid);

      }

      if(strRsa.is_empty())
      {

         throw ::exception(error_pre_authentication_invalid);

      }

      auto tickGetLoginEnd = ::time::now();

      information() << "NetLogin: Get Login Millis = " << (tickGetLoginEnd - tickGetLoginBeg).integral_second();

      string strPass;

      string strAuth;

      auto tickAuthBeg = ::time::now();

      string strAuthUrl("https://ca2.software/api/account/auth3");

      string strDeferRegistration;

      ::property_set setAuthUrlQuery;

      if(puser->m_bDeferRegistration)
      {

         setAuthUrlQuery["defer_registration"] = "true";

      }

      if(puser->m_bDeferRegistration)
      {

         setAuthUrlQuery["ruri"] =puser->m_pathRuri;

      }

      setAuthUrlQuery["sessid"] = puser->m_strSessId;

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

      set["app"] = get_app();

      set["user"] = puser;

      set["cookies"] = puser->m_phttpcookies;

      auto tickTimeProfile1 = ::time::now();

      auto strResponse = http()->get(strAuthUrl, set);

      pcredentials->m_strResponse = strResponse;

      pcredentials->m_estatusHttp = set["get_status"].as_atom().as_estatus();

      information() << "login_task::NetLogin Total time http()->get(\""<<strAuthUrl<<"\") : " << tickTimeProfile1.elapsed().integral_millisecond();

      information() << "NetLogin: Authentication Millis = " << tickAuthBeg.elapsed().integral_millisecond();

      //return ::success;

   }


   void network_authenticator::get_account_server(credentials * pcredentials)
   {

      for (::collection::index iTry = 0; iTry < 2; iTry++)
      {

         _get_account_server(pcredentials);

      }

   }


   void network_authenticator::_get_account_server(credentials * pcredentials)
   {

      auto puser = pcredentials->m_puser;

      ::url::url url(puser->m_pathUrl);

      puser->m_strHost = url.connect().host();

      ::url::parts partsGetFontopus("https://ca2.software/get_account_login");
      
      partsGetFontopus.arguments()["lang"] = m_pcontext->m_papexcontext->get_locale();

      partsGetFontopus.arguments()["styl"] = m_pcontext->m_papexcontext->get_schema();

      string strNode;

      i32 iRetry = 2;

      auto timeStart = ::time::now();

      ::property_set set;

      set["timeout"] = 30'000;

      set["try"] = iRetry <= 1 ? 2 : 1;

      set["raw_http"] = true;

      auto urlGetFontopus = partsGetFontopus.as_url();

      strNode = http()->get(urlGetFontopus, set);

      if(set["get_status"].failed())
      {

         throw ::exception(set["get_status"].as_estatus());

      }

      auto timeEnd = ::time::now();

      information() << set["http_get_serial"].as_string() << "> get_account_login HTTP GET time = " << (timeEnd - timeStart).integral_millisecond();

      strNode.trim();

      if(strNode.is_empty())
      {

         throw ::exception(error_failed);

      }

      throw ::exception(todo, "xml->js");

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

      //if(strSessId.length() < 16)
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

      //return ::success;

   }


//string department::get_server(::file::path pathUrl, i32 iRetry)
//{
//
//   string strHost(purl->get_server(pszUrl));
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
//   strGetFontopus = "http://ca2.software/get_account_login";
//
//   purl->set_param(strGetFontopus,strGetFontopus,"lang",psession->get_locale());
//
//   purl->set_param(strGetFontopus,strGetFontopus,"styl",psession->get_schema());
//
//   ::pointer<::sockets::http_session>psession;
//
//   string strNode;
//
//   try
//   {
//
//      ::u32 dwBeg= ::time::now();
//
//      ::property_set set;
//
//      set["timeout"] = 3000;
//
//      set["try"] = iRetry <= 1 ? 2 : 1;
//
//      set["raw_http"] = true;
//
//      strNode = http()->get(strGetFontopus, set);
//
//      ::u32 tickEnd= ::time::now();
//
//      informationf("get_account_login HTTP GET time = %dms",tickEnd - dwBeg);
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
//   ::xml::document doc(this);
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
//   synchronouslock.lock();
//
//   if(strSomeBrothersAndSisters.has_char())
//   {
//
//      string_array straSomeBrothersAndSisters;
//
//      straSomeBrothersAndSisters.explode(";",strSomeBrothersAndSisters);
//
//      for (::collection::index i = 0; i < straSomeBrothersAndSisters.get_count(); i++)
//      {
//
//         string strX = straSomeBrothersAndSisters[i];
//
//         m_mapFontopusServer.set_at(straSomeBrothersAndSisters[i], strFontopusServer);
//
//         strX.replace("-api.ca2.software", "-account.ca2.software");
//
//         m_mapSomeBrothersAndSisters[strFontopusServer].add_unique(strX);
//
//         //psystem->sockets().net().m_mapCache.set_at(straSomeBrothersAndSisters[i],item);
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



