#pragma once


namespace sort
{

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortAsc(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list)
   {
      ::raw_array < POSITION > stackLowerBound;
      ::raw_array < POSITION > stackUpperBound;
      POSITION iLowerBound;
      POSITION iUpperBound;
      POSITION iLPos, iUPos, iMPos;

      if(list.get_size() >= 2)
      {
         stackLowerBound.push(list.get_head_position());
         stackUpperBound.push(list.get_tail_position());
         while(true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
            {
               while(true)
               {
                  if(iMPos == iUPos)
                     break;
                  if(list.get_at(iMPos) < list.get_at(iUPos))
                     list.get_previous(iUPos);
                  else
                  {
                     list.__swap(iMPos, iUPos);
                     break;
                  }
               }
               if(iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while(true)
               {
                  if(iMPos == iLPos)
                     break;
                  if(list.get_at(iLPos) < list.get_at(iMPos))
                     list.get_next(iLPos);
                  else
                  {
                     list.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(list.position_index(iLowerBound) < list.position_index(iMPos) - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(list.position_index(iMPos) + 1 < list.position_index(iUpperBound))
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }
   }

   template <class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortDesc(comparable_list < TYPE, ARG_TYPE, ARRAY_TYPE > & list)
   {
      ::raw_array < POSITION > stackLowerBound;
      ::raw_array < POSITION > stackUpperBound;
      POSITION iLowerBound;
      POSITION iUpperBound;
      POSITION iLPos, iUPos, iMPos;

      if(list.get_size() >= 2)
      {
         stackLowerBound.push(list.get_head_position());
         stackUpperBound.push(list.get_tail_position());
         while(true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while(true)
            {
               while(true)
               {
                  if(iMPos == iUPos)
                     break;
                  if(list.get_at(iUPos) < list.get_at(iMPos))
                     list.get_previous(iUPos);
                  else
                  {
                     list.__swap(iMPos, iUPos);
                     break;
                  }
               }
               if(iMPos == iUPos)
                  break;
               iMPos = iUPos;
               while(true)
               {
                  if(iMPos == iLPos)
                     break;
                  if(list.get_at(iMPos) < list.get_at(iLPos))
                     list.get_next(iLPos);
                  else
                  {
                     list.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(list.position_index(iLowerBound) < list.position_index(iMPos) - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(list.position_index(iMPos) + 1 < list.position_index(iUpperBound))
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }
   }

   template < class ARRAY >
   inline bool sort_find(ARRAY & a, typename ARRAY::BASE_ARG_TYPE arg,index & iIndex,index iStart,index iEnd)
   {
      if(a.get_size() == 0)
      {
         return false;
      }
      index iLowerBound = iStart;
      index iMaxBound = iEnd;
      index iUpperBound = iMaxBound;
      memsize iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while(iUpperBound - iLowerBound >= 8)
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
         {
            return true;
         }
         else if(iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if(iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if(iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while(iIndex < a.get_count())
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare < 0)
            iIndex++;
         else
            break;
      }
      if(iIndex >= a.get_count())
         return false;
      while(iIndex >= 0)
      {
         iCompare = CompareElements(a.element_at(iIndex),arg);
         if(iCompare == 0)
            return true;
         else if(iCompare > 0)
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }


} // namespace sort




//#include "collection_sort_array.h"
#include "collection_key_sort_array.h"


//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//void comparable_array<  TYPE,  ARG_TYPE,  ARRAY_TYPE >::quick_sort(bool bAsc)
//{
//   if(bAsc)
//   {
//      sort::QuickSortAsc(*this);
//   }
//   else
//   {
//      sort::QuickSortDesc(*this);
//   }
//}







template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
void comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
quick_sort(bool bAsc)
{
   if(bAsc)
   {
      sort::QuickSortAsc(*this);
   }
   else
   {
      sort::QuickSortDesc(*this);
   }
}

template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
void key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
SetKeyProperty(KEY (TYPE::* lpfnKeyProperty)())
{
   m_lpfnKeyProperty= lpfnKeyProperty;
   sort::QuickSortByKey < KEY, TYPE, ARG_TYPE >(
      m_array,
      m_lpfnKeyProperty);
}


