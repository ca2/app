#pragma once


#include "aura/platform/session.h"


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session
   {
   public:


      //::pointer<::account::department>                m_paccount;


      session();
      ~session() override;


      virtual void initialize(::particle * pparticle) override;


      virtual void process_init() override;

      virtual void init1() override;

      virtual void init2() override;

      virtual void init() override;

      virtual void term() override;


      virtual void term2() override;

      virtual void term1() override;

      virtual void process_term() override;

      virtual void on_instantiate_application(::platform::application* papp) override;

      //virtual ::user::style* user_style() override;

      virtual ::account::department * account();

      virtual void on_user_logon(::account::user* puser);

      ::axis::user* axisuser() override;

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual void on_erase_user(::account::user * puser);

      virtual bool is_licensed(const ::string & pszId, bool bInteractive = true) override;

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      //::aura::application * application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::request * prequest) override;

      virtual void install_message_routing(::channel* pchannel) override;


      virtual bool InitializeLocalDataCentral() override;


   };


} // namespace axis



