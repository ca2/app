//
//  account_account.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#include "framework.h"
#include "department.h"
#include "user_array.h"
#include "product_array.h"
#include "user.h"
#include "system_storage.h"
#include "network_authenticator.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/constant/timer.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/prototype/prototype/url.h"
#include "acme/prototype/prototype/url_domain.h"
#include "acme/parallelization/pool.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/prototype/string/str.h"
#include "axis/platform/session.h"


namespace account
{


   department::department() 
#if !MOBILE_PLATFORM
      : m_semaphoreDialog(1, 1, "Local\\core_account_dialog")
#endif
   {

      defer_create_synchronization();

   }


   department::~department()
   {

   }




//   credentials * department::create_credentials()
//   {
//
//      return øallocate network_credentials(m_pstorage);
//
//   }
//
//
   ::file::path department::system_storage_default_path_prefix()
   {

      return directory_system()->userconfig() / "credential_storage";

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


   product * department::get_product(const ::scoped_string & scopedstrAppId, bool bFetch, bool bInteractive)
   {

      return m_pproducta->get_product(scopedstrAppId, bFetch, bInteractive);

   }


//   product * department::interactive_get_product(const ::scoped_string & scopedstrAppId)
//   {
//
//      return m_pproducta->interactive_get_product(strAppId);
//
//   }
//
//
//   product * department::noninteractive_get_product(const ::scoped_string & scopedstrAppId)
//   {
//
//      return m_pproducta->noninteractive_get_product(strAppId);
//
//   }
//

   bool department::is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive)
   {

      return m_pproducta->is_licensed(scopedstrAppId, bInteractive);

   }

   
   bool department::url_requires_auth(::file::path pathUrl)
   {

      ::url::url url(pathUrl);

      if (url.connect().host().case_insensitive_equals("ca2.network"))
      {

         return false;

      }

      if(::str::case_insensitive_find("/matter.ca2.network/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str::case_insensitive_find("-matter.ca2.network/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str::case_insensitive_find("sessid=", pathUrl) >= 0)
      {

         return false;

      }

      if (url.request().path().case_insensitive_contains("/matter/"))
      {

         return false;

      }

      string strServer = url.connect().host();

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


//   string department::get_server(::file::path pathUrl, int iRetry)
//   {
//
//   }
//
//
//   string department::_get_server(::file::path pathUrl, int iRetry)
//   {
//
//   }


//   string department::get_account_server(::file::path pathUrl, int iRetry)
//   {
//
//      string strRequestingServer = purl->get_server(pathUrl);
//
//      unsigned int dwGetFontopusBeg= ::time::now();
//
//      string strGetFontopus;
//
//      if(string_ends(strRequestingServer,".ca2.network"))
//      {
//         strGetFontopus = "https://ca2.network/get_account_login";
//      }
//      else
//      {
//         strGetFontopus = "https://ca2.network/get_account_login";
//      }
//
//      //      ::aura::application * papp = get_app();
//
//      url_domain domainFontopus;
//
//      string strFontopusServer = psession->account()->get_server(strGetFontopus, 2);
//
//      domainFontopus.create(strFontopusServer);
//
//      if(domainFontopus.m_strRadix != "ca2" && domainFontopus.m_strRadix != "account")
//         return "";
//
//      if(strRequestingServer == "ca2.network")
//         return "ca2.network";
//
//      unsigned int dwGetFontopusEnd= ::time::now();
//
//      informationf("NetLogin: Get Fontopus Millis = %d",dwGetFontopusEnd - dwGetFontopusBeg);
//
//      return strFontopusServer;
//
//   }


   void department::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::acme::department::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      øconstruct_new(m_ptaskpool);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pstorage = øallocate system_storage();

      m_pstorage = pstorage;

      //estatus =
      
      pstorage->initialize_system_storage(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pauthenticator = øcreate_new< network_authenticator >();

      auto pusera = øallocate user_array();
      
      m_pusera = pusera;

      //estatus = 
      
      pusera->initialize_user_array(this);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      m_pproducta = øallocate product_array();

      //estatus = 
      
      m_pproducta->initialize_product_array(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   ::pointer<authenticator>department::authenticator()
   {

      return m_pauthenticator;

   }


   void department::not_auth(::file::path pathUrl)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto puser = get_user(pathUrl);

      if(puser == nullptr)
      {

         return;

      }

      puser->m_estatus.defer_failed(error_authentication);

   }


   ::file::path department::get_default_url()
   {

      return "https://ca2.network/";

   }


   void department::on_user_logon(::account::user * puser)
   {

      if(::is_null(puser))
      {

         return;

      }

      m_ptaskpool->set_timer(e_timer_slow, 1_minute);

      auto psession = session();

      psession->on_user_logon(puser);

   }


   class ::time department::get_session_timeout()
   {

#ifdef _DEBUG

      return 3_minutes;

#else // __DEBUG

      return 15_minutes;

#endif // !__DEBUG

   }


   void department::on_clock(enum_timer etimer)
   {

      if(etimer == e_timer_slow)
      {

         m_pusera->on_clock(etimer);

      }

   }


} // namespace account



