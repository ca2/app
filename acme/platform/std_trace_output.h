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
#if CA2_STD_TRACE || CA2_TRACE_TO_FILE
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#if defined(WINDOWS)
#include "acme/_operating_system.h"
#endif
inline void ca2_write_standard_trace(const char *text)
{
   if (!text)
      return;
   int savedErrno = errno;
#if defined(WINDOWS)
   DWORD savedError = GetLastError();
#if CA2_STD_TRACE
   HANDLE output = GetStdHandle(STD_ERROR_HANDLE);
   if (!output || output == INVALID_HANDLE_VALUE)
      output = GetStdHandle(STD_OUTPUT_HANDLE);
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
#if CA2_TRACE_TO_FILE
   wchar_t path[MAX_PATH];
   DWORD count = GetModuleFileNameW(nullptr, path, MAX_PATH);
   if (count && count < MAX_PATH)
   {
      wchar_t *slash = wcsrchr(path, L'\\');
      if (slash && (size_t)(slash-path)+1+wcslen(L"ca2-trace.log") < MAX_PATH)
      {
         wcscpy(slash+1, L"ca2-trace.log");
         HANDLE file = CreateFileW(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
         if (file != INVALID_HANDLE_VALUE)
         {
            LARGE_INTEGER endOffset = {};
            if (SetFilePointerEx(file, endOffset, nullptr, FILE_END))
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
            }
            CloseHandle(file);
         }
      }
   }
#endif
   SetLastError(savedError);
#else
#if CA2_STD_TRACE
   fputs(text, stderr);
   fputc('\n', stderr);
   fflush(stderr);
#endif
#endif
   errno = savedErrno;
}
#endif
