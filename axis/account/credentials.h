//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 12/12/18.
//
#pragma once


#include "storage_client.h"
#include "user.h"
//#include "acme/prototype/geometry2d/_geometry2d.h"
#include "acme/prototype/geometry2d/rectangle.h"


namespace account
{


   class CLASS_DECL_AXIS credentials :
      virtual public storage_client
   {
   public:


      ::pointer<::account::user>                m_puser;
      interactive *                             m_pinteractive;
      bool                                      m_bInteractive;
      ::e_status                                m_estatusHttp;
      string                                    m_strTitle;
      ::int_rectangle                           m_rectangleDialog;
      string                                    m_strPassword;
      string                                    m_strPasshash;
      character_count                                   m_iPasswordOriginalLength;
      ::e_status                                m_estatus;
      //bool                                    m_bInteractive;

      string                                    m_strResponse;

      string                                    m_strModHash;
      string                                    m_strKeyHash;
      string                                    m_strCa2Hash;

      string                                    m_strRsa;
      string                                    m_strSecret;


      string                                    m_strLabel_user;
      string                                    m_strLabel_pass;
      string                                    m_strLabel_open;




      //credentials(user * puser, storage * pstorage);
      //credentials(const credentials & credentials);
      credentials();
      ~credentials() override;

      virtual void initialize_account_credentials(::account::user * puser, storage * pstorage);
      virtual void initialize_account_credentials(const credentials & credentials);

      virtual bool is_ok();
      virtual void get_credentials();

      virtual void interactive_credentials();


      /// input
      /// m_strToken
      virtual ::e_status load_from_storage(::collection::count cTry = 8);

      /// input
      /// m_strToken
      /// m_strUsername
      /// m_strPassword
      virtual void save_to_storage();

      /// input
      /// m_strToken
      /// eresult
      virtual void save_status_to_storage(const ::e_status & estatus);


      //virtual void  authenticate();


      virtual void get_mod(string_array_base & straHash,string_array_base & straSource);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
      virtual bool check_ca2_hash();


   };


} // namespace account



