//
// Created by camilo on 2024-10-24 02:17 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_acme.h"


namespace platform
{


   ::release_time_for_project acme_application_layer::release_time()
   {

      return {};

   }


   //void acme_application_layer::initialize_application(::platform::platform * pplatform){}

   void acme_application_layer::initialize_application()
   {


   }


   // #if REFERENCING_DEBUGGING
   //
   //       void on_after_construct(::reference_referer* preferer) override{}
   //
   // #endif

   void acme_application_layer::_001TryCloseApplication()
   {
   }


   void acme_application_layer::application_on_status(::e_status estatus, ::particle* pparticle, long long hi, void* p)
   {
   }


   void acme_application_layer::on_error_icloud_not_available(::particle* pparticle, long long hi, void* p)
   {
   }


   //void acme_application_layer::application_main(){}

   int acme_application_layer::application_main()
   {
      return 0;
   }


   //void on_set_platform() override{}


   //void on_initialize_particle() override{}


   //void initialize(::particle * pparticle) override{}


   //void acme_application_layer::start_application(::request* prequest)
void acme_application_layer::start_application()
   {
   }


   //void acme_application_layer::on_initialize_application(){}

   class ::application_menu* acme_application_layer::application_menu()
   {

      return nullptr;
   }


   //      using ::platform::context::factory{}

   //      virtual ::factory::factory_pointer& factory() const override{}

   //void acme_application_layer::implement_application(){}

   void acme_application_layer::initialize_application_flags()
   {
   }


   bool acme_application_layer::is_application() const
   {
      return false;
   }


   // bool is_system() const override{}
   // bool is_session() const override{}
   //
   // bool acme_application_layer::is_service() const{}
   // bool acme_application_layer::is_user_service() const{}
   //
   // bool acme_application_layer::can_exit_application() override{}

   ::file::path acme_application_layer::get_module_path()
   {
      return {};
   }


   ::file::path acme_application_layer::get_module_folder()
   {
      return {};
   }


   ::string acme_application_layer::app_name()
   {
      return {};
   }


   //::string acme_application_layer::app_name(){}

   ::string acme_application_layer::app_root()
   {
      return {};
   }


   ::string acme_application_layer::application_title()
   {
      return {};
   }


   ::string acme_application_layer::application_name()
   {
      return {};
   }


   //
   //#ifdef WINDOWS
   //
   //      void get_arguments_from_command_line(){}
   //
   //#else
   //
   //      void set_args(int argc, char * argv[], char * envpb[]){}
   //
   //#endif

   int acme_application_layer::__implement()
   {
      return 0;
   }


   int acme_application_layer::main_loop()
   {
      return 0;
   }


   ::enum_id acme_application_layer::key_command(::user::enum_key ekey, ::user::key_state* pkeystate)
   {
      return id_none;
   }


   void acme_application_layer::on_before_launching()
   {
   }


   //void acme_application_layer::os_native_bergedge_start()
   //{
   //}


   // void acme_application_layer::init1(){}
   // void acme_application_layer::init2(){}
   // void acme_application_layer::init3(){}
   //
   //
   // void acme_application_layer::init(){}
   // void acme_application_layer::term(){}
   //
   // void acme_application_layer::term3(){}
   // void acme_application_layer::term2(){}
   // void acme_application_layer::term1(){}
   //

   void acme_application_layer::do_install()
   {
   }


   void acme_application_layer::do_uninstall()
   {
   }


   void acme_application_layer::on_install()
   {
   }


   void acme_application_layer::on_uninstall()
   {
   }


   void acme_application_layer::init_instance()
   {
   }


   void acme_application_layer::term_instance()
   {
   }


   // void init_task() override{}
   // void term_task() override{}


   bool acme_application_layer::has_capability(enum_application_capability eapplicationcapability) const
   {
      return false;
   }


   void acme_application_layer::add_capability(enum_application_capability ecapability)
   {
   }


   //bool handle_call(::payload & payload, const ::scoped_string & scopedstrObject, const ::scoped_string & scopedstrMember, ::property_set & propertyset) override{}
   bool acme_application_layer::handle_application_call(::payload& payload, const ::scoped_string & scopedstrMember,
                                                        ::property_set& propertyset)
   {
      return false;
   }


