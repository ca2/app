#pragma once


namespace str
{

   template < typename TYPE >
   class get_char_type
   {
   public:

      using CHAR_TYPE = typename TYPE::CHAR_TYPE;

   };

   template < > class get_char_type < const char * > { public: using CHAR_TYPE = char; };
   template < > class get_char_type < char * > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < const char[n] > { public: using CHAR_TYPE = char; };
   template < int n > class get_char_type < char[n] > { public: using CHAR_TYPE = char; };


   template < typename TYPE1, typename TYPE2 >
   inline i32 compare(const TYPE1 & str1, const TYPE2 & str2)
   {

      return ::str::string_compare(str1, str2);

   }


   template < typename TYPE1, typename TYPE2 >
   inline i32 compare_ci(const TYPE1 & str1, const TYPE2 & str2)
   {

      return ::str::string_compare_ci(str1, str2);

   }

   template < typename TYPE1, typename TYPE2 >
   inline bool equals(const TYPE1 & str1, const TYPE2 & str2)
   {

      return !compare(str1, str2);

   }


   template < typename TYPE1, typename TYPE2 >
   inline bool equals_ci(const TYPE1 & str1, const TYPE2 & str2)
   {

      return !compare_ci(str1, str2);

   }

   template < typename TYPE1, typename TYPE2 >
   inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
   {

      return equals(str1, str2) ? strOnEqual : strOnDifferent;

   }


   template < typename TYPE1, typename TYPE2 >
   inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent)
   {

      return equals_ci(str1, str2) ? strOnEqual : strOnDifferent;

   }


   template < typename TYPE, typename PREFIX >
   inline bool begins(const TYPE & str, const PREFIX & strPrefix)
   {

      return !::str::string_n_compare(str, strPrefix, ::str::string_safe_length(strPrefix));

   }


   template < typename TYPE, typename FED, typename PREFIX >
   inline bool begins(const TYPE & str, FED & strFed, const PREFIX & strPrefix)
   {

      if (!begins(str, strPrefix))
      {

         return false;

      }

      strFed = strPrefix;

      return true;

   }


   template < typename TYPE, typename PREFIX >
   inline bool begins_ci(const TYPE & str, const PREFIX & strPrefix)
   {

      return !::str::string_n_compare_ci(str, strPrefix, ::str::string_safe_length(strPrefix));

   }


   template < typename TYPE, typename FED, typename PREFIX >
   inline bool begins_ci(const TYPE & str, FED & strFed, const PREFIX & strPrefix)
   {

      if (!begins_ci(str, strPrefix))
      {

         return false;

      }

      strFed = strPrefix;

      return true;

   }

   template < typename TYPE, typename PREFIX >
   inline bool begins_eat(TYPE & str, const PREFIX & strPrefix)
   {

      auto len = ::str::string_safe_length(strPrefix);

      if (::str::string_n_compare(str, strPrefix, len))
      {

         return false;

      }

      str = str.c_str() + len;

      return true;

   }


   template < typename TYPE, typename PREFIX >
   inline bool begins_eat_ci(TYPE & str, const PREFIX & strPrefix)
   {

      auto len = ::str::string_safe_length(strPrefix);

      if (::str::string_n_compare_ci(str, strPrefix, len))
      {

         return false;

      }

      str = str.ptr_at(len);

      return true;

   }



   template < typename PREFIX >
   inline bool begins_eat(payload & payload, const PREFIX& strPrefix)
   {

      string str = payload.get_string();

      if (!begins_eat(str, strPrefix))
      {

         return false;

      }

      payload = str;

      return true;

   }


   template < typename PREFIX >
   inline bool begins_eat_ci(payload & payload, const PREFIX& strPrefix)
   {

      string str = payload.get_string();

      if (!begins_eat_ci(str, strPrefix))
      {

         return false;

      }

      payload = str;

      return true;

   }


   template < typename PREFIX >
   inline bool begins_eat(property & property, const PREFIX& strPrefix)
   {

      return begins_eat((::payload&)property, strPrefix);

   }



   template < typename PREFIX >
   inline bool begins_eat_ci(property & property, const PREFIX& strPrefix)
   {

      return begins_eat_ci((::payload&)property, strPrefix);

   }


   template < typename TYPE, typename SUFFIX >
   inline bool ends(const TYPE & strTopic, const SUFFIX & strSuffix)
   {

      auto len = ::str::string_safe_length(strSuffix);

      auto end = ::str::string_safe_length(strTopic) - len;

      auto strEnd = __string_base(strTopic);

      auto pszEnd = strEnd.c_str() + end;

      auto strSuf = __string_base(strSuffix);

      auto pszSuf = strSuf.c_str();

      return !::str::string_n_compare(pszEnd, pszSuf, len);

   }


   template < typename SUFFIX >
   inline bool ends(const ::id & id, const SUFFIX & strSuffix)
   {

      return ends(string(id), strSuffix);

   }


   // one sample overload to show some mercy to broeginneersen
   inline bool ends(const ansichar * pszTopic, const ansichar * pszSuffix)
   {

      auto len = ::str::string_safe_length(pszSuffix);

      auto end = ::str::string_safe_length(pszTopic) - len;

      return !::str::string_n_compare(pszTopic + end, pszSuffix, len);

   }

   template < typename TYPE, typename SUFFIX >
   inline bool ends_ci(const TYPE & str, const SUFFIX & strSuffix)
   {

      using CHAR_TYPE = typename get_char_type < TYPE >::CHAR_TYPE;

      auto len = ::str::string_safe_length(strSuffix);

      auto end = ::str::string_safe_length(str) - len;

      return !::str::string_n_compare_ci(&((const CHAR_TYPE *)str)[end], strSuffix, len);

   }


   template < typename SUFFIX >
   inline bool ends_ci(const ::id & id, const SUFFIX & strSuffix)
   {

      return ends_ci(string(id), strSuffix);

   }


   inline bool ends_ci(const ansichar * pszTopic, const ansichar * pszSuffix)
   {

      auto len = ::str::string_safe_length(pszSuffix);

      auto end = ::str::string_safe_length(pszTopic) - len;

      return !::str::string_n_compare_ci(pszTopic + end, pszSuffix, len);

   }


   template < typename TYPE, typename SUFFIX >
   inline bool ends_eat(TYPE & str, const SUFFIX & strSuffix)
   {

      auto len = ::str::string_safe_length(strSuffix);

      auto end = ::str::string_safe_length(str) - len;

      if (::str::string_n_compare(&str[end], strSuffix, len))
      {

         return false;

      }

      str.truncate(end);

      return true;

   }


   template < typename TYPE, typename SUFFIX >
   inline bool ends_eat_ci(TYPE & str, const SUFFIX & strSuffix)
   {

      auto len = ::str::string_safe_length(strSuffix);

      auto end = ::str::string_safe_length(str) - len;

      if (::str::string_n_compare_ci(&str[end], strSuffix, len))
      {

         return false;

      }

      str.truncate(end);

      return true;

   }


} // namespace str


