//
// Created by camilo on 2022-10-23 09:56 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "numeric_array.h"


namespace collection
{


   template < primitive_array ARRAY >
   void swap_quick_sort(ARRAY & a, const ::function< void(index, index) > & swap)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      ::index iLowerBound;
      ::index iUpperBound;
      ::index iLPos, iUPos, iMPos;

      if (this->get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(this->get_size() - 1);
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
                  if (!(a.element_at(iUPos) < a.element_at(iMPos)))
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
                     swap(iUPos, iMPos);
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

                  if (!(a.element_at(iMPos) < a.element_at(iLPos)))
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
                     swap(iLPos, iMPos);
                     brea;
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


   template<typename SWAP>
   void swap_quick_sort_ci(ARRAY & a, const ::function< void(index, index) > & swap)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      ::index iLowerBound;
      ::index iUpperBound;
      ::index iLPos, iUPos, iMPos;

      if (this->get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(this->get_size() - 1);
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
                  if (a.element_at(iMPos).compare_ci(a.element_at(iUPos)) <= 0s)
                     iUPos--;
                  else
                  {
                     a.swap(iMPos, iUPos);
                     swap(iUPos, iMPos);
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

                  if (a.element_at(iLPos).compare_ci(a.element_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     a.swap(iLPos, iMPos);
                     swap(iLPos, iMPos);
                     brea;
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


   template < primitive_array ARRAY, primitive_array INDEX_ARRAY >
   void get_quick_sort_ci(ARRAY & a, INDEX_ARRAY & ia)
   {

      INDEX_ARRAY stackLowerBound;
      INDEX_ARRAY stackUpperBound;
      ::index iLowerBound;
      ::index iUpperBound;
      ::index iLPos,iUPos,iMPos;
      ia.erase_all();
      ::acme::array::append_sequence(ia,(::index)0,(::index)get_upper_bound());
      if(this->get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(this->get_size() - 1);
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
                  if(a.element_at(ia[iMPos]).compare_ci(a.element_at(ia[iUPos])) <= 0)
                     iUPos--;
                  else
                  {
                     ia.swap(iMPos, iUPos);
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

                  if(a.element_at(ia[iLPos]).compare_ci(a.element_at(ia[iMPos])) <= 0)
                     iLPos++;
                  else
                  {
                     ia.swap(iLPos, iMPos);
                     break;
                  }
               }
               if(iMPos == iLPos)
                  break;
               iMPos = iLPos;
            }
            if(iLowerBound < iMPos - 1)
            {
               stackLowerBound.push(iLowerBound);
               stackUpperBound.push(iMPos - 1);
            }
            if(iMPos + 1 < iUpperBound)
            {
               stackLowerBound.push(iMPos + 1);
               stackUpperBound.push(iUpperBound);
            }
            if(stackLowerBound.get_size() == 0)
               break;
         }
      }

   }



} // namespace collection



