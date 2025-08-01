//
// Created by camilo on 2024-10-24 01:14<3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_apex.h"


namespace platform
{


   ::file::path apex_application_layer::cloud_protocol()
   {
      return {};
   }


   //void on_initialize_application(::main* pmain) override{}
   //// void assert_ok() const override{}
   //// void dump(dump_context & dumpcontext) const override{}


   ::string apex_application_layer::apex_application_layer::__get_text(string str)
   {
      return {};
   }


   ::pointer<::fs::folder_sync> fs_folder_sync(const ::scoped_string& scopedstr)
   {
      return {};
   }


   //void apex_application_layer::process_command_line(command_line* pcommandline){}


   //virtual ::user::style* get_user_style() const{}
   //bool apex_application_layer::app_data_get(const ::atom & atom, stream & os) override{}
   //bool apex_application_layer::app_data_set(const ::atom & atom, stream & is) override{}

   //bool apex_application_layer::app_data_set(const ::atom & atom, object & obj) override{}
   //bool apex_application_layer::app_data_get(const ::atom & atom, object & obj) override{}

   //      virtual void     interactive_credentials(::account::credentials * pcredentials) override{}

   //virtual ::database::key calc_data_key() override{}


   //::string apex_application_layer::apex_application_layer::load_podata(string strLang, bool bOnlyHeader){}

   // ::string apex_application_layer::apex_application_layer::load_string(const ::atom& atom)
   // {
   //    return {};
   // }


   // bool apex_application_layer::load_string(string& str, const ::atom& atom)
   // {
   //    return false;
   // }


   void apex_application_layer::load_string_table()
   {
   }


   bool apex_application_layer::load_cached_string(string& str, const ::atom& atom, bool bLoadStringTable)
   {
      return false;
   }


   bool apex_application_layer::load_cached_string_by_id(string& str, const ::atom& atom, bool bLoadStringTable)
   {
      return false;
   }


   void apex_application_layer::load_string_table(const ::scoped_string & scopedstrApp, const ::scoped_string & scopedstrId)
   {
   }


   // bool apex_application_layer::is_application() const override{}
   //
   //
   // bool apex_application_layer::is_system() const override{}
   //
   //
   // bool apex_application_layer::is_session() const override{}


   bool apex_application_layer::is_service()
   {
      return false;
   }


   bool apex_application_layer::is_user_service()
   {
      return false;
   }


   ::pointer<::service> apex_application_layer::create_service()
   {
      return {};
   }


   void apex_application_layer::on_service_request(::request* prequest)
   {
   }


   //virtual ::simpledb::server * simpledb(){}
   ::database::server* apex_application_layer::dataserver()
   {
      return nullptr;
   }


   //void apex_application_layer::verb(){}


   // bool apex_application_layer::Ex2OnAppInstall(){}
   //
   //
   // bool apex_application_layer::Ex2OnAppUninstall(){}
   //

   //void apex_application_layer::init_application(){}

   // void init1() override{}
   //
   //
   // void init2() override{}
   //
   //
   // void init3() override{}
   //
   //
   // void init() override{}
   //
   //
   // void init_instance() override{}


   void apex_application_layer::defer_interprocess_communication()
   {
   }


   // void apex_application_layer::run() override{}
   //
   //
   // //virtual void     main() override{}
   // void apex_application_layer::on_run(){}


   // void destroy() override{}
   //
   //
   // //bool apex_application_layer::initial_check_directrix() override{}
   // void os_native_bergedge_start() override{}
   //

   //bool apex_application_layer::on_application_menu_action(const ::string apex_application_layer::& pszCommand){}


   // void term() override{}
   //
   //
   // void term_application() override{}
   //

   void apex_application_layer::show_about_box(::user::activation_token * puseractivationtoken)
   {
   }


   ::pointer<::innate_ui::icon> apex_application_layer::innate_ui_icon(const ::int_size& size)
   {
      return {};
   }


   void apex_application_layer::init_fs_set(::fs::set* pfsset)
   {
   }


   //bool apex_application_layer::InitApplication(){}


   // void do_install() override{}
   //
   //
   // void do_uninstall() override{}
   //
   //
   // void on_install() override{}
   //
   //
   // void on_uninstall() override{}


   void apex_application_layer::enable_service()
   {
   }


   void apex_application_layer::disable_service()
   {
   }


   void apex_application_layer::update_appmatter(::pointer<::sockets::http_session>& psession,
                                                 const ::file::path & pathRoot,
                                                 const ::scoped_string & scopedstrRelative)
   {
   }


