#include "framework.h"
#include "acme/operating_system.h"
#include "static_start.h"
#include "acme/memory/plex_heap1.h"
#include "acme/memory/plex_heap_impl1.h"
#include "acme/primitive/primitive/malloc.h"
#include "acme/astr.h"
#include "acme/platform/simple_trace.h"


#ifdef WINDOWS

LARGE_INTEGER g_largeintegerFrequency;


#endif

#ifdef WINDOWS_DESKTOP

#include "acme/os/windows/callstack.h"

#endif

::array < ::routine > * g_proutineaOsTerm;

extern natural_meta_data < string_meta_data < ansichar > > * g_pansistringNil;

extern natural_meta_data < string_meta_data < wd16char > > * g_pwd16stringNil;

extern natural_meta_data < string_meta_data < wd32char > > * g_pwd32stringNil;


static void delete_all_release_on_end();

void os_term_run_routinea();


enum_platform_level g_eplatformlevel = ::e_platform_level_acme;


CLASS_DECL_ACME void set_platform_level(enum_platform_level eplatformlevel)
{

   g_eplatformlevel = eplatformlevel;

}


CLASS_DECL_ACME enum_platform_level get_platform_level()
{

   return g_eplatformlevel;

}


void __node_acme_factory_exchange(::factory_map * pfactorymap);


CLASS_DECL_ACME void __seed_srand();


void initialize_global_message_queue();
void finalize_global_message_queue();


#undef new


#ifdef RASPBIAN
#define PLATFORM_NAMESPACE linux
#endif


#if defined(__APPLE__)
#include <xlocale.h>
#else
#include <locale.h>
#endif


#ifdef LINUX
//#include <glib.h> // sudo apt-get install libglib2.0-dev


//!!!void x11_hook_init();
//!!!void x11_hook_term();


#endif


CLASS_DECL_ACME void trace_category_static_init();
CLASS_DECL_ACME void trace_category_static_term();


extern thread_local __pointer(::thread) t_pthread;


namespace acme
{


   static element_address_array* g_pelementaddraReleaseOnEnd;


#if OBJ_TYP_CTR

   map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;

#endif


   bool g_bAcme;


#if OBJ_TYP_CTR

   int g_iObjTypCtrInit;

#endif

   //CLASS_DECL_ACME critical_section* g_pcsFont = nullptr;

   //CLASS_DECL_ACME string_map < int_to_string > * g_pmapFontFaceName = nullptr;

   ::mutex * g_pmutexChildren;
   ::mutex * g_pmutexThreadWaitClose;


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


   //::mutex * &System.g_mutexLibrary;

   //__LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

   ::mutex * g_pmutexGlobals;

   critical_section* g_pcsGlobal;

   bool g_bOutputDebugString;

   critical_section * g_pcsTrace;

   ::matter * g_ptrace;

   simple_trace * g_psimpletrace;

   //critical_section* g_pcsTrace;

   // acme commented
   //::matter* g_ptrace;

   // acme commented
   //simple_trace* g_psimpletrace;

#ifdef __APPLE__

   // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
   // http://stackoverflow.com/users/346736/jbenet

   //#include <mach/clock.h>
   //#include <mach/mach.h>
#include <mach/mach_time.h>

//clock_serv_t   g_cclock;
   double g_machtime_conversion_factor;
   //   clock_get_time(cclock, &mts);

#endif


   //::mutex * g_pmutexCred;


   class ::exception_engine* g_pexceptionengine;

   ::mutex * g_pmutexMessageDispatch;


   array < matter* >* g_paAura;


   //::map < ::id, const ::id&, ::id, const ::id& >* g_pmapRTL;

   plex_heap_alloc_array* g_pheap;

   critical_section* g_pmutexSystemHeap;

#if defined(WINDOWS)

   _locale_t g_localeC;

#else

   locale_t g_localeC;

#endif

   //map < ithread_t, ithread_t, ithread_t, ithread_t > * g_pmapThreadOn;



   i64 g_iFirstNano;

   //plex_heap_alloc_array * g_pplexheapallocarray;

   int g_iMemoryCountersStartable;
   //::mutex * g_pmutexTrait;
   //::mutex * g_pmutexFactory;

