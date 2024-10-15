#include "framework.h"
#include "acme.h"
#include "system.h"
#include "library.h"
#include "platform.h"
#include "acme/memory/c_malloc.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/task_context.h"
#include "acme/platform/_synchronization.h"
#include "acme/platform/referencing_debugging.h"
#include "acme/prototype/prototype/malloc.h"
#include "acme/user/user/theme_colors.h"


#include "acme/_operating_system.h"
#include "acme/operating_system/acme_initialize.h"

#include "acme/operating_system/ansi/binreloc.h"
#include "parallelization/manual_reset_event.h"


CLASS_DECL_ACME bool should_output_debug_string();
CLASS_DECL_ACME bool add_matter(::matter * pmatter);


//CLASS_DECL_ACME::particle * task_get_top_track();


#include <locale.h>
#if defined(__APPLE__)
#include <xlocale.h>
#endif


//namespace main_memory_allocate_heap
//{
//   CLASS_DECL_ACME void memdleak_init();
//   CLASS_DECL_ACME void memdleak_term();
//   CLASS_DECL_ACME void memdleak_dump();
//}
//namespace array_memory_allocate_heap
//{
//   CLASS_DECL_ACME void memdleak_init();
//   CLASS_DECL_ACME void memdleak_term();
//   CLASS_DECL_ACME void memdleak_dump();
//}
//namespace property_memory_allocate_heap
//{
//   CLASS_DECL_ACME void memdleak_init();
//   CLASS_DECL_ACME void memdleak_term();
//   CLASS_DECL_ACME void memdleak_dump();
//}
//namespace secondary_memory_allocate_heap
//{
//   CLASS_DECL_ACME void memdleak_init();
//   CLASS_DECL_ACME void memdleak_term();
//   CLASS_DECL_ACME void memdleak_dump();
//}
//namespace string_memory_allocate_heap
//{
//   CLASS_DECL_ACME void memdleak_init();
//   CLASS_DECL_ACME void memdleak_term();
//   CLASS_DECL_ACME void memdleak_dump();
//}


#ifdef WINDOWS
CLASS_DECL_ACME _locale_t get_c_locale();
#else
CLASS_DECL_ACME locale_t get_c_locale();
#endif



class plex_heap_alloc_array;



#if OBJECT_TYPE_COUNTER

extern map < const char *, const char *, ::i64, ::i64 > * g_pmapObjTypCtr;

#endif


#if OBJECT_TYPE_COUNTER

extern int g_iObjTypCtrInit;

#endif

#ifdef WINDOWS


#else

extern char * g_pszDemangle;

#endif


extern bool g_bOutputDebugString;


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


extern CLASS_DECL_ACME ::array<matter *> * g_paAura;


extern id_to_id * g_pmapRTL;


#if defined(WINDOWS)

extern _locale_t g_localeC;

#else

extern locale_t g_localeC;

#endif



extern ::nanosecond g_nanosecondFirst;


extern int g_iMemoryCountersStartable;


//void initialize_memory_management();
//void finalize_memory_management();


#define ThomasBS_Acme this


#ifdef WINDOWS


LARGE_INTEGER g_largeintegerFrequency;


#endif


::array < ::procedure > * g_proutineaOsTerm;

//extern natural_meta_data < string_meta_data < ::ansi_character > > * g_pansistringNil;
//
//extern natural_meta_data < string_meta_data < ::wd16_character > > * g_pwd16stringNil;
//
//extern natural_meta_data < string_meta_data < ::wd32_character > > * g_pwd32stringNil;


//static void delete_all_release_on_end();

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

//void ([a-z0-9_]+)_factory(::factory::factory * pfactory);



CLASS_DECL_ACME void __seed_srand();


//void initialize_global_message_queue();
//void finalize_global_message_queue();





#ifdef RASPBERRYPIOS
#define OPERATING_SYSTEM_NAMESPACE linux
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


extern thread_local ::task_pointer t_pthread;


//void check_all_pending_releases();


#if REFERENCING_DEBUGGING


extern bool g_bDefaultEnableObjectReferenceCountDebug;


#endif


namespace acme
{


   ::acme::acme * singleton::s_pacme = nullptr;


   acme::acme()
   {

      m_pheapmanagement = nullptr;

//      s_pacme = this;

      acme_construct();

#if REFERENCING_DEBUGGING

      initialize_referencing_debugging();

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }

#endif

      //::allocator::add_referer({ this, __FUNCTION_FILE_LINE__ });

