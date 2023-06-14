// From tracer.h by camilo on 2023-06-10 23:27 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/pointer.h"
#include "acme/filesystem/file/string_stream.h"


class particle;

constexpr ::particle * trace_this() { return nullptr; }


struct trace_statement_struct
{

   class tracer *          m_ptracer;
   ::particle *            m_pparticleLogging = nullptr;
   enum_trace_level        m_etracelevel = e_trace_level_information;
   enum_trace_category     m_etracecategory = e_trace_category_general;
   const char *            m_pszFunction = nullptr;
   const char *            m_pszFile = nullptr;
   int                     m_iLine = -1;

   trace_statement_struct(class tracer * ptracer) : m_ptracer(ptracer) {}
   trace_statement_struct(trace_statement_struct && tracestatementstruct) = default;

};


class CLASS_DECL_ACME trace_statement :
   public trace_statement_struct,
   public string_stream
{
public:


   trace_statement(class tracer & tracer);
   trace_statement(const trace_statement & tracestatement) = delete;
   trace_statement(trace_statement && tracestatement) : trace_statement_struct(::transfer(tracestatement)), string_stream(::transfer(tracestatement)) { tracestatement.m_ptracer = nullptr; }
   ~trace_statement();


   //template < typename T >
   //inline auto & operator << (T && t){ return (*m_ptracer) << t; }

   inline trace_statement & operator()(::particle * pparticle) { m_pparticleLogging = pparticle; return *this; }
   inline trace_statement & operator()(enum_trace_level etracelevel) { m_etracelevel = etracelevel; return *this; }
   inline trace_statement & operator()(enum_trace_category etracecategory) { m_etracecategory = etracecategory; return *this; }
   inline trace_statement & operator()(const ::ansi_character * pszFunction, const ::ansi_character * pszFile, int iLine)
   {
      m_pszFunction = pszFunction;
      m_pszFile = pszFile;
      m_iLine = iLine;
      return *this;
   }


   void format_output_arguments(const ::ansi_character * psz, va_list & arguments);

   trace_statement & operator()(const ::ansi_character * pszFormat, ...);


   //void format_output_arguments(const ::ansi_character * psz, va_list & arguments)
//{

//   string str;

//   str.format_arguments(psz, arguments);

//   operator << (str);

//}


//tracer & format_output(const ::ansi_character * psz, ...)
//{

//   va_list arguments;

//   va_start(arguments, psz);

//   string str;

//   str.format_arguments(psz, arguments);

//   operator << (str);

//   va_end(arguments);

//   return *this;

//}


//template < typename STRINGABLE >
//tracer & operator <<(const STRINGABLE & stringable)
//{

//   string str;

//   ::copy(str, stringable);

//   m_str += str;

//   return *this;

//   //return operator << (str);

//}

};






CLASS_DECL_ACME::trace_statement log_statement();
//CLASS_DECL_ACME trace_statement trace_log_warning() << ;
//CLASS_DECL_ACME trace_statement trace_log_error() << ;
//CLASS_DECL_ACME trace_statement trace_log_fatal() << ;



