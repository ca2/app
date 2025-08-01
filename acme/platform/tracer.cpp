//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "tracer.h"
#include "acme/platform/log.h"
#include "acme/platform/system.h"


tracer::tracer()
{

   //m_plogger = nullptr;
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
//tracer & tracer::operator()(::platform::context * pcontext, enum_trace_level etracelevel)
//{
//
//
//   m_papplication = pcontext;
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
//tracer & tracer::operator()(::platform::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory)
//{
//
//
//   m_papplication = pcontext;
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
//tracer & tracer::operator()(::platform::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory, const_char_pointer pszFunction, const_char_pointer pszFile, int iLine, logger * plogger)
//{
//   
//   m_papplication = pcontext;
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
//   //   ptask = this->::system()->m_psystem;
//
//   //}
//
//   //m_pprintformatting = ptask->m_pprintformatting;
//
//}



//CLASS_DECL_ACME void trace_log_information(const_char_pointer psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_papplication, e_trace_level_information).format_output_arguments(scopedstr, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_warning(const_char_pointer psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_papplication, e_trace_level_warning).format_output_arguments(scopedstr, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_error(const_char_pointer psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_papplication, e_trace_level_error).format_output_arguments(scopedstr, arguments);
//
//   va_end(arguments);
//
//}
//
//
//CLASS_DECL_ACME void trace_log_fatal(const_char_pointer psz, ...)
//{
//
//   va_list arguments;
//
//   va_start(arguments, psz);
//
//   get_tracer()(::get_task()->m_papplication, e_trace_level_fatal).format_output_arguments(scopedstr, arguments);
//
//   va_end(arguments);
//
//}


void tracer::flush(trace_statement & tracestatement)
{

   ::logger * plogger = nullptr;

   if(::is_set(m_plogger))
   {

      plogger = m_plogger;

   }
   else
   {

      auto ptask = ::get_task();

      if (ptask && ptask->m_plogger)
      {

         plogger = ptask->m_plogger;

      }

      if(!plogger)
      {

         plogger = system()->m_plogger;

      }

   }

   if (::is_set(plogger))
   {

      plogger->print(tracestatement, true);

   }
   else
   {

      if (tracestatement.m_etracelevel >= system()->m_etracelevelMinimum)
      {

         ::output_debug_string("OutDebStr:"+ tracestatement.as_string() + "\n");

         ::output_debug_string_flush();

      }

   }

}




class tracer * fallback_tracer()
{

   static class tracer s_tracerFallback;

   return &s_tracerFallback;

}
