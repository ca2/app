//
//  base_static_start.h
//  aura
//
//
//
#pragma once

//
//#include "acme/platform/acme.h"
//
//
//class plex_heap_alloc_array;
//
//
//namespace aura
//{
//
//
////#if OBJECT_TYPE_COUNTER
////
////   extern map < const_char_pointer , const ::scoped_string & scopedstr, long long, long long >* g_pmapObjTypCtr;
////
////#endif
//
//
//   //extern CLASS_DECL_AURA critical_section* g_pcsGlobal;
//
//   extern CLASS_DECL_AURA string_map < int_to_string > * g_pmapFontFaceName;
//
//   extern CLASS_DECL_AURA critical_section* g_pcsFont;
//
//   extern CLASS_DECL_AURA ::pointer< ::mutex > g_pmutexWindowing;
//
//   //extern critical_section* g_pcsRefDbg;
//
//
////#if OBJECT_TYPE_COUNTER
////
////   extern int g_iObjTypCtrInit;
////
////#endif
//
//   extern ::pointer< ::mutex > g_pmutexChildren;
//   //extern ::pointer< ::mutex > g_pmutexThreadWaitClose;
//   //extern string_map < ::pointer<::acme::library >> g_pmapLibrary;
//   //extern string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;
//
//
//////#if !defined(WINDOWS)
////
//////void windows10_init();
////#ifdef WINDOWS
////
////
////#else
////
////   extern DWORD_PTR g_tlsindexLastError;
////   extern char* g_pszDemangle;
////   extern critical_section* g_pcsDemangle;
////
////#endif
//
//
//   //extern ::pointer< ::mutex > psystem->g_mutexLibrary;
//
//   //extern __LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;
//
//   //extern ::pointer< ::mutex > g_pmutexGlobals;
//
//   //extern critical_section* g_pcsGlobal;
//
//   //extern bool g_bOutputDebugString;
//
//   //extern critical_section* g_pcsTrace;
//
//   //extern ::matter* g_ptrace;
//
//   //extern simple_trace* g_psimpletrace;
//
////#ifdef __APPLE__
////
////   // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
////   // http://stackoverflow.com/users/346736/jbenet
////
////   //#include <mach/clock.h>
////   //#include <mach/mach.h>
////#include <mach/mach_time.h>
////
//////clock_serv_t   g_cclock;
////   extern double g_machtime_conversion_factor;
////   //   clock_get_time(cclock, &mts);
////
////#endif
//
//
//   //extern ::pointer< ::mutex > g_pmutexCred;
//
//
//   //extern class ::exception_engine* g_pexceptionengine;
//
//   //extern ::pointer< ::mutex > g_pmutexMessageDispatch;
//
//
//   //extern CLASS_DECL_AURA array < matter* >* g_paAura;
//
//
//   //extern ::map < ::atom, const ::atom&, ::atom, const ::atom& >* g_pmapRTL;
//
//   //extern plex_heap_alloc_array* g_pheap;
//
//   //extern critical_section* g_pmutexSystemHeap;
//
////#if defined(WINDOWS)
////
////   extern _locale_t g_localeC;
////
////#else
////
////   extern locale_t g_localeC;
////
////#endif
//
//   //extern map < itask, itask, itask, itask > * g_pmapThreadOn;
//
////#ifdef WINDOWS
////
////   extern LARGE_INTEGER g_largeintegerFrequency;
////
////#endif
//
//   //extern long long g_iFirstNano;
//
//   //plex_heap_alloc_array * g_pplexheapallocarray;
//
//   //extern int g_iMemoryCountersStartable;
//   //extern ::pointer< ::mutex > g_pmutexTrait;
//   //extern ::pointer< ::mutex > g_pmutexFactory;
//
//   extern ::pointer< ::mutex > g_pmutexUiDestroyed;
//
////#ifdef __ANDROID__
////
////   extern ::pointer< ::mutex > g_pmutexOutputDebugStringA;
////
////#endif
//
//
//   // #if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)
//
//   // extern ::pointer< ::mutex > g_pmutexMq;
//
//   // #endif
////
////#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(__ANDROID__)
////
//////extern ::pointer< ::mutex > g_pmutexThreadIdHandleLock;
////
//////extern ::pointer< ::mutex > g_pmutexThreadIdLock;
////
//////#if !defined(UNIVERSAL_WINDOWS)
////
//////extern ::pointer< ::mutex > g_pmutexPendingThreadsLock;
////
//////#endif
////
//////extern ::pointer< ::mutex > g_pmutexTlsData;
////
////#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)
//
////
////#if defined(LINUX) || defined(__APPLE__)
////
////
////   extern ::pointer< ::mutex > g_pmutexTz;
////
////   extern ::pointer< ::mutex > g_pmutexThreadHandleLock;
////
////
////#endif // defined(LINUX) || defined(__APPLE__)
//
//
////#ifdef __APPLE__
////
////
////   extern ::pointer< ::mutex > g_pmutexCvt;
////
////
////#endif
//
//
//   //extern critical_section g_csRefDbg;
//   
//   //CLASS_DECL_AURA void ref();
//
////   class aura
////   {
////   public:
////
////
////      bool m_bRef;
////
////
////      aura();
////      ~aura();
////
////      static aura g_aura;
////
////      void this_ref();
////
////
////
////      void construct();
////
////
////      void init();
////      void term();
////
////
////      //void init_windowing();
////      //void terg_windowing();
////
////
////
////
////   };
//
//
//} // namespace aura
//
//
////extern ::aura::aura __aura;
//
////::get_context_system()
//
////__aura.g_psystem
//
