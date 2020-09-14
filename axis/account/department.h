//
//  account_account.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//

namespace account
{


   class CLASS_DECL_AXIS department :
      virtual public ::apex::department
   {
   public:


      __pointer(user_array)             m_pusera;
      __pointer(product_array)          m_pproducta;
      __pointer(class storage)          m_pstorage;
      __pointer(class authenticator)    m_pauthenticator;

#if !MOBILE_PLATFORM
      
      semaphore                  m_semaphoreDialog;

#endif

//      duration                   m_durationSessionTimeout;
//
//
      department();
      virtual ~department();


      class __pointer(class authenticator) authenticator();


      ::file::path system_storage_default_path_prefix();

      virtual user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//      virtual user * fecth_user(::file::path pathUrl = nullptr, bool bInteractive = true);
      //    virtual user * noninteractive_get_user(::file::path pathUrl = nullptr);

      bool is_authenticated(::file::path pathUrl = nullptr, bool bInteractive = true);

      //__pointer(credentials) get_credentials(::file::path pathUrl, bool bInteractive = true);

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


      virtual void on_clock(e_clock eclock) override;


   };


} // namespace account
