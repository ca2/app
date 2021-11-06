//
// Created by camilo on 2021-05-07 07:24 BRT <3ThomasBS_!!
//
#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 topic :
      virtual public ::regular_expression::topic
   {
   public:


      // thread specific
      pcre2_match_data *         m_pmatchdata;
      ::count                    m_cMatchCount;


      topic();
      virtual ~topic();

      ::e_status create(const ::string & str) override;


      ::count get_count() const override;

      string get_match(::index i) const override;

      void _get_range_array() override;

      //virtual bool replace(string & strFind, const ::string & strReplace, string & strResult) override;


   };


}  // namespace regular_expression_pcre2



