// Created by camilo on 2025-03-28 22:20 <3ThomasBorregaardSorensen!!
#pragma once


#pragma once


#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/data.h"
#include "acme/prototype/data/tree_item_base.h"


namespace data
{


   class CLASS_DECL_ACME tree_base :
      virtual public ::data::data,
      virtual public ::data::tree_item_base
   {
   public:


      //pointer_array < tree_base >                    m_treea;
      //::pointer<tree_item_base>               m_proot;
      bool                                m_bFill;
      index_array                         m_iaLevelNext;




      tree_base();
      ~tree_base() override;


      virtual ::pointer<::data::tree_item_base> create_tree_item() = 0;

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

      virtual ::collection::count _tree_count() = 0;
      virtual tree_base * _tree_at(::collection::index iIndex) = 0;

      virtual void predicate_each_tree(const ::function < void(tree_base *) > & callback);

      virtual tree_item_base * _find(const ::data::item * pitem, ::collection::index * piIndex = nullptr);
      virtual bool _contains(const ::data::item * pitem);

      bool _contains(const tree_item_base * pitem) override;

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(tree_item_base * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(tree_item_base * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(tree_item_base * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(tree_item_base * pitem, const ::action_context & action_context, ::user::element * ptree, const ::int_point & point);

      void _erase(::pointer_array < tree_item_base > & itemptra);
      void _erase(tree_item_base * pitem);
      void _erase(::data::item  * pitem, ::collection::index i = 0);


      //tree_item_base * __previous() override;
      //tree_item_base * __next() override;
      //template < typename PRED >
      //void sort_children(PRED pred)
      //{

      //   tree_sort(this, pred);

      //}
      //void sort_children(const ::function < bool(const tree_item_base * p1, const tree_item_base * p2) > & functionLess) override;

      virtual tree_item_base * __get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      virtual tree_item_base * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel) override;
      virtual ::collection::index _get_proper_item_index(tree_item_base * pitemParam, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      //      virtual ::collection::count get_proper_item_count() override;

      virtual void _update_levels();

      virtual tree_item_base * _get_base_item();

      virtual const tree_item_base * _get_base_item() const;

      virtual tree_item_base * _insert_item(::data::item * pitemdataNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item_base * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      virtual bool _insert_item(tree_item_base * pitemNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item_base * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      ::image::image_list * get_image_list() const override;

      virtual void _001ExpandItem(tree_item_base * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(tree_item_base * pitem);
      virtual void _001SelectItem(tree_item_base * pitem);

      virtual void _get_selection(::pointer_array <tree_item_base> & itemptraSelected) const;
      virtual bool _is_selected(const tree_item_base * pitem) const;
      virtual bool _is_selected(const ::data::item * pitem) const;

      virtual ::collection::count   _selection_set(::pointer_array <tree_item_base> & itemptra);
      virtual bool      _selection_set(tree_item_base * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      _selection_set(::data::item *  pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      _selection_set(::collection::index iIndex, ::data::item * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);


      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void on_fill_children() override;
      //virtual void start_fill_children();

      virtual void on_tree_layout();

      virtual void fill_children();


      //virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };

   //template < primitive_data_item ::data::item * >
   //tree < ::data::item * >::tree()
   //{

   //   //defer_create_synchronization();

   //   m_bFill = false;

   //   //m_proot = __allocate tree_item_base();

   //   //if (m_proot == nullptr)
   //   //{

   //   //   throw ::exception(error_no_memory);

   //   //}

   //   this->m_dwState |= ::data::e_tree_item_state_expandable;

   //   this->m_dwState |= ::data::e_tree_item_state_expanded;

   //   this->m_ptree = this;

   //   this->m_pparent = __allocate tree_item_base();

   //}

   //template < primitive_data_item ::data::item * >
   //tree < ::data::item * >::~tree()
   //{

   //}

   //template < primitive_data_item ::data::item * >
   //tree_item_base * tree < ::data::item * >::find(const ::data::item * * pitemdata, ::collection::index * piIndex)
   //{

   //   ::collection::index iIndex;

   //   if (pitemdata == nullptr)
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

   //   ::pointer<::data::tree_item_base>pitem = this;

   //   for (; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
   //   {

   //      if (pitem->m_pdataitem == pitemdata)
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

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::contains(const ::data::item * * pitemdata)
   //{

   //   return find(pitemdata) != nullptr;

   //}
   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::contains(const tree_item_base * pitemParam)
   //{

   //   return tree_item_base::contains(pitemParam);

   //   //if (pitemParam == this)
   //   //{

   //   //   return true;

   //   //}
   //   //
   //   //::data::tree_item_base * pitem = this;

   //   //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
   //   //{

   //   //   if (pitem == pitemParam)
   //   //   {

   //   //      return true;

   //   //   }

   //   //}

   //   //return false;

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001OnTreeDataChange()
   //{

   //   update_levels();

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::erase(::data::item * * pitemdata, ::collection::index i)
   //{

   //   tree_item_base * pitem = find(pitemdata, &i);

   //   if (pitem == nullptr)
   //   {

   //      return;

   //   }

   //   return erase(pitem);

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::erase(tree_item_ptr_array<::data::item *> & itemptra)
   //{

   //   for (int i = 0; i < itemptra.get_count(); i++)
   //   {

   //      erase(itemptra[i]);

   //   }

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::erase(tree_item_base * pitem)
   //{

   //   if (pitem->m_ptree == this)
   //   {

   //      pitem->erase_tree_item();

   //   }

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::sort_children(const ::function < bool(const ::data::tree_item_base * p1, const ::data::tree_item_base * p2) > & functionLess)
   //{

   //   this->m_treeitema2.predicate_sort(functionLess);

   //   this->m_treeitema2.predicate_each([](auto pitem) {pitem->clear_cache(); });

   //}

   //template < primitive_data_item ::data::item * >
   //::data::tree_item_base * tree < ::data::item * >::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   //{

   //   ::collection::index iCount = 0;

   //   if (piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item_base>pitem = this;

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

   //template < primitive_data_item ::data::item * >
   //::data::tree_item_base * tree < ::data::item * >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   //{

   //   if (piLevel)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item_base>pitem = this;

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

   //template < primitive_data_item ::data::item * >
   //::collection::index tree < ::data::item * >::get_proper_item_index(::data::tree_item_base * pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   //{

   //   int iIndex = 0;

   //   ::collection::count iCount = 0;

   //   if (piLevel != nullptr)
   //   {

   //      *piLevel = 0;

   //   }

   //   ::pointer<::data::tree_item_base>pitem = get_base_item();

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


   ////::collection::count tree < ::data::item * >::get_proper_item_count()
   ////{

   ////   _synchronous_lock synchronouslock(this->synchronization());

   ////   return get_base_item()->get_proper_item_count();

   ////}

   //template < primitive_data_item ::data::item * >
   //::data::tree_item_base * tree < ::data::item * >::get_base_item()
   //{

   //   return this;

   //}

   //template < primitive_data_item ::data::item * >
   //const ::data::tree_item_base * tree < ::data::item * >::get_base_item() const
   //{

   //   return this;

   //}
   //template < primitive_data_item ::data::item * >

   //::data::tree_item_base * tree < ::data::item * >::_____previous()
   //{

   //   return nullptr;

   //}

   //template < primitive_data_item ::data::item * >
   //::data::tree_item_base * tree < ::data::item * >::_____next()
   //{

   //   return nullptr;

   //}

   //template < primitive_data_item ::data::item * >
   //::data::tree_item_base * tree < ::data::item * >::insert_item(::data::item * * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item_base * pitemRelative, bool bVoidTreeDataChangeEvent)
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

   //   ::pointer<::data::tree_item_base>pitemNew = __allocate tree_item_base();

   //   if (pitemNew == nullptr)
   //      return nullptr;

   //   if (!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
   //   {

   //      return nullptr;

   //   }

   //   pitemNew->m_pdataitem = pitemdataNew;

   //   return pitemNew;

   //}
   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::destroy()
   //{

   //   ::data::data::destroy();
   //   ::data::tree_item_base::destroy();

   //}
   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::on_insert_tree(tree * ptree)
   //{

   //   m_treea.add(ptree);

   //}

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::insert_item(::data::tree_item_base * pitemNew, enum_relative erelativeNewItem, ::data::tree_item_base * pitemRelative, bool bVoidTreeDataChangeEvent)
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

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::erase_all()
   //{

   //   this->erase_tree_item_descendants();

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::update_tree()
   //{

   //   _001OnTreeDataChange();

   //}


   ////void tree < ::data::item * >::sort(index ( * pfnCompare )(const ::pointer<tree_item_base>&, const ::pointer<tree_item_base>))

   ////{

   ////   ::pointer<tree_item_base>pitem = get_base_item();

   ////   while(pitem != nullptr)
   ////   {

   ////      pitem->sort_children(pfnCompare);


   ////      pitem = pitem->get_child_next_or_parent();

   ////   }

   ////}
   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::update_levels()
   //{

   //   ::collection::index iLevel = -1;

   //   ::pointer<tree_item_base>pitem = get_base_item();

   //   while (pitem != nullptr)
   //   {

   //      pitem->m_iLevel = iLevel;

   //      pitem = pitem->get_child_next_or_parent(&iLevel);

   //   }

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001ExpandItem(::data::tree_item_base * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   //{


   //}
   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001EnsureVisible(::data::tree_item_base * pitem)
   //{


   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001SelectItem(::data::tree_item_base * pitem)
   //{


   //}
   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::get_selection(::data::tree_item_ptr_array<::data::item *> & itemptraSelected) const
   //{


   //}
   //template < primitive_data_item ::data::item * >

   //bool tree < ::data::item * >::is_selected(const ::data::tree_item_base * pitem) const
   //{


   //   return false;

   //}

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::is_selected(const ::data::item * * pitem) const
   //{


   //   return false;

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001OnItemExpand(::data::tree_item_base * pitem, const ::action_context & context)
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

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001OnItemCollapse(::data::tree_item_base * pitem, const ::action_context & context)
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

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001OnOpenItem(::data::tree_item_base * pitem, const ::action_context & context)
   //{


   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::_001OnItemContextMenu(::data::tree_item_base * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   //{


   //}

   //template < primitive_data_item ::data::item * >
   //::collection::count tree < ::data::item * >::selection_set(::data::tree_item_ptr_array<::data::item *> & itemptra)
   //{

   //   return 0;

   //}

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::selection_set(::data::tree_item_base * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::selection_set(::data::item * * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < primitive_data_item ::data::item * >
   //bool tree < ::data::item * >::selection_set(::collection::index iIndex, ::data::item * * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   //{

   //   return false;

   //}

   //template < primitive_data_item ::data::item * >
   //::image::image_list * tree < ::data::item * >::get_image_list() const
   //{

   //   return nullptr;

   //}


   ////void tree < ::data::item * >::signal(::signal * psignal)
   ////{

   ////}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::handle(::topic * ptopic, ::context * pcontext)
   //{

   //   for (auto & ptree : m_treea)
   //   {

   //      ptree->handle(ptopic, pcontext);

   //   }

   //}



   ////void tree < ::data::item * >::handle(::topic * ptopic, ::context * pcontext)
   ////{

   ////}


   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::on_fill_children()
   //{

   //}


   ////void tree < ::data::item * >::start_fill_children()
   ////{

   ////   _synchronous_lock synchronouslock(this->synchronization());

   ////   m_bFill = true;

   ////   fork([this]()
   ////   {

   ////      fill_children();

   ////   });

   ////}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::on_tree_layout()
   //{

   //}

   //template < primitive_data_item ::data::item * >
   //void tree < ::data::item * >::fill_children()
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


   ////void tree < ::data::item * >::tree_layout(::draw2d::graphics_pointer & pgraphics)
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

