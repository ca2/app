#pragma once


class CLASS_DECL_AXIS pcre_regex :
   virtual public ::regex
{
public:


   pcre_regex();
   virtual ~pcre_regex();

   static __pointer(regex) compile(const string& str);

   //virtual int matches(const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual int matches(const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const string& str, regex_context* pcreContext = nullptr) = 0;

   //virtual void matches(strsize_array& ia, const char* psz, strsize len, regex_context* pcreContext = nullptr) = 0;

   //virtual bool replace(string& str, const string& strPrefix, string& strRet, regex_context* pcreContext = nullptr) = 0;



/*   virtual int matches(const string& str) = 0;

   virtual int matches(const char* psz, strsize len) = 0;

   virtual int matches(strsize_array& ia, const string& str) = 0;

   virtual int matches(strsize_array& ia, const char* psz, strsize len) = 0;

   virtual bool replace(string& str, const string& strPrefix, string& strRet) = 0;*/

};


