// Created by camilo on 2023-01-20 22:37 <3ThomasBorregaardSorensen!!
// 2023-01-20 22:37 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
// 2023-01-20 22:37 - lowluds, shegotmad, mrsteinbergplease and octaelliptical contribution through Twitch.TV!!
#pragma once




namespace compare_swap
{


   template < typename F1, typename F2, typename A1, typename A2 >
   void quick_sort_compare_swap(
      ::collection::index iSize,
      //const ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > & comparefunctiona,
      const F1 & comparefunctiona,
      //const ::array < ::function < void(void *, iptr, iptr) > > & swapfunctiona,
      const F2 & swapfunctiona,
      //const void_ptra & comparearga,
      const A1 & comparearga,
      //const void_ptra & swaparga)
      const A2 & swaparga)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      ::collection::index iLowerBound;
      ::collection::index iUpperBound;
      ::collection::index iLPos, iUPos, iMPos;

      int iCmp;
      ::std::strong_ordering iCompare(::std::strong_ordering::equal);

      if (iSize >= 2)
      {

         stackLowerBound.push(0);
         stackUpperBound.push(iSize - 1);

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
                  iCmp = 0;
                  for (int i = 0; i < comparefunctiona.get_size(); i++)
                  {
                     auto iCompare = comparefunctiona[i](comparearga[i], iMPos, iUPos);
                     if (iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if (iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if (iCmp <= 0)
                     iUPos--;
                  else
                  {
                     for (int i = 0; i < swapfunctiona.get_size(); i++)
                     {
                        swapfunctiona[i](swaparga[i], iMPos, iUPos);
                     }
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
                  iCmp = 0;
                  for (int i = 0; i < comparefunctiona.get_size(); i++)
                  {
                     iCompare = comparefunctiona[i](comparearga[i], iLPos, iMPos);
                     if (iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if (iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if (iCmp <= 0)
                     iLPos++;
                  else
                  {
                     for (int i = 0; i < swapfunctiona.get_size(); i++)
                     {
                        swapfunctiona[i](swaparga[i], iLPos, iMPos);
                     }
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


   //typedef void (*ARG_SWAP_FUNCTION)(void * pVoidSwapArg, iptr, iptr);

   //typedef ::std::strong_ordering(*ARG_COMPARE_FUNCTION)(void * pVoidCompareArg, iptr, iptr);


   //void CLASS_DECL_ACME quick_sort(
   //   iptr iSize,
   //   const ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
   //   const ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
   //   const void_ptra & comparearga,
   //   const void_ptra & swaparga);


   // void CLASS_DECL_ACME quick_sort(
   //    iptr iSize,
   //    const ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > & comparefna,
   //    const ::array < ::function < void(void *, iptr, iptr) > > & swapfna,
   //    const void_ptra & comparearga,
   //    const void_ptra & swaparga);

   // void CLASS_DECL_ACME quick_sort(
   //    iptr iSize,
   //    const ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > & comparefna,
   //    const ::array < ::function < void(void *, iptr, iptr) > > & swapfna,
   //    const void_ptra & comparearga,
   //    const void_ptra & swaparga);


} //  namespace compare_swap



