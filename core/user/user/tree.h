#pragma once


class image_list;


namespace user
{




   class CLASS_DECL_CORE tree :
      virtual public ::user::interaction
   {
   public:


      //size                           m_sizeTotal;
      int                                       m_iDrawTextFlags;
      __composite(::data::tree)                 m_ptree;
      __reference_array(::data::tree)           m_treeaBound;
      __composite(::data::tree_item_ptr_array)  m_pitemptraSelected;
      ::data::tree_item *                       m_pitemHover;

      ::draw2d::graphics_extension              m_dcextension;
      index                                     m_dwFirstVisibleItem;
      index                                     m_iItemCount;
      UINT                                      m_uiLButtonUpFlags;
      point                                     m_pointLButtonUp;
      ::data::tree_item *                       m_pitemFirstVisible;
      index                                     m_iFirstVisibleItemProperIndex;
      i32                                       m_iCurrentViewWidth;
      //COLORREF                                m_crTextSelected;
      //COLORREF                                m_crTextHighlight;
      //COLORREF                                m_crTextSelectedHighlight;
      u32_array                                 m_dwaItemState;
      __pointer(image_list)                     m_pimagelist;
      index                                     m_iImageCollapse;
      index                                     m_iImageExpand;
      ::draw2d::brush_pointer                   m_brushTextSelected;
      ::draw2d::brush_pointer                   m_brushTextSelectedHighlight;
      ::draw2d::brush_pointer                   m_brushTextHighlight;
      ::draw2d::brush_pointer                   m_brushText;
      ::draw2d::font_pointer                    m_fontTreeItem;
      ::color                                   m_colorTreeBackground;


      bool                                      m_bHoverStart;
      tick                                      m_tickHoverStart;
      tick                                      m_tickHoverEnd;
      BYTE                                      m_uchHoverAlpha;
      BYTE                                      m_uchHoverAlphaInit;
      manual_reset_event                        m_evExpand;
      manual_reset_event                        m_evOpen;
      ptr_array < ::data::tree_item >           m_treeitemaExpand;
      ptr_array < ::data::tree_item >           m_treeitemaOpen;



      tree();
      virtual ~tree();

      void user_tree_common_construct();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawItem(tree_draw_item & data);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual __pointer(::data::tree) find_tree(::data::tree_item * pitem) const;
      virtual __pointer(::data::tree_item) find(::data::item * pitem, index * piIndex = nullptr);
      virtual bool contains(::data::item * pitem);
      virtual bool contains(::data::tree_item * pitem);


      void on_change_view_size() override;

      void _001OnTreeDataChange();
      __pointer(::data::tree_item) CalcFirstVisibleItem(index & iProperIndex);
      virtual i32 _001CalcCurrentViewWidth();
      virtual i32 _001CalcTotalViewWidth();
      virtual i32 _001CalcTotalViewHeight();
      void _001SelectItem(::data::tree_item * pitem);
      count _001GetProperItemCount();
      count _001GetVisibleItemCount();
      void _001SetCollapseImage(const char * pszMatter);
      void _001SetExpandImage(const char * pszMatter);
      void update_tree_hover();
      void update_tree_hover(point point);
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context, ::user::tree * ptree, const ::point & point);
      void _001ExpandItem(::data::tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context);
      virtual bool _001GetItemElementRect(RECT * prect, tree_draw_item & drawitem, ::user::e_tree_element eelement);

      virtual void install_message_routing(::channel * pchannel) override;
      i32 _001GetItemHeight();
      virtual index _001GetIndentation();


      __pointer(::data::tree_item) _001HitTest(const ::point & point, ::user::e_tree_element & eelement);

      virtual bool on_click(const ::user::item & item) override;

      virtual bool on_right_click(const ::user::item & item) override;

      virtual void perform_click();

      virtual void perform_right_click(uptr uiFlags, const ::point & point);

      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_viewport_offset() override;

      __pointer(image_list) get_image_list();

      // Overrides
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnLButtonDblClk);
      DECL_GEN_SIGNAL(_001OnRButtonDown);
      DECL_GEN_SIGNAL(_001OnRButtonUp);
      void _001OnTimer(::timer * ptimer) override;
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnVScroll);
      DECL_GEN_SIGNAL(_001OnHScroll);
      DECL_GEN_SIGNAL(_001OnChangeExperience);


      virtual bool      hover(::data::tree_item * pitem);
      virtual bool      hover(::data::item * pitem, index i = 0);

      virtual bool      is_hover(const ::data::tree_item * pitem) const;
      virtual bool      is_hover(const ::data::item * pitem) const;


      virtual ::count   clear_selection();




      virtual bool      is_selected(const ::data::tree_item * pitem) const;
      virtual bool      is_selected(const ::data::item * pitem) const;

      virtual ::count   selection_add(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_add(::data::tree_item * pitem);
      virtual bool      selection_add(::data::item * pitem, index i = 0);

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual ::count   selection_remove(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_remove(::data::tree_item * pitem);
      virtual bool      selection_remove(::data::item * pitem, index i = 0);


      virtual bool      can_merge(const ::data::tree * ptree) const;
      virtual bool      merge(::data::tree * ptree, bool bBind);

      virtual __pointer(::data::tree_item) get_proper_item(index iIndex, index* piLevel = nullptr);
      virtual __pointer(::data::tree_item) _get_proper_item(index iIndex, index * piLevel = nullptr, index * piCount = nullptr);
      virtual index     get_proper_item_index(::data::tree_item *pitemParam, index * piLevel);
      virtual index     get_proper_item_count();

      virtual void      _001EnsureVisible(::data::tree_item * pitem);

      virtual void update(::update * pupdate) override;

      virtual bool keyboard_focus_is_focusable() override;

      //virtual ::sized get_total_size() override;

      virtual void on_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;


   };


} // namespace user


namespace user
{

   class CLASS_DECL_CORE tree_window :
      virtual public ::user::tree
   {
   public:

      tree_window();
      virtual ~tree_window();

      virtual void install_message_routing(::channel * pchannel);
   };

   typedef show < tree > tree_view;

} // namespace user



