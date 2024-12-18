#pragma once


#include "numeric_array.h"
#include "acme/prototype/comparison/less.h"


namespace sort
{


   template<typename A, typename B>
   constexpr bool sort(A & a, B & b)
   {

      if (b < a)
      {

         swap(a, b);

         return true;

      }

      return false;

   }

   template<class TYPE>
   static iptr NumericCompare(const TYPE * pointA, const TYPE * pointB);

   //    static iptr DWordCompare(const iptr dwA, const iptr dwB);

   //   static void BubbleSort(LPINT pInt, iptr int_size);


   //   static void quick_sort(
      //    array<unsigned int, unsigned int> & a,
      //  iptr (*fCompare)(const iptr, const iptr),
      //void (*__swap)(void * pVoidSwapArg, iptr iA, iptr iB),

      //void * pVoidSwapArg);


   template<class A>
   static iptr CompareTkPosition(const A a1, const A a2);

   template<class TYPE>
   iptr NumericCompare(const TYPE * p1, const TYPE * p2)
   {
      if (*p1 > *p2)
         return 1;
      else if (*p1 < *p2)
         return -1;
      else
         return 0;
   }


   template<class A>
   static iptr CompareTkPosition(const A a1, const A a2)
   {
      if (a1.m_tkPosition > a2.m_tkPosition)
         return 1;
      else if (a1.m_tkPosition > a2.m_tkPosition)
         return -1;
      else
         return 0;
   }

   //   template <class TYPE, class ARG_TYPE>
   //   void SwapArray(
   //      array<TYPE, ARG_TYPE> & a,
   //      iptr   iA,
   //      iptr iB)
   //   {
   //      TYPE t;
   //      t = a.get_at(iA);
   //      a.set_at(iA, a.get_at(iB));
   //      a.set_at(iB, t);
   //   };
      /*template <class TYPE, class ARG_TYPE>
      void quick_sort(
      array<TYPE, ARG_TYPE> & array,
      ::std::strong_ordering (* fCompare)(const TYPE *, const TYPE *),
      void (* fSwap)(TYPE *, TYPE *));*/

      /*template <class TYPE, class ARG_TYPE>
      void __swap(
      CarrayInterface<TYPE, ARG_TYPE> * parray,
      iptr   iA,
      iptr iB)
      {
      TYPE t;
      t = parray->element_at(iA);
      parray->set_at(iA, parray->element_at(iB));
      parray->set_at(iB, t);
      };*/


   template<class TYPE>
   iptr CompareAscending(
      TYPE * pA,
      TYPE * pB)
   {
      return *pA - *pB;
   };

   template<class TYPE, class ARG_TYPE, class FIRST>
   void quick_sort(array<TYPE, ARG_TYPE> & a)
   {
      TYPE t;
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;
      //   unsigned int t;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (FIRST::Compare(&a.element_at(iMPos), &a.element_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     t = a.element_at(iMPos);
                     a.element_at(iMPos) = a.element_at(iUPos);
                     a.element_at(iUPos) = t;
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
                  if (FIRST::Compare(&a.element_at(iLPos), &a.element_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     t = a.element_at(iMPos);
                     a.element_at(iMPos) = a.element_at(iLPos);
                     a.element_at(iLPos) = t;
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }

   };


   template<class TYPE, class ARG_TYPE, typename SWAP>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      SWAP __swap)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (a.get_at(iMPos) <= a.get_at(iUPos))
                     iUPos--;
                  else
                  {
                     a.__swap(iMPos, iUPos);
                     __swap(iUPos, iMPos);
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
                  if (a.get_at(iLPos) <= a.get_at(iMPos))
                     iLPos++;
                  else
                  {
                     a.__swap(iMPos, iLPos);
                     __swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }

   }


