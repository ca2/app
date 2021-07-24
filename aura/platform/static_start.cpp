#include "framework.h"
#include "static_start.h"
#include "apex/net/sockets/_.h"
#include "acme/memory/plex_heap1.h"
#include "acme/memory/plex_heap_impl1.h"
#include "apex/platform/app_core.h"
#include "acme/primitive/primitive/malloc.h"
#include "aura/astr.h"
#include "acme/platform/static_start_internal.h"
//#include "aura/os/_os.h"
//
//#include <sqlite3.h>

#ifdef RASPBIAN
#define PLATFORM_NAMESPACE linux
#endif

#if defined(__APPLE__)
#include <xlocale.h>
#else
#include <locale.h>
#endif

//#ifdef LINUX
//#include <glib.h> // sudo apt-get install libglib2.0-dev
//#endif



#ifdef LINUX
//#include <glib.h> // sudo apt-get install libglib2.0-dev


//void x11_hook_init();
//void x11_hook_term();


#endif

void trace_category_static_init();
void trace_category_static_term();


//extern thread_local ::task_pointer t_pthread;


#undef new


//#ifdef LINUX
//static void
//log_handler (const gchar   *log_domain,
//             GLogLevelFlags log_level,
//             const gchar   *message,
//             gpointer       user_data)
//{
//   g_log_default_handler (log_domain, log_level, message, user_data);
//
//   g_on_error_query (nullptr);
//}
//
//
//#endif


namespace aura
{

   // aura commented
//#if OBJECT_TYPE_COUNTER
//
//   map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;
//
//#endif
//

   //critical_section* g_pcsRefDbg;
   bool g_bAura;

   // aura commented
//#if OBJECT_TYPE_COUNTER
//
//   int g_iObjTypCtrInit;
//
//#endif

   CLASS_DECL_AURA critical_section * g_pcsFont = nullptr;

   CLASS_DECL_AURA ::mutex * g_pmutexWindowing = nullptr;

   CLASS_DECL_AURA string_map < int_to_string > * g_pmapFontFaceName = nullptr;

   ::mutex * g_pmutexChildren;
   ::mutex * g_pmutexThreadWaitClose;
   //string_map < __pointer(::acme::library) >* g_pmapLibrary;
   //string_map < PFN_NEW_AURA_LIBRARY >* g_pmapNewAuraLibrary;


#if !defined(WINDOWS)

//void windows10_init();
//#ifdef WINDOWS

//
//   void set_simple_output_debug_string_a();
//
//   void set_extended_output_debug_string_a();
//
//   void set_simple_output_debug_string_w();
//
//   void set_extended_output_debug_string_w();
//
//
//   //#endif
//
//#else

   //DWORD_PTR g_tlsindexLastError;
   char* g_pszDemangle;
   critical_section* g_pcsDemangle;

#endif


   //::mutex * psystem->g_mutexLibrary;

   //__LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

   //::mutex * g_pmutexGlobals;

   //critical_section* g_pcsGlobal;

   //bool g_bOutputDebugString;

   //critical_section* g_pcsTrace;

   //::matter* g_ptrace;

   //simple_trace* g_psimpletrace;
   // aura commented
//#ifdef __APPLE__
//
//   // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
//   // http://stackoverflow.com/users/346736/jbenet
//
//   //#include <mach/clock.h>
//   //#include <mach/mach.h>
//#include <mach/mach_time.h>
//
////clock_serv_t   g_cclock;
//   double g_machtime_conversion_factor;
//   //   clock_get_time(cclock, &mts);
//
//#endif


   //::mutex * g_pmutexCred;


   //class ::exception_engine* g_pexceptionengine;

   ::mutex * g_pmutexMessageDispatch;


   //array < matter* >* g_paAura;


   //::map < ::id, const ::id&, ::id, const ::id& >* g_pmapRTL;

   //plex_heap_alloc_array* g_pheap;

   //critical_section* g_pmutexSystemHeap;

#if defined(WINDOWS)

   _locale_t g_localeC;

#else

   locale_t g_localeC;

#endif

   //map < itask_t, itask_t, itask_t, itask_t > * g_pmapThreadOn;

   // aura commented
//#ifdef WINDOWS
//
//   LARGE_INTEGER g_largeintegerFrequency;
//
//#endif

   // aura commented
   //i64 g_iFirstNano;

   //plex_heap_alloc_array * g_pplexheapallocarray;

   // aura commented
   //int g_iMemoryCountersStartable;
   //::mutex * g_pmutexTrait;
   //::mutex * g_pmutexFactory;

