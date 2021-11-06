#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 regular_expression :
      virtual public ::regular_expression::regular_expression
   {
   public:


      // thread-safe, exclusive write
      pcre2_code *               m_pcode;
      //pcre_context_impl *        m_pcreContext;


      regular_expression();
      virtual ~regular_expression();


      ::e_status create(const string& str) override;


      __pointer(::regular_expression::topic) create_topic(const ::string & str) override;


      bool replace(string& str, const string& strPrefix, string& strRet) override;


   };


} // namespace regular_expression_pcre2



