#pragma once


namespace apex
{


   class CLASS_DECL_APEX session:
      virtual public ::apex::context,
      virtual public ::application_container
      //,
      //virtual public ::filemanager::item_action //,
      //virtual public ::filemanager::component,
      //virtual public ::user::document_manager_container
   {
   public:


      class CLASS_DECL_APEX map:
         virtual public ::map < index, __pointer(::apex::session) >
      {


      };


//#if defined _UWP
//
//      ::universal_windows::directx_framework_view ^                          m_frameworkview;
//
//#endif


      //::aqua::session* m_paquasession;
      //::aura::session* m_paurasession;
      //::axis::session* m_paxissession;
      //::base::session* m_pbasesession;
      //::bred::session* m_pbredsession;
      //::core::session* m_pcoresession;

      // For Mobile systems it is particularly meaningful...
      // ... is is the "Main Window" (sometimes just a concept) holding the App.
      // For Desktop Applications a meaning should be given or this member could be ignored?
      // The Main papplication window?
      __pointer(::user::primitive)                         m_puserprimitiveHost;
      //__pointer(::layered)     m_pimplLastSeed;
      //__pointer(::layered)                        m_puiMain2;

      // apex commented
      //__composite(::user::keyboard)                         m_pkeyboard;

      index                                                 m_iEdge;

      ::map < ::user::enum_key, bool > *                       m_pmapKeyPressed;

      bool                                                  m_bProgrammerMode;

      //bool                                                  m_bOnInitializeWindowObject;

      bool                                                  m_bSystemSynchronizedCursor;
      point_i32                                                 m_pointCursor;

      //comparable_array < __reference(::layered) > m_uiptraToolWindow;

      // apex commented
      //::user::interaction_impl *                            m_pimplPendingFocus2;
      //::layered *                                 m_puiLastUserInputPopup;
      //::draw2d::cursor *                                    m_pcursor;
      //::draw2d::cursor *                                    m_pcursorCursor;
      //enum_cursor                                              m_ecursorDefault;
      //enum_cursor                                              m_ecursor;

      // apex commented
      //::layered *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;

      //__pointer(::object)                                   m_pobjectCoreUser;

      // apex commented
      //__composite(::user::copydesk)                         m_pcopydesk;

      // apex commented
      //::layered *                                 m_puiMouseMoveCapture;
      //::layered *                                 m_puiLastLButtonDown;


      // apex commented
      //::write_text::font_enumeration_item_array                        m_fontenumitema;

      //index                                               m_iEdge;

      //__composite(::account::department)                    m_paccount;
      //__pointer(::account::licensing)                     m_plicensing;
      //__composite(::layered)                      m_puserinteractionSystem;

      ::payload                                                   m_varTopicFile;
      ::payload                                                   m_varCurrentViewFile;
      bool                                                  m_bShowPlatform;

      __composite(::text::context)                      m_ptextcontext;



      //index                                                 m_iMainMonitor;
      //index                                                 m_iMainWorkspace;


      // apex commented
      //id_map < ::layered * >                      m_mapboundui;



      //__composite(::userpresence::department)               m_puserpresence;


      __composite(::ftpfs)                                  m_pftpfs;
      __composite(::fs::remote_native)                      m_premotefs;
      __composite(::fs::fs)                                 m_pfs;
      __composite(::fs::data)                               m_pfsdata;
      __composite(::ifs)                                    m_pifs;
      //ke
      bool                                                  m_bIfs;

      bool                                                  m_bMatterFromHttpCache;

      ::u32                                                 m_dwLongPhRESSingTime;


      session();
      ~session() override;


      virtual void     initialize(::object * pobject) override;


      void install_message_routing(::channel* pchannel) override;


      //virtual void on_initialize_window_object();
      //virtual void _on_initialize_window_object();


      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      virtual bool is_session() const override;



      //virtual void enum_display_monitors();

      ////void construct(::object * pobject, int iPhase) override;

      //virtual index get_main_monitor(RECTANGLE_I32* prectangle = nullptr);

      //virtual ::count get_monitor_count();
      //virtual bool  get_monitor_rectangle(index iMonitor, RECTANGLE_I32* prectangle);

      //virtual ::count get_desk_monitor_count();
      //virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32* prectangle);


      //virtual index get_main_workspace(RECTANGLE_I32* prectangle = nullptr);

      //virtual ::count get_workspace_count();
      //virtual bool  get_workspace_rectangle(index iWorkspace, RECTANGLE_I32* prectangle);

      //virtual ::count get_desk_workspace_count();
      //virtual bool  get_desk_workspace_rect(index iWorkspace, RECTANGLE_I32* prectangle);

      //virtual index get_ui_workspace(::user::interaction * pinteraction);

      virtual void process_init();

      virtual void init1();

      virtual void init2();

      virtual void init_session();

      virtual void init();

      virtual void term();

      virtual void term_session();

      DECLARE_MESSAGE_HANDLER(on_message_erase_application);

      inline class ::fs::data * fs() { return m_pfsdata; }


      //inline ::sockets::sockets & sockets() { return *m_psockets; }


      //virtual size_i32 get_window_minimum_size();


      //virtual void  get_cursor_position(POINT_I32 * ppoint);

      virtual bool on_get_task_name(string& strThreadName) override;


      virtual void on_request(::create * pcreate) override;


      //virtual string matter_as_string(const ::string & pszMatter,const ::string & pszMatter2);
      //virtual string dir().matter(const ::string & pszMatter,const ::string & pszMatter2);

      //virtual bool is_inside_time_dir(const ::string & pszPath);
      //virtual bool file_is_read_only(const ::string & pszPath);

      // Long PhRESSing time
      // time in ::durations that a pressing is considered a double click
      virtual ::u32 get_Long_PhRESSing_time();

      //virtual void defer_initialize_user_presence();

      //virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual bool on_create_frame_window();

      //virtual string account_get_user_sessid(const ::string & str) override;

      // apex commented
      //virtual void translate_os_key_message(::user::key * pkey);

      //virtual void on_user_logon(::account::user * puser);

      virtual void pre_translate_message(::message::message * pmessage) override;

      //session();
      //virtual ~session();


      //virtual ::user::style * get_user_style() const;


      virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::string & strLocale, const ::string & strSchema) override;
      virtual string get_locale_schema_dir() override;


