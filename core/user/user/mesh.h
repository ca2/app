#pragma once


namespace user
{


   class CLASS_DECL_CORE mesh :
      virtual public ::user::scroll_base
   {
   protected:


      /// Hovering items select them? Imply single-click open.
      bool                             m_bHoverSelect2;
      int                              m_iTimerHoverSelect;


   public:

      enum EView
      {
         impact_grid,
         impact_list,
         impact_report,
         impact_icon,
      };

      enum ItemState
      {
         ItemStateHover = 1,
         ItemStateSelected = 2,
      };

      enum enum_flag
      {
         flag_auto_arrange,
         flag_align_to_grid,
      };


      enum enum_element
      {

         e_element_item,
         element_image,
         e_element_text,
         element_sub_item,
         element_group_image,
         element_group_item_text,

      };


      class CLASS_DECL_CORE mesh_layout:
         virtual public ::object
      {
      public:


         mesh_layout();
         virtual ~mesh_layout();


         index_array       m_iaDisplayToStrict;
         i32               m_iWidth;

      };

      class CLASS_DECL_CORE icon_layout:
         virtual public ::object
      {
      public:


         index_biunique    m_iaDisplayToStrict;


         icon_layout();
         virtual ~icon_layout();


      };


      static const ::u32 MESSAGE_ENDCOLUMNHEADERDRAG;
      static const ::u32 MESSAGE_COLUMNHEADERTRACK;
      static const ::u32 MESSAGE_ENDCOLUMNHEADERTRACK;

      // Simple Filter Implementation
      // Base Mesh Side

      enum EFilterState
      {
         FilterStateNoFilter,
         FilterStateSetup,
         FilterStateFilter,
      };


      class CSortInfoItem
      {
      public:
         index    m_iSubItem;
         bool     m_bAscendent;
      };

      class CSortInfo
      {
      public:


         raw_array < CSortInfoItem > m_itema;


      };

      //size_i32                       m_sizeTotal;
      ::size_i32                       m_sizePage;
      ::user::list *                   m_plist; // should be set to this ::user::list if this is a list

      int                              m_iDefaultColumnWidth;
      index_map < int >                m_mapColumnWidth;

      CSortInfo                        m_sortinfo;
      ::size_i32                       m_sizeMaximumItem;

      EFilterState                     m_efilterstate;
      index_biunique *                 m_piaFilterIcon;
      index_array *                    m_piaFilterMesh;

      /// Are items selectable?
      bool                             m_bSelect;


      /// Is multiple selection of items enabled?
      bool                             m_bMultiSelect;

      bool                             m_bDrag;
      index                            m_iItemLButtonDown;

      // Sort
      bool                             m_bSort;
      bool                             m_bEmboss;


      bool                             m_bSortEnable;
      __pointer(mesh_cache_interface)  m_pmeshcache;

      draw2d::graphics_extension       m_dcextension;

      index                            m_iClick;
      bool                             m_bLButtonDown;
      point_i32                        m_pointLButtonDown1;
      point_i32                        m_pointLButtonDown2;
      millis                           m_millisLButtonDownStart1;
      millis                           m_millisLButtonDownStart2;
      index                            m_iDisplayItemLButtonDown1;
      index                            m_iDisplayItemLButtonDown2;

      index                            m_iDisplayItemFocus;

      bool                             m_bLockViewUpdate;
      i32                              m_iItemWidth;

      index                            m_iDisplayItemHover;
      index                            m_iSubItemHover;

      index                            m_iLastItemSel;
      index                            m_iLastSubItemSel;
      index                            m_iItemEnter;
      index                            m_iSubItemEnter;
      index                            m_iMouseFlagEnter;
      index                            m_iItemSel;
      index                            m_iSubItemSel;

      range                            m_rangeSelection;
      range                            m_rangeHighlight;

      index                            m_iShiftFirstSelection;
      uptr                             m_uiLButtonDownFlags;
      uptr                             m_uiLButtonUpFlags;
      point_i32                        m_pointLButtonUp;
      ::u32                            m_uiRButtonUpFlags;
      point_i32                        m_pointRButtonUp;
      ::regular_expression_pointer     m_pregexFilter1;
      i32                              m_iFilter1Step;
      bool                             m_bFilter1;

      bool                             m_bTopText;
      string                           m_strTopText;
      ::rectangle_i32                           m_rectangleTopText;
      __pointer(mesh_data)                    m_pmeshdata;
//      ::write_text::font_pointer                m_pfont;
      //    ::write_text::font_pointer                m_pfontHover;
      ::draw2d::pen_pointer                 m_ppenFocused;
      ::draw2d::pen_pointer                 m_ppenHighlight;
      EView                            m_eview;
      flags < enum_flag >                 m_flags;
      __pointer(icon_layout)           m_piconlayout;
      __pointer(mesh_layout)           m_pmeshlayout;
      //::mutex                            m_mutex;


      index                    m_iTopDisplayIndex;
      index                    m_iTopGroup;
      ::count                  m_nDisplayCount;
      ::count                  m_nItemCount;
      ::count                  m_nGroupCount;
      ::count                  m_nColumnCount;


      ::count                  m_nGridItemCount;
      ::count                  m_nGridColumnCount;

      __pointer(::image_list)            m_pilGroup;
      __pointer(::image_list)            m_pilGroupHover;
      bool                             m_bGroup;
      bool                             m_bLateralGroup;
      i32                              m_iLateralGroupWidth;
      i32                              m_iGroupMinHeight;
      index                    m_iGroupHover;

      draw_mesh_item *                 m_pdrawmeshitem;

      ::mutex                          m_mutexData;

      bool                             m_bAutoCreateMeshHeader;
      bool                             m_bAutoCreateMeshData;

      // This member is only valid if m_pmeshdata is simple_mesh_data object
      // (i.e. a simple_mesh_data class object or a simple_mesh_data based class object)
      // It should match the pointer of m_pmeshdata and yes, may kind
      // of memory waste and dangling appendix in some (or many cases).
      __reference(simple_mesh_data)    m_psimplemeshdata;


      i32                              m_iLeftMargin;
      i32                              m_iTopMargin;



      mesh();
      virtual ~mesh();



      //virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,index iItem,index iSubItem);
      //i32 _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,::write_text::font * pfont,index iItem,index iSubItem);


      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


      virtual void install_message_routing(::channel * pchannel) override;

      virtual mesh_data * GetDataInterface();
      using interaction::update_hover;
      virtual bool update_hover(const ::point_i32& point, bool bAvoidRedraw = true) override;
      //::write_text::font * _001GetFont();
      //::write_text::font * _001GetFontHover();
      virtual ::draw2d::pen * _001GetPenFocused();
      virtual ::draw2d::pen * _001GetPenHighlight();
      virtual void PreSubClassWindow() override;
      virtual void _OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn);
      virtual i32 _001CalcItemWidth(::draw2d::graphics_pointer& pgraphics, index iItem,index iSubItem);
      virtual i32 _001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, index iColumn);
      virtual i32 _001CalcMeshWidth(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnSort();


      virtual bool does_drag_reorder();

      virtual void _001OnBeforeDeleteRange(range& range);
      virtual void _001OnDeleteRange(range& range);
      virtual void _001DeleteRange(range& range);

      // Sort
      virtual index _001Compare(index iItem1,index iItem2);
      virtual index _002Compare(index iItem1,index iItem2,index iSubItem);
      virtual index _001DisplayCompare(index iDisplayItem1,index iDisplayItem2);


      virtual bool is_valid_display_item(index iDisplayItem);
      virtual bool is_valid_strict_item(index iStrictItem);


      virtual void on_hover_select_timer();


      virtual ::size_i32 get_item_size();

      virtual void _001OnSort(index iSubItem);
      virtual void _001OnMeshHeaderItemClick(index iHeaderItem);
      virtual void _001OnMeshHeaderItemDblClk(index iHeaderItem);
      virtual void Filter1(const string & str);
      virtual bool Filter1Step();


      virtual index _001CalcDisplayTopIndex();
      virtual count _001CalcDisplayItemCount();
      virtual i32 _001GetGroupHeight(index iGroup);


      virtual void FilterInclude(int_array & array);
      virtual void FilterInclude(index iItem);
      virtual void FilterExcludeAll();
      virtual void FilterClose();
      virtual void FilterApply();
      virtual void FilterBegin();
      virtual index _001StrictToDisplay(index iStrict);
      virtual index _001DisplayToStrict(index iDisplay);
      virtual void _001Select(index iItem,index iSubItem);
      virtual void _001Highlight(index iItem,bool bRedraw);
      virtual void _001RemoveSelection();
      virtual bool _001OnRemoveItem(index iItem);
      virtual bool _001RemoveItem(index iItem,bool bRedraw = true);
      virtual void _001EnsureVisible(index iItem,bool bRedraw = true);
      virtual void _001EnsureVisible(index iItem, range& rangeRedraw);
      virtual void _001ItemScroll(index iItem,bool bRedraw = true);
      virtual index _001ConfigIdToColumnKey(const ::database::key & key);
      virtual index _001ConfigIdToSubItem(const ::database::key & key);
      virtual bool _001HasConfigId(const ::database::key & key);
      virtual void _001GetSelection(::database::key & key,::database::selection & selection);

      virtual void set_data_interface(mesh_data * pinterface);
      virtual void cache_hint();
      virtual void set_cache_interface(mesh_cache_interface * pinterface);
      virtual void _001ShowTopText(bool bShow = true);
      virtual void _001LayoutTopText(::draw2d::graphics_pointer & pgraphics);
      virtual void _001SetTopText(const widechar * pcwsz);

      virtual bool DIDDXHeaderLayout(bool bSave);


      virtual void data_get_DisplayToStrict();
      virtual void data_set_DisplayToStrict();
      virtual id data_get_current_sort_id();
      virtual id data_get_sort_id(EView eview);
      virtual id data_get_current_mesh_layout_id();

      virtual bool query_drop(index iDisplayDrop,index iDisplayDrag);
      virtual bool do_drop(index iDisplayDrop,index iDisplayDrag);
      virtual bool defer_drop(index iDisplayDrop,index iDisplayDrag);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawGroups(draw_mesh_item * pdrawitem,index iGroupFirst,index iGroupLast,index iItemFirst,index iItemLast);

      virtual void _001DrawGroup(draw_mesh_item * pdrawitem);

      virtual void _001DrawItems(draw_mesh_item * pdrawitem,index iItemFirst,index iItemLast);

      virtual void _001DrawItem(draw_mesh_item * pdrawitem);

      virtual void _001DrawSubItem(draw_mesh_item * pdrawitem);

      virtual void _001GetItemImage(mesh_item * pitem);

      virtual void _001GetItemText(mesh_item * pitem);

      virtual void _001SetItemText(mesh_item * pitem);

      virtual void _001GetItemColor(mesh_item * pitem);

      virtual void _001SearchGetItemText(mesh_item * pitem);

      virtual ::count _001GetGroupItemCount(index iGroup);

      virtual ::count _001GetGroupMetaItemCount(index iGroup);

      virtual void _001GetGroupText(mesh_item * pitem);

      virtual void _001GetGroupImage(mesh_item * pitem);

      //virtual void _001InsertColumns();

      virtual ::count _001GetColumnCount();

      virtual void draw_framing(::draw2d::graphics_pointer & pgraphics);
//      virtual ::user::mesh_header * create_mesh_header();
      virtual __pointer(::user::mesh_data) create_mesh_data();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool _001OnUpdateColumnCount(u32 dwFlags = 0);
      virtual bool _001OnUpdateItemCount(u32 dwFlags = 0);

      virtual void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnInitialize();


      virtual void _001GetGroupRect(draw_mesh_item * pitem);
      virtual void _001GetItemRect(draw_mesh_item * pitem);
      virtual void _001GetSubItemRect(draw_mesh_item * pitem);
      virtual void _001GetElementRect(draw_mesh_item * pitem,::user::mesh::enum_element eelement);

      //virtual void _001OnColumnChange();

      virtual bool _001SetColumnWidth(index iColumn,i32 iWidth);

      virtual void _001GetColumnWidth(draw_mesh_item * pdrawitem);

      virtual index _001MapSubItemToOrder(index iSubItem);

      virtual index _001MapOrderToSubItem(index iOrder);

      virtual index _001MapOrderToColumn(index iOrder);

      virtual index _001MapColumnToOrder(index iColumn);

      virtual index _001MapSubItemToColumn(index iSubItem);

      virtual index _001MapColumnToSubItem(index iColumn);


      virtual ::count _001GetItemCount();
      virtual ::count _001GetGroupCount();


      virtual bool _001HitTest_(const ::point_i32 & point, index &iItem, index&iSubItem, index&iListItem,::user::mesh::enum_element &eelement);
      virtual bool _001HitTest_(const ::point_i32 & point, index&iItem, index&iSubItem);
      virtual bool _001HitTest_(const ::point_i32 & point, index&iItemParam);


      virtual bool _001DisplayHitTest(const ::point_i32 & point, index&iItem, index&iSubItem, index&iListItem,::user::mesh::enum_element &eelement);
      virtual bool _001DisplayHitTest(const ::point_i32 & point, index&iItem, index&iSubItem);
      virtual bool _001DisplayHitTest(const ::point_i32 & point, index&iItemParam);


      virtual void _001OnAfterSort();


      virtual void auto_arrange(bool bAutoArrange = true);


      virtual bool get_auto_arrange();


      virtual void on_create_draw_item();


      DECLARE_MESSAGE_HANDLER(on_message_size);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnHScroll);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateMeshViewAutoArrange);
      DECLARE_MESSAGE_HANDLER(_001OnMeshViewAutoArrange);


      virtual void _001OnTimer(::timer * ptimer) override;


      virtual void enable_hover_select(bool bEnable = true);
      virtual void on_enable_hover_select();


      virtual bool on_click(const ::item & item) override;
      virtual bool _001OnRightClick(uptr uFlags,const ::point_i32 & point);

      virtual void _001GetSelection(range& selection);


      virtual bool _001IsEditing();


      virtual ::count _001GetSelectedItemCount();

      virtual string _001GetColumnText(index iColumn);

      virtual bool _001OnHeaderCtrlEndTrack(wparam wparam,lparam lparam);


      virtual bool _001OnHeaderCtrlTrack(wparam wparam,lparam lparam);


      virtual void _001ShowSubItem(index iSubItem,bool bShow = true);

      virtual void DISaveOrder();

      virtual void DILoadOrder();

      virtual void _001OnSelectionChange();

      virtual bool _001IsItemVisible(index iItem);

      void _001ClearSelection();

      virtual void _001SetSelection(const range&range);

      virtual void _001AddSelection(const item_range & itemrange);

      ::e_status set_current_item(const item & item, const ::action_context & action_context) override;

      item current_item() override;

      virtual void set_current_item(const index_array & iaSel, const ::action_context & action_context);

      virtual void get_cur_sel(index_array & iaSel);

      virtual void _001SetHighlightRange(range & range);

      virtual void _001SetView(EView eview, bool bLayout = true);

      virtual  EView _001GetView();


      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      virtual bool keyboard_focus_is_focusable() const override;


      virtual void _thread_data_update_visible_subitem();

      virtual void defer_create_mesh_data();

      virtual ::point_i32 get_viewport_offset() override;

      //virtual rectangle_i32 get_scroll_margin();

      //virtual bool get_client_rect(RECTANGLE_I32 * prectangle);

      virtual ::size_f64 get_page_size() override;
      //virtual ::size_f64 get_total_size() override;

      virtual string _001GetItemId(index iStrictItem);
      virtual index _001GetItemById(const ::string & pszChar);

   };



} // namespace user



inline stream operator <<(stream & s, const ::user::mesh::icon_layout & layout)
{

      return s << layout.m_iaDisplayToStrict;

}


inline stream operator >>(stream & s, ::user::mesh::icon_layout & layout)
{

      return s >> layout.m_iaDisplayToStrict;

}


inline stream operator <<(stream & s, const ::user::mesh::mesh_layout & layout)
{

   s << layout.m_iaDisplayToStrict;
   return s << layout.m_iWidth;

}


inline stream operator >>(stream & s, ::user::mesh::mesh_layout & layout)
{

   s >> layout.m_iaDisplayToStrict;

   return s >> layout.m_iWidth;

}





