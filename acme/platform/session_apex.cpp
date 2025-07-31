//
// Created by camilo on 2024-10-24 03:14 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "session_apex.h"
#include "acme/constant/user_key.h"


namespace platform
{


   //void initialize(::particle* pparticle) override{}


   //void install_message_routing(::channel* pchannel) override{}


   //void apex_session_layer::on_initialize_window_object(){}
   //void apex_session_layer::_on_initialize_window_object(){}


   //inline ::userpresence::department & userpresence() { return *m_puserpresence{} }

   //bool apex_session_layer::is_session() const override{}

   //void main() override{}


   //void apex_session_layer::enum_display_monitors(){}

   ////void construct(::particle * pparticle, int iPhase) override{}

   //virtual ::collection::index get_main_monitor(::int_rectangle* prectangle){}

   //virtual ::collection::count get_monitor_count(){}
   //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle* prectangle){}

   //virtual ::collection::count get_desk_monitor_count(){}
   //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle* prectangle){}


   //virtual ::collection::index get_main_workspace(::int_rectangle* prectangle){}

   //virtual ::collection::count get_workspace_count(){}
   //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle* prectangle){}

   //virtual ::collection::count get_desk_workspace_count(){}
   //virtual bool  get_desk_workspace_rect(::collection::index iWorkspace, ::int_rectangle* prectangle){}

   //virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction){}

   // void apex_session_layer::process_init() override{}
   //
   //
   // void init1() override{}
   //
   //
   // void init2() override{}
   //
   //
   // void init_session() override{}
   //
   //
   // void init() override{}
   //
   //
   // void term() override{}
   //
   //
   // void term_session() override{}


   //DECLARE_MESSAGE_HANDLER(on_message_erase_application){}

   class ::fs::data* apex_session_layer::fs()

   {
      return nullptr;
   }


   //inline ::sockets::sockets & sockets() { return *m_psockets{} }


   //virtual int_size get_window_minimum_size(){}


   //virtual void  get_cursor_position(::int_point * ppoint){}

   //bool apex_session_layer::on_get_task_name(string& strThreadName) override{}


   //void request(::request * prequest) override{}


   //virtual string matter_as_string(const ::scoped_string & scopedstrMatter,const ::scoped_string & scopedstrMatter2){}
   //virtual string directory()->matter(const ::scoped_string & scopedstrMatter,const ::scoped_string & scopedstrMatter2){}

   //bool apex_session_layer::is_inside_time_dir(const ::scoped_string & scopedstrPath){}
   //bool apex_session_layer::file_is_read_only(const ::scoped_string & scopedstrPath){}

   // Long PhRESSing time
   // time in ::times that a pressing is considered a double click
   unsigned int apex_session_layer::get_Long_PhRESSing_time()
   {

      return 0;
   }


   //void apex_session_layer::defer_initialize_user_presence(){}

   //virtual void     interactive_credentials(::account::credentials * pcredentials) override{}

   //bool apex_session_layer::on_create_frame_window(){}

   //virtual string account_get_user_sessid(const ::scoped_string & scopedstr) override{}

   // apex commented
   //void apex_session_layer::translate_os_key_message(::user::key * pkey){}

   //void apex_session_layer::on_user_logon(::account::user * puser){}

   //void apex_session_layer::pre_translate_message(::message::message* pmessage) override{}


   //session(){}
   //virtual ~session(){}


   //virtual ::user::style * get_user_style() const{}


   //void apex_session_layer::locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override{}
   //virtual string get_locale_schema_dir() override{}


   //virtual void     initialize(::particle * pparticle) override{}


   //virtual ::user::interaction * get_session_window(){}

   // apex commented

   //bool apex_session_layer::is_session() const override{}

   //void apex_session_layer::init_task() override{}


   //void apex_session_layer::process_init(){}

   //void apex_session_layer::init1(){}

   //void apex_session_layer::init2(){}

   //void apex_session_layer::init_session(){}

   //void apex_session_layer::init(){}

   // //void apex_session_layer::term(){}
   // void term2() override{}
   //
   //
   // void term1() override{}
   //
   //
   // void term_task() override{}
   //
   //
   // //void apex_session_layer::term_session(){}
   //
   // void process_term() override{}
   //

