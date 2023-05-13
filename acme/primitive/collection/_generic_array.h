//
// Created by camilo on 2023-05-12 21:34 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace generic
{


   namespace array
   {


      template < typename ARRAY, typename CONTAINER >
      ARRAY & append(ARRAY & a, const CONTAINER & container)
      {

         if constexpr( ::std::is_base_of_v<ARRAY, CONTAINER> || ::std::is_base_of_v<CONTAINER, ARRAY>)
         {

            a.append(container);

         }
         else
         {

            for (auto & item : container)
            {

               ::copy(a.add_new(), item);

            }

         }

         return a;

      }


      template < typename ARRAY, typename CONTAINER >
      ARRAY & copy(ARRAY & a, const CONTAINER & container)
      {

         if constexpr(::std::is_base_of_v<ARRAY, CONTAINER> || ::std::is_base_of_v<CONTAINER, ARRAY>)
         {

            a.append(container);

         }
         else
         {

            a.clear();

            append(a, container);

         }

         return a;

      }


   } // namespace array


} // namespace generic