   void apex_application_layer::update_appmatter(::pointer<::sockets::http_session>& psession,
                                                 const ::file::path & pathRoot,
                                                 const ::scoped_string & scopedstrRelative, const ::scoped_string & scopedstrLocale,
                                                 const ::scoped_string & scopedstrStyle)
   {
   }


   //void apex_application_layer::SetCurrentHandles() override{}

   //void apex_application_layer::france_exit(){}


   //void apex_application_layer::process_exception(const ::exception& e) override{}


   //virtual ::pointer<::apex::application>assert_running(const ::string apex_application_layer::& pszAppId) override{}

   //bool apex_application_layer::is_taskrunning()
   //{
   //   return false;
   //}


   //bool pump_runnable(){}

   void apex_application_layer::add_activation_message(const ::scoped_string & scopedstrMessage)
   {
   }


   bool apex_application_layer::has_activation_message() const
   {
      return false;
   }


   bool apex_application_layer::defer_process_activation_message()
   {
      return false;
   }


   //void apex_application_layer::on_request(::request * prequest) override{}


   bool apex_application_layer::assert_user_logged_in()
   {
      return false;
   }


   ::string apex_application_layer::apex_application_layer::matter_as_string(
      const ::scoped_string & scopedstrMatter, const ::scoped_string & scopedstrMatter2)
   {
      return {};
   }


   //bool apex_application_layer::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument){}
   //bool apex_application_layer::do_prompt_file_name(::payload& payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument){}
   //user bool apex_application_layer::do_prompt_file_name(::payload& payloadFile, string nIDSTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument){}


   //void apex_application_layer::process_message_filter(int code, ::message::message * pmessage) override{}


   void apex_application_layer::DoWaitCursor(int nCode)
   {
   } // 0 => restore, 1=> begin, -1=> end

   void apex_application_layer::_001TryCloseApplication()
   {
   }


   void apex_application_layer::_001CloseApplication()
   {
   }


   bool apex_application_layer::try_close_application()
   {
      return false;
   }


   bool apex_application_layer::can_close_application()
   {
      return false;
   }


   void apex_application_layer::close_application()
   {
   }


   ::string apex_application_layer::apex_application_layer::get_license_id()

   {
      return {};
   }


   //void process_init() override{}


   ::string apex_application_layer::apex_application_layer::get_mutex_name_gen()
   {
      return {};
   }


   //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow){}


   void apex_application_layer::hotplugin_host_starter_start_sync(const ::scoped_string & scopedstrCommandLine,
                                                                  ::apex::application* papp,
                                                                  hotplugin::host* phost,
                                                                  hotplugin::plugin* pplugin)
   {
   }


   void apex_application_layer::hotplugin_host_host_starter_start_sync(const ::scoped_string & scopedstrCommandLine,
                                                                       ::apex::application* papp,
                                                                       hotplugin::host* phost,
                                                                       hotplugin::plugin* pplugin)
   {
   }


   //bool apex_application_layer::is_local_data() override{}

   class ::application_menu* apex_application_layer::application_menu()
   {
      return nullptr;
   }


   ::file::path apex_application_layer::appconfig_folder()
   {
      return {};
   }


   //// void assert_ok() const override{}
   //// void dump(dump_context & dumpcontext) const override{}


   //bool apex_application_layer::app_data_set(const ::atom & atom, stream & os){}
   //bool apex_application_layer::app_data_get(const ::atom & atom, stream & is){}

   bool apex_application_layer::app_data_set(const ::atom& atom, ::object& obj)
   {
      return false;
   }


   bool apex_application_layer::app_data_get(const ::atom& atom, ::object& obj)
   {
      return false;
   }


   //void install_message_routing(::channel* pchannel) override{}


   ::string apex_application_layer::apex_application_layer::dialog_box(const ::scoped_string & scopedstrMatter,
                                                                       ::property_set& propertyset)
   {
      return {};
   }


   void apex_application_layer::application_menu_update()
   {
   }


   //::string apex_application_layer::apex_application_layer::calc_data_key(){}


   //void apex_application_layer::notify_changed(const ::atom & atom, const ::action_context & action_context){}


   ::file::path apex_application_layer::local_application_path()
   {
      return {};
   }


   ::file::path apex_application_layer::local_application_home_path()
   {
      return {};
   }


   //void apex_application_layer::destroy() override{}


