#pragma once


#include "axis/account/interactive.h"
#include "aura/platform/application.h"


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


      ::pointer<::simpledb::server>                        m_psimpledb;
      

      application();
      ~application() override;


      virtual void initialize(::particle * pparticle) override;


//      void assert_ok() const override;
//      void dump(dump_context & dumpcontext) const override;
      virtual bool assert_user_logged_in() override;

      virtual string __get_text(string str) override;

      //virtual ::user::style* get_user_style() const;
    
      virtual ::database::key calc_data_key() override;




      virtual ::simpledb::server * simpledb();
      virtual ::database::server * dataserver() override;


      virtual void verb() override;


      virtual bool Ex2OnAppInstall() override;
      virtual bool Ex2OnAppUninstall() override;

      //virtual void init_application() override;

      virtual void init1() override;
      virtual void init2() override;
      virtual void init3() override;


      virtual void init() override;


      virtual void init_instance() override;


      virtual void     run() override;
      //virtual void     main() override;
      virtual void     on_run() override;

      virtual void application_pre_run() override;
      virtual void os_native_bergedge_start() override;





      virtual void term() override;


      virtual void term_application() override;




      //virtual bool InitApplication() override;


      virtual void process_init() override;








      //virtual bool app_data_set(const ::atom & atom, stream & os) override;
      //virtual bool app_data_get(const ::atom & atom, stream & is) override;

      virtual bool app_data_set(const ::atom & atom, ::object & obj) override;
      virtual bool app_data_get(const ::atom & atom, ::object & obj) override;




      virtual void process_term() override;


      virtual void term1() override;
      virtual void term2() override;
      virtual void term3() override;






      //virtual string http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema);

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema);

      //virtual string get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema);
      //virtual string get_locale_schema_dir(const ::string & strLocale);
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

     
      virtual ::type control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype) override;
      ::user::interaction* create_menu_interaction() override;
//      void handle_url(const ::string & strUrl) override;

   };


} // namespace axis








