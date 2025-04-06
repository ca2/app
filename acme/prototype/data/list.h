// From data/tree_item.h by camilo on 2025-03-28 22:24
#pragma once


template < typename LIST_ITEM >
bool list_item_is_before(const LIST_ITEM * pitem1, const LIST_ITEM * pitem2)
{

   if (::is_null(pitem2))
   {

      return false;

   }

   if (pitem1 == pitem2)
   {

      return false;

   }

   while (::is_set(pitem1))
   {

      if (pitem1->m_pnext == pitem2)
      {

         return true;

      }

      pitem1 = pitem1->m_pnext;

   }

   return false;

}


template < typename LIST_ITEM >
const LIST_ITEM * list_item_calculate_head(const LIST_ITEM * pitem)
{

   if (::is_null(pitem))
   {

      return nullptr;

   }

   while (true)
   {

      if (::is_null(pitem->m_pprevious))
      {

         return pitem;

      }

      pitem = pitem->m_pprevious;

   }

}


template < typename LIST_ITEM >
const LIST_ITEM * list_item_calculate_tail(const LIST_ITEM * pitem)
{

   if (::is_null(pitem))
   {

      return nullptr;

   }

   while (true)
   {

      if (::is_null(pitem->m_pnext))
      {

         return pitem;

      }

      pitem = pitem->m_pnext;

   }

}


template < typename LIST_ITEM, typename ARRAY >
void list_set_children(LIST_ITEM * plist, const ARRAY & a)
{

   list_erase_all(plist);

   if (a.is_empty())
   {

      return;

   }

   plist->m_phead = a.first();

   plist->m_ptail = a.last();

   LIST_ITEM * pprevious = nullptr;

   for (auto & p : a)
   {

      if (pprevious)
      {

         pprevious->m_pnext = p;

      }

      p->m_pprevious = pprevious;

      pprevious = p;

   }

   if (pprevious)
   {

      pprevious->m_pnext = nullptr;

   }

}

template < typename LIST_ITEM >
void list_swap(LIST_ITEM * plist, LIST_ITEM * pitemA, LIST_ITEM * pitemB)
{

   auto pitemAPrevious = pitemA->m_pprevious;

   auto pitemANext = pitemA->m_pnext;

   auto pitemBPrevious = pitemB->m_pprevious;

   auto pitemBNext = pitemB->m_pnext;

   if (pitemAPrevious == pitemB)
   {

      if (pitemB->m_pnext != pitemA)
      {

         throw "error";

      }

      pitemANext->m_pprevious = pitemB;

      pitemBPrevious->m_pnext = pitemA;

      pitemA->m_pprevious = pitemB->m_pprevious;

      pitemB->m_pnext = pitemA->m_pnext;

      pitemA->m_pnext = pitemB;

      pitemB->m_pprevious = pitemA;

   }
   else if (pitemANext == pitemB)
   {

      if (pitemB->m_pprevious != pitemA)
      {

         throw "error";

      }

      pitemAPrevious->m_pnext = pitemB;

      pitemBNext->m_pprevious = pitemA;

      pitemA->m_pnext = pitemB->m_pnext;

      pitemB->m_pprevious = pitemA->m_pprevious;

      pitemA->m_pprevious = pitemB;

      pitemB->m_pnext = pitemA;

   }
   else
   {

      pitemA->m_pprevious = pitemBPrevious;

      pitemA->m_pnext = pitemBNext;

      pitemB->m_pprevious = pitemAPrevious;

      pitemB->m_pnext = pitemANext;

      if (::is_set(pitemAPrevious))
      {

         pitemAPrevious->m_pnext = pitemB;

      }

      if (::is_set(pitemANext))
      {

         pitemANext->m_pprevious = pitemB;

      }

      if (::is_set(pitemBPrevious))
      {

         pitemBPrevious->m_pnext = pitemA;

      }

      if (::is_set(pitemBNext))
      {

         pitemBNext->m_pprevious = pitemA;

      }

   }

}



template < typename LIST_ITEM, typename PRED >
void list_sort(LIST_ITEM * pitem, PRED pred)
{

   if (::is_null(pitem->m_phead) || ::is_null(pitem->m_ptail))
   {

      return;

   }

   ::raw_array < LIST_ITEM * > stackLowerBound;
   ::raw_array < LIST_ITEM * > stackUpperBound;

   LIST_ITEM * iLowerBound;
   LIST_ITEM * iUpperBound;
   LIST_ITEM * iLPos, * iUPos, * iMPos;

   stackLowerBound.push(pitem->m_phead);
   stackUpperBound.push(pitem->m_ptail);
   while (true)
   {
      iLowerBound = stackLowerBound.pop();
      iUpperBound = stackUpperBound.pop();
      iLPos = iLowerBound;
      iUPos = iUpperBound;
      auto p1 = iLPos;
      auto p2 = iUPos;
      iMPos = p1;
      while (p1 != p2)
      {
         p2 = p2->m_pprevious;
         if (p1 == p2)
         {
            iMPos = p1;
            break;
         }
         p1 = p1->m_pnext;
         if (p1 == p2)
         {
            iMPos = p1;
            break;
         }
      }
      while (true)
      {
         while (true)
         {
            if (iMPos == iUPos)
               break;
            if (pred(iMPos, iUPos))
            {
               iUPos = iUPos->m_pprevious;
            }
            else
            {
               list_swap(pitem, iMPos, iUPos);
               break;
            }
         }
         if (iMPos == iUPos)
            break;
         iMPos = iUPos;
         while (true)
         {
            if (iMPos == iLPos)
               break;
            if (pred(iLPos, iMPos))
            {
               iLPos = iLPos->m_pnext;
            }
            else
            {
               list_swap(pitem, iLPos, iMPos);
               break;
            }
         }
         if (iMPos == iLPos)
            break;
         iMPos = iLPos;
      }
      if (list_item_is_before(iLowerBound, (const LIST_ITEM *)iMPos->m_pprevious))
      {
         stackLowerBound.push(iLowerBound);
         stackUpperBound.push(iMPos->m_pprevious);
      }
      if (list_item_is_before((const LIST_ITEM *)iMPos->m_pnext, iUpperBound))
      {
         stackLowerBound.push(iMPos->m_pnext);
         stackUpperBound.push(iUpperBound);
      }
      if (stackLowerBound.get_size() == 0)
         break;
   }
   pitem->m_phead = list_item_calculate_head((const LIST_ITEM *)pitem->m_phead);
   pitem->m_ptail = list_item_calculate_tail((const LIST_ITEM *)pitem->m_ptail);
}


