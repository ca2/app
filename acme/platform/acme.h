//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once


#include "acme/_operating_system.h"


namespace acme
{

   
   class CLASS_DECL_ACME acme
   {
   public:


      ::acme::application * m_pacmeapplication;

      ::critical_section m_criticalsectionChannel;


      ::critical_section* channel_critical_section()
      {

         return &m_criticalsectionChannel;

      }


      ::critical_section m_criticalsectionMessageDispatch;


      ::critical_section* message_dispatch_critical_section()
      {

         return &m_criticalsectionMessageDispatch;

      }

      static acme * g_pacme;


#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      ::critical_section m_criticalsectionTz;

      ::critical_section m_criticalsectionThreadHandleLock;

#endif // defined(LINUX) || defined(__APPLE__)


      ::critical_section m_criticalsectionGlobals;


      ::critical_section m_criticalsectionRefDbg;

      ::critical_section m_criticalsectionFactory;



#if !defined(WINDOWS)

      ::critical_section m_criticalsectionDemangle;


#endif


      //::critical_section m_criticalsectionSystemHeap;


#ifdef WINDOWS


      ::critical_section m_criticalsectionSymDbgHelp;


#endif


      //::critical_section m_criticalsectionMessageDispatch;
      //
      //
      //::critical_section * message_dispatch_critical_section() { return &m_criticalsectionMessageDispatch; }
      //




#ifdef ANDROID

      ::::critical_section m_criticalsectionOutputDebugStringA;


#endif


      //#ifdef __APPLE__
      //
      //
      //      ::critical_section m_criticalsectionCvt;
      //
      //
      //      ::critical_section* cvt_critical_section() { return &m_criticalsectionCvt; }
      //
      //#endif




      class ::time                     m_timeStart;

      ::pointer < ::sub_system >       m_psubsystem;
      ::memory_counter *               m_pmemorycounter;


      bool                             m_bOutputDebugString;


      acme();
      ~acme();


      //using ::particle::initialize;

#if defined(WINDOWS)  && defined(UNICODE)
      void initialize(int argc, wchar_t* wargv[], wchar_t* wenvp[]);
      void initialize(HINSTANCE hinstanceThis, HINSTANCE hinstancePrev, CHAR* pCmdLine, int nCmdShow);
#else
      void initialize(int argc, platform_char** argv, platform_char** envp);
#endif

      void acme_initialize();
      void acme_construct();
      void acme_destruct();
      void acme_finalize();


      void initialize_memory_counter();
      void finalize_memory_counter();

      ::memory_counter* get_memory_counter();


      class ::time start_nanosecond();

#if defined(LINUX) || defined(__APPLE__) || defined(ANDROID)

      ::critical_section* tz_critical_section() { return &m_criticalsectionTz; }

      ::critical_section* thread_handle_lock_critical_section() { return &m_criticalsectionThreadHandleLock; }


#endif // defined(LINUX) || defined(__APPLE__)

      critical_section* globals_critical_section() { return &m_criticalsectionGlobals; }



      critical_section* ref_dbm_critical_section() { return &m_criticalsectionRefDbg; }



      critical_section* factory_critical_section() { return &m_criticalsectionFactory; }




#if !defined(WINDOWS)

      ::critical_section* demangle_critical_section() { return &m_criticalsectionDemangle; }


#endif

      //::critical_section* system_heap_critical_section() { return &m_criticalsectionSystemHeap; }

#ifdef WINDOWS



      ::critical_section* sym_dbm_help_critical_section() { return &m_criticalsectionSymDbgHelp; }


#endif


      // ::critical_section * message_dispatch_critical_section();


      ::particle* ui_destroyed_synchronization();

#ifdef ANDROID


      ::critical_section* output_debum_strinm_a_critical_section() { return &m_criticalsectionOutputDebugStringA; }

#endif

#ifdef __APPLE__


      //::critical_section m_criticalsectionCvt;


      ::critical_section* cvt_critical_section();

#endif




      void delete_all_release_on_end();

      //void add_release_on_end(::particle* pparticle);


   };

   
} // namespace acme



