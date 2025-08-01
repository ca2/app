#pragma once


#include "impact_base.h"
#include "acme/handler/item.h"
#include "core/filesystem/userfs/list.h"


namespace filemanager
{


   class CLASS_DECL_CORE file_list :
      virtual public ::filemanager_show < ::userfs::list >
   {
   public:

      
      ::pointer<context_menu>            m_pcontextmenu;
      string_array                        m_straOpenWith;
      bool                                m_bFileSize;
      bool                                m_bShow;
      ::collection::index                               m_iSizeSubItem;
      class ::time                          m_timeLastFileSizeGet;


      //map < icon_key,const icon_key &,icon,icon & > m_iconmap;

//#ifdef WINDOWS_DESKTOP
//      IShellFolder *                   m_pshellfolder;
//#endif
      bool                             m_bStatic;


      file_list();
      ~file_list() override;


      void initialize_impact(::user::document * pdocument) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;



      //void schedule_file_size(const ::scoped_string & scopedstr);

      void _017OpenContextMenuFolder(::pointer<::file::item>item, const ::action_context & action_context) override;
      void _017OpenContextMenuFile(const ::file::item_array &itema, const ::action_context & action_context) override;
      void _017OpenContextMenu(const ::action_context & action_context) override;
      void _017OpenFile(const ::file::item_array & itema, const ::action_context & action_context) override;
      //void _017OpenFolder(::pointer<::file::item>pitem, const ::action_context & action_context) override;
      virtual void RenameFile(int iLine, string & str, const ::action_context & action_context);

      //void FileSize();

      void route_command(::message::command * pcommand, bool bRouteToKeyDescendant = false) override;
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      bool pre_create_window(::user::system * pusersystem) override;

      void on_command_probe(::message::command * pcommand) override;
      void on_command(::message::command * pcommand) override;

      DECLARE_MESSAGE_HANDLER(_001OnUpdateOpenWith);
      DECLARE_MESSAGE_HANDLER(_001OnEditCopy);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateEditCopy);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);

      DECLARE_MESSAGE_HANDLER(on_message_set_focus);
      DECLARE_MESSAGE_HANDLER(on_message_kill_focus);
      DECLARE_MESSAGE_HANDLER(_001OnFileOpen);




      virtual atom data_get_current_list_layout_id() override;



      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_context_menu);

      DECLARE_MESSAGE_HANDLER(_001OnShellCommand);
      DECLARE_MESSAGE_HANDLER(_001OnFileManagerItemCommand);
      DECLARE_MESSAGE_HANDLER(_001OnFileManagerItemUpdate);

      DECLARE_MESSAGE_HANDLER(_001OnFileRename);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileRename);

      DECLARE_MESSAGE_HANDLER(_001OnTrashThatIsNotTrash);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateTrashThatIsNotTrash);

      //DECLARE_MESSAGE_HANDLER(_001OnSpafy);
      //DECLARE_MESSAGE_HANDLER(_001OnUpdateSpafy);
      //DECLARE_MESSAGE_HANDLER(_001OnSpafy2);
      //DECLARE_MESSAGE_HANDLER(_001OnUpdateSpafy2);


      virtual void on_timer(::timer * ptimer) override;


      bool on_click(::item * pitem, ::user::mouse * pmouse) override;
      bool on_right_click(::item * pitem, ::user::mouse * pmouse) override;

      virtual void _001OnAfterSort() override;

      void install_message_routing(::channel * pchannel) override;

      virtual void on_insert_columns() override;

      //virtual void file_size_add_request(bool bClear);


      //virtual ::color::color get_background_color() override;
      bool add_fs_item(::file::path pathUser, ::file::path pathFinal, const ::scoped_string & scopedstrName);
      virtual void browse_sync(const ::action_context & action_context) override;

      ::image::image_list * GetActionButtonImageList(::collection::index i);

      //void GetSelected(::file::item_array & itema);

      void _001OnInitializeForm(::user::interaction * pinteraction) override;
      void _001OnButtonAction(::user::interaction * pinteraction) override;

      //virtual void _017OpenSelected(bool bOpenFile, const ::action_context & action_context) override;
      virtual void _017OpenContextMenuSelected(const ::action_context & action_context) override;
      void _017PreSynchronize(const ::action_context & action_context);
      //void TakeAnimationSnapshot();
      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      ::file::item & GetFileManagerItem();
      //DECLARE_MESSAGE_HANDLER(_001OnMainPostMessage);
      void _017UpdateList(const ::action_context & action_context);


      //virtual bool TwiHasTranslucency();
      //void _001CreateImageList();
      //bool _001CreateImageListStep();
      void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;
      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;
      virtual ::collection::count _001GetItemCount() override;
      void _017Browse(const ::scoped_string & scopedstr, const ::action_context & action_context);

      void _017UpdateList(const ::scoped_string & scopedstr, const ::action_context & action_context);

      void _017UpdateZipList(const ::scoped_string & scopedstr, const ::action_context & action_context);


      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);


      virtual void _001InitializeFormPreData() override;



      virtual bool query_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag) override;
      virtual bool do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag) override;


   };


} // namespace filemanager


