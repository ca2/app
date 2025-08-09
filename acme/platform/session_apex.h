//
// Created by camilo on 2024-10-24 22:12 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace platform
{


   struct CLASS_DECL_ACME apex_session_layer_t
   {

      ///__creatable(session);




//#if defined UNIVERSAL_WINDOWS
//
//      ::universal_windows::directx_framework_impact ^                          m_frameworkview;
//
//#endif




      //::aqua::session* m_paquasession;
      //::aura::session* m_paurasession;
      //::axis::session* m_paxissession;
      //::berg::session* m_pbasesession;
      //::bred::session* m_pbredsession;
      //::core::session* m_pcoresession;

      // For Mobile systems it is particularly meaningful...
      // ... is is the "Main Window" (sometimes just a concept) holding the App.
      // For Desktop Applications a meaning should be given or this member could be ignored?
      // The Main papp window?
      ::pointer<::user::interaction_base>                        m_puserprimitiveHost;
      //::pointer<::layered>    m_pimplLastSeed;
      //::pointer<::layered>                       m_puiMain2;

      // apex commented
      //::pointer<::user::keyboard>                        m_pkeyboard;

      ::pointer < ::map < ::user::enum_key, bool > >        m_pmapKeyPressed;

      bool                                                  m_bProgrammerMode;

      //bool                                                  m_bOnInitializeWindowObject;

      bool                                                  m_bSystemSynchronizedCursor;
      int_point                                                 m_pointCursor;

      //comparable_array < ::pointer<::layered >>m_uiptraToolWindow;

      // apex commented
      //::windowing::window *                            m_pimplPendingFocus2;
      //::layered *                                 m_puiLastUserInputPopup;
      //::image::cursor *                                    m_pcursor;
      //::image::cursor *                                    m_pcursorCursor;
      //enum_cursor                                              m_ecursorDefault;
      //enum_cursor                                              m_ecursor;

      // apex commented
      //::layered *                                 m_puiCapture;
      //bool                                                  m_bDrawCursor;

      //::pointer<::object>                                  m_pobjectCoreUser;

      // apex commented
      //::pointer<::user::copydesk>                        m_pcopydesk;

      // apex commented
      //::layered *                                 m_puiMouseMoveCapture;
      //::layered *                                 m_puiLastLButtonDown;


      // apex commented
      //::write_text::font_enumeration_item_array                        m_fontenumitema;

      //index                                               m_iEdge;

      //::pointer<::account::department>                   m_paccount;
      //::pointer<::account::licensing>                    m_plicensing;
      //::pointer<::layered>                     m_puserinteractionSystem;

      ::payload                                                   m_varTopicFile;
      bool                                                  m_bShowPlatform;


      //index                                                 m_iMainMonitor;
      //index                                                 m_iMainWorkspace;


      // apex commented
      //atom_map < ::layered * >                      m_mapboundui;



      //::pointer<::userpresence::department>              m_puserpresence;


      ::pointer<::ftpfs>                                 m_pftpfs;
      ::pointer<::fs::remote_native>                     m_premotefs;
      ::pointer<::fs::fs>                                m_pfs;
      ::pointer<::fs::data>                              m_pfsdata;
      ::pointer<::ifs>                                   m_pifs;
      //ke
      bool                                                  m_bIfs;

      bool                                                  m_bMatterFromHttpCache;

      unsigned int                                                 m_dwLongPhRESSingTime;


   };


   class CLASS_DECL_ACME apex_session_layer
   {
   public:

      //void initialize(::particle * pparticle) override;


      //void install_message_routing(::channel* pchannel) override;


      //virtual void on_initialize_window_object();
      //virtual void _on_initialize_window_object();


      //inline ::userpresence::department & userpresence() { return *m_puserpresence; }

      //virtual bool is_session() const override;

      //void main() override;

      //virtual void enum_display_monitors();

      ////void construct(::particle * pparticle, int iPhase) override;

      //virtual ::collection::index get_main_monitor(::int_rectangle* prectangle = nullptr);

      //virtual ::collection::count get_monitor_count();
      //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle* prectangle);

      //virtual ::collection::count get_desk_monitor_count();
      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle* prectangle);


      //virtual ::collection::index get_main_workspace(::int_rectangle* prectangle = nullptr);

      //virtual ::collection::count get_workspace_count();
      //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle* prectangle);

      //virtual ::collection::count get_desk_workspace_count();
      //virtual bool  get_desk_workspace_rect(::collection::index iWorkspace, ::int_rectangle* prectangle);

      //virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction);

      // virtual void process_init() override;
      //
      // void init1() override;
      //
      // void init2() override;
      //
      // void init_session() override;
      //
      // void init() override;
      //
      // void term() override;
      //
      // void term_session() override;

      //DECLARE_MESSAGE_HANDLER(on_message_erase_application);

      virtual class ::fs::data * fs();


      //inline ::sockets::sockets & sockets() { return *m_psockets; }


      //virtual int_size get_window_minimum_size();


      //virtual void  get_cursor_position(::int_point * ppoint);

      //virtual bool on_get_task_name(string& strThreadName) override;


      //void request(::request * prequest) override;


      //virtual string matter_as_string(const ::scoped_string & scopedstrMatter,const ::scoped_string & scopedstrMatter2);
      //virtual string directory()->matter(const ::scoped_string & scopedstrMatter,const ::scoped_string & scopedstrMatter2);

      //virtual bool is_inside_time_dir(const ::scoped_string & scopedstrPath);
      //virtual bool file_is_read_only(const ::scoped_string & scopedstrPath);

      // Long PhRESSing time
      // time in ::times that a pressing is considered a double click
      virtual unsigned int get_Long_PhRESSing_time();

      //virtual void defer_initialize_user_presence();

      //virtual void     interactive_credentials(::account::credentials * pcredentials) override;

      //virtual bool on_create_frame_window();

      //virtual string account_get_user_sessid(const ::scoped_string & scopedstr) override;

      // apex commented
      //virtual void translate_os_key_message(::user::key * pkey);

      //virtual void on_user_logon(::account::user * puser);

      //virtual void pre_translate_message(::message::message * pmessage) override;

      //session();
      //virtual ~session();


      //virtual ::user::style * get_user_style() const;


      //virtual void locale_schema_matter(string_array & stra, const string_array & straMatterLocator, const ::scoped_string & scopedstrLocale, const ::scoped_string & scopedstrSchema) override;
      //virtual string get_locale_schema_dir() override;


      //virtual void     initialize(::particle * pparticle) override;


      //virtual ::user::interaction * get_session_window();

      // apex commented

      //virtual bool is_session() const override;

      //virtual void init_task() override;

      //virtual void process_init();

      //virtual void init1();

      //virtual void init2();

      //virtual void init_session();

      //virtual void init();

      // //virtual void term();
      // void term2() override;
      //
      // void term1() override;
      //
      // void term_task() override;
      //
      // //virtual void term_session();
      //
      // void process_term() override;

      // apex commented
      //::user::keyboard& keyboard();

      virtual bool open_by_file_extension(const ::scoped_string & scopedstrPathName, ::request * prequest = nullptr);

      virtual bool open_by_file_extension(::request * prequest);

      virtual ::color::color get_default_color(::color::color color);

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant) override;

      virtual void frame_pre_translate_message(::message::message * pmessage);

      virtual bool is_licensed(const ::scoped_string & scopedstrId, bool bInteractive = true);

      virtual bool get_auth(const ::scoped_string & scopedstrForm, string & strUsername, string & strPassword);

      //void on_instantiate_application(::platform::application* papp) override;

      //::application * application_get(const ::scoped_string & scopedstrAppId, bool bCreate, bool bSynch, ::request * prequest) override;

      virtual ::user::e_key key_modifiers();

      //bool is_key_pressed(::user::enum_key ekey) override;

      virtual void set_key_pressed(::user::enum_key ekey, bool bPressed);


      // apex commented
      //virtual void get_cursor_position(::int_point * ppoint);
      //inline ::int_point get_cursor_position() {::int_point point; get_cursor_position(&point); return point;}

      // apex commented
      //virtual void set_cursor_pos(const ::int_point & point);

      //virtual ::collection::index get_main_monitor(::int_rectangle * prectangle = nullptr);

      // virtual bool set_main_monitor(::collection::index iMonitor);
      // //virtual ::collection::count get_monitor_count();
      // //virtual bool  get_monitor_rectangle(::collection::index iMonitor, ::int_rectangle * prectangle);

      // //virtual ::collection::index get_main_workspace(::int_rectangle * prectangle = nullptr);

      // virtual bool set_main_workspace(::collection::index iWorkspace);
      // //virtual ::collection::count get_workspace_count();
      // //virtual bool  get_workspace_rectangle(::collection::index iWorkspace, ::int_rectangle * prectangle);

      // virtual bool workspace_to_monitor(::int_rectangle * prectangle, ::collection::index iMonitor, ::collection::index iWorkspace);

      // virtual bool monitor_to_workspace(::int_rectangle * prectangle, ::collection::index iWorkspace, ::collection::index iMonitor);

      // virtual bool workspace_to_monitor(::int_rectangle * prectangle);

      // virtual bool monitor_to_workspace(::int_rectangle * prectangle);

      // //virtual ::collection::count get_desk_monitor_count();
      // //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::int_rectangle * prectangle);

      // virtual void  get_monitor(int_rectangle_array & rectaMonitor, int_rectangle_array & rectaIntersect, const ::int_rectangle & rectangle);

      // // apex commented
      // //virtual ::collection::index initial_frame_position(::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bMove, ::user::interaction * pinteraction);

      // virtual ::collection::index _get_best_zoneing(edisplay * pedisplay, ::int_rectangle * prectangle, const ::int_rectangle & rectangle, bool bPreserveSize = false);

      // virtual ::collection::index get_best_monitor(::int_rectangle * prectangle, const ::int_rectangle & rectangle, const ::user::activation & useractivation = {});

      // virtual ::collection::index get_best_workspace(::int_rectangle * prectangle, const ::int_rectangle& rectangle, const ::user::activation & useractivation = {});

      // virtual ::collection::index get_good_iconify(::int_rectangle * prectangle, const ::int_rectangle & rectangle);

      // apex commented
      //virtual ::collection::index get_window_restore_1(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual ::collection::index get_window_restore_2(::int_rectangle* prectangle, const ::int_rectangle& rectangle, ::user::interaction* pinteraction, edisplay edisplayRestore);

      // apex commented
      //virtual ::collection::index get_good_move(::int_rectangle * prectangle, const ::int_rectangle & rectangle, ::user::interaction * pinteraction);

      // apex commented
      //virtual ::collection::index get_ui_workspace(::user::interaction * pinteraction);


      //virtual void defer_instantiate_user_theme(const ::scoped_string & scopedstrUiInteractionLibrary = nullptr);
      //::pointer<::user::theme>instantiate_user_theme(const ::scoped_string & scopedstrExperienceLibrary, ::apex::application * papp = nullptr);
      //::pointer<::user::theme>get_user_theme(const ::scoped_string & scopedstrExperienceLibrary, ::apex::application * papp = nullptr);


      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::int_rectangle & rectangle, ::draw2d::brush_pointer & pbrushText);


      // apex commented
      //virtual void set_bound_ui(::atom idImpact, ::user::interaction * pinteraction);
      //virtual ::user::interaction * get_bound_ui(::atom idImpact);

      // apex commented
      //virtual void on_show_user_input_popup(::user::interaction * pinteraction);

      //virtual void on_user_logon(::account::user * puser);



      //virtual void initialize(::particle * pparticle) override;

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

      //virtual void destroy() override;




      virtual bool InitializeLocalDataCentral();

      //virtual void bergedge_start() override;

      virtual void _001OnFileNew();

      //void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;

      //virtual ::user::document* userex_on_request(::create* pcreate);

      //void OnFileManagerOpenFile(::filemanager::data* pdata, ::file::item_array& itema);

      //void load_string_table() override;

