//
// Created by camilo on 2024-10-28 01:50 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME axis_application_layer_t
   {


      ::pointer<::simpledb::server>                        m_psimpledb;


   };


   class CLASS_DECL_ACME axis_application_layer
   {
   public:

      virtual ::pointer < ::geo::geo > create_geo();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
      //bool assert_user_logged_in() override;

       //string __get_text(string str) override;

      //virtual ::user::style* get_user_style() const;

      //::string calculate_data_key() override;




      virtual ::simpledb::server * simpledb();

      // ::database::server * dataserver() override;
      //
      //
      // void verb() override;
      //
      //
      // bool Ex2OnAppInstall() override;
      // bool Ex2OnAppUninstall() override;
      //
      // //virtual void init_application() override;
      //
      // void init1() override;
      // void init2() override;
      // void init3() override;
      //
      //
      // void init() override;
      //
      //
      // void init_instance() override;

      //
      // void run() override;
      // //void     main() override;
      // void on_run() override;
      //
      // void application_pre_run() override;
      // void os_native_bergedge_start() override;
      //


      //
      //
      // void term() override;
      //
      //
      // void term_application() override;
      //



      //bool InitApplication() override;


      //void process_init() override;








      //bool app_data_set(const ::atom & atom, stream & os) override;
      //bool app_data_get(const ::atom & atom, stream & is) override;

      //bool app_data_set(const ::atom & atom, ::object & obj) override;
      //bool app_data_get(const ::atom & atom, ::object & obj) override;


      //
      //
      // void process_term() override;
      //
      //
      // void term1() override;
      // void term2() override;
      // void term3() override;
      //
      //
      //



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



      //void interactive_credentials(::account::credentials * pcredentials) override;


      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr);

      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr);


      //::type_atom control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype) override;
      //::user::interaction* create_menu_interaction() override;

   };


} // namespace platform




