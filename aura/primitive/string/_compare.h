#pragma once


namespace str
{

   template < typename TYPE1, typename TYPE2 >
   inline i32 compare(const TYPE1 & str1, const TYPE2 & str2);

   template < typename TYPE1, typename TYPE2 >
   inline i32 compare_ci(const TYPE1 & str1, const TYPE2 & str2);

   template < typename TYPE1, typename TYPE2 >
   inline bool equals(const TYPE1 & str1, const TYPE2 & str2);

   template < typename TYPE1, typename TYPE2 >
   inline bool equals_ci(const TYPE1 & str1, const TYPE2 & str2);

   template < typename TYPE1, typename TYPE2 >
   inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent = nullptr);

   template < typename TYPE1, typename TYPE2 >
   inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent = nullptr);

   template < typename TYPE, typename PREFIX >
   inline bool begins(const TYPE & str, const PREFIX & strPrefix);

   template < typename TYPE, typename FED, typename PREFIX >
   inline bool begins(const TYPE & str, FED & strFed, const PREFIX & strPrefix);

   template < typename TYPE, typename PREFIX >
   inline bool begins_ci(const TYPE & str, const PREFIX & strPrefix);

   template < typename TYPE, typename FED, typename PREFIX >
   inline bool begins_ci(const TYPE & str, FED & strFed, const PREFIX & strPrefix);

   // case insensitive, ignore white space - only in searched string
   bool CLASS_DECL_AURA begins_ci_iws(const string & str, const string & strPrefix);
   bool CLASS_DECL_AURA begins_ci_iws(const wstring & wstr, const wstring & wstrPrefix);

   template < typename TYPE, typename PREFIX >
   inline bool begins_eat(TYPE & str, const PREFIX & strPrefix);

   template < typename TYPE, typename PREFIX >
   inline bool begins_eat_ci(TYPE & str, const PREFIX & strPrefix);

   template < typename PREFIX >
   inline bool begins_eat(var & var, const PREFIX& strPrefix);

   template < typename PREFIX >
   inline bool begins_eat_ci(var & var, const PREFIX& strPrefix);

   template < typename PREFIX >
   inline bool begins_eat(property & property, const PREFIX& strPrefix);

   template < typename PREFIX >
   inline bool begins_eat_ci(property & property, const PREFIX& strPrefix);

   bool CLASS_DECL_AURA while_begins_with_chars_eat(string & str, const char * pcszChars);
   bool CLASS_DECL_AURA while_begins_with_chars_eat_ci(string & str, const char * pcszChars);

   template < typename TYPE, typename SUFFIX >
   inline bool ends(const TYPE & str, const SUFFIX & strSuffix);
   
   template < typename TYPE, typename SUFFIX >
   inline bool ends_ci(const TYPE & str, const SUFFIX & strSuffix);

   template < typename TYPE, typename SUFFIX >
   inline bool ends_eat(TYPE & str, const SUFFIX & strSuffix);

   template < typename TYPE, typename SUFFIX >
   inline bool ends_eat_ci(TYPE & str, const SUFFIX & strSuffix);

   bool CLASS_DECL_AURA eat_before(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound = false);
   bool CLASS_DECL_AURA eat_before_let_separator(string & strBefore, string strSeparator, string & str, bool bEatEverythingIfNotFound = false);

   bool CLASS_DECL_AURA eat_before(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound = false);
   bool CLASS_DECL_AURA eat_before_let_separator(wstring & wstrBefore, wstring wstrSeparator, wstring & wstr, bool bEatEverythingIfNotFound = false);

} // namespace str



