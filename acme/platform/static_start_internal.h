//
// Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#include "acme/exception/engine.h"

class plex_heap_alloc_array;


namespace acme
{

#if OBJECT_TYPE_COUNTER

   extern map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;

#endif


   extern CLASS_DECL_ACME critical_section
   *
   g_pcsGlobal;

#if OBJECT_TYPE_COUNTER

   extern int g_iObjTypCtrInit;

#endif

   extern ::mutex * g_pmutexChildren;
   
#ifdef WINDOWS


#else

//extern DWORD_PTR g_tlsindexLastError;
   extern char * g_pszDemangle;
   extern critical_section * g_pcsDemangle;

#endif


//extern ::mutex * get_system()->g_mutexLibrary;

//extern __LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

//extern critical_section* g_pcsGlobal;

   extern bool g_bOutputDebugString;

// acme commented
//extern critical_section* g_pcsTrace;

//extern ::matter* g_ptrace;

//// acme commented
//extern simple_trace* g_psimpletrace;

#ifdef __APPLE__

   // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
      // http://stackoverflow.com/users/346736/jbenet

      //#include <mach/clock.h>
      //#include <mach/mach.h>
#include <mach/mach_time.h>

   //clock_serv_t   g_cclock;
      extern double g_machtime_conversion_factor;
      //   clock_get_time(cclock, &mts);

#endif


   extern ::mutex * g_pmutexCred;


   extern class ::exception_engine * g_pengine;


   extern ::mutex * g_pmutexMessageDispatch;


   extern CLASS_DECL_ACME array<matter *>
   *
   g_paAura;


   extern id_to_id * g_pmapRTL;


#if defined(WINDOWS)

   extern _locale_t g_localeC;

#else

   extern locale_t g_localeC;

#endif

//extern map < itask_t, itask_t, itask_t, itask_t > * g_pmapThreadOn;


   extern ::nanosecond g_nanosecondFirst;

//plex_heap_alloc_array * g_pplexheapallocarray;

   extern int g_iMemoryCountersStartable;
//extern ::mutex * g_pmutexTrait;
//extern ::mutex * g_pmutexFactory;

   extern ::mutex * g_pmutexUiDestroyed;

#ifdef ANDROID

   extern ::mutex * g_pmutexOutputDebugStringA;

#endif


// #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

// extern ::mutex * g_pmutexMq;

// #endif

#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)

   //extern ::mutex * g_pmutexThreadIdHandleLock;

   //extern ::mutex * g_pmutexThreadIdLock;

   //#if !defined(_UWP)

   //extern ::mutex * g_pmutexPendingThreadsLock;

   //#endif

   //extern ::mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)


#if defined(LINUX) || defined(__APPLE__)


   extern ::mutex * g_pmutexTz;

      extern ::mutex * g_pmutexThreadHandleLock;


#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


   extern ::mutex * g_pmutexCvt;


#endif


   extern critical_section g_csRefDbg;

   CLASS_DECL_ACME void ref();

   class static_start
   {
   public:


      bool m_bRef;


      critical_section *                           m_pcriticalsectionFactory;
      __pointer(::factory::factory)                m_pfactory;
      id_map < __pointer(::factory::factory) >     m_mapFactory;


      static_start();
      ~static_start();


      static static_start g_staticstart;

      void this_ref();


      void construct();


      void init();

      void term();


      //void init_windowing();
      //void term_windowing();




   };


} // namespace acme