   //void apex_application_layer::release_parents() override{}
   //::property_object* parent_property_set_holder() const override{}


   //bool apex_application_layer::is_set_finish() const override{}


   void apex_application_layer::on_change_theme()
   {
   }


   ::string apex_application_layer::apex_application_layer::get_theme()
   {
      return {};
   }


   //bool apex_application_layer::start_application(::request * prequest){}


   //void apex_application_layer::release_children() override{}
   //void apex_application_layer::merge_command_line(::create * pcommand){}

   //   void apex_application_layer::merge(::handler * phandler){}

   //void apex_application_layer::record(::create * pcommand){}

   //void apex_application_layer::on_event(unsigned long long u, ::particle * pparticle) override{}
   //virtual ::pointer<::thread_toolset>create_thread_toolset(::enum_task_tool etool){}


   //// ca2verses
   //// os_* functions generally
   //// reserves a lot of surprises from each
   //// operating system specific behavior
   //void apex_application_layer::auto pmessagebox = __initialize_new ::message_box(::user::interaction_base * puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}

   //pmessagebox->sync(){}


   //void apex_application_layer::ui_message_box(::user::interaction_base * puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}
   //void apex_application_layer::ui_message_box_timeout(::user::interaction_base * puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}


   //using ::platform::context::message_box{}
   //void apex_application_layer::message_box(::user::interaction_base * puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}
   //void apex_application_layer::message_box_timeout(::user::interaction_base * puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}


   void apex_application_layer::on_file_new()
   {
   }


   ::string apex_application_layer::apex_application_layer::title()
   {
      return {};
   }


   string_array apex_application_layer::get_categories()
   {
      return {};
   }


   void apex_application_layer::defer_create_keyboard()
   {
   }


   //bool apex_application_layer::set_keyboard_layout(const ::string apex_application_layer::& pszPath, const ::action_context & action_context){}


   bool apex_application_layer::enable_application_events(::particle* pparticle, bool bEnable)
   {
      return false;
   }


   bool apex_application_layer::is_equal_file_path(const ::file::path& path1, const ::file::path& path2)
   {
      return false;
   }


   //bool apex_application_layer::process_exception(const ::exception & e) override{}


   void set_has_installer(bool bSet)
   {
   }


   //::file::path apex_application_layer::defer_process_path(::file::path path){}
   //::file::path apex_application_layer::full_process_path(::file::path path){}

   //void apex_application_layer::DoWaitCursor(int nCode){} // 0 => restore, 1=> begin, -1=> end
   //void apex_application_layer::show_wait_cursor(bool bShow){}


   //void apex_application_layer::process_message_filter(int code,::message::message * pmessage) override{}

   //void apex_application_layer::on_thread_on_idle(::thread * pthread, int lCount) override{}


   void apex_application_layer::app_set(string strPath, string strValue)
   {
   }


   ::string apex_application_layer::apex_application_layer::app_get(string strPath, string strDefault)
   {
      return {};
   }


   //bool apex_application_layer::Ex2OnAppInstall(){}
   //bool apex_application_layer::Ex2OnAppUninstall(){}

   //bool apex_application_layer::on_application_menu_action(const ::string apex_application_layer::& pszCommand){}
   //void apex_application_layer::_001CloseApplication(){}

   //::string apex_application_layer::apex_application_layer::get_license_id(){}

   ::string apex_application_layer::apex_application_layer::get_version()
   {
      return {};
   }


   //virtual ::pointer < ::interprocess::handler > create_interprocess_handler(){}

   //void apex_application_layer::process_init(){}
   //void process_term() override{}


   //void apex_application_layer::impl_process_init(){}
   //void apex_application_layer::impl_init1(){}
   //void apex_application_layer::impl_init2(){}
   //void apex_application_layer::impl_init3(){}

   //void apex_application_layer::impl_process_term(){}
   //void apex_application_layer::impl_term1(){}
   //void apex_application_layer::impl_term2(){}
   //void apex_application_layer::impl_term3(){}

   //void apex_application_layer::init1(){}
   //void apex_application_layer::init2(){}
   //void apex_application_layer::init3(){}

   // void term1() override{}
   //
   //
   // void term2() override{}
   //
   //
   // void term3() override{}
   //
   //
   // void apex_application_layer::init_task() override{}

   //
   // //void apex_application_layer::init_application(){}
   // //void apex_application_layer::term_application(){}
   // void apex_application_layer::term_task() override{}
   //
   //
   // //void apex_application_layer::init_instance() override{}
   // void term_instance() override{}
   //

