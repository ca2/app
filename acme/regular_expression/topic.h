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


      virtual ::e_status create(const ::string & strExpression);


      virtual ::count get_count() const;

      
      virtual bool has_match() const;


      virtual string get_match(::index iMatch) const;


      virtual ::str::range_array & get_range_array();


      virtual void _get_range_array();


      //virtual bool matches(const char * psz, strsize len) = 0;

      //virtual ::count match_count(const ::string & str) = 0;

      //virtual ::count match_count(const char * psz, strsize len) = 0;

      //virtual __pointer(::str::range_array)

      //matches_ranges(const ::string & str) = 0;

      //virtual __pointer(::str::range_array)

      //matches_ranges(const char * psz, strsize len) = 0;

      //virtual bool replace(string & strFind, const ::string & strReplace, string & strResult);

      //virtual ::count matches(string_array & stra, const ::string & str);


   };


} // namespace regular_expression



