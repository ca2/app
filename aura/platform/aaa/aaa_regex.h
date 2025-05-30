#pragma once


class CLASS_DECL_AURA regex :
   virtual public object
{
public:



   virtual bool matches(const ::string & str) = 0;

   virtual bool matches(const ::string & psz, character_count len) = 0;

   virtual ::collection::count match_count(const string& str) = 0;

   virtual ::collection::count match_count(const ::string & psz, character_count len) = 0;

   virtual ::pointer<::strsize_range_array>matches_ranges(const string& str) = 0;

   virtual ::pointer<::strsize_range_array>matches_ranges(const ::string & psz, character_count len) = 0;

   virtual bool replace(string& str, const string& strPrefix, string& strRet) = 0;

   virtual ::collection::count matches(string_array & stra, const ::string & str);

   //virtual ::collection::count match(string_array & stra, const string & pcsz, character_count iSize);

   //virtual int matches(const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual int matches(const ::string & psz, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const ::string & psz, character_count len, regex_context* pcreContext = nullptr) = 0;

   //virtual bool replace(string& str, const string& strPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;


};

class CLASS_DECL_AURA regex_context :
   virtual public ::object
{
public:

   virtual ::pointer<regex>compile(const string& str) = 0;

};


using regex_pointer = ::pointer<regex>