   // apex commented
   //::user::keyboard& keyboard(){}

   bool apex_session_layer::open_by_file_extension(const ::string& pszPathName, ::request* prequest)
   {

      return false;

   }


   bool apex_session_layer::open_by_file_extension(::request* prequest)
   {

      return false;

   }


   ::color::color apex_session_layer::get_default_color(::color::color color)
   {

      return {};

   }


   //void route_command(::message::command* pcommand, bool bRouteToKeyDescendant) override{}


   void apex_session_layer::frame_pre_translate_message(::message::message* pmessage)
   {


   }


   bool apex_session_layer::is_licensed(const ::string& pszId, bool bInteractive)
   {

      return false;

   }


   bool apex_session_layer::get_auth(const string& pszForm, string& strUsername, string& strPassword)
   {

      return false;

   }


   //void on_instantiate_application(::platform::application* papp) override{}


   //::application * application_get(const ::scoped_string & scopedstrAppId, bool bCreate, bool bSynch, ::request * prequest) override{}

   ::user::e_key apex_session_layer::key_modifiers()
   {

      return ::user::e_key_none;

   }


   //bool apex_session_layer::is_key_pressed(::user::enum_key ekey)
   //{}


   void apex_session_layer::set_key_pressed(::user::enum_key ekey, bool bPressed)
   {


   }


   // apex commented
   //void apex_session_layer::get_cursor_position(::int_point * ppoint){}
   //inline ::int_point get_cursor_position() {::int_point point{} get_cursor_position(&point){} return point{}}

   // apex commented
   //void apex_session_layer::set_cursor_pos(const ::int_point & point){}

   //virtual ::collection::index get_main_monitor(::int_rectangle * prectangle){}

   // bool apex_session_layer::set_main_monitor(::collection::index iMonitor){}
   // //virtual ::collection::count get_monitor_count(){}
   // //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle){}

   // //virtual ::collection::index get_main_workspace(::int_rectangle * prectangle){}

   // bool apex_session_layer::set_main_workspace(::collection::index iWorkspace){}
   // //virtual ::collection::count get_workspace_count(){}
   // //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle * prectangle){}

   // bool apex_session_layer::workspace_to_monitor(::int_rectangle * prectangle, ::collection::index iMonitor, ::collection::index iWorkspace){}

   // bool apex_session_layer::monitor_to_workspace(::int_rectangle * prectangle, ::collection::index iWorkspace, ::collection::index iMonitor){}

   // bool apex_session_layer::workspace_to_monitor(::int_rectangle * prectangle){}

   // bool apex_session_layer::monitor_to_workspace(::int_rectangle * prectangle){}

   // //virtual ::collection::count get_desk_monitor_count(){}
   // //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle * prectangle){}

   // virtual void  get_monitor(int_rectangle_array & rectaMonitor, int_rectangle_array & rectaIntersect, const ::int_rectangle & rectangle){}

   // // apex commented
   // //virtual ::collection::index initial_frame_position(::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bMove, ::user::interaction * pinteraction){}

   // virtual ::collection::index _get_best_zoneing(edisplay * pedisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bPreserveSize = false){}

   // virtual ::collection::index get_best_monitor(::int_rectangle * prectangle, const ::int_rectangle & rectangle, const ::user::activation & useractivation = {}){}

   // virtual ::collection::index get_best_workspace(::int_rectangle * prectangle, const ::int_rectangle& rectangle, const ::user::activation & useractivation = {}){}

   // virtual ::collection::index get_good_iconify(::int_rectangle * prectangle, const ::int_rectangle & rectangle){}

   // apex commented
   //virtual ::collection::index get_window_restore_1(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore){}

   // apex commented
   //virtual ::collection::index get_window_restore_2(::int_rectangle* prectangle, const ::int_rectangle& rectangle, ::user::interaction* pinteraction, edisplay edisplayRestore){}

   // apex commented
   //virtual ::collection::index get_good_move(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction){}

   // apex commented
   //virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction){}