   // aura commented
   ::mutex * g_pmutexUiDestroyed;

//#ifdef ANDROID
//
//   ::mutex * g_pmutexOutputDebugStringA;
//
//#endif

   //CLASS_DECL_AURA aura_str_pool* g_paurastrpool;

   // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   // ::mutex * g_pmutexMq;

   // #endif

//#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)
//
////::mutex * g_pmutexThreadIdHandleLock;
//
////::mutex * g_pmutexThreadIdLock;
//
////#if !defined(_UWP)
//
////::mutex * g_pmutexPendingThreadsLock;
//
////#endif
//
////::mutex * g_pmutexTlsData;
//
//#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)


//#if defined(LINUX) || defined(__APPLE__)
//
//
//   ::mutex * g_pmutexTz;
//
//   ::mutex * g_pmutexThreadHandleLock;
//
//
//#endif // defined(LINUX) || defined(__APPLE__)
//
//
//#ifdef __APPLE__
//
//
//   ::mutex * g_pmutexCvt;
//
//
//#endif

//
//   critical_section g_csRefDbg;
//


   void aura::construct()
   {

      g_bAura = 0;

#if OBJECT_TYPE_COUNTER

      g_pmapObjTypCtr = nullptr;

#endif

      g_bAura = false;

#if OBJECT_TYPE_COUNTER

      g_iObjTypCtrInit = 0;

#endif

      g_pmutexChildren = nullptr;

      g_pmutexThreadWaitClose = nullptr;

#if !defined(WINDOWS)

      //g_tlsindexLastError = 0;

      g_pszDemangle = nullptr;

      g_pcsDemangle = nullptr;

#endif

      //g_main_deferred_run = nullptr;

      //g_pmutexGlobals = nullptr;

//      g_pcsGlobal = nullptr;

      //g_bOutputDebugString = true;

      //g_pcsTrace = nullptr;

      //g_ptrace = nullptr;

      //g_psimpletrace = nullptr;

//#ifdef __APPLE__
//
//      // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
//      // http://stackoverflow.com/users/346736/jbenet
//
//      //#include <mach/clock.h>
//      //#include <mach/mach.h>
//#include <mach/mach_time.h>
//
////clock_serv_t   g_cclock;
//      g_machtime_conversion_factor = 0.0;
//      //   clock_get_time(cclock, &mts);
//
//#endif

      //g_pmutexCred = nullptr;

      //g_pexceptionengine = nullptr;
      //g_pmutexMessageDispatch = nullptr;

//      g_paAura = nullptr;

      //g_pmapRTL = nullptr;

      //::map < void *, void *,::aura::application *, ::aura::application * > * g_pmapAura;

      //string_map < __pointer(::acme::library) > * g_pmapLibCall;

      //g_pheap = nullptr;

      //g_pmutexSystemHeap = nullptr;

      //::mutex * g_pmutexThreadOn;

//#if defined(WINDOWS)
//
//      g_localeC = 0;
//
//#else
//
//      g_localeC = 0;
//
//#endif

      //map < itask_t, itask_t, itask_t, itask_t > * g_pmapThreadOn;

//#ifdef WINDOWS
//
//      g_largeintegerFrequency = {};
//
//#endif
//
//      g_iFirstNano = 0;

      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;

      //g_iMemoryCountersStartable = 0;
      //::mutex * g_pmutexTrait;
      //::mutex * g_pmutexFactory;

      g_pmutexUiDestroyed = 0;

//#ifdef ANDROID
//
//      g_pmutexOutputDebugStringA = 0;
//
//#endif

      //g_paurastrpool = nullptr;

      // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      // ::mutex * g_pmutexMq;

      // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(_UWP) || defined(ANDROID)

//::mutex * g_pmutexThreadIdHandleLock;

//::mutex * g_pmutexThreadIdLock;

//#if !defined(_UWP)

//::mutex * g_pmutexPendingThreadsLock;

//#endif

//::mutex * g_pmutexTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(_UWP)

//#if defined(LINUX) || defined(__APPLE__)
//
//      g_pmutexTz = nullptr;
//
//      g_pmutexThreadHandleLock = nullptr;
//
//#endif // defined(LINUX) || defined(__APPLE__)


//#ifdef __APPLE__
//
//
//      g_pmutexCvt = nullptr;
//
//
//#endif

      g_pcsFont = nullptr;

      g_pmapFontFaceName = nullptr;

      g_pmutexWindowing = nullptr;



   }


