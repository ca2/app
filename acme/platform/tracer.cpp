//
// Created by camilo on 30/10/2021 23:50 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "tracer.h"
#include "std_trace_output.h"
#include <mutex>

// Shutdown can still emit traces from other translation units' destructors.
// Keep the lock alive until process exit, independent of static destruction order.
static std::recursive_mutex &tracer_flush_mutex()
{
   static auto *mutex = new std::recursive_mutex;
   return *mutex;
}
#if defined(WINDOWS)
static bool g_standardTraceFileEnabled = CA2_TRACE_TO_FILE != 0;
static wchar_t g_standardTracePath[32768] = {};
static char g_applicationBuildTimestamp[128] = "Application build timestamp: unavailable (not registered by entry point).";

// Access is serialized by tracer_flush_mutex(), including path changes and disable.
struct standard_trace_file
{
   HANDLE handle = INVALID_HANDLE_VALUE;
   wchar_t path[32768] = {};

   void close()
   {
      const DWORD savedError = GetLastError();
      const HANDLE closingHandle = handle;
      handle = INVALID_HANDLE_VALUE;
      if (closingHandle != INVALID_HANDLE_VALUE && closingHandle != nullptr)
         CloseHandle(closingHandle);
      path[0] = L'\0';
      SetLastError(savedError);
   }

};

static standard_trace_file &standard_trace_file_state()
{
   // Late shutdown traces must not access an already-destroyed file object.
   // Disable/path changes close it explicitly; Windows reclaims it at process exit.
   static auto *file = new standard_trace_file;
   return *file;
}

void ca2_write_standard_trace_file(const char *text, const wchar_t *path)
{
   const int savedErrno = errno;
   const DWORD savedError = GetLastError();
   {
      std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());
      if (g_standardTraceFileEnabled && text && path && *path
         && wcslen(path) < sizeof(standard_trace_file_state().path) / sizeof(wchar_t))
      {
         if (wcscmp(path, standard_trace_file_state().path) != 0)
            standard_trace_file_state().close();

         if (standard_trace_file_state().handle == INVALID_HANDLE_VALUE)
         {
            standard_trace_file_state().handle = CreateFileW(path, FILE_APPEND_DATA,
               FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr, OPEN_ALWAYS,
               FILE_ATTRIBUTE_NORMAL, nullptr);
            if (standard_trace_file_state().handle != INVALID_HANDLE_VALUE)
               wcscpy(standard_trace_file_state().path, path);
         }

         if (standard_trace_file_state().handle != INVALID_HANDLE_VALUE)
         {
            size_t left = strlen(text);
            const char *cursor = text;
            bool complete = true;
            while (left)
            {
               DWORD written = 0;
               const DWORD chunk = left > 65536 ? 65536 : (DWORD)left;
               if (!WriteFile(standard_trace_file_state().handle, cursor, chunk, &written, nullptr)
                  || !written)
               {
                  complete = false;
                  break;
               }
               cursor += written;
               left -= written;
            }
            DWORD written = 0;
            if (complete)
               complete = WriteFile(standard_trace_file_state().handle, "\r\n", 2, &written, nullptr)
                  && written == 2;
            // Keep crash diagnostics durable. Only handle acquisition is cached.
            if (!FlushFileBuffers(standard_trace_file_state().handle) || !complete)
               standard_trace_file_state().close(); // Allow a later statement to retry opening.
         }
      }
   }
   SetLastError(savedError);
   errno = savedErrno;
}

void ca2_set_application_build_timestamp(const char *timestamp)
{
   std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());
   if (timestamp && *timestamp)
      snprintf(g_applicationBuildTimestamp, sizeof(g_applicationBuildTimestamp),
         "Application built: %s (compiler local time)", timestamp);
}

void ca2_enable_standard_trace_file(bool enable)
{
   std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());
   g_standardTraceFileEnabled = enable;
   if (!enable)
      standard_trace_file_state().close();
}

bool ca2_standard_trace_file_enabled()
{
   std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());
   return g_standardTraceFileEnabled;
}

bool ca2_set_standard_trace_path(const wchar_t *path)
{
   std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());
   if (!path || wcslen(path) >= sizeof(g_standardTracePath) / sizeof(wchar_t))
      return false;
   if (wcscmp(path, g_standardTracePath) != 0)
      standard_trace_file_state().close();
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

      std::lock_guard<std::recursive_mutex> lock(tracer_flush_mutex());

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


