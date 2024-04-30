#pragma once


#include "aura/user/user/scroll.h"
#include "acme/primitive/mathematics/int_biunique.h"


namespace user
{


   enum enum_list
   {
      e_list_grid,
      e_list_list,
      e_list_report,
      e_list_icon,
   };

   enum enum_list_element
   {

      e_list_element_item,
      e_list_element_image,
      e_list_element_text,
      e_list_element_sub_item

   };


   class CLASS_DECL_CORE list2 :
      virtual public ::user::scroll_base
   {
   public:


      bool                                         m_bColumnsAdded;
      int                                          m_iImageSpacing;
      bool                                         m_bMorePlain;
      bool                                         m_bAutoCreateListHeader;
      bool                                         m_bHeaderCtrl;
      bool                                         m_bSingleColumnMode;

      ::pointer<list_header>                      m_plistheader;

      //index_map < ::pointer<draw_list_item >>     m_mapDrawListGroup;
      //index_map < ::pointer<draw_list_subitem >>  m_mapDrawListSubitem;

      ::pointer<::user::list_column_array>        m_pcolumna;

      ::pointer<simple_list_data>                 m_psimplelistdata;


      ::pointer<::draw2d::fastblur>               m_pfastblur;
      index_map < ::image_pointer >                m_mapBlur;
      index_map < string >                         m_mapText;
      index_map < ::color::color >                 m_mapBackColor;
      ::pointer<::draw2d::fastblur>               m_pfastblurIcon;
      index_map < ::image_pointer >                m_mapIconBlur;
      double                                       m_dIconSaturation;
      double                                       m_dIconLightness;
      double                                       m_dIconOpacity;
      int                                          m_iIconBlur;
      int                                          m_iIconBlurRadius;
      int                                          m_iTextSpreadRadius;
      int                                          m_iTextBlurRadius;
      int                                          m_iTextBlur;
      ::rectangle_i32                              m_rectangleSpot;
      ::image_pointer                              m_pimageSpot;
      ::image_pointer                              m_pimageTime;
      bool                                         m_bHighHighLight;


      list2();
      ~list2() override;


      ::core::application* get_app();
      ::core::session* get_session();
      ::core::system* get_system();



      virtual i32 _001CalcSubItemWidth(::draw2d::graphics_pointer& pgraphics, ::raw::index iItem, ::raw::index iSubItem);
      virtual i32 _001CalcSubItemWidth(::draw2d::graphics_pointer& pgraphics, ::write_text::font* pfont, ::raw::index iItem, ::raw::index iSubItem);
      virtual i32 _001CalcItemHeight(::user::style* pstyle, int iBaseHeight);
      virtual ::e_align get_draw_text_align(enum_list eview);
      virtual ::e_draw_text get_draw_text_flags(enum_list eview);




      //virtual ::raw::index item_index(::user::interaction * pinteractionControl);
      virtual ::raw::index subitem_index(::user::interaction* pinteractionControl);
      //virtual ::raw::index list_item_index(::user::interaction * pinteractionControl);
      virtual ::raw::index column_index(::user::interaction* pinteractionControl);

      //::pointer<mesh_item>& get_item(::raw::index iItem) override;
      //::pointer<mesh_subitem>& get_subitem(mesh_item* pitem, ::raw::index iSubItem) override;

      //using mesh::get_subitem;

      ::pointer<list_column>new_list_column();


      //void on_hover_select_timer() override;


      void install_message_routing(::channel* pchannel) override;

      //mesh_data * GetDataInterface();
      //using mesh::update_hover;
      //::item_pointer update_hover(::user::mouse * pmouse, ::user::e_zorder ezorder) override;
      //::write_text::font * _001GetFont();
      //::write_text::font * _001GetFontHover();
      //::draw2d::pen * _001GetPenFocused();
      //::draw2d::pen * _001GetPenHighlight();
      void PreSubClassWindow() override;
      virtual void _OnDraw(::draw2d::graphics_pointer& pgraphics);
      virtual void _001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, ::raw::index iColumn);
      //virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, ::raw::index iItem, ::raw::index iSubItem) override;
      virtual i32 _001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, ::raw::index iColumn);
      virtual i32 _001CalcListWidth(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnSort();


      inline ::user::list_column_array& column_array() { return *m_pcolumna; }

      //void _001OnBeforeDeleteRange(range& range) override;
      //void _001OnDeleteRange(range& range) override;
      //void _001DeleteRange(range& range) override;

      // Sort
      //::std::strong_ordering _001Compare(::raw::index iItem1, ::raw::index iItem2) override;
      //::std::strong_ordering _002Compare(::raw::index iItem1, ::raw::index iItem2, ::raw::index iSubItem) override;
      //::std::strong_ordering _001DisplayCompare(::raw::index iDisplayItem1, ::raw::index iDisplayItem2) override;


      virtual bool is_valid_display_item(::raw::index iDisplayItem);
      virtual bool is_valid_strict_item(::raw::index iStrictItem);


      virtual ::size_i32 get_item_size();

      //virtual void _001OnSort(::raw::index iSubItem);
      virtual void _001OnListHeaderItemClick(::raw::index iHeaderItem);
      virtual void _001OnListHeaderItemDblClk(::raw::index iHeaderItem);
      //virtual void Filter1(const string& str);
      //bool Filter1Step() override;


      virtual ::raw::index _001CalcDisplayTopIndex();
      virtual count _001CalcDisplayItemCount();
      virtual i32 _001GetGroupHeight(::raw::index iGroup);


      //void FilterInclude(::i32_array& array) override;
      //void FilterInclude(::raw::index iItem) override;
      //void FilterExcludeAll() override;
      //void FilterClose() override;
      //void FilterApply() override;
      //void FilterBegin() override;
      ::raw::index strict_to_display(::raw::index iStrict) override;
      ::raw::index display_to_strict(::raw::index iDisplay) override;
      void _001Select(::raw::index iItem, ::raw::index iSubItem) override;
      void _001Highlight(::raw::index iItem, bool bRedraw) override;
      void _001RemoveSelection() override;
      bool _001OnRemoveItem(::raw::index iItem) override;
      bool _001RemoveItem(::raw::index iItem, bool bRedraw = true) override;
      void _001EnsureVisible(::raw::index iItem, ::e_align ealign = e_align_vertical_center, bool bRedraw = true);
      //void _001EnsureVisible(::raw::index iItem, range& rangeRedraw) override;
      void scroll_to_item(::raw::index iItem, bool bRedraw = true) override;
      virtual ::raw::index config_id_index(const ::scoped_string& strDataKey);
      ::raw::index data_key_to_sub_item(const ::scoped_string& strDataKey) override;
      bool has_data_key(const ::scoped_string& strDataKey) override;
      void get_selection(const ::scoped_string& scopedstrDataKey, ::string_array& straSelection) override;

      virtual void _001SetSingleColumnMode(bool bHeaderCtrl);
      //virtual bool _001InsertColumn(::user::list_column * pcolumn);
      //virtual void _001OnAfterNewColumns();
      void set_data_interface(mesh_data* pinterface) override;
      void cache_hint() override;
      //void SetCacheInterface(mesh_cache_interface * pinterface);
      //void AddMessageHandling(::channel * pchannel);
      void _001ShowTopText(bool bShow = true) override;
      void _001LayoutTopText(::draw2d::graphics_pointer& pgraphics) override;
      void _001SetTopText(const ::wide_character* pcwsz) override;

      bool DIDDXHeaderLayout(bool bSave) override;


      void data_get_DisplayToStrict() override;
      void data_set_DisplayToStrict() override;
      atom data_get_current_sort_id() override;
      atom data_get_sort_id(enum_list eview) override;
      virtual atom data_get_current_list_layout_id();

      bool query_drop(::raw::index iDisplayDrop, ::raw::index iDisplayDrag) override;
      bool do_drop(::raw::index iDisplayDrop, ::raw::index iDisplayDrag) override;
      bool defer_drop(::raw::index iDisplayDrop, ::raw::index iDisplayDrag) override;



      virtual bool CreateHeaderCtrl();

      void _001OnNcDraw(::draw2d::graphics_pointer& pgraphics) override;

      void _001OnDraw(::draw2d::graphics_pointer& pgraphics) override;

      //virtual void _001DrawGroups(::draw2d::graphics_pointer & pgraphics, ::raw::index iGroupFirst, ::raw::index iGroupLast, ::raw::index iItemFirst, ::raw::index iItemLast);

      void _001DrawGroups(::draw2d::graphics_pointer& pgraphics, ::raw::index iGroupFirst, ::raw::index iGroupLast) override;

      virtual void _001DrawGroup(::draw2d::graphics_pointer& pgraphics, draw_list_group* pdrawgroup);

      void _001DrawItems(::draw2d::graphics_pointer& pgraphics, ::raw::index iItemFirst, ::raw::index iItemLast) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, draw_list_item* pdrawitem);

      virtual void _001DrawSubItem(::draw2d::graphics_pointer& pgraphics, draw_list_subitem* psubitem);

      //virtual void _001GetItemImage(list_item * pitem);

      //virtual void _001GetItemText(list_item * pitem);

      //virtual void _001GetItemColor(list_item * pitem);

      //virtual void _001SearchGetItemText(list_item * pitem);

      ::raw::count _001GetGroupItemCount(::raw::index iGroup) override;

      ::raw::count _001GetGroupMetaItemCount(::raw::index iGroup) override;

      //virtual void _001GetGroupText(list_item * pitem);

      //virtual void _001GetGroupImage(list_item * pitem);

      virtual void on_insert_columns();

      ::raw::count _001GetColumnCount() override;


      virtual ::pointer<::user::list_header>create_list_header();
      ::pointer<::user::mesh_data>create_mesh_data() override;

      void on_layout(::draw2d::graphics_pointer& pgraphics) override;

      bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      void on_change_impact_size(::draw2d::graphics_pointer& pgraphics) override;


      void _001OnInitialize() override;


      //virtual ::pointer<list_column>new_column();
      virtual void _001OnAddColumn(list_column* pcolumn);

      virtual void _001GetGroupRect(draw_list_group* pdrawlistgroup);
      virtual void index_item_rectangle(draw_list_item* pdrawlistitem);
      virtual void _001GetSubItemRect(draw_list_subitem* pdrawlistsubitem);
      virtual void index_element_rectangle(draw_list_subitem* pdrawlistsubitem, ::user::enum_list_element eelement);
      //virtual void _001GetGroupElementRect(draw_list_group* pdrawlistgroup, ::user::mesh::enum_group_element egroupelement);

      virtual ::user::interaction* get_subitem_control(::raw::index iSubItem);

      virtual void _001OnColumnChange();

      bool _001SetColumnWidth(::raw::index iColumn, i32 iWidth) override;

      //virtual int _001GetColumnWidth(::raw::index iColumn);

      ::raw::index sub_item_to_order(::raw::index iSubItem) override;

      ::raw::index _001MapOrderToSubItem(::raw::index iOrder) override;

      ::raw::index _001MapOrderToColumn(::raw::index iOrder) override;

      ::raw::index _001MapColumnToOrder(::raw::index iColumn) override;

      ::raw::index _001MapSubItemToColumn(::raw::index iSubItem) override;

      ::raw::index _001MapColumnToSubItem(::raw::index iColumn) override;

      void _001DeleteColumn(::raw::index iColumn);


      ::raw::count _001GetItemCount() override;
      ::raw::count _001GetGroupCount() override;


      bool _001HitTest_(const ::point_i32& point, ::raw::index & iItem, ::raw::index & iSubItem, ::raw::index & iListItem, ::user::enum_list_element& eelement) override;
      bool _001HitTest_(const ::point_i32& point, ::raw::index & iItem, ::raw::index & iSubItem) override;
      bool _001HitTest_(const ::point_i32& point, ::raw::index & iItemParam) override;


      bool _001DisplayHitTest(const ::point_i32& point, ::raw::index & iItem, ::raw::index & iSubItem, ::raw::index & iListItem, ::user::enum_list_element& eelement) override;
      bool _001DisplayHitTest(const ::point_i32& point, ::raw::index & iItem, ::raw::index & iSubItem) override;
      bool _001DisplayHitTest(const ::point_i32& point, ::raw::index & iItemParam) override;


      void _001OnAfterSort() override;


      virtual void LayoutHeaderCtrl();

      void auto_arrange(bool bAutoArrange = true) override;

      bool get_auto_arrange() override;

      //void on_create_draw_item() override;

      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      void _001OnTimer(::timer* ptimer) override;

      DECLARE_MESSAGE_HANDLER(_001OnUpdateListImpactAutoArrange);

      DECLARE_MESSAGE_HANDLER(_001OnListImpactAutoArrange);


      bool on_click(::item* pitem) override;
      bool on_right_click(::item* pitem) override;

      //void get_selection(range& selection) override;
      virtual ::raw::index _001GetCurItem();

      virtual void _001SelectItem(::raw::index iItem);

      bool _001IsEditing() override;


      ::raw::count _001GetSelectedItemCount() override;
      virtual ::raw::count _001GetSelectedItems(index_array& ia);


      string _001GetColumnText(::raw::index iColumn) override;

      virtual void HeaderCtrlLayout();

      virtual ::raw::index HeaderCtrlMapColumnToOrder(::raw::index iColumn);

      virtual bool _001OnHeaderCtrlEndDrag(wparam wparam, lparam lparam);



      bool _001OnHeaderCtrlEndTrack(wparam wparam, lparam lparam) override;


      bool _001OnHeaderCtrlTrack(wparam wparam, lparam lparam) override;


      void _001ShowSubItem(::raw::index iSubItem, bool bShow = true) override;
      void DISaveOrder() override;

      void DILoadOrder() override;


      //void on_selection_change() override;


      virtual void _001UpdateColumns();


      virtual void _001RemoveAllColumns();


      virtual void _001CreateImageList(list_column* pcolumn);

      bool _001IsItemVisible(::raw::index iItem) override;

      //virtual void clear_selection() override;

      //void set_selection(const range & range) override;

      //void _001AddSelection(const item_range & itemrange) override;

      void set_current_item(::item* pitem, const ::action_context& action_context) override;
      ::item_pointer current_item() override;

      void set_current_item(const index_array& iaSel, const ::action_context& action_context) override;
      void get_cur_sel(index_array& iaSel) override;

      //void _001SetHighlightRange(range& range) override;

      //void _001SetImpact(enum_list eview, bool bLayout = true);

      enum_list _001GetImpact() override;


      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_context_offset(::draw2d::graphics_pointer& pgraphics) override;

      virtual bool keyboard_focus_is_focusable() override;

      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);

      virtual void _thread_data_update_visible_subitem() override;

      virtual void defer_create_mesh_data() override;

      virtual void on_context_offset(::draw2d::graphics_pointer& pgraphics) override;

      virtual void _001OnClip(::draw2d::graphics_pointer& pgraphics) override;

      //virtual bool this->rectangle(::rectangle_i32 * prectangle) override;


      virtual void update_icon_list_impact_sort();

   };


} // namespace user




