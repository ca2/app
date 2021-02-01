#pragma once


namespace aura
{


   class CLASS_DECL_AURA session :
      virtual public ::aqua::session,
      virtual public ::filemanager::item_action,
      virtual public ::user::style_base
   {
   public:


//#if defined _UWP
//
//      ::uwp::directx_framework_view ^                          m_frameworkview;
//
//#endif


      __composite(::user::keyboard)                         m_pkeyboard;

      bool                                                  m_bAcceptsFirstResponder;

      ::user::interaction_impl *                            m_pimplPendingFocus2;
      ::user::interaction *                                 m_puiLastUserInputPopup;
      ::draw2d::cursor *                                    m_pcursor;
      ::draw2d::cursor *                                    m_pcursorCursor;
      e_cursor                                              m_ecursorDefault;
      e_cursor                                              m_ecursor;

      ::user::interaction *                                 m_puiCapture;
      bool                                                  m_bDrawCursor;

      //__pointer_array(::user::interaction)                  m_uiptraToolWindow;

      __composite(::user::copydesk)                         m_pcopydesk;

      ::user::interaction *                                 m_puiMouseMoveCapture;
      ::user::interaction *                                 m_puiLastLButtonDown;


      ::draw2d::font_enum_item_array                        m_fontenumitema;

      __composite(::apex::savings)                          m_psavings;

      index                                                 m_iMainMonitor;
      index                                                 m_iMainWkspace;

      id_map < ::user::interaction * >                      m_mapboundui;

      __composite(::draw2d::font_list)                      m_pfontlistSingleColumn;
      __composite(::user::user)                             m_puser;


      session();
      virtual ~session();


      virtual ::u32 get_monitor_color_temperature(index iMonitor);
      virtual bool adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dwGamma);
      virtual bool os_adjust_monitor(index iMonitor, ::u32 dwTemperature, double dBrightness, double dwGamma);


#if defined(WINDOWS)

      ////#pragma message("at macos??")
      //static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32* prcMonitor, lparam dwData);

      //void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, RECTANGLE_I32* prcMonitor);

#if defined(WINDOWS_DESKTOP)
      
      //inline ::user::interaction* system_window() { return __user_interaction(m_puiSession); }

#endif


#endif

      virtual ::e_status finish(::context_object * pcontextobjectFinish = nullptr) override;


      virtual void enum_display_monitors() override;

      virtual index get_main_monitor(RECTANGLE_I32* prectangle = nullptr) override;

      virtual ::count get_monitor_count() override;
      virtual bool  get_monitor_rect(index iMonitor, RECTANGLE_I32* prectangle) override;

