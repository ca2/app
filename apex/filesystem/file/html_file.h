#pragma once


namespace html
{


   class CLASS_DECL_APEX file:
      virtual public ::object
#if defined(VARIADIC_TEMPLATE_FORMAT)
      ,public string_format_printer
#endif
   {
   public:


      string                              m_strOptions;
      string                              m_strStyle;
      __pointer(::text::context)      m_ptextcontext;


      file();
      virtual ~file();


      virtual const ::text::context * textcontext();

      virtual void print(const ::string & str);

      virtual void raw_print(const ::string & str);


#ifndef VARIADIC_TEMPLATE_FORMAT

      virtual void printf(string str,...);

      virtual void printstr(string str,...);

#else

      void trace(void *,const char * psz);


      inline void printf(const char *pszFmt) const
      {

         string_format format(this,&::html::file::trace,nullptr);

         format.format(pszFmt);

      }

      template<typename T,typename... Args>
      inline void printf(const char * pszFmt,const T & value,Args... args) const
      {

         string_format format(this,&::html::file::trace,nullptr);

         format.format(pszFmt,value,args...);

      }

#endif



      virtual void dprint(const char * pcsz);


   };


} // namespace html



