#pragma once

class pcre_context_impl;

class CLASS_DECL_APEX pcre_context :
   virtual public ::regex_context
{
public:


   pcre_context_impl *      m_pimpl;


   virtual ~pcre_context();


   static __pointer(pcre_context) create_context(::object * pobject, int iSizeData);

   virtual __pointer(regex) compile(const string& str);

protected:

   pcre_context(::layered * pobjectContext);

};


class CLASS_DECL_APEX pcre_regex :
   virtual public ::regex
{
public:


   pcre_regex(::object* pobject);
   virtual ~pcre_regex();

   static __pointer(regex) compile(::object * pobject, const string & str);

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


class CLASS_DECL_APEX pcre_code :
   virtual public pcre_regex
{
public:


   virtual ~pcre_code();

   static __pointer(pcre_code) compile(pcre_context * pcreContext, const string & str);

protected:

   pcre_code(::layered * pobjectContext);


};