   aura::aura()
   {

      m_bRef = false;

      construct();

      //g_pcsRefDbg = nullptr;


#if defined(WINDOWS)

      g_localeC = _wcreate_locale(LC_ALL, L"C");

#elif defined(__APPLE__)

      g_localeC = newlocale(LC_ALL, "C", NULL);

#else

      g_localeC = newlocale(LC_ALL_MASK, "C", NULL);

#endif

#ifndef WINDOWS

      g_pcsDemangle = new critical_section;

#endif

      //g_pcsTrace = new critical_section;

//#ifdef WINDOWS

//#ifdef WINDOWS_DESKTOP
//
//      SetThreadLocale(65001);
//
//      ::SetConsoleOutputCP(65001);
//
//#endif

      //::QueryPerformanceFrequency(&g_largeintegerFrequency);

//#elif defined(__APPLE__)
//
//      {
//
//         mach_timebase_info_data_t timebase;
//
//         mach_timebase_info(&timebase);
//
//         g_machtime_conversion_factor = (double)timebase.numer / (double)timebase.denom;
//
//      }
//
//#endif

      //g_iFirstNano = get_nanos();

      //xxdebug_box("aura.dll base_static_start (0)", "box", e_message_box_ok);

      //g_pexceptionengine = new ::PLATFORM_NAMESPACE::exception_engine();

      //g_pmutexGlobals = new ::mutex();

      g_pmutexChildren = new ::mutex();

      //g_pcsGlobal = new critical_section();

//#ifndef __MCRTDBG
//
//      g_pheap = new plex_heap_alloc_array();
//
//#endif

      //::id_space::s_pidspace = new id_space();

      //init_id_pool();

//#ifdef ANDROID
//
//      g_pmutexOutputDebugStringA = new ::mutex();
//
//#endif

#if OBJECT_TYPE_COUNTER

      g_pmapObjTypCtr = new map < const char*, const char*, ::i64, ::i64 >;

#endif

      //trace_category_static_init();

      //g_psimpletrace = new simple_trace;

      //g_ptrace = g_psimpletrace;

//#ifdef BSD_STYLE_SOCKETS
//
//      ::sockets::base_socket::s_pmutex = new ::mutex();
//
//#endif

//
//#ifdef __APPLE__
//
//      g_pmutexCvt = new ::mutex();
//
//#endif

      g_pmutexThreadWaitClose = new ::mutex();

      //g_pmutexThreadOn = new ::mutex();

      //g_pmapThreadOn = new ::map < itask_t, itask_t, itask_t, itask_t >;

      //g_pmutexSystemHeap = new critical_section();

#if MEMDLEAK

      memdleak_init();

#endif

      //::factory::factory_init();

      //g_paAura = new array < matter * >;

      //g_pmapAura =new ::map < void *,void *,::aura::application *,::aura::application * >;

      g_pmutexUiDestroyed = new ::mutex();

      g_pmutexMessageDispatch = new ::mutex();

      //g_pmutexCred = new ::mutex();

//#if defined(LINUX) || defined(__APPLE__)
//
//      g_pmutexTz = new ::mutex();
//
//#endif // defined(LINUX) || defined(__APPLE__)

      //g_pmapRTL = nullptr;

      //psystem->g_mutexLibrary = new ::mutex;

      //g_pmapLibrary = new string_map < __pointer(::acme::library) >();

      //g_pmapNewAuraLibrary = new string_map < PFN_NEW_AURA_LIBRARY >();

//#ifndef _UWP
//
//      br_init(nullptr);
//
//#endif

      // Only draw2d implementations needing "big" synch should init_draw2d_mutex();
      // init_draw2d_mutex();

#ifdef MACOS

      //mach_port_deallocate(mach_task_self(), g_cclock);

#endif

#ifdef PRIMITIVE_DEBUG

      aura_auto_debug_teste();

#endif

      //g_pmapLibCall = new string_map < __pointer(::acme::library) >();

#ifdef MEMORY_COUNTERS

      g_iMemoryCountersStartable = 1;

#else

      //g_iMemoryCountersStartable = 0;

#endif

      //sqlite3_config(SQLITE_CONFIG_MULTITHREAD);

      __construct_new(::channel::s_pmutexChannel);

      //g_paurastrpool = new aura_str_pool();

      ::user::init_windowing();

      //g_pcsRefDbg = new critical_section();

      g_bAura = 1;

      //::thread::g_pmutex = new mutex();

      //::thread::g_pthreadmap = new ::thread_map();

      create_factory < ::aura::context >();


#if OBJECT_TYPE_COUNTER
      g_iObjTypCtrInit = 1;
#endif


//#ifdef LINUX
//
//     x11_hook_init();
//
//#endif

      g_pcsFont = new critical_section();

      g_pmapFontFaceName = new string_map < i32_map < string > >();

      g_pmutexWindowing = new mutex();

      init();

   }


