// Created by camilo on 2021-04-30 03:24 <3TBS_!!
#include "framework.h"


::e_status acme_main_data::system_construct(int argc, char** argv, char** envp)
{

   m_argc = argc;

   m_argv = argv;

   m_envp = envp;

   m_wargv = nullptr;

   m_wenvp = nullptr;

   return ::success;

}


::e_status acme_main_data::system_construct(int argc, wchar_t** argv, wchar_t** envp)
{

   m_argc = argc;

   m_argv = nullptr;

   m_envp = nullptr;

   m_wargv = argv;

   m_wenvp = envp;

   return ::success;

}


::e_status acme_main_data::system_construct(const char* pszCommandLine)
{

   m_strCommandLine = pszCommandLine;

#ifdef WINDOWS_DESKTOP

   m_argc = __argc;

   m_argv = __argv;

   m_wargv = __wargv;

   m_envp = *__p__environ();

   m_wenvp = *__p__wenviron();

#endif

   return ::success;

}



