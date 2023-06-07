#pragma once


template < typename CONTAINER, typename LIST_ITEM >
void list_predicateicate_add(CONTAINER& a, LIST_ITEM&& pitem)
{

   list_predicate(pitem, [&a](auto& p) { a.add(p); });

}


template < typename LIST_ITEM >
::count list_erase_all(LIST_ITEM&& pitem)
{

   ::count c = 0;

   auto pprevious = pitem->m_phead;

   if (pprevious)
   {

      for (auto p = pprevious->m_pnext; ::is_set(p); p = p->m_pnext, c++)
      {

         pprevious->m_pnext = nullptr;

         p->m_pprevious = nullptr;

      }

   }

   pitem->m_phead = nullptr;

   pitem->m_ptail = nullptr;

   return c;

}


template < typename LIST_ITEM >
::count list_count(LIST_ITEM&& pitem)
{

   ::count c = 0;

   for (auto p = pitem->m_phead; ::is_set(p); p = p->m_pnext, c++);

   return c;

}


template < typename LIST_ITEM, typename PRED >
LIST_ITEM list_predicateicate_find(LIST_ITEM&& plist, PRED pred)
{

   for (auto p = plist->m_phead; ::is_set(p); p = p->m_pnext)
   {

      if (pred(p))
      {

         return p;

      }

   }

   return nullptr;

}


template < typename LIST_ITEM, typename LIST_ITEM2 >
bool list_contains_item(LIST_ITEM && pitem, LIST_ITEM2 && pitemItem)
{

   for (auto p = pitem->m_phead; ::is_set(p); p = p->m_pnext)
   {

      if (p == pitemItem)
      {

         return true;

      }

   }

   return false;

}


template < typename LIST_ITEM, typename LIST_ITEM2 >
::index list_item_index(LIST_ITEM&& pitem, LIST_ITEM2&& pitemItem)
{

   ::index i = 0;

   for (auto p = pitem->m_phead; ::is_set(p); p = p->m_pnext, i++)
   {

      if (p == pitemItem)
      {

         return i;

      }

   }

   return -1;

}


//template < typename LIST_ITEM, typename LIST_ITEM2 >
//bool list_contains(LIST_ITEM&& pitem, LIST_ITEM2&& pitemItem)
//{
//
//   auto pFind = list_find_first(pitem, pitemItem);
//
//   return ::is_set(pFind);
//
//}


template < typename LIST_ITEM, typename LIST_ITEM2, typename LIST_ITEM3 >
void list_insert_before(LIST_ITEM&& plist, LIST_ITEM2&& pitem, LIST_ITEM3&& pitemBefore)
{

   if (plist->m_phead == pitem)
   {

      pitem->m_phead = pitemBefore;

   }

   pitemBefore->m_pprevious = pitem->m_pprevious;

   pitem->m_pprevious = pitemBefore;

   pitemBefore->m_pnext = pitem;

}


template < typename LIST_ITEM, typename LIST_ITEM2, typename LIST_ITEM3 >
void list_insert_after(LIST_ITEM&& plist, LIST_ITEM2&& pitem, LIST_ITEM3&& pitemAfter)
{

   if (plist->m_ptail == pitem)
   {

      pitem->m_ptail = pitemAfter;

   }

   pitemAfter->m_pnext = pitem->m_pnext;

   pitem->m_pnext = pitemAfter;

   pitemAfter->m_pprevious = pitem;

}


template < typename LIST_ITEM, typename LIST_ITEM2, typename LIST_ITEM3 >
void list_replace_item(LIST_ITEM&& plist, LIST_ITEM2&& pitem, LIST_ITEM3&& pitemNew)
{

   if (plist->m_phead == pitem)
   {

      pitem->m_phead = pitemNew;

   }

   if (plist->m_ptail == pitem)
   {

      pitem->m_ptail = pitemNew;

   }

   pitemNew->m_pprevious = pitem->m_pprevious;

   pitemNew->m_pnext = pitem->m_pnext;

   pitem->m_pprevious = nullptr;

   pitem->m_pnext = nullptr;

   if (pitemNew->m_pnext)
   {

      pitemNew->m_pnext->m_pprevious = pitemNew;

   }

   if (pitemNew->m_pprevious)
   {

      pitemNew->m_pprevious->m_pnext = pitemNew;

   }

}





template < typename LIST_ITEM, typename LIST_ITEM2 >
void list_add(LIST_ITEM&& plist, LIST_ITEM2&& pitemAdd)
{

   if (plist->m_ptail)
   {

      plist->m_ptail->m_pnext = pitemAdd;

   }

   pitemAdd->m_pnext = nullptr;

   pitemAdd->m_pprevious = plist->m_ptail;

   plist->m_ptail = pitemAdd;

   if (!plist->m_phead)
   {

      plist->m_phead = plist->m_ptail;

   }

}


template < typename LIST_ITEM, typename LIST_ITEM2 >
void list_add_head(LIST_ITEM&& plist, LIST_ITEM2&& pitemAdd)
{

   if (plist->m_phead)
   {

      plist->m_phead->m_pprevious = pitemAdd;

   }

   pitemAdd->m_pprevious = nullptr;

   pitemAdd->m_pnext = plist->m_phead;

   plist->m_phead = pitemAdd;

   if (!plist->m_ptail)
   {

      plist->m_ptail = plist->m_phead;

   }

}


template < typename LIST_ITEM, typename LIST_ITEM2 >
void list_erase(LIST_ITEM&& pitem, LIST_ITEM2&& pitemRemove)
{

   if (pitem->m_phead == pitemRemove)
   {

      pitem->m_phead = pitemRemove->m_pnext;

   }

   if (pitem->m_ptail == pitemRemove)
   {

      pitem->m_ptail = pitemRemove->m_pprevious;

   }

   if (pitemRemove->m_pnext)
   {

      pitemRemove->m_pnext->m_pprevious = pitemRemove->m_pprevious;

   }

   if (pitemRemove->m_pprevious)
   {

      pitemRemove->m_pprevious->m_pnext = pitemRemove->m_pnext;

   }

}



template < typename LIST_ITEM, typename PRED  >
void list_predicate(LIST_ITEM* pitem, PRED pred)
{

   for (auto p = pitem->m_phead; ::is_set(p); p = p->m_pnext)
   {

      pred(p);

   }

}

template < typename LIST_ITEM, typename PRED  >
void list_predicateicate_with_index(LIST_ITEM* pitem, PRED pred)
{

   ::index i = 0;

   for (auto p = pitem->m_phead; ::is_set(p); p = p->m_pnext, i++)
   {

      pred(p, i);

   }


}


template < typename TREE_ITEM, typename PRED >
void tree_sort(TREE_ITEM* pitem, PRED pred)
{

   list_sort(pitem);

   list_predicate(pitem, [pred](auto p) {tree_sort(p, pred); });

}



