// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardSørensen!!
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


   tracer & format_output(const char * psz, ...)
   {

      va_list arguments;

      va_start(arguments, psz);

      string str;

      str.FormatV(psz, arguments);

      operator << (str);

      va_end(arguments);

      return *this;

   }


   template < typename STRINGABLE >
   tracer & format_from_string(const STRINGABLE & stringable)
   {

      string str;

      to_string(str, stringable);

      return operator << (str);

   }


   tracer & operator << (const string & str);
   tracer & operator << (enum_flush);
   tracer & operator << (const integral_byte & memsize);
   template < typename STRINGABLE >
   tracer & operator << (const STRINGABLE & stringable) { return format_from_string(stringable); }


   template < primitive_integral INTEGRAL >
   tracer & operator << (const INTEGRAL integral) { return operator << (::__string(integral)); }


   void flush();


};


inline tracer trace_log_information();
inline tracer trace_log_warning();
inline tracer trace_log_error();
inline tracer trace_log_fatal();



