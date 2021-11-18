// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardS�rensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
#pragma once


struct CLASS_DECL_ACME PLAIN_MAIN
{


   int               m_argc = 0;

   char** m_argv = nullptr;
   char** m_envp = nullptr;

   wchar_t** m_wargv = nullptr;
   wchar_t** m_wenvp = nullptr;

#ifdef WINDOWS

   hinstance         m_hinstanceThis = nullptr;
   hinstance         m_hinstancePrev = nullptr;
   int               m_nCmdShow = -1000;

#elif defined(LINUX)

   char * _binary__matter_zip_start = nullptr;
   char * _binary__matter_zip_end = nullptr;

#endif

   int                           m_iExitCode = 0;

   ::boolean                     m_bLocalization;
   ::boolean                     m_bConsole;
   ::boolean                     m_bDraw2d;
   ::boolean                     m_bWriteText;
   ::boolean                     m_bUser;
   ::boolean                     m_bUserEx;
   ::boolean                     m_bImaging;
   ::boolean                     m_bAudio;
   ::boolean                     m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::boolean                     m_bGdiplus;
#elif defined(LINUX)
   ::boolean                     m_bGtkApp;
#endif
   ::boolean                     m_bShowApplicationInformation;
   //::boolean                     m_bPreferNoFrameWindow;


};


class CLASS_DECL_ACME main :
   virtual public PLAIN_MAIN,
   virtual public acme::implementable
{
public:

   
   string                        m_strCommandLine;
   string                        m_strAppId;



   virtual ::e_status system_construct(const main& main);


};


CLASS_DECL_ACME ::e_status __main(main & main);


namespace acme
{


   CLASS_DECL_ACME void create_system();
   CLASS_DECL_ACME i32 run_system();


} // namespace acme



