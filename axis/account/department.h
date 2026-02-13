//
//  account_account.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


#include "acme/platform/department.h"
#include "acme/parallelization/semaphore.h"


namespace account
{


   class CLASS_DECL_AXIS department :
      virtual public ::platform::department
   {
   public:


      ::pointer<user_array>                       m_pusera;
      ::pointer<product_array>                    m_pproducta;
      ::pointer<class storage>                     m_pstorage;
      ::pointer<class authenticator>               m_pauthenticator;
      ::pointer<::task_pool>                      m_ptaskpool;

#if !MOBILE_PLATFORM
      
      semaphore                                    m_semaphoreDialog;

#endif

//      time                   m_timeSessionTimeout;
//
//
      
      
      department();
      ~department() override;


      void initialize(::particle * pparticle) override;


      class ::pointer<class authenticator> authenticator();


      ::file::path system_storage_default_path_prefix();

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//      virtual user * fecth_user(::file::path pathUrl = nullptr, bool bInteractive = true);
      //    virtual user * noninteractive_get_user(::file::path pathUrl = nullptr);

      bool is_authenticated(::file::path pathUrl = nullptr, bool bInteractive = true);

      //::pointer<credentials>get_credentials(::file::path pathUrl, bool bInteractive = true);

      virtual product * get_product(const ::scoped_string & scopedstrAppId, bool bFetch = false, bool bInteractive = true);
//      virtual product * interactive_get_product(const ::scoped_string & scopedstrAppId);
//      virtual product * noninteractive_get_product(const ::scoped_string & scopedstrAppId);

      bool is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive = true);

      virtual bool url_requires_auth(::file::path pathUrl);

      virtual void on_user_logon(::account::user * puser);



      virtual void not_auth(::file::path pathUrl);

      virtual class ::time get_session_timeout();


      class storage * storage();


      ::file::path get_default_url();

      void on_clock(enum_timer etimer);


   };


} // namespace account
