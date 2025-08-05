#include "framework.h"
//#include "apex/operating_system.h"
#include "apex.h"
#include "apex/networking/sockets/base/base_socket.h"
//#include "apex/platform/app_core.h"
//#include "apex/astr.h"
//#include "acme/exception/engine.h"
#include "system.h"


//bool __node_apex_pre_init();
//bool __node_apex_pos_init();

CLASS_DECL_APEX string __apex_get_text(const ::scoped_string & scopedstr);




namespace parallelization
{

   void destroy();


} // namespace parallelization



void on_term_thread();

//extern ::pointer< ::mutex > g_pmutexThreadDeferredCreation;
//extern ::array < ::pointer<thread >> g_pthreadaDeferredCreate;


//#include <sqlite3.h>



//typedef bool THREAD_GET_RUN();
//using PFN_THREAD_GET_RUN = THREAD_GET_RUN*;

//CLASS_DECL_ACME void set_thread_get_run(PFN_THREAD_GET_RUN pthreadrun);

//bool apex_thread_get_run();

#ifdef RASPBERRYPIOS
#define OPERATING_SYSTEM_NAMESPACE linux
#endif

#if defined(__APPLE__)
#include <xlocale.h>
#else
#include <locale.h>
#endif

//#ifdef LINUX
//#include <glib.h> // sudo apt-get install libglib2.0-dev
//#endif






//extern thread_local ::task_pointer t_pthread;







