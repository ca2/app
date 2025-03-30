// From tree.cpp on 2025-03-28 22:36 <3ThomasBorregaardSorensen!!
#include "framework.h" 
#include "tree_base.h"
#include "tree_item_base.h"
#include "listener.h"
#include "item.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"


//void data_tree_item_list_sort(::data::tree_item_base * pitem, const ::function < bool(const ::data::tree_item_base *, const ::data::tree_item_base *) > & functionLess);

namespace data
{


   tree_base::tree_base()
   {

      //defer_create_synchronization();

      m_bFill = false;

      //m_proot = __allocate tree_item_base();

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      m_dwState |= ::data::e_tree_item_state_expandable;

      m_dwState |= ::data::e_tree_item_state_expanded;

      //_get_tree() = this;

      //m_pparent = __allocate ::data::tree_item_base ();

   }


   tree_base::~tree_base()
   {

   }


   tree_item_base * tree_base::_find(const item * pitemdata, ::collection::index * piIndex)
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

      ::pointer<::data::tree_item_base>pitem = this;

      for(; pitem != nullptr; pitem = pitem->_get_item(e_tree_navigation_expanded_forward))
      {
         
         if(pitem->_data_item() == pitemdata)
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

   
   bool tree_base::_contains(const item * pitemdata)
   {
      
      return _find(pitemdata) != nullptr;

   }


   bool tree_base::_contains(const tree_item_base * pitemParam)
   {

      return tree_item_base::_contains(pitemParam);

      //if (pitemParam == this)
      //{

      //   return true;

      //}
      //
      //::data::tree_item_base * pitem = this;

      //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      //{

      //   if (pitem == pitemParam)
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }


   void tree_base::_001OnTreeDataChange()
   {

      _update_levels();

   }


   void tree_base::_erase(item * pitemdata, ::collection::index i)
   {
      
      tree_item_base * pitem = _find(pitemdata, &i);

      if (pitem == nullptr)
      {

         return;

      }

      return _erase(pitem);

   }


   void tree_base::_erase(::pointer_array < tree_item_base > & itemptra)
   {

      for(int i = 0; i < itemptra.get_count(); i++)
      {

         _erase(itemptra[i]);

      }

   }


   void tree_base::_erase(tree_item_base * pitem)
   {

      if (pitem->_get_tree() == this)
      {

         pitem->erase_tree_item();

      }

   }







   //void tree_base::sort_children(const ::function < bool(const ::data::tree_item_base * p1, const ::data::tree_item_base * p2) > & functionLess)
   //{

   //   m_treeitema2.predicate_sort(functionLess);

   //   m_treeitema2.predicate_each([](auto pitem) {pitem->clear_cache(); });

   //}


   ::data::tree_item_base * tree_base::__get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   {

      ::collection::index iCount = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item_base>pitem = this;

      while(pitem && iIndex >= 0)
      {

         pitem = pitem->_get_proper_next(piLevel);

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


   ::data::tree_item_base* tree_base::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item_base>pitem = this;

      while (pitem && iIndex >= 0)
      {

         pitem = pitem->_get_proper_next(piLevel);

         iIndex--;

      }

      if (iIndex < 0 && pitem)
      {

         return pitem;

      }

      return nullptr;

   }


   ::collection::index tree_base::_get_proper_item_index(::data::tree_item_base *pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   {

      int iIndex = 0;

      ::collection::count iCount = 0;

      if (piLevel != nullptr)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item_base>pitem = _get_base_item();

      while (pitem != nullptr)
      {

         pitem = pitem->_get_proper_next(piLevel);

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


   //::collection::count tree_base::get_proper_item_count()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return get_base_item()->get_proper_item_count();

   //}


   ::data::tree_item_base * tree_base::_get_base_item()
   {

      return this;

   }


   const ::data::tree_item_base * tree_base::_get_base_item() const
   {

      return this;

   }


   //::data::tree_item_base * tree_base::__previous()
   //{

   //   return nullptr;

   //}


   //::data::tree_item_base * tree_base::__next()
   //{

   //   return nullptr;

   //}


   ::data::tree_item_base * tree_base::_insert_item(::data::item * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item_base *pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      if (pitemRelative == nullptr)
      {

         pitemRelative = this;

      }

      if(erelativeNewItem == e_relative_replace)
      {

         if(!_contains(pitemRelative))
            return nullptr;

         pitemRelative->_set_data_item(pitemdataNew);

         return pitemRelative;

      }

      auto pitemNew = create_tree_item();

      if (pitemNew == nullptr)
      {

         return nullptr;

      }

      if(!_insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
      {

         return nullptr;

      }

      pitemNew->_set_data_item(pitemdataNew);

      return pitemNew;

   }


   void tree_base::destroy()
   {

      ::data::data::destroy();
      ::data::tree_item_base::destroy();

   }

   void tree_base::_insert_tree(tree_base * ptree)
   {

      // m_treea.add(ptree);

      throw ::interface_only();

   }


   bool tree_base::_insert_item(::data::tree_item_base *pitemNew, enum_relative erelativeNewItem, ::data::tree_item_base *pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      ::pointer<tree_base>ptreeNew = pitemNew;

      if (ptreeNew)
      {

         _insert_tree(ptreeNew);

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

      if (!_contains(pitemRelative))
      {

         return false;

      }

      if (erelativeNewItem == e_relative_parent)
      {

         return false;

      }

      if(erelativeNewItem == e_relative_last_sibling)
      {
         
         if(pitemRelative == this)
         {

            erelativeNewItem = e_relative_first_child;

         }

      }

      bool bOk = false;

      switch(erelativeNewItem)
      {
      case e_relative_first_child:
      {

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_last_child:
      {

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_previous_sibling:
      {

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_next_sibling:
      {

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_last_sibling:
      {

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;
      case e_relative_replace:
      {

         pitemNew->m_dwUser         = pitemRelative->m_dwUser;
         pitemNew->m_dwMetaData     = pitemRelative->m_dwMetaData;
         pitemNew->m_dwState        = pitemRelative->m_dwState;
         pitemNew->_set_data_item(pitemRelative->_data_item());

         pitemNew->m_iLevel = pitemRelative->m_iLevel;

         bOk = pitemRelative->_insert(erelativeNewItem, pitemNew);

      }
      break;

      case e_relative_macro_record:
      {

         if (pitemRelative->_get_next() != nullptr)
         {

            bOk = _insert_item(pitemNew, ::data::e_relative_first_child, pitemRelative);

         }
         else
         {

            bOk = _insert_item(pitemNew, ::data::e_relative_last_sibling, pitemRelative);

         }

      }
      break;
      default:

         throw ::exception(error_not_supported);

      }

      pitemNew->_set_tree(this);

      if (!bVoidTreeDataChangeEvent)
      {

         _001OnTreeDataChange();

      }

      return bOk;

   }


   void tree_base::erase_all()
   {

      erase_tree_item_descendants();

   }


   void tree_base::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree_base::sort(index ( * pfnCompare )(const ::pointer<tree_item_base>&, const ::pointer<tree_item_base>))

   //{

   //   ::pointer<tree_item_base>pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}


   void tree_base::_update_levels()
   {

      ::collection::index iLevel = -1;

      ::pointer<tree_item_base>pitem = _get_base_item();

      while (pitem != nullptr)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->_get_child_next_or_parent(&iLevel);

      }

   }


   void tree_base::_001ExpandItem(::data::tree_item_base * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {


   }

   void tree_base::_001EnsureVisible(::data::tree_item_base * pitem)
   {


   }


   void tree_base::_001SelectItem(::data::tree_item_base * pitem)
   {


   }


   void tree_base::_get_selection(::pointer_array <tree_item_base> & itemptraSelected) const
   {


   }


   bool tree_base::_is_selected(const ::data::tree_item_base * pitem) const
   {


      return false;

   }


   bool tree_base::_is_selected(const ::data::item * pitem) const
   {


      return false;

   }


   void tree_base::_001OnItemExpand(::data::tree_item_base * pitem, const ::action_context & context)
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


   void tree_base::_001OnItemCollapse(::data::tree_item_base * pitem, const ::action_context & context)
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


   void tree_base::_001OnOpenItem(::data::tree_item_base * pitem, const ::action_context & context)
   {


   }


   void tree_base::_001OnItemContextMenu(::data::tree_item_base * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   {


   }


   ::collection::count tree_base::_selection_set(::pointer_array < tree_item_base > & itemptra)
   {

      return 0;

   }


   bool tree_base::_selection_set(::data::tree_item_base * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree_base::_selection_set(::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree_base::_selection_set(::collection::index iIndex, ::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   ::image::image_list * tree_base::get_image_list() const
   {

      return nullptr;

   }


   //void tree_base::signal(::signal * psignal)
   //{

   //}

   ::collection::count tree_base::_tree_count()
   {

      throw ::interface_only();


      return -1;

   }


   tree_base * tree_base::_tree_at(::collection::index iIndex)
   {
      throw ::interface_only();


      return nullptr;

   }


   void tree_base::predicate_each_tree(const ::function < void(tree_base *) > & callback)
   {

      auto c = _tree_count();

      for (::collection::index i = 0; i < c; i++)
      {

         auto pitem = _tree_at(i);

         callback(pitem);

      }

   }


   void tree_base::handle(::topic * ptopic, ::context * pcontext)
   {

      predicate_each_tree ([ptopic, pcontext](auto& ptree)
      {

         ptree->handle(ptopic, pcontext);

      });

   }



   //void tree_base::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}



   void tree_base::on_fill_children()
   {

   }


   //void tree_base::start_fill_children()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_bFill = true;

   //   fork([this]()
   //   {

   //      fill_children();

   //   });

   //}


   void tree_base::on_tree_layout()
   {

   }


   void tree_base::fill_children()
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


   //void tree_base::tree_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


} // namespace data



