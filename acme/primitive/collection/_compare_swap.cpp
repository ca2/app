// Created by camilo on 2023-01-20 22:37 <3ThomasBorregaardSørensen!!
// 2023-01-20 22:37 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
// 2023-01-20 22:37 - lowluds, shegotmad, mrsteinbergplease and octaelliptical contribution through Twitch.TV!!
#include "framework.h"
#include "_compare_swap.h"


namespace compare_swap
{


   //void CLASS_DECL_ACME quick_sort(
   //   index iSize,
   //   const ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
   //   const ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
   //   const void_ptra & comparearga,
   //   const void_ptra & swaparga)
   //   {

   //      ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > comparefunctiona;
   //      ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > swapfunctiona;

   //      for (auto fna : comparefna)
   //      {

   //         comparefunctiona.add([fna](void * p, iptr a, iptr b)
   //         {

   //                  return fna(p, a, b) <=> 0;

   //         });

   //      }

   //      for (auto fna : swapfna)
   //      {

   //         swapfunctiona.add([fna](void * p, iptr a, iptr b)
   //         {

   //                  return fna(p, a, b);

   //         });

   //      }

   //      quick_sort(iSize,
   //         comparefunctiona,
   //         swapfunctiona,
   //         comparearga,
   //         swaparga);

   //}


   void quick_sort(
      index iSize,
      const ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > & comparefunctiona,
      const ::array < ::function < void(void *, iptr, iptr) > > & swapfunctiona,
      const void_ptra & comparearga,
      const void_ptra & swaparga)
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


} // namespace compare_swap



#ifdef DEBUG



   //namespace test_compilation_some_int_compare_functions
   //{



   //   void stringaSwap(void * lpVoidSwapArg, const index i1, const index i2)
   //   {

   //      string_array * pstra = (string_array *)lpVoidSwapArg;

   //      string str = pstra->element_at(i1);

   //      pstra->element_at(i1) = pstra->element_at(i2);

   //      pstra->element_at(i2) = str;

   //   }


   //   ::std::strong_ordering stringaCompare(void * lpVoidCompareArg, const index i1, const index i2)
   //   {

   //      string_array * pstra = (string_array *)lpVoidCompareArg;

   //      return pstra->element_at(i1) <=> pstra->element_at(i2);

   //   }


   //   void test_compilation_some_int_compare_functions()
   //   {

   //      ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > comparefna;

   //      ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > swapfna;

   //      void_ptra comparearga;

   //      void_ptra swaparga;

   //      string_array straName;

   //      for (int i = 0; i < straPath.get_size(); i++)
   //      {
   //         string strCode(straPath[i].name() + strSuffix);
   //         string str;
   //         str.format("%08x", acmesystem()->crc32(0, strCode));
   //         straName.set_at_grow(i, str);
   //      }

   //      comparefna.add(&stringaCompare);
   //      swapfna.add(&stringaSwap);
   //      swapfna.add(&filelistingSwap);
   //      comparearga.add(&straName);
   //      swaparga.add(&straName);
   //      swaparga.add(&straPath);
   //   }


   //} // namespace test_compilation_some_int_compare_functions


#include "acme/filesystem/filesystem/listing.h"


namespace test_compilation_some_strong_ordering_swap_functions
{


   void filelistingSwap(void * lpVoidSwapArg, const index i1, const index i2)
   {
      ::file::listing * plisting = (::file::listing *)lpVoidSwapArg;
      ::file::path path = plisting->element_at(i1);
      plisting->element_at(i1) = plisting->element_at(i2);
      plisting->element_at(i2) = path;
   }


   void stringaSwap(void * lpVoidSwapArg, const index i1, const index i2)
   {
      string_array * pstra = (string_array *)lpVoidSwapArg;
      string str = pstra->element_at(i1);
      pstra->element_at(i1) = pstra->element_at(i2);
      pstra->element_at(i2) = str;
   }


   ::std::strong_ordering stringaCompare(void * lpVoidCompareArg, const index i1, const index i2)
   {
      string_array * pstra = (string_array *)lpVoidCompareArg;
      return pstra->element_at(i1) <=> pstra->element_at(i2);
   }



   void test_compilation_some_strong_ordering_swap_functions(string_array & straPath, const ::string & strSuffix)
   {

      ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > comparefna;
      ::array < ::function < void(void *, iptr, iptr) > > swapfna;
      void_ptra comparearga;
      void_ptra swaparga;
      string_array straName;
      for (int i = 0; i < straPath.size(); i++)
      {
         string strCode(straPath[i] + strSuffix);
         string str;
         str.format("%08x", atoi(strCode));
         straName.set_at_grow(i, str);
      }

      comparefna.add(&stringaCompare);
      swapfna.add(&stringaSwap);
      swapfna.add(&filelistingSwap);
      comparearga.add(&straName);
      swaparga.add(&straName);
      swaparga.add(&straPath);


      ::compare_swap::quick_sort(straPath.get_size(), comparefna, swapfna, comparearga, swaparga);

   }


} // namespace test_compilation_some_strong_ordering_swap_functions


#endif DEBUG




