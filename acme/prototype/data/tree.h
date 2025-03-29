#pragma once


#include "acme/parallelization/synchronous_lock.h"
#include "acme/prototype/data/tree_base.h"
#include "acme/prototype/data/tree_item.h"


namespace data
{


   template < primitive_data_item DATA_ITEM >
   class tree :
      virtual public ::data::tree_base,
      virtual public tree_item < DATA_ITEM >
   {
   public:


      pointer_array < tree >                    m_treea;
      //::pointer<tree_item < DATA_ITEM >>               m_proot;
      bool                                m_bFill;
      index_array                         m_iaLevelNext;




      tree();
      ~tree() override;

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


      virtual void erase_all();

      virtual void update_tree();

      tree_item < DATA_ITEM > * find(const DATA_ITEM * pitem, ::collection::index * piIndex = nullptr);
       bool contains(const DATA_ITEM * pitem);

      bool contains(const tree_item < DATA_ITEM > * pitem);

      virtual void _001OnTreeDataChange();

      virtual void _001OnItemExpand(tree_item < DATA_ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnItemCollapse(tree_item < DATA_ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnOpenItem(tree_item < DATA_ITEM > * pitem, const ::action_context & action_context);
      virtual void _001OnItemContextMenu(tree_item < DATA_ITEM > * pitem, const ::action_context & action_context, ::user::element * ptree, const ::int_point & point);

      void erase(tree_item_ptr_array <DATA_ITEM > & itemptra);
      void erase(tree_item < DATA_ITEM > * pitem);
      void erase(DATA_ITEM * pitem, ::collection::index i = 0);


      tree_item < DATA_ITEM > * _____previous() override;
      tree_item < DATA_ITEM > * _____next() override;
      //template < typename PRED >
      //void sort_children(PRED pred)
      //{

      //   tree_sort(this, pred);

      //}
      void sort_children(const ::function < bool(const tree_item < DATA_ITEM > * p1, const tree_item < DATA_ITEM > * p2) > & functionLess) override;

      tree_item < DATA_ITEM > * _get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
      tree_item < DATA_ITEM > * get_proper_item(::collection::index iIndex, ::collection::index * piLevel) override;
      ::collection::index get_proper_item_index(tree_item < DATA_ITEM > * pitemParam, ::collection::index * piLevel, ::collection::index * piCount = nullptr);
//      virtual ::collection::count get_proper_item_count() override;

      void update_levels();

      tree_item_base * _get_base_item() { return get_base_item(); }


      const tree_item_base * _get_base_item() const { return get_base_item(); }

      tree_item < DATA_ITEM > * get_base_item();

      const tree_item < DATA_ITEM > * get_base_item() const;

      tree_item < DATA_ITEM > * insert_item(DATA_ITEM * pitemdataNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item < DATA_ITEM > * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);
      bool insert_item(tree_item < DATA_ITEM > * pitemNew, enum_relative erelativeNewItem = e_relative_last_child, tree_item < DATA_ITEM > * pitemRelative = nullptr, bool bVoidTreeDataChangeEvent = false);

      ::image::image_list * get_image_list() const override;

      virtual void _001ExpandItem(tree_item < DATA_ITEM > * pitem, const ::action_context & action_context, bool bExpand = true, bool bRedraw = true, bool bLayout = true);
      virtual void _001EnsureVisible(tree_item < DATA_ITEM > * pitem);
      virtual void _001SelectItem(tree_item < DATA_ITEM > * pitem);

      virtual void get_selection(::data::tree_item_ptr_array <DATA_ITEM> & itemptraSelected) const;
      virtual bool is_selected(const tree_item < DATA_ITEM > * pitem) const;
      virtual bool is_selected(const DATA_ITEM * pitem) const;

      virtual ::collection::count   selection_set(::data::tree_item_ptr_array <DATA_ITEM> & itemptra);
      virtual bool      selection_set(tree_item < DATA_ITEM > * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(DATA_ITEM * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);
      virtual bool      selection_set(::collection::index iIndex, DATA_ITEM * pitem, bool bIfNotInSelection = false, bool bIfParentInSelection = false);


      //void signal(::signal * psignal) override;
      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void on_fill_children() override;
      //virtual void start_fill_children();

      virtual void on_tree_layout();

      virtual void fill_children();


      //virtual void tree_layout(::draw2d::graphics_pointer & pgraphics);


   };

   template < primitive_data_item DATA_ITEM >
   tree < DATA_ITEM >::tree()
   {

      //defer_create_synchronization();

      m_bFill = false;

      //m_proot = __allocate tree_item < DATA_ITEM >();

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      this->m_dwState |= ::data::e_tree_item_state_expandable;

      this->m_dwState |= ::data::e_tree_item_state_expanded;

      this->m_ptree = this;

      this->m_pparent = __allocate tree_item < DATA_ITEM >();

   }

   template < primitive_data_item DATA_ITEM >
   tree < DATA_ITEM >::~tree()
   {

   }

   template < primitive_data_item DATA_ITEM >
   tree_item < DATA_ITEM > * tree < DATA_ITEM >::find(const DATA_ITEM * pitemdata, ::collection::index * piIndex)
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

      ::pointer<::data::tree_item < DATA_ITEM >>pitem = this;

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

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::contains(const DATA_ITEM * pitemdata)
   {

      return find(pitemdata) != nullptr;

   }
   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::contains(const tree_item < DATA_ITEM > * pitemParam)
   {

      return tree_item < DATA_ITEM >::contains(pitemParam);

      //if (pitemParam == this)
      //{

      //   return true;

      //}
      //
      //::data::tree_item < DATA_ITEM > * pitem = this;

      //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      //{

      //   if (pitem == pitemParam)
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001OnTreeDataChange()
   {

      update_levels();

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::erase(DATA_ITEM * pitemdata, ::collection::index i)
   {

      tree_item < DATA_ITEM > * pitem = find(pitemdata, &i);

      if (pitem == nullptr)
      {

         return;

      }

      return erase(pitem);

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::erase(tree_item_ptr_array<DATA_ITEM> & itemptra)
   {

      for (int i = 0; i < itemptra.get_count(); i++)
      {

         erase(itemptra[i]);

      }

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::erase(tree_item < DATA_ITEM > * pitem)
   {

      if (pitem->m_ptree == this)
      {

         pitem->erase_tree_item();

      }

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::sort_children(const ::function < bool(const ::data::tree_item < DATA_ITEM > * p1, const ::data::tree_item < DATA_ITEM > * p2) > & functionLess)
   {

      this->m_treeitema2.predicate_sort(functionLess);

      this->m_treeitema2.predicate_each([](auto pitem) {pitem->clear_cache(); });

   }

   template < primitive_data_item DATA_ITEM >
   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   {

      ::collection::index iCount = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item < DATA_ITEM >>pitem = this;

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

   template < primitive_data_item DATA_ITEM >
   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item < DATA_ITEM >>pitem = this;

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

   template < primitive_data_item DATA_ITEM >
   ::collection::index tree < DATA_ITEM >::get_proper_item_index(::data::tree_item < DATA_ITEM > * pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   {

      int iIndex = 0;

      ::collection::count iCount = 0;

      if (piLevel != nullptr)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item < DATA_ITEM >>pitem = get_base_item();

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


   //::collection::count tree < DATA_ITEM >::get_proper_item_count()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return get_base_item()->get_proper_item_count();

   //}

   template < primitive_data_item DATA_ITEM >
   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::get_base_item()
   {

      return this;

   }

   template < primitive_data_item DATA_ITEM >
   const ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::get_base_item() const
   {

      return this;

   }
   template < primitive_data_item DATA_ITEM >

   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::_____previous()
   {

      return nullptr;

   }

   template < primitive_data_item DATA_ITEM >
   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::_____next()
   {

      return nullptr;

   }

   template < primitive_data_item DATA_ITEM >
   ::data::tree_item < DATA_ITEM > * tree < DATA_ITEM >::insert_item(DATA_ITEM * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item < DATA_ITEM > * pitemRelative, bool bVoidTreeDataChangeEvent)
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

      ::pointer<::data::tree_item < DATA_ITEM >>pitemNew = __allocate tree_item < DATA_ITEM >();

      if (pitemNew == nullptr)
         return nullptr;

      if (!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
      {

         return nullptr;

      }

      pitemNew->m_pdataitem = pitemdataNew;

      return pitemNew;

   }
   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::destroy()
   {

      ::data::data::destroy();
      ::data::tree_item < DATA_ITEM >::destroy();

   }
   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::on_insert_tree(tree * ptree)
   {

      m_treea.add(ptree);

   }

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::insert_item(::data::tree_item < DATA_ITEM > * pitemNew, enum_relative erelativeNewItem, ::data::tree_item < DATA_ITEM > * pitemRelative, bool bVoidTreeDataChangeEvent)
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

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::erase_all()
   {

      this->erase_tree_item_descendants();

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree < DATA_ITEM >::sort(index ( * pfnCompare )(const ::pointer<tree_item < DATA_ITEM >>&, const ::pointer<tree_item < DATA_ITEM >>))

   //{

   //   ::pointer<tree_item < DATA_ITEM >>pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}
   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::update_levels()
   {

      ::collection::index iLevel = -1;

      ::pointer<tree_item < DATA_ITEM >>pitem = get_base_item();

      while (pitem != nullptr)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->get_child_next_or_parent(&iLevel);

      }

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001ExpandItem(::data::tree_item < DATA_ITEM > * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {


   }
   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001EnsureVisible(::data::tree_item < DATA_ITEM > * pitem)
   {


   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001SelectItem(::data::tree_item < DATA_ITEM > * pitem)
   {


   }
   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::get_selection(::data::tree_item_ptr_array<DATA_ITEM> & itemptraSelected) const
   {


   }
   template < primitive_data_item DATA_ITEM >

   bool tree < DATA_ITEM >::is_selected(const ::data::tree_item < DATA_ITEM > * pitem) const
   {


      return false;

   }

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::is_selected(const DATA_ITEM * pitem) const
   {


      return false;

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001OnItemExpand(::data::tree_item < DATA_ITEM > * pitem, const ::action_context & context)
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

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001OnItemCollapse(::data::tree_item < DATA_ITEM > * pitem, const ::action_context & context)
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

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001OnOpenItem(::data::tree_item < DATA_ITEM > * pitem, const ::action_context & context)
   {


   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::_001OnItemContextMenu(::data::tree_item < DATA_ITEM > * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   {


   }

   template < primitive_data_item DATA_ITEM >
   ::collection::count tree < DATA_ITEM >::selection_set(::data::tree_item_ptr_array<DATA_ITEM> & itemptra)
   {

      return 0;

   }

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::selection_set(::data::tree_item < DATA_ITEM > * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::selection_set(DATA_ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }

   template < primitive_data_item DATA_ITEM >
   bool tree < DATA_ITEM >::selection_set(::collection::index iIndex, DATA_ITEM * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }

   template < primitive_data_item DATA_ITEM >
   ::image::image_list * tree < DATA_ITEM >::get_image_list() const
   {

      return nullptr;

   }


   //void tree < DATA_ITEM >::signal(::signal * psignal)
   //{

   //}

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::handle(::topic * ptopic, ::context * pcontext)
   {

      for (auto & ptree : m_treea)
      {

         ptree->handle(ptopic, pcontext);

      }

   }



   //void tree < DATA_ITEM >::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}


   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::on_fill_children()
   {

   }


   //void tree < DATA_ITEM >::start_fill_children()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_bFill = true;

   //   fork([this]()
   //   {

   //      fill_children();

   //   });

   //}

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::on_tree_layout()
   {

   }

   template < primitive_data_item DATA_ITEM >
   void tree < DATA_ITEM >::fill_children()
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


   //void tree < DATA_ITEM >::tree_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}



} // namespace data

//
//
//inline stream & operator <<(stream & s, const ::data::tree & tree);
//
//inline stream & operator >>(stream & s, ::data::tree & tree);
//
//

