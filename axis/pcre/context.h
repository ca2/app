#pragma once

class pcre_context_impl;

class CLASS_DECL_AXIS pcre_context :
   virtual public ::regex_context
{
public:


   pcre_context_impl *      m_pimpl;


   pcre_context();
   virtual ~pcre_context();


   static __pointer(pcre_context) create_context(int iSizeData);

   virtual __pointer(regex) compile(const string& str);

protected:

   pcre_context(::layered * pobjectContext);

};