      {

         //REFDBG_THIS(this);

         m_pplatform = new ::platform::platform(this);

      }
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
      m_pplatform->platform_initialize();
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
      acme_construct_platform_dependent();
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
         m_pmanualreseteventReadyToExit = __allocate ::manual_reset_event();

#if REFERENCING_DEBUGGING

         g_bDefaultEnableObjectReferenceCountDebug = true;

#endif

   }

   void acme::on_before_destroy()
   {

      __destroy_and_release(m_pplatform->m_psystem);

      m_pmanualreseteventReadyToExit->_wait(5_min);

      m_ptaskmessagequeue.release();

      ::task_release();

      acme_destruct_platform_dependent();

      m_pplatform->platform_finalize();

      //m_pplatform.release();

      delete m_pplatform;

      m_pplatform = nullptr;

#if REFERENCING_DEBUGGING

      // Some cleanup

      while (::task_context_base::current())
      {

         ::task_context_base::current()->pop();

      }

      g_bDefaultEnableObjectReferenceCountDebug = false;

      {

         auto preferencingdebugging = ::transfer(m_preferencingdebugging);

         g_bDefaultEnableObjectReferenceCountDebug = false;

         preferencingdebugging->dump_pending_releases();

      }

      //dump_pending_releases();

      //m_preferencingdebugging.release();

#endif

   }


   acme::~acme()
   {



      acme_destruct();

      //s_pacme = nullptr;

   }


   //void acme::acme_initialize()
   //{


   //}
   //  

   //void acme::acme_finalize()
   //{


   //}


//#if defined(WINDOWS)  && defined(UNICODE)
//
//
//   void initialize(int argc, wchar_t* argv[], wchar_t* envp[])
//   {
//
//      m_pplatform->initialize(argc, argv, envp);
//
//   }
//
//
//   void initialize(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow)
//   {
//
//      m_pplatform->initialize(hinstanceThis, hinstancePrev, nCmdShow);
//
//   }
//
//
//#else
//
//
//   void initialize(int argc, platform_char** argv, platform_char** envp)
//   {
//
//      m_pplatform->initialize(argc, argv, envp);
//
//   }
//
//
//#endif


   //acme * acme::g_p = nullptr;


   


#if OBJECT_TYPE_COUNTER

   map < const char*, const char*, ::i64, ::i64 >* g_pmapObjTypCtr;

#endif


   bool g_bAcme;


#if OBJECT_TYPE_COUNTER

   int g_iObjTypCtrInit;

#endif



   //::critical_section system()->g_mutexLibrary;

   //__LPFN_MAIN_DEFERRED_RUN g_main_deferred_run;

//   critical_section get_global_critical_section()
//   {
//
//      return &g_criticalsectionGlobal;
//
//   }

   //critical_section g_criticalsectionGlobal;

   bool g_bOutputDebugString;

   //criticalsection g_criticalsectionTrace;

   //::matter * g_ptrace;

   //simple_trace * g_psimpletrace;

   //critical_section* g_criticalsectionTrace;

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


   //::critical_section g_criticalsectionCred;


   //class ::exception_engine* g_pengine;


   ::array < matter* >* g_paAura;


   //::map < ::atom, const ::atom&, ::atom, const ::atom& >* g_pmapRTL;

   //plex_heap_alloc_array* g_pheap;

   // critical_section* g_criticalsectionSystemHeap;

#if defined(WINDOWS)

   _locale_t g_localeC;

#else

   locale_t g_localeC;

#endif


#if !defined(WINDOWS)


   char* g_pszDemangle;


#endif


   //map < itask_t, itask_t, itask_t, itask_t > * g_pmapThreadOn;



   //plex_heap_alloc_array * g_pplexheapallocarray;

   int g_iMemoryCountersStartable;
   //::critical_section g_criticalsectionTrait;
   //::critical_section g_criticalsectionFactory;




   //CLASS_DECL_ACME acme_str_pool* g_pacmestrpool;

   // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

   // ::critical_section g_criticalsectionMq;

   // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(ANDROID)

//::critical_section g_criticalsectionThreadIdHandleLock;

//::critical_section g_criticalsectionThreadIdLock;

//#if !defined(UNIVERSAL_WINDOWS)

//::critical_section g_criticalsectionPendingThreadsLock;

//#endif

//::critical_section g_criticalsectionTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)




//
//
//
//   critical_section g_csRefDbg;
//


