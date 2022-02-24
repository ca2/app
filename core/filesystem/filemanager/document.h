#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE document :
      virtual public ::file::listener,
      virtual public ::userfs::document,
      virtual public ::filemanager::callback,
      virtual public ::filemanager::file_list_callback
   {
   public:

            ::file::watch_id                    m_filewatchid;
      __pointer(::filemanager::data)             m_pfilemanagerdata;
      __pointer(::file::item)                      m_pitem;
      ::file::path                        m_strTopic;
      bool                                m_bFullBrowse;
      string                              m_strManagerId;
      ::userfs::e_mode                    m_emode;
      bool                                m_bInitialized;



      document();
      ~document() override;


      inline ::core::application* get_app() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }

      
      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;


      virtual ::fs::data *                         fs_data();
      virtual ::file::item *                         filemanager_item();
      virtual ::filemanager::data *                filemanager_data();

      virtual document * get_main_document();

      DECLARE_MESSAGE_HANDLER(_001OnLevelUp);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateLevelUp);
      DECLARE_MESSAGE_HANDLER(_001OnAddLocation);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateAddLocation);
      DECLARE_MESSAGE_HANDLER(_001OnReplaceText);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateReplaceText);
      DECLARE_MESSAGE_HANDLER(_001OnEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditPaste);
      DECLARE_MESSAGE_HANDLER(_001OnFileSaveAs);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileSaveAs);
      DECLARE_MESSAGE_HANDLER(_001OnFileImport);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileImport);
      DECLARE_MESSAGE_HANDLER(_001OnFileExport);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileExport);
      DECLARE_MESSAGE_HANDLER(_001OnNewManager);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateNewManager);
      DECLARE_MESSAGE_HANDLER(_001OnDelManager);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateDelManager);
      DECLARE_MESSAGE_HANDLER(_001OnNewFolder);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateNewFolder);

      virtual void defer_check_manager_id(string strNewManagerId = "");
      virtual void on_request(::create * pcreate) override;

      virtual bool do_prompt_file_name(::payload & payloadFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      __pointer(::filemanager::data) create_file_manager_data(::create * pcreate = nullptr);

      //virtual void Initialize(i32 iTemplate, const ::string & pszMatter);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);


      virtual void InitializeFileManager(const ::string & pszMatter);


      string get_initial_browse_path(const ::string & pszDefault = nullptr);


      virtual void browse(const ::string & pcsz, const ::action_context & action_context);

      virtual bool browse(__pointer(::file::item) item, const ::action_context & action_context) override;

      virtual void on_file_manager_open_context_menu_folder(__pointer(::file::item)  item, string_array & straCommand, string_array & straCommandTitle, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu(const ::action_context & action_context);
      virtual void on_file_manager_open(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_folder(__pointer(::file::item)  str, const ::action_context & action_context);

      virtual void on_file_manager_item_update(::message::command * pcommand, const ::file::item_array & itema);
      virtual void on_file_manager_item_command(const ::string & pszId, const ::file::item_array & itema);

      //critical_section * GetItemIdListCriticalSection();

      //virtual bool FileManagerBrowse(::file::item * pitem, const ::action_context & action_context);
      //virtual bool FileManagerBrowse(const ::string & pcsz, const ::action_context & action_context);


      virtual void FileManagerOneLevelUp(const ::action_context & action_context);
      virtual void OnFileManagerBrowse(const ::action_context & action_context);
      virtual void OpenSelectionProperties();

      virtual void GetActiveImpactSelection(::file::item_array & itema);


      virtual void FileManagerSaveAs(::user::document * pdocument);
      virtual void FileManagerImport(::user::document * pdocument);
      virtual void FileManagerExport(::user::document * pdocument);
      virtual void FileManagerTopicOK();
      virtual void FileManagerTopicCancel();



      virtual void handle_file_action(::file::action * paction) override;


      virtual void on_create(::create * pcreate) override;


      operation_document * get_operation_doc(bool bSwitch);


      virtual void on_command(::message::command * pcommand) override;
      virtual void on_command_probe(::message::command * pcommand) override;

      bool on_new_document() override;
      virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual bool HandleDefaultFileManagerItemCmdMsg(::message::command * pcommand,::file::item_array & itema);

      void PopImpacts();
      void CreateImpacts();
      void OpenFolder(::file::item * item, const ::action_context & action_context);
      void filemanager_initialize(bool bMakeVisible, bool bInitialBrowsePath = true);
      void filemanager_initialize(bool bMakeVisible, const ::file::path & path);


      bool set_filemanager_data(::filemanager::data * pdata);


      //virtual ::user::toolbar * get_toolbar(::user::frame * pframe, bool bCreate) override;


      ::atom get_toolbar_id() override;


      virtual void start_full_browse(__pointer(::file::item) pitem, const ::action_context & action_context);
      virtual void full_browse(__pointer(::file::item) pitem, const ::action_context & action_context);


   };


   CLASS_DECL_CORE int get_manager_id_byte_len();

   CLASS_DECL_CORE int get_manager_id_len();

   CLASS_DECL_CORE string create_manager_id(::object * pobject);

   CLASS_DECL_CORE bool is_valid_manager_id(const ::string &);

   CLASS_DECL_CORE bool is_valid_filemanager_project_entry(const ::string &);

   CLASS_DECL_CORE ::file::path filemanager_project_entry(string & strManagerId, const ::string & psz, ::aura::context * pcontext);


} // namespace filemanager




