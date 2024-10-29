//
// Created by camilo on 2024-10-24 12:54 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "application_aura.h"


namespace platform
{


   //      // void assert_ok() const override{}
   //      // void dump(dump_context & dumpcontext) const override{}


   void aura_application_layer::enumerate_composite(matter_array& a)
   {
   }


   ::aura::game* aura_application_layer::game()
   {
      return nullptr;
   }


   //void aura_application_layer::_001CloseApplication() override{}


   //virtual ::user::style* get_user_style() const{}
   //bool aura_application_layer::app_data_get(const ::atom & atom, stream & os) override{}
   //bool aura_application_layer::app_data_set(const ::atom & atom, stream & is) override{}

   //bool aura_application_layer::app_data_set(const ::atom & atom, object & obj) override{}
   //bool aura_application_layer::app_data_get(const ::atom & atom, object & obj) override{}

   //      void aura_application_layer::    interactive_credentials(::account::credentials * pcredentials) override{}

   //virtual ::database::key calc_data_key() override{}


   //::string aura_application_layer::load_podata(string strLang, bool bOnlyHeader){}

   //::string aura_application_layer::load_string(const ::atom & atom) override{}
   //bool aura_application_layer::load_string(string & str, const ::atom & atom) override{}
   //void aura_application_layer::load_string_table() override{}
   //bool aura_application_layer::load_cached_string(string & str, const ::atom & atom, bool bLoadStringTable) override{}
   //bool aura_application_layer::load_cached_string_by_id(string & str, const ::atom & atom, bool bLoadStringTable) override{}
   //void aura_application_layer::load_string_table(const string & pszApp, const string & pszId) override{}


   //bool aura_application_layer::is_system() const override{}
   //bool aura_application_layer::is_session() const override{}
   //bool aura_application_layer::is_serviceable() const override{}
   ::string aura_application_layer::get_window_class_name(::user::enum_control_type econtroltype)
   {
      return {};
   }


   //virtual ::simpledb::server * simpledb(){}
   //virtual ::database::server * dataserver() override{}
   //inline ::image_context& image() { return *m_pimagecontext{} }


   //void aura_application_layer::verb() override{}


   //::aura::session* get_session(){}
   //::aura::system* system(){}


   // bool aura_application_layer::Ex2OnAppInstall() override{}
   // bool aura_application_layer::Ex2OnAppUninstall() override{}

   //void aura_application_layer::init_application() override{}
   //
   // void aura_application_layer::init1() override{}
   // void aura_application_layer::init2() override{}
   // void aura_application_layer::init3() override{}
   //
   //
   // void aura_application_layer::init() override{}
   //
   //
   // void aura_application_layer::init_instance() override{}
   //

   //void aura_application_layer::    run() override{}
   //void aura_application_layer::    main() override{}
   //void aura_application_layer::    on_run(){}

   //void aura_application_layer::application_pre_run(){}
   //bool aura_application_layer::initial_check_directrix() override{}
   //void aura_application_layer::os_native_bergedge_start(){}


   //
   //
   // void aura_application_layer::term() override{}
   //
   //
   // void aura_application_layer::term_application() override{}
   //
   //


   //bool aura_application_layer::InitApplication(){}

   //
   // void aura_application_layer::do_install() override{}
   // void aura_application_layer::do_uninstall() override{}
   //
   //
   // void aura_application_layer::on_install() override{}
   // void aura_application_layer::on_uninstall() override{}
   //

   //void aura_application_layer::update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative) override{}
   //void aura_application_layer::update_appmatter(::pointer<::sockets::http_session>& psession, const ::file::path & pszRoot, const string & pszRelative, const ::string & strLocale, const ::string & strStyle) override{}

   //void aura_application_layer::SetCurrentHandles() override{}


   //void aura_application_layer::process_exception(const ::exception & e) override{}


   //virtual ::pointer<::aura::application>assert_running(const ::string & pszAppId) override{}

   //bool aura_application_layer::is_running() override{}


   //void aura_application_layer::on_request(::request * prequest) override{}


   //bool aura_application_layer::assert_user_logged_in() override{}

   //::string aura_application_layer::matter_as_string(const ::string & pszMatter, const ::string & pszMatter2 = nullptr) override{}


