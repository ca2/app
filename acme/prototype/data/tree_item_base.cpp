// From tree_item_base.cpp on 2025-03-28 22:37 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "tree_item_base.h"
#include "item.h"
#include "listener.h"
#include "tree.h"
#include "acme/exception/interface_only.h"


#include "acme/template/list.h"


//void data_tree_item_list_swap(
//   const ::pointer < ::data::tree_item_base > & pitemA, 
//   const ::pointer < ::data::tree_item_base > & pitemB)
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
//void data_tree_item_list_sort(::data::tree_item_base * pitem, const ::function < bool(const ::data::tree_item_base *, const ::data::tree_item_base *) > & functionLess)
//{
//
//   if (::is_null(pitem->____head()) || ::is_null(pitem->____tail()))
//   {
//
//      return;
//
//   }
//
//   ::pointer_array < ::data::tree_item_base > stackLowerBound;
//   ::pointer_array < ::data::tree_item_base > stackUpperBound;
//
//   ::pointer < ::data::tree_item_base > iLowerBound;
//   ::pointer < ::data::tree_item_base > iUpperBound;
//   ::pointer < ::data::tree_item_base > iLPos, iUPos, iMPos;
//   ::pointer < ::data::tree_item_base > p1;
//   ::pointer < ::data::tree_item_base > p2;
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
//      if (list_item_is_before((const ::data::tree_item_base *)iLowerBound, (const ::data::tree_item_base *)iMPos->____previous()))
//      {
//         stackLowerBound.push(iLowerBound);
//         stackUpperBound.push(iMPos->____previous());
//      }
//      if (list_item_is_before((const ::data::tree_item_base *)iMPos->____next(), (const ::data::tree_item_base *)iUpperBound))
//      {
//         stackLowerBound.push(iMPos->____next());
//         stackUpperBound.push(iUpperBound);
//      }
//      if (stackLowerBound.get_size() == 0)
//         break;
//   }
//   pitem->____head() = list_item_calculate_head((const ::data::tree_item_base *)pitem->____head());
//   pitem->____tail() = list_item_calculate_tail((const ::data::tree_item_base *)pitem->____tail());
//
//}

namespace data
{


   tree_item_base::tree_item_base()
   {

      m_iIndexHint      = -1;
      m_dwUser          = 0;
      m_dwState         = 0;
      //m_ptree           = nullptr;
      //_get_parent()         = nullptr;
      m_iLevel          = -1;
      //_get_parent()         = nullptr;

   }


   tree_item_base::~tree_item_base()
   {

   }


   tree_base * tree_item_base::_get_tree() const
   {

      //return m_ptree;

      throw ::interface_only();

      return nullptr;

   }


   void tree_item_base::_set_tree(tree_base * ptree)
   {

      throw ::interface_only();

   }


   //void tree_item_base::set_parent(tree_item_base * pparent)
   //{

   //   //if(_get_parent() == pparent || pparent == this || is_descendant(pparent) || is_ascendant(pparent))
   //   if (_get_parent() == pparent || pparent == this || is_descendant(pparent))
   //   {

   //      return;

   //   }

   //   if (::is_set(pparent))
   //   {

   //      pparent->m_treeitema2.add_unique(this);

   //   }

   //   _get_parent()->m_treeitema2.erase(this);

   //   _get_parent() = pparent;

   //   for (auto pitem : _get_parent()->m_treeitema2)
   //   {

   //      pitem->clear_cache();

   //   }

   //}

   
   void tree_item_base::erase_tree_item()
   {

      erase_tree_item_descendants();

      if(_get_parent())
      {

         _get_parent()->_erase_child(this);

      }

   }



   void tree_item_base::_set_parent(tree_item_base * ptreeitembase)
   {


      throw interface_only();
      }


   void tree_item_base::_erase_child(tree_item_base * ptreeitem)
   {

      auto iIndex = _find_child(ptreeitem);

      if (iIndex < 0)
      {

         return;

      }

      _erase_child_at(iIndex);

      predicate_each([](auto pitem)
      {

         pitem->clear_cache();

         return true;

      });

   }


