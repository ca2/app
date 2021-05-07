//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#pragma once


namespace regular_expression
{


   class CLASS_DECL_ACME topic :
      virtual public matter
   {
   public:


      void *                           m_pResult;
      ::count                          m_cMatchData;
      string                           m_str;
      ::regular_expression_pointer     m_pregularexpression;
      ::str::range_array               m_rangea;


      topic();
      virtual ~topic();


      ::count get_count() const;

      string get_match(::index iMatch) const;


      virtual bool matches(const char * psz, strsize len) = 0;

      virtual ::count match_count(const string & str) = 0;

      virtual ::count match_count(const char * psz, strsize len) = 0;

      virtual __pointer(::str::range_array)

      matches_ranges(const string & str) = 0;

      virtual __pointer(::str::range_array)

      matches_ranges(const char * psz, strsize len) = 0;

      virtual bool replace(string & str, const string & strPrefix, string & strRet) = 0;

      virtual ::count matches(string_array & stra, const string & str);


   };


} // namespace regular_expression



