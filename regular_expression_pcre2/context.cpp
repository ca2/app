#include "framework.h"


namespace regular_expression_pcre2
{


   context::context()
   {

      m_pContext = this;

      m_pgeneralcontext = pcre2_general_context_create(nullptr, nullptr, nullptr);

      m_pcompilecontext = pcre2_compile_context_create(m_pgeneralcontext);

   }


   context::~context()
   {

      if (m_pcompilecontext != nullptr)
      {

         pcre2_compile_context_free(m_pcompilecontext);

         m_pcompilecontext = nullptr;

      }

      if (m_pgeneralcontext != nullptr)
      {

         pcre2_general_context_free(m_pgeneralcontext);

         m_pgeneralcontext = nullptr;

      }

   }


   ::regular_expression_pointer context::compile(const ::string & str)
   {

      auto pregularexpression = __new(regular_expression);

      pregularexpression->m_pcontext = this;

      //auto estatus = 
      
      pregularexpression->create(str);

      //if(!estatus)
      //{

      //   return nullptr;

      //}

      return pregularexpression;

   }


} // namespace regular_expression_pcre2



