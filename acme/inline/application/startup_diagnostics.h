#pragma once
#ifndef CA2_STARTUP_TRACE
#define CA2_STARTUP_TRACE 0
#endif
#ifndef CA2_ATTACH_PARENT_CONSOLE
#define CA2_ATTACH_PARENT_CONSOLE 0
#endif
#if defined(WINDOWS) && (CA2_STARTUP_TRACE || CA2_ATTACH_PARENT_CONSOLE)
#include <stdio.h>
#include <string.h>
#include <exception>
namespace ca2_startup_diagnostics
{
inline void attach_console()
{
#if CA2_ATTACH_PARENT_CONSOLE
   if (AttachConsole(ATTACH_PARENT_PROCESS) || GetLastError() == ERROR_ACCESS_DENIED)
   {
      DWORD mode;
      if (GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &mode))
      {
         freopen("CONOUT$", "w", stdout);
         setvbuf(stdout, nullptr, _IONBF, 0);
      }
      if (GetConsoleMode(GetStdHandle(STD_ERROR_HANDLE), &mode))
      {
         freopen("CONOUT$", "w", stderr);
         setvbuf(stderr, nullptr, _IONBF, 0);
      }
      if (GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode))
         freopen("CONIN$", "r", stdin);
   }
#endif
}
inline void write(const char *message)
{
#if CA2_STARTUP_TRACE
   DWORD savedError = GetLastError();
   char line[2048];
   int count = _snprintf(line, sizeof(line)-1, "[pid=%lu tick=%lu] %s\r\n",
      (unsigned long)GetCurrentProcessId(), (unsigned long)GetTickCount(), message ? message : "(null)");
   line[sizeof(line)-1] = 0;
   DWORD length = count < 0 ? (DWORD)strlen(line) : (DWORD)count;
   DWORD written, mode;
   HANDLE console = GetStdHandle(STD_ERROR_HANDLE);
   if (GetConsoleMode(console, &mode))
      WriteFile(console, line, length, &written, nullptr);
   char path[MAX_PATH];
   DWORD n = GetModuleFileNameA(nullptr, path, sizeof(path));
   if (n && n < sizeof(path))
   {
      char *slash = strrchr(path, '\\');
      if (slash && (size_t)(slash-path)+1+strlen("ca2-startup.log") < sizeof(path))
      {
         strcpy(slash+1, "ca2-startup.log");
         HANDLE file = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE,
            nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
         if (file != INVALID_HANDLE_VALUE)
         {
            LARGE_INTEGER endOffset = {};
            if (SetFilePointerEx(file, endOffset, nullptr, FILE_END))
            {

            WriteFile(file, line, length, &written, nullptr);
            FlushFileBuffers(file);
            }
            CloseHandle(file);
         }
         else if (GetConsoleMode(console, &mode))
         {
            const char *failure = "Cannot open ca2-startup.log beside executable.\r\n";
            WriteFile(console, failure, (DWORD)strlen(failure), &written, nullptr);
         }
      }
   }
   SetLastError(savedError);
#else
   (void)message;
#endif
}
inline void returned(int code)
{
#if CA2_STARTUP_TRACE
   char text[80];
   _snprintf(text, sizeof(text), "application main returned %d", code);
   text[sizeof(text)-1] = 0;
   write(text);
#else
   (void)code;
#endif
}
}
#endif
