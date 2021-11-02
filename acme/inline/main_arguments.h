// Created on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
#pragma once


struct CLASS_DECL_ACME main_arguments :
   virtual public acme::implementable
{

   int               m_argc = 0;

   char**            m_argv = nullptr;
   char**            m_envp = nullptr;

   wchar_t**         m_wargv = nullptr;
   wchar_t**         m_wenvp = nullptr;

   bool              m_bConsole = false;

#ifdef WINDOWS_DESKTOP

   hinstance         m_hinstanceThis = nullptr;
   hinstance         m_hinstancePrev = nullptr;
   tchar *           m_pszCommandLine = nullptr;
   int               m_nCmdShow = -1000;

#endif

};


CLASS_DECL_ACME ::e_status __main(main_arguments& mainarguments);



