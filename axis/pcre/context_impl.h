#pragma once


class pcre_context_impl :
   virtual public pcre_context
{
public:


   pcre2_general_context* m_pgc;
   pcre2_compile_context* m_pcc;
   pcre2_match_data* m_pmd;
   int                     m_iSizeData;


   pcre_context_impl(int iSizeData);


   virtual ~pcre_context_impl();

};






