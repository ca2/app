#include "framework.h"
#include "acme/template/list.h"
#include "_data.h"


namespace data
{


   tree_item::tree_item()
   {

      m_iIndexHint      = -1;
      m_dwUser          = 0;
      m_dwState         = 0;
      m_ptree           = nullptr;
      m_pparent         = nullptr;
      m_iLevel          = -1;

   }


   tree_item::~tree_item()
   {

   }


   tree * tree_item::get_tree()
   {

      return m_ptree;

   }


   void tree_item::set_parent(tree_item * pparent)
   {

      //if(m_pparent == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
      if (m_pparent == pparent || pparent == this || is_descendant(pparent))
      {

         return;

      }

      if (::is_set(pparent))
      {

         list_add(pparent, this);

      }

      list_remove(m_pparent, this);

      m_pparent = pparent;

   }

   
   void tree_item::remove_tree_item()
   {

      remove_tree_item_descendants();

      if(m_pparent)
      {

         if(list_contains(m_pparent, this))
         {

            list_remove(m_pparent, this);

         }

      }

   }


   void tree_item::remove_tree_item_descendants()
   {

      list_pred(this, [](auto p) { p->remove_tree_item(); });

      list_remove_all(this);

   }


   tree_item * tree_item::find_next_by_user_data(uptr iUserData)
   {
    
      auto ptreeitem = this;

      while(true)
      {

         ptreeitem = ptreeitem->get_item(TreeNavigationExpandedForward);

         if (!ptreeitem)
         {

            return nullptr;

         }

         if (ptreeitem->m_dwUser == (u32)iUserData)
         {

            return ptreeitem;

         }

      }

   }


   bool tree_item::remove_item_from_parent()
   {

      tree_item * pitem = this;

      if (pitem->m_pparent == nullptr)
      {

         return true;

      }

      if (!list_contains(pitem->m_pparent, pitem))
      {

         // self healing?
         pitem->m_pparent = nullptr;

         return false;

      }

      list_remove(pitem->m_pparent, pitem);

      pitem->m_pparent = nullptr;

      return true;

   }


