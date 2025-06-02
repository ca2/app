// From core/user/user/user.h by camilo
// on 2024-06-22 15:12 <3ThomasBorregaardSorensen!!
#pragma once


#include "base/user/user/user.h"
//#include "core/filesystem/filemanager/component.h"


namespace bred
{


   class CLASS_DECL_BRED user :
      virtual public ::base::user
      //,
      //virtual public ::filemanager::component
   {
   public:



      //::user::impact_system *                      m_ptemplatePlaceHolder;



      //::user::multiple_document_template *         m_ptemplateProgress2;


      //map < ::type, ::user::impact_system * >      m_mapTemplate;

      //atom_map < ::user::impact_system * >           m_mapimpactsystem;


      //::pointer<::userex::userex>             m_puserex;
//      bool                                         m_bFontSelInitialized;
//
//
//      
//
//
//      string_array                                 m_straEscape;
//
//      ::type_atom                                  m_typeatomDefaultMeshData;
//      ::type_atom                                  m_typeatomDefaultListHeader;
//      ::type_atom                                  m_typeatomDefaultListData;
//
//      ::pointer<::userfs::userfs>               m_puserfs;
//
//      ::e_status                                   m_estatus;
//
//      //::pointer<::user::keyboard>             m_pkeyboard;
//
//      //index                                      m_iEdge;
//      //::map < ::user::enum_key, ::user::enum_key, bool, bool > *  m_pmapKeyPressed;
//
//      //bool                                       m_bProgrammerMode;
//
//      //bool                                       m_bSystemSynchronizedCursor;
//      //int_point                                      m_pointCursor;
//
//      //pointer_array < ::user::interaction >         m_uiptraToolWindow;
//
//      //::windowing::window *                            m_pimplPendingFocus2;
//      //::user::interaction *                                 m_puiLastUserInputPopup;
//      //::image::cursor *                                    m_pcursor;
//      //::image::cursor *                                    m_pcursorCursor;
//      //e_cursor                                              m_ecursorDefault;
//      //e_cursor                                              m_ecursor;
//
//      //::pointer<::user::theme>                           m_ptheme;
//      //string_map < ::pointer<::user::theme >>            m_mapTheme;
//
//      //::user::interaction *                                 m_puiCapture;
//      //bool                                                  m_bDrawCursor;
//
//
//      //::pointer<::user::copydesk>                        m_pcopydesk;
//
//      //::user::interaction *                                 m_puiMouseMoveCapture;
//      //::user::interaction *                                 m_puiLastLButtonDown;
//
//
//      //::write_text::font_enumeration_item_array                        m_fontenumitema;
//
//      ////index                                               m_iEdge;
//
//      //::pointer<::account::department>                   m_paccount;
//      ////::pointer<::account::licensing>                    m_plicensing;
//      ////::pointer<::user::interaction>                     m_puserinteractionSystem;
//
//      //::payload                                                   m_varTopicFile;
//      //::payload                                                   m_varCurrentImpactFile;
//      //bool                                                  m_bShowPlatform;
//
//      //::pointer<::text::context>                     m_ptextcontext;
//
//
//      //bool                                                  m_bSystemSynchronizedScreen;
//      //int_rectangle_array                                            m_rectangleaMonitor;
//      //int_rectangle_array                                            m_rectangleaWorkspace;
//      //index                                                 m_iMainMonitor;
//      //index                                                 m_iMainWorkspace;
//
//
//
//      //atom_map < ::user::interaction * >                      m_mapboundui;
//
//
//
//      //::pointer<::userpresence::department>              m_puserpresence;
//
//
//      ////::pointer<::ftpfs>                                 m_pftpfs;
//      ////::pointer<::fs::remote_native>                     m_premotefs;
//      ////::pointer<::fs::fs>                                m_pfs;
//      ////::pointer<::fs::data>                              m_pfsdata;
//      ////::pointer<::ifs>                                   m_pifs;
//      //////ke
//      ////bool                                                  m_bIfs;
//
//      //bool                                                  m_bMatterFromHttpCache;
//
//      //unsigned int                                                 m_dwLongPhRESSingTime;
//
//
//      //::pointer<::userex::userex>                        m_puserex;
//      //bool                                                  m_bFontSelInitialized;
//      //::pointer<::write_text::font_list>                     m_pfontlistSingleColumn;
//      //::pointer<::user::user>                            m_puser;
//      


      user();
      ~user() override;


      // ::bred::application* get_app();
      // ::bred::session* get_session();
      // ::bred::system* get_system();
      //


      void destroy() override;


      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style* pstyle, ::menu::item* pitem) override;