   //void apex_application_layer::init(){}
   //void apex_application_layer::term(){}

   void apex_application_layer::notify_process_init()
   {
   }


   void apex_application_layer::notify_init1()
   {
   }


   void apex_application_layer::notify_init2()
   {
   }


   void apex_application_layer::notify_init3()
   {
   }


   void apex_application_layer::notify_term3()
   {
   }


   void apex_application_layer::notify_term2()
   {
   }


   void apex_application_layer::notify_term1()
   {
   }


   void apex_application_layer::notify_process_term()
   {
   }


   // bool apex_application_layer::is_installing(){}
   // bool apex_application_layer::is_unstalling(){}

   //::string apex_application_layer::apex_application_layer::get_version(){}
   //virtual void     run() override{}
   //virtual void     main() override{}
   //virtual void     on_run(){}

   //void on_before_launching() override{}


   //void apex_application_layer::os_native_bergedge_start(){}

   // void apex_application_layer::pre_run(){}
   //void apex_application_layer::application_pre_run(){}

   //void apex_application_layer::on_pos_run_thread() override{}
   //void apex_application_layer::pos_run() override{}
   //void apex_application_layer::application_pos_run() override{}


   //bool apex_application_layer::InitApplication(){}
   //void apex_application_layer::TermApplication(){}

   //bool apex_application_layer::on_install(){}
   //bool apex_application_layer::on_uninstall(){}

   bool apex_application_layer::system_add_app_install(const ::scoped_string & scopedstrId, const ::scoped_string & scopedstrBuild)
   {
      return false;
   }


   //void apex_application_layer::TermThread(HINSTANCE hInstTerm){}

   //void apex_application_layer::SetCurrentHandles(){}

   //void apex_application_layer::set_env_var(const string & payload,const string & value){}
   //virtual itask get_thread_id(){}


   bool apex_application_layer::_001OnDDECommand(const ::string& pcsz)
   {
      return false;
   }


   void apex_application_layer::_001InitializeShellOpen()
   {
   }


   void apex_application_layer::_001OnFileNew(::message::message* pmessage)
   {
   }


   void apex_application_layer::get_temp_file_name_template(string& str, const ::scoped_string & scopedstrName,
                                                            const ::scoped_string & scopedstrExtension,
                                                            const ::scoped_string & scopedstrTemplate)
   {
   }


   void apex_application_layer::get_temp_file_name(string& str, const ::scoped_string & scopedstrName, const ::scoped_string & scopedstrExtension)
   {
   }


   ::service_handler* apex_application_layer::service_handler()
   {
      return nullptr;
   }


   //void apex_application_layer::on_service_request(::request * prequest){}

   //bool apex_application_layer::is_running(){}

   //::string apex_application_layer::apex_application_layer::get_mutex_name_gen(){}


   void apex_application_layer::___property_set_test_001()
   {
   }


   /// return true if this instance might continue execution
   /// bHandled true if some action was done in response to this ___new additional instance creation
   void apex_application_layer::on_exclusive_instance_conflict(::request* prequest, bool& bHandled,
                                                               enum_exclusive_instance eexclusive, string strId)
   {
   }


   /// return true if this instance might continue execution
   /// bHandled true if some action was done in response to this ___new additional instance creation
   void apex_application_layer::on_exclusive_instance_local_conflict(::request* prequest, bool& bHandled)
   {
   }


   /// return true if this instance might continue execution
   /// bHandled true if some action was done in response to this ___new additional instance creation
   void apex_application_layer::on_exclusive_instance_local_conflict_id(::request* prequest, bool& bHandled,
                                                                        string strId)
   {
   }


   void apex_application_layer::on_exclusive_instance_global_conflict(::request* prequest, bool& bHandled)
   {
   }


   /// return true if the external additional instance might continue execution
   /// bHandled true if some action was done in response to the external aaa_memory_new additional instance creation
   void apex_application_layer::on_additional_local_instance(bool& bHandled, string strModule, int iPid,
                                                             string strCommandLine)
   {
   }


   void apex_application_layer::on_new_instance(string strModule, const ::atom& idPid)
   {
   }


   ::string apex_application_layer::apex_application_layer::get_local_mutex_id()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_global_mutex_id()
   {
      return {};
   }


   //virtual ::pointer< ::mutex > get_local_mutex(){}
   //virtual ::pointer< ::mutex > get_global_mutex(){}