   ::mutex * g_pmutexUiDestroyed;

#ifdef ANDROID

   ::mutex * g_pmutexOutputDebugStringA;

#endif

   CLASS_DECL_ACME acme_str_pool* g_pacmestrpool;

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


#if defined(LINUX) || defined(__APPLE__)


   ::mutex * g_pmutexTz;

   ::mutex * g_pmutexThreadHandleLock;


#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


   ::mutex * g_pmutexCvt;


#endif


   critical_section g_csRefDbg;



   void acme::construct()
   {

      __seed_srand();

      g_bAcme = 0;

#if OBJ_TYP_CTR

      g_pmapObjTypCtr = nullptr;

#endif

      g_bAcme = false;

#if OBJ_TYP_CTR

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

      g_pmutexGlobals = nullptr;

      g_pcsGlobal = nullptr;

      g_bOutputDebugString = true;

      g_pcsTrace = nullptr;

      g_ptrace = nullptr;

      g_psimpletrace = nullptr;

      //g_pcsTrace = nullptr;

      // acme commented
      //g_ptrace = nullptr;

      // acme commented
      //g_psimpletrace = nullptr;

#ifdef __APPLE__

      // http://stackoverflow.com/questions/5167269/clock-gettime-alternative-in-mac-os-x
      // http://stackoverflow.com/users/346736/jbenet

      //#include <mach/clock.h>
      //#include <mach/mach.h>
#include <mach/mach_time.h>

//clock_serv_t   g_cclock;
      g_machtime_conversion_factor = 0.0;
      //   clock_get_time(cclock, &mts);

#endif

      //g_pmutexCred = nullptr;

      g_pexceptionengine = nullptr;
      g_pmutexMessageDispatch = nullptr;

      g_paAura = nullptr;

      //g_pmapRTL = nullptr;

      //::map < void *, void *,::acme::application *, ::acme::application * > * g_pmapAura;

      //string_map < __pointer(::acme::library) > * g_pmapLibCall;

      g_pheap = nullptr;

      g_pmutexSystemHeap = nullptr;

      //::mutex * g_pmutexThreadOn;

#if defined(WINDOWS)

      g_localeC = 0;

#else

      g_localeC = 0;

#endif

      //map < ithread_t, ithread_t, ithread_t, ithread_t > * g_pmapThreadOn;

#ifdef WINDOWS

      g_largeintegerFrequency = {};

#endif

      g_iFirstNano = 0;

      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;

      g_iMemoryCountersStartable = 0;
      //::mutex * g_pmutexTrait;
      //::mutex * g_pmutexFactory;

      g_pmutexUiDestroyed = 0;

#ifdef ANDROID

      g_pmutexOutputDebugStringA = 0;

#endif

      g_pacmestrpool = nullptr;

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

#if defined(LINUX) || defined(__APPLE__)

      g_pmutexTz = nullptr;

      g_pmutexThreadHandleLock = nullptr;

#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


      g_pmutexCvt = nullptr;


#endif

      //g_pcsFont = nullptr;

      //g_pmapFontFaceName = nullptr;



   }