   bool tree_item::insert(ERelative erelative, tree_item * pitemNew)
   {

      if (erelative == RelativeFirstChild)
      {

         pitemNew->remove_item_from_parent();

         list_add_head(this, pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == RelativeLastChild)
      {

         pitemNew->remove_item_from_parent();

         list_add(this, pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == RelativePreviousSibling)
      {

         ASSERT(m_pparent != nullptr);

         if (m_pparent == nullptr)
         {

            return false;

         }

         index iFind = list_find_first(m_pparent, this);

         if (iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         if (iFind > 0)
         {

            iFind--;

         }

         list_insert_before(m_pparent, this, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;


      }
      else if(erelative == RelativeNextSibling)
      {

         if (m_pparent == nullptr)
         {

            return false;

         }

         index iFind = list_find_first(m_pparent, this);

         if (iFind < 0)
         {

            // self-healing
            m_pparent = nullptr;

            return false;

         }

         list_insert_after(m_pparent, this, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

      }
      else if(erelative == RelativeLastSibling)
      {

         list_add(m_pparent, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

      }
      else if(erelative == RelativeReplace)
      {

         index iFind = list_find_first(m_pparent,this);

         if(iFind < 0)
         {

            m_pparent = nullptr;

            return false;

         }

         list_replace_item(m_pparent, this, pitemNew);

         m_pparent = nullptr;

         remove_tree_item();

      }

      return false;

   }

   
   tree_item * tree_item::get_child_by_user_data(uptr iUserData)
   {

      return list_pred_find(this, [iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

   }

   
   void tree_item::get_children(tree_item_ptr_array & ptra)
   {

      list_pred_add(ptra, this);

   }


   ::count tree_item::get_children_count()
   {

      return list_count(this);

   }


   tree_item * tree_item::get_parent()
   {

      return m_pparent;

   }


   ::count tree_item::get_expandable_children_count()
   {

      ::count c = 0;
      
      list_pred(this, [&c](auto& p)
         {

            if (p->get_children_count() > 0)
            {

               c++;

            }

         });

      return c;

   }


   tree_item * tree_item::get_expandable_child(index iIndex)
   {
      
      ::count c = 0;

      return list_pred_find(this, [&c, iIndex](auto& p)
         {

            if (p->get_children_count() > 0)
            {

               if (c == iIndex)
               {

                  return true;

               }

            }

            return false;

         });

   }


   ::count tree_item::get_proper_descendant_count()
   {

      ::count iCount = 0;

      index iLevel = 0;

      tree_item * pitem = this;

      for(;;)
      {

         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);

         if (pitem == nullptr || iLevel <= 0)
         {

            break;

         }

         iCount++;

      }

      return iCount;

   }


   tree_item * tree_item::get_previous_or_parent(index * piLevel)
   {

      if (m_pprevious)
      {

         return m_pprevious;

      }

      if (m_pparent)
      {

         if (piLevel)
         {

            (*piLevel)--;

         }

         return m_pparent->get_previous_or_parent(piLevel);

      }

      return this;

   }


   tree_item * tree_item::get_previous()
   {

      return m_pprevious;

   }


   tree_item * tree_item::get_next()
   {

      return m_pnext;

   }


   index tree_item::calc_level()
   {

      if (m_iLevel < 0)
      {


         m_iLevel = -1;

         tree_item * p = this;

         while (p != nullptr)
         {

            m_iLevel++;

            p = p->m_pparent;

         }

      }

      return m_iLevel;

   }


   index tree_item::_get_index()
   {

      if (m_pparent == nullptr)
      {

         return 0;

      }

      return list_find_first(m_pparent, this);

   }


   tree_item * tree_item::get_next_or_parent_next(index * piLevel)
   {

      if (m_pnext)
      {

         return m_pnext;

      }

      if (!m_pparent)
      {

         return nullptr;

      }

      if (piLevel)
      {

         (*piLevel)--;

      }

      return m_pparent->get_next_or_parent_next(piLevel);

   }


   tree_item * tree_item::get_child_or_next(index * piLevel)
   {

      if (m_phead)
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return m_phead;

      }

      return m_pnext;

   }


   tree_item * tree_item::get_child_next_or_parent(index * piLevel)
   {

      if (m_phead)
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return m_phead;

      }

      return get_next_or_parent_next(piLevel);

   }


   tree_item * tree_item::get_item(ETreeNavigation enavigation, index * pindexLevel)
   {

      switch(enavigation)
      {
      case TreeNavigationExpandedForward:

         return get_child_next_or_parent(pindexLevel);

      case TreeNavigationProperForward:

         return get_proper_next(pindexLevel);

      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }

   }


   tree_item * tree_item::get_item(ERelative erelative)
   {

      switch(erelative)
      {
      case RelativeFirstChild:
      {
         return m_phead;
      }
      break;
      case RelativeLastChild:
      {
         return m_ptail;
      }
      case RelativeParent:
      {
         return m_pparent;
      }
      break;
      case RelativeFirstSibling:
      {
         return m_pparent->m_phead;
      }
      break;
      case RelativePreviousSibling:
      {
         return m_pprevious;
      }
      break;
      case RelativeNextSibling:
      {
         return m_pnext;
      }
      break;
      case RelativeLastSibling:
      {
         return m_pparent->m_ptail;
      }
      break;
      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }
   }



   tree_item * tree_item::first_child()
   {

      return m_phead;

   }


   string tree_item::get_text() const
   {

      if (!m_pdataitem)
      {

         return "";

      }

      return m_pdataitem->data_item_get_text(m_ptree);

   }


   index tree_item::get_image() const
   {

      if (!m_pdataitem)
      {

         return -1;

      }

      return m_pdataitem->data_item_get_image(m_ptree);

   }


   image_list * tree_item::get_image_list() const
   {

      if (!m_pdataitem)
      {

         return nullptr;

      }
         
      return m_pdataitem->data_item_get_image_list(m_ptree);

   }


   tree_item * tree_item::get_proper_item(index iIndex, index * piLevel)
   {

      if (*piLevel)
      {

         *piLevel = 0;

      }

      tree_item * pitem = this;

      while(pitem && iIndex >= 0)
      {

         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);

         iIndex--;

      }

      if (iIndex < 0)
      {

         return pitem;

      }

      return nullptr;

   }


   index tree_item::get_proper_item_index(tree_item * pitemParam, index * piLevel)
   {
      
      i32 iIndex = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      tree_item * pitem = this;

      while(pitem)
      {

         pitem = pitem->get_item(TreeNavigationProperForward, piLevel);

         if (pitem == pitemParam)
         {

            return iIndex;

         }

         iIndex++;

      }

      return -1;

   }

   
   ::count tree_item::get_proper_item_count()
   {

      tree_item * pitem = this;

      index iLevel = 0;

      ::count iCount = -1;

      while(pitem)
      {

         pitem = pitem->get_item(TreeNavigationProperForward, &iLevel);

         iCount++;

         if (iCount >= 65536)
         {

            break;

         }

         if (iLevel <= 0)
         {

            break;

         }

      }

      return iCount;

   }


   bool tree_item::is_expanded() const
   {

      return (m_dwState & ::data::tree_item_state_expanded) != 0;

   }


   bool tree_item::is_expandable() const
   {

      return (m_dwState & ::data::tree_item_state_expandable) != 0;

   }


   bool tree_item::is_descendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      return pitem->is_ascendant(this);

   }


   bool tree_item::is_ascendant(tree_item * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      tree_item * pparent = m_pparent;

      if (pparent == nullptr)
      {

         return false;

      }

      while(pparent != nullptr)
      {

         if(pparent == pitem)
            return true;

         pparent = pparent->m_pparent;

      }

      return false;

   }


   void tree_item::on_fill_children()
   {

      if (m_pdataitem)
      {

         m_pdataitem->data_item_on_fill_children(this);

      }

      list_pred(this, [](auto& p)
         {

            if (p->is_expanded())
            {

               p->on_fill_children();

            }

         });

   }


} // namespace data



