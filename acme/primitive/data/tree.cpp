#include "framework.h" 
#include "_data.h"


namespace data
{


   tree::tree()
   {

      //defer_create_mutex();

      m_bFill = false;

      //m_proot = __new(tree_item);

      //if (m_proot == nullptr)
      //{

      //   throw ::exception(error_no_memory);

      //}

      m_dwState |= ::data::e_tree_item_state_expandable;

      m_dwState |= ::data::e_tree_item_state_expanded;

      m_ptree = this;


   }


   tree::~tree()
   {

   }


   tree_item * tree::find(const item * pitemdata, index * piIndex)
   {

      index iIndex;

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

      __pointer(::data::tree_item) pitem = this;

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

      if (pitemParam == this)
      {

         return true;

      }
      
      ::data::tree_item * pitem = this;

      for(; pitem != nullptr; pitem = pitem->get_item(e_tree_navigation_expanded_forward))
      {

         if (pitem == pitemParam)
         {

            return true;

         }

      }

      return false;

   }


   void tree::_001OnTreeDataChange()
   {

      update_levels();

   }


   void tree::erase(item * pitemdata, index i)
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


   ::data::tree_item * tree::_get_proper_item(index iIndex, index * piLevel, index * piCount)
   {

      index iCount = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      __pointer(::data::tree_item) pitem = this;

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


   ::data::tree_item* tree::get_proper_item(index iIndex, index* piLevel)
   {

      if (piLevel)
      {

         *piLevel = 0;

      }

      __pointer(::data::tree_item) pitem = this;

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


   index tree::get_proper_item_index(::data::tree_item *pitemParam, index * piLevel, index * piCount)
   {

      i32 iIndex = 0;

      count iCount = 0;

      if (piLevel != nullptr)
      {

         *piLevel = 0;

      }

      __pointer(::data::tree_item) pitem = get_base_item();

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


   //::count tree::get_proper_item_count()
   //{

   //   synchronous_lock synchronouslock(mutex());

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

      __pointer(::data::tree_item) pitemNew = __new(tree_item);

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

      __pointer(tree) ptreeNew = pitemNew;

      if (ptreeNew)
      {

         on_insert_tree(ptreeNew);

      }

      if (pitemRelative == nullptr)
      {

         pitemRelative = this;

      }

      synchronous_lock synchronouslock(mutex());

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

         bOk=pitemRelative->insert(erelativeNewItem, pitemNew);

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

            insert_item(pitemNew, ::data::e_relative_first_child, pitemRelative);

         }
         else
         {

            insert_item(pitemNew, ::data::e_relative_last_sibling, pitemRelative);

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

      return true;

   }


   void tree::erase_all()
   {

      erase_tree_item_descendants();

   }


   void tree::update_tree()
   {

      _001OnTreeDataChange();

   }


   //void tree::sort(index ( * pfnCompare )(const __pointer(tree_item) &, const __pointer(tree_item) &))

   //{

   //   __pointer(tree_item) pitem = get_base_item();

   //   while(pitem != nullptr)
   //   {

   //      pitem->sort_children(pfnCompare);


   //      pitem = pitem->get_child_next_or_parent();

   //   }

   //}

   void tree::update_levels()
   {

      index iLevel = -1;

      __pointer(tree_item) pitem = get_base_item();

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

      /*      for (index i = 0; i < m_treeptra.get_count(); i++)
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
      /*for (index i = 0; i < m_treeptra.get_count(); i++)
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


   ::count   tree::selection_set(::data::tree_item_ptr_array & itemptra)
   {

      return 0;

   }


   bool      tree::selection_set(::data::tree_item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool      tree::selection_set(::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   bool      tree::selection_set(index iIndex, ::data::item * pitem, bool bIfNotInSelection, bool bIfParentInSelection)
   {

      return false;

   }


   image_list * tree::get_image_list() const
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

   //   synchronous_lock synchronouslock(mutex());

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



