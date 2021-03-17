#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list :
      virtual public ::filemanager_show < ::userfs::list >
   {
   public:


      context_menu                        m_contextmenu;
      string_array                        m_straOpenWith;
      bool                                m_bFileSize;
      bool                                m_bShow;
      index                               m_iSizeSubItem;
      millis                              m_millisLastFileSizeGet;


      //map < icon_key,const icon_key &,icon,icon & > m_iconmap;

//#ifdef WINDOWS_DESKTOP
//      IShellFolder *                   m_pshellfolder;
//#endif
      bool                             m_bStatic;


      file_list();
      virtual ~file_list();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;


      virtual __pointer(::fs::data) fs_data() override;

      //void schedule_file_size(const char * psz);

      virtual void _017OpenContextMenuFolder(__pointer(::file::item) item, const ::action_context & action_context) override;
      virtual void _017OpenContextMenuFile(const ::file::item_array &itema, const ::action_context & action_context) override;
      virtual void _017OpenContextMenu(const ::action_context & action_context) override;
      virtual void _017OpenFile(const ::file::item_array & itema, const ::action_context & action_context) override;
      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context) override;
      virtual void RenameFile(i32 iLine, string & str, const ::action_context & action_context);

      //void FileSize();

      virtual void route_command_message(::message::command * pcommand) override;
      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;

      virtual void on_command_probe(::message::command * pcommand) override;
      virtual void on_command(::message::command * pcommand) override;

      DECL_GEN_SIGNAL(_001OnUpdateOpenWith);
      DECL_GEN_SIGNAL(_001OnEditCopy);
      DECL_GEN_SIGNAL(_001OnUpdateEditCopy);
      DECL_GEN_SIGNAL(_001OnShowWindow);

      DECL_GEN_SIGNAL(_001OnSetFocus);
      DECL_GEN_SIGNAL(_001OnKillFocus);




      virtual id data_get_current_list_layout_id() override;



      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnContextMenu);

      DECL_GEN_SIGNAL(_001OnShellCommand);
      DECL_GEN_SIGNAL(_001OnFileManagerItemCommand);
      DECL_GEN_SIGNAL(_001OnFileManagerItemUpdate);

      DECL_GEN_SIGNAL(_001OnFileRename);
      DECL_GEN_SIGNAL(_001OnUpdateFileRename);

      DECL_GEN_SIGNAL(_001OnTrashThatIsNotTrash);
      DECL_GEN_SIGNAL(_001OnUpdateTrashThatIsNotTrash);

      //DECL_GEN_SIGNAL(_001OnSpafy);
      //DECL_GEN_SIGNAL(_001OnUpdateSpafy);
      //DECL_GEN_SIGNAL(_001OnSpafy2);
      //DECL_GEN_SIGNAL(_001OnUpdateSpafy2);


      virtual void _001OnTimer(::timer * ptimer) override;


      virtual bool on_click(const ::user::item & item) override;
      virtual bool on_right_click(const ::user::item & item) override;

      virtual void _001OnAfterSort() override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void _001InsertColumns() override;

      //virtual void file_size_add_request(bool bClear);


      //virtual color32_t get_background_color() override;
      bool add_fs_item(::file::path pathUser, ::file::path pathFinal, string strName);
      virtual void browse_sync(const ::action_context & action_context) override;

      __pointer(::image_list) GetActionButtonImageList(index i);

      //void GetSelected(::file::item_array & itema);

      void _001OnInitializeForm(::user::interaction * pinteraction) override;
      void _001OnButtonAction(::user::interaction * pinteraction) override;

      //virtual void _017OpenSelected(bool bOpenFile, const ::action_context & action_context) override;
      virtual void _017OpenContextMenuSelected(const ::action_context & action_context) override;
      void _017PreSynchronize(const ::action_context & action_context);
      //void TakeAnimationSnapshot();
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      ::file::item & GetFileManagerItem();
      //DECL_GEN_SIGNAL(_001OnMainPostMessage);
      void _017UpdateList(const ::action_context & action_context);


      //virtual bool TwiHasTranslucency();
      //void _001CreateImageList();
      //bool _001CreateImageListStep();
      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;
      void _017Browse(const char * pcsz, const ::action_context & action_context);

      void _017UpdateList(const char * pcsz, const ::action_context & action_context);

      void _017UpdateZipList(const char * pcsz, const ::action_context & action_context);


      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnVScroll);


      virtual void _001InitializeFormPreData() override;



      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag) override;
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag) override;


   };


} // namespace filemanager


