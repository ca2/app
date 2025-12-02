// Created by camilo on 2023-07-09 19:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "_sort.h"


// take in accptr that _001RemoveIndexes machine
// the ::collection::index raw_array by sorting it and returning
// only the indexes that could be erased
// without indexes duplicates
template < prototype_array ARRAY, prototype_array ARRAY_INDEXES >
void _001RemoveIndexes(ARRAY & a, ARRAY_INDEXES & ia)
{

   // sort
   //::sort::quick_sort(ia,true);

   ::sort::QuickSortAsc(ia);

   ::collection::index i = ia.get_upper_bound();

   // filter out of upper bound indexes
   while (i >= 0 && ia[i] >= a.get_size())
   {

      ia.erase_at(i);

      i--;

   }

   // filter out of lower bound indexes
   while (ia.get_size() > 0 && ia[0] < 0)
   {

      ia.erase_at(0);

   }

   i = ia.get_upper_bound();

   // filter out duplicates
   while (i > 0 && ia[i] >= a.get_size())
   {

      if (ia[i] == ia[i - 1])
         ia.erase_at(i);

      i--;

   }

   a.erase_indexes(ia);

}