//   void acme::construct()
//   {
//
//      __seed_srand();
//
//      g_bAcme = 0;
//
//#if OBJECT_TYPE_COUNTER
//
//      g_pmapObjTypCtr = nullptr;
//
//#endif
//
//      g_bAcme = false;
//
//#if OBJECT_TYPE_COUNTER
//
//      g_iObjTypCtrInit = 0;
//
//#endif
//
//      //g_criticalsectionChildren = nullptr;
//
//      //g_criticalsectionThreadWaitClose = nullptr;
//
//#if !defined(WINDOWS)
//
//      //g_tlsindexLastError = 0;
//
//      g_pszDemangle = nullptr;
//
//      //g_criticalsectionDemangle = nullptr;
//
//#endif
//
//      //g_main_deferred_run = nullptr;
//
//      //g_criticalsectionGlobals = nullptr;
//
//      //g_criticalsectionGlobal = nullptr;
//
//      g_bOutputDebugString = true;
//
//      //g_criticalsectionTrace = nullptr;
//
//      //g_ptrace = nullptr;
//
//      //g_psimpletrace = nullptr;
//
//      //g_criticalsectionTrace = nullptr;
//
//      // acme commented
//      //g_ptrace = nullptr;
//
//      // acme commented
//      //g_psimpletrace = nullptr;
//
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
//
//      //g_criticalsectionCred = nullptr;
//
//      //g_pengine = nullptr;
//      //g_criticalsectionMessageDispatch = nullptr;
//
//      g_paAura = nullptr;
//
//#if defined(WINDOWS)
//
//      g_localeC = 0;
//
//#else
//
//      g_localeC = 0;
//
//#endif
//
//#ifdef WINDOWS
//
//      g_largeintegerFrequency = {};
//
//#endif
//
//      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;
//
//      g_iMemoryCountersStartable = 0;
//      //::critical_section g_criticalsectionTrait;
//      //::critical_section g_criticalsectionFactory;
//
//      //g_criticalsectionUiDestroyed = 0;
//
//#ifdef ANDROID
//
//      //g_criticalsectionOutputDebugStringA = 0;
//
//#endif
//
//      //g_pacmestrpool = nullptr;
//
//      // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)
//
//      // ::critical_section g_criticalsectionMq;
//
//      // #endif
//
//#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(ANDROID)
//
////::critical_section g_criticalsectionThreadIdHandleLock;
//
////::critical_section g_criticalsectionThreadIdLock;
//
////#if !defined(UNIVERSAL_WINDOWS)
//
////::critical_section g_criticalsectionPendingThreadsLock;
//
////#endif
//
////::critical_section g_criticalsectionTlsData;
//
//#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)
//
//#if defined(LINUX) || defined(__APPLE__)
//
//      //g_criticalsectionTz = nullptr;
//
//      //g_criticalsectionThreadHandleLock = nullptr;
//
//#endif // defined(LINUX) || defined(__APPLE__)
//
//
//#ifdef __APPLE__
//
//
//      //g_criticalsectionCvt = nullptr;
//
//
//#endif
//
//#ifdef WINDOWS
//
//
//      //g_criticalsectionSymDbgHelp = nullptr;
//
//
//#endif
//
//
//   }


   void acme::acme_construct()
   {

      initialize_memory_management();
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
      //static natural_meta_data < string_meta_data < ::ansi_character > > s_ansistringNil;

      //static natural_meta_data < string_meta_data < ::wd16_character > > s_wd16stringNil;

      //static natural_meta_data < string_meta_data < ::wd32_character > > s_wd32stringNil;

      //::g_pansistringNil = &s_ansistringNil;

      //::g_pwd16stringNil = &s_wd16stringNil;

      //::g_pwd32stringNil = &s_wd32stringNil;

      //m_bRef = false;

      //construct();

      __seed_srand();

      g_bAcme = 0;

#if OBJECT_TYPE_COUNTER

      g_pmapObjTypCtr = nullptr;

#endif

      g_bAcme = false;

#if OBJECT_TYPE_COUNTER

      g_iObjTypCtrInit = 0;

#endif

      //g_criticalsectionChildren = nullptr;

      //g_criticalsectionThreadWaitClose = nullptr;

#if !defined(WINDOWS)

      //g_tlsindexLastError = 0;

      g_pszDemangle = nullptr;

      //g_criticalsectionDemangle = nullptr;

#endif

      //g_main_deferred_run = nullptr;

      //g_criticalsectionGlobals = nullptr;

      //g_criticalsectionGlobal = nullptr;

      g_bOutputDebugString = true;

      //g_criticalsectionTrace = nullptr;

      //g_ptrace = nullptr;

      //g_psimpletrace = nullptr;

      //g_criticalsectionTrace = nullptr;

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

      //g_criticalsectionCred = nullptr;

      //g_pengine = nullptr;
      //g_criticalsectionMessageDispatch = nullptr;

      g_paAura = nullptr;

#if defined(WINDOWS)

      g_localeC = 0;

#else

      g_localeC = 0;

#endif

#ifdef WINDOWS

      g_largeintegerFrequency = {};

#endif

      //plex_heap_alloc_array * g_pplexheapallocarray = nullptr;

      g_iMemoryCountersStartable = 0;
      //::critical_section g_criticalsectionTrait;
      //::critical_section g_criticalsectionFactory;

      //g_criticalsectionUiDestroyed = 0;

#ifdef ANDROID

      //g_criticalsectionOutputDebugStringA = 0;

#endif

      //g_pacmestrpool = nullptr;

      // #if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      // ::critical_section g_criticalsectionMq;

      // #endif

#if defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS) || defined(ANDROID)

//::critical_section g_criticalsectionThreadIdHandleLock;

//::critical_section g_criticalsectionThreadIdLock;

//#if !defined(UNIVERSAL_WINDOWS)

//::critical_section g_criticalsectionPendingThreadsLock;

//#endif

//::critical_section g_criticalsectionTlsData;

#endif // defined(LINUX) || defined(__APPLE__) || defined(UNIVERSAL_WINDOWS)

#if defined(LINUX) || defined(__APPLE__)

      //g_criticalsectionTz = nullptr;

      //g_criticalsectionThreadHandleLock = nullptr;

#endif // defined(LINUX) || defined(__APPLE__)


#ifdef __APPLE__


      //g_criticalsectionCvt = nullptr;


#endif

#ifdef WINDOWS


      //g_criticalsectionSymDbgHelp = nullptr;


#endif


      //g_criticalsectionRefDbg = nullptr;


#if defined(WINDOWS)

      g_localeC = _wcreate_locale(LC_ALL, L"C");

      //#elif defined(__APPLE__)
      //
      //      g_localeC = newlocale(LC_ALL_MASK, "C", NULL);
      //
#else

      g_localeC = newlocale(LC_ALL_MASK, "C", NULL);

#endif

      //m_criticalsectionFactory = __new critical_section();

//#ifndef WINDOWS
//
//      //g_criticalsectionDemangle = __new critical_section();
//
//#endif

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

      //__defer_new(m_pelementaddraReleaseOnEnd);


      //xxdebug_box("acme.dll base_static_start (0)", "box", e_message_box_ok);

      //g_pengine = __new ::OPERATING_SYSTEM_NAMESPACE::exception_engine ();

      //g_criticalsectionGlobals = __new ::critical_section ();

      //g_criticalsectionChildren = __new ::critical_section ();

      //g_criticalsectionGlobal = __new critical_section();

      //::initialize_sequence_critical_section();

      //::update::g_criticalsection = __new critical_section();

#ifndef __MCRTDBG

      //::main_memory_allocate_heap::initialize();
      //::string_memory_allocate_heap::initialize();
      //::property_memory_allocate_heap::initialize();
      //::array_memory_allocate_heap::initialize();


#endif

      //::atom_space::s_pidspace = __new atom_space();

//      ::acme::idpool::init();

      //
      //#ifdef ANDROID
      //
      //      g_criticalsectionOutputDebugStringA = __new ::critical_section ();
      //
      //#endif

#if OBJECT_TYPE_COUNTER

      g_pmapObjTypCtr = memory_new map < const char*, const char*, ::i64, ::i64 >;

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }

