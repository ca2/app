﻿// From ::papaya::weak to ::loosely by camilo on 2022-11-18 07:47 <3ThomasBorregaardSørensen!!
#pragma once


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

      return a.weakly_contains(b);

   }


   template < typename CHAR1, typename CHAR2 >
   inline bool contains(const string_base < CHAR1 >& a, const string_base < CHAR2 >& b)
   {

      return a.case_insensitive_contains(b);

   }

   template <  >
   inline bool contains(const string& a, const ::block& b)
   {

      return ansi_count_compare_ci(a, (const char*)b.data(), b.size());

   }

   template <  >
   inline bool contains(const string & a, const ::scoped_string & scopedstr)
   {

      return ansi_count_compare_ci(a, (const char *)scopedstr.data(), scopedstr.size());

   }


   template <  >
   inline bool contains(const ::block& a, const ::string& b)
   {

      return ansi_count_compare_ci((const char*)a.data(), b, a.size());

   }


   template <  >
   inline string default_payload < string >()
   {

      return string();

   }


} // namespace loosely



