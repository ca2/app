#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 regular_expression :
      virtual public ::regular_expression::regular_expression
   {
   public:


      // thread-safe, exclusive write
      pcre2_code * m_pc;
      pcre_context_impl * m_pcreContext;


      regular_expression(pcre_context_impl * pcreContext);
      virtual ~regular_expression();


      bool compile(const string & str);


      virtual bool matches(const string & str) override;

      virtual bool matches(const char * psz, strsize len) override;


      virtual ::count match_count(const string & str) override;

      virtual ::count match_count(const char * psz, strsize len) override;


      virtual __pointer(::str::range_array) matches_ranges(const string & str) override;


      virtual __pointer(::str::range_array) matches_ranges(const char * psz, strsize len) override;


      virtual bool replace(string & str, const string & strPrefix, string & strRet) override;


   };


} // namespace regular_expression_pcre2