#endif


      //g_criticalsectionTrace = __new critical_section();

      //g_psimpletrace = __new simple_trace();

      //g_ptrace = g_psimpletrace;


      // acme commented
      //g_psimpletrace = __new simple_trace();

      //g_ptrace = g_psimpletrace;

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      ::sockets::base_socket::s_criticalsection = __new ::critical_section ();
//
//#endif


//#ifdef __APPLE__
//
//      g_criticalsectionCvt = __new ::critical_section ();
//
//#endif

      //g_criticalsectionThreadWaitClose = __new ::critical_section ();

      //g_criticalsectionThreadOn = __new ::critical_section ();

      //g_pmapThreadOn = aaa_memory_new ::map < itask_t, itask_t, itask_t, itask_t >;

      //g_criticalsectionSystemHeap = __new critical_section();

#if MEMDLEAK

      main_memory_allocate_heap::memdleak_init();
      array_memory_allocate_heap::memdleak_init();
      property_memory_allocate_heap::memdleak_init();
      secondary_memory_allocate_heap::memdleak_init();
      string_memory_allocate_heap::memdleak_init();

#endif

      ////factory_init();

      //g_paAura = __new ::array < matter* > ();

      ////::task_on_after_new_particle(g_paAura);

      //{

      //   auto p = ::allocator::task_get_top_track();

      //   ASSERT(p == nullptr);

      //}


      //g_pmapAura =aaa_memory_new ::map < void *,void *,::acme::application *,::acme::application * >;

      //g_criticalsectionUiDestroyed = __new ::critical_section ();

      //g_criticalsectionMessageDispatch = __new ::critical_section ();

      //g_criticalsectionCred = __new ::critical_section ();

