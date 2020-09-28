#pragma once


class CLASS_DECL_ACME regex :
   virtual public elemental
{
public:



   virtual bool matches(const string & str) = 0;

   virtual bool matches(const char * psz, strsize len) = 0;

   virtual ::count match_count(const string& str) = 0;

   virtual ::count match_count(const char* psz, strsize len) = 0;

   virtual __pointer(::str::range_array) matches_ranges(const string& str) = 0;

   virtual __pointer(::str::range_array) matches_ranges(const char* psz, strsize len) = 0;

   virtual bool replace(string& str, const string& strPrefix, string& strRet) = 0;

   virtual ::count matches(string_array & stra, const string & str);

   //virtual ::count match(string_array & stra, const string & pcsz, strsize iSize);

   //virtual int matches(const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual int matches(const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

   //virtual bool replace(string& str, const string& strPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;


};

class CLASS_DECL_ACME regex_context :
   virtual public ::elemental
{
public:

   virtual __pointer(regex) compile(const string& str) = 0;

};


using regex_pointer = __pointer(regex);