//namespace apex
//{
//
//
////   bool g_bApex;
////
//
////   CLASS_DECL_APEX critical_section* g_pcsFont = nullptr;
////
////
////   CLASS_DECL_APEX string_to_string * g_pmapFontFaceName = nullptr;
////
//
////   ::pointer< ::mutex > g_pmutexChildren;
//
////#if !defined(WINDOWS)
////
////   char* g_pszDemangle;
////   critical_section* g_pcsDemangle;
////
////#endif
//
//
//   //::pointer< ::mutex > psystem->g_mutexLibrary;
//
//   //__LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;
//
//   //::pointer< ::mutex > get_globals_mutex();
//
//   //critical_section* g_pcsGlobal;
//
//   //bool g_bOutputDebugString;
//
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
////   double g_machtime_conversion_factor;
////   //   clock_get_time(cclock, &mts);
////
////#endif
//
//
//   //::pointer< ::mutex > g_pmutexCred;
//
//
//   //class ::exception_engine* g_pexceptionengine;
//
////   ::pointer< ::mutex > g_pmutexMessageDispatch;
//
//
////   array < matter* >* g_paAura;
////
////#ifdef WINDOWS
////
////   LARGE_INTEGER g_largeintegerFrequency;
////
////#endif
//
////   long long g_iFirstNano;
//
//   //plex_heap_alloc_array * g_pplexheapallocarray;
//
////   int g_iMemoryCountersStartable;
////   //::pointer< ::mutex > g_pmutexTrait;
////   //::pointer< ::mutex > g_pmutexFactory;
////
////   ::pointer< ::mutex > g_pmutexUiDestroyed;
//
////#ifdef __ANDROID__
////
////   ::pointer< ::mutex > g_pmutexOutputDebugStringA;
////
////#endif
//
//   //CLASS_DECL_APEX apex_str_pool* g_papexstrpool;
//
//   // #if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)
//
//   // ::pointer< ::mutex > g_pmutexMq;
//
//   // #endif
////
////#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(__ANDROID__)
////
//////::pointer< ::mutex > g_pmutexThreadIdHandleLock;
////
//////::pointer< ::mutex > g_pmutexThreadIdLock;
////
//////#if !defined(UNIVERSAL_WINDOWS)
////
//////::pointer< ::mutex > g_pmutexPendingThreadsLock;
////
//////#endif
////
//////::pointer< ::mutex > g_pmutexTlsData;
////
////#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)
////
////
//////#if defined(LINUX) || defined(__APPLE__)
////
////
////   ::pointer< ::mutex > g_pmutexTz;
////
////   ::pointer< ::mutex > g_pmutexThreadHandleLock;
////
////
////#endif // defined(LINUX) || defined(__APPLE__)
//
//
////#ifdef __APPLE__
////
////
////   ::pointer< ::mutex > g_pmutexCvt;
////
////
////#endif
//
//
//   //critical_section g_csRefDbg;
//
//
//
////   void static_start::construct()
////   {
////
////      //::set_thread_get_run(&apex_thread_get_run);
////      //::set_task_sleep(&acme_task_sleep);
////
////      g_bApex = 0;
////
////#if OBJECT_TYPE_COUNTER
////
////      g_pmapObjTypCtr = nullptr;
////
////#endif
////
////      g_bApex = false;
////
////#if OBJECT_TYPE_COUNTER
////
////      g_iObjTypCtrInit = 0;
////
////#endif
////
////      g_pmutexChildren = nullptr;
////
////#if !defined(WINDOWS)
////
//////      g_tlsindexLastError = 0;
////
////      g_pszDemangle = nullptr;
////
////      g_pcsDemangle = nullptr;
////
////#endif
////
////      //g_main_deferred_run = nullptr;
////
////      //get_globals_mutex() = nullptr;
////
////      //g_pcsGlobal = nullptr;
////
////      //g_bOutputDebugString = true;
////
////      //g_pcsTrace = nullptr;
////
////      //g_ptrace = nullptr;
////
////      //g_psimpletrace = nullptr;
////
////
////      g_pexceptionengine = nullptr;
////      g_pmutexMessageDispatch = nullptr;
////
////      g_paAura = nullptr;
////
////#ifdef WINDOWS
////
////      g_largeintegerFrequency = {};
////
////#endif
////
////      g_iFirstNano = 0;
////
////      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;
////
////      g_iMemoryCountersStartable = 0;
////      //::pointer< ::mutex > g_pmutexTrait;
////      //::pointer< ::mutex > g_pmutexFactory;
////
////      g_pmutexUiDestroyed = 0;
////
////#ifdef __ANDROID__
////
////      g_pmutexOutputDebugStringA = 0;
////
////#endif
////
////      //g_papexstrpool = nullptr;
////
////      // #if defined(LINUX) || defined(__APPLE__) || defined(__ANDROID__)
////
////      // ::pointer< ::mutex > g_pmutexMq;
////
////      // #endif
////
////#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(__ANDROID__)
////
//////::pointer< ::mutex > g_pmutexThreadIdHandleLock;
////
//////::pointer< ::mutex > g_pmutexThreadIdLock;
////
//////#if !defined(UNIVERSAL_WINDOWS)
////
//////::pointer< ::mutex > g_pmutexPendingThreadsLock;
////
//////#endif
////
//////::pointer< ::mutex > g_pmutexTlsData;
////
////#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)
////
////#if defined(LINUX) || defined(__APPLE__)
////
////      g_pmutexTz = nullptr;
////
////      g_pmutexThreadHandleLock = nullptr;
////
////#endif // defined(LINUX) || defined(__APPLE__)
////
////
////#ifdef __APPLE__
////
////
////      g_pmutexCvt = nullptr;
////
////
////#endif
////
////      //g_pcsFont = nullptr;
////
////      //g_pmapFontFaceName = nullptr;
////
////      //add_factory_item < ::apex::idpool >();
////
////
////
////   }
////
//
////   void initialize_system()
////   {
////
////      //m_bRef = false;
////
////      //construct();
////
//////
//////#ifndef WINDOWS
//////
//////      g_pcsDemangle = ___new critical_section();
//////
//////#endif
////
////
////
//////#ifdef BSD_STYLE_SOCKETS
//////
//////      ::sockets::base_socket::s_pmutex = ___new ::pointer < ::mutex > ();
//////
//////#endif
////
////
//////#ifdef __APPLE__
//////
//////      g_pmutexCvt = ___new ::pointer < ::mutex > ();
//////
//////#endif
////
//////#if MEMDLEAK
//////
//////      memdleak_init();
//////
//////#endif
////
//////      g_paAura = aaa_memory_new array < matter * >;
//////
//////      g_pmutexUiDestroyed = ___new ::pointer < ::mutex > ();
//////
//////      g_pmutexMessageDispatch = ___new ::pointer < ::mutex > ();
//////
//////      g_pmutexCred = ___new ::pointer < ::mutex > ();
//////
//////#if defined(LINUX) || defined(__APPLE__)
//////
//////      g_pmutexTz = ___new ::pointer < ::mutex > ();
//////
//////#endif // defined(LINUX) || defined(__APPLE__)
////
////
//////#ifdef MACOS
//////
//////      //mach_port_deallocate(mach_task_self(), g_cclock);
//////
//////#endif
////
//////#ifdef PRIMITIVE_DEBUG
//////
//////      apex_auto_debug_teste();
//////
//////#endif
////
//////#ifdef MEMORY_COUNTERS
//////
//////      g_iMemoryCountersStartable = 1;
//////
//////#else
//////
//////      g_iMemoryCountersStartable = 0;
//////
//////#endif
////
////      //::channel::s_pmutexChannel = __allocate mutex();
////
////      //g_papexstrpool = ___new apex_str_pool();
////
////      //::user::init_windowing();
////
////      //g_pcsRefDbg = ___new critical_section();
////
////      //g_bApex = true;
////
////      //::thread::g_pmutex = ___new mutex();
////
////      //::thread::g_pthreadmap = ___new ::thread_map ();
////
//////      factory()->add_factory_item < ::apex::system, ::platform::system >();
//////      factory()->add_factory_item < ::platform::context, ::platform::context >();
////
////
//////#if OBJECT_TYPE_COUNTER
//////      g_iObjTypCtrInit = 1;
//////#endif
//////
//////      g_pcsFont = ___new critical_section();
//////
//////      g_pmapFontFaceName = ___new string_to_string();
////
////      //g_pmutexThreadDeferredCreation = aaa_memory_new ::pointer < ::mutex >;
////
////      //g_pthreadaDeferredCreate = aaa_memory_new ::array < ::pointer<thread >>);
////
////
//////      void static_start::init()
//////xxxxxx init();
////      {
////
////         ::parallelization::initialize();
////
////      }
////
////   }
//
//
////   void finalize_system()
////   {
////
//////      void static_start::term()
//////xxxxxx term();
////      {
////
////         //::parallelization::wait_threads(1_min);
////
////         //if (g_axisontermthread)
////         //{
////
////         //   g_axisontermthread();
////
////         //}
////
//////         on_term_thread();
//////
//////         ::parallelization::destroy();
////
////         //__node_apex_pre_term();
////
//////#ifdef WINDOWS
//////
//////      set_simple_output_debug_string_a();
//////
//////      set_simple_output_debug_string_w();
//////
//////#endif
////
//////         processor_cache_oriented_destroy_all_memory_pools();
////
////         //__node_apex_pos_term();
////
////         //::apex::static_start::term();
////
////         //return true;
////
////         //return ::success;
//////
////      }
////
//////      ::acme::del(g_pthreadaDeferredCreate);
////
//////      ::acme::del(g_pmutexThreadDeferredCreation);
////
//////      ::acme::del(g_pmapFontFaceName);
//////
//////      ::acme::del(g_pcsFont);
////
////////#if OBJECT_TYPE_COUNTER
//////      g_iObjTypCtrInit = 0;
//////#endif
//////
//////      //::release(t_pthread);
////
////      // if(g_pmapAura)
////      // {
////
////      //    try
////      //    {
////
////      //       g_pmapAura->erase_all();
////
////      //    }
////      //    catch(...)
////      //    {
////
////      //    }
////
////      // }
////
////      //try
////      //{
////
////      //   synchronous_lock synchronouslock(psystem->g_mutexLibrary);
////
////      //   g_pmapLibCall->erase_all();
////
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //try
////      //{
////
////      //   synchronous_lock synchronouslock(psystem->g_mutexLibrary);
////
////      //   psystem->g_mapLibrary.erase_all();
////
////      //}
////      //catch (...)
////      //{
////
////      //}
////
////      //if(g_pmapRTL)
////      //{
////
////      //   try
////      //   {
////
////      //      g_pmapRTL->erase_all();
////
////      //   }
////      //   catch(...)
////      //   {
////
////      //   }
////
////      //}
////
////      //if(g_pmapRTL)
////      //{
////
////      //   try
////      //   {
////
////      //      g_pmapRTL->erase_all();
////
////      //   }
////      //   catch(...)
////      //   {
////
////      //   }
////
////      //}
////
////      //::acme::del(::thread::g_pmutex);
////
////      //::acme::del(::thread::g_pthreadmap);
////
////      //::user::term_windowing();
////
////      //g_bApex = 0;
////
////      //::acme::del(g_papexstrpool);
////
////      //::channel::s_pmutexChannel.release();
////
////      //::acme::del(g_pmapRTL);
//////
//////#if defined(LINUX) || defined(__APPLE__)
//////
//////      ::acme::del(g_pmutexTz);
//////
//////#endif // defined(LINUX) || defined(__APPLE__)
//////
//////      ::acme::del(g_pmutexCred);
//////
//////      ::acme::del(g_pmutexMessageDispatch);
//////
//////      ::acme::del(g_pmutexUiDestroyed);
////
////      //del(g_pmapAura);
////
//////      if (g_paAura != nullptr)
//////      {
//////
//////         for (auto* po : *g_paAura)
//////         {
//////
//////            try
//////            {
//////
//////               ::acme::del(po);
//////
//////            }
//////            catch (...)
//////            {
//////
//////            }
//////
//////         }
//////
//////         ::acme::del(g_paAura);
//////
//////      }
////
//////#if OBJECT_TYPE_COUNTER
//////
//////      ::acme::del(g_pmapObjTypCtr);
//////
//////#endif
////
//////#if MEMDLEAK
//////
//////      memdleak_term();
//////
//////#endif
////
////      //::acme::del(g_pmutexSystemHeap);
////
////      //del(g_pmutexThreadOn);
////
////      //del(g_pmapThreadOn);
//////
//////#ifdef __APPLE__
//////
//////      ::acme::del(g_pmutexCvt);
//////
//////#endif
////
//////#ifdef BSD_STYLE_SOCKETS
//////
//////      ::acme::del(::sockets::base_socket::s_pmutex);
//////
//////#endif
////
////      //::acme::del(g_psimpletrace);
////
////      //::acme::del(g_pcsTrace);
////
//////#ifdef __ANDROID__
//////
//////      del(g_pmutexOutputDebugStringA);
//////
//////#endif
////
////////#if !defined(__MCRTDBG) && !MEMDLEAK
////////
////////      auto pheap = g_pheap;
////////
////////      g_pheap = nullptr;
////////
////////      ::acme::del(pheap);
////////
////////#endif
////
////      //::acme::del(g_pcsGlobal);
////
////      //::acme::del(g_pmutexChildren);
////
////      //::acme::del(get_globals_mutex());
////
//////#if MEMDLEAK
//////
//////      ::set_thread(nullptr);
//////
//////#ifdef __USE_BFD
//////
//////      init_resolve_addr_file_func_line();
//////
//////#endif
//////
//////      memdleak_dump();
//////
//////#endif
//////
//////#ifndef WINDOWS
//////
//////      ::acme::free(g_pszDemangle);
//////
//////#endif
//////
//////#ifndef WINDOWS
//////
//////      ::acme::del(g_pcsDemangle);
//////
//////#endif
////
//////#ifdef WINDOWS
//////      _free_locale(g_localeC);
//////#elif defined(__ANDROID__)
//////      //_freelocale(g_localeC);
//////#else
//////      freelocale(g_localeC);
//////#endif
////
////   }
//
//
////   void static_start::this_ref()
////   {
////
////      m_bRef = true;
////      //printf()
////
////   }
//
//
//   //::apex::system * apex_create_system(app_core * pappcore)
//   //{
//
//   //   auto psystem = ___new ::apex::system ();
//
//   //   psystem->initialize(nullptr);
//
//   //   return psystem;
//
//   //}
//
//
////
////   void static_start::init()
////   {
////
////      //::apex::static_start::init();
////
////      //if (!__node_apex_pre_init())
////      //{
////
////      //   return ::error_failed;
////
////      //}
////
////      ::parallelization::initialize();
////
////      //if (!__node_apex_pos_init())
////      //{
////
////      //   return ::error_failed;
////
////      //}
////
//////#ifdef WINDOWS
//////
//////      set_extended_output_debug_string_a();
//////
//////      set_extended_output_debug_string_w();
//////
//////#endif
////
////      //g_pfn_create_system = &apex_create_apex_system;
////
////      //return true;
////
////   }
//
//
//
//
////} // namespace static_start
//
//
//} // namespace apex
//

