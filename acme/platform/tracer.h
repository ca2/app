// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/file/text_stream.h"
#include "acme/primitive/string/string.h"


class logger;


class CLASS_DECL_ACME tracer :
   public string_stream
{
public:


   ::acme::context *          m_pcontext;
   enum_trace_level           m_etracelevel;
   enum_trace_category        m_etracecategory;
   const char *               m_pszFunction;
   const char *               m_pszFile;
   int                        m_iLine;
   logger *                   m_plogger;


   tracer(::acme::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory = e_trace_category_general, const char * pszFunction = nullptr, const char * pszFile = nullptr, int iLine = -1, logger * plogger = nullptr) :
      m_pcontext(pcontext),
      m_etracelevel(etracelevel),
      m_etracecategory(etracecategory),
      m_pszFunction(pszFunction),
      m_pszFile(pszFile),
      m_iLine(iLine),
      m_plogger(plogger)
   {

   }


   ~tracer()
   {

      flush();

   }


   void format_output_arguments(const char * psz, va_list & arguments)
   {

      string str;

      str.format_arguments(psz, arguments);

      operator << (str);

   }


   tracer & format_output(const char * psz, ...)
   {

      va_list arguments;

      va_start(arguments, psz);

      string str;

      str.format_arguments(psz, arguments);

      operator << (str);

      va_end(arguments);

      return *this;

   }


   //template < typename STRINGABLE >
   //tracer & operator <<(const STRINGABLE & stringable)
   //{

   //   string str;

   //   ::copy(str, stringable);

   //   m_str += str;

   //   return *this;

   //   //return operator << (str);

   //}

   //tracer & operator << (const exception & exception);
   //tracer & operator << (const e_status & estatus);
   //tracer & operator << (const enum_status& estatus);
   //tracer & operator << (const ansistring & str);
   //tracer & operator << (const char * psz);
//   tracer & operator << (enum_flush);
//   tracer & operator << (const integral_byte & memsize);
//
//   tracer & operator << (const INTEGRAL_NANOSECOND & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_MICROSECOND & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_MILLISECOND & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_SECOND & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_MINUTE & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_HOUR & time) { return format(time); }
//   tracer & operator << (const INTEGRAL_DAY & time) { return format(time); }
//
////   tracer & operator << (const FLOATING_NANOSECOND & time) { return format(time); }
////   tracer & operator << (const FLOATING_MICROSECOND & time) { return format(time); }
////   tracer & operator << (const FLOATING_MILLISECOND & time) { return format(time); }
////   tracer & operator << (const FLOATING_SECOND & time) { return format(time); }
////   tracer & operator << (const FLOATING_MINUTE & time) { return format(time); }
////   tracer & operator << (const FLOATING_HOUR & time) { return format(time); }
////   tracer & operator << (const FLOATING_DAY & time) { return format(time); }
//   
//   template < primitive_integral INTEGRAL >
//   tracer & operator << (const INTEGRAL integral) { return operator << (::as_string(integral)); }
//
//
   void flush();


};


CLASS_DECL_ACME void trace_log_information(const char * psz, ...);
CLASS_DECL_ACME void trace_log_warning(const char * psz, ...);
CLASS_DECL_ACME void trace_log_error(const char * psz, ...);
CLASS_DECL_ACME void trace_log_fatal(const char * psz, ...);


CLASS_DECL_ACME tracer trace_log_information();
CLASS_DECL_ACME tracer trace_log_warning();
CLASS_DECL_ACME tracer trace_log_error();
CLASS_DECL_ACME tracer trace_log_fatal();