   acme::acme()
   {

      static natural_meta_data < string_meta_data < ansichar > > s_ansistringNil;

      static natural_meta_data < string_meta_data < wd16char > > s_wd16stringNil;

      static natural_meta_data < string_meta_data < wd32char > > s_wd32stringNil;

      ::g_pansistringNil = &s_ansistringNil;

      ::g_pwd16stringNil = &s_wd16stringNil;

      ::g_pwd32stringNil = &s_wd32stringNil;

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

#ifdef WINDOWS

#ifdef WINDOWS_DESKTOP

      SetThreadLocale(65001);

      ::SetConsoleOutputCP(65001);

#endif

      ::QueryPerformanceFrequency(&g_largeintegerFrequency);

#elif defined(__APPLE__)

      {

         mach_timebase_info_data_t timebase;

         mach_timebase_info(&timebase);

         g_machtime_conversion_factor = (double)timebase.numer / (double)timebase.denom;

      }

#endif

      g_iFirstNano = get_nanos();

      //xxdebug_box("acme.dll base_static_start (0)", "box", e_message_box_ok);

      g_pexceptionengine = new ::PLATFORM_NAMESPACE::exception_engine();

      g_pmutexGlobals = new ::mutex();

      g_pmutexChildren = new ::mutex();

      g_pcsGlobal = new critical_section();

      ::initialize_future_critical_section();

#ifdef WINDOWS

      ::windows::callstack::s_pcriticalsection = new critical_section();

#endif

      //::update::g_pcs = new critical_section();

#ifndef __MCRTDBG

      g_pheap = new plex_heap_alloc_array();

#endif

      ::id_space::s_pidspace = new id_space();

//      ::acme::idpool::init();

      initialize_global_message_queue();


#ifdef ANDROID

      g_pmutexOutputDebugStringA = new ::mutex();

#endif

#if OBJ_TYP_CTR

      g_pmapObjTypCtr = new map < const char*, const char*, ::i64, ::i64 >;

#endif

      trace_category_static_init();

      g_pcsTrace = new critical_section;

      g_psimpletrace = new simple_trace;

      g_ptrace = g_psimpletrace;


      // acme commented
      //g_psimpletrace = new simple_trace;

      //g_ptrace = g_psimpletrace;

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      ::sockets::base_socket::s_pmutex = new ::mutex();
//
//#endif


#ifdef __APPLE__

      g_pmutexCvt = new ::mutex();

#endif

      g_pmutexThreadWaitClose = new ::mutex();

      //g_pmutexThreadOn = new ::mutex();

      //g_pmapThreadOn = new ::map < ithread_t, ithread_t, ithread_t, ithread_t >;

      g_pmutexSystemHeap = new critical_section();

#if MEMDLEAK

      memdleak_init();

#endif

      ::factory::factory_init();

      g_paAura = new array < matter * >;

      //g_pmapAura =new ::map < void *,void *,::acme::application *,::acme::application * >;

      g_pmutexUiDestroyed = new ::mutex();

      g_pmutexMessageDispatch = new ::mutex();

      //g_pmutexCred = new ::mutex();

#if defined(LINUX) || defined(__APPLE__)

      g_pmutexTz = new ::mutex();

#endif // defined(LINUX) || defined(__APPLE__)

      //g_pmapRTL = nullptr;

      //&System.g_mutexLibrary = new ::mutex;

      //g_pmapLibrary = new string_map < __pointer(::acme::library) >();

      //g_pmapNewAuraLibrary = new string_map < PFN_NEW_ACME_LIBRARY >();

#ifdef LINUX

      br_init(nullptr);

#endif

      // Only draw2d implementations needing "big" synch should init_draw2d_mutex();
      // init_draw2d_mutex();

#ifdef MACOS

      //mach_port_deallocate(mach_task_self(), g_cclock);

#endif

#ifdef PRIMITIVE_DEBUG

      acme_auto_debug_teste();

#endif

      //g_pmapLibCall = new string_map < __pointer(::acme::library) >();

#ifdef MEMORY_COUNTERS

      g_iMemoryCountersStartable = 1;

#else

      g_iMemoryCountersStartable = 0;

#endif

      g_pacmestrpool = new acme_str_pool();

      //acme commented
      //::user::init_windowing();

      //g_pcsRefDbg = new critical_section();

      g_bAcme = 1;

      //::thread::g_pmutex = new mutex();

      //::thread::g_pthreadmap = new ::thread_map();

      // acme commented
      //create_factory < ::context >();


#if OBJ_TYP_CTR
      g_iObjTypCtrInit = 1;
#endif

      //g_pcsFont = new critical_section();

      //g_pmapFontFaceName = new string_to_string();

      init();


      create_reusable_factory < manual_reset_event >();

#ifdef LINUX

//!!!      x11_hook_init();

#endif

   }


