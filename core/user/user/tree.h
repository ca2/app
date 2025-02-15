#pragma once


#include "acme/prototype/collection/raw_pointer_array.h"
#include "aura/user/user/scroll_base.h"
#include "acme/parallelization/manual_reset_happening.h"


class image_list;


namespace user
{


   class CLASS_DECL_CORE tree :
      virtual public ::user::scroll_base
   {
   public:


      //int_size                                m_sizeTotal;
      ::e_align                                 m_ealignText;
      ::e_draw_text                             m_edrawtext;
      ::pointer<::data::tree>                   m_ptreedata;
      ::pointer_array < ::data::tree >          m_treeaBound;
      ::pointer<::data::tree_item_ptr_array>    m_pitemptraSelected;
      ::data::tree_item *                       m_pitemHover;

      ::pointer<::draw2d::graphics_extension>   m_pgraphicsextension;
      ::collection::index                                     m_dwFirstVisibleItem;
      ::collection::index                                     m_iItemCount;
      unsigned int                                     m_uiLButtonUpFlags;
      int_point                                 m_pointLButtonUp;
      ::data::tree_item *                       m_pitemFirstVisible;
      ::collection::index                                     m_iFirstVisibleItemProperIndex;
      int                                       m_iCurrentImpactWidth;
      ::int_size                                m_sizeItemMaximum;
      //::color::color                               m_colorTextSelected;
      //::color::color                               m_colorTextHighlight;
      //::color::color                               m_colorTextSelectedHighlight;
      unsigned_int_array                                 m_dwaItemState;
      ::image::image_list_pointer                    m_pimagelist;
      ::collection::index                                     m_iImageCollapse;
      ::collection::index                                     m_iImageExpand;
      ::collection::index                                     m_iImageCollapseDark;
      ::collection::index                                     m_iImageExpandDark;
      ::draw2d::brush_pointer                   m_pbrushTextSelected;
      ::draw2d::brush_pointer                   m_pbrushTextSelectedHighlight;
      ::draw2d::brush_pointer                   m_pbrushTextHighlight;
      ::draw2d::brush_pointer                   m_pbrushText;
      ::write_text::font_pointer                m_pfontTreeItem;
      status < ::color::color >                 m_colorTreeBackground;

      bool                                      m_bPendingDrawingObjectsUpdate;

      bool                                      m_bHover;
      class ::time                              m_timeHoverStart;
      int                                     m_iHoverAlpha;
      int                                     m_iHoverAlphaInit;
      class ::time                              m_timeLeaveStart;
      int                                     m_iLeaveAlphaInit;

      manual_reset_happening                        m_happeningExpand;
      manual_reset_happening                        m_happeningOpen;
      raw_pointer_array < ::data::tree_item >   m_treeitemaExpand;
      raw_pointer_array < ::data::tree_item >   m_treeitemaOpen;



      tree();
      ~tree() override;


      // ::core::application* get_app();
      // ::core::session* get_session();
      // ::core::system* get_system();


      void user_tree_common_construct();

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      virtual void _001DrawItem(tree_draw_item & data);

      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual ::pointer<::data::tree>find_data_tree(::data::tree_item * pitem) const;
      virtual ::pointer<::data::tree_item>find_data_tree_item(::data::item * pitem, ::collection::index * piIndex = nullptr);
      virtual bool contains(::data::item * pitem);
      virtual bool contains(::data::tree_item * pitem);

      void update_drawing_objects();


      void on_would_change_total_size(::user::enum_layout elayout = ::user::e_layout_sketch) override;


      void _001OnTreeDataChange();
      ::pointer<::data::tree_item>CalcFirstVisibleItem(::collection::index & iProperIndex);
      virtual void _001CalculateItemHeight(::draw2d::graphics_pointer & pgraphics);
      virtual int _001CalcCurrentImpactWidth();
      virtual int _001CalcTotalImpactWidth(::draw2d::graphics_pointer & pgraphics);
      virtual int _001CalcTotalImpactHeight();
      void _001SelectItem(::data::tree_item * pitem);
      ::collection::count _001GetProperItemCount();
      ::collection::count _001GetVisibleItemCount();
      void _001SetCollapseImage(const ::string & pszMatter);
      void _001SetExpandImage(const ::string & pszMatter);
      void _001SetCollapseImageDark(const ::string & pszMatter);
      void _001SetExpandImageDark(const ::string & pszMatter);
      void update_tree_hover();
      void update_tree_hover(int_point point);
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context, ::user::tree * ptree, const ::int_point & point);
      void _001ExpandItem(::data::tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context);
      virtual bool _001GetItemElementRect(::int_rectangle * prectangle, tree_draw_item & drawitem, ::user::enum_tree_element eelement);

      void install_message_routing(::channel * pchannel) override;
      virtual double _001GetItemHeight();
      virtual ::collection::index _001GetIndentation();


      ::pointer<::data::tree_item>_001HitTest(const ::int_point & point, ::user::enum_tree_element & eelement);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;

      bool on_right_click(::item * pitem, ::user::mouse * pmouse) override;

      virtual void perform_click();

      virtual void perform_right_click(uptr uFlags, const ::int_point & point);

      virtual int get_wheel_scroll_delta() override;

      //void on_context_offset_layout(::draw2d::graphics_pointer & pgraphics) override;

      void on_change_context_offset(::user::enum_layout elayout) override;

      ::image::image_list_pointer get_image_list();

      
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_double_click);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_right_button_up);
      void on_timer(::timer * ptimer) override;
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
      DECLARE_MESSAGE_HANDLER(on_message_scroll_x);
      DECLARE_MESSAGE_HANDLER(_001OnChangeExperience);


      virtual bool      hover(::data::tree_item * pitem);
      virtual bool      hover(::data::item * pitem, ::collection::index i = 0);

      virtual bool      is_hover(const ::data::tree_item * pitem) const;
      virtual bool      is_hover(const ::data::item * pitem) const;


      virtual ::collection::count   clear_selection();




      virtual bool      is_selected(const ::data::tree_item * pitem) const;
      virtual bool      is_selected(const ::data::item * pitem) const;

      virtual ::collection::count   selection_add(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_add(::data::tree_item * pitem);
      virtual bool      selection_add(::data::item * pitem, ::collection::index i = 0);

      virtual ::collection::count   selection_set(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_set(::data::tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::collection::index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);

      virtual ::collection::count   selection_erase(::data::tree_item_ptr_array & itemptra);
      virtual bool      selection_erase(::data::tree_item * pitem);
      virtual bool      selection_erase(::data::item * pitem, ::collection::index i = 0);


      virtual bool      can_merge(const ::data::tree * ptree) const;
      virtual bool      merge(::data::tree * ptree, bool bBind);

      virtual ::pointer<::data::tree_item>get_proper_item(::collection::index iIndex, ::collection::index * piLevel = nullptr);
      virtual ::pointer<::data::tree_item>_get_proper_item(::collection::index iIndex, ::collection::index * piLevel = nullptr, ::collection::index * piCount = nullptr);
      virtual ::collection::index     get_proper_item_index(::data::tree_item *pitemParam, ::collection::index * piLevel);
      virtual ::collection::index     get_proper_item_count();

      virtual void      _001EnsureVisible(::data::tree_item * pitem);

      void handle(::topic * ptopic, ::context * pcontext) override;

      bool keyboard_focus_is_focusable() override;

      //virtual ::double_size get_total_size() override;

      //void on_context_offset(::draw2d::graphics_pointer & pgraphics) override;


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

   typedef show < tree > tree_impact;

} // namespace user



