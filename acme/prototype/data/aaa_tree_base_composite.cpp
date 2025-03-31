// From tree.cpp on 2025-03-29 00:34 <3ThomasBorregaardSorensen!!
#include "framework.h" 
#include "tree_base_composite.h"
#include "tree_item.h"
#include "listener.h"
#include "item.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"


//void data_tree_item_list_sort(::data::tree_item * pitem, const ::function < bool(const ::data::tree_item *, const ::data::tree_item *) > & functionLess);

namespace data
{


   tree_base_composite::tree_base_composite()
   {

      //defer_create_synchronization();

      m_bFill = false;

      //m_proot = __allocate tree_item();

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      m_dwState |= ::data::e_tree_item_state_expandable;

      m_dwState |= ::data::e_tree_item_state_expanded;

      //_get_tree() = this;

      //m_pparent = __allocate ::data::tree_item ();

   }


   tree_base_composite::~tree_base_composite()
   {

   }


   tree_item * tree_base_composite::_find(const ::item * pitem, ::collection::index * piIndex)
   {

      return m_ptreebase->_find(pitem, piIndex);

   }


   bool tree_base_composite::_contains(const ::item * pitem)
   {

      return m_ptreebase->_contains(pitem);

   }


   bool tree_base_composite::_contains(const tree_item * pitemParam)
   {

      return m_ptreebase->_contains(pitemParam);

   }


   void tree_base_composite::_001OnTreeDataChange()
   {

      m_ptreebase->_001OnTreeDataChange();

   }


   void tree_base_composite::_erase(::item * pitem, ::collection::index i)
   {

      m_ptreebase->_erase(pitem, i);

   }


   void tree_base_composite::_erase(::data::tree_item_ptr_array & itemptra)
   {

      m_ptreebase->_erase(itemptra);

   }


   void tree_base_composite::_erase(tree_item * pitem)
   {

      m_ptreebase->_erase(pitem);

   }


   //void tree_base_composite::sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess)
   //{

   //   m_treeitema2.predicate_sort(functionLess);

   //   m_treeitema2.predicate_each([](auto pitem) {pitem->clear_cache(); });

   //}


   ::data::tree_item * tree_base_composite::__get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   {

      return m_ptreebase->__get_proper_item(iIndex, piLevel, piCount);

   }


   ::data::tree_item * tree_base_composite::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      return m_ptreebase->__get_proper_item(iIndex, piLevel);

   }


   ::collection::index tree_base_composite::_get_proper_item_index(::data::tree_item * pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   {

      return m_ptreebase->_get_proper_item_index(pitemParam, piLevel, piCount);

   }


   //::collection::count tree_base_composite::get_proper_item_count()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return get_base_item()->get_proper_item_count();

   //}


   ::data::tree_item * tree_base_composite::_get_base_item()
   {

      return m_ptreebase->_get_base_item();

   }


   const ::data::tree_item * tree_base_composite::_get_base_item() const
   {

      return m_ptreebase->_get_base_item();

   }


   //::data::tree_item * tree_base_composite::__previous()
   //{

   //   return nullptr;

   //}


   //::data::tree_item * tree_base_composite::__next()
   //{

   //   return nullptr;

   //}


   ::data::tree_item * tree_base_composite::_insert_item(::item * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item * pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      return m_ptreebase->_insert_item(pitemdataNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent);

   }


   void tree_base_composite::destroy()
   {

      m_ptreebase->destroy();

   }


   void tree_base_composite::_insert_tree(tree_base * ptree)
   {

      m_ptreebase->_insert_tree(ptree);

   }


   bool tree_base_composite::_insert_item(::data::tree_item * pitemNew, enum_relative erelativeNewItem, ::data::tree_item * pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      return m_ptreebase->_insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent);

   }


   void tree_base_composite::erase_all()
   {

      erase_tree_item_descendants();

   }


   void tree_base_composite::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree_base_composite::sort(index ( * pfnCompare )(const ::pointer<tree_item>&, const ::pointer<tree_item>))

   //{

   //   ::pointer<tree_item>pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}


   void tree_base_composite::_update_levels()
   {

      ::collection::index iLevel = -1;

      ::pointer<tree_item>pitem = _get_base_item();

      while (pitem != nullptr)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->_get_child_next_or_parent(&iLevel);

      }

   }


   void tree_base_composite::_001ExpandItem(::data::tree_item * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {


   }

   void tree_base_composite::_001EnsureVisible(::data::tree_item * pitem)
   {


   }


   void tree_base_composite::_001SelectItem(::data::tree_item * pitem)
   {


   }


   void tree_base_composite::_get_selection(::data::tree_item_base_ptr_array & itemptraSelected) const
   {


   }


   bool tree_base_composite::_is_selected(const ::data::tree_item * pitem) const
   {


      return false;

   }


   bool tree_base_composite::_is_selected(const ::item * pitem) const
   {


      return false;

   }


   void tree_base_composite::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
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


   void tree_base_composite::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
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


   void tree_base_composite::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   {


   }


   void tree_base_composite::_001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & context, ::user::element * ptree, const ::int_point & point)
   {


   }


   ::collection::count tree_base_composite::_selection_set(::data::tree_item_ptr_array & itemptra)
   {

      return 0;

   }


   bool tree_base_composite::_selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree_base_composite::_selection_set(::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree_base_composite::_selection_set(::collection::index iIndex, ::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   ::image::image_list * tree_base_composite::get_image_list() const
   {

      return nullptr;

   }


   //void tree_base_composite::signal(::signal * psignal)
   //{

   //}

   ::collection::count tree_base_composite::_tree_count()
   {

      throw ::interface_only();


      return -1;

   }


   tree_base * tree_base_composite::_tree_at(::collection::index iIndex)
   {

      return m_ptreebase->_tree_at(iIndex);

   }


   void tree_base_composite::predicate_each_tree(const ::function < void(tree_base *) > & callback)
   {

      m_ptreebase->predicate_each_tree(callback);

   }


   void tree_base_composite::handle(::topic * ptopic, ::context * pcontext)
   {

      m_ptreebase->handle(ptopic, pcontext);

   }



   //void tree_base_composite::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}



   void tree_base_composite::on_fill_children()
   {

      m_ptreebase->on_fill_children();

   }


   //void tree_base_composite::start_fill_children()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_bFill = true;

   //   fork([this]()
   //   {

   //      fill_children();

   //   });

   //}


   void tree_base_composite::on_tree_layout()
   {

      m_ptreebase->on_tree_layout();

   }


   void tree_base_composite::fill_children()
   {

      m_ptreebase->fill_children();

   }


   //void tree_base_composite::tree_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


} // namespace data