   void tree_item_base::predicate_each(const ::function < bool(tree_item_base *) > & callback)
   {

      auto c = get_children_count();

      for (::collection::index i = 0; i < c; i++)
      {

         auto pitem = _child_at(i);

         if (!callback(pitem))
         {

            break;

         }

      }

   }


   ::collection::index tree_item_base::predicate_find_first(const ::function < bool(tree_item_base *) > & callback)
   {

      auto c = get_children_count();

      for (::collection::index i = 0; i < c; i++)
      {

         auto pitem = _child_at(i);

         if (callback(pitem))
         {

            return i;

         }

      }

      return -1;

   }


   void tree_item_base::_set_data_item(::data::item * pdataitem)
   {

      throw ::interface_only();

   }

   void tree_item_base::_erase_child_at(::collection::index i)
   {

      throw ::interface_only();

   }


   void tree_item_base::_insert_child_at(::collection::index i, tree_item_base * ptreeitemNew)
   {

      throw ::interface_only();

   }


   void tree_item_base::_add_child(tree_item_base * ptreeitemNew)
   {

      throw ::interface_only();

   }


   void tree_item_base::_set_child_at(::collection::index i, tree_item_base * ptreeitemSet)
   {

      throw ::interface_only();

   }


   void tree_item_base::_erase_children()
   {

      throw ::interface_only();

   }


   tree_item_base * tree_item_base::_child_at(::collection::index i) const
   {

      throw ::interface_only();

      return nullptr;

   }


   ::collection::index tree_item_base::_find_child(::data::tree_item_base * pitreeitem) const
   {

      throw ::interface_only();

      return -1;

   }



   bool tree_item_base::_contains_child(tree_item_base * ptreeitem) const

   {

      auto i = _find_child(ptreeitem);

      if (i < 0)
      {

         return false;

      }

      return true;

   }


   //::collection::index tree_item_base::_find_child(tree_item_base * ptreeitem) const
   //{

   //   throw ::interface_only();

   //   return -1;

   //}


   void tree_item_base::erase_tree_item_descendants()
   {

      predicate_each([](auto p)
      {

         p->erase_tree_item_descendants();

         p->clear_cache();

         return true;

      });

      //list_predicate(this, [](auto p) { p->erase_tree_item(); });

      //list_erase_all(this);

      _erase_children();

      clear_cache();

   }


