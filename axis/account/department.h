//
//  account_account.hpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 12/12/18.
//

namespace account
{


   class CLASS_DECL_AXIS department :
      virtual public ::acme::department
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

//      duration                   m_durationSessionTimeout;
//
//
      
      
      department();
      ~department() override;


      void initialize(::object * pobject) override;


      class ::pointer<class authenticator> authenticator();


      ::file::path system_storage_default_path_prefix();

      virtual user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//      virtual user * fecth_user(::file::path pathUrl = nullptr, bool bInteractive = true);
      //    virtual user * noninteractive_get_user(::file::path pathUrl = nullptr);

      bool is_authenticated(::file::path pathUrl = nullptr, bool bInteractive = true);

      //::pointer<credentials>get_credentials(::file::path pathUrl, bool bInteractive = true);

      virtual product * get_product(string strAppId, bool bFetch = false, bool bInteractive = true);
//      virtual product * interactive_get_product(string strAppId);
//      virtual product * noninteractive_get_product(string strAppId);

      bool is_licensed(string strAppId, bool bInteractive = true);

      virtual bool url_requires_auth(::file::path pathUrl);

      virtual void on_user_logon(user * puser);



      virtual void not_auth(::file::path pathUrl);

      virtual duration get_session_timeout();


      class storage * storage();


      ::file::path get_default_url();

      void on_clock(enum_timer etimer);


   };


} // namespace account