   //bool aura_application_layer::do_prompt_file_name(::payload & payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument){}
   //bool aura_application_layer::do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument){}
   //user bool aura_application_layer::do_prompt_file_name(::payload& payloadFile, string nIDSTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument){}


   //void aura_application_layer::process_message_filter(i32 code, ::message::message * pmessage) override{}


   //void aura_application_layer::DoWaitCursor(i32 nCode) override{} // 0 => restore, 1=> begin, -1=> end

   // void aura_application_layer::_001TryCloseApplication() override{}


   //::string aura_application_layer::get_license_id() override{}


   //void aura_application_layer::process_init() override{}


   //#ifdef WINDOWS_DESKTOP
   //      void aura_application_layer::TermThread(HINSTANCE hInstTerm) override{}
   //#endif

   //void aura_application_layer::set_env_var(const string & payload, const string & value) override{}


   ::draw2d::printer* aura_application_layer::get_printer(const ::string& pszDeviceName)
   {
      return nullptr;
   }


   ::image::icon* aura_application_layer::set_icon(::object* pobject, ::image::icon* picon, bool bBigIcon)
   {
      return nullptr;
   }


    ::image::icon* aura_application_layer:: get_icon(::object* pobject, bool bBigIcon) const
   {
      return nullptr;
   }


   //void aura_application_layer::on_service_request(::request * prequest) override{}

   //::string aura_application_layer::get_mutex_name_gen() override{}

   //virtual ::user::interaction * user_interaction_from_oswindow(::windowing::window * pwindow){}


   //virtual i32 hotplugin_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr){}
   //virtual i32 hotplugin_host_host_starter_start_sync(const ::string & pszCommandLine, ::aura::application * papp, hotplugin::host * phost, hotplugin::plugin * pplugin = nullptr){}

   //void aura_application_layer::on_update_impact(::user::impact * pimpact, ::user::impact * pviewSender, lparam lHint, object * pHint){}

   //void handle(::topic * ptopic, ::context * pcontext) override{}
   //void aura_application_layer::on_notify_control_event(::user::control_event* pevent){}
   //void aura_application_layer::route(::topic * ptopic, ::context * pcontext){}


   //user bool aura_application_layer::on_open_document(::user::document * pdocument, ::payload payloadFile){}
   //user bool aura_application_layer::on_save_document(::user::document * pdocument, ::payload payloadFile){}


   //inline ::html::html * html() { return puser->m_phtml{} }

   //virtual ::html::html * create_html(){}

   //::string aura_application_layer::http_get(const ::string & strUrl, ::property_set & set) override{}

   //bool aura_application_layer::compress_ungz(const ::stream & os, const ::stream & is) override{}

   ///bool aura_application_layer::compress_ungz(memory_base & mem) override{}
   //bool aura_application_layer::compress_gz(const ::stream& os, const ::stream& is, int iLevel = 6) override{}

   //bool aura_application_layer::compress_gz(::file::file * pfileOut, ::file::file * pfileIn, int iLevel = 6) override{}


   //bool aura_application_layer::is_local_data() override{}


   //application(){}
   //~ application() override{}

   //void aura_application_layer::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema){}
   //::string aura_application_layer::get_locale_schema_dir(){}


   //void aura_application_layer::initialize(::particle * pparticle) override{}


   //::application_menu & applicationmenu(){}


   //virtual ::file::path appconfig_folder() override{}


   //// void assert_ok() const override{}
   //// void dump(dump_context & dumpcontext) const override{}


   //virtual ::file::path get_app_localconfig_folder() override{}
   //virtual ::handle::ini get_ini() override{}


   //bool aura_application_layer::app_data_set(const ::atom & atom, stream & os) override{}
   //bool aura_application_layer::app_data_get(const ::atom & atom, stream & is) override{}

   //bool aura_application_layer::app_data_set(const ::atom & atom, ::object & obj) override{}
   //bool aura_application_layer::app_data_get(const ::atom & atom, ::object & obj) override{}

   //void install_message_routing(::channel * pchannel) override{}

   //::string aura_application_layer::dialog_box(const ::string & pszMatter, property_set & propertyset) override{}

   //void aura_application_layer::application_menu_update() override{}


