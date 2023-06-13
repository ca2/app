//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "tracer.h"
#include "acme/platform/log.h"
#include "acme/platform/system.h"


tracer::tracer()
{

   m_plogger = nullptr;
   //m_pprintingformat = &m_printformatting;

}


tracer::~tracer()
{


}

//tracer & tracer::operator()(::particle * pparticle)
//{
//
//
//   m_pparticleLoggin = pparticle;
//
//   return *this;
//
//}
//
//
//tracer & tracer::operator()(::acme::context * pcontext, enum_trace_level etracelevel)
//{
//
//
//   m_pcontext = pcontext;
//   m_etracelevel = etracelevel;
//   m_etracecategory = e_trace_category_general;
//   m_pszFunction = nullptr;
//   m_pszFile = nullptr;
//   m_iLine = 0;
//
//
//   return *this;
//
//}
//
//
//tracer & tracer::operator()(::acme::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory)
//{
//
//
//   m_pcontext = pcontext;
//   m_etracelevel = etracelevel;
//   m_etracecategory = etracecategory;
//   m_pszFunction = nullptr;
//   m_pszFile = nullptr;
//   m_iLine = 0;
//
//
//   return *this;
//
//}
//
//
//tracer & tracer::operator()(::acme::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory, const ::ansi_character * pszFunction, const ::ansi_character * pszFile, int iLine, logger * plogger)
//{
//   
//   m_pcontext = pcontext;
//   m_etracelevel = etracelevel;
//   m_etracecategory = etracecategory;
//   m_pszFunction = pszFunction;
//   m_pszFile = pszFile;
//   m_iLine = iLine;
//   
//   if (plogger)
//   {
//
//      m_plogger = plogger;
//
//   }
//
//
//   return *this;
//
//   //auto ptask = ::get_task();
//
//   //if (!ptask)
//   //{
//
//   //   ptask = ::acme::acme::g_pacme->m_psubsystem->m_pacmesystem;
//
//   //}
//
//   //m_pprintformatting = ptask->m_pprintformatting;
//
//}



//CLASS_DECL_ACME void trace_log_information(const ::ansi_character * psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_pcontext, e_trace_level_information).format_output_arguments(psz, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_warning(const ::ansi_character * psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_pcontext, e_trace_level_warning).format_output_arguments(psz, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_error(const ::ansi_character * psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_pcontext, e_trace_level_error).format_output_arguments(psz, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_fatal(const ::ansi_character * psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_pcontext, e_trace_level_fatal).format_output_arguments(psz, arguments);
//
//   va_end(arguments);
//
//}


void tracer::flush(trace_statement & tracestatement)
{

   auto plogger = ::is_set(m_plogger) ? m_plogger : ::get_task()->acmesystem()->m_plogger;

   if (::is_set(plogger))
   {

      plogger->print(tracestatement);

   }

}