   acme::~acme()
   {

      ::user::os_term_theme_colors();

#ifdef LINUX

//!!!      x11_hook_term();

#endif

      term();

      //::acme::del(g_pmapFontFaceName);

      //::acme::del(g_pcsFont);

#if OBJ_TYP_CTR
      g_iObjTypCtrInit = 0;
#endif

      // acme commented
      //::release(t_pthread);

      // if(g_pmapAura)
      // {

      //    try
      //    {

      //       g_pmapAura->remove_all();

      //    }
      //    catch(...)
      //    {

      //    }

      // }

      //try
      //{

      //   synchronization_lock synchronizationlock(&System.g_mutexLibrary);

      //   g_pmapLibCall->remove_all();


      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   synchronization_lock synchronizationlock(&System.g_mutexLibrary);

      //   &System.g_mapLibrary.remove_all();

      //}
      //catch (...)
      //{

      //}

      /*if(g_pmapRTL)
      {

         try
         {

            g_pmapRTL->remove_all();

         }
         catch(...)
         {

         }

      }*/

      //if(g_pmapRTL)
      //{

      //   try
      //   {

      //      g_pmapRTL->remove_all();

      //   }
      //   catch(...)
      //   {

      //   }

      //}

      try
      {

         ::factory::factory_close();

      }
      catch (...)
      {

      }

      //::acme::del(::thread::g_pmutex);

      //::acme::del(::thread::g_pthreadmap);

      ////acme commented
      //::user::term_windowing();

      g_bAcme = 0;

      ::acme::del(g_pacmestrpool);



      // acme commented
      //g_ptrace = g_psimpletrace;

      g_ptrace = g_psimpletrace;

      //::acme::del(g_pmapRTL);

#if defined(LINUX) || defined(__APPLE__)

      ::acme::del(g_pmutexTz);

#endif // defined(LINUX) || defined(__APPLE__)

      //::acme::del(g_pmutexCred);

      ::acme::del(g_pmutexMessageDispatch);

      ::acme::del(g_pmutexUiDestroyed);

      //del(g_pmapAura);

      if (g_paAura != nullptr)
      {

         for (auto* po : *g_paAura)
         {

            try
            {

               ::acme::del(po);

            }
            catch (...)
            {

            }

         }

         ::acme::del(g_paAura);

      }

      try
      {

         ::factory::factory_term();

      }
      catch (...)
      {

      }

      //del(g_pmapLibCall);

      //del(g_pmapLibrary);

      //del(g_pmapNewAuraLibrary);

      //del(&System.g_mutexLibrary);

      //trace_category_static_term();

#if OBJ_TYP_CTR

      ::acme::del(g_pmapObjTypCtr);

#endif

#if MEMDLEAK

      memdleak_term();

#endif

      ::acme::del(g_pmutexSystemHeap);

      //::acme::del(g_pmutexThreadOn);

      //::acme::del(g_pmapThreadOn);

      ::acme::del(g_pmutexThreadWaitClose);

#ifdef __APPLE__

      ::acme::del(g_pmutexCvt);

#endif

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      del(::sockets::base_socket::s_pmutex);
//
//#endif

      // acme commented
      //::acme::del(g_psimpletrace);

      //::acme::del(g_pcsTrace);
      
      ::acme::del(g_psimpletrace);

      ::acme::del(g_pcsTrace);

      trace_category_static_term();

#ifdef ANDROID

      del(g_pmutexOutputDebugStringA);

#endif

      //term_id_pool();

      finalize_global_message_queue();

      ::acme::del(::id_space::s_pidspace);

#if !defined(__MCRTDBG) && !MEMDLEAK

      auto pheap = g_pheap;

      g_pheap = nullptr;

      ::acme::del(pheap);

#endif

      delete_all_release_on_end();

#ifdef WINDOWS

      ::acme::del(::windows::callstack::s_pcriticalsection);

#endif

      ::initialize_future_critical_section();

      ::acme::del(g_pcsGlobal);

      ::acme::del(g_pmutexChildren);

      ::acme::del(g_pmutexGlobals);

#if MEMDLEAK

      ::set_thread(nullptr);

#ifdef __USE_BFD

      init_resolve_addr_file_func_line();

#endif

      memdleak_dump();

#endif

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


   void acme::this_ref()
   {

      m_bRef = true;
      //printf()

   }


   //::acme::system * acme_create_system(app_core * pappcore)
   //{

   //   auto psystem = new ::acme::system();

   //   psystem->initialize(nullptr);

   //   return psystem;

   //}



   ::e_status acme::init()
   {

      //::acme::static_start::init();

      if (!__node_acme_pre_init())
      {

         return ::error_failed;

      }

      // acme commented for apex
      //::parallelization::init_multithreading();

      if (!__node_acme_pos_init())
      {

         return ::error_failed;

      }

#ifdef WINDOWS

      set_extended_output_debug_string_a();

      set_extended_output_debug_string_w();

#endif

      create_factory < ::stdio_file >();

      __node_acme_factory_exchange(::factory::get_factory_map());

      return true;

   }


   ::e_status acme::term()
   {

      //::parallelization::wait_threads(1_min);

      //if (g_axisontermthread)
      //{

      //   g_axisontermthread();

      //}

      // acme commented for apex
      //on_term_thread();

      // acme commented for apex
      //::parallelization::term_multithreading();

      __node_acme_pre_term();

#ifdef WINDOWS

      set_simple_output_debug_string_a();

      set_simple_output_debug_string_w();

#endif

      processor_cache_oriented_destroy_all_memory_pools();



      __node_acme_pos_term();

      //::acme::static_start::term();

      //return true;

      return ::success;

   }


//} // namespace static_start


} // namespace acme


//static ::mutex * s_pmutexDraw2d = nullptr;
//
//CLASS_DECL_ACME ::mutex * draw2d_mutex()
//{
//
//   return s_pmutexDraw2d;
//
//}


//CLASS_DECL_ACME void init_draw2d_mutex()
//{
//
//   s_pmutexDraw2d = new ::mutex();
//
//}


//CLASS_DECL_ACME void terg_draw2d_mutex()
//{
//
//   ::acme::del(s_pmutexDraw2d);
//
//}



//CLASS_DECL_ACME ::mutex * get_cred_mutex()
//{
//
//   return ::acme::g_pmutexCred;
//
//}







//level * acme_level::s_plevel = nullptr;

//acme_level acmelevelAura(::acme_level::level_acme, &defer_acme_init);



CLASS_DECL_ACME color32_t dk_red() // <3 tbs
{
   return argb(255, 200, 16, 46);
}


thread_local  ::e_status t_estatus;


CLASS_DECL_ACME void set_last_status(const ::e_status & estatus)
{

   t_estatus = estatus;

}


CLASS_DECL_ACME ::e_status get_last_status()
{

   return t_estatus;

}




//acme_level acmelevelAxis(::acme_level::level_axis, &defer_axis_init);
//
//namespace axis
//{
//
//
//   namespace static_start
//   {
//
//
//      CLASS_DECL_ACME void init()
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
//      CLASS_DECL_ACME void term()
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

#ifdef WINDOWS
_locale_t get_c_locale()
#else
locale_t get_c_locale()
#endif
{

   return ::acme::g_localeC;

}


void acme_ref()
{

   ::acme::acme::g_acme.this_ref();

}


CLASS_DECL_ACME ::mutex * get_globals_mutex()
{

   return ::acme::g_pmutexGlobals;

}




CLASS_DECL_ACME ::mutex* get_children_mutex()
{

   return ::acme::g_pmutexChildren;

}


CLASS_DECL_ACME void release_on_end(::matter* pmatter)
{

   critical_section_lock l(::acme::g_pcsGlobal);

   __defer_new(::acme::g_pelementaddraReleaseOnEnd);

   ::acme::g_pelementaddraReleaseOnEnd->add(pmatter);

}


void delete_all_release_on_end()
{

   critical_section_lock l(::acme::g_pcsGlobal);

   if (is_set(::acme::g_pelementaddraReleaseOnEnd))
   {

      for (auto pmatter : *::acme::g_pelementaddraReleaseOnEnd)
      {

         ::acme::del(pmatter);

      }

      ::acme::del(::acme::g_pelementaddraReleaseOnEnd);

   }

}


void add_release_on_end(::matter * pmatter)
{

   critical_section_lock l(::acme::g_pcsGlobal);

   if (::is_null(::acme::g_pelementaddraReleaseOnEnd))
   {

      ::acme::g_pelementaddraReleaseOnEnd = new element_address_array();

   }

   ::acme::g_pelementaddraReleaseOnEnd->add(pmatter);

}



