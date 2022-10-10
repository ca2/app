#pragma once


#include "acme/primitive/data/tree.h"


namespace user
{


   class scroll_bar;


   class CLASS_DECL_CORE tree_draw_item
   {
   public:
      ::pointer<::data::tree_item>    m_pitem;
      ::draw2d::graphics *             m_pdc;
      index                            m_iItem;
      index                            m_iIndentation;
      double                           m_dItemHeight;
      ::rectangle_f64                          m_rectangleClient;
      ::rectangle_f64                          m_rectangle;
   };


   class CLASS_DECL_CORE tree_data:
      virtual public ::data::tree
   {
   public:


      pointer_array < ::user::tree >       m_usertreea;
      pointer_array < ::user::tree >       m_usertreeaBound;
      ::pointer<::image_list>          m_pimagelist;



      tree_data();
      ~tree_data() override;



      virtual ::count               get_data_bound_impact_count() const override;
      virtual ::user::primitive *   get_data_bound_impact(index iImpact) override;



      virtual void _001OnTreeDataChange() override;

      virtual void _001OnItemExpand(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemCollapse(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnOpenItem(::data::tree_item * pitem, const ::action_context & action_context) override;
      virtual void _001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & action_context,::user::tree * ptree,const ::point_i32 & point);

      ::image_list * get_image_list() const override;

      virtual void _001ExpandItem(::data::tree_item * pitem, const ::action_context & action_context,bool bExpand = true,bool bRedraw = true,bool bLayout = true) override;
      virtual void _001EnsureVisible(::data::tree_item * pitem) override;
      virtual void _001SelectItem(::data::tree_item * pitem) override;

      virtual void get_selection(::data::tree_item_ptr_array & itemptraSelected) const override;
      virtual bool is_selected(const ::data::tree_item * pitem) const override;
      virtual bool is_selected(const ::data::item * pitem) const override;

      virtual ::count   selection_set(::data::tree_item_ptr_array & itemptra) override;
      virtual bool      selection_set(::data::tree_item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      virtual bool      selection_set(::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      virtual bool      selection_set(index iIndex,::data::item * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_fill_children() override;

      virtual void on_tree_layout() override;

      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);


   };


} // namespace aura



