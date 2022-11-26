//
//  base_static_start.h
//  acme
//
//
//
//
// Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
//#include "acme/exception/engine.h"
#pragma once


//#include "acme/primitive/collection/array.h"
#include "acme/primitive/primitive/factory.h"
//#include "acme/primitive/primitive/pointer.h"


namespace acme
{


   //void initialize_system();
   //void finalize_system();

   //   class CLASS_DECL_ACME acme
   //   {
   //   public:
   //
   //      acme() {::acme::initialize();}
   //      ~acme() {::acme::finalize();}
   //
   //   };


   CLASS_DECL_ACME bool should_output_debug_string();
   CLASS_DECL_ACME bool add_matter(::matter * pmatter);

#ifdef WINDOWS
   CLASS_DECL_ACME _locale_t get_c_locale();
#else
   CLASS_DECL_ACME locale_t get_c_locale();
#endif



   class plex_heap_alloc_array;



#if OBJECT_TYPE_COUNTER

   extern map < const char *, const char *, ::i64, ::i64 > * g_pmapObjTypCtr;

#endif


   //extern CLASS_DECL_ACME critical_section
     // *
      //g_pcsGlobal;

#if OBJECT_TYPE_COUNTER

   extern int g_iObjTypCtrInit;

#endif

   //extern ::pointer< ::mutex > g_pmutexChildren;

#ifdef WINDOWS


#else

   //extern DWORD_PTR g_tlsindexLastError;
   extern char * g_pszDemangle;
   //extern critical_section * g_pcsDemangle;

#endif


   //extern ::pointer< ::mutex > get_system()->g_mutexLibrary;

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


   //extern ::pointer< ::mutex > g_pmutexCred;


   //extern class ::exception_engine * g_pengine;


   ///extern ::pointer< ::mutex > g_pmutexMessageDispatch;


   extern CLASS_DECL_ACME ::array<matter *>
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
   //extern ::pointer< ::mutex > g_pmutexTrait;
   //extern ::pointer< ::mutex > g_pmutexFactory;

   //extern ::pointer< ::mutex > g_pmutexUiDestroyed;

#ifdef ANDROID

   //extern ::pointer< ::mutex > g_pmutexOutputDebugStringA;

#endif


   // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   // extern ::pointer< ::mutex > g_pmutexMq;

   // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)

      //extern ::pointer< ::mutex > g_pmutexThreadIdHandleLock;

   //extern ::pointer< ::mutex > g_pmutexThreadIdLock;

   //#if !defined(_UWP)

   //extern ::pointer< ::mutex > g_pmutexPendingThreadsLock;

   //#endif

   //extern ::pointer< ::mutex > g_pmutexTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)


#if defined(LINUX) || defined(__APPLE__)


   //extern ::pointer< ::mutex > g_pmutexTz;

   //extern ::pointer< ::mutex > g_pmutexThreadHandleLock;


#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


   //extern ::pointer< ::mutex > g_pmutexCvt;


#endif


   //CLASS_DECL_ACME void ref();

   class CLASS_DECL_ACME acme
   {
   public:


      //bool m_bRef;

      class ::time m_timeStart;


      ::sub_system * m_psubsystem;
      static acme * g_p;


      acme();
      ~acme();


      //static static_start g_staticstart;

      //void this_ref();

      class ::time start_nanosecond();
      //void construct();


      //void init();

      //void term();


      //void init_windowing();
      //void term_windowing();

   


   };



} // namespace acme



