// Offloading apex(TBS) from deep stack stuff 2022-02-22 by camilo at 07:17 <3ThomasBorregaardSørensen!!
#pragma once


typedef int_bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;
typedef int_bool DEFER_TERM();
typedef DEFER_TERM * PFN_DEFER_TERM;


class node_data_exchange;


class raw_fail {};


// ATTENTION
// apex_apex class should be instantiated before any other ca2 framework 
// class instantiation or any other ca2 framework function call.
// It should be maintained allocated while process is running.
// Not even memory_new/delete/strings/ids can be used after it goes out of scope.


//
//
//class main_runner_data
//{
//public:
//   void *      m_p;
//#ifdef WINDOWS
//   HINSTANCE m_hinstance;
//#endif
//
//};
//typedef int MAIN_RUNNER(main_runner_data * pmainrunnerdata);
//typedef MAIN_RUNNER * LPFN_MAIN_RUNNER;

#include "apex_main_data.h"


#define APP_CORE_MAXIMUM_STATUS_COUNT 100



class CLASS_DECL_ACME app_core :
   virtual public ::apex_main_data
{
public:


   //string                            m_strCommandLine;
   string                              m_strProgName;
   PFN_DEFER_TERM                      m_pfnDeferTerm;
   ::duration                          m_durationStart;
   ::duration                          m_durationAfterApplicationFirstRequest;
   //::apex::system *                  acmesystem();
   //::pointer<apex_main_data>        m_pmaindata;
   ::pointer<::acme::library>         m_plibrary;
   ::e_status                          m_estatusa[APP_CORE_MAXIMUM_STATUS_COUNT];
   int                                 m_iStatusCount;
   int                                 m_iTotalStatusCount;


   //app_core(apex_main_data * pdata);
   app_core();
   ~app_core();

   bool on_result(const ::e_status & estatus);

   //static ::u32 WINAPI MAIN(void * pvoid);

   //bool system_beg();

   //bool system_init();

   void system_proc();

   bool has_apex_application_factory() const;

   virtual void system_init();

   virtual void system_prep();

   //virtual void system_main();

   //virtual void system_call();

   string get_command_line();

   void system_end();

   ::pointer<::acme::application>new_app();
   ::pointer<::acme::application>new_app(const char* pszAppId);


   //   ::pointer<::apex::application>get_new_application(::object* pparticle);
   //   ::pointer<::apex::application>get_new_application(::object* pparticle, const char* pszAppId);

   virtual void initialize_application(::acme::application * papp, ::object* pparticle);


};


//
//typedef bool FN_APEX_APP_CORE(app_core * pappcore);
//
//typedef FN_APEX_APP_CORE * PFN_APEX_APP_CORE;

//CLASS_DECL_ACME long apex_apex(system * pmaindata);

//CLASS_DECL_ACME bool node_fill(system * pappcore);

//CLASS_DECL_APEX i32 apex_entry_point(HINSTANCE hinstance, HINSTANCE hPrevInstance, char * pCmdLine, int nCmdShow, PFN_NEW_APEX_APPLICATION pfnNewAuraApplication = nullptr, PFN_NEW_APEX_LIBRARY pfnNewLibrary = nullptr);

//CLASS_DECL_APEX int apex_entry_point(int argc, char* argv[], char* pszCommandLin, PFN_NEW_APEX_APPLICATION pfnNewAuraApplication = nullptr, PFN_NEW_APEX_LIBRARY pfnNewLibrary = nullptr);



//class CLASS_DECL_ACME apex_level
//{
//public:
//
//
//   enum enum_level
//   {
//      e_level_none = 0,
//      e_level_acme = 1,
//      e_level_apex = 2,
//      e_level_aqua = 3,
//      e_level_aura = 4,
//      e_level_axis = 5,
//      e_level_base = 6,
//      e_level_bred = 7,
//      e_level_core = 8,
//   };
//
//
//   enum_level                 m_elevel;
//   PFN_DEFER_INIT             m_pfnDeferInit;
//   apex_level *               m_plevelNext;
//
//
//   apex_level(enum_level elevel, PFN_DEFER_INIT pfnDeferInit);
//
//   static apex_level * get_maximum_level();
//
//   static apex_level * find_level(PFN_DEFER_INIT pfnDeferInit);
//
//   static bool defer_init();
//
//   static bool defer_init(PFN_DEFER_INIT pfnDeferInit);
//
//
//};