   //::string aura_application_layer::calc_data_key(){}


   //void aura_application_layer::notify_changed(const ::atom & atom, const ::action_context & action_context){}


   //virtual ::file::path local_application_path() override{}

   //virtual ::file::path local_application_home_path() override{}


   //void aura_application_layer::destroy() override{}


   //void aura_application_layer::release_parents() override{}
   //::property_object * parent_property_set_holder() const override{}


   //bool aura_application_layer::is_set_finish() const override{}


   //void aura_application_layer::on_change_theme() override{}
   //::string aura_application_layer::get_theme() override{}


   //virtual ::pointer<::acme::exclusive>get_exclusive(string str, LPSECURITY_ATTRIBUTES psa) override{}
   //bool aura_application_layer::exclusive_fails(string str, LPSECURITY_ATTRIBUTES psa) override{}


   //bool aura_application_layer::start_application(bool bSynch, ::request * prequest) override{}


   //void aura_application_layer::release_children() override{}
   //void aura_application_layer::merge_command_line(::create * pcommand){}

   //   void aura_application_layer::merge(::handler * phandler){}

   //void aura_application_layer::record(::create * pcommand){}

   //void aura_application_layer::on_event(::u64 u, ::particle * pparticle) override{}
   //virtual ::pointer<::thread_toolset>create_thread_toolset(::enum_task_tool etool){}


   //// ca2verses
   //// os_* functions generally
   //// reserves a lot of surprises from each
   //// operating system specific behavior
   //void aura_application_layer::auto pmessagebox = __initialize_new ::message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}

   //pmessagebox->sync(){}


   //void aura_application_layer::ui_message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}
   //void aura_application_layer::ui_message_box_timeout(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}


   //using ::aura::context_thread::message_box{}
   //void aura_application_layer::message_box(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}
   //void aura_application_layer::message_box_timeout(::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const class ::time& timeTimeOut = time::infinite(), const ::e_message_box & emessagebox = e_message_box_ok, ::callback callback = ::callback()){}


   //void aura_application_layer::on_file_new() override{}


   //::string aura_application_layer::get_title() override{}
   //virtual string_array get_categories() override{}

   //void aura_application_layer::defer_create_keyboard() override{}
   //bool aura_application_layer::set_keyboard_layout(const ::string & pszPath, const ::action_context & action_context){}


   //bool aura_application_layer::enable_application_events(::particle * pparticle, bool bEnable) override{}

   //bool aura_application_layer::is_equal_file_path(const ::file::path & path1, const ::file::path & path2) override{}


   //bool aura_application_layer::process_exception(const ::exception & e) override{}


   //bool aura_application_layer::is_system() const override{}
   //bool aura_application_layer::is_session() const override{}
   //bool aura_application_layer::is_serviceable() const{}
   //bool aura_application_layer::is_user_service() const override{}

   //void set_has_installer(bool bSet){}


   //virtual ::file::path defer_process_path(::file::path path){}
   //virtual ::file::path full_process_path(::file::path path){}

   //void aura_application_layer::DoWaitCursor(i32 nCode){} // 0 => restore, 1=> begin, -1=> end
   //void aura_application_layer::show_wait_cursor(bool bShow = true) override{}


   //void aura_application_layer::process_message_filter(i32 code,::message::message * pmessage) override{}

   //void aura_application_layer::on_thread_on_idle(::thread * pthread,::i32 lCount) override{}


   //bool aura_application_layer::app_set(string strPath, string strValue) override{}
   //::string aura_application_layer::app_get(string strPath, string strDefault = "") override{}


   //bool aura_application_layer::Ex2OnAppInstall(){}
   //bool aura_application_layer::Ex2OnAppUninstall(){}

   //bool on_application_menu_action(const ::atom & atom) override{}
   //void aura_application_layer::_001CloseApplication(){}

   //::string aura_application_layer::get_license_id(){}

   //::string aura_application_layer::get_version() override{}

   //      virtual ::pointer<::interprocess::communication>create_interprocess_communication() override{}

   //void aura_application_layer::process_init(){}
   //void aura_application_layer::process_term() override{}

   //void aura_application_layer::impl_process_init(){}
   //void aura_application_layer::impl_init1(){}
   //void aura_application_layer::impl_init2(){}
   //void aura_application_layer::impl_init3(){}

