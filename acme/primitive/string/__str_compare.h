

//   template < typename TYPE1, typename TYPE2 >
//   inline i32 compare(const TYPE1 & str1, const TYPE2 & str2);

//   template < typename TYPE1, typename TYPE2 >
//   inline i32 compare_ci(const TYPE1 & str1, const TYPE2 & str2);

//   template < typename TYPE1, typename TYPE2 >
//   inline bool equals(const TYPE1 & str1, const TYPE2 & str2);
//
//   template < typename TYPE1, typename TYPE2 >
//   inline bool equals_ci(const TYPE1 & str1, const TYPE2 & str2);

//   template < typename TYPE1, typename TYPE2 >
//   inline TYPE1 equals_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent = nullptr);

//   template < typename TYPE1, typename TYPE2 >
//   inline TYPE1 equals_ci_get(const TYPE1 & str1, const TYPE2 & str2, const TYPE1 & strOnEqual, const TYPE1 & strOnDifferent = nullptr);

//   template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
//   inline bool begins(const TOPIC_STRING & topic, const PREFIX_STRING & prefix);

//   template < const_c_string TOPIC_STRING, const_c_string PREFIX_STRING >
//   inline bool begins_ci(const TOPIC_STRING & topic, const PREFIX_STRING & prefix);

//   template < typename TYPE, typename FED, typename PREFIX >
//   inline bool begins(const TYPE & str, FED & strFed, const PREFIX & strPrefix);

//   template < typename TYPE, typename FED, typename PREFIX >
//   inline  bool begins_ci(const TYPE & str, FED & strFed, const PREFIX & strPrefix);

   // case insensitive, ignore white space - only in searched string
   bool begins_ci_iws(const ::string & str, const ::string & strPrefix);
   bool begins_ci_iws(const wstring & wstr, const wstring & wstrPrefix);

//   template < typename TYPE, typename PREFIX >
//   inline bool begins_eat(TYPE & str, const PREFIX & strPrefix);
//
//   template < typename TYPE, typename PREFIX >
//   inline bool begins_eat_ci(TYPE & str, const PREFIX & strPrefix);
//
//   template < typename PREFIX >
//   inline bool begins_eat(::payload & payload, const PREFIX& strPrefix);
//
//   template < typename PREFIX >
//   inline bool begins_eat_ci(::payload & payload, const PREFIX& strPrefix);
//
//   template < typename PREFIX >
//   inline bool begins_eat(property & property, const PREFIX& strPrefix);
//
//   template < typename PREFIX >
//   inline bool begins_eat_ci(property & property, const PREFIX& strPrefix);

//   inline bool begins_eat(::payload & payload, const ::string & strPrefix);
//
//   inline bool begins_eat_ci(::payload & payload, const ::string & strPrefix);
//
//   inline bool begins_eat(::property & property, const ::string & strPrefix);
//
//   inline bool begins_eat_ci(::property & property, const ::string & strPrefix);

   bool  while_begins_with_chars_eat(string & str, const char * pcszChars);
   bool  while_begins_with_chars_eat_ci(string & str, const char * pcszChars);

//   template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
//   inline bool ends(const TOPIC_STRING & topic, const SUFFIX_STRING & suffix);
//
//   template < const_c_string TOPIC_STRING, const_c_string SUFFIX_STRING >
//   inline bool ends_ci(const TOPIC_STRING & topic, const SUFFIX_STRING & suffix);
//
//   template < typename TYPE, typename SUFFIX >
//   inline bool ends_eat(TYPE & str, const SUFFIX & strSuffix);
//
//   template < typename TYPE, typename SUFFIX >
//   inline bool ends_eat_ci(TYPE & str, const SUFFIX & strSuffix);

//   bool eat_before(ansistring & strBefore, const ansistring & strSeparator, ansistring & str, bool bEatEverythingIfNotFound = false);
//   bool eat_before_let_separator(ansistring & strBefore, ansistring strSeparator, ansistring & str, bool bEatEverythingIfNotFound = false);
//
//   bool eat_before(widestring & wstrBefore, widestring wstrSeparator, widestring & wstr, bool bEatEverythingIfNotFound = false);
//   bool eat_before_let_separator(widestring & wstrBefore, widestring wstrSeparator, widestring & wstr, bool bEatEverythingIfNotFound = false);


   //template <  >
   //inline i32 compare(const ::string & str1, const ::string & str2);

   //template <  >
   //inline i32 compare_ci(const ::string & str1, const ::string & str2);

   //template < >
   //bool equals(const ::string & str1, const ::string & str2);

   //template < >
   //bool equals_ci(const ::string & str1, const ::string & str2);


   //template < >
   //string equals_get(const ::string & str1, const ::string & str2, const ::string &strGetOnEqual, const ::string & strGetOnDifferent);


   //template < >
   //string equals_ci_get(const ::string & str1, const ::string & str2, const ::string & strGetOnEqual, const ::string & strGetOnDifferent);


   //template < >
   //bool begins(const ::string & str, const ::string & strPrefix);


   //template < >
   //bool begins_with(const ::string & str, const ::string & strPrefix);

   //template < >
   //bool begins_ci(const ::string & str, const ::string & strPrefix);

   //template < >
   //bool begins_ci(const widestring & pcwsz, const widestring & pcwszPrefix);

