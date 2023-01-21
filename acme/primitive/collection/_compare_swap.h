// Created by camilo on 2023-01-20 22:37 <3ThomasBorregaardSørensen!!
// 2023-01-20 22:37 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
// 2023-01-20 22:37 - lowluds, shegotmad, mrsteinbergplease and octaelliptical contribution through Twitch.TV!!
#pragma once




namespace compare_swap
{


   //typedef void (*ARG_SWAP_FUNCTION)(void * pVoidSwapArg, iptr, iptr);

   //typedef ::std::strong_ordering(*ARG_COMPARE_FUNCTION)(void * pVoidCompareArg, iptr, iptr);


   //void CLASS_DECL_ACME quick_sort(
   //   iptr iSize,
   //   const ::array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > & comparefna,
   //   const ::array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > & swapfna,
   //   const void_ptra & comparearga,
   //   const void_ptra & swaparga);


   void CLASS_DECL_ACME quick_sort(
      iptr iSize,
      const ::array < ::function < ::std::strong_ordering(void *, iptr, iptr) > > & comparefna,
      const ::array < ::function < void(void *, iptr, iptr) > > & swapfna,
      const void_ptra & comparearga,
      const void_ptra & swaparga);


} //  namespace compare_swap



