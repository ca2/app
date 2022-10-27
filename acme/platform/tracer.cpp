//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "tracer.h"
#include "acme/platform/system.h"


CLASS_DECL_ACME void trace_log_information(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_system(), e_trace_level_information).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_warning(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_system(), e_trace_level_warning).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_error(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_system(), e_trace_level_error).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_fatal(const char * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_system(), e_trace_level_fatal).format_output_arguments(psz, arguments);

   va_end(arguments);

}



