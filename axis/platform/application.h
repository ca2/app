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


      virtual ::e_status initialize(::context_object * pcontextobject) override;


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
      virtual bool assert_user_logged_in() override;

      virtual string __get_text(string str) override;

      //virtual ::user::style* get_user_style() const;
    
      virtual ::database::key calc_data_key() override;




      virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver() override;


      virtual ::e_status verb() override;


      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      //virtual ::e_status init_application() override;

      virtual ::e_status init1() override;
      virtual ::e_status init2() override;
      virtual ::e_status init3() override;


      virtual ::e_status init() override;


      virtual ::e_status init_instance() override;


      virtual ::e_status     run() override;
      virtual ::e_status     main() override;
      virtual ::e_status     on_run() override;

      virtual ::e_status application_pre_run() override;
      virtual ::e_status os_native_bergedge_start() override;





      virtual void term() override;


      virtual void term_application() override;




      virtual bool InitApplication() override;


      virtual ::e_status process_init() override;








      virtual bool app_data_set(const ::id & id, stream & os) override;
      virtual bool app_data_get(const ::id & id, stream & is) override;

      virtual bool app_data_set(const ::id & id, ::object & obj) override;
      virtual bool app_data_get(const ::id & id, ::object & obj) override;




      virtual void process_term() override;


      virtual void term1() override;
      virtual void term2() override;
      virtual void term3() override;






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

     
      virtual ::type control_type_from_id(const ::id& id, ::user::enum_control_type& econtroltype) override;
      ::user::interaction* create_menu_interaction() override;


   };


} // namespace axis








