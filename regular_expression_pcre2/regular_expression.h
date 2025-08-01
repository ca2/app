#pragma once


#include "acme/regular_expression/regular_expression.h"


namespace regular_expression_pcre2
{


   class CLASS_DECL_REGULAR_EXPRESSION_PCRE2 regular_expression :
      virtual public ::regular_expression::regular_expression
   {
   public:


      pcre2_code *                  m_pcode;
      pcre2_general_context *       m_pgeneralcontext;


      regular_expression();
      ~regular_expression() override;


      void compile(const ::scoped_string & scopedstr) override;


      ::pointer<::regular_expression::result>run(const ::scoped_string & scopedstr) override;


      bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet) override;


   };


} // namespace regular_expression_pcre2