   //void aura_application_layer::impl_process_term(){}
   //void aura_application_layer::impl_term1(){}
   //void aura_application_layer::impl_term2(){}
   //void aura_application_layer::impl_term3(){}

   //void aura_application_layer::init1(){}
   //void aura_application_layer::init2(){}
   //void aura_application_layer::init3(){}

   // void aura_application_layer::term1() override{}
   // void aura_application_layer::term2() override{}
   // void aura_application_layer::term3() override{}
   //
   // //void aura_application_layer::init_thread() override{}
   // //void aura_application_layer::init_application(){}
   // //void aura_application_layer::term_application(){}
   // //void aura_application_layer::term_thread() override{}
   //
   // //void aura_application_layer::init_instance() override{}
   // void aura_application_layer::term_instance() override{}

   //void aura_application_layer::init(){}
   //void aura_application_layer::term(){}

   //void aura_application_layer::notify_process_init(){}
   //void aura_application_layer::notify_init1(){}
   //void aura_application_layer::notify_init2(){}
   //void aura_application_layer::notify_init3(){}

   //void aura_application_layer::notify_term3(){}
   //void aura_application_layer::notify_term2(){}
   //void aura_application_layer::notify_term1(){}
   //void aura_application_layer::notify_process_term(){}

   // bool aura_application_layer::is_installing(){}
   // bool aura_application_layer::is_unstalling(){}

   //::string aura_application_layer::get_version(){}
   //void aura_application_layer::    run() override{}
   //void aura_application_layer::    main() override{}
   //void aura_application_layer::    on_run(){}

   //void aura_application_layer::on_before_launching() override{}
   //void aura_application_layer::os_native_bergedge_start(){}

   //void aura_application_layer::pre_run() override{}
   //void aura_application_layer::application_pre_run(){}

   // void aura_application_layer::on_pos_run_thread() override{}
   // void aura_application_layer::pos_run() override{}
   // void aura_application_layer::application_pos_run() override{}

   //bool aura_application_layer::InitApplication(){}
   //void aura_application_layer::TermApplication() override{}

   //bool aura_application_layer::on_install(){}
   //bool aura_application_layer::on_uninstall(){}

   //bool aura_application_layer::system_add_app_install(const ::string & pszId, const ::string & pszBuild) override{}

   //void aura_application_layer::TermThread(HINSTANCE hInstTerm){}

   //void aura_application_layer::SetCurrentHandles(){}

   //void aura_application_layer::set_env_var(const string & payload,const string & value){}
   //virtual itask_t get_thread_id(){}


   //bool aura_application_layer::_001OnDDECommand(const ::string & pcsz) override{}

   // void aura_application_layer::_001InitializeShellOpen() override{}
   // void aura_application_layer::_001OnFileNew(::message::message * pmessage) override{}


   //::string aura_application_layer::multimedia_audio_get_default_implementation_name() override{}
   //::string aura_application_layer::multimedia_audio_mixer_get_default_implementation_name() override{}
   //::string aura_application_layer::veriwell_multimedia_music_midi_get_default_implementation_name() override{}

   //bool aura_application_layer::get_temp_file_name_template(string & str, const ::string & lpszName, const ::string & pszExtension, const ::string & pszTemplate) override{}

   //bool aura_application_layer::get_temp_file_name(string & str, const ::string & lpszName, const ::string & pszExtension) override{}

   //service_base * get_service(){}
   //virtual service_base * allocate_new_service() override{}
   //bool aura_application_layer::init_service() override{}

   //bool aura_application_layer::os_create_service() override{}
   //bool aura_application_layer::os_erase_service() override{}

   //bool aura_application_layer::os_start_service() override{}
   //bool aura_application_layer::os_stop_service() override{}

   //void aura_application_layer::on_service_request(::request * prequest){}

   //bool aura_application_layer::is_running(){}

   //::string aura_application_layer::get_mutex_name_gen(){}

   /// return true if this instance might continue execution
   /// bHandled true if some action was done in response to this ___new additional instance creation
   //void aura_application_layer::on_exclusive_instance_conflict(bool & bHandled, enum_exclusive_instance eexclusive, string strId) override{}

