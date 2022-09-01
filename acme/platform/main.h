// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
#pragma once


struct CLASS_DECL_ACME PLAIN_MAIN // : public ::acme::reference
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

#elif defined(LINUX) || defined(FREEBSD) || defined(ANDROID)

   const char * m_pchar_binary__matter_zip_start = nullptr;
   const char * m_pchar_binary__matter_zip_end = nullptr;

#endif

   int                           m_iExitCode = 0;

   ::tristate                     m_bLocalization;
   ::tristate                     m_bNetworking;
   ::tristate                     m_bConsole;
   ::tristate                     m_bDraw2d;
   ::tristate                     m_bWriteText;
   ::tristate                     m_bUser;
   ::tristate                     m_bUserEx;
   ::tristate                     m_bImaging;
   ::tristate                     m_bAudio;
   ::tristate                     m_bMidi;
   ::tristate                     m_bInitializeDataCentral;
#ifdef WINDOWS_DESKTOP
   ::tristate                     m_bGdiplus;
#elif defined(LINUX) || defined(FREEBSD)
   ::tristate                     m_bGtkApp;
#endif
   ::tristate                     m_bShowApplicationInformation;
   //::tristate                     m_bPreferNoFrameWindow;

   PLAIN_MAIN();

};


//#ifdef LINUX
//
//extern char _binary__matter_zip_start[] __attribute__((weak_import));
//extern char _binary__matter_zip_end[] __attribute__((weak_import));
//
//#endif


class CLASS_DECL_ACME main :
   virtual public PLAIN_MAIN,
   virtual public acme::implementable
{
public:

   
   string                              m_strCommandLine;
   string                              m_strAppId;
   __pointer(::app)                    m_pappStartup;
   __pointer(::app)                    m_pappMain;



   main();
   ~main();


//   main(int argc, char * argv[], char * envp[])
//   {
//
//
//   }



   virtual void system_construct(const main& main);

   inline ::count _get_argc() const { return m_argc; }

   string _get_argv(int iArg) const;

   inline ::count get_argument_count1() const { return _get_argc() - 1; }

   string_array get_arguments();

   string get_executable() const;

   string get_argument1(int iArgument) const;


};


CLASS_DECL_ACME void __main(main & main);


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
