//
//  account_account.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//
#include "framework.h"
#include "system_storage.h"
#include "network_authenticator.h"


namespace account
{


   department::department() 
#if !MOBILE_PLATFORM
      : m_semaphoreDialog(1, 1, "Local\\core_account_dialog")
#endif
   {

      defer_create_mutex();

      m_pstorage = __new(system_storage(this));
      m_pauthenticator = __new(network_authenticator(this));
      m_pusera = __new(user_array(this));
      m_pproducta = __new(product_array(this));

   }


   department::~department()
   {

   }


//   credentials * department::create_credentials()
//   {
//
//      return __new(network_credentials(m_pstorage));
//
//   }
//
//
   ::file::path department::system_storage_default_path_prefix()
   {

      return ::dir::system() / "credential_storage";

   }


   user * department::get_user(::file::path pathUrl, bool bFetch, bool bInteractive)
   {

      return m_pusera->get_user(pathUrl, bFetch, bInteractive);

   }


//   user * department::fetch_user(::file::path pathUrl, bool bInteractive)
//   {
//
//      return m_pusera->interactive_get_user(pathUrl, bInteractive);
//
//   }


//   user * department::noninteractive_get_user(::file::path pathUrl)
//   {
//
//      return m_pusera->noninteractive_get_user(pathUrl);
//
//   }


   bool department::is_authenticated(::file::path pathUrl, bool bInteractive)
   {

      return m_pusera->is_authenticated(pathUrl, bInteractive);

   }


   product * department::get_product(string strAppId, bool bFetch, bool bInteractive)
   {

      return m_pproducta->get_product(strAppId, bFetch, bInteractive);

   }


//   product * department::interactive_get_product(string strAppId)
//   {
//
//      return m_pproducta->interactive_get_product(strAppId);
//
//   }
//
//
//   product * department::noninteractive_get_product(string strAppId)
//   {
//
//      return m_pproducta->noninteractive_get_product(strAppId);
//
//   }
//

   bool department::is_licensed(string strAppId, bool bInteractive)
   {

      return m_pproducta->is_licensed(strAppId, bInteractive);

   }

   bool department::url_requires_auth(::file::path pathUrl)
   {

      if (System.url().get_server(pathUrl).lowered() == "server.ca2.cc")
      {

         return false;

      }

      if(::str::find_ci("/matter.ca2.cc/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str::find_ci("-matter.ca2.cc/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str::find_ci("sessid=", pathUrl) >= 0)
      {

         return false;

      }

      if(::str::find_ci("/matter/",System.url().get_script(pathUrl)) >= 0)
      {

         return false;

      }

      string strServer = System.url().get_server(pathUrl);

      url_domain domain;

      domain.create(strServer);

      if(domain.m_strRadix != "ca2" && domain.m_strRadix != "veriwell")
      {

         // Fake/Dummy/veriYSimple implementation

         return false;

      }

      // Fake/Dummy/veriYSimple implementation

      return true;

   }


   class storage * department::storage()
   {

      return m_pstorage;

   }


//   string department::get_server(::file::path pathUrl, i32 iRetry)
//   {
//
//   }
//
//
//   string department::_get_server(::file::path pathUrl, i32 iRetry)
//   {
//
//   }


//   string department::get_account_server(::file::path pathUrl, i32 iRetry)
//   {
//
//      string strRequestingServer = System.url().get_server(pathUrl);
//
//      DWORD dwGetFontopusBeg = ::get_tick();
//
//      string strGetFontopus;
//
//      if(::str::ends(strRequestingServer,".ca2.cc"))
//      {
//         strGetFontopus = "https://ca2.cc/get_account_login";
//      }
//      else
//      {
//         strGetFontopus = "https://ca2.cc/get_account_login";
//      }
//
//      //      ::aura::application * papp = get_context_application();
//
//      url_domain domainFontopus;
//
//      string strFontopusServer = Session.account()->get_server(strGetFontopus, 2);
//
//      domainFontopus.create(strFontopusServer);
//
//      if(domainFontopus.m_strRadix != "ca2" && domainFontopus.m_strRadix != "account")
//         return "";
//
//      if(strRequestingServer == "ca2.cc")
//         return "ca2.cc";
//
//      DWORD dwGetFontopusEnd = ::get_tick();
//
//      TRACE("NetLogin: Get Fontopus Millis = %d",dwGetFontopusEnd - dwGetFontopusBeg);
//
//      return strFontopusServer;
//
//   }


   ::estatus department::initialize(::layered * pobjectContext)
   {

      auto estatus = ::apex::department::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      estatus = __construct_new(m_ptaskpool);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   __pointer(authenticator) department::authenticator()
   {

      return m_pauthenticator;

   }


   void department::not_auth(::file::path pathUrl)
   {

      sync_lock sl(mutex());

      auto puser = get_user(pathUrl);

      if(puser == nullptr)
      {

         return;

      }

      defer_failed(puser->m_estatus, error_authentication);

   }


   ::file::path department::get_default_url()
   {

      return "https://ca2.cc/";

   }


   void department::on_user_logon(user * puser)
   {

      if(::is_null(puser))
      {

         return;

      }

      m_ptaskpool->start_clock(e_clock_slow, one_minute());

      Session.on_user_logon(puser);

   }




   duration department::get_session_timeout()
   {

#ifdef __DEBUG

      return minutes(3);

#else // __DEBUG

      return minutes(15);

#endif // !__DEBUG

   }


   void department::on_clock(enum_clock eclock)
   {

      if(eclock == e_clock_slow)
      {

         m_pusera->on_clock(eclock);

      }

   }


} // namespace account



