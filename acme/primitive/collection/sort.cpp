#include "framework.h"
//#if !BROAD_PRECOMPILED_HEADER
//#include "acme/user/_user.h"
//#endif


namespace  sort
{


   void quick_sort(
                  ::array<u32, u32> & array,
                  i32 fCompare(const index, const index),
                  void __swap(void * pVoidSwapArg, index iA, index iB),
                  void * pVoidSwapArg);


   void BubbleSort(LPINT pint, i32 size);


   void quick_sort(
      ::array<u32, u32> & array,
      i32 fCompare(const index, const index),
      void __swap(void * pVoidSwapArg, index iA, index iB),
      void * pVoidSwapArg)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      u32 t;

      if(array.get_size() >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(array.get_upper_bound());
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
                  if(fCompare(array.get_at(iMPos), array.get_at(iUPos)) <= 0)
                     iUPos--;
                  else
                  {
                     t = array.get_at(iMPos);
                     array.set_at(iMPos, array.get_at(iUPos));
                     array.set_at(iUPos, t);
                     __swap(pVoidSwapArg, iUPos, iMPos);

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
                  if(fCompare(array.get_at(iLPos), array.get_at(iMPos)) <= 0)
                     iLPos++;
                  else
                  {
                     t = array.get_at(iMPos);
                     array.set_at(iMPos, array.get_at(iLPos));
                     array.set_at(iLPos, t);
                     __swap(pVoidSwapArg, iLPos, iMPos);

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

   void BubbleSort(LPINT pint, i32 size)

   {
      for(i32 i = 0; i < size; i++)
         for(i32 j = i + 1; j < size; j++)
         {
            if(pint[i] > pint[j])

            {
               INT __swap = pint[j];

               pint[j] = pint[i];

               pint[i] = __swap;

            }
         }

   }



   void quick_sort(
      index iSize,
      ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
      ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
      void_ptra & comparearga,
      void_ptra & swaparga)
   {

      index_array stackLowerBound;
      index_array stackUpperBound;
      index iLowerBound;
      index iUpperBound;
      index iLPos, iUPos, iMPos;

      i32 iCmp;
      i32 iCompare;

      if(iSize >= 2)
      {
         stackLowerBound.push(0);
         stackUpperBound.push(iSize - 1);
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
                  iCmp = 0;
                  for(i32 i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iMPos, iUPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iUPos--;
                  else
                  {
                     for(i32 i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iMPos, iUPos);
                     }
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
                  iCmp = 0;
                  for(i32 i = 0; i < comparefna.get_size(); i++)
                  {
                     iCompare = comparefna[i](comparearga[i], iLPos, iMPos);
                     if(iCompare > 0)
                     {
                        iCmp = 1;
                        break;
                     }
                     else if(iCompare < 0)
                     {
                        iCmp = -1;
                        break;
                     }
                  }
                  if(iCmp <= 0)
                     iLPos++;
                  else
                  {
                     for(i32 i = 0; i < swapfna.get_size(); i++)
                     {
                        swapfna[i](swaparga[i], iLPos, iMPos);
                     }
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
//         return str1.compare_ci(str2);
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
