#pragma once


class pcre_code_impl :
   virtual public pcre_code
{
public:


   pcre2_code* m_pc;

   pcre_context_impl* m_pcreContext;


   pcre_code_impl(pcre_context_impl* pcreContext);

   virtual ~pcre_code_impl();
   

   bool compile(const string& str);


   virtual bool matches(const string& str) override;

   virtual bool matches(const char* psz, strsize len) override;


   virtual ::count match_count(const string& str) override;

   virtual ::count match_count(const char* psz, strsize len) override;


   virtual __pointer(::str::range_array) matches_ranges(const string& str) override;


   virtual __pointer(::str::range_array) matches_ranges(const char* psz, strsize len) override;


   virtual bool replace(string& str, const string& strPrefix, string& strRet) override;


};



