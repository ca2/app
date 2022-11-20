// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// ReCreated/Merged (from acme_main_data and apex_main_data) on 2022-09-25 01:35 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/path.h"


struct CLASS_DECL_ACME MAIN // : public ::acme::reference
{

   bool                             m_bFork;

   int                              m_iExitCode = 0;

   ::tristate                       m_bLocalization;
   ::tristate                       m_bNetworking;
   ::tristate                       m_bConsole;
   ::tristate                       m_bDraw2d;
   ::tristate                       m_bWriteText;
   ::tristate                       m_bUser;
   ::tristate                       m_bUserEx;
   ::tristate                       m_bImaging;
   ::tristate                       m_bAudio;
   ::tristate                       m_bMidi;
   ::tristate                       m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::tristate                       m_bGdiplus;
#elif defined(LINUX) || defined(FREEBSD)
   ::tristate                       m_bGtkApp;
#endif
   ::tristate                       m_bShowApplicationInformation;
   ::tristate                       m_bDataCentralRequired;

   ::tristate                       m_bExperienceMainFrame;

   ::i32_sz *                       m_pintstringLanguageResourceMap;
   int                              m_iMatterFromHttpCache;

   const char *                     m_pszMain;
//   //PFN_NEW_MATTER                   m_pfnnewmatterApplication;
//   //PFN_NEW_LIBRARY                  m_pfnnewlibrary;
//   PFN_DEFER_TERM                      m_pfnDeferTerm;

   MAIN();


   void copy_main(const MAIN & main)
   {

      memcpy(this, &main, sizeof(MAIN));

   }


};


//#ifdef LINUX
//
//extern char _binary__matter_zip_start[] __attribute__((weak_import));
//extern char _binary__matter_zip_end[] __attribute__((weak_import));
//
//#endif


//#include "acme/primitive/primitive/object.h"
#include "implementable.h"


class CLASS_DECL_ACME main :
   virtual public MAIN,
   virtual public ::object,
   virtual public acme::implementable
{
public:

   
   string                              m_strCommandLine;
   string                              m_strAppId;
   ::pointer<::acme::application>     m_pacmeapplicationStartup;
   ::pointer<::acme::application>     m_pacmeapplicationMain;


   ///int                              m_iPathInstallFolderExeArg;
   string                           m_strStandalone;
   //LPFN_MAIN_RUNNER                 m_mainrunnera[64];
   ::file::path                     m_pathCacheDirectory;

 //string                            m_strCommandLine;
   string                              m_strProgName;
   ::duration                          m_durationStart;
   ::duration                          m_durationAfterApplicationFirstRequest;
   //::apex::system *                  acmesystem();
   //::pointer<apex_main_data>        m_pmaindata;
   ::pointer<::acme::library>         m_plibrary;
   array < ::e_status >                m_estatusa;


   main();
   ~main();


//   main(int argc, char * argv[], char * envp[])
//   {
//
//
//   }



   virtual void system_construct(const main * pmain);

   //inline ::count _get_argc() const { return m_argc; }

   //string _get_argv(int iArg) const;

   //inline ::count get_argument_count1() const { return _get_argc() - 1; }

   //string_array get_arguments();

 /*  string get_executable() const;

   string get_argument1(int iArgument) const;*/

//#ifdef WINDOWS
//
//   hinstance                        m_hinstance;
//   hinstance                        m_hPrevInstance;
//   int                              m_nCmdShow;
//
//#endif


   //apex_main_data();
   //~apex_main_data() override;




   //void system_construct(const class ::main * pmain) override;


   //void system_construct(int argc, char** argv, char ** envp);
   //void system_construct(int argc, wchar_t** argv, wchar_t ** envp);

   virtual void on_system_construct();


#ifdef WINDOWS_DESKTOP

   void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char * pCmdLine, i32 nCmdShow);

#elif defined(_UWP)

   void system_construct(const string_array & stra);

#else

   void system_construct(const char * pszCommandLine, const ::e_display & edisplay = ::e_display_none);

#endif



   bool is_console_app() const;


   //app_core(apex_main_data * pdata);
   //app_core();
   //~app_core();

   bool on_result(const ::e_status & estatus);

   //static ::u32 WINAPI MAIN(void * pvoid);

   //bool system_beg();

   //bool system_init();

   void system_proc();

   //bool has_apex_application_factory() const;

   virtual void system_init();

   virtual void system_prep();

   //virtual void system_main();

   //virtual void system_call();

   string get_command_line();

   void system_end();

   //::pointer<::acme::application>new_app();
   //::pointer<::acme::application>new_app(const char* pszAppId);


   //   ::pointer<::apex::application>get_new_application(::object* pparticle);
   //   ::pointer<::apex::application>get_new_application(::object* pparticle, const char* pszAppId);

   virtual void initialize_application(::acme::application * pacmeapplication, ::particle * pparticle);


};


class subsystem;

CLASS_DECL_ACME void __main(::acme::application * pacmeapplication);


namespace acme
{


   CLASS_DECL_ACME void create_system();
   CLASS_DECL_ACME i32 run_system();


} // namespace acme


class embed_resource
{
public:


   embed_resource(char * start = nullptr, char * end = nullptr);

   static char * get_start();
   static char * get_end();


};


class CLASS_DECL_ACME app_flag
{
public:


   app_flag(::main & main, const char * pszFlag);


};


#if defined(LINUX) || defined(FREEBSD) //|| defined(ANDROID)


//#define __embed_resource(app) \
//extern char _binary__matter_zip_start[]; \
//extern char _binary__matter_zip_end[];   \
//embed_resource g_embed_resource(app, _binary__matter_zip_start, _binary__matter_zip_end);


#define __embed_resource \
extern char _binary__matter_zip_start[]; \
extern char _binary__matter_zip_end[];   \
embed_resource g_embed_resource(_binary__matter_zip_start, _binary__matter_zip_end)


#else

#define __embed_resource \
embed_resource g_embed_resource()

#endif


#define __app_flag(app, flag) \
app_flag g_appflag ## __LINE__(app, flag);