#if defined(LINUX) || defined(__APPLE__)

      //g_criticalsectionTz = __new ::critical_section ();

#endif // defined(LINUX) || defined(__APPLE__)


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

#ifdef MEMORY_COUNTERS

      g_iMemoryCountersStartable = 1;

#else

      g_iMemoryCountersStartable = 0;

#endif

      //g_pacmestrpool = __new acme_str_pool();

      //acme commented
      //::user::init_windowing();

      //g_criticalsectionRefDbg = __new critical_section();

      g_bAcme = 1;

      //::thread::g_criticalsection = __new mutex();

      //::thread::g_pthreadmap = __new ::thread_map ();

      // acme commented
      //add_factory_item < ::context >();


#if OBJECT_TYPE_COUNTER
      g_iObjTypCtrInit = 1;
#endif




#ifdef LINUX

      //!!!      x11_hook_init();

#endif


//#ifdef WINDOWS
//
//
//      g_criticalsectionSymDbgHelp = __new ::critical_section ();
//
//
//#endif

      //::acme::library::s_criticalsectionLoading = __new ::critical_section ();

      //init();

            //::acme::acme::init();

      //if (!__node_acme_pre_init())
      __node_acme_pre_init();
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
      //{

      //   throw ::exception(error_failed);

      //}

      // acme commented for apex
      //::parallelization::init_multitasking();

      //if (!__node_acme_pos_init())
      __node_acme_pos_init();
      //{

      //   throw ::exception(error_failed);

      //}

//#ifdef WINDOWS
//
//      set_extended_output_debug_string_a();
//
//      set_extended_output_debug_string_w();
//
//#endif

      //add_factory_item < ::stdio_file >();

      //([a-z0-9_]+)_factory(::factory_item::get_factory());

      //return true;

      //factory()->add_factory_item < ::acme::system >();
