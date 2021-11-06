#pragma once


namespace account
{


   class CLASS_DECL_AXIS user :
      virtual public object
   {
   public:


      bool                                      m_bOpening;
      __pointer(::http::cookies)                       m_phttpcookies;
      string                                    m_strSessId;
      string                                    m_strLogin;
      string                                    m_strUserId;
      
      ::e_status                                      m_estatus;
      ::e_status                                      m_estatusAuthentication;

      ::datetime::time                          m_timeAuthenticationRequest;
      ::datetime::time                          m_timeAuthentication;

      ::file::path                              m_pathFolder;
      __pointer(contact_list)                          m_pcontactlist;
      string                                    m_strLoginStats;
      string                                    m_strServerInfo;
      string                                    m_strAuthResponse;
      i32                                       m_iView;
      string                                    m_strForm;
      bool                                      m_bDeferRegistration;
      string_array                                   m_straSiblingServers;
      
      string                                    m_strHost;
      ::file::path                              m_pathUrl;
      ::file::path                              m_pathRuri;
      string                                    m_strRequestingHost;
      string                                    m_strAccountServer;
      string                                    m_strValidUntil;

      string                                    m_strSalt;
      
      


      user();
      virtual ~user();
      

      virtual ::e_status initialize(::object * pobject) override;


      virtual void logon_local(string strAccount);
      
      virtual void logon(::file::path pathUrl, bool bInteractive);

      virtual ::e_status  do_logon(::file::path pathUrl, bool bInteractive);
      
      void not_auth(string strServer);
      
      virtual bool is_ok();
      
      virtual bool is_authenticated();
      
      void on_clock(enum_timer etimer);
      
   };
   

} // namespace account



