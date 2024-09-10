#include "framework.h" 
#include "tree.h"
#include "tree_item.h"
#include "listener.h"
#include "item.h"
////#include "acme/exception/exception.h"
#include "acme/parallelization/synchronous_lock.h"


//void data_tree_item_list_sort(::data::tree_item * pitem, const ::function < bool(const ::data::tree_item *, const ::data::tree_item *) > & functionLess);

namespace data
{


   tree::tree()
   {

      //defer_create_synchronization();

      m_bFill = false;

      //m_proot = ::place(new tree_item());

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      m_dwState |= ::data::e_tree_item_state_expandable;

      m_dwState |= ::data::e_tree_item_state_expanded;

      m_ptree = this;

      m_pparent = ::place(new ::data::tree_item ());

   }


   tree::~tree()
   {

   }


   tree_item * tree::find(const item * pitemdata, ::collection::index * piIndex)
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

      ::pointer<::data::tree_item>pitem = this;

      for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      {
         
         if(pitem->m_pdataitem == pitemdata)
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

   
   bool tree::contains(const item * pitemdata)
   {
      
      return find(pitemdata) != nullptr;

   }


   bool tree::contains(const tree_item * pitemParam)
   {

      return tree_item::contains(pitemParam);

      //if (pitemParam == this)
      //{

      //   return true;

      //}
      //
      //::data::tree_item * pitem = this;

      //for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      //{

      //   if (pitem == pitemParam)
      //   {

      //      return true;

      //   }

      //}

      //return false;

   }


   void tree::_001OnTreeDataChange()
   {

      update_levels();

   }


   void tree::erase(item * pitemdata, ::collection::index i)
   {
      
      tree_item * pitem = find(pitemdata, &i);

      if (pitem == nullptr)
      {

         return;

      }

      return erase(pitem);

   }


   void tree::erase(tree_item_ptr_array & itemptra)
   {

      for(i32 i = 0; i < itemptra.get_count(); i++)
      {

         erase(itemptra[i]);

      }

   }


   void tree::erase(tree_item * pitem)
   {

      if (pitem->m_ptree == this)
      {

         pitem->erase_tree_item();

      }

   }


   void tree::sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess)
   {

      m_treeitema.predicate_sort(functionLess);

   }


   ::data::tree_item * tree::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel, ::collection::index * piCount)
   {

      ::collection::index iCount = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item>pitem = this;

      while(pitem && iIndex >= 0)
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


   ::data::tree_item* tree::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (piLevel)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item>pitem = this;

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


   ::collection::index tree::get_proper_item_index(::data::tree_item *pitemParam, ::collection::index * piLevel, ::collection::index * piCount)
   {

      i32 iIndex = 0;

      ::collection::count iCount = 0;

      if (piLevel != nullptr)
      {

         *piLevel = 0;

      }

      ::pointer<::data::tree_item>pitem = get_base_item();

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


   //::collection::count tree::get_proper_item_count()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   return get_base_item()->get_proper_item_count();

   //}


   ::data::tree_item * tree::get_base_item()
   {

      return this;

   }


   const ::data::tree_item * tree::get_base_item() const
   {

      return this;

   }


   ::data::tree_item * tree::____previous()
   {

      return nullptr;

   }


   ::data::tree_item * tree::____next()
   {

      return nullptr;

   }


   ::data::tree_item * tree::insert_item(::data::item * pitemdataNew, enum_relative erelativeNewItem, ::data::tree_item *pitemRelative, bool bVoidTreeDataChangeEvent)
   {

      if (pitemRelative == nullptr)
      {

         pitemRelative = this;

      }

      if(erelativeNewItem == e_relative_replace)
      {

         if(!contains(pitemRelative))
            return nullptr;

         pitemRelative->m_pdataitem = pitemdataNew;

         return pitemRelative;

      }

      ::pointer<::data::tree_item>pitemNew = ::place(new tree_item());

      if(pitemNew == nullptr)
         return nullptr;

      if(!insert_item(pitemNew, erelativeNewItem, pitemRelative, bVoidTreeDataChangeEvent))
      {

         return nullptr;

      }

      pitemNew->m_pdataitem = pitemdataNew;

      return pitemNew;

   }


   void tree::on_insert_tree(tree * ptree)
   {

      m_treea.add(ptree);

   }


   bool tree::insert_item(::data::tree_item *pitemNew, enum_relative erelativeNewItem, ::data::tree_item *pitemRelative, bool bVoidTreeDataChangeEvent)
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

         pitemNew->m_dwUser         = pitemRelative->m_dwUser;
         pitemNew->m_dwMetaData     = pitemRelative->m_dwMetaData;
         pitemNew->m_dwState        = pitemRelative->m_dwState;
         pitemNew->m_pdataitem      = pitemRelative->m_pdataitem;

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


   void tree::erase_all()
   {

      erase_tree_item_descendants();

   }


   void tree::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree::sort(index ( * pfnCompare )(const ::pointer<tree_item>&, const ::pointer<tree_item>))

   //{

   //   ::pointer<tree_item>pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}

   void tree::update_levels()
   {

      ::collection::index iLevel = -1;

      ::pointer<tree_item>pitem = get_base_item();

      while (pitem != nullptr)
      {

         pitem->m_iLevel = iLevel;

         pitem = pitem->get_child_next_or_parent(&iLevel);

      }

   }


   void tree::_001ExpandItem(::data::tree_item * pitem, const ::action_context & context, bool bExpand, bool bRedraw, bool bLayout)
   {


   }

   void tree::_001EnsureVisible(::data::tree_item * pitem)
   {


   }


   void tree::_001SelectItem(::data::tree_item * pitem)
   {


   }

   void tree::get_selection(::data::tree_item_ptr_array & itemptraSelected) const
   {


   }


   bool tree::is_selected(const ::data::tree_item * pitem) const
   {


      return false;

   }


   bool tree::is_selected(const ::data::item * pitem) const
   {


      return false;

   }


   void tree::_001OnItemExpand(::data::tree_item * pitem, const ::action_context & context)
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


   void tree::_001OnItemCollapse(::data::tree_item * pitem, const ::action_context & context)
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


   void tree::_001OnOpenItem(::data::tree_item * pitem, const ::action_context & context)
   {


   }


   void tree::_001OnItemContextMenu(::data::tree_item * pitem, const ::action_context & context, ::user::primitive * ptree, const ::point_i32 & point)
   {


   }


   ::collection::count tree::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      return 0;

   }


   bool tree::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree::selection_set(::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool tree::selection_set(::collection::index iIndex, ::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   ::image::image_list * tree::get_image_list() const
   {

      return nullptr;

   }


   //void tree::signal(::signal * psignal)
   //{

   //}


   void tree::handle(::topic * ptopic, ::context * pcontext)
   {

      for (auto& ptree : m_treea)
      {

         ptree->handle(ptopic, pcontext);

      }

   }



   //void tree::handle(::topic * ptopic, ::context * pcontext)
   //{

   //}



   void tree::on_fill_children()
   {

   }


   //void tree::start_fill_children()
   //{

   //   _synchronous_lock synchronouslock(this->synchronization());

   //   m_bFill = true;

   //   fork([this]()
   //   {

   //      fill_children();

   //   });

   //}


   void tree::on_tree_layout()
   {

   }


   void tree::fill_children()
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


   //void tree::tree_layout(::draw2d::graphics_pointer & pgraphics)
   //{

   //}


} // namespace data



