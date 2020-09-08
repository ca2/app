//
//  base_static_start.h
//  acme
//
//
//
#pragma once


class plex_heap_alloc_array;

namespace acme
{


#if OBJ_TYP_CTR

   extern map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;

#endif


   extern CLASS_DECL_ACME critical_section* g_pcsGlobal;

   extern CLASS_DECL_ACME string_to_string* g_pmapFontFaceName;

   extern CLASS_DECL_ACME critical_section* g_pcsFont;

   //extern critical_section* g_pcsRefDbg;


#if OBJ_TYP_CTR

   extern int g_iObjTypCtrInit;

#endif

   extern ::mutex* g_pmutexChildren;
   extern ::mutex* g_pmutexThreadWaitClose;
   //extern string_map < __pointer(::acme::library) >* g_pmapLibrary;
   //extern string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;


//#if !defined(WINDOWS)

//void windows10_init();
#ifdef WINDOWS


   void set_simple_output_debug_string_a();

   void set_extended_output_debug_string_a();

   void set_simple_output_debug_string_w();

   void set_extended_output_debug_string_w();


   //#endif

#else

   extern DWORD_PTR g_tlsindexLastError;
   extern char* g_pszDemangle;
   extern critical_section* g_pcsDemangle;

#endif


   //extern ::mutex * &::get_context_system()->g_mutexLibrary;

   extern __LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

   extern ::mutex* g_pmutexGlobals;

   //extern critical_section* g_pcsGlobal;

   extern bool g_bOutputDebugString;

   // acme commented
   //extern critical_section* g_pcsTrace;

   //extern ::generic* g_ptrace;

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


   extern ::mutex* g_pmutexCred;


   extern class ::exception_engine* g_pexceptionengine;

   extern ::mutex* g_pmutexMessageDispatch;


   extern CLASS_DECL_ACME array < generic* >* g_paAura;


   extern ::map < ::id, const ::id&, ::id, const ::id& >* g_pmapRTL;

   extern plex_heap_alloc_array* g_pheap;

   extern critical_section* g_pmutexSystemHeap;

#if defined(WINDOWS)

   extern _locale_t g_localeC;

#else

   extern locale_t g_localeC;

#endif

   //extern map < ITHREAD, ITHREAD, ITHREAD, ITHREAD > * g_pmapThreadOn;

#ifdef WINDOWS

   extern LARGE_INTEGER g_largeintegerFrequency;

#endif

   extern i64 g_iFirstNano;

   //plex_heap_alloc_array * g_pplexheapallocarray;

   extern int g_iMemoryCountersStartable;
   //extern mutex * g_pmutexTrait;
   //extern ::mutex * g_pmutexFactory;

   extern ::mutex* g_pmutexUiDestroyed;

#ifdef ANDROID

   extern ::mutex* g_pmutexOutputDebugStringA;

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

   
   extern ::mutex* g_pmutexTz;

   extern ::mutex* g_pmutexThreadHandleLock;


#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


   extern ::mutex* g_pmutexCvt;


#endif


   extern critical_section g_csRefDbg;
   
   CLASS_DECL_ACME void ref();

   class acme
   {
   public:


      bool m_bRef;


      acme();
      ~acme();

      static acme g_acme;
      
      void this_ref();

      
      
      void construct();


      ::estatus init();
      ::estatus term();


      void init_windowing();
      void terg_windowing();


      void init_id_pool();
      void term_id_pool();


   };


} // namespace acme


//extern ::acme::acme __acme;

//::get_context_system()

//__acme.g_psystem

