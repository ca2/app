#pragma once


#include "acme/prototype/data/tree.h"
#include "acme/prototype/geometry2d/rectangle.h"
#include "aura/graphics/draw2d/draw2d.h"
#include "acme/prototype/data/listener.h"
#include "acme/user/user/element.h"


namespace user
{


   class scroll_bar;


   class CLASS_DECL_CORE tree_draw_item
   {
   public:
      ::pointer<::data::tree_item_base>                 m_pitem;
      ::pointer < ::draw2d::graphics >             m_pdc;
      ::collection::index                          m_iItem;
      ::collection::index                          m_iIndentation;
      double                                       m_dItemHeight;
      ::double_rectangle                           m_rectangleX;
      ::double_rectangle                           m_rectangle;
   };

   class CLASS_DECL_CORE tree_data_base :
      virtual public ::data::tree_base
   {
   public:

      pointer_array < ::user::tree >         m_usertreea;
      pointer_array < ::user::tree >         m_usertreeaBound;
      ::image::image_list_pointer            m_pimagelist;


      tree_data_base();
      ~tree_data_base() override;


      virtual ::collection::count               get_data_bound_impact_count() const override;
      virtual ::user::element * get_data_bound_impact(::collection::index iImpact) override;


      //virtual void _001OnTreeDataChange() override;


      virtual void on_merge_user_tree(::user::tree * pusertree);
      virtual void on_bind_user_tree(::user::tree * pusertree);
      ::image::image_list * get_tree_image_list() override;


   };


   template < prototype_item ITEM >
   class tree_data:
      virtual public ::data::tree < ITEM >,
      virtual public ::user::tree_data_base
   {
   public:




      tree_data();
      ~tree_data() override;




      ::image::image_list * get_tree_image_list() override;


      void _001OnItemExpand(::data::tree_item_base * ptreeitembase, const ::action_context & action_context) override;
      void _001OnItemCollapse(::data::tree_item_base * ptreeitembase, const ::action_context & action_context) override;
      void _001OnOpenItem(::data::tree_item_base * ptreeitembase, const ::action_context & action_context) override;
      virtual void _001OnItemContextMenu(::data::tree_item_base * ptreeitembase, const ::action_context & action_context,::user::tree * ptree,const ::int_point & point);


      void _001ExpandItem(::data::tree_item < ITEM > * pitem, const ::action_context & action_context,bool bExpand = true,bool bRedraw = true,bool bLayout = true) override;
      void _001EnsureVisible(::data::tree_item < ITEM > * pitem) override;
      void _001SelectItem(::data::tree_item < ITEM > * pitem) override;

      void get_selection(::data::tree_item_ptr_array < ITEM > & itemptraSelected) const override;
      bool is_selected(const ::data::tree_item < ITEM > * pitem) const override;
      bool is_selected(const ITEM * pitem) const override;

      ::collection::count   selection_set(::data::tree_item_ptr_array < ITEM > & itemptraSelected) override;
      bool      selection_set(::data::tree_item < ITEM > * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      bool      selection_set(ITEM * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;
      bool      selection_set(::collection::index iIndex,ITEM * pitem,bool bIfNotInSelection = false,bool bIfParentInSelection = false) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      void on_fill_children() override;

      void on_tree_layout() override;



   };


   template < prototype_item ITEM >
   tree_data < ITEM >::tree_data()
   {



   }

   template < prototype_item ITEM >
   tree_data < ITEM >::~tree_data()
   {

   }






   //template < prototype_item ITEM >
   //void tree_data < ITEM >::_001OnTreeDataChange()
   //{

   //   ::data::tree<ITEM>::_001OnTreeDataChange();

   //}





   template < prototype_item ITEM >
   void tree_data < ITEM >::_001OnItemExpand(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {

      if (ptreeitembase->is_expanded())
      {

         return;

      }

      ptreeitembase->on_fill_children();

      if (ptreeitembase->get_children_count() > 0)
      {

         ptreeitembase->m_etreeitemstate |= ::data::e_tree_item_state_expanded;

         ptreeitembase->m_etreeitemstate |= ::data::e_tree_item_state_expandable;

      }

      /*      for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

      m_usertreea[i]->_001OnItemExpand(pitem, context);

      }*/




   }

   template < prototype_item ITEM >
   void tree_data < ITEM >::_001OnItemCollapse(::data::tree_item_base * ptreeitembase, const ::action_context & context)
   {

      if (!ptreeitembase->is_expanded())
         return;
      if (ptreeitembase->get_children_count() > 0)
      {
         ptreeitembase->m_etreeitemstate |= ::data::e_tree_item_state_expandable;
      }
      ptreeitembase->m_etreeitemstate -= ::data::e_tree_item_state_expanded;
      /*for (::collection::index i = 0; i < m_usertreea.get_count(); i++)
      {

      m_usertreea[i]->_001OnItemCollapse(pitem);

      }*/

   }


   template < prototype_item ITEM >
   ::image::image_list * tree_data < ITEM >::get_tree_image_list()
   {

      return ::user::tree_data_base::get_tree_image_list();

   }


   template < prototype_item ITEM >
   void tree_data < ITEM >::on_fill_children()
   {

   }



} // namespace aura