   /// return true if this instance might continue execution
   /// bHandled true if some action was done in response to this ___new additional instance creation
   //      bool aura_application_layer::on_exclusive_instance_local_conflict(bool & bHandled) override{}

   /// return true if this instance might continue execution
/// bHandled true if some action was done in response to this ___new additional instance creation
   //bool aura_application_layer::on_exclusive_instance_local_conflict_id(bool & bHandled, string strId) override{}

   /// return true if the external additional instance might continue execution
   /// bHandled true if some action was done in response to the external aaa_memory_new additional instance creation
   //void aura_application_layer::on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine) override{}

   //void aura_application_layer::on_new_instance(string strModule, const ::atom & idPid) override{}

   //::string aura_application_layer::get_local_mutex_id() override{}
   //::string aura_application_layer::get_global_mutex_id() override{}

   //virtual ::pointer< ::mutex > get_local_mutex(){}
   //virtual ::pointer< ::mutex > get_global_mutex(){}

   //::string aura_application_layer::get_local_mutex_name() override{}
   //::string aura_application_layer::get_local_id_mutex_name() override{}
   //::string aura_application_layer::get_global_mutex_name() override{}
   //::string aura_application_layer::get_global_id_mutex_name() override{}

   //bool aura_application_layer::check_exclusive(bool & bHandled) override{}
   //bool aura_application_layer::release_exclusive() override{}

   //void aura_application_layer::on_set_scalar(e_scalar escalar,i64 iValue,int iFlags) override{}
   //void aura_application_layer::get_scalar_minimum(e_scalar escalar,i64 & i) override{}
   //void aura_application_layer::get_scalar(e_scalar escalar,i64 & i) override{}
   //void aura_application_layer::get_scalar_maximum(e_scalar escalar,i64 & i) override{}


   //bool safe_is_running(){}


   //void aura_application_layer::on_request(::request * prequest) override{}

   //// name by Mummi (Japanese -> Guddo : from English : Good, ca2 interpretation : Goods).
   //// get/set serializables to user directory
   //template < typename TYPE >
   //bool gudo_get(const ::string & strKey, TYPE & t){}

   //template < typename TYPE >
   //bool gudo_set(const ::string & strKey, const TYPE & t){}


   //bool aura_application_layer::assert_user_logged_in(){}

   //void aura_application_layer::    do_request(::request * prequest) override{}
   //void aura_application_layer::call_request(::request * prequest) override{}


   //void aura_application_layer::process_message(::user::message * base) override{}

   //void aura_application_layer::message_handler(::user::message * pusermessage) override{}


   //::string aura_application_layer::http_get_locale_schema(const ::string & pszUrl, const ::string & pszLocale, const ::string & pszSchema) override{}

   //void aura_application_layer::on_update_matter_locator() override{}

   //void aura_application_layer::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override{}
   //void aura_application_layer::matter_locator_locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override{}

   //::string aura_application_layer::get_locale_schema_dir(const ::string & strLocale, const ::string & strSchema) override{}
   //::string aura_application_layer::get_locale_schema_dir(const ::string & strLocale) override{}
   //::string aura_application_layer::get_locale_schema_dir() override{}

   //void aura_application_layer::set_locale(const string & pcsz, const ::action_context & action_context) override{}

   //void aura_application_layer::set_schema(const string & pcsz, const ::action_context & action_context) override{}

   //void aura_application_layer::on_set_locale(const string & pcsz, const ::action_context & action_context) override{}

   //void aura_application_layer::on_set_schema(const string & pcsz, const ::action_context & action_context) override{}


   //void aura_application_layer::fill_locale_schema(::text::international::locale_schema & localeschema) override{}
   //void aura_application_layer::fill_locale_schema(::text::international::locale_schema & localeschema,const string & pszLocale,const string & pszSchema) override{}

   //bool aura_application_layer::platform_open_by_file_extension(::collection::index iEdge, const ::string & pszPathName, ::request * prequest = nullptr) override{}
   //bool aura_application_layer::platform_open_by_file_extension(::collection::index iEdge,::create * pcc) override{}


   //bool aura_application_layer::on_start_application() override{}

   //bool aura_application_layer::os_on_start_application() override{}

