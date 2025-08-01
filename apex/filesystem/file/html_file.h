#pragma once


////#include "acme/prototype/prototype/object.h"


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

   virtual void print(const ::scoped_string & scopedstr);

   virtual void raw_print(const ::scoped_string & scopedstr);


#ifndef VARIADIC_TEMPLATE_FORMAT

   virtual void printf(const_char_pointer pszFormat,...);

   virtual void printstr(const_char_pointer pszFormat,...);

#else

   void trace(void *,const ::scoped_string & scopedstr);


   inline void printf(const_char_pointer pszFmt) const
   {

      string_format format(this,&::html_file::trace,nullptr);

      format.format(scopedstrFmt);

   }

   template<typename T,typename... Args>
   inline void printf(const ::scoped_string & scopedstrFmt,const T & value,Args... args) const
   {

      string_format format(this,&::html_file::trace,nullptr);

      format.format(scopedstrFmt,value,args...);

   }

#endif



   virtual void dprint(const ::scoped_string & scopedstr);


};