      //virtual void     initialize(::object * pobject) override;


      //virtual ::user::interaction * get_session_window();

      // apex commented
      ::text::context * text_context() { return m_ptextcontext.get(); }

      //virtual bool is_session() const override;

      virtual void init_thread() override;

      //virtual void process_init();

      //virtual void init1();

      //virtual void init2();

      //virtual void init_session();

      //virtual void init();

      //virtual void term();
      virtual void term2();

      virtual void term1();

      virtual void term_thread() override;

      //virtual void term_session();

      virtual void process_term();

      // apex commented
      //::user::keyboard& keyboard();

      virtual bool open_by_file_extension(const ::string & pszPathName, ::create * pcreate = nullptr);

      virtual bool open_by_file_extension(::create * pcc);

      virtual ::color::color get_default_color(u64 u);

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant) override;

      virtual void frame_pre_translate_message(::message::message * pmessage);

      virtual bool is_licensed(const ::string & pszId, bool bInteractive = true);

      virtual bool get_auth(const string & pszForm, string & strUsername, string & strPassword);

      virtual void on_instantiate_application(::application* papp) override;

      //::application * application_get(const ::string & pszAppId, bool bCreate, bool bSynch, ::create * pcreate) override;

      virtual bool is_key_pressed(::user::enum_key ekey);

      virtual void set_key_pressed(::user::enum_key ekey, bool bPressed);


      // apex commented
      //virtual void get_cursor_position(POINT_I32 * ppoint);
      //inline ::point_i32 get_cursor_position() {::point_i32 point; get_cursor_position(&point); return point;}

      // apex commented
      //virtual void set_cursor_pos(const ::point_i32 & point);

      //virtual index get_main_monitor(RECTANGLE_I32 * prectangle = nullptr);

      // virtual bool set_main_monitor(index iMonitor);
      // //virtual ::count get_monitor_count();
      // //virtual bool  get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle);

      // //virtual index get_main_workspace(RECTANGLE_I32 * prectangle = nullptr);

      // virtual bool set_main_workspace(index iWorkspace);
      // //virtual ::count get_workspace_count();
      // //virtual bool  get_workspace_rectangle(index iWorkspace, RECTANGLE_I32 * prectangle);

      // virtual bool workspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWorkspace);

      // virtual bool monitor_to_workspace(RECTANGLE_I32 * prectangle, index iWorkspace, index iMonitor);

      // virtual bool workspace_to_monitor(RECTANGLE_I32 * prectangle);

      // virtual bool monitor_to_workspace(RECTANGLE_I32 * prectangle);

      // //virtual ::count get_desk_monitor_count();
      // //virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle);

      // virtual void  get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const ::rectangle_i32 & rectangle);

      // // apex commented
      // //virtual index initial_frame_position(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, bool bMove, ::user::interaction * pinteraction);

      // virtual index _get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bPreserveSize = false);

      // virtual index get_best_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default);

      // virtual index get_best_workspace(::rectangle_i32 * prectangle, const ::rectangle_i32& rectangle, ::e_activation eactivation = e_activation_default);

      // virtual index get_good_iconify(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle);

      // apex commented
      //virtual index get_window_restore_1(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual index get_window_restore_2(RECTANGLE_I32* prectangle, const ::rectangle_i32& rectangle, ::user::interaction* pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual index get_good_move(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction);

      // apex commented
      //virtual index get_ui_workspace(::user::interaction * pinteraction);


      //virtual void defer_instantiate_user_theme(const ::string & pszUiInteractionLibrary = nullptr);
      //__pointer(::user::theme) instantiate_user_theme(const ::string & pszExperienceLibrary, ::application * papp = nullptr);
      //__pointer(::user::theme) get_user_theme(const ::string & pszExperienceLibrary, ::application * papp = nullptr);


      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rectangle_i32 & rectangle, ::draw2d::brush_pointer & pbrushText);


      // apex commented
      //virtual void set_bound_ui(::id idView, ::user::interaction * pinteraction);
      //virtual ::user::interaction * get_bound_ui(::id idView);

      // apex commented
      //virtual void on_show_user_input_popup(::user::interaction * pinteraction);

      //virtual void on_user_logon(::account::user * puser);



      //virtual void initialize(::object * pobject) override;

      //virtual void install_message_routing(::channel* pchannel) override;

      //virtual void userex_process_init();
      //virtual void userex_init1();
      //virtual void init2() override;
      //virtual bool init3() override;
      //virtual bool initialize_filemanager();
      ///virtual void init_session() override;
      //virtual void add_document_template(::user::impact_system * ptemplate);

      //virtual void term_session() override;
      //virtual void term3() override;
      //virtual bool finalize_filemanager();

      virtual void destroy() override;

      //template < typename VIEW >
      //__pointer(::user::document)   create_form(__pointer(::user::interaction) puserinteractionParent = nullptr, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(::type point, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(::user::form_callback* pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(::user::form_callback* pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument), ::payload varArgs = payload(::e_type_empty_argument));
      //template < typename VIEW >
      //__pointer(::user::document)   create_child_form(__pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(::type point, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument));
      //__pointer(::user::document)   create_child_form(__pointer(::user::form) pview, ::user::form_callback* pcallback, __pointer(::user::interaction) puserinteractionParent, ::payload payload = payload(::e_type_empty_argument));


      //virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle,::user::menu_item* pitem) override;




      virtual bool InitializeLocalDataCentral();

      //virtual void bergedge_start() override;

      void _001OnFileNew();

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      //virtual ::user::document* userex_on_request(::create* pcreate);

      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);

      //void load_string_table() override;