#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }
#endif
   }


   void acme::acme_construct_platform_dependent()
   {

      initialize_message_queue();

#if REFERENCING_DEBUGGING

      {

         auto p = ::allocator::task_get_top_track();

         ASSERT(p == nullptr);

      }


#endif


   }


   void acme::acme_destruct_platform_dependent()
   {

      finalize_message_queue();

   }


   void acme::acme_destruct()
   {


      //term();


      //erase_all_global_particles();


      //::parallelization::wait_threads(1_min);

      //if (g_axisontermthread)
      //{

      //   g_axisontermthread();

      //}

      // acme commented for apex
      //on_term_thread();

      // acme commented for apex
      //::parallelization::term_multitasking();

      __node_acme_pre_term();

      //#ifdef WINDOWS
      //
      //      set_simple_output_debug_string_a();
      //
      //      set_simple_output_debug_string_w();
      //
      //#endif

      processor_cache_oriented_destroy_all_memory_pools();



      __node_acme_pos_term();

      //::acme::acme::term();

      //return true;

      //return ::success;



      //::acme::del(::acme::library::s_criticalsectionLoading);

      //::user::os_term_theme_colors();

#ifdef LINUX

      //!!!      x11_hook_term();

#endif


#if OBJECT_TYPE_COUNTER
      g_iObjTypCtrInit = 0;
#endif

      // acme commented
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

      //   synchronous_lock synchronouslock(system()->g_mutexLibrary);

      //   g_pmapLibCall->erase_all();


      //}
      //catch (...)
      //{

      //}

      //try
      //{

      //   synchronous_lock synchronouslock(system()->g_mutexLibrary);

      //   system()->g_mapLibrary.erase_all();

      //}
      //catch (...)
      //{

      //}

      /*if(g_pmapRTL)
      {

         try
         {

            g_pmapRTL->erase_all();

         }
         catch(...)
         {

         }

      }*/

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


      //::acme::del(::thread::g_criticalsection);

      //::acme::del(::thread::g_pthreadmap);

      ////acme commented
      //::user::term_windowing();

      g_bAcme = 0;

      //::acme::del(g_pacmestrpool);



      // acme commented
      //g_ptrace = g_psimpletrace;

      //g_ptrace = g_psimpletrace;

      //::acme::del(g_pmapRTL);

#if defined(LINUX) || defined(__APPLE__)

      //::acme::del(g_criticalsectionTz);

#endif // defined(LINUX) || defined(__APPLE__)

      //::acme::del(g_criticalsectionCred);

      //::acme::del(g_criticalsectionMessageDispatch);

      //::acme::del(g_criticalsectionUiDestroyed);

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

      //try
      //{

      //   factory_term();

      //}
      //catch (...)
      //{

      //}

#if OBJECT_TYPE_COUNTER

      ::acme::del(g_pmapObjTypCtr);

#endif

#if MEMDLEAK

      main_memory_allocate_heap::memdleak_term();
      array_memory_allocate_heap::memdleak_term();
      property_memory_allocate_heap::memdleak_term();
      secondary_memory_allocate_heap::memdleak_term();
      string_memory_allocate_heap::memdleak_term();

#endif

      //::acme::del(g_criticalsectionSystemHeap);

      //::acme::del(g_criticalsectionThreadOn);

      //::acme::del(g_pmapThreadOn);

      //::acme::del(g_criticalsectionThreadWaitClose);

#ifdef __APPLE__

      //::acme::del(g_criticalsectionCvt);

#endif

      //acme commented
//#ifdef BSD_STYLE_SOCKETS
//
//      del(::sockets::base_socket::s_criticalsection);
//
//#endif

      // acme commented
      //::acme::del(g_psimpletrace);

      //::acme::del(g_criticalsectionTrace);

      //::acme::del(g_psimpletrace);

      //::acme::del(g_criticalsectionTrace);

      //trace_category_static_term();

#ifdef ANDROID

      //del(g_criticalsectionOutputDebugStringA);

#endif

      //term_id_pool();

      //::acme::del(::atom_space::s_pidspace);

#if !defined(__MCRTDBG) && !MEMDLEAK

      //auto pheap = g_pheap;

      //g_pheap = nullptr;

      //::acme::del(pheap);

      //::array_memory_allocate_heap::destroy();
      //::property_memory_allocate_heap::destroy();
      //::string_memory_allocate_heap::destroy();
      //::main_memory_allocate_heap::destroy();

#endif


#ifdef WINDOWS


      //::acme::del(g_criticalsectionSymDbgHelp);


#endif


      //::finalize_sequence_critical_section();

      //::acme::del(g_criticalsectionGlobal);

      //::acme::del(g_criticalsectionChildren);

      //::acme::del(g_criticalsectionGlobals);

#if MEMDLEAK

      ::set_task(nullptr);

#ifdef __USE_BFD

      init_resolve_addr_file_func_line();

#endif

      heap()->memdleak_dump();

#endif

#ifndef WINDOWS

      ::acme::free(g_pszDemangle);

#endif

#ifndef WINDOWS

      //::acme::del(g_criticalsectionDemangle);

#endif

      //::acme::del(m_pcriticalsectionFactory);

#ifdef WINDOWS
      _free_locale(g_localeC);
#elif defined(ANDROID)
      //_freelocale(g_localeC);
#else
      freelocale(g_localeC);
#endif

#if !REFERENCING_DEBUGGING

      finalize_memory_management();

#endif

   }


   //::memory_counter* g_pmemorycounter = nullptr;




   //void acme::this_ref()
   //{

   //   //m_bRef = true;
   //   //printf()

   //}


   //::acme::system * acme_create_system(app_core * pappcore)
   //{

   //   auto psystem = __new ::acme::system ();

   //   psystem->initialize(nullptr);

   //   return psystem;

   //}


//
//   void acme::init()
//   {
//
//      //::acme::acme::init();
//
//      //if (!__node_acme_pre_init())
//      __node_acme_pre_init();
//      //{
//
//      //   throw ::exception(error_failed);
//
//      //}
//
//      // acme commented for apex
//      //::parallelization::init_multitasking();
//
//      //if (!__node_acme_pos_init())
//      __node_acme_pos_init();
//      //{
//
//      //   throw ::exception(error_failed);
//
//      //}
//
////#ifdef WINDOWS
////
////      set_extended_output_debug_string_a();
////
////      set_extended_output_debug_string_w();
////
////#endif
//
//      //add_factory_item < ::stdio_file >();
//
//      //([a-z0-9_]+)_factory(::factory_item::get_factory());
//
//      //return true;
//
//      //factory()->add_factory_item < ::acme::system >();
//
//   }
//