//static ::pointer< ::mutex > s_pmutexDraw2d = nullptr;
//
//CLASS_DECL_APEX ::pointer< ::mutex > draw2d_mutex()
//{
//
//   return s_pmutexDraw2d;
//
//}


//CLASS_DECL_APEX void init_draw2d_mutex()
//{
//
//   s_pmutexDraw2d = ___new ::pointer < ::mutex > ();
//
//}


//CLASS_DECL_APEX void terg_draw2d_mutex()
//{
//
//   ::acme::del(s_pmutexDraw2d);
//
//}


//
//CLASS_DECL_APEX ::pointer< ::mutex > get_cred_mutex()
//{
//
//   return ::apex::g_pmutexCred;
//
//}
//
//
//
//
//


//level * apex_level::s_plevel = nullptr;

//apex_level apexlevelAura(::apex_level::level_apex, &defer_apex_init);


//
//CLASS_DECL_APEX ::color::color dk_red() // <3 tbs
//{
//   return argb(255, 200, 16, 46);
//}


//thread_int_ptr < void    > t_estatus;


//CLASS_DECL_APEX void set_last_status(const ::e_status & estatus)
//{
//
//   ::get_task()->m_estatus = estatus;
//
//}


//CLASS_DECL_APEX void  get_last_status()
//{
//
//   return ::get_task()->m_estatus;
//
//}