      virtual ::count get_desk_monitor_count() override;
      virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32* prectangle) override;


      virtual index get_main_wkspace(RECTANGLE_I32* prectangle = nullptr) override;

      virtual ::count get_wkspace_count() override;
      virtual bool  get_wkspace_rect(index iWkspace, RECTANGLE_I32* prectangle) override;

      virtual ::count get_desk_wkspace_count() override;
      virtual bool  get_desk_wkspace_rect(index iWkspace, RECTANGLE_I32* prectangle) override;

      virtual index get_ui_wkspace(::user::interaction* pinteraction);


      virtual ::e_status     initialize(::layered * pobjectContext) override;

      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      virtual bool is_session() const override;

      //void construct(::object * pobject, int iPhase) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init1() override;

      virtual ::e_status init2() override;

      //virtual ::e_status init_session() override;

      virtual ::e_status init() override;

      virtual void term() override;

      //virtual void term_session() override;


      inline class ::fs::data * fs() { return m_pfsdata; }


      //inline ::sockets::sockets & sockets() { return *m_psockets; }


      virtual size_i32 get_window_minimum_size() override;


      //virtual void  get_cursor_pos(POINT_I32 * ppoint);

      virtual bool on_get_thread_name(string& strThreadName) override;


      virtual void on_request(::create * pcreate) override;


      //virtual string matter_as_string(const char * pszMatter,const char * pszMatter2);
      //virtual string dir().matter(const char * pszMatter,const char * pszMatter2);

      //virtual bool is_inside_time_dir(const char * pszPath);
      //virtual bool file_is_read_only(const char * pszPath);

      // Long PhRESSing time
      // time in milliseconds that a pressing is considered a double click
      virtual ::u32 get_Long_PhRESSing_time() override;

      //virtual void defer_initialize_user_presence();

      //virtual ::e_status     interactive_credentials(::account::credentials * pcredentials) override;

      virtual bool on_create_frame_window() override;

      //virtual string account_get_user_sessid(const string & str) override;

      virtual void translate_os_key_message(::user::key * pkey);

      //virtual void on_user_logon(::account::user * puser);

      virtual void pre_translate_message(::message::message * pmessage) override;

      //session();
      //virtual ~session();


      //virtual ::user::style * get_user_style() const;

      virtual ::user::style* get_user_style();


      virtual bool simple_ui_draw_focus_rect(::user::interaction * pinteraction, ::draw2d::graphics_pointer& pgraphics);


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const string & strLocale, const string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual ::e_status     initialize(::layered * pobjectContext) override;


      //virtual ::user::interaction * get_session_window() override;


      //::apex::str_context * str_context() { return m_puserstrcontext; }

      //virtual bool is_session() const override;

      //virtual ::e_status init_thread() override;

      //virtual ::e_status process_init();

      //virtual ::e_status init1();

      //virtual ::e_status init2();

      //virtual ::e_status init_session();

      //virtual ::e_status init();

      //virtual void term();
      virtual void term2() override;

      virtual void term1() override;

      //virtual void term_thread() override;

      //virtual void term_session();

      virtual void process_term() override;

      ::user::keyboard& keyboard();

      virtual bool open_by_file_extension(const char * pszPathName, ::create * pcreate = nullptr) override;

      virtual bool open_by_file_extension(::create * pcc) override;

      //__pointer(::aura::application) get_new_application(::layered * pobjectContext, const char * pszAppId);

      inline ::apex::savings &                  savings()      { return *m_psavings; }

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem);

      virtual color32_t get_default_color(u64 u) override;

      //virtual ::size_i32 get_window_minimum_size();

      virtual void frame_pre_translate_message(::message::message * pmessage) override;

      virtual bool defer_create_session_frame_window();

      //inline ::account::department * account() { return m_paccount; }

      ::user::copydesk & copydesk();

      //virtual ::account::user * get_user(::file::path pathUrl = nullptr, bool bFetch = false, bool bInteractive = true);

      //virtual void on_remove_user(::account::user * puser);

      virtual bool is_licensed(const char * pszId, bool bInteractive = true) override;

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword) override;

      //virtual void interactive_credentials(::account::credentials * pcredentials);

      //::aura::application * application_get(const char * pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual bool is_key_pressed(::user::e_key ekey) override;

      virtual void set_key_pressed(::user::e_key ekey, bool bPressed) override;

      virtual ::user::primitive * get_active_ui() override;

      virtual void on_finally_focus_set(::user::primitive * pelementalFocus);

      virtual oswindow get_capture();

      virtual bool set_cursor(::user::interaction * pinteraction, ::draw2d::cursor * pcursor);
      virtual bool set_cursor(::user::interaction * pinteraction, e_cursor ecursor);
      virtual bool set_default_cursor(::user::interaction * pinteraction, e_cursor ecursor);
      virtual ::draw2d::cursor * get_cursor();
      virtual ::draw2d::cursor * get_default_cursor();

      virtual bool on_ui_mouse_message(::message::mouse * pmouse);

      virtual ::user::primitive * GetActiveWindow();
      virtual ::user::primitive * GetFocus();

      virtual bool ReleaseCapture();
      virtual __pointer(::user::interaction) GetCapture();

      //virtual void translate_os_key_message(::user::key * pkey);
      //virtual bool on_create_frame_window();

      virtual void get_cursor_pos(POINT_I32 * ppoint) override;
      inline ::point_i32 get_cursor_pos() {::point_i32 point; get_cursor_pos(&point); return point;}

      //virtual void set_cursor_pos(const ::point_i32 & point) override;

//      virtual index get_main_monitor(RECTANGLE_I32 * prectangle = nullptr) override;

      virtual bool set_main_monitor(index iMonitor) override;
      //virtual ::count get_monitor_count() override//;
      //virtual bool  get_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle) override//;

