#pragma once


#include "core/user/simple/_.h"
#include "core/user/user/_.h"
#include "aura/user/user/scroll.h"
#include "aura/user/user/range.h"
#include "acme/prototype/mathematics/int_biunique.h"


namespace user
{


   enum enum_cache_hinting
   {

      e_cache_hinting_none,
      e_cache_hinting_subitem_color_per_theme_and_state = 1 << 0,

   };

   DECLARE_ENUMERATION(e_cache_hinting, enum_cache_hinting);

   class CLASS_DECL_CORE mesh :
      virtual public ::user::scroll_base
   {
   protected:


      /// Hovering items select them? Imply single-click open.
      bool                             m_bHoverSelect2;
      int                              m_iTimerHoverSelect;


   public:


      enum EImpact
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
         e_element_image,
         e_element_text,
         e_element_sub_item

      };


      enum enum_group_element
      {

         e_group_element_image,
         e_group_element_item_text,

      };


      class CLASS_DECL_CORE mesh_layout:
         virtual public ::object
      {
      public:


         mesh_layout();
         ~mesh_layout() override;


         index_array       m_iaDisplayToStrict;
         int               m_iWidth;

      };

      class CLASS_DECL_CORE icon_layout:
         virtual public ::object
      {
      public:


         index_biunique    m_iaDisplayToStrict;


         icon_layout();
         ~icon_layout() override;


      };


      static const enum_message MESSAGE_ENDCOLUMNHEADERDRAG;
      static const enum_message MESSAGE_COLUMNHEADERTRACK;
      static const enum_message MESSAGE_ENDCOLUMNHEADERTRACK;

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
         ::collection::index    m_iSubItem;
         bool     m_bAscendent;
      };

      class CSortInfo
      {
      public:


         raw_array_base < CSortInfoItem > m_itema;


      };

      //int_size                                   m_sizeTotal;
      ::int_size                                   m_sizePage;
      ::user::list *                               m_plist; // should be set to this ::user::list if this is a list_base

      int                                          m_iDefaultColumnWidth;
      index_map_base < int >                            m_mapColumnWidth;

      CSortInfo                                    m_sortinfo;
      ::int_size                                   m_sizeMaximumImage;

      EFilterState                                 m_efilterstate;
      index_biunique *                             m_piaFilterIcon;
      index_array *                                m_piaFilterMesh;

      /// Are items selectable?
      bool                                         m_bMeshSelect;


      /// Is multiple selection of items enabled?
      bool                                         m_bMultiSelect;

      bool                                         m_bDrag;
      ::collection::index                                        m_iItemLButtonDown;

      // Sort
      bool                                         m_bSort;
      bool                                         m_bEmboss;


      bool                                         m_bSortEnable;
      ::pointer<mesh_cache_interface>             m_pmeshcache;
      e_cache_hinting                              m_ecachehinting;

      ::pointer<draw2d::graphics_extension>        m_pgraphicsextension;

      ::collection::index                                        m_iClick;
      bool                                         m_bLButtonDown;
      int_point                                    m_pointLButtonDown1;
      int_point                                    m_pointLButtonDown2;
      class ::time                                   m_timeLButtonDownStart1;
      class ::time                                   m_timeLButtonDownStart2;
      ::collection::index                                        m_iDisplayItemLButtonDown1;
      ::collection::index                                        m_iDisplayItemLButtonDown2;

      ::collection::index                                        m_iDisplayItemFocus;

      bool                                         m_bLockImpactUpdate;
      int                                          m_iItemWidth;

      //index                                        m_iDisplayItemHover;
      //index                                        m_iSubItemHover;

      ::collection::index                                        m_iLastItemSel;
      ::collection::index                                        m_iLastSubItemSel;
      ::collection::index                                        m_iItemEnter;
      ::collection::index                                        m_iSubItemEnter;
      ::collection::index                                        m_iMouseFlagEnter;
      ::collection::index                                        m_iItemSel;
      ::collection::index                                        m_iSubItemSel;

      range                                        m_rangeSelection;
      range                                        m_rangeHighlight;

      ::collection::index                                        m_iShiftFirstSelection;
      uptr                                         m_uiLButtonDownFlags;
      uptr                                         m_uiLButtonUpFlags;
      int_point                                    m_pointLButtonUp;
      unsigned int                                        m_uiRButtonUpFlags;
      int_point                                    m_pointRButtonUp;
      ::regular_expression_pointer                 m_pregexFilter1;
      int                                          m_iFilter1Step;
      bool                                         m_bFilter1;

      bool                                         m_bTopText;
      string                                       m_strTopText;
      ::int_rectangle                              m_rectangleTopText;
      ::pointer<mesh_data>                        m_pmeshdata;
