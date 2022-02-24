// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardS�rensen!!
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

#elif defined(LINUX) || defined(FREEBSD)

   char * m_pchar_binary__matter_zip_start = nullptr;
   char * m_pchar_binary__matter_zip_end = nullptr;

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
#elif defined(LINUX) || defined(FREEBSD)
   ::boolean                     m_bGtkApp;
#endif
   ::boolean                     m_bShowApplicationInformation;
   //::boolean                     m_bPreferNoFrameWindow;

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

   
   string                        m_strCommandLine;
   string                        m_strAppId;


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

   string get_executable() const;

   string get_argument1(int iArgument) const;


};


CLASS_DECL_ACME void __main(main & main);


namespace acme
{


   CLASS_DECL_ACME void create_system();
   CLASS_DECL_ACME i32 run_system();


} // namespace acme


#ifdef LINUX


class embed_resource
{
public:

   inline embed_resource(main & main, char * start, char * end)
   {

      main.m_pchar_binary__matter_zip_start = start;
      main.m_pchar_binary__matter_zip_end = end;

   }

};


#endif


class CLASS_DECL_ACME app_flag
{
public:


   app_flag(::main & main, const char * pszFlag);


};


#ifdef LINUX


#define __embed_resource(app) \
extern char _binary__matter_zip_start[]; \
extern char _binary__matter_zip_end[];   \
embed_resource g_embed_resource(app, _binary__matter_zip_start, _binary__matter_zip_end);

#else

#define __embed_resource(app)

#endif


#define __app_flag(app, flag) \
app_flag g_appflag ## __LINE__(app, flag);
