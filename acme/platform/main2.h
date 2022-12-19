// ReCreated/Merged (from acme_main_data) on 2021-11-01 12:24 BRT <3ThomasBorregaardSørensen!!
// Created by camilo 2021-03-12 12:08 BRT <3_ThomasBS, Mummi and bilbo!!
// ReCreated/Merged (from acme_main_data and apex_main_data) on 2022-09-25 01:35 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/filesystem/filesystem/path.h"


//
//
//////#include "acme/primitive/primitive/object.h"
////#include "implementable.h"
//
//
//class CLASS_DECL_ACME main2 :
//   virtual public ::particle,
//   virtual public APPLICATION_FLAGS
//{
//public:
//
//
//
//
//
//
//   ///int                              m_iPathInstallFolderExeArg;
//   //LPFN_MAIN_RUNNER                 m_mainrunnera[64];
//
//   //string                            m_strCommandLine;
//   //::apex::system *                  acmesystem();
//   //::pointer<apex_main_data>        m_pmaindata;
//   //::pointer<::acme::library>         m_plibrary;
//   //array < ::e_status >                m_estatusa;
//
//
//   main();
//   ~main();
//
//
//   //   main(int argc, char * argv[], char * envp[])
//   //   {
//   //
//   //
//   //   }
//
//
//
//   virtual void system_construct(const main* pmain);
//
//   //inline ::count _get_argc() const { return m_argc; }
//
//   //string _get_argv(int iArg) const;
//
//   //inline ::count get_argument_count1() const { return _get_argc() - 1; }
//
//   //string_array get_arguments();
//
// /*  string get_executable() const;
//
//   string get_argument1(int iArgument) const;*/
//
//   //#ifdef WINDOWS
//   //
//   //   hinstance                        m_hinstance;
//   //   hinstance                        m_hPrevInstance;
//   //   int                              m_nCmdShow;
//   //
//   //#endif
//
//
//      //apex_main_data();
//      //~apex_main_data() override;
//
//
//
//
//      //void system_construct(const class ::main * pmain) override;
//
//
//      //void system_construct(int argc, char** argv, char ** envp);
//      //void system_construct(int argc, wchar_t** argv, wchar_t ** envp);
//
//   virtual void on_system_construct();
//
//
//#ifdef WINDOWS_DESKTOP
//
//   void system_construct(hinstance hinstanceThis, hinstance hPrevInstance, char* pCmdLine, i32 nCmdShow);
//
//#elif defined(_UWP)
//
//   void system_construct(const string_array& stra);
//
//#else
//
//   void system_construct(const scoped_string & strCommandLine, const ::e_display& edisplay = ::e_display_none);
//
//#endif
//
//
//
//   bool is_console_app() const;
//
//
//   //app_core(apex_main_data * pdata);
//   //app_core();
//   //~app_core();
//
//   bool on_result(const ::e_status& estatus);
//
//   //static ::u32 WINAPI MAIN(void * pvoid);
//
//   //bool system_beg();
//
//   //bool system_init();
//
//   void system_proc();
//
//   //bool has_apex_application_factory() const;
//
//   virtual void system_init();
//
//   virtual void system_prep();
//
//   //virtual void system_main();
//
//   //virtual void system_call();
//
//   string get_command_line();
//
//   void system_end();
//
//   //::pointer<::acme::application>new_app();
//   //::pointer<::acme::application>new_app(const scoped_string & strAppId);
//
//
//   //   ::pointer<::apex::application>get_new_application(::object* pparticle);
//   //   ::pointer<::apex::application>get_new_application(::object* pparticle, const scoped_string & strAppId);
//
//   virtual void initialize_application(::acme::application* pacmeapplication, ::particle* pparticle);
//
//
//};
//
//
//class subsystem;
//
//CLASS_DECL_ACME void __main(::acme::application* pacmeapplication);
//
//
//namespace acme
//{
//
//
//   CLASS_DECL_ACME void create_system();
//   CLASS_DECL_ACME i32 run_system();
//
//
//} // namespace acme
//
//
//class embed_resource
//{
//public:
//
//
//   embed_resource(char* start = nullptr, char* end = nullptr);
//
//   static char* get_start();
//   static char* get_end();
//
//
//};
//
//
//class CLASS_DECL_ACME app_flag
//{
//public:
//
//
//   app_flag(::main& main, const scoped_string & strFlag);
//
//
//};
//
//
//#if defined(LINUX) || defined(FREEBSD) //|| defined(ANDROID)
//
//
////#define __embed_resource(app) \
////extern char _binary__matter_zip_start[]; \
////extern char _binary__matter_zip_end[];   \
////embed_resource g_embed_resource(app, _binary__matter_zip_start, _binary__matter_zip_end);
//
//
//#define __embed_resource \
//extern char _binary__matter_zip_start[]; \
//extern char _binary__matter_zip_end[];   \
//embed_resource g_embed_resource(_binary__matter_zip_start, _binary__matter_zip_end)
//
//
//#else
//
//#define __embed_resource \
//embed_resource g_embed_resource()
//
//#endif
//
//
//#define __app_flag(app, flag) \
//app_flag g_appflag ## __LINE__(app, flag);
//