   aura::~aura()
   {

//#ifdef LINUX
//
//     x11_hook_term();
//
//#endif


      term();

      ::acme::del(g_pmutexWindowing);

      ::acme::del(g_pmapFontFaceName);

      ::acme::del(g_pcsFont);

#if OBJECT_TYPE_COUNTER
      g_iObjTypCtrInit = 0;
#endif

      //::release(t_pthread);

      // if(g_pmapAura)
      // {

      //    try
      //    {

      //       g_pmapAura->erase_all();

      //    }
      //    catch(...)
      //    {

      //    }

      // }

      //try
      //{

      //   synchronous_lock synchronouslock(psystem->g_mutexLibrary);

      //   g_pmapLibCall->erase_all();


      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   synchronous_lock synchronouslock(psystem->g_mutexLibrary);

      //   psystem->g_mapLibrary.erase_all();

      //}
      //catch (...)
      //{

      //}

      //if(g_pmapRTL)
      //{

      //   try
      //   {

      //      g_pmapRTL->erase_all();

      //   }
      //   catch(...)
      //   {

      //   }

      //}

      //if(g_pmapRTL)
      //{

      //   try
      //   {

      //      g_pmapRTL->erase_all();

      //   }
      //   catch(...)
      //   {

      //   }

      //}

      //::acme::del(::thread::g_pmutex);

      //::acme::del(::thread::g_pthreadmap);

      ::user::term_windowing();

      g_bAura = 0;

      //::acme::del(g_paurastrpool);

      //::channel::s_pmutexChannel.release();

      //g_ptrace = g_psimpletrace;

      //del(g_pmapRTL);

//#if defined(LINUX) || defined(__APPLE__)
//
//      ::acme::del(g_pmutexTz);
//
//#endif // defined(LINUX) || defined(__APPLE__)

//      ::acme::del(g_pmutexCred);

      ::acme::del(g_pmutexMessageDispatch);

      ::acme::del(g_pmutexUiDestroyed);

      //del(g_pmapAura);

      //if (g_paAura != nullptr)
      //{

      //   for (auto* po : *g_paAura)
      //   {

      //      try
      //      {

      //         ::acme::del(po);

      //      }
      //      catch (...)
      //      {

      //      }

      //   }

      //   ::acme::del(g_paAura);

      //}



      //del(g_pmapLibCall);

      //del(g_pmapLibrary);

      //del(g_pmapNewAuraLibrary);

      //del(psystem->g_mutexLibrary);

      trace_category_static_term();

#if OBJECT_TYPE_COUNTER

      ::acme::del(g_pmapObjTypCtr);

#endif

#if MEMDLEAK

      memdleak_term();

#endif

      //::acme::del(g_pmutexSystemHeap);

      //del(g_pmutexThreadOn);

      //del(g_pmapThreadOn);

      ::acme::del(g_pmutexThreadWaitClose);

//#ifdef __APPLE__
//
//      ::acme::del(g_pmutexCvt);
//
//#endif

//#ifdef BSD_STYLE_SOCKETS
//
//      ::acme::del(::sockets::base_socket::s_pmutex);
//
//#endif

      //::acme::del(g_psimpletrace);

      //::acme::del(g_pcsTrace);

      trace_category_static_term();

//#ifdef ANDROID
//
//      del(g_pmutexOutputDebugStringA);
//
//#endif

      //term_id_pool();

      //del(::id_space::s_pidspace);

//#if !defined(__MCRTDBG) && !MEMDLEAK
//
//      auto pheap = g_pheap;
//
//      g_pheap = nullptr;
//
//      del(pheap);
//
//#endif

      //del(g_pcsGlobal);

      ::acme::del(g_pmutexChildren);

      //del(g_pmutexGlobals);

//#if MEMDLEAK
//
//      ::set_thread(nullptr);
//
//#ifdef __USE_BFD

//      init_resolve_addr_file_func_line();
//
//#endif
//
//      memdleak_dump();
//
//#endif

#ifndef WINDOWS

      ::acme::free(g_pszDemangle);

#endif

#ifndef WINDOWS

      ::acme::del(g_pcsDemangle);

#endif

#ifdef WINDOWS
      _free_locale(g_localeC);
#elif defined(ANDROID)
      //_freelocale(g_localeC);
#else
      freelocale(g_localeC);
#endif

   }


   void aura::this_ref()
   {

      m_bRef = true;
      //printf()

   }


   //::aura::system * aura_create_system(app_core * pappcore)
   //{

   //   auto psystem = new ::aura::system();

   //   psystem->initialize(nullptr);

   //   return psystem;

   //}



