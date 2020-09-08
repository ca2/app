#pragma once


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session
   {
   public:


      __composite(::account::department)                 m_paccount;


      session();
      virtual ~session();


      virtual ::estatus     initialize(::object * pobjectContext) override;


      virtual ::estatus process_init() override;

      virtual ::estatus init1() override;

      virtual ::estatus init2() override;

      virtual ::estatus init() override;

      virtual void term() override;


      virtual void term2() override;

      virtual void term1() override;

      virtual void process_term() override;

      virtual ::user::style* get_user_style() override;

      inline ::account::department * account() { return m_paccount; }

      virtual void on_user_logon(::account::user* puser);

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual void on_remove_user(::account::user * puser);

      virtual bool is_licensed(const char * pszId, bool bInteractive = true) override;

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      ::aura::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual void install_message_routing(::channel* pchannel) override;


      virtual bool InitializeLocalDataCentral();


   };


} // namespace axis



