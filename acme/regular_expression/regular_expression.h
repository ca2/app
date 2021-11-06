//
// Recreated by camilo on 2021-05-05 22:52 <3ThomasBS_!!
//
#pragma once


namespace regular_expression
{


   class CLASS_DECL_ACME regular_expression :
      virtual public matter
   {
   public:


      void *                     m_pRegularExpression;

      __pointer(context)         m_pcontext;

      string                     m_str;

      int                        m_iRangeCount;


      regular_expression();
      virtual ~regular_expression();


      virtual ::e_status create(const string& str);

      //virtual ::count calculate_range_count();

      virtual __pointer(topic) create_topic(const ::string & str);


      //virtual bool matches(const ::string & str) = 0;

//      virtual bool matches(const char * psz, strsize len) = 0;
//
//      virtual ::count match_count(const ::string & str) = 0;
//
//      virtual ::count match_count(const char * psz, strsize len) = 0;
//
//      virtual __pointer(::str::range_array)
//
//      matches_ranges(const ::string & str) = 0;
//
//      virtual __pointer(::str::range_array)
//
//      matches_ranges(const char * psz, strsize len) = 0;
//
//      virtual bool replace(string & str, const ::string & strPrefix, string & strRet) = 0;
//
//      virtual ::count matches(string_array & stra, const ::string & str);

      //virtual ::count match(string_array & stra, const string & pcsz, strsize iSize);

      //virtual int matches(const string& str, regex_context* pcreContext = nullptr) = 0;

      //virtual int matches(const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const string& str, regex_context* pcreContext = nullptr) = 0;

      //virtual void matches(strsize_array& ia, const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

      //virtual bool replace(string& str, const string& strPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;

      virtual bool replace(string & strFind, const ::string & strReplace, string & strResult);

   };


} // namespace regular_expression



