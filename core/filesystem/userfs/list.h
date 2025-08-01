#pragma once


#include "core/user/user/form_list_impact.h"


namespace userfs
{

   
   class main_impact;


   class CLASS_DECL_CORE list :
      virtual public ::user::form_list_impact
   {
   public:


      


      string_array               m_straFileSize;
      ::file::path_array         m_pathaStrictOrder;
      ::collection::index                      m_iSelectionSubItem;
      ::collection::index                      m_iNameSubItem;
      ::collection::index                      m_iNameSubItemText;
      ::collection::index                      m_iIconSubItem;
      document *                 m_pdocument;
      //::fs::data *               m_pfsdata;


      list();
      ~list() override;


      void initialize_impact(::user::document * pdocument) override;


      //inline ::fs::data * fs_data() { return m_pfsdata; }

      
      void on_insert_columns() override;

      void on_update_item_count() override;

      inline ::userfs::document * get_document() { return m_pdocument; }

      virtual list_data * fs_list();

      //void add_fs_item(::file::path pathUser, ::file::path pathFinal, const ::scoped_string & scopedstrName);

      void install_message_routing(::channel * pchannel) override;

      ::image::image_list * GetActionButtonImageList(::collection::index i);


      virtual void get_selected_user_path(::file::path_array & stra);
      virtual void get_selected_final_path(::file::path_array & stra);
      virtual void get_selected_items(::file::item_array & itema);


      virtual ::file::path_array get_selected_user_path();
      virtual ::file::path_array get_selected_final_path();
      virtual ::file::item_array get_selected_items();
      virtual ::file::item * get_first_selected_item();


      void _001OnInitializeForm(::user::interaction * pinteraction) override;
      void _001OnButtonAction(::user::interaction * pinteraction) override;

      virtual void _017OpenItem(::pointer<::file::item>pitem, bool bOpenFile, const ::action_context & action_context);
      virtual void _017OpenFile(const ::file::item_array & itema, const ::action_context & action_context);
      //virtual void _017OpenFolder(::pointer<::file::item>pitem, const ::action_context & action_context);
      virtual bool _017OpenSelected(bool bOpenFile, const ::action_context & action_context);
      virtual void _017OpenContextMenuSelected(const ::action_context & action_context);
      virtual void _017OpenContextMenuFolder(::pointer<::file::item> item, const ::action_context & action_context);
      virtual void _017OpenContextMenuFile(const ::file::item_array &itema, const ::action_context & action_context);
      virtual void _017OpenContextMenu(const ::action_context & action_context);
      //void TakeAnimationSnapshot();
      //virtual void StartAnimation();
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      //void GetSelectedFilePath(string_array & array);
      void _001GetSubItemImage(::user::mesh_subitem * psubitem) override;
      void _001GetSubItemText(::user::mesh_subitem * psubitem) override;
      ::collection::count _001GetItemCount() override;


      void _001InitializeFormPreData() override;

      /*bool query_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag) override;
      bool do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag) override;*/


      bool on_click(::item * pitem, ::user::mouse * pmouse) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
      bool pre_create_window(::user::system * pusersystem) override;

      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(_001OnFileRename);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateFileRename);
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(_001OnCancelMode);


      void on_timer(::timer * ptimer) override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      ::pointer<::user::mesh_data>create_mesh_data() override;

      //virtual ::fs::data * fs_data();
      ::file::item * fs_list_item(::collection::index iIndex);


   };


} // namespace userfs



