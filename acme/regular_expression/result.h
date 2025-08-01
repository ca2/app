//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#pragma once



//#include "acme/prototype/prototype/pointer.h"
//#include "acme/prototype/collection/string_array.h"


namespace regular_expression
{


   class CLASS_DECL_ACME result :
      virtual public particle
   {
   public:


      void *                           m_pResult;
      ::collection::count                          m_cMatchData;
      string                           m_str;
      ::regular_expression_pointer     m_pregularexpression;
      ::strsize_range_array               m_rangea;


      result();
      ~result() override;


      //virtual void compile(const ::scoped_string & scopedstrExpression);


      virtual ::collection::count get_count() const;

      
      virtual bool has_match() const;


      virtual string get_match(::collection::index iMatch) const;


      virtual ::strsize_range_array & get_range_array();


      virtual void _get_range_array();


      //virtual bool matches(const ::scoped_string & scopedstr, character_count len) = 0;

      //virtual ::collection::count match_count(const ::scoped_string & scopedstr) = 0;

      //virtual ::collection::count match_count(const ::scoped_string & scopedstr, character_count len) = 0;

      //virtual ::pointer<::strsize_range_array>

      //matches_ranges(const ::scoped_string & scopedstr) = 0;

      //virtual ::pointer<::strsize_range_array>

      //matches_ranges(const ::scoped_string & scopedstr, character_count len) = 0;

      //virtual bool replace(string & strFind, const ::scoped_string & scopedstrReplace, string & strResult);

      //virtual ::collection::count matches(string_array & stra, const ::scoped_string & scopedstr);


   };


} // namespace regular_expression