   template<class TYPE, class ARG_TYPE>
   void quick_sort(
      array<TYPE, ARG_TYPE> & a,
      ::std::strong_ordering fCompare(const ARG_TYPE, const ARG_TYPE),
      void __swap(void * pVoidSwapArg, iptr iA, iptr iB),

      void * pVoidSwapArg)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (fCompare(a.get_at(iMPos), a.get_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     a.__swap(iMPos, iUPos);
                     __swap(pVoidSwapArg, iUPos, iMPos);

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
                  if (fCompare(a.get_at(iLPos), a.get_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     a.__swap(iMPos, iLPos);
                     __swap(pVoidSwapArg, iLPos, iMPos);

                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }

   }


   template<class iterator, class COMPARE = ::comparison::less<typename iterator::BASE_TYPE, typename iterator::BASE_ARG_TYPE> >
   void quick_sort(const iterator & a, const iterator & b);





   //template <class TYPE, class ARG_TYPE>
   //void quick_sort(
   //   array<TYPE, ARG_TYPE> & a,
   //   int (* fCompare)(const ARG_TYPE, const ARG_TYPE))
   //{
   //   index_array stackLowerBound;
   //   index_array stackUpperBound;
   //   iptr iLowerBound;
   //   iptr iUpperBound;
   //   iptr iLPos, iUPos, iMPos;
   //   TYPE t;

   //   if(a.get_size() >= 2)
   //   {
   //      stackLowerBound.push(0);
   //      stackUpperBound.push(a.get_size() - 1);
   //      while(true)
   //      {
   //         iLowerBound = stackLowerBound.pop();
   //         iUpperBound = stackUpperBound.pop();
   //         iLPos = iLowerBound;
   //         iMPos = iLowerBound;
   //         iUPos = iUpperBound;
   //         while(true)
   //         {
   //            while(true)
   //            {
   //               if(iMPos == iUPos)
   //                  break;
   //               if(fCompare(a.element_at(iMPos), a.element_at(iUPos)) <= 0)
   //                  iUPos--;
   //               else
   //               {
   //                  //    t = a.get_at(iMPos);
   //                  //  a.set_at(iMPos, a.get_at(iUPos));
   //                  //a.set_at(iUPos, t);
   //                  a.__swap(iMPos, iUPos);
   //                  break;
   //               }
   //            }
   //            if(iMPos == iUPos)
   //               break;
   //            iMPos = iUPos;
   //            while(true)
   //            {
   //               if(iMPos == iLPos)
   //                  break;
   //               if(fCompare(a.element_at(iLPos), a.element_at(iMPos)) <= 0)
   //                  iLPos++;
   //               else
   //               {
   //                  //                        t = a.get_at(iMPos);
   //                  //                      a.set_at(iMPos, a.get_at(iLPos));
   //                  //                    a.set_at(iLPos, t);
   //                  a.__swap(iLPos, iMPos);
   //                  break;
   //               }
   //            }
   //            if(iMPos == iLPos)
   //               break;
   //            iMPos = iLPos;
   //         }
   //         if(iLowerBound < iMPos - 1)
   //         {
   //            stackLowerBound.push(iLowerBound);
   //            stackUpperBound.push(iMPos - 1);
   //         }
   //         if(iMPos + 1 < iUpperBound)
   //         {
   //            stackLowerBound.push(iMPos + 1);
   //            stackUpperBound.push(iUpperBound);
   //         }
   //         if(stackLowerBound.get_size() == 0)
   //            break;
   //      }
   //   }
   //}

   template<typename PRED_LE, typename ARRAY>
   void predicate_array_quick_sort(ARRAY & a, PRED_LE predicate_le)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (predicate_le(a.element_at(iMPos), a.element_at(iUPos)))
                     iUPos--;
                  else
                  {
                     //    t = a.get_at(iMPos);
                     //  a.set_at(iMPos, a.get_at(iUPos));
                     //a.set_at(iUPos, t);
                     a.__swap(iMPos, iUPos);
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
                  if (predicate_le(a.element_at(iLPos), a.element_at(iMPos)))
                     iLPos++;
                  else
                  {
                     //                        t = a.get_at(iMPos);
                     //                      a.set_at(iMPos, a.get_at(iLPos));
                     //                    a.set_at(iLPos, t);
                     a.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }

            if (stackLowerBound.get_size() == 0)
               break;

         }

      }

   }