//      virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;

      //void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::create * pcreate);

      //virtual void will_use_view_hint(::id idView);

      //virtual void on_app_request_bergedge_callback(::object * pobject);

      // apex commented
      //virtual ::write_text::font_list* get_single_column_font_list();

      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::patha& patha);


      virtual void do_request(::create* pcreate) override;

      // apex commented
      //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);

      // apex commented
      //virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);

      //virtual void request_topic_file(::payload& varQuery);

      //virtual void request_topic_file();

      //virtual void check_topic_file_change();


      virtual void launch_app(const ::string & psz);
      virtual void install_app(const ::string & psz);



      //user __pointer(::user::document)                   get_document();
      //user __pointer(::user::impact)                     get_view();
      //user __pointer(::user::document)                   get_platform();
      //user __pointer(::user::document)                   get_nature();


      //inline ::userex::userex* userex() { return m_puserex; }


      //virtual void process_init() override;

      //virtual void init1() override;

      //virtual void init() override;

      //virtual void os_native_bergedge_start() override;

      virtual void main() override;

      virtual void defer_initialize_host_window(const RECTANGLE_I32 * lpcrect = nullptr);

      __pointer(::application) get_current_application();

      virtual void set_app_title(const ::string & pszAppId, const ::string & pszTitle);

      virtual __pointer(::apex::session) get_session();

      virtual bool is_remote_session();

      virtual string_array get_user_wallpaper();

      virtual ::user::primitive * get_user_interaction_host();
      virtual ::user::primitive * get_host_primitive();


   };


} // namespace apex



