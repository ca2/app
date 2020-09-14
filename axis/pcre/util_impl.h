#pragma once


class pcre_util_impl :
   virtual public pcre_code_impl
{
public:


   __pointer(pcre_context_impl) m_pcre;


   pcre_util_impl(pcre_context_impl* m_pcreContext);
   virtual ~pcre_util_impl();


   bool compile(const string& str);


   virtual ::count matches(const string& str, pcre_context*);

   virtual ::count matches(const char* psz, strsize len, pcre_context*);

   virtual __pointer(::str::range_array) matches_ranges(const string& str) override;

   virtual __pointer(::str::range_array) matches_ranges(const char* psz, strsize len) override;


};