//      ::write_text::font_pointer                 m_pfont;
      //    ::write_text::font_pointer             m_pfontHover;
      ::draw2d::pen_pointer                        m_ppenFocused;
      ::draw2d::pen_pointer                        m_ppenHighlight;
      EImpact                                      m_eview;
      flags < enum_flag >                          m_flags;
      ::pointer<icon_layout>                      m_piconlayout;
      ::pointer<mesh_layout>                      m_pmeshlayout;
      //::pointer < ::mutex >                            m_pmutex;


      ::collection::index                                        m_iTopDisplayIndex;
      ::collection::index                                        m_iTopGroup;
      ::collection::count                                      m_nDisplayCount;
      ::collection::count                                      m_nItemCount;
      ::collection::count                                      m_nGroupCount;
      ::collection::count                                      m_nColumnCount;


      ::collection::count                                      m_nGridItemCount;
      ::collection::count                                      m_nGridColumnCount;

      ::image::image_list_pointer                      m_pimagelistGroup;
      ::image::image_list_pointer                      m_pimagelistGroupHover;
      bool                                         m_bGroup;
      bool                                         m_bLateralGroup;
      int                                          m_iLateralGroupWidth;
      int                                          m_iGroupMinHeight;
      ::collection::index                                        m_iGroupHover;

      //draw_mesh_item *                 m_pdrawmeshitem;

      ::pointer < ::mutex >                                      m_pmutexData;

      bool                                         m_bAutoCreateMeshHeader;
      bool                                         m_bAutoCreateMeshData;

      // This member is only valid if m_pmeshdata is simple_mesh_data object
      // (i.e. a simple_mesh_data class object or a simple_mesh_data based class object)
      // It should match the pointer of m_pmeshdata and yes, may kind
      // of memory waste and dangling appendix in some (or many cases).
      ::pointer<simple_mesh_data>               m_psimplemeshdata;


      int                                          m_iLeftMargin;
      int                                          m_iTopMargin;

      index_map_base < ::pointer<mesh_item >>          m_mapItem;
      index_map_base < ::pointer<mesh_group >>         m_mapGroup;
      ::task_pointer                               m_ptaskHoverSelect;
      class ::time                                   m_timeLastHoverSelect;
      bool                                         m_bPendingHoverSelect;
      ::logic::boolean                                      m_bPendingColumnLayout;
      ::logic::boolean                                      m_bPendingColumnUpdate;


      mesh();
      ~mesh() override;





      //virtual int _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics, ::collection::index iItem, ::collection::index iSubItem);
      //int _001CalcItemWidth(::draw2d::graphics_pointer & pgraphics,::write_text::font * pfont, ::collection::index iItem, ::collection::index iSubItem);


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();


      void install_message_routing(::channel * pchannel) override;

      virtual mesh_data * GetDataInterface();
      
      //using interaction::update_hover;
      //::item_pointer update_hover(::user::mouse * pmouse, ::user::e_zorder ezorder) override;

      ::item_pointer on_hit_test(const ::int_point& point, e_zorder ezorder) override;

      //::write_text::font * _001GetFont();
      //::write_text::font * _001GetFontHover();
      virtual ::draw2d::pen * _001GetPenFocused();
      virtual ::draw2d::pen * _001GetPenHighlight();
      virtual void PreSubClassWindow() override;
      virtual void _OnDraw(::draw2d::graphics_pointer & pgraphics);
      virtual void _001MaximizeColumnWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iColumn);
      virtual void _001CalculateItemHeight(::draw2d::graphics_pointer & pgraphics);
      virtual int _001CalcSubItemWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iItem, ::collection::index iSubItem);
      virtual int _001CalcColumnWidth(::draw2d::graphics_pointer& pgraphics, ::collection::index iColumn);
      virtual int _001CalcMeshWidth(::draw2d::graphics_pointer& pgraphics);
      virtual void _001OnSort();


      virtual bool does_drag_reorder();

      virtual void _001OnBeforeDeleteRange(range& range);
      virtual void _001OnDeleteRange(range& range);
      virtual void _001DeleteRange(range& range);

      // Sort
      virtual ::std::strong_ordering _001Compare(::collection::index iItem1, ::collection::index iItem2);
      virtual ::std::strong_ordering _002Compare(::collection::index iItem1, ::collection::index iItem2, ::collection::index iSubItem);
      virtual ::std::strong_ordering _001DisplayCompare(::collection::index iDisplayItem1, ::collection::index iDisplayItem2);


      virtual bool is_valid_display_item(::collection::index iDisplayItem);
      virtual bool is_valid_strict_item(::collection::index iStrictItem);


      virtual void on_hover_select_timer();

      virtual void _task_hover_select();




      virtual ::int_size get_item_size();

      virtual void _001OnSort(::collection::index iSubItem);
      virtual void _001OnMeshHeaderItemClick(::collection::index iHeaderItem);
      virtual void _001OnMeshHeaderItemDblClk(::collection::index iHeaderItem);
      virtual void Filter1(const ::scoped_string & scopedstr);
      virtual bool Filter1Step();


      virtual ::collection::index _001CalcDisplayTopIndex();
      virtual ::collection::count _001CalcDisplayItemCount();
      virtual int _001GetGroupHeight(::collection::index iGroup);


      virtual void FilterInclude(::int_array_base & array);
      virtual void FilterInclude(::collection::index iItem);
      virtual void FilterExcludeAll();
      virtual void FilterClose();
      virtual void FilterApply();
      virtual void FilterBegin();
      virtual ::collection::index strict_to_display(::collection::index iStrict);
      virtual ::collection::index display_to_strict(::collection::index iDisplay);
      virtual void select_item(::collection::index iItem, ::collection::index iSubItem);
      virtual void highlight_item(::collection::index iItem,bool bRedraw);
      virtual void erase_selection();
      virtual bool on_erase_item(::collection::index iItem);
      virtual bool erase_item(::collection::index iItem,bool bRedraw = true);
      virtual void ensure_item_visible(::collection::index iItem,bool bRedraw = true);
      virtual void ensure_item_visible(::collection::index iItem, range& rangeRedraw);
      virtual void scroll_to_item(::collection::index iItem,bool bRedraw = true);
      virtual ::collection::index data_key_to_column_key(const ::scoped_string & strDataKey);
      virtual ::collection::index data_key_to_sub_item(const ::scoped_string & strDataKey);
      virtual bool has_data_key(const ::scoped_string & strDataKey);
      virtual void get_data_selection(const ::scoped_string & scopedstrDataKey,::string_array_base & straSelection);

      virtual void set_data_interface(mesh_data * pinterface);
      virtual void cache_hint();
      virtual void set_cache_interface(mesh_cache_interface * pinterface);
      virtual void _001ShowTopText(bool bShow = true);
      virtual void _001LayoutTopText(::draw2d::graphics_pointer & pgraphics);
      virtual void _001SetTopText(const ::wide_character * pcwsz);

      virtual bool DIDDXHeaderLayout(bool bSave);


      virtual void data_get_DisplayToStrict();
      virtual void data_set_DisplayToStrict();
      virtual atom data_get_current_sort_id();
      virtual atom data_get_sort_id(EImpact eview);
      virtual atom data_get_current_mesh_layout_id();

      virtual bool query_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag);
      virtual bool do_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag);
      virtual bool defer_drop(::collection::index iDisplayDrop, ::collection::index iDisplayDrag);



      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      //virtual void  _001DrawGroups(::draw2d::graphics_pointer & pgraphics, ::collection::index iGroupFirst, ::collection::index iGroupLast, ::collection::index iItemFirst, ::collection::index iItemLast);
      virtual void  _001DrawGroups(::draw2d::graphics_pointer & pgraphics, ::collection::index iGroupFirst, ::collection::index iGroupLast);

      virtual void  _001DrawGroup(draw_mesh_group * pdrawgroup);

      virtual void  _001DrawItems(::draw2d::graphics_pointer & pgraphics, ::collection::index iItemFirst, ::collection::index iItemLast);

      virtual void  _001DrawItem(draw_mesh_item * pdrawitem);

      virtual void  _001DrawSubItem(draw_mesh_subitem * pdrawsubitem);



      virtual ::pointer<mesh_item>& get_item(::collection::index iItem);
      virtual ::pointer<mesh_subitem>& get_subitem(::collection::index iItem, ::collection::index iSubItem);
      virtual ::pointer<mesh_subitem>& get_subitem(mesh_item * pitem, ::collection::index iSubItem);


      virtual void  _001GetSubItemImage(mesh_subitem * psubitem);

      virtual void  _001GetSubItemText(mesh_subitem * psubitem);

      virtual void  _001SetSubItemText(mesh_subitem * psubitem);

      virtual void  _001GetSubItemColor(mesh_subitem * psubitem);

      virtual void  _001SearchGetSubItemText(mesh_subitem * psubitem);

      virtual ::collection::count  _001GetGroupItemCount(::collection::index iGroup);

      virtual ::collection::count  _001GetGroupMetaItemCount(::collection::index iGroup);

      virtual void  _001GetGroupItemText(mesh_group * pgroup);

      virtual void  _001GetGroupImage(mesh_group * pgroup);

      virtual ::collection::count  _001GetColumnCount();

      virtual void  draw_framing(::draw2d::graphics_pointer & pgraphics);

      virtual ::pointer<::user::mesh_data> create_mesh_data();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void erase_columns();
      virtual void insert_columns();
      virtual void on_insert_columns();


      virtual void set_pending_column_layout();
      virtual void set_pending_column_update();


      virtual void on_column_update();
      virtual void on_update_item_count();
      bool on_impact_update() override;


      void on_would_change_total_size(::user::enum_layout elayout = ::user::e_layout_sketch) override;


      virtual void  _001OnInitialize();


      virtual void  _001GetGroupRect(draw_mesh_group * pgroup);
      virtual void  index_item_rectangle(draw_mesh_item * pitem);
      virtual void  _001GetSubItemRect(draw_mesh_subitem * psubitem);
      virtual void  index_element_rectangle(draw_mesh_subitem * psubitem,::user::mesh::enum_element eelement);
      virtual void  _001GetGroupElementRect(draw_mesh_group * pgroup, ::user::mesh::enum_group_element egrouplement);

      virtual bool  _001SetColumnWidth(::collection::index iColumn,int iWidth);

      //virtual void  _001GetColumnWidth(draw_mesh_item * pdrawitem);

      virtual ::collection::index  sub_item_to_order(::collection::index iSubItem);

      virtual ::collection::index  _001MapOrderToSubItem(::collection::index iOrder);

      virtual ::collection::index  _001MapOrderToColumn(::collection::index iOrder);

      virtual ::collection::index  _001MapColumnToOrder(::collection::index iColumn);

      virtual ::collection::index  _001MapSubItemToColumn(::collection::index iSubItem);

      virtual ::collection::index  _001MapColumnToSubItem(::collection::index iColumn);


      virtual ::collection::count  _001GetItemCount();
      virtual ::collection::count  _001GetGroupCount();


      virtual bool  _001HitTest_(const ::int_point & point, ::collection::index &iItem, ::collection::index&iSubItem, ::collection::index&iListItem,::user::mesh::enum_element &eelement);
      virtual bool  _001HitTest_(const ::int_point & point, ::collection::index&iItem, ::collection::index&iSubItem);
      virtual bool  _001HitTest_(const ::int_point & point, ::collection::index&iItemParam);


      virtual bool  _001DisplayHitTest(const ::int_point & point, ::collection::index&iItem, ::collection::index&iSubItem, ::collection::index&iListItem,::user::mesh::enum_element &eelement);
      virtual bool  _001DisplayHitTest(const ::int_point & point, ::collection::index&iItem, ::collection::index&iSubItem);
      virtual bool  _001DisplayHitTest(const ::int_point & point, ::collection::index&iItemParam);


      virtual void  _001OnAfterSort();


      virtual void  auto_arrange(bool bAutoArrange = true);


      virtual bool  get_auto_arrange();


      //virtual void  on_create_draw_item();


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
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(_001OnUpdateMeshImpactAutoArrange);
      DECLARE_MESSAGE_HANDLER(_001OnMeshImpactAutoArrange);


      virtual void on_timer(::timer * ptimer) override;


      virtual void  enable_hover_select(bool bEnable = true);
      virtual void  on_enable_hover_select();


      bool on_click(::item * pitem, ::user::mouse * pmouse) override;
      virtual bool  _001OnRightClick(uptr uFlags,const ::int_point & point);

      virtual void  get_selection(range& selection);


      virtual bool  _001IsEditing();


      virtual ::collection::count  _001GetSelectedItemCount();

      virtual string  _001GetColumnText(::collection::index iColumn);

      virtual bool  _001OnHeaderCtrlEndTrack(wparam wparam,lparam lparam);


      virtual bool  _001OnHeaderCtrlTrack(wparam wparam,lparam lparam);


      virtual void  _001ShowSubItem(::collection::index iSubItem,bool bShow = true);

      virtual void  DISaveOrder();

      virtual void  DILoadOrder();

      virtual void  on_highlight_change();

      virtual void  on_selection_change();

      virtual bool  _001IsItemVisible(::collection::index iItem);

      virtual void  clear_selection();

      virtual void  set_selection(const range&range);

      virtual void  _001AddSelection(const item_range & itemrange);

      void set_current_item(::item * pitem, const ::action_context & action_context) override;

      ::item_pointer current_item() override;

      virtual void  set_current_item(const index_array & iaSel, const ::action_context & action_context);

      virtual void  get_cur_sel(index_array & iaSel);

      virtual void  _001SetHighlightRange(range & range);

      virtual void _001SetImpact(EImpact eview, bool bLayout = true);

      virtual EImpact  _001GetImpact();


      virtual int get_wheel_scroll_delta() override;

      //virtual void on_context_offset_layout(::draw2d::graphics_pointer & pgraphics) override;
      void on_change_context_offset(::user::enum_layout elayout) override;

      bool keyboard_focus_is_focusable() override;


      virtual void  _thread_data_update_visible_subitem();

      virtual void  defer_create_mesh_data();

      ::double_point get_context_offset(::user::enum_layout elayout = ::user::e_layout_sketch) override;

      ::double_size get_page_size(::user::enum_layout elayout = ::user::e_layout_sketch) override;

      virtual string  _001GetItemId(::collection::index iStrictItem);
      virtual ::collection::index  _001GetItemById(const ::scoped_string & scopedstrChar);


   };



} // namespace user


CLASS_DECL_CORE binary_stream operator <<(binary_stream & s, const ::user::mesh::mesh_layout & layout);
CLASS_DECL_CORE binary_stream operator >>(binary_stream & s, ::user::mesh::mesh_layout & layout);



