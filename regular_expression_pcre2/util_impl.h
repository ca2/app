#pragma once


class pcre_util_impl :
   virtual public pcre_code_impl
{
public:


   ::pointer<pcre_context_impl>m_pcre;


   pcre_util_impl(pcre_context_impl* m_pcreContext);
   virtual ~pcre_util_impl();


   bool compile(const ::scoped_string & scopedstr);


   virtual ::collection::count matches(const ::scoped_string & scopedstr, pcre_context*);

   virtual ::collection::count matches(const ::scoped_string & scopedstr, character_count len, pcre_context*);

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::scoped_string & scopedstr) override;

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::scoped_string & scopedstr, character_count len) override;


};



