//
// Created by camilo on 2022-10-22 18:21 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace acme
{


   namespace array2d
   {

      template < typename A >
      ::collection::count predominant_column_count(A & a)
      {

         index_to_index column_count;

         for (::collection::index i = 0; i < a.get_size(); i++)
         {

            column_count[a[i].get_count()]++;

         }

         ::collection::count c = -1;

         ::collection::count cMax = -1;

         for (auto & assoc : column_count)
         {

            if (assoc.element2() > cMax || (assoc.element2() == cMax && assoc.element1() > c))
            {

               c = assoc.element1();

               cMax = assoc.element2();

            }

         }

         return c;

      }


   } //namespace array2d


} // namespace acme