   ::file::path acme_application_layer::get_app_localconfig_folder()
   {
      return {};
   }


   ::property_set acme_application_layer::get_ini(const ::scoped_string& scopedstrIniName)
   {
      return {};
   }


   ::string acme_application_layer::get_visual_studio_build()
   {
      return {};
   }


   ::string acme_application_layer::get_application_name()
   {
      return {};
   }


   void acme_application_layer::locale_schema_matter(string_array_base& stra, const string_array_base& straMatterLocator,
                                                     const ::scoped_string& scopedstrLocale,
                                                     const ::scoped_string& scopedstrSchema)
   {
   }


   void acme_application_layer::matter_locator_locale_schema_matter(string_array_base& stra,
                                                                    const string_array_base& straMatterLocator,
                                                                    const ::scoped_string& scopedstrLocale,
                                                                    const ::scoped_string& scopedstrSchema)
   {
   }


   ::string acme_application_layer::get_locale_schema_dir(const ::scoped_string& scopedstrLocale,
                                                          const ::scoped_string& scopedstrSchema)
   {
      return {};
   }


   ::string acme_application_layer::get_locale_schema_dir(const ::scoped_string& scopedstrLocale)
   {

      return {};
   }


   ::string acme_application_layer::get_locale_schema_dir()
   {

      return {};
   }


   void acme_application_layer::set_locale(const ::scoped_string& scopedstrLocale,
                                           const ::action_context& action_context)
   {
   }


   void acme_application_layer::set_schema(const ::scoped_string& scopedstrSchema,
                                           const ::action_context& action_context)
   {
   }


   void acme_application_layer::on_set_locale(const ::scoped_string& scopedstrLocale,
                                              const ::action_context& action_context)
   {
   }


   void acme_application_layer::on_set_schema(const ::scoped_string& scopedstrSchema,
                                              const ::action_context& action_context)
   {
   }


   void acme_application_layer::fill_locale_schema(::text::international::locale_schema& localeschema)
   {
   }


   void acme_application_layer::fill_locale_schema(::text::international::locale_schema& localeschema,
                                                   const ::scoped_string& scopedstrLocale,
                                                   const ::scoped_string& scopedstrSchema)
   {
   }


   void acme_application_layer::process_init()
   {
   }


   void acme_application_layer::process_term()
   {
   }


   //void acme_application_layer::pre_run()
   //{
   //}


   //void acme_application_layer::application_pre_run()
   //{
   //}


   //void acme_application_layer::pos_run()
   //{
   //}


   //void acme_application_layer::application_pos_run()
   //{
   //}


   void acme_application_layer::init_application()
   {
   }


   void acme_application_layer::term_application()
   {
   }


   ::string_array_base acme_application_layer::get_about_box_lines()
   {
      return {};
   }


   void acme_application_layer::show_about_box(::user::activation_token * puseractivationtoken)
   {


   }


   // bool acme_application_layer::on_command_final(const ::atom& atom, ::user::activation_token * puseractivationtoken)
   // {
   //
   //    return false;
   //
   // }


   void acme_application_layer::add_impact_system(const ::atom& atom,
                                                  const ::pointer<::user::impact_system>& pimpactsystem)
   {
   }


   ::pointer<::user::impact_system> acme_application_layer::impact_system(const ::atom& atom)
   {

      return {};
   }


   get_file_extension_mime_type* acme_application_layer::get_get_file_extension_mime_type()
   {
      return nullptr;
   }


   void acme_application_layer::pick_browse(const ::function<void(const ::file::path& path)>& callback)
   {
   }


   void acme_application_layer::pick_media(const ::scoped_string & scopedstrMediaType)
   {
   }


   void acme_application_layer::did_pick_document_at_url(const ::scoped_string & scopedstrUrl)
   {
   }


   void acme_application_layer::did_pick_document_at_urls(const ::string_array_base& stra)
   {
   }


   void acme_application_layer::on_prompt_write_file(::user::controller* pusercontroller)
   {
   }


   void acme_application_layer::file_manager_save_as(::user::controller* pusercontroller)
   {
   }


   bool acme_application_layer::fill_system_menu(::operating_system::a_system_menu* psystemmenu)
   {
      return false;
   }


}// namespace platform
