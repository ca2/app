#include "framework.h"
#include "tree_item.h"
#include "item.h"
#include "listener.h"
#include "tree.h"

#include "acme/template/list.h"


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

         pparent->m_childrena.add(this);

      }

      m_pparent->m_childrena.erase(this);

      m_pparent = pparent;

   }

   
   void tree_item::erase_tree_item()
   {

      erase_tree_item_descendants();

      if(m_pparent)
      {

         m_pparent->m_childrena.erase(this);

      }

   }


   void tree_item::erase_tree_item_descendants()
   {

      m_childrena.predicate_each([](auto p) { p->erase_tree_item(); });

      m_childrena.erase_all();

   }


   tree_item * tree_item::find_next_by_user_data(uptr iUserData)
   {
    
      auto ptreeitem = this;

      while(true)
      {

         ptreeitem = ptreeitem->get_item(e_tree_navigation_expanded_forward);

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


   bool tree_item::erase_item_from_parent()
   {

      tree_item * pitem = this;

      if (pitem->m_pparent == nullptr)
      {

         return true;

      }

      if (!pitem->m_pparent->m_childrena.contains(pitem))
      {

         // self healing?
         pitem->m_pparent = nullptr;

         return false;

      }

      //list_erase(pitem->m_pparent, pitem);

      pitem->m_pparent->m_childrena.erase(pitem);

      pitem->m_pparent = nullptr;

      return true;

   }


   bool tree_item::insert(enum_relative erelative, tree_item * pitemNew)
   {

      if (erelative == e_relative_first_child)
      {

         pitemNew->erase_item_from_parent();

         m_childrena.insert_at(0, pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == e_relative_last_child)
      {

         pitemNew->erase_item_from_parent();

         //list_add(this, pitemNew);

         m_childrena.add(pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == e_relative_previous_sibling)
      {

         ASSERT(m_pparent != nullptr);

         if (m_pparent == nullptr)
         {

            return false;

         }

         auto iFind = m_pparent->m_childrena.find_first(this);

         if(iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_childrena.insert_at(iFind, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if(erelative == e_relative_next_sibling)
      {

         if (m_pparent == nullptr)
         {

            return false;

         }

         auto iFind = m_pparent->m_childrena.find_first(this);

         if (iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_childrena.insert_at(iFind + 1, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if(erelative == e_relative_last_sibling)
      {

         //list_add(m_pparent, pitemNew);

         m_pparent->m_childrena.insert_at(0, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if(erelative == e_relative_replace)
      {

         auto iFind = m_pparent->m_childrena.find_first(this);

         if (iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_childrena.set_at(iFind, pitemNew);

         m_pparent = nullptr;

         //erase_tree_item();

         return true;

      }

      return false;

   }

   
   tree_item * tree_item::get_child_by_user_data(uptr iUserData)
   {

      auto iFind = m_childrena.predicate_find_first([iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

      if (iFind < 0)
         return nullptr;

      return m_childrena[iFind];

   }

   
   void tree_item::get_children(tree_item_ptr_array & ptra)
   {

      for (auto & p : m_childrena)
      {

         ptra.add(p);

      }

   }


   ::count tree_item::get_children_count()
   {

      return m_childrena.count();

   }


   tree_item * tree_item::get_parent()
   {

      return m_pparent;

   }


   ::count tree_item::get_expandable_children_count()
   {

      ::count c = 0;
      
      m_childrena.predicate_each([&c](auto& p)
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

      auto iFind = m_childrena.predicate_find_first([&c, iIndex](auto& p)
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

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_childrena[iFind];

   }


   ::count tree_item::get_proper_descendant_count()
   {

      ::count iCount = 0;

      index iLevel = 0;

      tree_item * pitem = this;

      for(;;)
      {

         pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

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

      auto pprevious = get_previous();

      if(pprevious)
      {

         return pprevious;

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

      if (::is_null(m_pparent))
      {

         return nullptr;

      }

      auto iFind = m_pparent->m_childrena.find_first(this);

      if (iFind > 0)
      {

         return m_pparent->m_childrena[iFind - 1];

      }

      return nullptr;


   }


   tree_item * tree_item::get_next()
   {

      if (!m_pparent)
      {

         return nullptr;

      }

      auto iFind = m_pparent->m_childrena.find_first(this);

      if (iFind >= 0 && iFind < m_pparent->m_childrena.get_upper_bound())
      {

         return m_pparent->m_childrena[iFind + 1];

      }

      return nullptr;

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

      return m_pparent->m_childrena.find_first(this);

   }


   tree_item * tree_item::get_next_or_parent_next(index * piLevel)
   {

      auto pnext = get_next();

      if (pnext)
      {

         return pnext;

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

      if (m_childrena.has_element())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return m_childrena.first();

      }

      return get_next();

   }


   tree_item * tree_item::get_child_next_or_parent(index * piLevel)
   {

      if (m_childrena.has_element())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return m_childrena.first();

      }

      return get_next_or_parent_next(piLevel);

   }


   tree_item * tree_item::get_item(enum_tree_navigation enavigation, index * pindexLevel)
   {

      switch(enavigation)
      {
      case e_tree_navigation_expanded_forward:

         return get_child_next_or_parent(pindexLevel);

      case e_tree_navigation_proper_forward:

         return get_proper_next(pindexLevel);

      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }

   }


   tree_item * tree_item::get_item(enum_relative erelative)
   {

      switch(erelative)
      {
      case e_relative_first_child:
      {
         return m_childrena.first();
      }
      break;
      case e_relative_last_child:
      {
         return m_childrena.last();
      }
      case e_relative_parent:
      {
         return m_pparent;
      }
      break;
      case e_relative_first_sibling:
      {
         return m_pparent->m_childrena.first();
      }
      break;
      case e_relative_previous_sibling:
      {
         return get_previous();
      }
      break;
      case e_relative_next_sibling:
      {
         return get_next();
      }
      break;
      case e_relative_last_sibling:
      {
         return m_pparent->m_childrena.last();
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

      return m_childrena.first();

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

         pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

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

         pitem = pitem->get_item(e_tree_navigation_proper_forward, piLevel);

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

         pitem = pitem->get_item(e_tree_navigation_proper_forward, &iLevel);

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

      return (m_dwState & ::data::e_tree_item_state_expanded) != 0;

   }


   bool tree_item::is_expandable() const
   {

      return (m_dwState & ::data::e_tree_item_state_expandable) != 0;

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

      m_childrena.predicate_each([](auto& p)
         {

            if (p->is_expanded())
            {

               p->on_fill_children();

            }

         });

   }


} // namespace data