   ::string apex_application_layer::apex_application_layer::get_local_mutex_name()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_local_id_mutex_name()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_global_mutex_name()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_global_id_mutex_name()
   {
      return {};
   }


   bool apex_application_layer::check_exclusive(::request* prequest, bool& bHandled)
   {
      return false;
   }


   bool apex_application_layer::erase_exclusive(const ::scoped_string & scopedstrId)
   {
      return false;
   }


   bool apex_application_layer::exclusive_fails(const ::scoped_string & scopedstr, security_attributes* psecurityattributes)
   {
      return false;
   }


   bool apex_application_layer::exclusive_erase(const ::scoped_string & scopedstr)
   {
      return false;
   }


   void apex_application_layer::release_exclusive()
   {
   }


   // bool on_set_scalar(enum_scalar escalar, ::number number, int iFlags) override{}
   //
   //
   // ::number get_scalar_minimum(enum_scalar escalar) override{}
   //
   //
   // ::number get_scalar(enum_scalar escalar) override{}
   //
   //
   // ::number get_scalar_maximum(enum_scalar escalar) override{}


   //bool safe_is_running(){}


   //void apex_application_layer::on_request(::request * prequest) override{}

   // name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
   // get/set serializables to user directory
   //template < typename TYPE >
   //bool gudo_get(const ::string apex_application_layer::& strKey, TYPE & t){}

   //template < typename TYPE >
   //bool gudo_set(const ::string apex_application_layer::& strKey, const TYPE & t){}


   //bool apex_application_layer::assert_user_logged_in(){}

   //void request(::request* prequest) override{}


   //void apex_application_layer::call_request(::request * prequest) override{}


   //void apex_application_layer::process_message(::user::message * base) override{}

   //void apex_application_layer::message_handler(::message::message* pmessage) override{}


   ::string apex_application_layer::apex_application_layer::http_get_locale_schema(
      const ::scoped_string & scopedstrUrl, const ::scoped_string & scopedstrLocale,
      const ::scoped_string & scopedstrSchema)
   {
      return {};
   }


   //void apex_application_layer::on_update_matter_locator() override{}

   bool apex_application_layer::platform_open_by_file_extension(::collection::index iEdge, const ::scoped_string & scopedstrPathName,
                                                                ::request* prequest)
   {
      return false;
   }


   bool apex_application_layer::platform_open_by_file_extension(::collection::index iEdge, ::request* prequest)
   {
      return false;
   }


   bool apex_application_layer::on_start_application()
   {
      return false;
   }


   //#if !defined(LINUX)
   //
   //      bool apex_application_layer::os_on_start_application(){}
   //
   //#endif

   // DECLARE_MESSAGE_HANDLER(on_message_app_exit){}
   //
   //
   // DECLARE_MESSAGE_HANDLER(on_message_close){}
   //
   //
   // DECLARE_MESSAGE_HANDLER(on_command_display_about){}
   //

   //bool apex_application_layer::_001OnAgreeExit(){}


   //void apex_application_layer::request_exit_application(){}
   //void apex_application_layer::can_exit_application(){}
   //void exit_application() override{}


   //void apex_application_layer::_001FranceExit(){}


   //::string apex_application_layer::apex_application_layer::lstr(const ::atom & atom, string strDefault) override{}


   //bool apex_application_layer::do_install(){}
   //bool apex_application_layer::do_uninstall(){}


   //void request(::create * pcommand) override{}
   //void on_create(::request * prequest) override{}

   //      void apex_application_layer::dispatch_user_message(::user::message * pusermessage){}

   //void apex_application_layer::throw_not_installed(){}

   //void apex_application_layer::play_audio(::payload payloadFile, bool bSynch = false){}

   void apex_application_layer::post_critical_error_message(const ::scoped_string & scopedstrMessage, bool bShowLog)
   {
   }


   void apex_application_layer::show_critical_error_log()
   {
   }


   ::string apex_application_layer::apex_application_layer::get_app_user_friendly_task_bar_name()
   {
      return {};
   }


   //void signal(::signal * psignal) override{}
   //void handle(::topic * ptopic, ::handler_context * phandlercontext) override{}

   //bool apex_application_layer::compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed){}

   //bool apex_application_layer::compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6){}

   //void apex_application_layer::interactive_credentials(::account::credentials * pcredentials) override{}

   ::file::path apex_application_layer::get_executable_path()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_executable_extension()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_executable_title()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_executable_appid()
   {
      return {};
   }


