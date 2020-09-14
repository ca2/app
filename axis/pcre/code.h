#pragma once


class CLASS_DECL_AXIS pcre_code :
   virtual public pcre_regex
{
public:

   virtual ~pcre_code();

   static __pointer(pcre_code) compile(pcre_context* pcreContext, const string& str);

protected:

   pcre_code();


};


