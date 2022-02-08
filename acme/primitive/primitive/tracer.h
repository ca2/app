// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardS�rensen!!
#pragma once


class logger;


class CLASS_DECL_ACME tracer
{
public:


   class ::system *           m_psystem;
   string                     m_str;
   enum_trace_level           m_etracelevel;
   enum_trace_category        m_etracecategory;
   const char *               m_pszFunction;
   const char *               m_pszFile;
   int                        m_iLine;
   logger *                   m_plogger;


   tracer(class ::system * psystem, enum_trace_level etracelevel, enum_trace_category etracecategory = e_trace_category_general, const char * pszFunction = nullptr, const char * pszFile = nullptr, int iLine = -1, logger * plogger = nullptr) :
      m_psystem(psystem),
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


   template < typename STRINGABLE >
   tracer & format(const STRINGABLE & stringable)
   {

      string str;

      to_string(str, stringable);

      return operator << (str);

   }

   tracer & operator << (const exception & exception);
   tracer & operator << (const e_status & estatus);
   tracer & operator << (const enum_status& estatus);
   tracer & operator << (const string & str);
   tracer & operator << (const char * psz);
   tracer & operator << (enum_flush);
   tracer & operator << (const integral_byte & memsize);

   tracer & operator << (const INTEGRAL_NANOSECOND & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_MICROSECOND & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_MILLISECOND & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_SECOND & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_MINUTE & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_HOUR & duration) { return format(duration); }
   tracer & operator << (const INTEGRAL_DAY & duration) { return format(duration); }

//   tracer & operator << (const FLOATING_NANOSECOND & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_MICROSECOND & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_MILLISECOND & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_SECOND & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_MINUTE & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_HOUR & duration) { return format(duration); }
//   tracer & operator << (const FLOATING_DAY & duration) { return format(duration); }
   
   template < primitive_integral INTEGRAL >
   tracer & operator << (const INTEGRAL integral) { return operator << (::__string(integral)); }


   void flush();


};


CLASS_DECL_ACME void trace_log_information(const char * psz, ...);
CLASS_DECL_ACME void trace_log_warning(const char * psz, ...);
CLASS_DECL_ACME void trace_log_error(const char * psz, ...);
CLASS_DECL_ACME void trace_log_fatal(const char * psz, ...);


inline tracer trace_log_information();
inline tracer trace_log_warning();
inline tracer trace_log_error();
inline tracer trace_log_fatal();



