#pragma once


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 context :
      virtual public ::regular_expression::context
   {
   public:


      // shared between pcre_code objects
      // thread-safe, exclusive write
      pcre2_general_context *    m_pgeneralcontext;
      // shared between pcre_code objects
      // thread-safe, exclusive write
      pcre2_compile_context *    m_pcompilecontext;


      context();
      virtual ~context();


      virtual ::regular_expression_pointer compile(const ::string & str) override;


   };


} // namespace regular_expression_pcre2



