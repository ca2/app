#include "framework.h"
//#include "sort.h"
//#include "acme/primitive/collection/numeric_array.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/user/_user.h"
//#endif


namespace  sort
{


   //   void quick_sort(
   //                  ::array<u32, u32> & array,
   //                  i32 fCompare(const index, const index),
   //                  void __swap(void * pVoidSwapArg, index iA, index iB),
   //                  void * pVoidSwapArg);
   //
   //
   //   void BubbleSort(::i32 * pint, i32 size);
   //

   //   void quick_sort(
   //      ::array<u32, u32> & array,
   //      i32 fCompare(const index, const index),
   //      void __swap(void * pVoidSwapArg, index iA, index iB),
   //      void * pVoidSwapArg)
   //   {
   //
   //      index_array stackLowerBound;
   //      index_array stackUpperBound;
   //      index iLowerBound;
   //      index iUpperBound;
   //      index iLPos, iUPos, iMPos;
   //
   //      u32 t;
   //
   //      if(array.get_size() >= 2)
   //      {
   //         stackLowerBound.push(0);
   //         stackUpperBound.push(array.get_upper_bound());
   //         while(true)
   //         {
   //            iLowerBound = stackLowerBound.pop();
   //            iUpperBound = stackUpperBound.pop();
   //            iLPos = iLowerBound;
   //            iMPos = iLowerBound;
   //            iUPos = iUpperBound;
   //            while(true)
   //            {
   //               while(true)
   //               {
   //                  if(iMPos == iUPos)
   //                     break;
   //                  if(fCompare(array.get_at(iMPos), array.get_at(iUPos)) <= 0)
   //                     iUPos--;
   //                  else
   //                  {
   //                     t = array.get_at(iMPos);
   //                     array.set_at(iMPos, array.get_at(iUPos));
   //                     array.set_at(iUPos, t);
   //                     __swap(pVoidSwapArg, iUPos, iMPos);
   //
   //                     break;
   //                  }
   //               }
   //               if(iMPos == iUPos)
   //                  break;
   //               iMPos = iUPos;
   //               while(true)
   //               {
   //                  if(iMPos == iLPos)
   //                     break;
   //                  if(fCompare(array.get_at(iLPos), array.get_at(iMPos)) <= 0)
   //                     iLPos++;
   //                  else
   //                  {
   //                     t = array.get_at(iMPos);
   //                     array.set_at(iMPos, array.get_at(iLPos));
   //                     array.set_at(iLPos, t);
   //                     __swap(pVoidSwapArg, iLPos, iMPos);
   //
   //                     break;
   //                  }
   //               }
   //               if(iMPos == iLPos)
   //                  break;
   //               iMPos = iLPos;
   //            }
   //            if(iLowerBound < iMPos - 1)
   //            {
   //               stackLowerBound.push(iLowerBound);
   //               stackUpperBound.push(iMPos - 1);
   //            }
   //            if(iMPos + 1 < iUpperBound)
   //            {
   //               stackLowerBound.push(iMPos + 1);
   //               stackUpperBound.push(iUpperBound);
   //            }
   //            if(stackLowerBound.get_size() == 0)
   //               break;
   //         }
   //      }
   //
   //   }

   //   void BubbleSort(::i32 * pint, i32 size)
   //
   //   {
   //      for(i32 i = 0; i < size; i++)
   //         for(i32 j = i + 1; j < size; j++)
   //         {
   //            if(pint[i] > pint[j])
   //
   //            {
   //               ::i32 __swap = pint[j];
   //
   //               pint[j] = pint[i];
   //
   //               pint[i] = __swap;
   //
   //            }
   //         }
   //
   //   }

   void quick_sort(
      index iSize,
      ::array < ARG_COMPARE_FUNCTION >& comparefna,
      ::array < ARG_SWAP_FUNCTION >& swapfna,
      void_ptra& comparearga,
      void_ptra& swaparga)
      {

         ::array < ::function < ::std::strong_ordering(void*, iptr, iptr) > > comparefunctiona;
         ::array < ::function < void(void*, iptr, iptr) > >& swapfunctiona;

         for(auto fna : comparefna)
         {

            comparefunction.add([fna](void * p, iptr a, iptr b)
            {

               return fna(a, b) <=> 0;

            });


         }

         for(auto fna : swapfna)
         {

            swapfunctiona.add([fna](void * p, iptr a, iptr b)
            {

               return fna(p, a, b);

            });

         }

      }
   

   void quick_sort(
      index iSize,
      ::array < ::function < ::std::strong_ordering(void*, iptr, iptr) > >& comparefunctiona,
      ::array < ::function < void(void*, iptr, iptr) > >& swapfunctiona,
      void_ptra& comparearga,
      void_ptra& swaparga)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      i32 iCmp;
      ::std::strong_ordering iCompare;

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
                  for (i32 i = 0; i < comparefunctiona.get_size(); i++)
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
                     for (i32 i = 0; i < swapfunctiona.get_size(); i++)
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
                  for (i32 i = 0; i < comparefunctiona.get_size(); i++)
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
                     for (i32 i = 0; i < swapfunctiona.get_size(); i++)
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


} // namespace sort





//void ___compile_test_sort_array_21304528734()
//{
//
//
//   sort_pointer_array < ::user::interaction > sorteduia;
//
//   auto puiA = __new(::user::interaction);
//
//   puiA->set_window_text("01");
//
//   auto puiH = __new(::user::interaction);
//
//   puiH->set_window_text("10");
//
//   sorteduia.add(puiA);
//
//   sorteduia.add(puiH);
//
//   sorteduia.add_sort("name", [](auto & pui1, auto & pui2)
//      {
//         string str1;
//         pui1->get_window_text(str1);
//         string str2;
//         pui1->get_window_text(str2);
//         return str1.case_insensitive_order(str2);
//      });
//
//   auto puiC = __new(::user::interaction);
//
//   puiC->set_window_text("03");
//
//   ::index iC = -1;
//
//   bool bFind = sorteduia.find(puiC, iC, "name");
//
//}
