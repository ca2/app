//
//  account_account.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
//
#include "framework.h"
#include "system_storage.h"
#include "network_authenticator.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/constant/timer.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/parallelization/pool.h"
#include "department.h"
#include "user_array.h"
#include "product_array.h"
#include "user.h"
#include "axis/platform/session.h"


namespace account
{


   department::department() 
#if !MOBILE_PLATFORM
      : m_semaphoreDialog(1, 1, "Local\\core_account_dialog")
#endif
   {

      defer_create_mutex();

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

      return m_psystem->m_pacmedirectory->system() / "credential_storage";

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

      auto psystem = m_psystem;

      auto purl = psystem->url();

      if (purl->get_server(pathUrl).lowered() == "server.ca2.software")
      {

         return false;

      }

      if(::str().find_ci("/matter.ca2.software/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str().find_ci("-matter.ca2.software/", pathUrl) >= 0)
      {

         return false;

      }

      if(::str().find_ci("sessid=", pathUrl) >= 0)
      {

         return false;

      }

      if(::str().find_ci("/matter/",purl->get_script(pathUrl)) >= 0)
      {

         return false;

      }

      string strServer = purl->get_server(pathUrl);

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
//      string strRequestingServer = purl->get_server(pathUrl);
//
//      ::u32 dwGetFontopusBeg= ::duration::now();
//
//      string strGetFontopus;
//
//      if(::str().ends(strRequestingServer,".ca2.software"))
//      {
//         strGetFontopus = "https://ca2.software/get_account_login";
//      }
//      else
//      {
//         strGetFontopus = "https://ca2.software/get_account_login";
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
//      if(strRequestingServer == "ca2.software")
//         return "ca2.software";
//
//      ::u32 dwGetFontopusEnd= ::duration::now();
//
//      FORMATTED_TRACE("NetLogin: Get Fontopus Millis = %d",dwGetFontopusEnd - dwGetFontopusBeg);
//
//      return strFontopusServer;
//
//   }


   void department::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::acme::department::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //estatus = 
      
      __construct_new(m_ptaskpool);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto pstorage = __new(system_storage);

      m_pstorage = pstorage;

      //estatus =
      
      pstorage->initialize_system_storage(this);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      m_pauthenticator = __create_new< network_authenticator >();

      auto pusera = __new(user_array);
      
      m_pusera = pusera;

      //estatus = 
      
      pusera->initialize_user_array(this);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      m_pproducta = __new(product_array);

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

      synchronous_lock synchronouslock(mutex());

      auto puser = get_user(pathUrl);

      if(puser == nullptr)
      {

         return;

      }

      defer_failed(puser->m_estatus, error_authentication);

   }


   ::file::path department::get_default_url()
   {

      return "https://ca2.software/";

   }


   void department::on_user_logon(user * puser)
   {

      if(::is_null(puser))
      {

         return;

      }

      m_ptaskpool->set_timer(e_timer_slow, minute());

      ::pointer<::axis::session>psession = get_session();

      psession->on_user_logon(puser);

   }




   duration department::get_session_timeout()
   {

#ifdef __DEBUG

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



