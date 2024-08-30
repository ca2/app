// From tracer.h by camilo on 2023-06-10 23:27 <3ThomasBorregaardSorensen!!
#pragma once


//#include "acme/primitive/primitive/pointer.h"
#include "acme/filesystem/file/string_stream.h"
#if defined(__STD_FORMAT)
#include <format>
#endif

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
   virtual public string_stream,
   virtual public trace_statement_struct
{
public:


   trace_statement(class tracer * ptracer);
   trace_statement(const trace_statement & tracestatement) = delete;
   trace_statement(trace_statement && tracestatement) :
      trace_statement_struct(::transfer(tracestatement)),
      string_stream(::transfer(tracestatement)),
      write_text_stream(::transfer(tracestatement)),
      write_text_stream_struct(::transfer(tracestatement))
   {
      tracestatement.m_ptracer = nullptr;
   }
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


   void formatf_output_arguments(const ::ansi_character * psz, va_list & arguments);

   #if defined(__STD_FORMAT__)
   
   template<typename... Ts>
   void format_output(const std::format_string<Ts...> fmt, Ts&&... args)
   {

      string str;

      str.format(fmt, ::std::forward < Ts >(args)...);

      operator << (str);

   }

   //trace_statement & operator()(const ::ansi_character * pszFormat, ...);

   template<typename... Ts>
   trace_statement & operator()(const std::format_string<Ts...> fmt, Ts&&... args)
   {

      return format_output(fmt, ::std::forward < Ts >(args)...);

   }
   #endif
   
   
   //void format_output_arguments(const ::ansi_character * psz, va_list & arguments)
//{

//   string str;

//   str.formatf_arguments(psz, arguments);

//   operator << (str);

//}


//tracer & format_output(const ::ansi_character * psz, ...)
//{

//   va_list arguments;

//   va_start(arguments, psz);

//   string str;

//   str.formatf_arguments(psz, arguments);

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



