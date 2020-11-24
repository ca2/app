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
      virtual ~document();

      //virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      //{
      //   return ::object::add_ref(OBJ_REF_DBG_ARGS);
      //}

      //virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      //{
      //   return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      //}

      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual ::fs::data *                         fs_data();
      virtual ::file::item *                         filemanager_item();
      virtual ::filemanager::data *                filemanager_data();

      virtual document * get_main_document();

      DECL_GEN_SIGNAL(_001OnLevelUp);
      DECL_GEN_SIGNAL(_001OnUpdateLevelUp);
      DECL_GEN_SIGNAL(_001OnAddLocation);
      DECL_GEN_SIGNAL(_001OnUpdateAddLocation);
      DECL_GEN_SIGNAL(_001OnReplaceText);
      DECL_GEN_SIGNAL(_001OnUpdateReplaceText);
      DECL_GEN_SIGNAL(_001OnEditPaste);
      DECL_GEN_SIGNAL(_001OnUpdateEditPaste);
      DECL_GEN_SIGNAL(_001OnFileSaveAs);
      DECL_GEN_SIGNAL(_001OnUpdateFileSaveAs);
      DECL_GEN_SIGNAL(_001OnFileImport);
      DECL_GEN_SIGNAL(_001OnUpdateFileImport);
      DECL_GEN_SIGNAL(_001OnFileExport);
      DECL_GEN_SIGNAL(_001OnUpdateFileExport);
      DECL_GEN_SIGNAL(_001OnNewManager);
      DECL_GEN_SIGNAL(_001OnUpdateNewManager);
      DECL_GEN_SIGNAL(_001OnDelManager);
      DECL_GEN_SIGNAL(_001OnUpdateDelManager);
      DECL_GEN_SIGNAL(_001OnNewFolder);
      DECL_GEN_SIGNAL(_001OnUpdateNewFolder);

      virtual void defer_check_manager_id(string strNewManagerId = "");
      virtual void on_request(::create * pcreate) override;

      virtual bool do_prompt_file_name(payload & varFile, string strTitle, u32 lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      __pointer(::filemanager::data) create_file_manager_data(::create * pcreate = nullptr);

      //virtual void Initialize(i32 iTemplate, const char * pszMatter);


      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);


      virtual void InitializeFileManager(const char * pszMatter);


      string get_initial_browse_path(const char * pszDefault = nullptr);


      virtual void browse(const char * pcsz, const ::action_context & action_context);

      virtual bool browse(__pointer(::file::item) item, const ::action_context & action_context) override;

      virtual void on_file_manager_open_context_menu_folder(__pointer(::file::item)  item, string_array & straCommand, string_array & straCommandTitle, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu(const ::action_context & action_context);
      virtual void on_file_manager_open(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_folder(__pointer(::file::item)  str, const ::action_context & action_context);

      virtual void on_file_manager_item_update(::user::command * pcommand, const ::file::item_array & itema);
      virtual void on_file_manager_item_command(const char * pszId, const ::file::item_array & itema);

      //::critical_section * GetItemIdListCriticalSection();

      //virtual bool FileManagerBrowse(::file::item * pitem, const ::action_context & action_context);
      //virtual bool FileManagerBrowse(const char * pcsz, const ::action_context & action_context);


      virtual void FileManagerOneLevelUp(const ::action_context & action_context);
      virtual void OnFileManagerBrowse(const ::action_context & action_context);
      virtual void OpenSelectionProperties();

      virtual void GetActiveViewSelection(::file::item_array & itema);


      virtual void FileManagerSaveAs(::user::document * pdocument);
      virtual void FileManagerImport(::user::document * pdocument);
      virtual void FileManagerExport(::user::document * pdocument);
      virtual void FileManagerTopicOK();
      virtual void FileManagerTopicCancel();



      virtual void handle_file_action(::file::action * paction) override;


      virtual void on_create(::create * pcreate) override;


      operation_document * get_operation_doc(bool bSwitch);


      virtual void on_command(::user::command * pcommand) override;
      virtual void on_command_probe(::user::command * pcommand) override;

      virtual bool on_new_document() override;
      virtual bool on_open_document(const payload & varFile) override;

      virtual bool HandleDefaultFileManagerItemCmdMsg(::user::command * pcommand,::file::item_array & itema);

      void PopViews();
      void CreateViews();
      void OpenFolder(::file::item * item, const ::action_context & action_context);
      void filemanager_initialize(bool bMakeVisible, bool bInitialBrowsePath = true);
      void filemanager_initialize(bool bMakeVisible, const ::file::path & path);


      bool set_filemanager_data(::filemanager::data * pdata);

      virtual bool on_create_bars(::user::frame_window * pframe) override;


      virtual void start_full_browse(__pointer(::file::item) pitem, const ::action_context & action_context);
      virtual void full_browse(__pointer(::file::item) pitem, const ::action_context & action_context);


   };


   CLASS_DECL_CORE int get_manager_id_byte_len();

   CLASS_DECL_CORE int get_manager_id_len();

   CLASS_DECL_CORE string create_manager_id(::layered * pobjectContext);

   CLASS_DECL_CORE bool is_valid_manager_id(const char *);

   CLASS_DECL_CORE bool is_valid_filemanager_project_entry(const char *);

   CLASS_DECL_CORE ::file::path filemanager_project_entry(string & strManagerId, const char * psz, ::context * pcontext);


} // namespace filemanager




