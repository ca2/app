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


   template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
   inline bool begins(const TOPIC_STRING & topic_string, const PREFIX_STRING & prefix_string)
   {
      
      using topic_type = typename base_const_c_string < TOPIC_STRING >::type;

      using prefix_type = typename base_const_c_string < PREFIX_STRING >::type;

      static_assert(::std::same_as < topic_type, prefix_type >);

      auto prefix = (prefix_type) prefix_string;

      auto prefix_length = ::str::string_safe_length(prefix);

      if (prefix_length <= 0)
      {

         return true;

      }

      auto topic = (topic_type) topic_string;

      auto topic_length = ::str::string_safe_length(topic);

      if (topic_length < prefix_length)
      {

         return false;

      }

      return !::str::string_n_compare(topic, prefix, prefix_length);

   }


   template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
   inline bool begins_ci(const TOPIC_STRING & topic_string, const PREFIX_STRING & prefix_string)
   {

      using topic_type = typename base_const_c_string < TOPIC_STRING >::type;

      using prefix_type = typename base_const_c_string < PREFIX_STRING >::type;

      static_assert(::std::same_as < topic_type, prefix_type >);

      auto prefix = (prefix_type)prefix_string;

      auto prefix_length = ::str::string_safe_length(prefix);

      if (prefix_length <= 0)
      {

         return true;

      }

      auto topic = (topic_type)topic_string;

      auto topic_length = ::str::string_safe_length(topic);

      if (topic_length < prefix_length)
      {

         return false;

      }

      return !::str::string_n_compare_ci(topic, prefix, prefix_length);

   }


//   template < typename TYPE, typename PREFIX >
//   inline bool begins_ci(const TYPE & str, const PREFIX & strPrefix)
//   {
//
//      return !::str::string_n_compare_ci(str, strPrefix, ::str::string_safe_length(strPrefix));
//
//   }


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

      str = &str[len];

      return true;

   }



   template < typename PREFIX >
   inline bool begins_eat(::payload & payload, const PREFIX& strPrefix)
   {

      string str = payload.string();

      if (!begins_eat(str, strPrefix))
      {

         return false;

      }

      payload = str;

      return true;

   }


   template < typename PREFIX >
   inline bool begins_eat_ci(::payload & payload, const PREFIX& strPrefix)
   {

      string str = payload.string();

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


   template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
   inline bool ends(const TOPIC_STRING & topic_string, const SUFFIX_STRING & suffix_string)
   {

      using topic_type = typename base_const_c_string < TOPIC_STRING >::type;

      using suffix_type = typename base_const_c_string < SUFFIX_STRING >::type;

      static_assert(::std::same_as < topic_type, suffix_type >);

      auto suffix = (suffix_type) suffix_string;

      auto suffix_length = ::str::string_safe_length(suffix);

      if (suffix_length <= 0)
      {

         return true;

      }

      auto topic = (topic_type) topic_string;

      auto topic_length = ::str::string_safe_length(topic);

      if (topic_length < suffix_length)
      {

         return false;

      }

      auto end_index = (topic_length - suffix_length);

      auto end = topic + end_index;

      return !::str::string_n_compare(end, suffix, suffix_length);

   }


   template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
   inline bool ends_ci(const TOPIC_STRING & topic_string, const SUFFIX_STRING & suffix_string)
   {

      using topic_type = typename base_const_c_string < TOPIC_STRING >::type;

      using suffix_type = typename base_const_c_string < SUFFIX_STRING >::type;

      static_assert(::std::same_as < topic_type, suffix_type >);

      auto suffix = (suffix_type)suffix_string;

      auto suffix_length = ::str::string_safe_length(suffix);

      if (suffix_length <= 0)
      {

         return true;

      }

      auto topic = (topic_type)topic_string;

      auto topic_length = ::str::string_safe_length(topic);

      if (topic_length < suffix_length)
      {

         return false;

      }

      auto end_index = (topic_length - suffix_length);

      auto end = topic + end_index;

      return !::str::string_n_compare_ci(end, suffix, suffix_length);

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


