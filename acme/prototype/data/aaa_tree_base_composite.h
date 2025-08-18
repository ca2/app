// From tree_base.h by camilo on 2025-03-29 00:33 <3ThomasBorregaardSorensen!!
#pragma once


#pragma once


#include "acme/prototype/data/tree_base.h"


namespace data
{


   class CLASS_DECL_ACME tree_base_composite :
      virtual public ::data::tree_base
   {
   public:


      ::pointer < tree_base >    m_ptreebase;




      tree_base_composite();
      ~tree_base_composite() override;

      void destroy() override;

      virtual void _insert_tree(tree_base * ptree);

      virtual long long increment_reference_count() override
      {
         return ::matter::increment_reference_count();
      }

      virtual long long decrement_reference_count() override
      {
         return ::matter::decrement_reference_count();
      }


      virtual void erase_all();

      virtual void update_tree();

      virtual ::collection::count _tree_count();
      virtual tree_base * _tree_at(::collection::index iIndex);

      virtual void predicate_each_tree(const ::function < void(tree_base *) > & callback);

      virtual tree_item * _find(const ::item * pitem, ::collection::index * piIndex = nullptr);
      virtual bool _contains(const ::item * pitem);

      virtual bool _contains(const tree_item * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(tree_item * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(tree_item * pitem, const ::action_context & action_context, ::user::element * ptree, const ::int_point & point);

      void _erase(::data::tree_item_ptr_array & itemptra);
      void _erase(tree_item * pitem);
      void _erase(::item * pitem, ::collection::index i = 0);


      //tree_item * __previous() override;
      //tree_item * __next() override;
      //template < typename PRED >
      //void sort_children(PRED pred)
      //{

      //   tree_sort(this, pred);

      //}
      //void sort_children(const ::function < bool(const tree_item * p1, const tree_item * p2) > & functionLess) override;

      virtual tree_item * __get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      virtual tree_item * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel) override;
      virtual ::collection::index _get_proper_item_index(tree_item * pitemParam, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      //      virtual ::collection::count get_proper_item_count() override;

      virtual void _update_levels();

      virtual tree_item * _get_base_item();

      virtual const tree_item * _get_base_item() const;

      virtual tree_item * _insert_item(::item * pitemdataNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      virtual bool _insert_item(tree_item * pitemNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      ::image::image_list * get_tree_image_list() override;

      virtual void _001ExpandItem(tree_item * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(tree_item * pitem);
      virtual void _001SelectItem(tree_item * pitem);

      virtual void _get_selection(::data::tree_item_base_ptr_array & itemptraSelected) const;
      virtual bool _is_selected(const tree_item * pitem) const;
      virtual bool _is_selected(const ::item * pitem) const;

      virtual ::collection::count   _selection_set(::data::tree_item_base_ptr_array & itemptra);
      virtual bool      _selection_set(tree_item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      _selection_set(::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      _selection_set(::collection::index iIndex, ::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);


      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;


      virtual void on_fill_children() override;
      //virtual void start_fill_children();

      virtual void on_tree_layout();

      virtual void fill_children();


      //virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };

   //template < prototype_item ::item * >
   //tree < ::item * >::tree()
   //{

   //   //defer_create_synchronization();

   //   m_bFill = false;

   //   //m_proot = øallocate tree_item();

   //   //if (m_proot == nullptr)
   //   //{

   //   //   throw ::exception(error_no_memory);

   //   //}

   //   this->m_dwState |= ::data::e_tree_item_state_expandable;

   //   this->m_dwState |= ::data::e_tree_item_state_expanded;

   //   this->m_ptree = this;

   //   this->m_pparent = øallocate tree_item();

   //}

   //template < prototype_item ::item * >
   //tree < ::item * >::~tree()
   //{

   //}

   //template < prototype_item ::item * >
   //tree_item * tree < ::item * >::find(const ::item * * pitem, ::collection::index * piIndex)
   //{

   //   ::collection::index iIndex;

   //   if (pitem == nullptr)
   //   {

   //      return nullptr;

   //   }

   //   if (piIndex == nullptr)
   //   {

   //      iIndex = 0;

   //   }
   //   else
   //   {

   //      iIndex = *piIndex;

   //   }

   //   ::pointer<::data::tree_item>pitem = this;

   //   for (; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
   //   {

   //      if (pitem->m_pdataitem == pitem)
   //      {

   //         iIndex--;

   //         if (iIndex < 0)
   //         {

   //            return pitem;

   //         }

   //      }

   //   }

   //   if (piIndex != nullptr)
   //   {

   //      *piIndex = iIndex;

   //   }

   //   return nullptr;

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::contains(const ::item * * pitem)
   //{

   //   return find(pitem) != nullptr;

   //}
   //template < prototype_item ::item * >
   //bool tree < ::item * >::contains(const tree_item * pitemParam)
   //{

   //   return tree_item::contains(pitemParam);

   //   //if (pitemParam == this)
   //   //{

   //   //   return true;

   //   //}
   //   //
   //   //::data::tree_item * pitem = this;

   //   //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
   //   //{

   //   //   if (pitem == pitemParam)
   //   //   {

   //   //      return true;

   //   //   }

   //   //}

   //   //return false;

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001OnTreeDataChange()
   //{

   //   update_levels();

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::erase(::item * * pitem, ::collection::index i)
   //{

   //   tree_item * pitem = find(pitem, &i);

   //   if (pitem == nullptr)
   //   {

   //      return;

   //   }

   //   return erase(pitem);

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::erase(tree_item_ptr_array<::item *> & itemptra)
   //{

   //   for (int i = 0; i < itemptra.get_count(); i++)
   //   {

   //      erase(itemptra[i]);

   //   }

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::erase(tree_item * pitem)
   //{

   //   if (pitem->m_ptree == this)
   //   {

   //      pitem->erase_tree_item();

   //   }

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess)
   //{

   //   this->m_treeitema2.predicate_sort(functionLess);

   //   this->m_treeitema2.predicate_each([](auto pitem) {pitem->clear_cache(); });

   //}

   //template < prototype_item ::item * >
   //::data::tree_item * tree < ::item * >::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   //{

   //   ::collection::index iCount = 0;

   //   if (piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item>pitem = this;

   //   while (pitem && iIndex >= 0)
   //   {

   //      pitem = pitem->get_proper_next(piLevel);

   //      iIndex--;

   //   }

   //   if (iIndex < 0 && pitem)
   //   {

   //      return pitem;

   //   }

   //   if (piCount != nullptr)
   //   {

   //      *piCount = iCount;

   //   }

   //   return nullptr;

   //}

   //template < prototype_item ::item * >
   //::data::tree_item * tree < ::item * >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   //{

   //   if (piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item>pitem = this;

   //   while (pitem && iIndex >= 0)
   //   {

   //      pitem = pitem->get_proper_next(piLevel);

   //      iIndex--;

   //   }

   //   if (iIndex < 0 && pitem)
   //   {

   //      return pitem;

   //   }

   //   return nullptr;

   //}

   //template < prototype_item ::item * >
   //::collection::index tree < ::item * >::get_proper_item_index(::data::tree_item * pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   //{

   //   int iIndex = 0;

   //   ::collection::count iCount = 0;

   //   if (piLevel != nullptr)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item>pitem = get_base_item();

   //   while (pitem != nullptr)
   //   {

   //      pitem = pitem->get_proper_next(piLevel);

   //      if (pitem == pitemParam)
   //      {

   //         if (piCount != nullptr)
   //         {

   //            *piCount += iCount;

   //         }

   //         return iIndex;

   //      }

   //      iIndex++;

   //      iCount++;

   //   }

   //   if (piCount != nullptr)
   //   {

   //      *piCount += iCount;

   //   }

   //   return -1;

   //}


   ////::collection::count tree < ::item * >::get_proper_item_count()
   ////{

   ////   _synchronous_lock synchronouslock(this->synchronization());

   ////   return get_base_item()->get_proper_item_count();

   ////}

   //template < prototype_item ::item * >
   //::data::tree_item * tree < ::item * >::get_base_item()
   //{

   //   return this;

   //}

   //template < prototype_item ::item * >
   //const ::data::tree_item * tree < ::item * >::get_base_item() const
   //{

   //   return this;

   //}
   //template < prototype_item ::item * >

   //::data::tree_item * tree < ::item * >::_____previous()
   //{

   //   return nullptr;

   //}

   //template < prototype_item ::item * >
   //::data::tree_item * tree < ::item * >::_____next()
   //{

   //   return nullptr;

   //}

   //template < prototype_item ::item * >
   //::data::tree_item * tree < ::item * >::insert_item(::item * * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item * pitemRelative, bool bVoidTreeDataChangeEvent)
   //{

   //   if (pitemRelative == nullptr)
   //   {

   //      pitemRelative = this;

   //   }

   //   if (erelativeNewItem == e_relative_replace)
   //   {

   //      if (!contains(pitemRelative))
   //         return nullptr;

   //      pitemRelative->m_pdataitem = pitemdataNew;

   //      return pitemRelative;

   //   }

   //   ::pointer<::data::tree_item>pitemNew = øallocate tree_item();

   //   if (pitemNew == nullptr)
   //      return nullptr;

   //   if (!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
   //   {

   //      return nullptr;

   //   }

   //   pitemNew->m_pdataitem = pitemdataNew;

   //   return pitemNew;

   //}
   //template < prototype_item ::item * >
   //void tree < ::item * >::destroy()
   //{

   //   ::data::data::destroy();
   //   ::data::tree_item::destroy();

   //}
   //template < prototype_item ::item * >
   //void tree < ::item * >::on_insert_tree(tree * ptree)
   //{

   //   m_treea.add(ptree);

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::insert_item(::data::tree_item * pitemNew, enum_relative erelativeNewItem, ::data::tree_item * pitemRelative, bool bVoidTreeDataChangeEvent)
   //{

   //   ::pointer<tree>ptreeNew = pitemNew;

   //   if (ptreeNew)
   //   {

   //      on_insert_tree(ptreeNew);

   //   }

   //   if (pitemRelative == nullptr)
   //   {

   //      pitemRelative = this;

   //   }

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   if (pitemNew == nullptr)
   //   {

   //      return false;

   //   }

   //   if (!contains(pitemRelative))
   //   {

   //      return false;

   //   }

   //   if (erelativeNewItem == e_relative_parent)
   //   {

   //      return false;

   //   }

   //   if (erelativeNewItem == e_relative_last_sibling)
   //   {

   //      if (pitemRelative == this)
   //      {

   //         erelativeNewItem = e_relative_first_child;

   //      }

   //   }

   //   bool bOk = false;

   //   switch (erelativeNewItem)
   //   {
   //   case e_relative_first_child:
   //   {

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;
   //   case e_relative_last_child:
   //   {

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;
   //   case e_relative_previous_sibling:
   //   {

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;
   //   case e_relative_next_sibling:
   //   {

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;
   //   case e_relative_last_sibling:
   //   {

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;
   //   case e_relative_replace:
   //   {

   //      pitemNew->m_dwUser = pitemRelative->m_dwUser;
   //      pitemNew->m_dwMetaData = pitemRelative->m_dwMetaData;
   //      pitemNew->m_dwState = pitemRelative->m_dwState;
   //      pitemNew->m_pdataitem = pitemRelative->m_pdataitem;

   //      pitemNew->m_iLevel = pitemRelative->m_iLevel;

   //      bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

   //   }
   //   break;

   //   case e_relative_macro_record:
   //   {

   //      if (pitemRelative->get_next() != nullptr)
   //      {

   //         bOk = insert_item(pitemNew, ::data::e_relative_first_child, pitemRelative);

   //      }
   //      else
   //      {

   //         bOk = insert_item(pitemNew, ::data::e_relative_last_sibling, pitemRelative);

   //      }

   //   }
   //   break;
   //   default:

   //      throw ::exception(error_not_supported);

   //   }

   //   pitemNew->m_ptree = this;

   //   if (!bVoidTreeDataChangeEvent)
   //   {

   //      _001OnTreeDataChange();

   //   }

   //   return bOk;

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::erase_all()
   //{

   //   this->erase_tree_item_descendants();

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::update_tree()
   //{

   //   _001OnTreeDataChange();

   //}


   ////void tree < ::item * >::sort(index ( * pfnCompare )(const ::pointer<tree_item>&, const ::pointer<tree_item>))

   ////{

   ////   ::pointer<tree_item>pitem = get_base_item();

   ////   while(pitem != nullptr)
   ////   {

   ////      pitem->sort_children(pfnCompare);


   ////      pitem = pitem->get_child_next_or_parent();

   ////   }

   ////}
   //template < prototype_item ::item * >
   //void tree < ::item * >::update_levels()
   //{

   //   ::collection::index iLevel = -1;

   //   ::pointer<tree_item>pitem = get_base_item();

   //   while (pitem != nullptr)
   //   {

   //      pitem->m_iLevel = iLevel;

   //      pitem = pitem->get_child_next_or_parent(&iLevel);

   //   }

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001ExpandItem(::data::tree_item * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   //{


   //}
   //template < prototype_item ::item * >
   //void tree < ::item * >::_001EnsureVisible(::data::tree_item * pitem)
   //{


   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001SelectItem(::data::tree_item * pitem)
   //{


   //}
   //template < prototype_item ::item * >
   //void tree < ::item * >::get_selection(::data::tree_item_ptr_array<::item *> & itemptraSelected) const
   //{


   //}
   //template < prototype_item ::item * >

   //bool tree < ::item * >::is_selected(const ::data::tree_item * pitem) const
   //{


   //   return false;

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::is_selected(const ::item * * pitem) const
   //{


   //   return false;

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
   //{

   //   if (pitem->is_expanded())
   //      return;

   //   pitem->on_fill_children();

   //   if (pitem->get_children_count() > 0)
   //   {
   //      pitem->m_dwState |= ::data::e_tree_item_state_expanded;
   //      pitem->m_dwState |= ::data::e_tree_item_state_expandable;
   //   }

   //   /*      for (::collection::index i = 0; i < m_treeptra.get_count(); i++)
   //         {

   //            m_treeptra[i]._001OnItemExpand(pitem, context);

   //         }*/




   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
   //{

   //   if (!pitem->is_expanded())
   //      return;
   //   if (pitem->get_children_count() > 0)
   //   {
   //      pitem->m_dwState |= ::data::e_tree_item_state_expandable;
   //   }
   //   pitem->m_dwState &= ~::data::e_tree_item_state_expanded;
   //   /*for (::collection::index i = 0; i < m_treeptra.get_count(); i++)
   //   {

   //      m_treeptra[i]._001OnItemCollapse(pitem);

   //   }*/

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   //{


   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::_001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   //{


   //}

   //template < prototype_item ::item * >
   //::collection::count tree < ::item * >::selection_set(::data::tree_item_ptr_array<::item *> & itemptra)
   //{

   //   return 0;

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::selection_set(::item * * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < prototype_item ::item * >
   //bool tree < ::item * >::selection_set(::collection::index iIndex, ::item * * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < prototype_item ::item * >
   //::image::image_list * tree < ::item * >::get_image_list() const
   //{

   //   return nullptr;

   //}


   ////void tree < ::item * >::signal(::signal * psignal)
   ////{

   ////}

   //template < prototype_item ::item * >
   //void tree < ::item * >::handle(::topic * ptopic, ::handler_context * phandlercontext)
   //{

   //   for (auto & ptree : m_treea)
   //   {

   //      ptree->handle(ptopic, phandlercontext);

   //   }

   //}



   ////void tree < ::item * >::handle(::topic * ptopic, ::handler_context * phandlercontext)
   ////{

   ////}


   //template < prototype_item ::item * >
   //void tree < ::item * >::on_fill_children()
   //{

   //}


   ////void tree < ::item * >::start_fill_children()
   ////{

   ////   _synchronous_lock synchronouslock(this->synchronization());

   ////   m_bFill = true;

   ////   fork([this]()
   ////   {

   ////      fill_children();

   ////   });

   ////}

   //template < prototype_item ::item * >
   //void tree < ::item * >::on_tree_layout()
   //{

   //}

   //template < prototype_item ::item * >
   //void tree < ::item * >::fill_children()
   //{

   //   try
   //   {

   //      on_fill_children();

   //   }
   //   catch (...)
   //   {

   //   }


   //   try
   //   {

   //      //auto pgraphics = ::draw2d::create_memory_graphics();

   //      //tree_layout(pgraphics);

   //      on_tree_layout();

   //   }
   //   catch (...)
   //   {

   //   }

   //   m_bFill = false;

   //}


   ////void tree < ::item * >::tree_layout(::draw2d::graphics_pointer & pgraphics)
   ////{

   ////}



} // namespace data

//
//
//inline stream & operator <<(stream & s, const ::data::tree & tree);
//
//inline stream & operator >>(stream & s, ::data::tree & tree);
//
//

