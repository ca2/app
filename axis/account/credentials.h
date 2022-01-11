//
//  account_credentials.hpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 12/12/18.
//


namespace account
{


   class CLASS_DECL_AXIS credentials :
      virtual public storage_client
   {
   public:


      __pointer(user)                                  m_puser;
      interactive *                             m_pinteractive;
      bool                                      m_bInteractive;
      void                                   m_estatusHttp;
      string                                    m_strTitle;
      ::rectangle_i32                                    m_rectangleDialog;
      string                                    m_strPassword;
      string                                    m_strPasshash;
      strsize                                   m_iPasswordOriginalLength;
      void                                      m_estatus;
      //bool                                      m_bInteractive;

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
      virtual ~credentials();

      virtual void initialize_account_credentials(user * puser, storage * pstorage);
      virtual void initialize_account_credentials(const credentials & credentials);

      virtual bool is_ok();
      virtual void  get_credentials();

      virtual void  interactive_credentials();


      /// input
      /// m_strToken
      virtual void  load_from_storage(::count cTry = 8);

      /// input
      /// m_strToken
      /// m_strUsername
      /// m_strPassword
      virtual void save_to_storage();

      /// input
      /// m_strToken
      /// eresult
      virtual void save_status_to_storage(const void & estatus);


      //virtual void  authenticate();


      virtual void get_mod(string_array & straHash,string_array & straSource);
      virtual string calc_mod_hash();
      virtual string calc_key_hash();
      virtual string calc_ca2_hash();
      virtual bool check_ca2_hash();


   };


} // namespace account