//   void acme::term()
//   {
//
//
//      erase_all_global_particles();
//
//
//      //::parallelization::wait_threads(1_min);
//
//      //if (g_axisontermthread)
//      //{
//
//      //   g_axisontermthread();
//
//      //}
//
//      // acme commented for apex
//      //on_term_thread();
//
//      // acme commented for apex
//      //::parallelization::term_multitasking();
//
//      __node_acme_pre_term();
//
////#ifdef WINDOWS
////
////      set_simple_output_debug_string_a();
////
////      set_simple_output_debug_string_w();
////
////#endif
//
//      processor_cache_oriented_destroy_all_memory_pools();
//
//
//
//      __node_acme_pos_term();
//
//      //::acme::acme::term();
//
//      //return true;
//
//      //return ::success;
//
//   }


//} // namespace static_start

//   criticalsection get_global_critical_section()
//   {
//
//      return g_criticalsectionGlobal;
//
//   }


   bool should_output_debug_string()
   {

      return g_bOutputDebugString;

   }


   bool add_matter(::matter * pmatter)
   {

      g_paAura->add(pmatter);

      return true;

   }
//
//#ifdef WINDOWS
//
//   _locale_t get_c_locale()
//   {
//
//      return g_localeC;
//
//   }
//
//#else
//
//   locale_t get_c_locale()
//   {
//
//      return g_localeC;
//
//   }
//
//#endif




//} // namespace acme


//static ::critical_section s_criticalsectionDraw2d = nullptr;
//
//CLASS_DECL_ACME ::critical_section draw2d_mutex()
//{
//
//   return s_criticalsectionDraw2d;
//
//}


//CLASS_DECL_ACME void init_draw2d_mutex()
//{
//
//   s_criticalsectionDraw2d = __new ::critical_section ();
//
//}


//CLASS_DECL_ACME void terg_draw2d_mutex()
//{
//
//   ::acme::del(s_criticalsectionDraw2d);
//
//}



//CLASS_DECL_ACME ::critical_section get_cred_mutex()
//{
//
//   return ::acme::g_criticalsectionCred;
//
//}







//level * acme_level::s_plevel = nullptr;

//acme_level acmelevelAura(::acme_level::level_acme, &defer_acme_init);




//
//void acme::add_release_on_end(::particle * pparticle)
//{
//
//   critical_section_lock criticalsectionlock(globals_critical_section());
//
////   if (::is_null(::acme::g_pelementaddraReleaseOnEnd))
////   {
////
////      ::acme::g_pelementaddraReleaseOnEnd = __new element_address_array();
////
////   }
//
//   //m_pelementaddraReleaseOnEnd->add(pparticle);
//
//}

//
//namespace acme
//{

 
//
//} // namespace acme


