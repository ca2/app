#pragma once


namespace acme
{


   inline bool is_false(const ::scoped_string & scopedstr)
   {

      return ::is_null(scopedstr) || *psz == '\0' || case_insensitive_ansi_compare(scopedstr, "false") == 0 || case_insensitive_ansi_compare(scopedstr, "no") == 0;

   }


   inline bool is_true(const ::scoped_string & scopedstr)
   {

      return !is_false(scopedstr);

   }


   inline bool is_set_false(const ::scoped_string & scopedstr)
   {

      return ::is_set(scopedstr) && (case_insensitive_ansi_compare(scopedstr, "false") == 0 || case_insensitive_ansi_compare(scopedstr, "no") == 0);

   }


   inline bool is_set_true(const ::scoped_string & scopedstr)
   {

      return ::is_set(scopedstr) && (case_insensitive_ansi_compare(scopedstr, "true") == 0 || case_insensitive_ansi_compare(scopedstr, "yes") == 0);

   }


   inline bool is_false(const ::scoped_string & scopedstr)
   {

      return str.is_empty() || str.case_insensitive_order("false") == 0 || str.case_insensitive_order("no") == 0;

   }


   inline bool is_true(const ::scoped_string & scopedstr)
   {

      return !is_false(str);

   }


   inline bool is_set_false(const ::scoped_string & scopedstr)
   {

      return str.case_insensitive_order("false") == 0 || str.case_insensitive_order("no") == 0;

   }


   inline bool is_set_true(const ::scoped_string & scopedstr)
   {

      return str.case_insensitive_order("true") == 0 || str.case_insensitive_order("yes") == 0;

   }



} // namespace acme






template < typename A, typename B >
inline bool equals(const A & a, const B & b)
{

   return a == b;

}

