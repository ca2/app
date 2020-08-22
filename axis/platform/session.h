#pragma once


namespace axis
{


   class CLASS_DECL_AXIS session:
      virtual public ::aura::session
   {
   public:

      __composite(::account::department)                    m_paccount;


      session();
      virtual ~session();


      virtual ::estatus     initialize(::object * pobjectContext) override;


      virtual ::estatus process_init();

      virtual ::estatus init1();

      virtual ::estatus init2();

      virtual ::estatus init();

      virtual void term();


      virtual void term2();

      virtual void term1();

      virtual void process_term();

      inline ::account::department * account() { return m_paccount; }

      virtual void on_user_logon(::account::user* puser);

      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual void on_remove_user(::account::user * puser);

      virtual bool is_licensed(const char * pszId, bool bInteractive = true);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      virtual void interactive_credentials(::account::credentials * pcredentials);

      ::aura::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual void install_message_routing(::channel* pchannel) override;



      bool InitializeLocalDataCentral();



     

   };


} // namespace axis



