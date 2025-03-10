#pragma once


class pcre_util_impl :
   virtual public pcre_code_impl
{
public:


   ::pointer<pcre_context_impl>m_pcre;


   pcre_util_impl(pcre_context_impl* m_pcreContext);
   virtual ~pcre_util_impl();


   bool compile(const string& str);


   virtual ::collection::count matches(const string& str, pcre_context*);

   virtual ::collection::count matches(const ::string & psz, character_count len, pcre_context*);

   virtual ::pointer<::strsize_range_array>matches_ranges(const string& str) override;

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::string & psz, character_count len) override;


};



