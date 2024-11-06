#include "framework.h"
#include "tree_item.h"
#include "item.h"
#include "listener.h"
#include "tree.h"



#include "acme/template/list.h"


//void data_tree_item_list_swap(
//   const ::pointer < ::data::tree_item > & pitemA, 
//   const ::pointer < ::data::tree_item > & pitemB)
//{
//
//   auto pitemAPrevious = pitemA->____previous();
//
//   auto pitemANext = pitemA->____next();
//
//   auto pitemBPrevious = pitemB->____previous();
//
//   auto pitemBNext = pitemB->____next();
//
//   if (pitemAPrevious == pitemB)
//   {
//
//      if (pitemB->____next() != pitemA)
//      {
//
//         throw "error";
//
//      }
//
//      if (pitemANext)
//      {
//
//         pitemANext->____previous() = pitemB;
//
//      }
//
//      if (pitemBPrevious)
//      {
//
//         pitemBPrevious->____next() = pitemA;
//
//      }
//
//      pitemA->____previous() = pitemB->____previous();
//
//      pitemB->____next() = pitemA->____next();
//
//      pitemA->____next() = pitemB;
//
//      pitemB->____previous() = pitemA;
//
//   }
//   else if (pitemANext == pitemB)
//   {
//
//      if (pitemB->____previous() != pitemA)
//      {
//
//         throw "error";
//
//      }
//
//      if (pitemAPrevious)
//      {
//
//         pitemAPrevious->____next() = pitemB;
//
//      }
//
//      if (pitemBNext)
//      {
//
//         pitemBNext->____previous() = pitemA;
//
//      }
//
//      pitemA->____next() = pitemB->____next();
//
//      pitemB->____previous() = pitemA->____previous();
//
//      pitemA->____previous() = pitemB;
//
//      pitemB->____next() = pitemA;
//
//   }
//   else
//   {
//
//      pitemA->____previous() = pitemBPrevious;
//
//      pitemA->____next() = pitemBNext;
//
//      pitemB->____previous() = pitemAPrevious;
//
//      pitemB->____next() = pitemANext;
//
//      if (::is_set(pitemAPrevious))
//      {
//
//         pitemAPrevious->____next() = pitemB;
//
//      }
//
//      if (::is_set(pitemANext))
//      {
//
//         pitemANext->____previous() = pitemB;
//
//      }
//
//      if (::is_set(pitemBPrevious))
//      {
//
//         pitemBPrevious->____next() = pitemA;
//
//      }
//
//      if (::is_set(pitemBNext))
//      {
//
//         pitemBNext->____previous() = pitemA;
//
//      }
//
//   }
//
//}
//
//void data_tree_item_list_sort(::data::tree_item * pitem, const ::function < bool(const ::data::tree_item *, const ::data::tree_item *) > & functionLess)
//{
//
//   if (::is_null(pitem->____head()) || ::is_null(pitem->____tail()))
//   {
//
//      return;
//
//   }
//
//   ::pointer_array < ::data::tree_item > stackLowerBound;
//   ::pointer_array < ::data::tree_item > stackUpperBound;
//
//   ::pointer < ::data::tree_item > iLowerBound;
//   ::pointer < ::data::tree_item > iUpperBound;
//   ::pointer < ::data::tree_item > iLPos, iUPos, iMPos;
//   ::pointer < ::data::tree_item > p1;
//   ::pointer < ::data::tree_item > p2;
//
//   stackLowerBound.push(pitem->____head());
//   stackUpperBound.push(pitem->____tail());
//   while (true)
//   {
//      iLowerBound = stackLowerBound.pop();
//      iUpperBound = stackUpperBound.pop();
//      iLPos = iLowerBound;
//      iUPos = iUpperBound;
//      p1 = iLPos;
//      p2 = iUPos;
//      iMPos = p1;
//      while (p1 != p2)
//      {
//         p2 = p2->____previous();
//         if (p1 == p2)
//         {
//            iMPos = p1;
//            break;
//         }
//         p1 = p1->____next();
//         if (p1 == p2)
//         {
//            iMPos = p1;
//            break;
//         }
//      }
//      while (true)
//      {
//         while (true)
//         {
//            if (iMPos == iUPos)
//               break;
//            if (functionLess(iMPos, iUPos))
//            {
//               iUPos = iUPos->____previous();
//            }
//            else
//            {
//               data_tree_item_list_swap(iMPos, iUPos);
//               swap(iMPos, iUPos);
//               if (iLowerBound == iMPos)
//               {
//                  iLowerBound = iUPos;
//               }
//               else if (iLowerBound == iUPos)
//               {
//                  iLowerBound = iMPos;
//               }
//               if (iUpperBound == iMPos)
//               {
//                  iUpperBound = iUPos;
//               }
//               else if (iUpperBound == iUPos)
//               {
//                  iUpperBound = iMPos;
//               }
//               break;
//            }
//         }
//         if (iMPos == iUPos)
//            break;
//         iMPos = iUPos;
//         while (true)
//         {
//            if (iMPos == iLPos)
//               break;
//            if (functionLess(iLPos, iMPos))
//            {
//               iLPos = iLPos->____next();
//            }
//            else
//            {
//               data_tree_item_list_swap(iLPos, iMPos);
//               swap(iLPos, iMPos);
//               if (iLowerBound == iMPos)
//               {
//                  iLowerBound = iLPos;
//               }
//               else if (iLowerBound == iLPos)
//               {
//                  iLowerBound = iMPos;
//               }
//               if (iUpperBound == iMPos)
//               {
//                  iUpperBound = iLPos;
//               }
//               else if (iUpperBound == iLPos)
//               {
//                  iUpperBound = iMPos;
//               }
//               break;
//            }
//         }
//         if (iMPos == iLPos)
//            break;
//         iMPos = iLPos;
//      }
//      if (list_item_is_before((const ::data::tree_item *)iLowerBound, (const ::data::tree_item *)iMPos->____previous()))
//      {
//         stackLowerBound.push(iLowerBound);
//         stackUpperBound.push(iMPos->____previous());
//      }
//      if (list_item_is_before((const ::data::tree_item *)iMPos->____next(), (const ::data::tree_item *)iUpperBound))
//      {
//         stackLowerBound.push(iMPos->____next());
//         stackUpperBound.push(iUpperBound);
//      }
//      if (stackLowerBound.get_size() == 0)
//         break;
//   }
//   pitem->____head() = list_item_calculate_head((const ::data::tree_item *)pitem->____head());
//   pitem->____tail() = list_item_calculate_tail((const ::data::tree_item *)pitem->____tail());
//
//}

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
      m_pparent         = nullptr;

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

         pparent->m_treeitema.add_unique(this);

      }

      m_pparent->m_treeitema.erase(this);

      m_pparent = pparent;

   }

   
   void tree_item::erase_tree_item()
   {

      erase_tree_item_descendants();

      if(m_pparent)
      {

         if(m_pparent->m_treeitema.contains(this))
         {

            m_pparent->m_treeitema.erase(this);

         }

      }

   }


   void tree_item::erase_tree_item_descendants()
   {

      for (auto & p : m_treeitema)
      {

         p->erase_tree_item_descendants();

      }

      //list_predicate(this, [](auto p) { p->erase_tree_item(); });

      //list_erase_all(this);

      m_treeitema.clear();

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

         if (ptreeitem->m_dwUser == (unsigned int)iUserData)
         {

            return ptreeitem;

         }

      }

   }

   void tree_item::destroy()
   {

      m_pparent.release();

      m_treeitema.destroy();

      m_ptree = nullptr;

   }

   bool tree_item::erase_item_from_parent()
   {

      tree_item * pitem = this;

      if (pitem->m_pparent == nullptr)
      {

         return true;

      }

      if (!pitem->m_pparent->m_treeitema.contains(pitem))
      {

         // self healing?
         pitem->m_pparent = nullptr;

         return false;

      }

      pitem->m_pparent->m_treeitema.erase(pitem);

      pitem->m_pparent = nullptr;

      return true;

   }


   bool tree_item::contains(const tree_item * ptreeitem)
   {

      if (ptreeitem == this)
      {

         return true;

      }

      for (auto & p : m_treeitema)
      {

         if (p->contains(ptreeitem))
         {

            return true;

         }

      }

      return false;

   }


   bool tree_item::insert(enum_relative erelative, tree_item * pitemNew)
   {

      if (contains(pitemNew))
      {

         throw ::exception(error_wrong_state);

      }

      if (erelative == e_relative_first_child)
      {

         pitemNew->erase_item_from_parent();

         m_treeitema.insert_at(0, pitemNew);

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->m_pparent = this;

         return true;

      }
      else if (erelative == e_relative_last_child)
      {

         pitemNew->erase_item_from_parent();

         m_treeitema.add(pitemNew);

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

         auto iFind = m_pparent->m_treeitema.find_first(this);

         if(iFind < 0)
         {

            // self-healinng
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema.insert_at(iFind, pitemNew);

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

         auto iFind = m_pparent->m_treeitema.find_first(this);

         if(iFind < 0)
         {

            // self-healing
            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema.insert_at(iFind + 1, pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if(erelative == e_relative_last_sibling)
      {

         m_pparent->m_treeitema.add(pitemNew);

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->m_pparent = m_pparent;

         return true;

      }
      else if(erelative == e_relative_replace)
      {

         auto iFind = m_pparent->m_treeitema.find_first(this);

         if(iFind < 0)
         {

            m_pparent = nullptr;

            return false;

         }

         m_pparent->m_treeitema[iFind] = pitemNew;

         m_pparent = nullptr;

         erase_tree_item();

         return true;

      }

      return false;

   }


   void tree_item::sort_children(const ::function < bool(const ::data::tree_item * p1, const ::data::tree_item * p2) > & functionLess)
   {

      //data_tree_item_list_sort(this, functionLess);

      m_treeitema.predicate_sort(functionLess);

   }
   
   tree_item * tree_item::get_child_by_user_data(uptr iUserData)
   {

      auto iFind = m_treeitema.predicate_find_first([iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

      if (iFind < 0)
      {

         return nullptr;

      }

      return m_treeitema[iFind];

   }

   
   void tree_item::get_children(tree_item_ptr_array & ptra)
   {

      ptra.append(m_treeitema);

   }


   ::collection::count tree_item::get_children_count()
   {

      return m_treeitema.get_count();

   }


   tree_item * tree_item::get_parent()
   {

      return m_pparent;

   }


   ::collection::count tree_item::get_expandable_children_count()
   {

      ::collection::count c = 0;
      
      for(auto & p : m_treeitema)
      {

         if (p->get_children_count() > 0)
         {

            c++;

         }

      }

      return c;

   }


   tree_item * tree_item::get_expandable_child(::collection::index iIndex)
   {
      
      ::collection::count c = 0;

      auto iFind = m_treeitema.predicate_find_first([&c, iIndex](auto& p)
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

      return m_treeitema[iFind];

   }


   ::collection::count tree_item::get_proper_descendant_count()
   {

      ::collection::count iCount = 0;

      ::collection::index iLevel = 0;

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


   tree_item * tree_item::get_previous_or_parent(::collection::index * piLevel)
   {

      if (____previous())
      {

         return ____previous();

      }

      if (m_pparent)
      {

         return m_pparent;

         //if (piLevel)
         //{

         //   (*piLevel)--;

         //}

         //return m_pparent->get_previous_or_parent(piLevel);

      }

      return nullptr;

   }


   tree_item * tree_item::get_previous()
   {

      return ____previous();

   }


   tree_item * tree_item::get_next()
   {

      return ____next();

   }


   ::collection::index tree_item::calc_level()
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


   ::data::tree_item * tree_item::____previous()
   {

      if (::is_null(m_pparent))
      {

         return nullptr;

      }

      auto iFind = m_pparent->m_treeitema.find_first(this);

      if (iFind <= 0)
      {

         return nullptr;

      }

      return m_pparent->m_treeitema[iFind - 1];

   }


   ::data::tree_item * tree_item::____next()
   {

     if (::is_null(m_pparent))
      {

         return nullptr;

      }

      auto iFind = m_pparent->m_treeitema.find_first(this);

      if (iFind < 0 || iFind >= m_pparent->m_treeitema.get_upper_bound())
      {

         return nullptr;

      }

      return m_pparent->m_treeitema[iFind + 1];

   }


   ::data::tree_item * tree_item::____head()
   {

      if (m_treeitema.is_empty())
      {

         return nullptr;

      }

      return m_treeitema.first();

   }


   ::data::tree_item * tree_item::____tail()
   {

      if (m_treeitema.is_empty())
      {

         return nullptr;

      }

      return m_treeitema.last();

   }


   ::collection::index tree_item::_get_index()
   {

      if (m_pparent == nullptr)
      {

         return 0;

      }

      return m_pparent->m_treeitema.find_first(this);

   }


   tree_item * tree_item::get_next_or_parent_next(::collection::index * piLevel)
   {

      if (____next())
      {

         return ____next();

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


   tree_item * tree_item::get_child_or_next(::collection::index * piLevel)
   {

      if (____head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return ____head();

      }

      return ____next();

   }


   tree_item * tree_item::get_child_next_or_parent(::collection::index * piLevel)
   {

      if (____head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return ____head();

      }

      return get_next_or_parent_next(piLevel);

   }


   tree_item * tree_item::get_item(enum_tree_navigation enavigation, ::collection::index * pindexLevel)
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
         return ____head();
      }
      break;
      case e_relative_last_child:
      {
         return ____tail();
      }
      case e_relative_parent:
      {
         return m_pparent;
      }
      break;
      case e_relative_first_sibling:
      {
         return m_pparent->____head();
      }
      break;
      case e_relative_previous_sibling:
      {
         return ____previous();
      }
      break;
      case e_relative_next_sibling:
      {
         return ____next();
      }
      break;
      case e_relative_last_sibling:
      {
         return m_pparent->____tail();
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

      return ____head();

   }


   string tree_item::get_text() const
   {

      if (!m_pdataitem)
      {

         return "";

      }

      return m_pdataitem->data_item_get_text(m_ptree);

   }


   ::collection::index tree_item::get_image() const
   {

      if (!m_pdataitem)
      {

         return -1;

      }

      return m_pdataitem->data_item_get_image(m_ptree);

   }


   ::image::image_list * tree_item::get_image_list() const
   {

      if (!m_pdataitem)
      {

         return nullptr;

      }
         
      return m_pdataitem->data_item_get_image_list(m_ptree);

   }


   tree_item * tree_item::get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
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


   ::collection::index tree_item::get_proper_item_index(tree_item * pitemParam, ::collection::index * piLevel)
   {
      
      int iIndex = 0;

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

   
   ::collection::count tree_item::get_proper_item_count()
   {

      tree_item * pitem = this;

      ::collection::index iLevel = 0;

      ::collection::count iCount = -1;

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

      for(auto & p : m_treeitema)
         {

            if (p->is_expanded())
            {

               p->on_fill_children();

            }

         };

   }


} // namespace data



