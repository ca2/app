#pragma once


namespace sphere
{


   class CLASS_DECL_SPHERE application :
      virtual public ::aura::application
   {
   public:


      ::pointer<::console::department>                   m_pconsole;
      ::pointer<::prompt::department>                    m_pprompt;
      ::pointer<::filehandler::department>               m_pfilehandler;
      ::pointer<::calculator::department>                m_pcalculator;


      colorertake5::ParserFactory *                m_pparserfactory;

      index                                        m_iEdge;

      bool                                         m_bShowPlatform;

      ::pointer<::aura::application>                     m_pappCurrent;
      
      ::pointer<::user::single_document_template>        m_ptemplate_main;
      ::pointer<::user::single_document_template>        m_ptemplate_pane;

      ::userstack::pane_impact *                     m_ppaneimpact;


      ::payload                                          m_varTopicFile;
      ::payload                                          m_varCurrentImpactFile;

      bool                                         m_bDrawCursor;

      string_map < ::pointer<::experience::experience >> m_mapExperience;


      application(::particle * pparticle);
      ~application() override;

      virtual void init_instance() override;
      virtual void term_instance() override;

      virtual void _001OnFileNew();
      virtual bool bergedge_start() override;


      virtual bool is_serviceable() const override;
      virtual service_base * allocate_new_service() override;


      virtual bool on_install() override;
      virtual bool on_uninstall() override;

      virtual void     run() override;

      virtual void on_request(::create * pcreate) override;

      ::user::document * _001OpenDocumentFile(::payload payloadFile) override;


      virtual ::console::department * console();
      virtual ::prompt::department * prompt();
      virtual ::filehandler::department * filehandler();
      virtual ::calculator::department * calculator();

      ::pointer<::aura::application>get_context_system();

//      virtual void init_instance() override;
      virtual bool init1() override;
      virtual bool init() override;



      //virtual void _001OnTheme(::message::message * pmessage);

      virtual u32 guess_code_page(const ::string & str) override;

      ::colorertake5::ParserFactory                &  parser_factory();

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;


      void construct();


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);

      void load_string_table() override;

      virtual bool file_manager_open_file(::filemanager::data * pdata, ::file::item_array & itema);

      void initialize_bergedge_application_interface();

      virtual void request_topic_file(::payload & varQuery);

      virtual void request_topic_file();

      virtual void check_topic_file_change();

      virtual bool on_exclusive_instance_conflict(bool & bHandled, EExclusiveInstance eexclusive, string strId) override;

      void launch_app(const ::string & psz);
      void install_app(const ::string & psz);

//      virtual bool init1() override;

//      virtual bool init() override;

      virtual bool os_native_bergedge_start() override;

      virtual void     main() override;

//      virtual bool on_uninstall() override;

//      virtual bool is_serviceable() override;

      //virtual service_base * allocate_new_service() override;

      //void on_request(::create * pcreate) override;

      ::pointer<::aura::application>application_get(const ::string & pszAppId, bool bCreate = true, bool bSynch = true, application_bias * pappbias = nullptr);

      ::pointer<::aura::application>get_current_application();

//      virtual bool on_install() override;

      virtual void set_app_title(const ::string & pszType, const ::string & pszAppId, const ::string & pszTitle);


      virtual void pre_translate_message(::message::message * pmessage) override;
   };


} // namespace sphere



