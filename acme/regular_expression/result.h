//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"
//#include "acme/primitive/collection/string_array.h"


namespace regular_expression
{


   class CLASS_DECL_ACME result :
      virtual public particle
   {
   public:


      void *                           m_pResult;
      ::count                          m_cMatchData;
      string                           m_str;
      ::regular_expression_pointer     m_pregularexpression;
      ::strsize_range_array               m_rangea;


      result();
      ~result() override;


      //virtual void compile(const ::string & strExpression);


      virtual ::count get_count() const;

      
      virtual bool has_match() const;


      virtual string get_match(::index iMatch) const;


      virtual ::strsize_range_array & get_range_array();


      virtual void _get_range_array();


      //virtual bool matches(const char * psz, strsize len) = 0;

      //virtual ::count match_count(const ::string & str) = 0;

      //virtual ::count match_count(const char * psz, strsize len) = 0;

      //virtual ::pointer<::strsize_range_array>

      //matches_ranges(const ::string & str) = 0;

      //virtual ::pointer<::strsize_range_array>

      //matches_ranges(const char * psz, strsize len) = 0;

      //virtual bool replace(string & strFind, const ::string & strReplace, string & strResult);

      //virtual ::count matches(string_array & stra, const ::string & str);


   };


} // namespace regular_expression



