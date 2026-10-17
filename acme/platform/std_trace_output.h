#pragma once
#ifndef CA2_STD_TRACE
#if defined(_DEBUG)
#define CA2_STD_TRACE 1
#else
#define CA2_STD_TRACE 0
#endif
#endif
#ifndef CA2_TRACE_TO_FILE
#if defined(_DEBUG)
#define CA2_TRACE_TO_FILE 1
#else
#define CA2_TRACE_TO_FILE 0
#endif
#endif
#if defined(WINDOWS)
#include "acme/_operating_system.h"
CLASS_DECL_ACME void ca2_set_application_build_timestamp(const char *timestamp);
CLASS_DECL_ACME void ca2_enable_standard_trace_file(bool enable);
CLASS_DECL_ACME bool ca2_standard_trace_file_enabled();
CLASS_DECL_ACME bool ca2_set_standard_trace_path(const wchar_t *path);
#endif
#if defined(WINDOWS) || CA2_STD_TRACE || CA2_TRACE_TO_FILE
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
inline void ca2_write_standard_trace(const char *text, bool errorStream = true,
   const wchar_t *tracePath = nullptr)
{
   if (!text)
      return;
   int savedErrno = errno;
#if defined(WINDOWS)
   DWORD savedError = GetLastError();
#if CA2_STD_TRACE
   HANDLE output = GetStdHandle(errorStream ? STD_ERROR_HANDLE : STD_OUTPUT_HANDLE);
   if (!output || output == INVALID_HANDLE_VALUE)
      output = GetStdHandle(errorStream ? STD_OUTPUT_HANDLE : STD_ERROR_HANDLE);
   if (output && output != INVALID_HANDLE_VALUE)
   {
      size_t left = strlen(text);
      const char *cursor = text;
      while (left)
      {
         DWORD written = 0;
         DWORD chunk = left > 65536 ? 65536 : (DWORD)left;
         if (!WriteFile(output, cursor, chunk, &written, nullptr) || !written)
            break;
         cursor += written;
         left -= written;
      }
      DWORD written;
      WriteFile(output, "\r\n", 2, &written, nullptr);
   }
#endif
   // The system selects a per-run path beside its command-line/environment dumps.
   // No trace is written beside the executable before that folder is available.
   if (tracePath && *tracePath)
   {
      HANDLE file = CreateFileW(tracePath, FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
         nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
      if (file != INVALID_HANDLE_VALUE)
      {
         size_t left = strlen(text);
         const char *cursor = text;
         while (left)
         {
            DWORD written = 0;
            DWORD chunk = left > 65536 ? 65536 : (DWORD)left;
            if (!WriteFile(file, cursor, chunk, &written, nullptr) || !written)
               break;
            cursor += written;
            left -= written;
         }
         DWORD written;
         WriteFile(file, "\r\n", 2, &written, nullptr);
         FlushFileBuffers(file);
         CloseHandle(file);
      }
   }
   SetLastError(savedError);
#else
#if CA2_STD_TRACE
   FILE *output = errorStream ? stderr : stdout;
   fputs(text, output);
   fputc('\n', output);
   fflush(output);
#endif
#endif
   errno = savedErrno;
}
#endif