//      virtual bool open_file(::filemanager::data* pdata, ::file::item_array& itema) override;

      //void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::request * prequest);

      //virtual void will_use_impact_hint(::atom idImpact);

      //virtual void on_app_request_bergedge_callback(::particle * pparticle);

      // apex commented
      //virtual ::write_text::font_list* get_single_column_font_list();

      //virtual void on_frame_window_drop_files(::user::interaction* pinteraction, ::file::path_array_base& patha);


      //void request(::request * prequest) override;

      // apex commented
      //virtual ::user::interaction* get_request_parent_ui(::user::interaction* pinteraction, ::create* pcreate);

      // apex commented
      //virtual bool place(::user::main_frame* pmainframe, ::create* pcreate);

      //virtual void request_topic_file(::payload& varQuery);

      //virtual void request_topic_file();

      //virtual void check_topic_file_change();


      virtual void launch_app(const ::scoped_string & scopedstr);
      virtual void install_app(const ::scoped_string & scopedstr);



      //user ::pointer<::user::document>                  get_document();
      //user ::pointer<::user::impact>                    get_impact();
      //user ::pointer<::user::document>                  get_platform();
      //user ::pointer<::user::document>                  get_nature();


      //inline ::userex::userex* userex() { return m_puserex; }


      //virtual void process_init() override;

      //virtual void init1() override;

      //virtual void init() override;

      //virtual void os_native_bergedge_start() override;

      //virtual void on_request(::request * prequest) override;

      virtual void defer_initialize_host_window(const ::int_rectangle * lpcrect = nullptr);

      ::pointer<::apex::application>get_current_application();

      virtual void set_app_title(const ::scoped_string & scopedstrAppId, const ::scoped_string & scopedstrTitle);

      virtual ::pointer<::apex::session>get_session();

      virtual bool is_remote_session();

      virtual string_array get_user_wallpaper();

      virtual ::user::interaction_base * get_user_interaction_host();
      virtual ::user::interaction_base * get_host_primitive();


   };


} // namespace platform