   ::e_status aura::init()
   {

      //::aura::static_start::init();

      if (!__node_aura_pre_init())
      {

         return ::error_failed;

      }

      ::parallelization::initialize();

      if (!__node_aura_pos_init())
      {

         return ::error_failed;

      }

#ifdef WINDOWS

      ::acme::set_extended_output_debug_string_a();

      ::acme::set_extended_output_debug_string_w();

#endif

      //g_pfn_create_system = &aura_create_aura_system;

      return true;

   }


   ::e_status aura::term()
   {

      //::parallelization::wait_threads(1_min);

      //if (g_axisontermthread)
      //{

      //   g_axisontermthread();

      //}

      on_term_thread();

      ::parallelization::finalize();

      __node_aura_pre_term();

#ifdef WINDOWS

      ::acme::set_simple_output_debug_string_a();

      ::acme::set_simple_output_debug_string_w();

#endif

      processor_cache_oriented_destroy_all_memory_pools();

      __node_aura_pos_term();

      //::aura::static_start::term();

      //return true;

      return ::success;

   }


//} // namespace static_start


} // namespace aura


//static ::mutex * s_pmutexDraw2d = nullptr;
//
//CLASS_DECL_AURA ::mutex * draw2d_mutex()
//{
//
//   return s_pmutexDraw2d;
//
//}


//CLASS_DECL_AURA void init_draw2d_mutex()
//{
//
//   s_pmutexDraw2d = new ::mutex();
//
//}


//CLASS_DECL_AURA void terg_draw2d_mutex()
//{
//
//   ::acme::del(s_pmutexDraw2d);
//
//}



//CLASS_DECL_AURA ::mutex * get_cred_mutex()
//{
//
//   return ::aura::g_pmutexCred;
//
//}







//level * aura_level::s_plevel = nullptr;

//aura_level auralevelAura(::aura_level::level_aura, &defer_aura_init);



//CLASS_DECL_AURA ::color::color dk_red() // <3 tbs
//{
//   return argb(255, 200, 16, 46);
//}


//thread_int_ptr < ::e_status    > t_estatus;


//CLASS_DECL_AURA void set_last_status(const ::e_status & estatus)
//{
//
//   ::get_task()->m_estatus = estatus;
//
//}


//CLASS_DECL_AURA ::e_status  get_last_status()
//{
//
//   return ::get_task()->m_estatus;
//
//}




//aura_level auralevelAxis(::aura_level::level_axis, &defer_axis_init);
//
//namespace axis
//{
//
//
//   namespace static_start
//   {
//
//
//      CLASS_DECL_AURA void init()
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
//         //         oswindow_data::s_pdataptra = new oswindow_dataptra;
//         //
//         //         oswindow_data::s_pmutex = new ::mutex;
//         //
//         //         osdisplay_data::s_pdataptra = new osdisplay_dataptra;
//         //
//         //         osdisplay_data::s_pmutex = new ::mutex;
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
//      CLASS_DECL_AURA void term()
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

//#ifdef WINDOWS
//_locale_t get_c_locale()
//#else
//locale_t get_c_locale()
//#endif
//{
//
//   return ::aura::g_localeC;
//
//}




// aura_level auralevelCore(::aura_level::level_core, &defer_aura_init);


//#ifdef ANDROID
//
//
//struct lconv* g_plconv = nullptr;
//
//
//#endif
//
//
//namespace aura
//{
//
//
//
//   namespace static_start
//   {
//
////
////      CLASS_DECL_AURA void init()
////      {
////
////         xxdebug_box("aura.dll base_static_start (0)", "box", e_message_box_ok);
////
////         //#ifdef ANDROID
////         //
////         //
////         //         g_plconv = new lconv;
////         //
////         //         g_plconv->decimal_point = strdup(".");
////         //
////         //         //oswindow_data::s_pdataptra = new oswindow_dataptra;
////         //
////         //         //oswindow_data::s_pmutex = new ::mutex;
////         //
////         //#endif
////
////         //#if defined(APPLEOS)
////         //
////         //         g_poswindowdataptra = new oswindow_dataptra;
////         //
////         //         g_poswindowdataptra->defer_create_mutex();
////         //
////         //#endif // defined(APPLEOS)
////
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
//      CLASS_DECL_AURA void term()
//      {
//
//
//         //#if defined(APPLEOS)
//         //
//         //         delete g_poswindowdataptra;
//         //
//         //         g_poswindowdataptra = nullptr;
//         //
//         //#endif // defined(APPLEOS)
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
//} // namespace base
//
//
//
//
//



void aura_ref()
{


   ::aura::aura::g_aura.this_ref();
   set_platform_level(e_platform_level_aura);


}



