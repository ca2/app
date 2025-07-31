//
// Created by camilo on 2021-05-07 07:24 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/regular_expression/result.h"


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 result :
      virtual public ::regular_expression::result
   {
   public:


      pcre2_match_data *         m_pmatchdata;
      ::collection::count                    m_cMatchCount;


      result();
      ~result() override;


      ::collection::count get_count() const override;

      string get_match(::collection::index i) const override;

      void _get_range_array() override;

      //virtual bool replace(string & strFind, const ::scoped_string & scopedstrReplace, string & strResult) override;


   };


}  // namespace regular_expression_pcre2



