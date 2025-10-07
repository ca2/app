#pragma once


#include "core/filesystem/userfs/document.h"
#include "file_list_callback.h"
#include "acme/filesystem/watcher/listener.h"
#include "aura/filesystem/filemanager/callback.h"


namespace filemanager
{


   class CLASS_DECL_CORE document :
      virtual public ::file::listener::base,
      virtual public ::userfs::document,
      virtual public ::filemanager::callback,
      virtual public ::filemanager::file_list_callback
   {
   public:

            ::pointer < ::file::watch >                    m_pfilewatch;
      ::pointer<::filemanager::data>            m_pfilemanagerdata;
      ::file::path                        m_strTopic;
      string                              m_strManagerId;
      bool                                m_bInitialized;
///      ::pointer < ::user::document >         m_pdocumentTopic;
      int m_iIconSize;

      document();
      ~document() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();
      //
      
//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      //virtual ::fs::data *                         fs_data();
      virtual ::file::item *                         filemanager_item();
      ::filemanager::data *                filemanager_data();

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

      //virtual void defer_check_manager_id(const ::scoped_string & scopedstrNewManagerId = "");
      virtual void on_request(::request * prequest) override;

      virtual bool do_prompt_file_name(::payload & payloadFile, const ::scoped_string & scopedstrTitle, unsigned int lFlags, bool bOpenFileDialog, ::user::impact_system * ptemplate, ::user::document * pdocument);

      ::pointer<::filemanager::data>create_file_manager_data(::request * prequest = nullptr);

      //virtual void Initialize(int iTemplate, const ::scoped_string & scopedstrMatter);

      void browse_initial_path(const ::action_context & actioncontext) override;

      void OnFileManagerOpenFile(::filemanager::data * pdata, ::file::item_array & itema);


      virtual void InitializeFileManager(const ::scoped_string & scopedstrMatter);
      
      
      virtual void _001Refresh();

      string get_initial_browse_path(const ::scoped_string & scopedstrDefault = nullptr);

      virtual void browse(const ::file::path & path, const ::action_context & action_context) override;
      virtual bool browse(::pointer<::file::item>pitem, const ::action_context & action_context) override;

      //virtual void browse(const ::file::path & path, const ::action_context & action_context);

      //virtual bool browse(::pointer<::file::item>item, const ::action_context & action_context) override;

      virtual void on_file_manager_open_context_menu_folder(::pointer<::file::item> item, string_array_base & straCommand, string_array_base & straCommandTitle, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu_file(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu(const ::action_context & action_context);
      virtual void on_file_manager_open(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_folder(::pointer<::file::item> str, const ::action_context & action_context);

      virtual void on_file_manager_item_update(::message::command * pcommand, const ::file::item_array & itema);
      virtual void on_file_manager_item_command(const ::scoped_string & scopedstrId, const ::file::item_array & itema);

      //critical_section * GetItemIdListCriticalSection();

      //virtual bool FileManagerBrowse(::file::item * pitem, const ::action_context & action_context);
      //virtual bool FileManagerBrowse(const ::scoped_string & scopedstr, const ::action_context & action_context);


      virtual void FileManagerOneLevelUp(const ::action_context & action_context);
      virtual void OnFileManagerBrowse(const ::action_context & action_context) override;
      virtual void OpenSelectionProperties();

      virtual void GetActiveImpactSelection(::file::item_array & itema);


      virtual void FileManagerSaveAs(::user::document * pdocument);
      virtual void FileManagerImport(::user::document * pdocument);
      virtual void FileManagerExport(::user::document * pdocument);
      virtual void FileManagerTopicOK();
      virtual void FileManagerTopicCancel();



      void operator()(::file::action * paction) override;


      //virtual void on_create(::request * prequest) override;


      operation_document * get_operation_doc(bool bSwitch);


      virtual void on_command(::message::command * pcommand) override;
      virtual void on_command_probe(::message::command * pcommand) override;

      bool on_new_document() override;
      //virtual bool on_open_document(const ::payload & payloadFile) override;

      virtual bool on_open_data(::data::data * pdata) override;

      virtual bool HandleDefaultFileManagerItemCmdMsg(::message::command * pcommand,::file::item_array & itema);

      void PopImpacts();
      void CreateImpacts();



      //void OpenFolder(::file::item * item, const ::action_context & action_context);
//      void browse_initial_path(const ::action_context & action_context);
      //virtual void browse_initial_path(const ::action_context & action_context);


      //virtual void browse(const ::file::path & path, const ::action_context & action_context);
      //virtual bool browse(::pointer<::file::item>pitem, const ::action_context & action_context);

      //void filemanager_initialize(bool bMakeVisible, const ::file::path & path);
       void defer_initialize_filemanager() override;

      bool set_filemanager_data(::filemanager::data * pdata);


      bool has_toolbar() override;

      ::atom get_toolbar_id() override;
      
      //virtual ::user::toolbar * get_toolbar(::user::frame_interaction * pframe, bool bCreate) override;

      void on_update_data(::data::data * pdata, ::topic * ptopic, const ::action_context & context) override;


   };


   CLASS_DECL_CORE int get_manager_id_byte_len();

   CLASS_DECL_CORE int get_manager_id_len();

   CLASS_DECL_CORE string create_manager_id(::particle * pparticle);

   CLASS_DECL_CORE bool is_valid_manager_id(const ::scoped_string & scopedstr);

   CLASS_DECL_CORE bool is_valid_filemanager_project_entry(const ::scoped_string & scopedstr);

   CLASS_DECL_CORE ::file::path filemanager_project_entry(string & strManagerId, const ::scoped_string & scopedstr, ::aura::context * pcontext);


} // namespace filemanager




