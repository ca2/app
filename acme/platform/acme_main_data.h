// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
#pragma once


class CLASS_DECL_ACME acme_main_data
{
public:


   int                              m_argc;
   char**                           m_argv;
   char**                           m_envp;
   wchar_t**                        m_wargv;
   wchar_t**                        m_wenvp;
   int                              m_iExitCode;
   string                           m_strCommandLine;


   acme_main_data()
   {

      m_argc = 0;
      m_argv = nullptr;
      m_envp = nullptr;
      m_wargv = nullptr;
      m_wenvp = nullptr;
      m_iExitCode = 0;

   }


};