      // ::user::shell* shell();
      
      
      virtual void init1() override;
      virtual void init2() override;
      virtual void init() override;

//
//      virtual pointer< ::sequence < ::conversation > > dialog_box(::particle * pparticle, const ::string & pszMatter, ::property_set & propertyset);
//
//
//      virtual pointer< ::sequence < ::conversation > > ui_message_box(::particle * pparticle, ::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok);
//      virtual pointer< ::sequence < ::conversation > > ui_message_box_timeout(::particle * pparticle, ::user::interaction_base * puiOwner, const ::string & pszMessage, const ::string & pszTitle = nullptr, const class time & timeTimeout = ::time::infinity(), const ::e_message_box & emessagebox = e_message_box_ok);
//      //virtual void ui_message_box_timeout(::object* pparticle, ::user::interaction_base* puiOwner, ::payload payload, class ::time timeTimeout, unsigned int fuStyle = e_message_box_ok, ::aura::application* papp = nullptr, const function_arg& functionargResult = function_arg());
//
//      virtual void on_file_manager_open(::filemanager::data* pdata, ::file::item_array& itema);
//
//      int track_popup_menu(const ::string & pszMatter, const ::int_point & point, ::pointer<::user::interaction>puie) override;
//
//
//      virtual bool get_fs_size(string & strSize, const ::string & pszPath, bool & bPending);
//      virtual bool get_fs_size(long long & i64Size, const ::string & pszPath, bool & bPending);
//
//      virtual void data_on_after_change(::message::message * pmessage);
//
//      class keyboard & keyboard();
//
//      virtual bool modal_get_color(::user::interaction * puiOwner, ::color::hls & hls);
//
//      virtual void AddToRecentFileList(const ::string & pszPathName);
//
//
//      virtual void route_command(::message::command * pcommand, bool bRouteToKeyDescendant);
//
//
//      virtual void _001OnFileNew();
//
//
//      ::pointer<::user::list_header>default_create_list_header(::particle * pparticle);
//      ::pointer<::user::mesh_data>default_create_mesh_data(::particle * pparticle);
//      ::pointer<::user::list_data>default_create_list_data(::particle * pparticle);
//
//
//      ::type_atom default_type_mesh_data();
//      ::type_atom default_type_list_header();
//      ::type_atom default_type_list_data();
//
//
//      virtual void will_use_impact_hint(::atom idImpact);
//
//
//      virtual void term_instance() override;
//
//
//      void LoadStdProfileSettings(unsigned int nMaxMRU = 10);
//
//      ::collection::count get_template_count() const;
//      ::pointer<::user::impact_system>get_template(::collection::index index) const;
//
//
//
//
//      ::user::document * hold(::pointer<::user::interaction>pinteraction);
//
//
//      virtual void initialize(::particle * pparticle) override;
//
//
//      //virtual bool do_prompt_file_name(::payload& payloadFile, string strTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system* ptemplate, ::user::document* pdocument, const atom & atomFileManager = "file_manager_save");
//
//
//      virtual void initialize_userex();
//
//      virtual void userfs_init1();
//      virtual void userfs_process_init();
//
//
//      //virtual void create_html();
//
//      //virtual ::pointer<::userex::userex>create_userex();
//      //virtual ::pointer<::userfs::userfs>create_userfs();
//
//
//      virtual ::type_atom get_pane_tab_impact_type_info();
//      //virtual ::type_atom get_simple_frame_window_type_info() override;
//      //virtual ::type_atom get_simple_child_frame_type_info();
//
//
//      virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha) override;
//
//
//
//
//      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }
//
//      //virtual bool is_session() const override;
//
//      ////void construct(::particle * pparticle, int iPhase) override;
//
//      //virtual void process_init();
//
//      //virtual void init1();
//
//      //virtual void init2();
//
//      //virtual void init_session();
//
//      //virtual void init();
//
//      //virtual void term();
//
//      //virtual void term_session();
//
//
//      //inline class ::fs::data * fs() { return m_pfsdata; }
//
//
//      ////inline ::sockets::sockets & sockets() { return *m_psockets; }
//
//
//      //virtual int_size get_window_minimum_size();
//
//
//      ////virtual void  get_cursor_position(::int_point * ppoint);
//
//      //virtual bool on_get_thread_name(string& strThreadName) override;
//
//
//      //virtual void on_request(::request * prequest) override;
//
//
//      ////virtual string matter_as_string(const ::string & pszMatter, const ::string & pszMatter2);
//      ////virtual string directory()->matter(const ::string & pszMatter, const ::string & pszMatter2);
//
//      ////virtual bool is_inside_time_dir(const ::string & pszPath);
//      ////virtual bool file_is_read_only(const ::string & pszPath);
//
//      //// Long PhRESSing time
//      //// time in ::times that a pressing is considered a double click
//      //virtual unsigned int get_Long_PhRESSing_time();
//
//      //virtual void defer_initialize_user_presence();
//
//      ////virtual void     interactive_credentials(::account::credentials * pcredentials) override;
//
//      //virtual bool on_create_frame_window();
//
//      ////virtual string account_get_user_sessid(const ::string & str) override;
//
//      //virtual void translate_os_key_message(::user::key * pkey);
//
//      //virtual void on_user_logon(::account::user * puser);
//
//      //virtual void pre_translate_message(::message::message * pmessage) override;
//
//      ////session();
//      ////virtual ~session();
//
//
//      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
//      //virtual string get_locale_schema_dir() override;
//
//
//      ////virtual void     initialize(::particle * pparticle) override;
//
//
//      //virtual ::user::interaction * get_session_window();
//
//
//      //::text::context *                        textcontext() { return m_ptextcontext; }
//
//      ////virtual bool is_session() const override;
//
//      //virtual void init_thread() override;
//
//      ////virtual void process_init();
//
//      ////virtual void init1();
//
//      ////virtual void init2();
//
//      ////virtual void init_session();
//
//      ////virtual void init();
//
//      ////virtual void term();
//      //virtual void term2();
//
//      //virtual void term1();
//
//      //virtual void term_thread() override;
//
//      ////virtual void term_session();
//
//      //virtual void process_term();
//
//      //::user::keyboard& keyboard();
//
//      //virtual bool open_by_file_extension(const ::string & pszPathName, ::request * prequest = nullptr);
//
//      //virtual bool open_by_file_extension(::create * pcc);
//
//      ////::pointer<::aura::application>get_new_application(::particle * pparticle, const ::string & pszAppId);
//
//      //virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style_pointer & pstyle, ::menu::item * pitem) override;
//
//      //virtual ::color::color get_default_color(unsigned long long u);
//
//      ////virtual ::int_size get_window_minimum_size();
//
//      //virtual void frame_pre_translate_message(::message::message * pmessage);
//
//      //virtual bool defer_create_session_frame_window();
//
//      //inline ::account::department * account() { return m_paccount; }
//
//      //::user::copydesk & copydesk();
//
//      //virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);
//
//      //virtual void on_erase_user(::account::user * puser);
//
//      ////virtual void defer_initialize_user_presence();
//
//      //virtual bool is_licensed(const ::string & pszId, bool bInteractive = true);
//
//      //virtual void userstyle(::user::style_context * pcontext);
//
//      //virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);
//
//      //virtual void interactive_credentials(::account::credentials * pcredentials);
//
//      ////virtual void on_request(::request * prequest) override;
//
//      //::aura::application * application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::request * prequest) override;
//
//      //virtual bool is_key_pressed(::user::enum_key ekey);
//
//      //virtual void set_key_pressed(::user::enum_key ekey, bool bPressed);
//
//      //virtual ::user::interaction_base * get_keyboard_focus();
//      //virtual bool set_keyboard_focus(::user::interaction_base * pkeyboardfocus);
//      //
//      //virtual ::user::interaction_base * clear_focus();
//
//
//      //virtual ::user::interaction_base * get_active_ui() override;
//      //virtual ::user::interaction_base * get_focus_ui();
//
//      //virtual void on_finally_focus_set(::user::interaction_base * pelementalFocus);
//
//      //virtual oswindow get_capture();
//
//      //virtual bool set_cursor(::user::interaction * pinteraction, ::image::cursor * pcursor);
//      //virtual bool set_cursor(::user::interaction * pinteraction, e_cursor ecursor);
//      //virtual bool set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor);
//      //virtual ::image::cursor * get_cursor();
//      //virtual ::image::cursor * get_default_cursor();
//
//      //virtual bool on_ui_mouse_message(::message::mouse * pmouse);
//
//      //virtual ::user::interaction_base * GetActiveWindow();
//      //virtual ::user::interaction_base * GetFocus();
//
//      //virtual bool ReleaseCapture();
//      //virtual ::pointer<::user::interaction>GetCapture();
//
//      ////virtual void translate_os_key_message(::user::key * pkey);
//      ////virtual bool on_create_frame_window();
//
//      //virtual void get_cursor_position(::int_point * ppoint);
//      //inline ::int_point get_cursor_position() {::int_point point; get_cursor_position(&point); return point;}
//
//      //virtual void set_cursor_pos(const ::int_point & point);
//
//      //virtual ::collection::index get_main_monitor(::int_rectangle * prectangle = nullptr);
//
//      //virtual bool set_main_monitor(::collection::index iMonitor);
//      //virtual ::collection::count get_monitor_count();
//      //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);
//
//      //virtual ::collection::index get_main_workspace(::int_rectangle * prectangle = nullptr);
//
//      //virtual bool set_main_workspace(::collection::index iWorkspace);
//      //virtual ::collection::count get_workspace_count();
//      //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle * prectangle);
//
//      //virtual bool workspace_to_monitor(::int_rectangle * prectangle, ::collection::index iMonitor, ::collection::index iWorkspace);
//
//      //virtual bool monitor_to_workspace(::int_rectangle * prectangle, ::collection::index iWorkspace, ::collection::index iMonitor);
//
//      //virtual bool workspace_to_monitor(::int_rectangle * prectangle);
//
//      //virtual bool monitor_to_workspace(::int_rectangle * prectangle);
//
//      //virtual ::collection::count get_desk_monitor_count();
//      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle * prectangle);
//
//      //virtual void  get_monitor(int_rectangle_array & rectaMonitor, int_rectangle_array & rectaIntersect, const ::int_rectangle & rectangle);
//
//      //virtual ::collection::index initial_frame_position(::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bMove, ::user::interaction * pinteraction);
//
//      //virtual ::collection::index _get_best_zoneing(edisplay * pedisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bPreserveSize = false);
//
//      //virtual ::collection::index get_best_monitor(::int_rectangle * prectangle, const ::int_rectangle & rectangle, const ::user::activation & useractivation = {});
//
//      //virtual ::collection::index get_best_workspace(::int_rectangle * prectangle, const ::int_rectangle& rectangle, const ::user::activation & useractivation = {});
//
//      //virtual ::collection::index get_good_iconify(::int_rectangle * prectangle, const ::int_rectangle & rectangle);
//
//      //virtual ::collection::index get_window_restore_1(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);
//
//      //virtual ::collection::index get_window_restore_2(::int_rectangle* prectangle, const ::int_rectangle& rectangle, ::user::interaction* pinteraction, edisplay edisplayRestore);
//
//      //virtual ::collection::index get_good_move(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction);
//
//      //virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction);
//
//
//
//
//      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText);
//
//
//      //virtual void set_bound_ui(::atom idImpact, ::user::interaction * pinteraction);
//      //virtual ::user::interaction * get_bound_ui(::atom idImpact);
//
//      //virtual void on_show_user_input_popup(::user::interaction * pinteraction);
//
//      ////virtual void on_user_logon(::account::user * puser);
//
//
//
//      ////virtual void initialize(::particle * pparticle) override;
//
//      //virtual void install_message_routing(::channel* pchannel) override;
//
//      ////virtual void userex_process_init();
//      ////virtual void userex_init1();
//      ////virtual void init2() override;
//      ////virtual bool init3() override;
//      ////virtual bool initialize_filemanager();
//      /////virtual void init_session() override;
//      ////virtual void add_document_template(::user::impact_system * ptemplate);
//
//      ////virtual void term_session() override;
//      ////virtual void term3() override;
//      ////virtual bool finalize_filemanager();
//
//      //template < typename VIEW >
//      //::pointer<::user::document>  create_form(::pointer<::user::interaction>userinteractionParent = nullptr, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_form(::type point, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_form(::user::form_callback* pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_form(::pointer<::user::form>impact, ::user::form_callback* pcallback, ::pointer<::user::interaction>serinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_child_form(::user::form_callback* pcallback, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument), ::payload varArgs = ::payload(::e_type_empty_argument));
//      //template < typename VIEW >
//      //::pointer<::user::document>  create_child_form(::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_child_form(::type point, ::pointer<::user::interaction>userinteractionParent, ::payload payload = ::payload(::e_type_empty_argument));
//      //::pointer<::user::document>  create_child_form(::pointer<::user::form>impact, ::user::form_callback* pcallback, ::pointer<::user::interaction>serinteractionParent, ::payload payload = ::payload(::e_type_empty_argument));
//
//
//      ////virtual ::pointer<::user::menu_interaction>create_menu_button(::user::style_pointer & pstyle, ::menu::item* pitem) override;
//
//
//
//
//      //bool InitializeLocalDataCentral();
//
//      ////virtual void bergedge_start() override;
//
//      //void _001OnFileNew();
//
//      ////void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
//
//      //virtual ::user::document* userex_on_request(::create* pcreate);
//
//      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);
//
//      ////void load_string_table() override;
//
//      //virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;
//
//      //void initialize_bergedge_application_interface();
//
//      ////virtual bool create_bergedge(::request * prequest);
//
//      //virtual void will_use_impact_hint(::atom idImpact);
//
//      ////virtual void on_app_request_bergedge_callback(::particle * pparticle);
//
//      //virtual ::write_text::font_list* get_single_column_font_list();
//
//      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array& patha);
//
//
//      //virtual void do_request(::create* pcreate) override;
//
//      //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);
//
//      //virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);
//
//      //virtual void request_topic_file(::payload& varQuery);
//
//      //virtual void request_topic_file();
//
//      //virtual void check_topic_file_change();
//
//
//      //void launch_app(const ::string & psz);
//      //void install_app(const ::string & psz);
//
//
//
//      //::pointer<::user::document>                  get_document();
//      //::pointer<::user::impact>                    get_impact();
//      //::pointer<::user::document>                  get_platform();
//      //::pointer<::user::document>                  get_nature();
//
//
//      //inline ::userex::userex* userex() { return m_puserex; }
//
//
//      ////virtual void process_init() override;
//
//      ////virtual void init1() override;
//
//      ////virtual void init() override;
//
//      ////virtual void os_native_bergedge_start() override;
//
//      //virtual void     main() override;
//
//      //virtual void defer_initialize_host_window(const ::int_rectangle * lprect = nullptr);
//
//      ////virtual service_base * allocate_new_service() override;
//
//      ////void on_request(::create* pcreate) override;
//
//      //::pointer<::aura::application>get_current_application();
//
//
//
//      //virtual void set_app_title(const ::string & pszAppId, const ::string & pszTitle);
//
//      //virtual ::pointer<::aura::session>get_session();
//
//      ////virtual void term() override;
//
//      ////virtual bool open_by_file_extension(const ::string & pszPathName, ::create* pcreate = nullptr) override;
//      ////virtual bool open_by_file_extension(::create* pcc) override;
//
//      ////virtual bool is_session() const override;
//
//      //virtual bool is_mouse_button_pressed(::user::enum_mouse emouse);
//
//      //virtual bool is_remote_session();
//
//      ////virtual ::image::cursor * get_cursor() override;
//      ////virtual ::image::cursor* get_default_cursor() override;
//
//      ////virtual ::collection::count   get_monitor_count() override;
//      ////virtual bool      get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle* prectangle) override;
//
//
//      ////virtual void on_user_logon(::account::user* puser) override;
//
//
//      ////virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle& rectangle, ::draw2d::brush_pointer& pbrushText) override;
//
//
//      //virtual string_array get_user_wallpaper();
//
//
//
//      ////virtual void interactive_credentials(::account::credentials* pcredentials) override;
//
//
//
//      ////session();
//      ////virtual ~session();
//
//      //inline ::user::user* user() { return m_puser; }
//
//      ////virtual ::pointer<::user::impact>                     get_impact();
//
//
//      ////virtual void     initialize(::particle * pparticle) override;
//
//
//      ////virtual void frame_pre_translate_message(::message::message* pmessage) override;
//
//      ////virtual void process_init() override;
//
//      ////virtual void init1() override;
//
//      ////virtual void init() override;
//
//      ////virtual void term_session() override;
//
//      ////virtual void interactive_credentials(::account::credentials* pcredentials) override;
//
//      ////virtual void on_finally_focus_set(::user::interaction_base* pelementalFocus) override;
//
//      ////virtual ::user::menu_interaction * create_menu_button(::user::style_pointer & pstyle, ::menu::item * pitem) override;
//
//      ////virtual oswindow get_capture() override;
//
//
//      ////virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle& rectangle, ::draw2d::brush_pointer& pbrushText) override;
//
//
//      //virtual bool prepare_menu_button(::menu::item* pitem) override;
//
//      ////virtual bool on_ui_mouse_message(::message::mouse* pmouse) override;
//
//
//
//      ::user::interaction_base* m_pmousefocusLButtonDown;
//      ::user::interaction_base* m_pmousefocusRButtonDown;
//      //string_array                       m_straEscape;
//      //::user::style_pointer              m_puserstyle;
//
//
//      //::user::style * get_user_style();
//
//
//      //virtual void init1() override;
//      //virtual void init2() override;
//      //virtual void init() override;
//
//
//
//
//      //virtual ::user::interaction_base* get_mouse_focus_LButtonDown();
//      //virtual void set_mouse_focus_LButtonDown(::user::interaction_base* pmousefocus);
//      //virtual ::user::interaction_base* get_mouse_focus_RButtonDown();
//      //virtual void set_mouse_focus_RButtonDown(::user::interaction_base* pmousefocus);
//
//
//
//      //virtual void SendMessageToWindows(::enum_message emessage, ::wparam wparam, ::lparam lparam);
//
//      virtual void term() override;
//
//      virtual ::type_atom controltype_to_typeinfo(::user::enum_control_type econtroltype) override;
//
//

      
   };


} // namespace bred



