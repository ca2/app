#pragma once


namespace papaya
{


   inline bool is_false(const char * psz)
   {

      return ::is_null(psz) || *psz == '\0' || ansi_compare_ci(psz, "false") == 0 || ansi_compare_ci(psz, "no") == 0;

   }


   inline bool is_true(const char * psz)
   {

      return !is_false(psz);

   }


   inline bool is_set_false(const char * psz)
   {

      return ::is_set(psz) && (ansi_compare_ci(psz, "false") == 0 || ansi_compare_ci(psz, "no") == 0);

   }


   inline bool is_set_true(const char * psz)
   {

      return ::is_set(psz) && (ansi_compare_ci(psz, "true") == 0 || ansi_compare_ci(psz, "yes") == 0);

   }


   inline bool is_false(const ::string & str)
   {

      return str.is_empty() || str.compare_ci("false") == 0 || str.compare_ci("no") == 0;

   }


   inline bool is_true(const ::string & str)
   {

      return !is_false(str);

   }


   inline bool is_set_false(const ::string & str)
   {

      return str.compare_ci("false") == 0 || str.compare_ci("no") == 0;

   }


   inline bool is_set_true(const ::string & str)
   {

      return str.compare_ci("true") == 0 || str.compare_ci("yes") == 0;

   }



} // namespace papaya






template < typename A, typename B >
inline bool equals(const A & a, const B & b)
{

   return a == b;

}

