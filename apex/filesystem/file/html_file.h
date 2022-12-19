#pragma once


////#include "acme/primitive/primitive/object.h"


class CLASS_DECL_APEX html_file:
   virtual public ::object
#if defined(VARIADIC_TEMPLATE_FORMAT)
   ,public string_format_printer
#endif
{
public:


   string                              m_strOptions;
   string                              m_strStyle;
   ::pointer<::text::context>     m_ptextcontext;


   html_file();
   ~html_file() override;


   virtual const ::text::context * textcontext();

   virtual void print(const ::string & str);

   virtual void raw_print(const ::string & str);


#ifndef VARIADIC_TEMPLATE_FORMAT

   virtual void printf(string str,...);

   virtual void printstr(string str,...);

#else

   void trace(void *,const scoped_string & str);


   inline void printf(const char *pszFmt) const
   {

      string_format format(this,&::html_file::trace,nullptr);

      format.format(pszFmt);

   }

   template<typename T,typename... Args>
   inline void printf(const scoped_string & strFmt,const T & value,Args... args) const
   {

      string_format format(this,&::html_file::trace,nullptr);

      format.format(pszFmt,value,args...);

   }

#endif



   virtual void dprint(const char * pcsz);


};