   //bool aura_application_layer::is_application() const override{}


   //DECLARE_MESSAGE_HANDLER(on_message_app_exit){}
   //bool aura_application_layer::_001OnAgreeExit() override{}
   //void aura_application_layer::france_exit() override{}
   //void aura_application_layer::_001FranceExit() override{}


   //::string aura_application_layer::lstr(const ::atom & atom, string strDefault = "") override{}


   //bool aura_application_layer::do_install(){}
   //bool aura_application_layer::do_uninstall(){}


   //void request(::create * pcommand) override{}
   //void on_create(::request * prequest) override{}

   //      void aura_application_layer::dispatch_user_message(::user::message * pusermessage){}

   //void aura_application_layer::throw_not_installed(){}

   //void aura_application_layer::play_audio(::payload payloadFile, bool bSynch){}

   //void aura_application_layer::post_critical_error_message(const ::string & pszMessage, bool bShowLog = true) override{}

   //void aura_application_layer::show_critical_error_log() override{}

   //::string aura_application_layer::get_app_user_friendly_task_bar_name() override{}

   //void handle(::topic * ptopic, ::context * pcontext) override{}

   //bool aura_application_layer::compress_ungz(::file::file * pfileUncompressed, ::file::file * pfileCompressed){}

   //bool aura_application_layer::compress_gz(::file::file * pfileCompressed, ::file::file * pfileUncompressed, int iLevel = 6){}

   //void aura_application_layer::interactive_credentials(::account::credentials * pcredentials) override{}

   //virtual ::file::path get_executable_path() override{}
   //::string aura_application_layer::get_executable_extension() override{}
   //::string aura_application_layer::get_executable_title() override{}
   //::string aura_application_layer::get_executable_appid() override{}


   //bool aura_application_layer::on_open_document_file(::payload payloadFile) override{}

   //::string aura_application_layer::get_app_id(string wstr) override{}


   //void aura_application_layer::install_trace(const ::string & str) override{}
   //void aura_application_layer::install_trace(double dRate) override{}
   //bool aura_application_layer::register_spa_file_type() override{}

   //bool aura_application_layer::low_is_app_app_admin_running(string strPlatform, string strConfiguration) override{}
   //void aura_application_layer::defer_start_program_files_app_app_admin(string strPlatform, string strConfiguration) override{}
   //void aura_application_layer::start_program_files_app_app_admin(string strPlatform, string strConfiguration) override{}


   // bool aura_application_layer::keyboard_focus_is_focusable(const ::user::interaction_base * pue) override{}
   // bool aura_application_layer::keyboard_focus_OnSetFocus(::user::interaction_base * pue) override{}

   ::user::interaction*  aura_application_layer::main_window()
   {
      return nullptr;
   }


   bool aura_application_layer::is_sandboxed()
   {
      return false;
   }


   ///virtual ::pointer<::user::message>get_user_message(MESSAGE * pmsg){}

   bool aura_application_layer::get_frame(::pointer<::user::interaction>& pinteraction)
   {
      return false;
   }


   void aura_application_layer::add_user_interaction(::user::interaction* puserinteraction)
   {
      
   }


   void aura_application_layer::erase_user_interaction(::user::interaction* puserinteraction)
   {
   }


   // bool aura_application_layer::send_message_to_windows(const ::atom & atom, wparam wparam, lparam lparam) override{} // with tbs in <3
   //
   // bool aura_application_layer::route_message_to_windows(::message::message * pmessage) override{} // with tbs in <3


   //void aura_application_layer::send_language_change_message() override{}


   //
   // ::string aura_application_layer::preferred_experience() override{}
   //
   //
   // // user virtual ::user::document * place_hold(::user::interaction * pinteraction){}
   //
   //
   // void aura_application_layer::post_message(const ::atom & atom, wparam wparam = 0, lparam lparam = 0) override{}
   //
   //
   //virtual ::image::icon * set_icon(object * pparticle, ::image::icon * picon, bool bBigIcon){}

   //virtual ::image::icon * get_icon(object * pparticle, bool bBigIcon) const{}

   //void aura_application_layer::handle(::topic * ptopic, ::context * pcontext){}


