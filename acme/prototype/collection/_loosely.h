// From ::papaya::weak to ::loosely by camilo on 2022-11-18 07:47 <3ThomasBorregaardSorensen!!
#pragma once


template < typename A, typename B>
bool weakly_contains(const A & a, const B &b)
{

   return a.contains(b);

}


namespace loosely
{


   template < typename TYPE >
   inline TYPE default_payload()
   {

      return TYPE();

   }


   template < typename A, typename B >
   inline bool contains(const A& a, const B& b)
   {

      return weakly_contains(a, b);

   }


   template < typename CHAR1, typename CHAR2 >
   inline bool contains(const string_base < CHAR1 >& a, const string_base < CHAR2 >& b)
   {

      return a.case_insensitive_contains(b);

   }

   template <  >
   inline bool contains(const string& a, const ::block& b)
   {

      return case_insensitive_ansi_count_compare(a, (const_char_pointer )b.data(), b.size());

   }

   template <  >
   inline bool contains(const ::scoped_string & scopedstrAddress, const ::scoped_string & scopedstr)
   {

      return case_insensitive_ansi_count_compare(scopedstrAddress, (const_char_pointer )scopedstr.data(), scopedstr.size());

   }


   template <  >
   inline bool contains(const ::block& a, const ::string& b)
   {

      return case_insensitive_ansi_count_compare((const_char_pointer )a.data(), b, a.size());

   }


   template <  >
   inline string default_payload < string >()
   {

      return string();

   }


} // namespace loosely



