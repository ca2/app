#pragma once


class CLASS_DECL_AURA regex :
   virtual public object
{
public:



   virtual bool matches(const ::scoped_string & scopedstr) = 0;

   virtual bool matches(const ::scoped_string & scopedstr, character_count len) = 0;

   virtual ::collection::count match_count(const ::scoped_string & scopedstr) = 0;

   virtual ::collection::count match_count(const ::scoped_string & scopedstr, character_count len) = 0;

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::scoped_string & scopedstr) = 0;

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::scoped_string & scopedstr, character_count len) = 0;

   virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet) = 0;

   virtual ::collection::count matches(string_array & stra, const ::scoped_string & scopedstr);

   //virtual ::collection::count match(string_array & stra, const string & pcsz, character_count iSize);

   //virtual int matches(const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

   //virtual int matches(const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const ::scoped_string & scopedstr, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual bool replace(string& str, const ::scoped_string & scopedstrPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;


};

class CLASS_DECL_AURA regex_context :
   virtual public ::object
{
public:

   virtual ::pointer<regex>compile(const ::scoped_string & scopedstr) = 0;

};


using regex_pointer = ::pointer<regex>



