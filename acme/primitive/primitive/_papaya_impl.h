#pragma once


namespace acme
{


   inline bool is_false(const ::scoped_string & scopedstr)
   {

      return ::is_null(psz) || *psz == '\0' || case_insensitive_ansi_compare(psz, "false") == 0 || case_insensitive_ansi_compare(psz, "no") == 0;

   }


   inline bool is_true(const ::scoped_string & scopedstr)
   {

      return !is_false(psz);

   }


   inline bool is_set_false(const ::scoped_string & scopedstr)
   {

      return ::is_set(psz) && (case_insensitive_ansi_compare(psz, "false") == 0 || case_insensitive_ansi_compare(psz, "no") == 0);

   }


   inline bool is_set_true(const ::scoped_string & scopedstr)
   {

      return ::is_set(psz) && (case_insensitive_ansi_compare(psz, "true") == 0 || case_insensitive_ansi_compare(psz, "yes") == 0);

   }


   inline bool is_false(const ::string & str)
   {

      return str.is_empty() || str.case_insensitive_order("false") == 0 || str.case_insensitive_order("no") == 0;

   }


   inline bool is_true(const ::string & str)
   {

      return !is_false(str);

   }


   inline bool is_set_false(const ::string & str)
   {

      return str.case_insensitive_order("false") == 0 || str.case_insensitive_order("no") == 0;

   }


   inline bool is_set_true(const ::string & str)
   {

      return str.case_insensitive_order("true") == 0 || str.case_insensitive_order("yes") == 0;

   }



} // namespace acme






template < typename A, typename B >
inline bool equals(const A & a, const B & b)
{

   return a == b;

}

