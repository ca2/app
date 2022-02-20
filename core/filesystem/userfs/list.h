#pragma once


namespace userfs
{

   class main_impact;

   class CLASS_DECL_CORE list :
      virtual public ::user::form_list_view
   {
   public:


      


      string_array              m_straFileSize;
      ::file::patha        m_pathaStrictOrder;
      index                m_iSelectionSubItem;
      index                m_iNameSubItem;
      index                m_iNameSubItemText;
      index                m_iIconSubItem;



      list();
      virtual ~list();

      virtual void _001InsertColumns() override;

      virtual bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      __pointer(::userfs::document) get_document();

      virtual list_data * fs_list();

      void add_fs_item(::file::path pathUser, ::file::path pathFinal, string strName);

      void install_message_routing(::channel * pchannel) override;

      __pointer(::image_list) GetActionButtonImageList(index i);


      virtual void get_selected_user_path(::file::patha & stra);
      virtual void get_selected_final_path(::file::patha & stra);
      virtual void get_selected_items(::file::item_array & itema);


      virtual ::file::patha get_selected_user_path();
      virtual ::file::patha get_selected_final_path();
      virtual ::file::item_array get_selected_items();
      virtual __pointer(::file::item) get_first_selected_item();


      void _001OnInitializeForm(::user::interaction * pinteraction) override;
      void _001OnButtonAction(::user::interaction * pinteraction) override;

      virtual void _017OpenItem(__pointer(::file::item) pitem, bool bOpenFile, const ::action_context & action_context);
      virtual void _017OpenFile(const ::file::item_array & itema, const ::action_context & action_context);
      virtual void _017OpenFolder(__pointer(::file::item) pitem, const ::action_context & action_context);
      virtual bool _017OpenSelected(bool bOpenFile, const ::action_context & action_context);
      virtual void _017OpenContextMenuSelected(const ::action_context & action_context);
      virtual void _017OpenContextMenuFolder(__pointer(::file::item)  item, const ::action_context & action_context);
      virtual void _017OpenContextMenuFile(const ::file::item_array &itema, const ::action_context & action_context);
      virtual void _017OpenContextMenu(const ::action_context & action_context);
      //void TakeAnimationSnapshot();
      //virtual void StartAnimation();
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      //void GetSelectedFilePath(string_array & array);
      virtual void _001GetItemImage(::user::mesh_item * pitem) override;
      virtual void _001GetItemText(::user::mesh_item * pitem) override;
      virtual count _001GetItemCount() override;


      virtual void _001InitializeFormPreData() override;

      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag) override;
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag) override;



      virtual bool on_click(::item * pitem) override;


      virtual void handle(::topic * ptopic, ::context * pcontext) override;
      virtual bool pre_create_window(::user::system * pusersystem) override;

      DECLARE_MESSAGE_HANDLER(_001OnHScroll);
      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnFileRename);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileRename);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnCancelMode);


      virtual void _001OnTimer(::timer * ptimer) override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      __pointer(::user::mesh_data) create_mesh_data() override;

      virtual __pointer(::fs::data) fs_data();
      virtual __pointer(::file::item) fs_list_item(index iIndex);


   };


} // namespace userfs