//namespace acme
//{
//
//
////   acme * acme::g_p = nullptr;
////   int g_iReference = 0;
//////critical_section g_cs;
////
////   void increment_reference_count()
////   {
////
//////      critical_section_lock lock(&g_cs);
////
////      g_iReference++;
////
////      if(g_iReference == 1)
////      {
////
////         __new acme();
////
////      }
////
////   }
////
////
////   void decrement_reference_count()
////   {
////
////      //critical_section_lock lock(&g_cs);
////
////      g_iReference--;
////
////      if(g_iReference == 0)
////      {
////
////         ::acme::del(acme::g_p);
////
////      }
////
////   }
//
//
////   class reference
////   {
////   public:
////
////
////      reference() { increment_reference_count(); }
////      ~reference() { decrement_reference_count(); }
////
////
////   };
//
//
////   reference g_reference;
//
////   void initialize()
////   {
////
////      increment_reference_count();
////
////   }
////
////
////
////   void finalize()
////   {
////
////
////
////   }
//
//
//



   void acme::initialize_memory_management()
   {

      if (m_pheapmanagement)
      {

         return;

      }

      m_pheapmanagement = ::c::malloc::create < ::heap::management >();

      m_pheapmanagement->initialize_memory_management(this);

      m_pheapmanagement->start_management();

      //DO_FOR_ALL_HEAPS(INITIALIZE_MEMORY_MANAGEMENT);
      //INITIALIZE_MEMORY_MANAGEMENT(main);
      //INITIALIZE_MEMORY_MANAGEMENT(secondary);
      //INITIALIZE_MEMORY_MANAGEMENT(array);
      //INITIALIZE_MEMORY_MANAGEMENT(property);
      //INITIALIZE_MEMORY_MANAGEMENT(string);

      //DO_FOR_ALL_HEAPS(INITIALIZE_MEMORY_HEAP);

   }


   void acme::finalize_memory_management()
   {

      if (!m_pheapmanagement)
      {

         return;

      }

      //::c::malloc::destroy(s_pheapmanagement);

      //::c::malloc::destroy(s_pheapmanagement);

      m_pheapmanagement->m_bDestroyIfEmpty = true;

      //DO_FOR_ALL_HEAPS(FINALIZE_MEMORY_HEAP);

   }


   singleton::singleton()
   {

      ::c::malloc::construct(s_pacme);

   }


   singleton::~singleton()
   {

//      auto pacme = s_pacme;
//
//      if(pacme)
//      {
//
//         auto pheapmanagement = pacme->m_pheapmanagement;
//
//         if(pheapmanagement)
//         {
//
//            pheapmanagement->m_pacmeDestroyOnDestroy = s_pacme;
//
//            s_pacme->acme_destruct();
//
//#if !REFERENCING_DEBUGGING
//
//            return;
//
//#endif
////
//            //return;
//
//         }
//
//
//      }

      s_pacme->on_before_destroy();

      auto pacme = s_pacme;

      ::c::malloc::destroy(pacme);

      s_pacme = nullptr;

   }


} // namespace acme


//#pragma comment (linker, "/export:_g_acme")


// _ACME_LINKER_FORCE_INCLUDE(g_acme);


//#ifdef WINDOWS
//
//
//#else


//#ifdef CLASS_DECL_APEX
//
//
//#include "openssl/applink.c"
//
//
//#endif

//#include "acme/platform/system_setup.h"


//int acme(int argc, char * argv[], char * envp[])
//{
//
//   auto papp = ::app_factory::new_app();
//
//   papp->set_args(argc, argv, envp);
//
//#if defined(LINUX) || defined(FREEBSD) || defined(OPENBSD)
//
//   papp->m_pchar_binary__matter_zip_start = embed_resource::get_start();
//
//   papp->m_pchar_binary__matter_zip_end = embed_resource::get_end();
//
//#endif
//
//   int iExitCode = papp->main_loop();
//
//   return iExitCode;
//
//}
//
//
//#endif










CLASS_DECL_ACME::color::color dk_red() // <3ThomasBS!!
{

   return argb(255, 200, 16, 46);

}


thread_local ::e_status t_estatus;


CLASS_DECL_ACME void set_last_status(const ::e_status& estatus)
{

   t_estatus = estatus;

}


CLASS_DECL_ACME::e_status get_last_status()
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
//         //         oswindow_data::s_pdataptra = __new oswindow_dataptra();
//         //
//         //         oswindow_data::s_criticalsection = __new ::critical_section ();
//         //
//         //         osdisplay_data::s_pdataptra = __new osdisplay_dataptra();
//         //
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
//         //         delete osdisplay_data::s_criticalsection;
//         //
//         //         osdisplay_data::s_criticalsection = nullptr;
//         //
//         //         delete osdisplay_data::s_pdataptra;
//         //
//         //         osdisplay_data::s_pdataptra = nullptr;
//         //
//         //         delete oswindow_data::s_criticalsection;
//         //
//         //         oswindow_data::s_criticalsection = nullptr;
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
//
//#ifdef WINDOWS
//_locale_t get_c_locale()
//#else
//locale_t get_c_locale()
//#endif
//{
//
//   return ::acme::g_localeC;
//
//}


//void acme_ref()
//{
//
//   ::acme::acme::g_pacme->this_ref();
//
//}


//CLASS_DECL_ACME ::critical_section * get_globals_critical_section()
//{
//
//   return &g_criticalsectionGlobals;
//
//}
//
//
//CLASS_DECL_ACME ::critical_section * get_children_mutex()
//{
//
//   return &::acme::g_criticalsectionChildren;
//
//}

//
//CLASS_DECL_ACME void release_on_end(::particle * pparticle)
//{
//
//   auto ppointer = __new global_::particle_pointer();
//
//   *ppointer = pparticle;
//
//}