   tree_item_base * tree_item_base::_find_next_by_user_data(uptr iUserData)
   {
    
      auto ptreeitem = this;

      while(true)
      {

         ptreeitem = ptreeitem->_get_item(e_tree_navigation_expanded_forward);

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


   void tree_item_base::clear_cache()
   {

      //m_bPrevious = false;
      //m_bNext = false;
      m_iIndex = -2;

   }


   void tree_item_base::destroy()
   {

      ::particle::destroy();
      //_get_parent().release();

      //m_treeitema2.destroy();

      //m_ptree = nullptr;

   }

   bool tree_item_base::erase_item_from_parent()
   {

      tree_item_base * pitem = this;

      if (pitem->_get_parent() == nullptr)
      {

         return true;

      }

      if (!pitem->_get_parent()->_contains_child(pitem))
      {

         // self healing?
         pitem->_set_parent(nullptr);

         return false;

      }

      pitem->_get_parent()->_erase_child(pitem);

      pitem->_get_parent()->predicate_each([](auto p)
      {

         p->clear_cache();


         return true;

      });

      pitem->_set_parent(nullptr);

      return true;

   }


   bool tree_item_base::_contains(const tree_item_base * ptreeitem)
   {

      if (ptreeitem == this)
      {

         return true;

      }

      bool bContains = false;

      predicate_each([ptreeitem, &bContains](auto p)
      {

         bContains = p->_contains(ptreeitem);

         return !bContains;

         });

      return bContains;

   }


   bool tree_item_base::_insert(enum_relative erelative, tree_item_base * pitemNew)
   {

      if (_contains(pitemNew))
      {

         throw ::exception(error_wrong_state);

      }

      if (erelative == e_relative_first_child)
      {

         pitemNew->erase_item_from_parent();

         _insert_child_at(0, pitemNew);

         predicate_each([](auto pitem)
         {

            pitem->clear_cache();

            return true;

         });

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->_set_parent(this);

         return true;

      }
      else if (erelative == e_relative_last_child)
      {

         pitemNew->erase_item_from_parent();

         _add_child(pitemNew);

         predicate_each([](auto pitem)
         {

            pitem->clear_cache();

            return true;

         });

         pitemNew->m_iLevel = m_iLevel + 1;

         pitemNew->_set_parent(this);

         return true;

      }
      else if (erelative == e_relative_previous_sibling)
      {

         ASSERT(_get_parent() != nullptr);

         if (_get_parent() == nullptr)
         {

            return false;

         }

         auto iFind = _get_parent()->_find_child(this);

         if(iFind < 0)
         {

            // self-healinng
            _set_parent(nullptr);

            return false;

         }

         _get_parent()->_insert_child_at(iFind, pitemNew);

         _get_parent()->predicate_each([](auto pitem)
         {

            pitem->clear_cache();

            return true;

         });


         pitemNew->m_iLevel = m_iLevel;

         pitemNew->_set_parent(_get_parent());

         return true;

      }
      else if(erelative == e_relative_next_sibling)
      {

         if (_get_parent() == nullptr)
         {

            return false;

         }

         auto iFind = _get_parent()->_find_child(this);

         if(iFind < 0)
         {

            // self-healing
            _set_parent( nullptr);

            return false;

         }

         _get_parent()->_insert_child_at(iFind + 1, pitemNew);

         _get_parent()->predicate_each([](auto & pitem)
         {

            pitem->clear_cache();

            return true;

         });

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->_set_parent(_get_parent());

         return true;

      }
      else if(erelative == e_relative_last_sibling)
      {

         _get_parent()->_add_child(pitemNew);

         _get_parent()->predicate_each([](auto & pitem)
         {

            pitem->clear_cache();

            return true;

         });

         pitemNew->m_iLevel = m_iLevel;

         pitemNew->_set_parent(_get_parent());

         return true;

      }
      else if(erelative == e_relative_replace)
      {

         auto iFind = _get_parent()->_find_child(this);

         if(iFind < 0)
         {

            _set_parent(nullptr);

            return false;

         }

         _get_parent()->_set_child_at(iFind, pitemNew);

         _get_parent()->predicate_each([](auto & pitem)
         {

            pitem->clear_cache();

            return true;

         });

         _set_parent(nullptr);

         erase_tree_item();

         return true;

      }

      return false;

   }


   //void tree_item_base::sort_children(const ::function < bool(const ::data::tree_item_base * p1, const ::data::tree_item_base * p2) > & functionLess)
   //{

   //   //data_tree_item_list_sort(this, functionLess);

   //   m_treeitema2.predicate_sort(functionLess);

   //   for (auto & pitem : m_treeitema2)
   //   {

   //      pitem->clear_cache();

   //   }


   //}
   
   tree_item_base * tree_item_base::_get_child_by_user_data(uptr iUserData)
   {

      auto iFind = predicate_find_first([iUserData](auto p)
         {

            return p->m_dwUser == iUserData;

         });

      if (iFind < 0)
      {

         return nullptr;

      }

      return _child_at(iFind);

   }

   
   void tree_item_base::_get_children(::pointer_array < tree_item_base > & ptra)
   {
      predicate_each([&ptra](auto p)
      {
         ptra.add_item(p);

         return true;
      });

   }


   ::collection::count tree_item_base::get_children_count()
   {

      throw ::interface_only();

      return -1;

   }


   tree_item_base * tree_item_base::_get_parent()
   {

      throw ::interface_only();

      return nullptr;

   }


   ::collection::count tree_item_base::get_expandable_children_count()
   {

      ::collection::count c = 0;
      
      predicate_each([&c](auto p)
      {

         if (p->get_children_count() > 0)
         {

            c++;

         }

         return true;

      });

      return c;

   }


   tree_item_base * tree_item_base::_get_expandable_child(::collection::index iIndex)
   {
      
      ::collection::count c = 0;

      auto iFind = predicate_find_first([&c, iIndex](auto& p)
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

      return _child_at(iFind);

   }


   ::collection::count tree_item_base::get_proper_descendant_count()
   {

      ::collection::count iCount = 0;

      ::collection::index iLevel = 0;

      tree_item_base * pitem = this;

      for(;;)
      {

         pitem = pitem->_get_item(e_tree_navigation_proper_forward, &iLevel);

         if (pitem == nullptr || iLevel <= 0)
         {

            break;

         }

         iCount++;

      }

      return iCount;

   }


   tree_item_base * tree_item_base::_get_previous_or_parent(::collection::index * piLevel)
   {

      if (__previous())
      {

         return __previous();

      }

      if (_get_parent())
      {

         return _get_parent();

         //if (piLevel)
         //{

         //   (*piLevel)--;

         //}

         //return _get_parent()->get_previous_or_parent(piLevel);

      }

      return nullptr;

   }


   tree_item_base * tree_item_base::_get_previous()
   {

      return __previous();

   }


   tree_item_base * tree_item_base::_get_next()
   {

      return __next();

   }


   ::collection::index tree_item_base::calc_level()
   {

      if (m_iLevel < 0)
      {

         m_iLevel = -1;

         tree_item_base * p = this;

         while (p != nullptr)
         {

            m_iLevel++;

            p = p->_get_parent();

         }

      }

      return m_iLevel;

   }


   ::data::tree_item_base * tree_item_base::__previous()
   {

      m_bPrevious = true;

      if (::is_null(_get_parent()))
      {

         //m_pprevious2.release();

         return nullptr;

      }

      auto iFind = _get_index();

      if (iFind <= 0)
      {

         // m_pprevious2.release();

         return nullptr;

      }

      return _get_parent()->_child_at(iFind - 1);

   }


   ::data::tree_item_base * tree_item_base::__next()
   {

      m_bNext = true;

     if (::is_null(_get_parent()))
      {

        //m_pnext2.release();

         return nullptr;

      }

      auto iFind = _get_index();

      if (iFind < 0 || iFind >= _get_parent()->get_children_count() - 1)
      {

         // m_pnext2.release();

         return nullptr;

      }

      return _get_parent()->_child_at(iFind + 1);

   }


   ::data::tree_item_base * tree_item_base::__head()
   {

      if (get_children_count() <= 0)
      {

         return nullptr;

      }

      return _child_at(0);

   }


   ::data::tree_item_base * tree_item_base::__tail()
   {

      if (get_children_count() <= 0)
      {

         return nullptr;

      }

      return _child_at(get_children_count()-1);

   }


   ::collection::index tree_item_base::_get_index()
   {

      if (m_iIndex >= -1)
      {

         return m_iIndex;

      }

      if (_get_parent() == nullptr)
      {

         m_iIndex = -1;

         return -1;

      }

      return m_iIndex = _get_parent()->_find_child(this);

   }


   tree_item_base * tree_item_base::_get_next_or_parent_next(::collection::index * piLevel)
   {

      if (__next())
      {

         return __next();

      }

      if (!_get_parent())
      {

         return nullptr;

      }

      if (piLevel)
      {

         (*piLevel)--;

      }

      return _get_parent()->_get_next_or_parent_next(piLevel);

   }


   tree_item_base * tree_item_base::_get_child_or_next(::collection::index * piLevel)
   {

      if (__head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return __head();

      }

      return __next();

   }


   tree_item_base * tree_item_base::_get_child_next_or_parent(::collection::index * piLevel)
   {

      if (__head())
      {

         if (piLevel)
         {

            (*piLevel)++;

         }

         return __head();

      }

      return _get_next_or_parent_next(piLevel);

   }


   tree_item_base * tree_item_base::_get_item(enum_tree_navigation enavigation, ::collection::index * pindexLevel)
   {

      switch(enavigation)
      {
      case e_tree_navigation_expanded_forward:

         return _get_child_next_or_parent(pindexLevel);

      case e_tree_navigation_proper_forward:

         return _get_proper_next(pindexLevel);

      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }

   }


   tree_item_base * tree_item_base::_get_item(enum_relative erelative)
   {

      switch(erelative)
      {
      case e_relative_first_child:
      {
         return __head();
      }
      break;
      case e_relative_last_child:
      {
         return __tail();
      }
      case e_relative_parent:
      {
         return _get_parent();
      }
      break;
      case e_relative_first_sibling:
      {
         return _get_parent()->__head();
      }
      break;
      case e_relative_previous_sibling:
      {
         return __previous();
      }
      break;
      case e_relative_next_sibling:
      {
         return __next();
      }
      break;
      case e_relative_last_sibling:
      {
         return _get_parent()->__tail();
      }
      break;
      default:
         // Not Expected
         ASSERT(false);
         return nullptr;
      }
   }



   tree_item_base * tree_item_base::_first_child()
   {

      return __head();

   }


   ::data::item * tree_item_base::_data_item() const
   {

      throw ::interface_only();

      return nullptr;

   }


   string tree_item_base::get_text() const
   {

      if (!_data_item())
      {

         return "";

      }

      return _data_item()->data_item_get_text(_get_tree());

   }


   ::collection::index tree_item_base::get_image() const
   {

      if (!_data_item())
      {

         return -1;

      }

      return _data_item()->data_item_get_image(_get_tree());

   }


   ::image::image_list * tree_item_base::get_image_list() const
   {

      if (!_data_item())
      {

         return nullptr;

      }
         
      return _data_item()->data_item_get_image_list(_get_tree());

   }


   tree_item_base * tree_item_base::_get_proper_item(::collection::index iIndex, ::collection::index * piLevel)
   {

      if (*piLevel)
      {

         *piLevel = 0;

      }

      tree_item_base * pitem = this;

      while(pitem && iIndex >= 0)
      {

         pitem = pitem->_get_item(e_tree_navigation_proper_forward, piLevel);

         iIndex--;

      }

      if (iIndex < 0)
      {

         return pitem;

      }

      return nullptr;

   }


   ::collection::index tree_item_base::_get_proper_item_index(tree_item_base * pitemParam, ::collection::index * piLevel)
   {
      
      int iIndex = 0;

      if (piLevel)
      {

         *piLevel = 0;

      }

      tree_item_base * pitem = this;

      while(pitem)
      {

         pitem = pitem->_get_item(e_tree_navigation_proper_forward, piLevel);

         if (pitem == pitemParam)
         {

            return iIndex;

         }

         iIndex++;

      }

      return -1;

   }

   
   ::collection::count tree_item_base::get_proper_item_count()
   {

      tree_item_base * pitem = this;

      ::collection::index iLevel = 0;

      ::collection::count iCount = -1;

      while(pitem)
      {

         pitem = pitem->_get_item(e_tree_navigation_proper_forward, &iLevel);

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


   bool tree_item_base::is_expanded() const
   {

      return (m_dwState & ::data::e_tree_item_state_expanded) != 0;

   }


   bool tree_item_base::is_expandable() const
   {

      return (m_dwState & ::data::e_tree_item_state_expandable) != 0;

   }


   bool tree_item_base::is_descendant(tree_item_base * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      return pitem->is_ascendant(this);

   }


   bool tree_item_base::is_ascendant(tree_item_base * pitem)
   {

      if (pitem == nullptr)
      {

         return false;

      }

      tree_item_base * pparent = _get_parent();

      if (pparent == nullptr)
      {

         return false;

      }

      while(pparent != nullptr)
      {

         if(pparent == pitem)
            return true;

         pparent = pparent->_get_parent();

      }

      return false;

   }


   void tree_item_base::on_fill_children()
   {

      //if (m_pdataitem)
      //{

      //   m_pdataitem->data_item_on_fill_children(this);

      //}

      //for(auto & p : m_treeitema2)
      //   {

      //      if (p->is_expanded())
      //      {

      //         p->on_fill_children();

      //      }

      //   };

   }


} // namespace data



