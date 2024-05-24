// Created by camilo on 2023-01-20 22:08 <3ThomasBorregaardSorensen!!
// 2023-01-20 22:08 - lowluds, lowluds, octaelliptical and mr. stein contribution through Twitch.TV!!
// 2023-01-20 22:08 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
#pragma once


namespace generic
{


   namespace range
   {


      template < primitive_range RANGE, typename COMPARE_INTERFACE >
      void quick_sort(
      RANGE & range,
      COMPARE_INTERFACE * pinterface,
      ::std::strong_ordering(COMPARE_INTERFACE:: * fCompare)(typename RANGE::ARG_ITEM a, typename RANGE::ARG_ITEM b))
      {

         comparable_array < typename RANGE::const_iterator > stackLowerBound;

         comparable_array < typename RANGE::const_iterator > stackUpperBound;

         typename RANGE::const_iterator pLowerBound;

         typename RANGE::const_iterator pUpperBound;

         typename RANGE::const_iterator pLPos, pUPos, pMPos;

         if (range.size() >= 2)
         {

            stackLowerBound.add(range.begin());

            stackUpperBound.add(range.end() - 1);

            while (true)
            {

               pLowerBound = stackLowerBound.pop();

               pUpperBound = stackUpperBound.pop();

               pLPos = pLowerBound;

               pMPos = pLowerBound;

               pUPos = pUpperBound;

               while (true)
               {

                  while (true)
                  {

                     if (pMPos == pUPos)
                     {

                        break;

                     }

                     if ((pinterface->*fCompare)(*pMPos, *pUPos) <= 0)
                     {

                        pUPos--;

                     }
                     else
                     {

                        range.__swap(pMPos, pUPos);

                        break;

                     }

                  }

                  if (pMPos == pUPos)
                  {

                     break;

                  }

                  pMPos = pUPos;

                  while (true)
                  {

                     if (pMPos == pLPos)
                     {

                        break;

                     }

                     if ((pinterface->*fCompare)(*pLPos, *pMPos) <= 0)
                     {

                        pLPos++;

                     }
                     else
                     {

                        range.__swap(pLPos, pMPos);

                        break;

                     }

                  }

                  if (pMPos == pLPos)
                  {

                     break;

                  }

                  pMPos = pLPos;

               }

               if (pLowerBound < pMPos - 1)
               {

                  stackLowerBound.push(pLowerBound);

                  stackUpperBound.push(pMPos - 1);

               }

               if (pMPos + 1 < pUpperBound)
               {

                  stackLowerBound.push(pMPos + 1);

                  stackUpperBound.push(pUpperBound);

               }

               if (stackLowerBound.get_size() == 0)
               {

                  break;

               }

            }

         }

      }


   } // namespace range


} //  namespace generic


