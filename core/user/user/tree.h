#pragma once


class image_list;


namespace user
{




   class CLASS_DECL_CORE tree :
      virtual public ::user::scroll_base
   {
   public:


      //size_i32                                m_sizeTotal;
      ::e_align                                 m_ealignText;
      ::e_draw_text                             m_edrawtext;
      __composite(::data::tree)                 m_ptree;
      __reference_array(::data::tree)           m_treeaBound;
      __composite(::data::tree_item_ptr_array)  m_pitemptraSelected;
      ::data::tree_item *                       m_itemHover;

      ::draw2d::graphics_extension              m_dcextension;
      index                                     m_dwFirstVisibleItem;
      index                                     m_iItemCount;
      ::u32                                     m_uiLButtonUpFlags;
      point_i32                                 m_pointLButtonUp;
      ::data::tree_item *                       m_pitemFirstVisible;
      index                                     m_iFirstVisibleItemProperIndex;
      i32                                       m_iCurrentImpactWidth;
      ::size_i32                                m_sizeItemMaximum;
      //::color::color                               m_colorTextSelected;
      //::color::color                               m_colorTextHighlight;
      //::color::color                               m_colorTextSelectedHighlight;
      u32_array                                 m_dwaItemState;
      __pointer(::image_list)                   m_pimagelist;
      index                                     m_iImageCollapse;
      index                                     m_iImageExpand;
      ::draw2d::brush_pointer                   m_pbrushTextSelected;
      ::draw2d::brush_pointer                   m_pbrushTextSelectedHighlight;
      ::draw2d::brush_pointer                   m_pbrushTextHighlight;
      ::draw2d::brush_pointer                   m_pbrushText;
      ::write_text::font_pointer                m_pfontTreeItem;
      status < ::color::color >          m_colorTreeBackground;


      bool                                      m_bHoverStart;
      ::duration                                    m_durationHoverStart;
      ::duration                                    m_durationHoverEnd;
      byte                                      m_uchHoverAlpha;
      byte                                      m_uchHoverAlphaInit;
      manual_reset_event                        m_evExpand;
      manual_reset_event                        m_evOpen;
      ptr_array < ::data::tree_item >           m_treeitemaExpand;
      ptr_array < ::data::tree_item >           m_treeitemaOpen;



      tree();
      virtual ~tree();



      inline ::core::application* get_application() const { return m_pcontext ? m_pcontext->m_pcoreapplication : nullptr; }
      inline ::core::session* get_session() const { return m_pcontext ? m_pcontext->m_pcoresession : nullptr; }
      inline ::core::system* get_system() const { return m_psystem ? m_psystem->m_pcoresystem : nullptr; }


      void user_tree_common_construct();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawItem(tree_draw_item & data);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual __pointer(::data::tree) find_tree(::data::tree_item * pitem) const;
      virtual __pointer(::data::tree_item) find(::data::item * pitem, index * piIndex = nullptr);
      virtual bool contains(::data::item * pitem);
      virtual bool contains(::data::tree_item * pitem);


      void on_change_view_size(::draw2d::graphics_pointer & pgraphics) override;

      void _001OnTreeDataChange();
      __pointer(::data::tree_item) CalcFirstVisibleItem(index & iProperIndex);
      virtual i32 _001CalcCurrentImpactWidth();
      virtual i32 _001CalcTotalImpactWidth();
      virtual i32 _001CalcTotalImpactHeight();
      void _001SelectItem(::data::tree_item * pitem);
      count _001GetProperItemCount();
      count _001GetVisibleItemCount();
      void _001SetCollapseImage(const ::string & pszMatter);
      void _001SetExpandImage(const ::string & pszMatter);
      void update_tree_hover();
      void update_tree_hover(point_i32 point);
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context, ::user::tree * ptree, const ::point_i32 & point);
      void _001ExpandItem(::data::tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context);
      virtual bool _001GetItemElementRect(RECTANGLE_I32 * prectangle, tree_draw_item & drawitem, ::user::enum_tree_element eelement);

      void install_message_routing(::channel * pchannel) override;
      virtual double _001GetItemHeight();
      virtual index _001GetIndentation();


      __pointer(::data::tree_item) _001HitTest(const ::point_i32 & point, ::user::enum_tree_element & eelement);

      virtual bool on_click(const ::item & item) override;

      virtual bool on_right_click(const ::item & item) override;

      virtual void perform_click();

      virtual void perform_right_click(uptr uFlags, const ::point_i32 & point);

      virtual i32 get_wheel_scroll_delta() override;

      virtual void on_change_viewport_offset(::draw2d::graphics_pointer & pgraphics) override;

      __pointer(::image_list) get_image_list();

      // Overrides
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      void _001OnTimer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnVScroll);
      DECLARE_MESSAGE_HANDLER(_001OnHScroll);
      DECLARE_MESSAGE_HANDLER(_001OnChangeExperience);


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

      virtual ::count   selection_erase(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_erase(::data::tree_item * pitem);
      virtual bool      selection_erase(::data::item * pitem, index i = 0);


      virtual bool      can_merge(const ::data::tree * ptree) const;
      virtual bool      merge(::data::tree * ptree, bool bBind);

      virtual __pointer(::data::tree_item) get_proper_item(index iIndex, index* piLevel = nullptr);
      virtual __pointer(::data::tree_item) _get_proper_item(index iIndex, index * piLevel = nullptr, index * piCount = nullptr);
      virtual index     get_proper_item_index(::data::tree_item *pitemParam, index * piLevel);
      virtual index     get_proper_item_count();

      virtual void      _001EnsureVisible(::data::tree_item * pitem);

      virtual void handle(::topic * psubject, ::context * pcontext) override;

      virtual bool keyboard_focus_is_focusable() const override;

      //virtual ::size_f64 get_total_size() override;

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

      void install_message_routing(::channel * pchannel) override;
   };

   typedef show < tree > tree_view;

} // namespace user