   bool apex_application_layer::on_open_document_file(::payload payloadFile)
   {
      return false;
   }


   ::string apex_application_layer::apex_application_layer::get_app_id(string wstr)
   {
      return {};
   }


   void apex_application_layer::install_trace(const ::scoped_string & scopedstr)
   {
   }


   void apex_application_layer::install_trace(double dRate)
   {
   }


   void apex_application_layer::register_application_as_spa_file_type_handler()
   {
   }


   //bool apex_application_layer::low_is_app_app_admin_running(string strPlatform, string strConfiguration){}
   //void apex_application_layer::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration){}
   // void apex_application_layer::start_program_files_app_app_admin(string strPlatform, string strConfiguration){}


   bool apex_application_layer::keyboard_focus_is_focusable(const ::user::interaction_base* pue)
   {
      return false;
   }


   bool apex_application_layer::keyboard_focus_OnSetFocus(::user::interaction_base* pue)
   {
      return false;
   }


   //virtual ::user::interaction * main_window(){}

   //         virtual ::pointer<::user::message>get_message_base(MESSAGE * pmsg) override{}


   //bool apex_application_layer::get_frame(::pointer<::user::interaction>& pinteraction){}
   //void apex_application_layer::add_frame(::user::interaction * puserinteraction){}
   //void apex_application_layer::erase_frame(::user::interaction * puserinteraction){}


