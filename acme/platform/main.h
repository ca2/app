// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
#pragma once


struct CLASS_DECL_ACME PLAIN_MAIN
{


   int               m_argc = 0;

   char** m_argv = nullptr;
   char** m_envp = nullptr;

   wchar_t** m_wargv = nullptr;
   wchar_t** m_wenvp = nullptr;

   bool              m_bConsole = false;

#ifdef WINDOWS_DESKTOP

   hinstance         m_hinstanceThis = nullptr;
   hinstance         m_hinstancePrev = nullptr;
   int               m_nCmdShow = -1000;

#endif

   int               m_iExitCode = 0;



};


class CLASS_DECL_ACME main :
   virtual public PLAIN_MAIN,
   virtual public acme::implementable
{
public:

   
   string            m_strCommandLine;
   string            m_strAppId;


   virtual ::e_status system_construct(const main& main);


};


CLASS_DECL_ACME ::e_status __main(main & main);


namespace acme
{


   CLASS_DECL_ACME void create_system();
   CLASS_DECL_ACME i32 run_system();


} // namespace acme



