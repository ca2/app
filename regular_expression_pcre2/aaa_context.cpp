#include "framework.h"


namespace regular_expression_pcre2
{


   context::context()
   {

   }


   context::~context()
   {

   }


   ::regular_expression_pointer context::compile(const ::string & str)
   {

      return pcre_code::compile(this, str);

   }


} // namespace regular_expression_pcre2



