#pragma once


namespace aura
{


   class view;

//   class session_docs;


   class CLASS_DECL_AURA session :
      virtual public ::aura::session,
      virtual public ::filemanager::item_action,
      virtual public ::filemanager::component,
      virtual public ::document_manager_container
   {
   public:


      class run_application
      {
      public:


         index                               m_iEdge;
         string                              m_strApp;
         string                              m_strQuery;
         __pointer(::aura::session)          m_pbergedgeParent;
         __pointer(::aura::application)      m_papp;
         bool                                m_bMakeVisible;
         __pointer(::user::interaction)      m_puserinteractionParent;
         property_set                        m_setParameters;

         run_application();


      };


      __composite(::userex::userex)                            m_puserex;
      bool                                                     m_bFontSelInitialized;
      __pointer(::draw2d::font_list)                           m_pfontlistSingleColumn;
      __pointer(::user::user)                                  m_puser;


      session();
      virtual ~session();


      virtual ::estatus initialize(::layered * pobjectContext) override;

      virtual void install_message_routing(::channel * pchannel) override;

      //virtual ::estatus userex_process_init();
      //virtual ::estatus userex_init1();
      virtual ::estatus init2() override;
      //virtual bool init3() override;
      //virtual bool initialize_filemanager();
      virtual ::estatus init_session() override;
      //virtual void add_document_template(::user::impact_system * ptemplate);

      virtual void term_session() override;
      //virtual void term3() override;
      //virtual bool finalize_filemanager();

      template < typename VIEW >
      __pointer(::user::document)   create_form(__pointer(::user::interaction) pwndParent = nullptr, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_form(::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_form(::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_form(__pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_child_form(::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, ::payload payload = ::payload(::type_empty_argument), ::payload varArgs = ::payload(::type_empty_argument));
      template < typename VIEW >
      __pointer(::user::document)   create_child_form(__pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_child_form(::type point, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));
      __pointer(::user::document)   create_child_form(__pointer(::user::form) pview, ::user::form_callback * pcallback, __pointer(::user::interaction) pwndParent, payload payload = ::payload(::type_empty_argument));


      virtual __pointer(::user::menu_interaction) create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;




      bool InitializeLocalDataCentral();

      //virtual ::estatus bergedge_start() override;

      void _001OnFileNew();

      //virtual void route_command_message(::user::command * pcommand) override;

      virtual ::user::document * userex_on_request(::create * pcreate);

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);

      //void load_string_table() override;

      virtual bool open_file(::filemanager::data * pdata, ::file::item_array & itema) override;

      void initialize_bergedge_application_interface();

      //virtual bool create_bergedge(::create * pcreate);

      virtual void will_use_view_hint(::id idView);

      //virtual void on_app_request_bergedge_callback(::layered * pobjectContext);

      virtual ::draw2d::font_list * get_single_column_font_list();

      virtual void on_frame_window_drop_files(::user::interaction * pinteraction, ::file::patha & patha);


      virtual ::estatus do_request(::create * pcreate) override;

      virtual ::user::interaction * get_request_parent_ui(::user::interaction * pinteraction, ::create * pcreate);

      virtual bool place(::user::main_frame * pmainframe, ::create * pcreate);

      virtual void request_topic_file(payload & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();


      void launch_app(const char * psz);
      void install_app(const char * psz);



      __pointer(::user::document)                   get_document();
      __pointer(::user::impact)                     get_view();
      __pointer(::user::document)                   get_platform();
      __pointer(::user::document)                   get_nature();


      inline ::userex::userex *              userex() { return m_puserex;  }


      virtual ::estatus process_init() override;

      virtual ::estatus init1() override;

      virtual ::estatus init() override;

      //virtual ::estatus os_native_bergedge_start() override;

      virtual ::estatus     main() override;

 

      //virtual service_base * allocate_new_service() override;

      void on_request(::create * pcreate) override;

      __pointer(::aura::application) get_current_application();

   

      virtual void set_app_title(const char * pszAppId, const char * pszTitle);

      virtual __pointer(::aura::session) get_context_session();

      virtual void term() override;

      virtual bool open_by_file_extension(const char * pszPathName, ::create * pcreate = nullptr) override;
      virtual bool open_by_file_extension(::create * pcc) override;

      virtual bool is_session() const override;

      virtual bool is_mouse_button_pressed(::user::enum_mouse emouse);

      virtual bool is_remote_session();

      //virtual ::draw2d::cursor * get_cursor() override;
      virtual ::draw2d::cursor * get_default_cursor() override;

      virtual ::count   get_monitor_count() override;
      virtual bool      get_monitor_rect(index iMonitor,RECT32 * prect) override;


      virtual void on_user_logon(::account::user * puser) override;


      virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane & pane, ::user::tab * ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect & rect, ::draw2d::brush_pointer & brushText) override;


      virtual string_array get_user_wallpaper();



      virtual void interactive_credentials(::account::credentials * pcredentials) override;



      //session();
      //virtual ~session();

      inline ::user::user* user() { return m_puser; }

      //virtual __pointer(::user::impact)                      get_view();


      //virtual ::estatus     initialize(::layered * pobjectContext) override;


      virtual void frame_pre_translate_message(::message::message* pmessage) override;

      //virtual ::estatus process_init() override;

      //virtual ::estatus init1() override;

      //virtual ::estatus init() override;

      //virtual void term_session() override;

      //virtual void interactive_credentials(::account::credentials* pcredentials) override;

      virtual void on_finally_focus_set(::user::primitive* pelementalFocus) override;

      //virtual ::user::menu_interaction * create_menu_button(::user::style_pointer & pstyle, ::user::menu_item * pitem) override;

      //virtual oswindow get_capture() override;


      //virtual void _001OnDefaultTabPaneDrawTitle(::user::tab_pane& pane, ::user::tab* ptab, ::draw2d::graphics_pointer & pgraphics, const ::rect& rect, ::draw2d::brush_pointer& brushText) override;


      virtual bool prepare_menu_button(::user::menu_item* pitem) override;

      virtual bool on_ui_mouse_message(::message::mouse* pmouse) override;

   };


} // namespace aura