   template<class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortAsc(comparable_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (a.element_at(iMPos) <= a.element_at(iUPos))
                     iUPos--;
                  else
                  {
                     a.__swap(iMPos, iUPos);
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
                  if (a.element_at(iLPos) <= a.element_at(iMPos))
                     iLPos++;
                  else
                  {
                     a.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }
   }

   template<class TYPE, class ARG_TYPE, class ARRAY_TYPE>
   void QuickSortDesc(comparable_array<TYPE, ARG_TYPE, ARRAY_TYPE> & a)
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_upper_bound());
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if (a.element_at(iUPos) <= a.element_at(iMPos))
                     iUPos--;
                  else
                  {
                     a.__swap(iMPos, iUPos);
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
                  if (a.element_at(iMPos) <= a.element_at(iLPos))
                     iLPos++;
                  else
                  {
                     a.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }
   }


   template<primitive_range RANGE>
   void QuickSortAsc(RANGE & range)
   {

      if (range.size() < 2)
      {

         return;

      }

      ::array < typename RANGE::iterator > stackLowerBound;
      ::array < typename RANGE::iterator > stackUpperBound;
      typename RANGE::iterator iLowerBound;
      typename RANGE::iterator iUpperBound;
      typename RANGE::iterator iLPos, iUPos, iMPos;

      stackLowerBound.push(range.begin());
      stackUpperBound.push(range.back());
      while (true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while (true)
         {
            while (true)
            {
               if (iMPos == iUPos)
                  break;
               if (*iMPos <= *iUPos)
                  iUPos--;
               else
               {
                  ::swap(*iMPos, *iUPos);
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
               if (*iLPos <= *iMPos)
                  iLPos++;
               else
               {
                  ::swap(*iLPos, *iMPos);
                  break;
               }
            }
            if (iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if (iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if (iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if (stackLowerBound.get_size() == 0)
            break;
      }

   }


   template<primitive_range RANGE>
   void QuickSortDesc(RANGE & range)
   {

      if (range.size() < 2)
      {

         return;

      }

      ::array < typename RANGE::iterator > stackLowerBound;
      ::array < typename RANGE::iterator > stackUpperBound;
      typename RANGE::iterator iLowerBound;
      typename RANGE::iterator iUpperBound;
      typename RANGE::iterator iLPos, iUPos, iMPos;

      stackLowerBound.push(range.begin());
      stackUpperBound.push(range.end());
      while (true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while (true)
         {
            while (true)
            {
               if (iMPos == iUPos)
                  break;
               if (*iUPos <= *iMPos)
                  iUPos--;
               else
               {
                  ::swap(*iMPos, *iUPos);
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
               if (*iMPos <= *iLPos)
                  iLPos++;
               else
               {
                  ::swap(*iLPos, *iMPos);
                  break;
               }
            }
            if (iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
         if (iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if (iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if (stackLowerBound.get_size() == 0)
            break;
      }

   }


   template<class KEY, class TYPE, class ARG_TYPE>
   void QuickSortByKey(
      array<TYPE, ARG_TYPE> & a,
      KEY(TYPE:: * fKey)())
   {
      index_array stackLowerBound;
      index_array stackUpperBound;
      iptr iLowerBound;
      iptr iUpperBound;
      iptr iLPos, iUPos, iMPos;
      TYPE t;

      if (a.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(a.get_size() - 1);
         while (true)
         {
            iLowerBound = stackLowerBound.pop();
            iUpperBound = stackUpperBound.pop();
            iLPos = iLowerBound;
            iMPos = iLowerBound;
            iUPos = iUpperBound;
            while (true)
            {
               while (true)
               {
                  if (iMPos == iUPos)
                     break;
                  if ((a.element_at(iMPos).*fKey)() < (a.element_at(iUPos).*fKey)())
                     iUPos--;
                  else
                  {
                     //    t = a.get_at(iMPos);
                     //  a.set_at(iMPos, a.get_at(iUPos));
                     //a.set_at(iUPos, t);
                     a.__swap(iMPos, iUPos);
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
                  if ((a.element_at(iLPos).*fKey)() < (a.element_at(iMPos).*fKey)())
                     iLPos++;
                  else
                  {
                     //                        t = a.get_at(iMPos);
                     //                      a.set_at(iMPos, a.get_at(iLPos));
                     //                    a.set_at(iLPos, t);
                     a.__swap(iLPos, iMPos);
                     break;
                  }
               }
               if (iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if (iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if (iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if (stackLowerBound.get_size() == 0)
               break;
         }
      }
   }

   template<class ARG_TYPE>
   inline iptr SortCompare(ARG_TYPE t1, ARG_TYPE t2)
   {
      return t1 - t2;
   }


   template<class TYPE, class ARG_TYPE>
   bool SortFind(array<TYPE, ARG_TYPE> & a, ARG_TYPE t, iptr & iIndex, iptr iStart, iptr iEnd)
   {
      if (a.get_size() == 0)
      {
         return false;
      }
      iptr iLowerBound = iStart;
      iptr iMaxBound = iEnd;
      iptr iUpperBound = iMaxBound;
      iptr iCompare;

      while (true)
      {
         iIndex = (iUpperBound + iLowerBound) / 2;
         iCompare = SortCompare((ARG_TYPE)a.element_at(iIndex), (ARG_TYPE)t);
         if (iCompare == 0)
         {
            return true;
         }
         else if (iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if (iUpperBound < 0)
               break;
         }
         else
         {
            iLowerBound = iIndex + 1;
            if (iLowerBound > iMaxBound)
            {
               iIndex = iLowerBound;
               break;
            }
         }
         if (iUpperBound < iLowerBound)
            break;

      }
      return false;

   }

   template<class TYPE, class ARG_TYPE>
   bool SortFind(array<TYPE, ARG_TYPE> & a, ARG_TYPE t, iptr & iIndex)
   {
      return SortFind(a, t, iIndex, 0, a.get_size() - 1);
   }

   template<class TYPE, class ARG_TYPE>
   void BubbleSortByLPGetSize(array<TYPE, ARG_TYPE> & a, bool bAsc = true);

   //template<class TYPE, class ARG_TYPE>
   //void BubbleSortByGetSize(array<TYPE, ARG_TYPE> & a, bool bAsc = true);

   template<typename TYPE>
   void BubbleSortByPtrAtGetSize(
      pointer_array<TYPE> & a,
      bool bAsc = true);

   template<class TYPE, class ARG_TYPE = const TYPE &, class DEFCONSTRUCTOR>
   void quick_sort(
      array<TYPE, ARG_TYPE, DEFCONSTRUCTOR> & a,
      ::std::strong_ordering(*pfnCompare)(ARG_TYPE, ARG_TYPE));


   template<class TYPE, class ARG_TYPE>
   void BubbleSortByLPGetSize(
      array<TYPE, ARG_TYPE> & a,
      bool bAsc)
   {
      TYPE * t;
      if (bAsc)
      {
         for (iptr i = 0; i < a.get_size(); i++)
            for (iptr j = i + 1; j < a.get_size(); j++)
            {
               if (a.element_at(i)->get_size() > a.element_at(j)->get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }
      else
      {
         for (iptr i = 0; i < a.get_size(); i++)
            for (iptr j = i + 1; j < a.get_size(); j++)
            {
               if (a.element_at(i)->get_size() < a.element_at(j)->get_size())
               {
                  t = a.element_at(i);
                  set_at(i, a.element_at(j));
                  set_at(j, t);
               }

            }
      }

      return;
   }


   template<primitive_array ARRAY>
   void BubbleSortByGetSize(ARRAY & a, bool bAsc)
   {

      if (bAsc)
      {

         for (iptr i = 0; i < a.get_size(); i++)
         {

            for (iptr j = i + 1; j < a.get_size(); j++)
            {

               if (a[i].get_size() > a[j].get_size())
               {

                  a.__swap(i, j);

               }

            }

         }

      }
      else
      {

         for (iptr i = 0; i < a.get_size(); i++)
         {

            for (iptr j = i + 1; j < a.get_size(); j++)
            {

               if (a[i].get_size() < a[j].get_size())
               {

                  a.__swap(i, j);

               }

            }

         }

      }

   }

   //template<class ARRAY>
   //void BubbleSortByGetSize(
   //   ARRAY & a,
   //   bool bAsc)
   //{
   //   typename ARRAY::BASE_TYPE t;
   //   if (bAsc)
   //   {
   //      for (iptr i = 0; i < a.get_size(); i++)
   //         for (iptr j = i + 1; j < a.get_size(); j++)
   //         {
   //            if (a.element_at(i).get_size() > a.element_at(j).get_size())
   //            {
   //               a.__swap(i, j);
   //            }
   //         }
   //   }
   //   else
   //   {
   //      for (iptr i = 0; i < a.get_size(); i++)
   //         for (iptr j = i + 1; j < a.get_size(); j++)
   //         {
   //            if (a.element_at(i).get_size() < a.element_at(j).get_size())
   //            {
   //               a.__swap(i, j);
   //            }

   //         }
   //   }

   //   return;
   //}


   template<typename TYPE>
   void BubbleSortByPtrAtGetSize(
      pointer_array<TYPE> & a,
      bool bAsc)
   {
      TYPE t;
      if (bAsc)
      {
         for (iptr i = 0; i < a.get_size(); i++)
            for (iptr j = i + 1; j < a.get_size(); j++)
            {
               if (a.element_at(i)->get_size() > a.element_at(j)->get_size())
               {
                  a.__swap(i, j);
               }
            }
      }
      else
      {
         for (iptr i = 0; i < a.get_size(); i++)
            for (iptr j = i + 1; j < a.get_size(); j++)
            {
               if (a.element_at(i)->get_size() < a.element_at(j)->get_size())
               {
                  a.__swap(i, j);
               }

            }
      }

      return;
   }



   namespace array
   {

      template < typename ARRAY_TYPE >
      void quick_sort(
      ARRAY_TYPE & a,
      ::std::strong_ordering(*pfnCompare)(typename ARRAY_TYPE::BASE_ARG_TYPE, typename ARRAY_TYPE::BASE_ARG_TYPE))
      {

         index_array stackLowerBound;

         index_array stackUpperBound;

         iptr iLowerBound;

         iptr iUpperBound;

         iptr iLPos, iUPos, iMPos;

         if (a.get_size() >= 2)
         {

            stackLowerBound.push(0);

            stackUpperBound.push(a.get_upper_bound());

            while (true)
            {

               iLowerBound = stackLowerBound.pop();

               iUpperBound = stackUpperBound.pop();

               iLPos = iLowerBound;

               iMPos = iLowerBound;

               iUPos = iUpperBound;

               while (true)
               {

                  while (true)
                  {

                     if (iMPos == iUPos)
                     {

                        break;

                     }

                     if (pfnCompare((typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iMPos), (typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iUPos)) <= 0)
                     {

                        iUPos--;

                     }
                     else
                     {

                        a.__swap(iMPos, iUPos);

                        break;

                     }

                  }

                  if (iMPos == iUPos)
                  {

                     break;

                  }

                  iMPos = iUPos;

                  while (true)
                  {

                     if (iMPos == iLPos)
                     {

                        break;

                     }

                     if (pfnCompare((typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iLPos), (typename ARRAY_TYPE::BASE_ARG_TYPE)a.element_at(iMPos)) <= 0)
                     {

                        iLPos++;

                     }
                     else
                     {

                        a.__swap(iLPos, iMPos);

                        break;

                     }

                  }

                  if (iMPos == iLPos)
                  {

                     break;

                  }

                  iMPos = iLPos;

               }

               if (iLowerBound < iMPos - 1)
               {

                  stackLowerBound.push(iLowerBound);

                  stackUpperBound.push(iMPos - 1);

               }

               if (iMPos + 1 < iUpperBound)
               {

                  stackLowerBound.push(iMPos + 1);

                  stackUpperBound.push(iUpperBound);

               }

               if (stackLowerBound.get_size() == 0)
               {

                  break;

               }

            }

         }

      }


      template < typename ARRAY_TYPE >
      void quick_sort(ARRAY_TYPE & a, less_predicate_base < typename ARRAY_TYPE::BASE_ARG_TYPE > * pless, index_array & ia)
      {

         if (ia.get_size() != a.get_size())
         {

            throw_exception(error_bad_argument);

         }

         index_array stackLowerBound;

         index_array stackUpperBound;

         iptr iLowerBound;

         iptr iUpperBound;

         iptr iLPos, iUPos, iMPos;

         if (a.get_size() >= 2)
         {

            stackLowerBound.push(0);

            stackUpperBound.push(a.get_upper_bound());

            while (true)
            {

               iLowerBound = stackLowerBound.pop();

               iUpperBound = stackUpperBound.pop();

               iLPos = iLowerBound;

               iMPos = iLowerBound;

               iUPos = iUpperBound;

               while (true)
               {

                  while (true)
                  {

                     if (iMPos == iUPos)
                     {

                        break;

                     }

                     if (pless->less(a.element_at(ia[iMPos]), a.element_at(ia[iUPos])) <= 0)
                     {

                        iUPos--;

                     }
                     else
                     {

                        ia.__swap(iMPos, iUPos);

                        break;

                     }

                  }

                  if (iMPos == iUPos)
                  {

                     break;

                  }

                  iMPos = iUPos;

                  while (true)
                  {

                     if (iMPos == iLPos)
                     {

                        break;

                     }

                     if (pless->less(a.element_at(ia[iLPos]), a.element_at(ia[iMPos])) <= 0)
                     {

                        iLPos++;

                     }
                     else
                     {

                        ia.__swap(iLPos, iMPos);

                        break;

                     }

                  }

                  if (iMPos == iLPos)
                  {

                     break;

                  }

                  iMPos = iLPos;

               }

               if (iLowerBound < iMPos - 1)
               {

                  stackLowerBound.push(iLowerBound);

                  stackUpperBound.push(iMPos - 1);

               }

               if (iMPos + 1 < iUpperBound)
               {

                  stackLowerBound.push(iMPos + 1);

                  stackUpperBound.push(iUpperBound);

               }

               if (stackLowerBound.is_empty())
               {

                  break;

               }

            }

         }

      }



   } // namespace array



   // Sort "array" according to "fCompare" function
   // of "pCompare" interface




   template < typename LIST, typename PRED>
   void predicate_quick_sort_list(LIST & list, PRED pred)
   {

      if (list.get_size() < 2)
      {

         return;

      }

      typedef typename LIST::node node;

      ::raw_array < node * > stackLowerBound;

      ::raw_array < node * > stackUpperBound;

      node * iLowerBound;

      node * iUpperBound;
      node * iLPos, * iUPos, * iMPos;

      stackLowerBound.push(list.m_phead);
      stackUpperBound.push(list.m_ptail);
      while (true)
      {
         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();
         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;
         while (true)
         {
            while (true)
            {
               if (iMPos == iUPos)
                  goto break_mid_loop;
               if (pred(iUPos->m_value, iMPos->m_value))
               {
                  list.__swap(iMPos, iUPos);
                  break;
               }
               iUPos = iUPos->m_pprevious;
            }
            iMPos = iUPos;
            while (true)
            {
               if (iMPos == iLPos)
                  goto break_mid_loop;
               if (pred(iMPos->m_value, iLPos->m_value))
               {
                  list.__swap(iLPos, iMPos);
                  break;
               }
               iLPos = iLPos->m_pnext;
            }
            iMPos = iLPos;
         }
      break_mid_loop:
         if (iLowerBound != iMPos->m_pprevious)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos->m_pprevious);
         }
         if (iMPos->m_pnext != iUpperBound)
         {
            stackLowerBound.push(iMPos->m_pnext);
            stackUpperBound.push(iUpperBound);
         }
         if (stackLowerBound.get_size() == 0)
            break;
      }

   }


   template < typename LIST, typename PRED >
   void predicate_quick_sort_list_descending(LIST & list, PRED pred)
   {

      predicate_quick_sort_list(list, [&](auto & a, auto & b) { return pred(b, a); });

   }


   template < typename LIST >
   void quick_sort_list(LIST & list, bool bAscendent = true)
   {

      if (bAscendent)
      {

         predicate_quick_sort_list(list, [](auto & a, auto & b) { return a < b; });

      }
      else
      {

         predicate_quick_sort_list(list, [](auto & a, auto & b) { return b < a; });

      }

   }


   template < class ARRAY >
   inline bool sort_find(ARRAY & a, typename ARRAY::BASE_ARG_TYPE arg, iptr & iIndex, iptr iStart, iptr iEnd)
   {
      if (a.get_size() == 0)
      {
         return false;
      }
      iptr iLowerBound = iStart;
      iptr iMaxBound = iEnd;
      iptr iUpperBound = iMaxBound;
      memsize iCompare;
      // do binary search
      iIndex = (iUpperBound + iLowerBound) / 2;
      while (iUpperBound - iLowerBound >= 8)
      {
         iCompare = CompareElements(a.element_at(iIndex), arg);
         if (iCompare == 0)
         {
            return true;
         }
         else if (iCompare > 0)
         {
            iUpperBound = iIndex - 1;
            if (iUpperBound < 0)
            {
               iIndex = 0;
               break;
            }
         }
         else
         {
            iLowerBound = iIndex + 1;
            if (iLowerBound > iMaxBound)
            {
               iIndex = iMaxBound + 1;
               break;
            }
         }
         iIndex = (iUpperBound + iLowerBound) / 2;
      }
      // do sequential search
      while (iIndex < a.get_count())
      {
         iCompare = CompareElements(a.element_at(iIndex), arg);
         if (iCompare == 0)
            return true;
         else if (iCompare < 0)
            iIndex++;
         else
            break;
      }
      if (iIndex >= a.get_count())
         return false;
      while (iIndex >= 0)
      {
         iCompare = CompareElements(a.element_at(iIndex), arg);
         if (iCompare == 0)
            return true;
         else if (iCompare > 0)
            iIndex--;
         else
            break;
      }
      iIndex++;
      return false;

   }

   template < class ARRAY >
   void quick_sort(ARRAY & a, bool bAsc)
   {
      if (bAsc)
      {
         sort::QuickSortAsc(a);
      }
      else
      {
         sort::QuickSortDesc(a);
      }
   }


   template < typename ITERATOR>
   void quick_sort_iter(ITERATOR first, ITERATOR last)
   {

      //auto & iterable = first.iterable();

      //ASSERT(&iterable == &last.iterable());

      //if (&iterable != &last.iterable())
      //{

      //   return;

      //}

      if (last - first < 2)
      {

         return;

      }

      ::array < ITERATOR > stackLowerBound;
      ::array < ITERATOR > stackUpperBound;
      ITERATOR iLowerBound;
      ITERATOR iUpperBound;
      ITERATOR iLPos, iUPos, iMPos;

      stackLowerBound.push(first);
      stackUpperBound.push(last);

      while (true)
      {

         iLowerBound = stackLowerBound.pop();
         iUpperBound = stackUpperBound.pop();

         iLPos = iLowerBound;
         iMPos = iLowerBound;
         iUPos = iUpperBound;

         while (true)
         {
            while (true)
            {
               if (iMPos == iUPos)
                  goto break_mid_loop;
               __sort(*iMPos, *iUPos);
               iUPos--;

            }
            if (iMPos == iUPos)
               break;
            iMPos = iUPos;
            while (true)
            {
               if (iMPos == iLPos)
                  goto break_mid_loop;
               __sort(*iLPos, *iMPos);
               iLPos++;
            }
            if (iMPos == iLPos)
               break;
            iMPos = iLPos;
         }
      break_mid_loop:
         if (iLowerBound < iMPos - 1)
         {
            stackLowerBound.push(iLowerBound);
            stackUpperBound.push(iMPos - 1);
         }
         if (iMPos + 1 < iUpperBound)
         {
            stackLowerBound.push(iMPos + 1);
            stackUpperBound.push(iUpperBound);
         }
         if (stackLowerBound.get_size() == 0)
            break;
      }

   }


   //https://stackoverflow.com/questions/32937902/sorting-iptr-of-array-using-merge-sort

   template < typename ARRAY, typename PRED >
   void predicate_index_merge(ARRAY & a, PRED leq, index_array & temp, index_array & perm, int lo, int mid, int hi)
   {

      int i = lo, j = mid + 1;

      for (int k = lo; k <= hi; k++)
      {

         temp[k] = perm[k];

      }

      for (int k = lo; k <= hi; k++)
      {

         if (i > mid)
         {

            perm[k] = temp[j++];

         }
         else if (j > hi)
         {

            perm[k] = temp[i++];

         }
         else if (leq(a[temp[i]], a[temp[j]]))
         {

            perm[k] = temp[i++];

         }
         else
         {

            perm[k] = temp[j++];

         }

      }

   }

   template < typename ARRAY, typename PRED >
   void predicate_index_merge_sort(ARRAY & a, PRED leq, index_array & temp, index_array & perm, int lo, int hi)
   {

      if (hi <= lo)
         return;

      int mid = (hi + lo) / 2;

      predicate_merge_sort(a, leq, temp, perm, lo, mid);

      predicate_merge_sort(a, leq, temp, perm, mid + 1, hi);

      predicate_merge(a, leq, temp, perm, lo, mid, hi);

   }

   template < typename ARRAY, typename PRED >
   void predicate_stable_index_sort(ARRAY & a, index_array & perm, PRED leq)
   {

      index_array temp;

      temp.set_size(a.get_size());

      predicate_index_merge_sort(a, leq, temp, perm, 0, a.get_upper_bound());

   }



   // Merges two subarrays of arr[].
   // First subarray is arr[l..m]
   // Second subarray is arr[m+1..r]
   template < typename ARRAY, typename PRED >
   void predicate_merge(ARRAY & a, PRED leq, int l, int m, int r)
   {

      int i, j, k;
      int n1 = m - l + 1;
      int n2 = r - m;

      /* create temp arrays */
      ARRAY L;
      L.set_size(n1);
      ARRAY R;
      R.set_size(n2);

      /* Copy data to temp arrays L[] and R[] */
      for (i = 0; i < n1; i++)
         L[i] = a[l + i];
      for (j = 0; j < n2; j++)
         R[j] = a[m + 1 + j];

      /* Merge the temp arrays back into arr[l..r]*/
      i = 0; // Initial iptr of first subarray
      j = 0; // Initial iptr of second subarray
      k = l; // Initial iptr of merged subarray
      while (i < n1 && j < n2)
      {
         if (leq(L[i], R[j]))
         {
            a[k] = L[i];
            i++;
         }
         else
         {
            a[k] = R[j];
            j++;
         }
         k++;
      }

      /* Copy the remaining elements of L[], if there
         are any */
      while (i < n1)
      {
         a[k] = L[i];
         i++;
         k++;
      }

      /* Copy the remaining elements of R[], if there
         are any */
      while (j < n2)
      {
         a[k] = R[j];
         j++;
         k++;
      }
   }

   /* l is for left iptr and r is right iptr of the
   sub-array of arr to be sorted */
   template < typename ARRAY, typename PRED >
   void predicate_merge_sort(ARRAY & a, PRED leq, int l, int r)
   {

      if (l < r)
      {

         // Same as (l+r)/2, but avoids overflow for large l and h

         int m = l + (r - l) / 2;

         // Sort first and second halves

         predicate_merge_sort(a, leq, l, m);

         predicate_merge_sort(a, leq, m + 1, r);

         predicate_merge(a, leq, l, m, r);

      }

   }

   template < typename ARRAY, typename PRED >
   void predicate_stable_sort(ARRAY & a, PRED leq)
   {

      predicate_merge_sort(a, leq, 0, a.get_upper_bound());

   }

} // namespace sort




//#include "collection_sort_array.h"
// #include "collection_key_sort_array.h"


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







//template < class TYPE, class ARG_TYPE, class ARRAY_TYPE>
//void comparable_list<  TYPE,  ARG_TYPE,  ARRAY_TYPE>::
//quick_sort(bool bAscendent)
//{
//
//   sort::quick_sort(*this, bAscendent);
//
//}

//template < class KEY, class TYPE, class ARG_TYPE , class ARRAY >
//void key_sort_array < KEY, TYPE, ARG_TYPE, ARRAY >::
//SetKeyProperty(KEY (TYPE::* pfnKeyProperty)())

//{
//   m_lpfnKeyProperty= pfnKeyProperty;

//   sort::QuickSortByKey < KEY, TYPE, ARG_TYPE >(
//      m_array,
//      m_lpfnKeyProperty);
//}
//
//