   //void apex_session_layer::defer_instantiate_user_theme(const ::scoped_string & scopedstrUiInteractionLibrary){}
   //::pointer<::user::theme>instantiate_user_theme(const ::scoped_string & scopedstrExperienceLibrary, ::apex::application * papp){}
   //::pointer<::user::theme>get_user_theme(const ::scoped_string & scopedstrExperienceLibrary, ::apex::application * papp){}


   //void apex_session_layer::_001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText){}


   // apex commented
   //void apex_session_layer::set_bound_ui(::atom idImpact, ::user::interaction * pinteraction){}
   //virtual ::user::interaction * get_bound_ui(::atom idImpact){}

   // apex commented
   //void apex_session_layer::on_show_user_input_popup(::user::interaction * pinteraction){}

   //void apex_session_layer::on_user_logon(::account::user * puser){}


   //void apex_session_layer::initialize(::particle * pparticle) override{}

   //void apex_session_layer::install_message_routing(::channel* pchannel) override{}

   //void apex_session_layer::userex_process_init(){}
   //void apex_session_layer::userex_init1(){}
   //void apex_session_layer::init2() override{}
   //bool apex_session_layer::init3() override{}
   //bool apex_session_layer::initialize_filemanager(){}
   ///void apex_session_layer::init_session() override{}
   //void apex_session_layer::add_document_template(::user::impact_system * ptemplate){}

   //void apex_session_layer::term_session() override{}
   //void apex_session_layer::term3() override{}
   //bool apex_session_layer::finalize_filemanager(){}

   //void apex_session_layer::destroy() override{}


   bool apex_session_layer::InitializeLocalDataCentral()
   {

      return false;


   }


   //void apex_session_layer::bergedge_start() override{}

   void apex_session_layer::_001OnFileNew()
   {


   }


   //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override{}

   //virtual ::user::document* userex_on_request(::create* pcreate){}

   //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema){}

   //void load_string_table() override{}

   //      bool apex_session_layer::open_file(::filemanager::data* pdata, ::file::item_array& itema) override{}

   //void initialize_bergedge_application_interface(){}

   //bool apex_session_layer::create_bergedge(::request * prequest){}

   //void apex_session_layer::will_use_impact_hint(::atom idImpact){}

   //void apex_session_layer::on_app_request_bergedge_callback(::particle * pparticle){}

   // apex commented
   //virtual ::write_text::font_list* get_single_column_font_list(){}

   //void apex_session_layer::on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha){}


   //void request(::request * prequest) override{}

   // apex commented
   //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate){}

   // apex commented
   //bool apex_session_layer::place(::user::main_frame* pmainframe, ::create* pcreate){}

   //void apex_session_layer::request_topic_file(::payload& varQuery){}

   //void apex_session_layer::request_topic_file(){}

   //void apex_session_layer::check_topic_file_change(){}


   void apex_session_layer::launch_app(const ::string& psz)
   {
   }


   void apex_session_layer::install_app(const ::string& psz)
   {
   }


   //user ::pointer<::user::document>                  get_document(){}
   //user ::pointer<::user::impact>                    get_impact(){}
   //user ::pointer<::user::document>                  get_platform(){}
   //user ::pointer<::user::document>                  get_nature(){}


   //inline ::userex::userex* userex() { return m_puserex{} }


   //void apex_session_layer::process_init() override{}

   //void apex_session_layer::init1() override{}

   //void apex_session_layer::init() override{}

   //void apex_session_layer::os_native_bergedge_start() override{}

   // void apex_session_layer::on_request(::request* prequest) override{}


   void apex_session_layer::defer_initialize_host_window(const ::int_rectangle* lpcrect)
   {
   }


   ::pointer<::apex::application> apex_session_layer::get_current_application()
   {
      return {};

   }


   void apex_session_layer::set_app_title(const ::string& pszAppId, const ::string& pszTitle)
   {
   }


   ::pointer<::apex::session> apex_session_layer::get_session()
   {
      return {};
   }


   bool apex_session_layer::is_remote_session()
   {

      return false;
   }


   ::string_array apex_session_layer::get_user_wallpaper()
   {

      return {};

   }


   ::user::interaction_base* apex_session_layer::get_user_interaction_host()
   {

      return nullptr;
   }


   ::user::interaction_base* apex_session_layer::get_host_primitive()
   {

      return nullptr;
   }


} // namespace platform