   void apex_application_layer::send_message_to_windows(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {
      // return false;
   } // with tbs in <3


   void apex_application_layer::route_message_to_windows(::message::message* pmessage)
   {
      //return false;
   } // with tbs in <3


   void apex_application_layer::send_language_change_message()
   {
   }


   // apex commented
   //virtual LPWAVEOUT waveout_open(int iChannel, LPAUDIOFORMAT pformat, LPWAVEOUT_CALLBACK pcallback){}


   ::string apex_application_layer::apex_application_layer::preferred_experience()
   {
      return {};
   }


   // user virtual ::user::document * place_hold(::user::interaction * pinteraction){}


   void apex_application_layer::post_message(::enum_message emessage, ::wparam wparam, ::lparam lparam)
   {
   }


   //virtual ::image::icon * set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon){}

   //virtual ::image::icon * get_icon(object * pparticle, bool bBigIcon) const{}

   //void apex_application_layer::handle(::topic * ptopic, ::handler_context * phandlercontext){}


   //      virtual ::account::user * get_user(::file::path pathUrl, bool bFetch = false, bool bInteractive){}
   //
   ////      virtual ::account::user * interactive_get_user(::file::path pathUrl){}
   //
   //      virtual ::account::user * noninteractive_get_user(::file::path pathUrl){}

   //void apex_application_layer::on_initial_frame_position(::user::frame_interaction * pframe){}

   //void apex_application_layer::on_graphics_ready(){}

   //virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype){}
   // apex commented
   //virtual ::type_atom control_type_from_id(const ::atom & atom, ::user::enum_control_type & econtroltype){}


   //virtual ::atom translate_property_id(const ::atom & atom) override{}
   //virtual property fetch_property(const ::atom & atom) override{}

   //void apex_application_layer::get_time(micro_time * pmicrotime){}


   void apex_application_layer::close(::enum_exit eexit)
   {
   }


   //user virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom){}


   void apex_application_layer::HideApplication()
   {
   }


   //void apex_application_layer::initialize(::particle * pparticle) override{}

   //void apex_application_layer::process_init() override{}

   //void apex_application_layer::init1() override{} // first initialization
   //void apex_application_layer::init2() override{} // second initialization
   //void apex_application_layer::init3() override{} // third initialization and so on...

   //void apex_application_layer::init() override{} // last initialization

   //void apex_application_layer::bergedge_start(){}
   //void apex_application_layer::os_native_bergedge_start() override{}

   //void apex_application_layer::term_application() override{}

   //void apex_application_layer::term() override{}

   //virtual void     main() override{}

   //virtual ::application * get_app() const override{}


   //virtual unsigned int guess_code_page(const ::scoped_string & scopedstr){}

   //virtual int _sync_message_box(::user::interaction_base* puiOwner, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, unsigned int fuStyle) override{}


   //void apex_application_layer::pre_translate_message(::message::message* pmessage) override{}


   //void apex_application_layer::install_message_routing(::channel* pchannel) override{}


   //void apex_application_layer::EnableShellOpen(){}


   //void apex_application_layer::_001CloseApplication() override{}


   //user void apex_application_layer::on_create_split_impact(::user::split_impact* pimpact){}


   //virtual ::type_atom control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype) override{}


   // bool apex_application_layer::base_support(){}

   //::string apex_application_layer::apex_application_layer::sync_message_box(const ::scoped_string & scopedstrMatter,::property_set & propertyset) override{}


   //virtual ::pointer<::user::interaction>uie_from_point(const ::int_point& point){}

   //bool apex_application_layer::on_application_menu_action(const ::string apex_application_layer::& pszCommand) override{}

   //bool apex_application_layer::on_install() override{}
   //bool apex_application_layer::on_uninstall() override{}
   bool apex_application_layer::on_run_install()
   {
      return false;
   }


   bool apex_application_layer::on_run_uninstall()
   {
      return false;
   }


   // DECLARE_MESSAGE_HANDLER(on_application_signal){}
   //
   //
   // DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme){}


   // open named file, trying to match a regsitered
   // document template to it.
   //void apex_application_layer::on_request(::create* pcreate) override{}

   //for implementation
   bool apex_application_layer::on_idle(int lCount)
   {
      return false;
   } // return tr(ue if more idle processing
   //void apex_application_layer::process_window_procedure_exceptionconst ::exception& e, ::message::message* pmessage) override{}


   //      void EnableModelessEx(bool bEnable){}
   ////#ifdef WINDOWS
   ////      HENHMETAFILE LoadEnhMetaFile(unsigned int uResource){}
   ////#endif
   //      bool GetResourceData(unsigned int nID, const ::string apex_application_layer::& lcszType, memory& storage){}

   //#ifdef WINDOWS
   //      bool apex_application_layer::OnMessageWindowMessage(MESSAGE * pmsg){}
   //
   //#elif defined(LINUX)
   //      bool apex_application_layer::OnX11WindowMessage(void* pev){}
   //#endif

   //bool CreateFileFromRawResource(unsigned int nID, const ::string apex_application_layer::& lcszType, const ::string apex_application_layer::& pcszFilePath){}

   //virtual LRESULT GetPaintMsgProc(int nCode, WPARAM wParam, LPARAM lParam){}


   //void OnUpdateRecentFileMenu(::message::command* pcommand){}

   //void apex_application_layer::send_app_language_changed(){}
   //void route_command(::message::command* pcommand, bool bRouteToKeyDescendant = false) override{}


   //virtual pointer< ::extended::future < ::conversation > > message_box(::user::interaction * puserinteraction, const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const ::e_message_box & emessagebox = e_message_box_ok) override{}
   //virtual ::enum_dialog_result message_box_timeout(const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, const class time & timeTimeout = ::time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future()) override{}


   //void EnableHtmlHelp(){}


   //virtual int sync_message_box_timeout(::user::interaction_base * puiOwner,::payload payload, const ::string apex_application_layer::& pszTitle, class ::time timeTimeout,unsigned int fuStyle = e_message_box_ok) override{}
   //virtual int sync_message_box(::user::interaction_base * puiOwner,const ::string apex_application_layer::& pszMessage, const ::string apex_application_layer::& pszTitle, unsigned int fuStyle = e_message_box_ok) override{}


   //bool on_exclusive_instance_conflict(bool & bHandled, enum_exclusive_instance eexclusive, string strId) override{}

   //bool apex_application_layer::process_exception(const ::exception & e) override{}

   //bool apex_application_layer::on_uninstall() override{}

   //bool apex_application_layer::on_install() override{}


   //::user::document* place_hold(::user::interaction* pinteraction) override{}


   //bool apex_application_layer::on_install() override{}
   //bool apex_application_layer::on_application_menu_action(const ::string apex_application_layer::& pszCommand) override{}


   //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style_pointer & pstyle,::menu::item * pitem) override{}

   // set regsitry key name to be used by application's
   // profile member functions{} prevents writing to an INI spfile->
   //void SetRegistryKey(const ::string apex_application_layer::& pszRegistryKey){}

   //void SetRegistryKey(unsigned int nIDRegistryKey){}


   //void RegisterShellFileTypes(bool bCompat = false){}

   //// call after all doc templates are registered
   //void UnregisterShellFileTypes(){}

   //
   //#ifdef WINDOWS
   //      // Printer DC Setup routine, 'struct tagPD' is a PRINTDLG structure.
   //      void SelectPrinter(HANDLE hDevNames, HANDLE hDevMode, bool bFreeOld){}
   //#endif

   // create a DC for the system default printer.
   //::draw2d::graphics* CreatePrinterDC(){}


   //   bool GetPrinterDeviceDefaults(PRINTDLG* pPrintDlg){}

   // run this cast as an embedded object.
   //bool RunEmbedded(){}

   // run this cast as an OLE automation server.
   //bool RunAutomated(){}

   // Parse the command line for stock options and commands.
   //   void ParseCommandLine(CCommandLineInfo& rCmdInfo){}

   // React to a shell-issued command line directive.
   //   bool ProcessShellCommand(CCommandLineInfo& rCmdInfo){}

   // Overridables


   // exiting
   bool apex_application_layer::save_all_modified()
   {
      return false;
   } // save before exit
   //void apex_application_layer::HideApplication() override{}
   //void apex_application_layer::close(::apex::e_end eend) override{} // close documents before exiting

   // Advanced: to override message boxes and other hooks
   //virtual int DoMessageBox(const ::string apex_application_layer::& pszPrompt,unsigned int nType,unsigned int nIDPrompt){}


   // Advanced: process async DDE request
   //bool apex_application_layer::OnDDECommand(LPWSTR pszCommand){}

   void apex_application_layer::_001OnFileNew()
   {
   }


   void apex_application_layer::on_file_open()
   {
   }


   bool apex_application_layer::does_launch_window_on_startup()
   {
      return false;
   }


   bool apex_application_layer::activate_app()
   {
      return false;
   }


   void apex_application_layer::initialize_contextualized_theme()
   {
   }


   bool apex_application_layer::get_fs_size(string& strSize, const ::scoped_string & scopedstrPath, bool& bPending)
   {
      return false;
   }


   bool apex_application_layer::get_fs_size(long long& i64Size, const ::scoped_string & scopedstrPath, bool& bPending)
   {
      return false;
   }


   void apex_application_layer::set_title(const ::scoped_string & scopedstrTitle)
   {
   }


   void apex_application_layer
   ::update_app_interest()
   {
   }


   void apex_application_layer::ensure_app_interest()
   {
   }


   //      virtual ::pointer<::apex::application>create_platform(::apex::session* psession){}


   ::pointer<::progress::real> apex_application_layer::show_progress(::user::interaction* puiParent, const ::scoped_string & scopedstrTitle,
                                                     ::collection::count iProgressCount)
   {
      return {};
   }


   void apex_application_layer::userfs_init1()
   {
   }


   void apex_application_layer::userfs_process_init()
   {
   }


   //void data_on_after_change(::database::client* pclient, const ::scoped_string& scopedstr,
   //                        ::topic* ptopic) override{}


   void apex_application_layer::report_error(const ::exception& e, int iMessageFlags, const ::scoped_string & scopedstrTopic)
   {
   }


   void apex_application_layer::create_impact_system()
   {
   }


   void apex_application_layer::on_song_added(const ::scoped_string & scopedstr)
   {
   }


   //string get_visual_studio_build(){}


   ::string apex_application_layer::apex_application_layer::sound_path(const ::scoped_string & scopedstr)
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::get_default_playlist_path()
   {
      return {};
   }


   ::string apex_application_layer::apex_application_layer::as_string(const ::payload& payload)
   {
      return {};
   }

#if defined(LINUX) || defined(__BSD__)

    ::string apex_application_layer::apex_application_layer::get_wm_class() const
    {

        return {};

    }

#endif


   void apex_application_layer::on_create_app_shortcut()
   {
   }


   void apex_application_layer::create_app_shortcut()
   {
   }


   class ::networking::application* apex_application_layer::networking_application(
      ::networking::application_handler* papplicationhandlerCreateNetworkApplication)
   {
      return nullptr;
   }


   void apex_application_layer::create_networking_application(const ::scoped_string& scopedstrHostName,
                                                              ::networking::application_handler*
                                                                 papplicationhandlerCreateNetworkApplication)
   {
   }


   //::e_status on_html_response(::networking::application_socket* psocket, ::string& strHtml, const ::scoped_string & scopedstrUrl,
   //const ::property_set& setPost) override{}


   //bool _handle_uri(const ::scoped_string & scopedstrUri) override{}


   //bool on_interprocess_handle(const ::scoped_string & scopedstrUri) override{}

   ///bool on_application_menu_action(const ::atom& atom) override{}


}