   //      virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch, bool bInteractive = true){}
   //
   ////      virtual ::account::user * interactive_get_user(::file::path pathUrl = nullptr){}
   //
   //      virtual ::account::user * noninteractive_get_user(::file::path pathUrl = nullptr){}

   void aura_application_layer::on_initial_frame_position(::user::frame_interaction* pframe)
   {
   }


   void aura_application_layer::on_graphics_ready()
   {
   }


   //virtual ::type_atom user_default_controltype_to_typeinfo(::user::enum_control_type econtroltype){}
   ::type_atom aura_application_layer::control_type_from_id(const ::atom& atom, ::user::enum_control_type& econtroltype)
   {
      return {};
   }


   //virtual ::atom translate_property_id(const ::atom & atom) override{}
   //virtual property fetch_property(const ::atom & atom) override{}

   //void aura_application_layer::get_time(struct timeval *point_i32) override{}
   //
   // void aura_application_layer::close(::enum_exit eexit) override{}


   //user virtual ::pointer<::user::document>defer_create_impact(string strImpact, ::user::interaction * puiParent, e_window_flag ewindowflag, const ::atom & atom = nullptr){}

   //
   // void aura_application_layer::HideApplication() override{}
   //

   //void aura_application_layer::initialize(::particle * pparticle) override{}

   //void aura_application_layer::process_init() override{}

   //void aura_application_layer::init1() override{} // first initialization
   //void aura_application_layer::init2() override{} // second initialization
   //void aura_application_layer::init3() override{} // third initialization and so on...

   //void aura_application_layer::init() override{} // last initialization

   //void aura_application_layer::bergedge_start(){}
   //void aura_application_layer::os_native_bergedge_start() override{}

   //void aura_application_layer::term_application() override{}

   //void aura_application_layer::term() override{}

   //void aura_application_layer::    main() override{}

   //virtual ::aura::application * get_app() const override{}

   //bool aura_application_layer::is_system() const override{}
   //bool aura_application_layer::is_session() const override{}

   //virtual u32 guess_code_page(const string& str) override{}

   //virtual i32 _sync_message_box(::user::interaction_base* puiOwner, const ::string & pszMessage, const ::string & pszTitle, ::u32 fuStyle) override{}

   //bool aura_application_layer::is_serviceable() const override{}
   //
   //
   // void aura_application_layer::pre_translate_message(::message::message* pmessage) override{}
   //

   //void aura_application_layer::EnableShellOpen() override{}


   //bool aura_application_layer::base_support() override{}

   //bool aura_application_layer::on_run_install() override{}
   //bool aura_application_layer::on_run_uninstall() override{}

   //DECLARE_MESSAGE_HANDLER(on_application_signal){}
   //DECLARE_MESSAGE_HANDLER(_001OnSwitchContextTheme){}


   //bool aura_application_layer::on_idle(::i32 lCount) override{} // return true if more idle processing
   //void aura_application_layer::process_window_procedure_exception(const ::exception & e, ::message::message* pmessage) override{}

   //      void EnableModelessEx(bool bEnable){}
   //      bool GetResourceData(::u32 nID, const ::string & lcszType, memory& storage){}

   //#ifdef WINDOWS
   //      bool aura_application_layer::OnMessageWindowMessage(MESSAGE * pmsg){}
   //
   //#elif defined(LINUX)
   //      bool aura_application_layer::OnX11WindowMessage(void* pev){}
   //#endif

   bool  aura_application_layer::CreateFileFromRawResource(::u32 nID, const ::string& lcszType, const ::string& pcszFilePath)
   {
      return false;
   }


   void aura_application_layer:: OnUpdateRecentFileMenu(::message::command* pcommand)
   {
   }


   // void aura_application_layer::route_command(::message::command * pcommand, bool bRouteToKeyDescendant) override{}
   //
   // //void aura_application_layer::EnableHtmlHelp(){}

   // set regsitry key name to be used by application's
   // profile member functions{} prevents writing to an INI spfile->
   void aura_application_layer::SetRegistryKey(const ::string& pszRegistryKey)
   {
   }


   void aura_application_layer::SetRegistryKey(::u32 nIDRegistryKey)
   {
   }


   void aura_application_layer::RegisterShellFileTypes(bool bCompat)
   {
   }


