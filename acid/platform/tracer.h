// Created by Camilo on 2021-10-04 12:06 BRT <3ThomasBorregaardSorensen!!
#pragma once

//
//#include "acid/filesystem/file/text_stream.h"
//
//
//
#include "acid/filesystem/file/print_formatting.h"


class logger;


class CLASS_DECL_ACID tracer :
   public print_formatting
{
public:


   //::acid::context *           m_pcontext;
   ::pointer < ::logger >          m_plogger;


   tracer();
   ~tracer();


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

   //tracer & operator << (const exception & exception);
   //tracer & operator << (const e_status & estatus);
   //tracer & operator << (const enum_status& estatus);
   //tracer & operator << (const ansi_string & str);
   //tracer & operator << (const ::ansi_character * psz);
//   tracer & operator << (enum_flush);
//   tracer & operator << (const integral_byte & memsize);
//
//   tracer & operator << (const integral_nanosecond & time) { return format(time); }
//   tracer & operator << (const integral_microsecond & time) { return format(time); }
//   tracer & operator << (const integral_millisecond & time) { return format(time); }
//   tracer & operator << (const integral_second & time) { return format(time); }
//   tracer & operator << (const integral_minute & time) { return format(time); }
//   tracer & operator << (const integral_hour & time) { return format(time); }
//   tracer & operator << (const integral_day & time) { return format(time); }
//
////   tracer & operator << (const floating_nanosecond & time) { return format(time); }
////   tracer & operator << (const floating_microsecond & time) { return format(time); }
////   tracer & operator << (const floating_millisecond & time) { return format(time); }
////   tracer & operator << (const floating_second & time) { return format(time); }
////   tracer & operator << (const floating_minute & time) { return format(time); }
////   tracer & operator << (const floating_hour & time) { return format(time); }
////   tracer & operator << (const floating_day & time) { return format(time); }
//   
//   template < primitive_integral INTEGRAL >
//   tracer & operator << (const INTEGRAL integral) { return operator << (::as_string(integral)); }
//
//
   virtual void flush(trace_statement & tracestatement);


};


//CLASS_DECL_ACID void trace_log_information() << const ::ansi_character * psz, ...;
//CLASS_DECL_ACID void trace_log_warning() << const ::ansi_character * psz, ...;
//CLASS_DECL_ACID void trace_log_error() << const ::ansi_character * psz, ...;
//CLASS_DECL_ACID void trace_log_fatal() << const ::ansi_character * psz, ...;

//
//CLASS_DECL_ACID ::trace_statement log_statement();
////CLASS_DECL_ACID trace_statement trace_log_warning() << ;
////CLASS_DECL_ACID trace_statement trace_log_error() << ;
////CLASS_DECL_ACID trace_statement trace_log_fatal() << ;
//
//
//
