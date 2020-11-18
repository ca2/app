#pragma once


namespace user
{


   class CLASS_DECL_CORE list :
      virtual public mesh
   {
   public:


      bool                                   m_bColumnsAdded;
      int                                    m_iImageSpacing;
      bool                                   m_bMorePlain;
      bool                                   m_bAutoCreateListHeader;
      bool                                   m_bHeaderCtrl;
      bool                                   m_bSingleColumnMode;

      __pointer(list_header)                 m_plistheader;

      draw_list_item *                       m_pdrawlistitem;

      ::user::list_column_array              m_columna;

      __pointer(simple_list_data)            m_psimplelistdata;


      ::draw2d::fastblur                     m_blur;
      index_map < ::image_pointer >          m_mapBlur;
      index_map < string >                   m_mapText;
      index_map < color32_t >                 m_mapBackColor;
      ::draw2d::fastblur                     m_blurIcon;
      index_map < ::image_pointer >          m_mapIconBlur;
      double                                 m_dIconSaturation;
      double                                 m_dIconLightness;
      double                                 m_dIconOpacity;
      int                                    m_iIconBlur;
      int                                    m_iIconBlurRadius;
      int                                    m_iTextSpreadRadius;
      int                                    m_iTextBlurRadius;
      int                                    m_iTextBlur;
      ::rect                                 m_rectSpot;
      ::image_pointer                        m_pimageSpot;
      ::image_pointer                        m_pimageTime;
      bool                                   m_bHighHighLight;


      list();
      virtual ~list();



      virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, index iItem, index iSubItem) override;
      virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, ::draw2d::font * pfont, index iItem, index iSubItem);
      virtual i32 _001CalcItemHeight(::user::style * pstyle, int iBaseHeight);
      virtual ::e_align get_draw_text_align(EView eview);
      virtual ::e_draw_text get_draw_text_flags(EView eview);



      __pointer(list_column) new_list_column();


      virtual void on_hover_select_timer() override;


      virtual void install_message_routing(::channel * pchannel) override;

      //mesh_data * GetDataInterface();
      using mesh::update_hover;
      virtual bool update_hover(const ::point& point, bool bAvoidRedraw = true) override;
      //::draw2d::font * _001GetFont();
      //::draw2d::font * _001GetFontHover();
      //::draw2d::pen * _001GetPenFocused();
      //::draw2d::pen * _001GetPenHighlight();
      virtual void PreSubClassWindow() override;
      virtual void _OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn) override;
      //virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, index iItem, index iSubItem) override;
      virtual i32 _001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn) override;
      virtual i32 _001CalcListWidth(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnSort() override;


      virtual void _001OnBeforeDeleteRange(range & range) override;
      virtual void _001OnDeleteRange(range & range) override;
      virtual void _001DeleteRange(range & range) override;

      // Sort
      virtual index _001Compare(index iItem1, index iItem2) override;
      virtual index _002Compare(index iItem1, index iItem2, index iSubItem) override;
      virtual index _001DisplayCompare(index iDisplayItem1, index iDisplayItem2) override;


      virtual bool is_valid_display_item(index iDisplayItem) override;
      virtual bool is_valid_strict_item(index iStrictItem) override;


      virtual ::size get_item_size() override;

      virtual void _001OnSort(index iSubItem) override;
      virtual void _001OnListHeaderItemClick(index iHeaderItem);
      virtual void _001OnListHeaderItemDblClk(index iHeaderItem);
      virtual void Filter1(string & str) override;
      virtual bool Filter1Step() override;


      virtual index _001CalcDisplayTopIndex() override;
      virtual count _001CalcDisplayItemCount() override;
      virtual i32 _001GetGroupHeight(index iGroup) override;


      virtual void FilterInclude(int_array & array) override;
      virtual void FilterInclude(index iItem) override;
      virtual void FilterExcludeAll() override;
      virtual void FilterClose() override;
      virtual void FilterApply() override;
      virtual void FilterBegin() override;
      virtual index _001StrictToDisplay(index iStrict) override;
      virtual index _001DisplayToStrict(index iDisplay) override;
      virtual void _001Select(index iItem, index iSubItem) override;
      virtual void _001Highlight(index iItem, bool bRedraw) override;
      virtual void _001RemoveSelection() override;
      virtual bool _001OnRemoveItem(index iItem) override;
      virtual bool _001RemoveItem(index iItem, bool bRedraw = true) override;
      virtual void _001EnsureVisible(index iItem, ::e_align e_align = e_align_vertical_center, bool bRedraw = true);
      virtual void _001EnsureVisible(index iItem, range & rangeRedraw) override;
      virtual void _001ItemScroll(index iItem, bool bRedraw = true) override;
      virtual index config_id_index(const ::database::key & key);
      virtual index _001ConfigIdToSubItem(const ::database::key & key) override;
      virtual bool _001HasConfigId(const ::database::key & key) override;
      virtual void _001GetSelection(::database::key & key, ::database::selection & selection) override;

      virtual void _001SetSingleColumnMode(bool bHeaderCtrl);
      //virtual bool _001InsertColumn(::user::list_column * pcolumn);
      //virtual void _001OnAfterNewColumns();
      virtual void SetDataInterface(mesh_data * pinterface) override;
      virtual void CacheHint() override;
      //void SetCacheInterface(mesh_cache_interface * pinterface);
      //void AddMessageHandling(::channel * pchannel);
      virtual void _001ShowTopText(bool bShow = true) override;
      virtual void _001LayoutTopText(::draw2d::graphics_pointer& pgraphics) override;
      virtual void _001SetTopText(const widechar * pcwsz) override;

      virtual bool DIDDXHeaderLayout(bool bSave) override;


      virtual void data_get_DisplayToStrict() override;
      virtual void data_set_DisplayToStrict() override;
      virtual id data_get_current_sort_id() override;
      virtual id data_get_sort_id(EView eview) override;
      virtual id data_get_current_list_layout_id();

      virtual bool query_drop(index iDisplayDrop, index iDisplayDrag) override;
      virtual bool do_drop(index iDisplayDrop, index iDisplayDrag) override;
      virtual bool defer_drop(index iDisplayDrop, index iDisplayDrag) override;



      virtual bool CreateHeaderCtrl();

      virtual void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawGroups(draw_list_item * pdrawitem, index iGroupFirst, index iGroupLast, index iItemFirst, index iItemLast);

      virtual void _001DrawGroup(draw_list_item * pdrawitem);

      virtual void _001DrawItems(draw_list_item * pdrawitem, index iItemFirst, index iItemLast);

      virtual void _001DrawItem(draw_list_item * pdrawitem);

      virtual void _001DrawSubItem(draw_list_item * pdrawitem);

      //virtual void _001GetItemImage(list_item * pitem);

      //virtual void _001GetItemText(list_item * pitem);

      //virtual void _001GetItemColor(list_item * pitem);

      //virtual void _001SearchGetItemText(list_item * pitem);

      virtual ::count _001GetGroupItemCount(index iGroup) override;

      virtual ::count _001GetGroupMetaItemCount(index iGroup) override;

      //virtual void _001GetGroupText(list_item * pitem);

      //virtual void _001GetGroupImage(list_item * pitem);

      virtual void _001InsertColumns();

      ::count _001GetColumnCount() override;


      virtual __pointer(::user::list_header) create_list_header();
      virtual __pointer(::user::mesh_data) create_mesh_data() override;

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool _001OnUpdateItemCount(u32 dwFlags = 0) override;

      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnInitialize() override;


      //virtual __pointer(list_column) new_column();
      virtual void _001OnAddColumn(list_column * pcolumn);

      virtual void _001GetGroupRect(draw_list_item * pitem);
      virtual void _001GetItemRect(draw_list_item * pitem);
      virtual void _001GetSubItemRect(draw_list_item * pitem);
      virtual void _001GetElementRect(draw_list_item * pitem, ::user::mesh::e_element eelement);

      virtual void _001OnColumnChange();

      virtual bool _001SetColumnWidth(index iColumn, i32 iWidth) override;

      virtual void _001GetColumnWidth(draw_list_item * pdrawitem);

      virtual index _001MapSubItemToOrder(index iSubItem) override;

      virtual index _001MapOrderToSubItem(index iOrder) override;

      virtual index _001MapOrderToColumn(index iOrder) override;

      virtual index _001MapColumnToOrder(index iColumn) override;

      virtual index _001MapSubItemToColumn(index iSubItem) override;

      virtual index _001MapColumnToSubItem(index iColumn) override;

      void _001DeleteColumn(index iColumn);


      virtual ::count _001GetItemCount() override;
      virtual ::count _001GetGroupCount() override;


      virtual bool _001HitTest_(const ::point & point, index & iItem, index & iSubItem, index & iListItem, ::user::mesh::e_element & eelement) override;
      virtual bool _001HitTest_(const ::point & point, index & iItem, index & iSubItem) override;
      virtual bool _001HitTest_(const ::point & point, index & iItemParam) override;


      virtual bool _001DisplayHitTest(const ::point & point, index & iItem, index & iSubItem, index & iListItem, ::user::mesh::e_element & eelement) override;
      virtual bool _001DisplayHitTest(const ::point & point, index & iItem, index & iSubItem) override;
      virtual bool _001DisplayHitTest(const ::point & point, index & iItemParam) override;


      virtual void _001OnAfterSort() override;


      virtual void LayoutHeaderCtrl();

      virtual void auto_arrange(bool bAutoArrange = true) override;

      virtual bool get_auto_arrange() override;

      virtual void on_create_draw_item() override;

      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnCreate);
      virtual void _001OnTimer(::timer * ptimer) override;

      DECL_GEN_SIGNAL(_001OnUpdateListViewAutoArrange);

      DECL_GEN_SIGNAL(_001OnListViewAutoArrange);


      virtual bool on_click(const ::user::item & item) override;
      virtual bool on_right_click(const ::user::item & item) override;

      virtual void _001GetSelection(range & selection) override;
      virtual index _001GetCurItem();

      virtual void _001SelectItem(index iItem);

      virtual bool _001IsEditing() override;


      virtual ::count _001GetSelectedItemCount() override;
      virtual ::count _001GetSelectedItems(index_array & ia);


      virtual id _001GetColumnTextId(index iColumn) override;

      virtual void HeaderCtrlLayout();

      virtual index HeaderCtrlMapColumnToOrder(index iColumn);

      virtual bool _001OnHeaderCtrlEndDrag(WPARAM wparam, LPARAM lparam);



      virtual bool _001OnHeaderCtrlEndTrack(WPARAM wparam, LPARAM lparam) override;


      virtual bool _001OnHeaderCtrlTrack(WPARAM wparam, LPARAM lparam) override;


      virtual void _001ShowSubItem(index iSubItem, bool bShow = true) override;
      virtual void DISaveOrder() override;

      virtual void DILoadOrder() override;


      virtual void _001OnSelectionChange() override;

      virtual void _001UpdateColumns();


      virtual void _001RemoveAllColumns();


      virtual void _001CreateImageList(list_column * pcolumn);

      virtual bool _001IsItemVisible(index iItem) override;

      virtual void _001ClearSelection();

      virtual void _001SetSelection(const range & range) override;

      virtual void _001AddSelection(const item_range & itemrange) override;

      virtual void set_current_item(const ::user::item & item, const ::action_context & action_context) override;
      virtual ::user::item current_item() override;

      virtual void set_current_item(const index_array & iaSel, const ::action_context & action_context) override;
      virtual void get_cur_sel(index_array & iaSel) override;

      virtual void _001SetHighlightRange(range & range) override;

      //void _001SetView(EView eview, bool bLayout = true);

      EView _001GetView() override;


      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_viewport_offset() override;

      virtual bool keyboard_focus_is_focusable() override;

      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);

      virtual void _thread_data_update_visible_subitem() override;

      virtual void defer_create_mesh_data() override;

      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;

      //virtual bool get_client_rect(RECT32 * prect) override;


      virtual void update_icon_list_view_sort();

   };


} // namespace user




