//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
//#include "tracer.h"
#include "acme/platform/log.h"
#include "acme/platform/system.h"


CLASS_DECL_ACME void trace_log_information(const ::ansi_character * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_task()->m_pcontext, e_trace_level_information).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_warning(const ::ansi_character * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_task()->m_pcontext, e_trace_level_warning).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_error(const ::ansi_character * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_task()->m_pcontext, e_trace_level_error).format_output_arguments(psz, arguments);

   va_end(arguments);

}


CLASS_DECL_ACME void trace_log_fatal(const ::ansi_character * psz, ...)
{

   va_list arguments;

   va_start(arguments, psz);

   tracer(::get_task()->m_pcontext, e_trace_level_fatal).format_output_arguments(psz, arguments);

   va_end(arguments);

}


void tracer::flush()
{

   auto plogger = ::is_set(m_plogger) ? m_plogger : ::get_task()->acmesystem()->m_plogger.get();

   if (::is_set(plogger))
   {

      plogger->print(m_etracelevel, m_etracecategory, m_pszFunction, m_pszFile, m_iLine, as_string());

   }

}