//apex_level apexlevelAxis(::apex_level::level_axis, &defer_axis_init);
//
//namespace axis
//{
//
//
//   namespace static_start
//   {
//
//
//      CLASS_DECL_APEX void init()
//      {
//
//         xxdebug_box("axis.dll axis_static_start (0)", "box", e_message_box_ok);

//         sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

//#if defined(LINUX)
//
//         //         set_defer_process_x_message(&axis_defer_process_x_message);
//
//         //         set_TranslateMessage(&axis_TranslateMessage);
//         //
//         //         set_DispatchMessage(&axis_DispatchMessage);
//         //
//         //         oswindow_data::s_pdataptra = ___new oswindow_dataptra();
//         //
//         //         oswindow_data::s_pmutex = aaa_memory_new ::pointer < ::mutex >;
//         //
//         //         osdisplay_data::s_pdataptra = ___new osdisplay_dataptra();
//         //
//         //         osdisplay_data::s_pmutex = aaa_memory_new ::pointer < ::mutex >;
//
//#endif // defined(LINUX)
//
//
//
//      }
//
//
//








































//
//
//
//      CLASS_DECL_APEX void term()
//      {
//
//         //#if defined(LINUX)
//         //
//         //         delete osdisplay_data::s_pmutex;
//         //
//         //         osdisplay_data::s_pmutex = nullptr;
//         //
//         //         delete osdisplay_data::s_pdataptra;
//         //
//         //         osdisplay_data::s_pdataptra = nullptr;
//         //
//         //         delete oswindow_data::s_pmutex;
//         //
//         //         oswindow_data::s_pmutex = nullptr;
//         //
//         //         delete oswindow_data::s_pdataptra;
//         //
//         //         oswindow_data::s_pdataptra = nullptr;
//         //
//         //#endif // defined(LINUX)
//
//
//
//
//      }
//
//
//
//   } // namespace static_start
//
//
//} // namespace axis
//
//
//
//
//




