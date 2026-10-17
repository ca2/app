//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "tracer.h"
#include "std_trace_output.h"
#include <mutex>

static std::recursive_mutex g_tracerFlushMutex;
#if defined(WINDOWS)
static bool g_standardTraceFileEnabled = CA2_TRACE_TO_FILE != 0;
static wchar_t g_standardTracePath[32768] = {};
static char g_applicationBuildTimestamp[128] = "Application build timestamp: unavailable (not registered by entry point).";

void ca2_set_application_build_timestamp(const char *timestamp)
{
   std::lock_guard<std::recursive_mutex> lock(g_tracerFlushMutex);
   if (timestamp && *timestamp)
      snprintf(g_applicationBuildTimestamp, sizeof(g_applicationBuildTimestamp),
         "Application built: %s (compiler local time)", timestamp);
}

void ca2_enable_standard_trace_file(bool enable)
{
   std::lock_guard<std::recursive_mutex> lock(g_tracerFlushMutex);
   g_standardTraceFileEnabled = enable;
}

bool ca2_standard_trace_file_enabled()
{
   std::lock_guard<std::recursive_mutex> lock(g_tracerFlushMutex);
   return g_standardTraceFileEnabled;
}

bool ca2_set_standard_trace_path(const wchar_t *path)
{
   std::lock_guard<std::recursive_mutex> lock(g_tracerFlushMutex);
   if (!path || wcslen(path) >= sizeof(g_standardTracePath) / sizeof(wchar_t))
      return false;
   wcscpy(g_standardTracePath, path);
   // Write the header under the same lock as trace flushing, before any log records.
   if (g_standardTraceFileEnabled && *path)
      ca2_write_standard_trace(g_applicationBuildTimestamp, false, g_standardTracePath);
   return true;
}
#endif
#include "acme/platform/log.h"
#include "acme/platform/system.h"

namespace platform
{


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
   //tracer & tracer::operator()(::platform::context * pcontext, enum_trace_level etracelevel, enum_trace_category etracecategory, const_char_pointer pszFunction, const_char_pointer pszFile, ::i32 iLine, logger * plogger)
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



   ::string tracer::trace_prefix() const
   {

      ::string strTaskName = ::current_task_name();

      return strTaskName;

   }


   void tracer::flush(trace_statement & tracestatement)
   {

      std::lock_guard<std::recursive_mutex> lock(g_tracerFlushMutex);

#if defined(WINDOWS) || CA2_STD_TRACE || CA2_TRACE_TO_FILE
      // Severity increases as the numeric trace level decreases.
      const bool errorStream = tracestatement.m_etracelevel >= e_trace_level_fatal
         && tracestatement.m_etracelevel <= e_trace_level_warning;
#if defined(WINDOWS)
      ca2_write_standard_trace(tracestatement.as_string().c_str(), errorStream,
         g_standardTraceFileEnabled ? g_standardTracePath : nullptr);
#else
      ca2_write_standard_trace(tracestatement.as_string().c_str(), errorStream);
#endif
#endif

      ::platform::logger * plogger = nullptr;

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

            plogger = ::system()->m_plogger;

         }

      }

      if (::is_set(plogger))
      {

         plogger->print(tracestatement, true);

      }
      else
      {

         if (tracestatement.m_etracelevel <= ::system()->m_etracelevelMinimum)
         {

            ::output_debug_string("output_debug_string: "+ tracestatement.as_string() + "\n");

            ::output_debug_string_flush();

         }

      }

   }


   ::platform::tracer * fallback_tracer()
   {

      static ::platform::tracer s_tracerFallback;

      return &s_tracerFallback;

   }


} // namespace platform


