#pragma once


#include "aura/platform/application.h"
#include "axis/account/interactive.h"
#include "axis/user/user/form_handler.h"


namespace geo
{

   class geo;

} // namespace geo


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
      virtual public ::account::interactive,
      virtual public ::axis::form_handler
   {
   public:


      //::pointer<::simpledb::server>                        m_psimpledb;
      

      application();
      ~application() override;
      
      void on_set_platform() override;

      void initialize(::particle * pparticle) override;

      ::pointer < ::geo::geo > create_geo() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      bool assert_user_logged_in() override;

       string __get_text(const ::scoped_string & scopedstr) override;

      //virtual ::user::style* get_user_style() const;
    
      ::string calculate_data_key() override;




      ::simpledb::server * simpledb() override;
      ::database::server * dataserver() override;


      void verb() override;


      bool Ex2OnAppInstall() override;
      bool Ex2OnAppUninstall() override;

      //virtual void init_application() override;

      void init1() override;
      void init2() override;
      void init3() override;


      void init() override;


      void init_instance() override;


      void run() override;
      //void     main() override;
      void on_run() override;

      //void application_pre_run() override;
      //void os_native_bergedge_start() override;





      void term() override;


      void term_application() override;




      //bool InitApplication() override;


      void process_init() override;








      //bool app_data_set(const ::atom & atom, stream & os) override;
      //bool app_data_get(const ::atom & atom, stream & is) override;

      bool app_data_set(const ::atom & atom, ::object & obj) override;
      bool app_data_get(const ::atom & atom, ::object & obj) override;




      void process_term() override;


      void term1() override;
      void term2() override;
      void term3() override;






      //virtual string http_get_locale_schema(const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      //virtual void on_update_matter_locator() override;

      //virtual void locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual void matter_locator_locale_schema_matter(string_array_base & stra, const string_array_base & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);

      //virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema);
      //virtual string get_locale_schema_dir(const ::scoped_string & scopedstrLocale);
      //virtual string get_locale_schema_dir() override;

      //virtual void set_locale(const string & pcsz, const ::action_context & action_context);

      //virtual void set_schema(const string & pcsz, const ::action_context & action_context);

 /*     virtual void on_set_locale(const string & pcsz, const ::action_context & action_context);

      virtual void on_set_schema(const string & pcsz, const ::action_context & action_context);
*/



      void interactive_credentials(::account::credentials * pcredentials) override;

  
      ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true) override;

      ::account::user * interactive_get_user(::file::path pathUrl = nullptr) override;

      ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr) override;

     
      ::type_atom control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype) override;
      ::user::interaction* create_menu_interaction() override;
//      void handle_url(const ::scoped_string & scopedstrUrl) override;

      //::user::user * axisuser() override;

   };


} // namespace axis