// apex_level apexlevelCore(::apex_level::level_core, &defer_apex_init);


//#ifdef __ANDROID__
//
//
//struct lconv* g_plconv = nullptr;
//
//
//#endif
//
//
//namespace apex
//{
//
//
//
//   namespace static_start
//   {
//
////
////      CLASS_DECL_APEX void init()
////      {
////
////         xxdebug_box("apex.dll base_static_start (0)", "box", e_message_box_ok);
////
////         //#ifdef __ANDROID__
////         //
////         //
////         //         g_plconv = ___new lconv();
////         //
////         //         g_plconv->decimal_point = strdup(".");
////         //
////         //         //oswindow_data::s_pdataptra = ___new oswindow_dataptra();
////         //
////         //         //oswindow_data::s_pmutex = aaa_memory_new ::pointer < ::mutex >;
////         //
////         //#endif
////
////         //#if defined(__APPLE__)
////         //
////         //         g_poswindowdataptra = ___new oswindow_dataptra();
////         //
////         //         g_poswindowdataptra->defer_create_synchronization();
////         //
////         //#endif // defined(__APPLE__)
////
////
////      }
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//










//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//      CLASS_DECL_APEX void term()
//      {
//
//
//         //#if defined(__APPLE__)
//         //
//         //         delete g_poswindowdataptra;
//         //
//         //         g_poswindowdataptra = nullptr;
//         //
//         //#endif // defined(__APPLE__)
//
//
//
//
//
//
//      }
//
//
//
//   } // namespace static_start
//
//
//} // namespace berg
//
//
//
//
//


//
//void apex_ref()
//{
//
//
//   ::apex::static_start::g_pstaticstatic->this_ref();
//   set_platform_level(e_platform_level_apex);
//
//
//}
//
//






