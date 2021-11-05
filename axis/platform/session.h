#pragma once


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session
   {
   public:


      __composite(::account::department)                 m_paccount;


      session();
      ~session() override;


      virtual ::e_status initialize(::object * pobject) override;


      virtual ::e_status process_init() override;

      virtual ::e_status init1() override;

      virtual ::e_status init2() override;

      virtual ::e_status init() override;

      virtual void term() override;


      virtual void term2() override;

      virtual void term1() override;

      virtual void process_term() override;

      virtual void on_instantiate_application(::application* papp) override;

      //virtual ::user::style* user_style() override;

      inline ::account::department * account() { return m_paccount; }

      virtual void on_user_logon(::account::user* puser);

      inline ::axis::user* user();

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual void on_erase_user(::account::user * puser);

      virtual bool is_licensed(const ::string & pszId, bool bInteractive = true) override;

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword) override;

      virtual void interactive_credentials(::account::credentials * pcredentials);

      //::aura::application * application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual void install_message_routing(::channel* pchannel) override;


      virtual bool InitializeLocalDataCentral() override;


   };


} // namespace axis



