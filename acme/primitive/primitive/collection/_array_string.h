// From RedDotLogics/utils by camilo on 2023-05-18 19:46 <3ThomasBorregaardSorensen!!
#pragma once


namespace generic
{


   namespace array
   {


      template < typename ARRAY >
      inline ARRAY from_string(const ::scoped_string& scopedstr)
      {

         static_assert(::primitive_integral<typename Container::BASE_TYPE>, "Integer containter expected.");

         ::tokenizer tokenizer(scopedstrPayload);

         ARRAY array;

         ::string strToken;

         while (tokenizer.get_next_token(strToken, "|"))
         {

            array.add(atoi(strToken));

         }

         return array;

      }


   } // namespace array


} // namespace generic


