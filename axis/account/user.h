#pragma once


//#include "acme/filesystem/filesystem/path.h"

////#include "acme/prototype/datetime/earth_time.h"
//#include "acme/prototype/collection/string_array.h"
//#include "acme/prototype/prototype/matter.h"


namespace account
{


   class CLASS_DECL_AXIS user :
      virtual public ::matter
   {
   public:


      bool                                      m_bOpening;
      ::pointer<::http::cookies>                      m_phttpcookies;
      string                                    m_strSessId;
      string                                    m_strLogin;
      string                                    m_strUserId;
      
      ::e_status                                m_estatus;
      ::e_status                                m_estatusAuthentication;

      ::earth::time                          m_timeAuthenticationRequest;
      ::earth::time                          m_timeAuthentication;

      ::file::path                              m_pathFolder;
      ::pointer<contact_list>                         m_pcontactlist;
      string                                    m_strLoginStats;
      string                                    m_strServerInfo;
      string                                    m_strAuthResponse;
      int                                       m_iImpact;
      string                                    m_strForm;
      bool                                      m_bDeferRegistration;
      string_array                              m_straSiblingServers;
      
      string                                    m_strHost;
      ::file::path                              m_pathUrl;
      ::file::path                              m_pathRuri;
      string                                    m_strRequestingHost;
      string                                    m_strAccountServer;
      string                                    m_strValidUntil;

      string                                    m_strSalt;
      

      user();
      ~user() override;
      

      virtual void initialize(::particle * pparticle) override;


      virtual void logon_local(const ::scoped_string & scopedstrAccount);
      
      virtual void logon(::file::path pathUrl, bool bInteractive);

      virtual void  do_logon(::file::path pathUrl, bool bInteractive);
      
      void not_auth(const ::scoped_string & scopedstrServer);
      
      virtual bool is_ok();
      
      virtual bool is_authenticated();
      
      void on_clock(enum_timer etimer);
      
   };
   

} // namespace account



