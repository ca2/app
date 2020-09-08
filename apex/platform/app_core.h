#pragma once


typedef int_bool DEFER_INIT();
typedef DEFER_INIT * PFN_DEFER_INIT;
typedef int_bool DEFER_TERM();
typedef DEFER_TERM * PFN_DEFER_TERM;


class node_data_exchange;


class raw_fail {};


// ATTENTION
// aura_aura class should be instantiated before any other ca2 framework 
// class instantiation or any other ca2 framework function call.
// It should be maintained allocated while process is running.
// Not even new/delete/strings/ids can be used after it goes out of scope.




class os_local;
typedef int MAIN_RUNNER(HINSTANCE hInstance);
typedef MAIN_RUNNER * LPFN_MAIN_RUNNER;


#include "aura_main_data.h"


#define APP_CORE_MAXIMUM_STATUS_COUNT 100



class CLASS_DECL_APEX app_core :
   virtual public ::aura_main_data
{
public:


   //string                           m_strCommandLine;
   string                           m_strProgName;
   PFN_DEFER_TERM                   m_pfnDeferTerm;
   tick                             m_tickStart;
   tick                             m_tickAfterApplicationFirstRequest;
   //::apex::system *                    m_psystem;
   //__pointer(aura_main_data)        m_pmaindata;
   __pointer(::apex::library)       m_plibrary;
   ::estatus                        m_estatusa[APP_CORE_MAXIMUM_STATUS_COUNT];
   int                              m_iStatusCount;
   int                              m_iTotalStatusCount;


   //app_core(aura_main_data * pdata);
   app_core();
   ~app_core();

   bool on_result(const ::estatus & estatus);

   static DWORD WINAPI MAIN(LPVOID pvoid);

   //bool system_beg();

   //bool system_init();

   ::estatus system_proc();

   bool has_aura_application_factory() const;

   virtual ::estatus system_init();

   virtual ::estatus system_prep();

   //virtual ::estatus system_main();

   //virtual ::estatus system_call();

   void set_command_line(const char * psz);

   string get_command_line();

   void system_end();

   __result(::apex::application) get_new_application(::object* pobjectContext);
   __result(::apex::application) get_new_application(::object* pobjectContext, const char* pszAppId);

};

//
//typedef bool FN_AURA_APP_CORE(app_core * pappcore);
//
//typedef FN_AURA_APP_CORE * PFN_AURA_APP_CORE;

CLASS_DECL_APEX long aura_aura(::apex::system * pmaindata);

CLASS_DECL_APEX bool node_fill(::apex::system * pappcore);

//CLASS_DECL_APEX i32 aura_entry_point(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow, PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = nullptr, PFN_NEW_AURA_LIBRARY pfnNewLibrary = nullptr);

//CLASS_DECL_APEX int aura_entry_point(int argc, char* argv[], char* pszCommandLin, PFN_NEW_AURA_APPLICATION pfnNewAuraApplication = nullptr, PFN_NEW_AURA_LIBRARY pfnNewLibrary = nullptr);



class CLASS_DECL_APEX aura_level
{
public:


   enum e_level
   {
      level_aura,
      level_axis,
      level_base,
      level_core,
   };


   e_level                    m_elevel;
   PFN_DEFER_INIT             m_pfnDeferInit;
   aura_level *               m_plevelNext;


   aura_level(e_level elevel, PFN_DEFER_INIT pfnDeferInit);

   static aura_level * get_maximum_level();

   static aura_level * find_level(PFN_DEFER_INIT pfnDeferInit);

   static bool defer_init();

   static bool defer_init(PFN_DEFER_INIT pfnDeferInit);


};



