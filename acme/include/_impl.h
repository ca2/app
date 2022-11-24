//
// Created by camilo on 22/11/22.
//
#pragma once


template<typename T1, typename T2>
inline void sort_non_negative(T1& t1, T2& t2)
{

   if (t1 < ::numeric_info<T1>::null())
   {

      return;

   }

   if (t2 < ::numeric_info<T2>::null())
   {

      return;

   }

   if (t1 > t2)
   {

      auto t = t2;

      t2 = t1;

      t1 = t;

   }

}




