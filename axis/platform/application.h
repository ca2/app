#pragma once


namespace axis
{


   enum e_end
   {

      end_close,
      end_app,
      end_session,
      end_system

   };


   class CLASS_DECL_AXIS application :
      virtual public ::aura::application,
      virtual public ::account::interactive
   {
   public:


      __pointer(::simpledb::server)                   m_psimpledb;



      application(const char * pszAppId = nullptr);
      virtual ~application();


      virtual ::estatus initialize(::object * pobjectContext) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      virtual bool assert_user_logged_in();

      virtual string __get_text(string str) override;

      virtual ::user::style* get_user_style() const;
    
      virtual ::database::key calc_data_key() override;




      virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver();


      virtual ::estatus verb() override;


      virtual bool Ex2OnAppInstall();
      virtual bool Ex2OnAppUninstall();

      virtual ::estatus init_application();

      virtual ::estatus init1();
      virtual ::estatus init2();
      virtual ::estatus init3();


      virtual ::estatus init();


      virtual ::estatus init_instance();


      virtual ::estatus     run() override;
      virtual ::estatus     main() override;
      virtual ::estatus     on_run();

      virtual ::estatus application_pre_run();
      virtual ::estatus os_native_bergedge_start();





      virtual void term();


      virtual void term_application();




      virtual bool InitApplication();


      virtual ::estatus process_init();








      virtual bool app_data_set(const ::id & id, stream & os);
      virtual bool app_data_get(const ::id & id, stream & is);

      virtual bool app_data_set(const ::id & id, ::object & obj);
      virtual bool app_data_get(const ::id & id, ::object & obj);




      virtual void process_term();


      virtual void term1();
      virtual void term2();
      virtual void term3();






      //virtual string http_get_locale_schema(const char * pszUrl, const char * pszLocale, const char * pszSchema);

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema);

      //virtual string get_locale_schema_dir(const string & strLocale, const string & strSchema);
      //virtual string get_locale_schema_dir(const string & strLocale);
      //virtual string get_locale_schema_dir() override;

      //virtual void set_locale(const string & pcsz, const ::action_context & action_context);

      //virtual void set_schema(const string & pcsz, const ::action_context & action_context);

 /*     virtual void on_set_locale(const string & pcsz, const ::action_context & action_context);

      virtual void on_set_schema(const string & pcsz, const ::action_context & action_context);
*/



      virtual void interactive_credentials(::account::credentials * pcredentials) override;

  
      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);

      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);

     
 

   };


} // namespace axis