   // call after all doc templates are registered
   void  aura_application_layer::UnregisterShellFileTypes()
   {
   }


   // run this cast as an embedded object.
   // bool aura_application_layer::RunEmbedded(){}

   // run this cast as an OLE automation server.
   //bool aura_application_layer::RunAutomated(){}

   // exiting
   // bool save_all_modified() override{} // save before exit

   void aura_application_layer::_001OnFileNew()
   {
   }


   void aura_application_layer::on_file_open()
   {
   }


   // Finds number of opened document items owned by templates
   // registered with the doc manager.
   //virtual ::collection::count get_open_document_count(){}

   //static const char gen_FileSection[]{}
   //static const char gen_FileEntry[]{}
   //static const char gen_ThumbnailSection[]{}
   //static const char gen_ThumbnailEntry[]{}


   //
   //
   // bool aura_application_layer::does_launch_window_on_startup() override{}
   // bool aura_application_layer::activate_app() override{}
   //
   //


   ::user::interaction* aura_application_layer::get_request_parent_ui(::user::interaction* pinteraction, ::user::system* pusersystem)
   {
      return nullptr;
   }


   ::aura::theme*  aura_application_layer::theme()
   {
      return nullptr;
   }


   // void aura_application_layer::initialize_contextualized_theme() override{}
   //


    i32 aura_application_layer::track_popup_menu(::menu::track_popup* ptrackpopup)
   {
      return 0;
   }


   // bool aura_application_layer::get_fs_size(string& strSize, const ::string & pszPath, bool& bPending) override{}
   // bool aura_application_layer::get_fs_size(i64& i64Size, const ::string & pszPath, bool& bPending) override{}
   //
   // void aura_application_layer::set_title(const ::string & pszTitle) override{}


   bool aura_application_layer::_001CloseApplicationByUser(::pointer<::user::interaction> puserinteractionExcept)
   {
      return false;
   }


   void aura_application_layer:: update_app_interest()
   {
   }


   void  aura_application_layer::ensure_app_interest()
   {
   }


   // bool aura_application_layer::is_system() const override{}
   // bool aura_application_layer::is_session() const override{}
   //

   //      virtual ::pointer<::apex::application>create_platform(::apex::session* psession) override{}

   //void data_on_after_change(::database::client* pclient, const ::scoped_string & scopedstr, ::topic * ptopic) override{}


   i32  aura_application_layer::GetVisibleTopLevelFrameCountExcept(::pointer<::user::interaction> puserinteractionExcept)
   {
      return 0;
   }


    i32  aura_application_layer::GetVisibleFrameCount()
   {
      return 0;
   }


   void aura_application_layer::prepare_form(atom atom, ::form_document* pformdocument)
   {
   }


   // void report_error(const ::exception & exception, int iMessageFlags, const ::string & pszTopic) override{}
   //
   //
   // bool can_close_application() override{}


   bool aura_application_layer::on_close_frame_window(::user::frame_interaction* pframe)
   {
      return false;
   }


   //void create_impact_system() override{}

    ::user::interaction*  aura_application_layer::create_menu_interaction()
   {

      return nullptr;
   }


   // void on_song_added(const string& str) override{}
   //
   //
   // ::string aura_application_layer::get_visual_studio_build() override{}
   //
   //
   // string sound_path(const ::string & psz) override{}
   // string get_default_playlist_path() override{}


   //#if defined(FREEBSD) || defined(OPENBSD)
   //
   //      bool os_on_start_application() override{}
   //
   //#endif

   ::string aura_application_layer::draw2d_get_default_implementation_name()
   {
      return {};
   }


   //void on_additional_local_instance(bool & bHandled, string strModule, int iPid, string strCommandLine) override{}


   //virtual ::user::user * user(){}
   // ::axis::user * axisuser() override{}
   // ::base::user * baseuser() override{}
   // ::bred::user * breduser() override{}
   // ::core::user * coreuser() override{}

   // void pick_browse(const ::function < void(const ::file::path & path) > & callback) override{}
   //
   // void pick_media(const char * pszMediaType) override{}
   //
   // void on_prompt_write_file(::user::controller * pusercontroller) override{}

   //::pointer < ::innate_ui::icon > innate_ui_icon(const ::size_i32 & size) override{}


}


