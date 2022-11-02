// Created by camilo on 2022-11-02 04:49 <3ThomasBorregaardSorensen!!
#pragma once


template < typename TUPLE, typename FIND_CONDITION, typename CONTINUE_CONDITION >
inline TUPLE * tuple_array_find(TUPLE * ptuple, FIND_CONDITION find_condition, CONTINUE_CONDITION continue_condition)
{

   while (continue_condition(ptuple))
   {

      if (find_condition(ptuple))
      {

         return ptuple;

      }

      ptuple++;

   }

   return nullptr;

}



