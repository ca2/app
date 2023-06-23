// Created by camilo on 2023-01-20 22:25 <3ThomasBorregaardSorensen!!
// 2023-01-20 22:25 - Mummi, Lucinho, Bilbo, Blue, Carol e Zibia contribution through ca2 HQ!!
// 2023-01-20 22:25 - lowluds, shegotmad, mrsteinbergplease and octaelliptical contribution through Twitch.TV!!
#include "framework.h"
#include "_range.h"



#ifdef DEBUG


namespace test_compilation_some_range_functions
{


   class compare_interface
   {
   public:


      ::index_array m_ia;

      ::std::strong_ordering _001Compare(index iItem1, index iItem2)
      {

         return iItem1 <=> iItem2;

      }


   };


   void test_compilation_some_range_functions()
   {

      compare_interface compareinterface;

      ::generic::range::quick_sort(compareinterface.m_ia, &compareinterface, &compare_interface::_001Compare);

   }


} // namespace test_compilation_some_quick_sort_functions


#endif DEBUG


