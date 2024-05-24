//
// Created by camilo on 2/22/2024 <3ThomasBorregaardSorensen!!
//
#pragma once



namespace comparison
{


   namespace array
   {

      template < typename A, primitive_integral I, typename T >
      bool defer_transfer_to(A & a, I i, const T & t)
      {

         auto find = a.find_first(t);

         if(find == i)
         {

            return false;

         }

         a.erase_at(find);

         if(i > find)
         {

            i--;

         }

         a.insert_at(i, t);

         return true;

      }


   } // namespace array


} // namespace comparison