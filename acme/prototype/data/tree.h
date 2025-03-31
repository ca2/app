#pragma once


#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/tree_base.h"
#include "acme/prototype/data/tree_item.h"


namespace data
{


   template < prototype_item ITEM >
   class tree :
      virtual public ::data::tree_base,
      virtual public ::data::tree_item <  ITEM >
   {
   public:


      pointer_array < tree >                    m_treea;
      //::pointer<tree_item <  ITEM >>               m_proot;
      bool                                m_bFill;
      index_array                         m_iaLevelNext;




      tree();
      ~tree() override;

      virtual ::pointer < ::data::tree_item <  ITEM > > create_tree_item();
      ::pointer < ::data::tree_item_base > _create_tree_item() override;

      void destroy() override;

      virtual void on_insert_tree(tree * ptree);

      virtual long long increment_reference_count() override
      {
         return ::matter::increment_reference_count();
      }

      virtual long long decrement_reference_count() override
      {
         return ::matter::decrement_reference_count();
      }
      
      
      ::collection::count _tree_count() override;
      tree_base * _tree_at(::collection::index iIndex) override;


      void erase_all() override;

      void update_tree() override;

      tree_item <  ITEM > * find(const  ITEM * pitem, ::collection::index * piIndex = nullptr);
       bool contains(const  ITEM * pitem);

      bool contains(const tree_item <  ITEM > * pitem) override;

      void _001OnTreeDataChange() override;

      virtual void _001OnItemExpand(tree_item <  ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(tree_item <  ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(tree_item <  ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(tree_item <  ITEM > * pitem, const ::action_context & action_context, ::user::element * ptree, const ::int_point & point);
      virtual void _001OnOpenItem(::data::tree_item_base * pitem, const ::action_context & context) override;

      void erase(tree_item_ptr_array < ITEM > & itemptra);
      void erase(tree_item <  ITEM > * pitem);
      void erase( ITEM * pitem, ::collection::index i = 0);


      tree_item_base * __previous() override;
      tree_item_base * __next() override;
      //template < typename PRED >
      //void sort_children(PRED pred)
      //{

      //   tree_sort(this, pred);

      //}
      void sort_children(const ::function < bool(const tree_item <  ITEM > * p1, const tree_item <  ITEM > * p2) > & functionLess) override;

      tree_item <  ITEM > * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      tree_item <  ITEM > * get_proper_item(::collection::index iIndex, ::collection::index * piLevel) override;
      ::collection::index get_proper_item_index(tree_item <  ITEM > * pitemParam, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
//      virtual ::collection::count get_proper_item_count() override;

      void update_levels();

      tree_item_base * _get_base_item() override { return get_base_item(); }


      const tree_item_base * _get_base_item() const override { return get_base_item(); }

      tree_item <  ITEM > * get_base_item();

      const tree_item <  ITEM > * get_base_item() const;

      tree_item <  ITEM > * insert_item( ITEM * pitemdataNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item <  ITEM > * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      bool insert_item(tree_item <  ITEM > * pitemNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item <  ITEM > * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      ::image::image_list * get_tree_image_list() override;

      virtual void _001ExpandItem(tree_item <  ITEM > * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(tree_item <  ITEM > * pitem);
      virtual void _001SelectItem(tree_item <  ITEM > * pitem);

      virtual void get_selection(::data::tree_item_ptr_array < ITEM> & itemptraSelected) const;
      virtual bool is_selected(const tree_item <  ITEM > * pitem) const;
      virtual bool is_selected(const  ITEM * pitem) const;

      virtual ::collection::count   selection_set(::data::tree_item_ptr_array < ITEM> & itemptra);
      virtual bool      selection_set(tree_item <  ITEM > * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set( ITEM * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::collection::index iIndex,  ITEM * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);


      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void on_fill_children() override;
      //virtual void start_fill_children();

      void on_tree_layout() override;

      void fill_children() override;


      //virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };

   template < prototype_item ITEM >
   tree <  ITEM >::tree()
   {

      //defer_create_synchronization();

      m_bFill = false;

      //m_proot = __allocate tree_item <  ITEM >();

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      this->m_dwState |= ::data::e_tree_item_state_expandable;

      this->m_dwState |= ::data::e_tree_item_state_expanded;

      this->m_ptree = this;

      this->m_pparent = __allocate tree_item <  ITEM >();

   }

   template < prototype_item ITEM >
   tree <  ITEM >::~tree()
   {

   }

   template < prototype_item ITEM >
   tree_item <  ITEM > * tree <  ITEM >::find(const  ITEM * pitemdata, ::collection::index * piIndex)
   {

      ::collection::index iIndex;

      if (pitemdata == nullptr)
      {

         return nullptr;

      }

      if (piIndex == nullptr)
      {

         iIndex = 0;

      }
      else
      {

         iIndex = *piIndex;

      }

      ::pointer<::data::tree_item <  ITEM >>pitem = this;

      for (; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      {

         if (pitem->m_pdataitem == pitemdata)
         {

            iIndex--;

            if (iIndex < 0)
            {

               return pitem;

            }

         }

      }

      if (piIndex != nullptr)
      {

         *piIndex = iIndex;

      }

      return nullptr;

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::contains(const  ITEM * pitemdata)
   {

      return find(pitemdata) != nullptr;

   }
   template < prototype_item ITEM >
   bool tree <  ITEM >::contains(const tree_item <  ITEM > * pitemParam)
   {

      return tree_item <  ITEM >::contains(pitemParam);

      //if (pitemParam == this)
      //{

      //   return true;

      //}
      //
      //::data::tree_item <  ITEM > * pitem = this;

      //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      //{

      //   if (pitem == pitemParam)
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnTreeDataChange()
   {

      update_levels();

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::erase( ITEM * pitemdata, ::collection::index i)
   {

      tree_item <  ITEM > * pitem = find(pitemdata, &i);

      if (pitem == nullptr)
      {

         return;

      }

      return erase(pitem);

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::erase(tree_item_ptr_array< ITEM> & itemptra)
   {

      for (int i = 0; i < itemptra.get_count(); i++)
      {

         erase(itemptra[i]);

      }

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::erase(tree_item <  ITEM > * pitem)
   {

      if (pitem->m_ptree == this)
      {

         pitem->erase_tree_item();

      }

   }


   template < prototype_item ITEM >
   void tree <  ITEM >::sort_children(const ::function < bool(const ::data::tree_item <  ITEM > * p1, const ::data::tree_item <  ITEM > * p2) > & functionLess)
   {

      if (!this->m_ptreeitema2)
      {

return;

      }

      this->m_ptreeitema2->predicate_sort(functionLess);

      this->m_ptreeitema2->predicate_each([](auto pitem) {pitem->clear_cache(); });

   }


   template < prototype_item ITEM >
   ::data::tree_item <  ITEM > * tree <  ITEM >::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   {

      ::collection::index iCount = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item <  ITEM >>pitem = this;

      while (pitem && iIndex >= 0)
      {

         pitem = pitem->get_proper_next(piLevel);

         iIndex--;

      }

      if (iIndex < 0 && pitem)
      {

         return pitem;

      }

      if (piCount != nullptr)
      {

         *piCount = iCount;

      }

      return nullptr;

   }

   template < prototype_item ITEM >
   ::data::tree_item <  ITEM > * tree <  ITEM >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item <  ITEM >>pitem = this;

      while (pitem && iIndex >= 0)
      {

         pitem = pitem->get_proper_next(piLevel);

         iIndex--;

      }

      if (iIndex < 0 && pitem)
      {

         return pitem;

      }

      return nullptr;

   }

   template < prototype_item ITEM >
   ::collection::index tree <  ITEM >::get_proper_item_index(::data::tree_item <  ITEM > * pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   {

      int iIndex = 0;

      ::collection::count iCount = 0;

      if (piLevel != nullptr)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item <  ITEM >>pitem = get_base_item();

      while (pitem != nullptr)
      {

         pitem = pitem->get_proper_next(piLevel);

         if (pitem == pitemParam)
         {

            if (piCount != nullptr)
            {

               *piCount += iCount;

            }

            return iIndex;

         }

         iIndex++;

         iCount++;

      }

      if (piCount != nullptr)
      {

         *piCount += iCount;

      }

      return -1;

   }


   //::collection::count tree <  ITEM >::get_proper_item_count()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return get_base_item()->get_proper_item_count();

   //}

   template < prototype_item ITEM >
   ::data::tree_item <  ITEM > * tree <  ITEM >::get_base_item()
   {

      return this;

   }

   template < prototype_item ITEM >
   const ::data::tree_item <  ITEM > * tree <  ITEM >::get_base_item() const
   {

      return this;

   }


   template < prototype_item ITEM >
   ::data::tree_item_base * tree <  ITEM >::__previous()
   {

      return nullptr;

   }


   template < prototype_item ITEM >
   ::data::tree_item_base * tree <  ITEM >::__next()
   {

      return nullptr;

   }

   template < prototype_item ITEM >
   ::data::tree_item <  ITEM > * tree <  ITEM >::insert_item( ITEM * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item <  ITEM > * pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      if (pitemRelative == nullptr)
      {

         pitemRelative = this;

      }

      if (erelativeNewItem == e_relative_replace)
      {

         if (!contains(pitemRelative))
            return nullptr;

         pitemRelative->m_pdataitem = pitemdataNew;

         return pitemRelative;

      }

      ::pointer<::data::tree_item <  ITEM >>pitemNew = __allocate tree_item <  ITEM >();

      if (pitemNew == nullptr)
         return nullptr;

      if (!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
      {

         return nullptr;

      }

      pitemNew->m_pdataitem = pitemdataNew;

      return pitemNew;

   }

   template < prototype_item ITEM >
   ::pointer < ::data::tree_item <  ITEM > > tree <  ITEM >::create_tree_item()
   {

      return __create_new < ::data::tree_item <  ITEM > >();

   }

   template < prototype_item ITEM >
   ::pointer < ::data::tree_item_base > tree <  ITEM >::_create_tree_item()
   {

      return this->create_tree_item();

   }
   template < prototype_item ITEM >
   void tree <  ITEM >::destroy()
   {

      ::data::data::destroy();
      ::data::tree_item <  ITEM >::destroy();

   }
   template < prototype_item ITEM >
   void tree <  ITEM >::on_insert_tree(tree * ptree)
   {

      m_treea.add(ptree);

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::insert_item(::data::tree_item <  ITEM > * pitemNew, enum_relative erelativeNewItem, ::data::tree_item <  ITEM > * pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      ::pointer<tree>ptreeNew = pitemNew;

      if (ptreeNew)
      {

         on_insert_tree(ptreeNew);

      }

      if (pitemRelative == nullptr)
      {

         pitemRelative = this;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      if (pitemNew == nullptr)
      {

         return false;

      }

      if (!contains(pitemRelative))
      {

         return false;

      }

      if (erelativeNewItem == e_relative_parent)
      {

         return false;

      }

      if (erelativeNewItem == e_relative_last_sibling)
      {

         if (pitemRelative == this)
         {

            erelativeNewItem = e_relative_first_child;

         }

      }

      bool bOk = false;

      switch (erelativeNewItem)
      {
      case e_relative_first_child:
      {

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_last_child:
      {

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_previous_sibling:
      {

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_next_sibling:
      {

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_last_sibling:
      {

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_replace:
      {

         pitemNew->m_dwUser = pitemRelative->m_dwUser;
         pitemNew->m_dwMetaData = pitemRelative->m_dwMetaData;
         pitemNew->m_dwState = pitemRelative->m_dwState;
         pitemNew->m_pdataitem = pitemRelative->m_pdataitem;

         pitemNew->m_iLevel = pitemRelative->m_iLevel;

         bOk = pitemRelative->insert(erelativeNewItem, pitemNew);

      }
      break;

      case e_relative_macro_record:
      {

         if (pitemRelative->get_next() != nullptr)
         {

            bOk = insert_item(pitemNew, ::data::e_relative_first_child, pitemRelative);

         }
         else
         {

            bOk = insert_item(pitemNew, ::data::e_relative_last_sibling, pitemRelative);

         }

      }
      break;
      default:

         throw ::exception(error_not_supported);

      }

      pitemNew->m_ptree = this;

      if (!bVoidTreeDataChangeEvent)
      {

         _001OnTreeDataChange();

      }

      return bOk;

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::erase_all()
   {

      this->erase_tree_item_descendants();

   }


   template < prototype_item ITEM >
   ::collection::count tree <  ITEM >::_tree_count()
   {

      return this->m_treea.size();

   }


   template < prototype_item ITEM >
   tree_base * tree <  ITEM >::_tree_at(::collection::index iIndex)
   {

      return this->m_treea[iIndex];

   }


   template < prototype_item ITEM >
   void tree <  ITEM >::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree <  ITEM >::sort(index ( * pfnCompare )(const ::pointer<tree_item <  ITEM >>&, const ::pointer<tree_item <  ITEM >>))

   //{

   //   ::pointer<tree_item <  ITEM >>pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}
   template < prototype_item ITEM >
   void tree <  ITEM >::update_levels()
   {

      ::collection::index iLevel = -1;

      ::pointer<tree_item <  ITEM >>pitem = get_base_item();

      while (pitem != nullptr)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->get_child_next_or_parent(&iLevel);

      }

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001ExpandItem(::data::tree_item <  ITEM > * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {


   }
   template < prototype_item ITEM >
   void tree <  ITEM >::_001EnsureVisible(::data::tree_item <  ITEM > * pitem)
   {


   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001SelectItem(::data::tree_item <  ITEM > * pitem)
   {


   }
   template < prototype_item ITEM >
   void tree <  ITEM >::get_selection(::data::tree_item_ptr_array< ITEM> & itemptraSelected) const
   {


   }
   template < prototype_item ITEM >

   bool tree <  ITEM >::is_selected(const ::data::tree_item <  ITEM > * pitem) const
   {


      return false;

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::is_selected(const  ITEM * pitem) const
   {


      return false;

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnItemExpand(::data::tree_item <  ITEM > * pitem, const ::action_context & context)
   {

      if (pitem->is_expanded())
         return;

      pitem->on_fill_children();

      if (pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::e_tree_item_state_expanded;
         pitem->m_dwState |= ::data::e_tree_item_state_expandable;
      }

      /*      for (::collection::index i = 0; i < m_treeptra.get_count(); i++)
            {

               m_treeptra[i]._001OnItemExpand(pitem, context);

            }*/




   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnItemCollapse(::data::tree_item <  ITEM > * pitem, const ::action_context & context)
   {

      if (!pitem->is_expanded())
         return;
      if (pitem->get_children_count() > 0)
      {
         pitem->m_dwState |= ::data::e_tree_item_state_expandable;
      }
      pitem->m_dwState &= ~::data::e_tree_item_state_expanded;
      /*for (::collection::index i = 0; i < m_treeptra.get_count(); i++)
      {

         m_treeptra[i]._001OnItemCollapse(pitem);

      }*/

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnOpenItem(::data::tree_item <  ITEM > * pitem, const ::action_context & context)
   {


   }


   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnOpenItem(::data::tree_item_base * pitem, const ::action_context & context)
   {

      ::cast < ::data::tree_item <  ITEM > > ptreeitem = pitem;

      _001OnOpenItem(ptreeitem, context);

   }


   template < prototype_item ITEM >
   void tree <  ITEM >::_001OnItemContextMenu(::data::tree_item <  ITEM > * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   {


   }

   template < prototype_item ITEM >
   ::collection::count tree <  ITEM >::selection_set(::data::tree_item_ptr_array< ITEM> & itemptra)
   {

      return 0;

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::selection_set(::data::tree_item <  ITEM > * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::selection_set( ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }

   template < prototype_item ITEM >
   bool tree <  ITEM >::selection_set(::collection::index iIndex,  ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   template < prototype_item ITEM >
   ::image::image_list * tree <  ITEM >::get_tree_image_list()
   {

      return nullptr;

   }


   //void tree <  ITEM >::signal(::signal * psignal)
   //{

   //}

   template < prototype_item ITEM >
   void tree <  ITEM >::handle(::topic * ptopic, ::context * pcontext)
   {

      for (auto & ptree : m_treea)
      {

         ptree->handle(ptopic, pcontext);

      }

   }



   //void tree <  ITEM >::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}


   template < prototype_item ITEM >
   void tree <  ITEM >::on_fill_children()
   {

   }


   //void tree <  ITEM >::start_fill_children()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_bFill = true;

   //   fork([this]()
   //   {

   //      fill_children();

   //   });

   //}

   template < prototype_item ITEM >
   void tree <  ITEM >::on_tree_layout()
   {

   }

   template < prototype_item ITEM >
   void tree <  ITEM >::fill_children()
   {

      try
      {

         on_fill_children();

      }
      catch (...)
      {

      }


      try
      {

         //auto pgraphics = ::draw2d::create_memory_graphics();

         //tree_layout(pgraphics);

         on_tree_layout();

      }
      catch (...)
      {

      }

      m_bFill = false;

   }


   //void tree <  ITEM >::tree_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}

   template < prototype_item ITEM >
   tree_base * tree_item <  ITEM >::_get_tree() const
   {

      return m_ptree;

   }

   template < prototype_item ITEM >
   void tree_item <  ITEM >::_set_tree(tree_base * ptreebase)
   {

      m_ptree = dynamic_cast <::data::tree <  ITEM > *>(ptreebase);

   }



} // namespace data

//
//
//inline stream & operator <<(stream & s, const ::data::tree & tree);
//
//inline stream & operator >>(stream & s, ::data::tree & tree);
//
//