//      virtual index get_main_wkspace(RECTANGLE_I32 * prectangle = nullptr) override;

      virtual bool set_main_wkspace(index iWkspace) override;
      //virtual ::count get_wkspace_count() override;
      //virtual bool  get_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle) override;

      virtual bool wkspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWkspace) override;

      virtual bool monitor_to_wkspace(RECTANGLE_I32 * prectangle, index iWkspace, index iMonitor) override;

      virtual bool wkspace_to_monitor(RECTANGLE_I32 * prectangle) override;

      virtual bool monitor_to_wkspace(RECTANGLE_I32 * prectangle) override;

      //virtual ::count get_desk_monitor_count() override;
      //virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle) override;

      virtual void  get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const ::rectangle_i32 & rectangle) override;

      virtual index initial_frame_position(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bMove, ::user::interaction * pinteraction);

      virtual index _get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bPreserveSize = false) override;

      virtual index get_best_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default) override;

      virtual index get_best_wkspace(::rectangle_i32 * prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation = e_activation_default) override;

      virtual index get_good_iconify(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle) override;

      virtual index get_window_restore_1(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      virtual index get_window_restore_2(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle, ::user::interaction* pinteraction, edisplay edisplayRestore);

      virtual index get_good_move(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction);

      //virtual index get_ui_wkspace(::user::interaction * pinteraction);


      //virtual void defer_instantiate_user_theme(const char * pszUiInteractionLibrary = nullptr);
      //__pointer(::user::theme) instantiate_user_theme(const char * pszExperienceLibrary, ::aura::application * papp = nullptr);
      //__pointer(::user::theme) get_user_theme(const char * pszExperienceLibrary, ::aura::application * papp = nullptr);


      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & brushText);


      virtual void set_bound_ui(::id idView, ::user::interaction * pinteraction);
      virtual ::user::primitive * get_bound_ui(::id idView);

      virtual void on_show_user_input_popup(::user::interaction * pinteraction);

      //virtual void on_user_logon(::account::user * puser);



      //virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual void install_message_routing(::channel* pchannel) override;

      //virtual ::e_status userex_process_init();
      //virtual ::e_status userex_init1();
      //virtual ::e_status init2() override;
      //virtual bool init3() override;
      //virtual bool initialize_filemanager();
      ///virtual ::e_status init_session() override;
      //virtual void add_document_template(::user::impact_system * ptemplate);

      //virtual void term_session() override;
      //virtual void term3() override;
      //virtual bool finalize_filemanager();

      virtual void finalize() override;

      //template < typename VIEW >
      //__pointer(::user::document)   create_form(__pointer(::user::interaction) pwndParent = nullptr, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(::type point_i32, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //template < typename VIEW >
      //__pointer(::user::document)   create_child_form(__pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(::type point_i32, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = payload(::e_type_empty_argument));

      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle,::user::menu_item* pitem) override;

      virtual bool InitializeLocalDataCentral() override;

      //virtual ::e_status bergedge_start() override;

      void _001OnFileNew();

      //virtual void route_command_message(::user::command * pcommand) override;

      //virtual ::user::document* userex_on_request(::create* pcreate);

      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);

      //void load_string_table() override;

      virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;

      //void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::create * pcreate);

      //virtual void will_use_view_hint(::id idView);

      //virtual void on_app_request_bergedge_callback(::layered * pobjectContext);

      virtual ::draw2d::font_list* get_single_column_font_list();

      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha);


      virtual ::e_status do_request(::create* pcreate) override;

      virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);

      virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);

      virtual void request_topic_file(::payload& varQuery) override;

      virtual void request_topic_file() override;

      virtual void check_topic_file_change() override;


      void launch_app(const char* psz);
      void install_app(const char* psz);



      //user __pointer(::user::document)                   get_document();
      //user __pointer(::user::impact)                     get_view();
      //user __pointer(::user::document)                   get_platform();
      //user __pointer(::user::document)                   get_nature();


      //inline ::userex::userex* userex() { return m_puserex; }


      //virtual ::e_status process_init() override;

      //virtual ::e_status init1() override;

      //virtual ::e_status init() override;

      //virtual ::e_status os_native_bergedge_start() override;

      virtual ::e_status     main() override;

      virtual ::e_status defer_initialize_host_window(const RECTANGLE_I32 * lprect = nullptr) override;

      //virtual service_base * allocate_new_service() override;

      //void on_request(::create* pcreate) override;

      __pointer(::aura::application) get_current_application();



      virtual void set_app_title(const char* pszAppId, const char* pszTitle) override;

      virtual __pointer(::apex::session) get_context_session() override;

      //virtual void term() override;

      //virtual bool open_by_file_extension(const char* pszPathName, ::create* pcreate = nullptr) override;
      //virtual bool open_by_file_extension(::create* pcc) override;

      //virtual bool is_session() const override;

      virtual bool is_mouse_button_pressed(::user::enum_mouse emouse);

      virtual bool is_remote_session() override;


      virtual string_array get_user_wallpaper() override;

      inline ::user::user* user() { return m_puser; }


      virtual ::color get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate = ::user::e_state_none) const override;
      virtual bool get_int(const ::user::interaction* pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate = ::user::e_state_none) const override;
      virtual bool get_double(const ::user::interaction* pinteraction, double & i, ::user::enum_double eint, ::user::enum_state estate = ::user::e_state_none) const override;


   };


} // namespace aura



