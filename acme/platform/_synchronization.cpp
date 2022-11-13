// Created by camilo on 2022-11-01 23:26 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/parallelization/mutex.h"


#if defined(LINUX) || defined(__APPLE__)

static ::critical_section g_criticalsectionTz;

::critical_section * tz_critical_section() { return &g_criticalsectionTz; }

static ::critical_section g_criticalsectionThreadHandleLock;

::critical_section * thread_handle_lock_critical_section() { return &g_criticalsectionThreadHandleLock; }


#endif // defined(LINUX) || defined(__APPLE__)


static ::critical_section g_criticalsectionGlobals;


critical_section * globals_critical_section() { return &g_criticalsectionGlobals; }


static ::critical_section g_criticalsectionRefDbg;


critical_section * ref_dbg_critical_section() { return &g_criticalsectionRefDbg; }


static ::critical_section g_criticalsectionFactory;


critical_section * factory_critical_section() { return &g_criticalsectionFactory; }




#if !defined(WINDOWS)

critical_section g_criticalsectionDemangle;

::critical_section * demangle_critical_section() { return &g_criticalsectionDemangle; }


#endif


critical_section g_criticalsectionSystemHeap;

::critical_section * system_heap_critical_section() { return &g_criticalsectionSystemHeap; }

#ifdef WINDOWS


::critical_section g_criticalsectionSymDbgHelp;


::critical_section * sym_dbg_help_critical_section() { return &g_criticalsectionSymDbgHelp; }


#endif


//::critical_section g_criticalsectionMessageDispatch;
//
//
//::critical_section * message_dispatch_critical_section() { return &g_criticalsectionMessageDispatch; }
//




#ifdef ANDROID

::critical_section g_criticalsectionOutputDebugStringA;

::critical_section * output_debug_string_a_critical_section() { return &g_criticalsectionOutputDebugStringA; }

#endif


#ifdef __APPLE__


::critical_section g_criticalsectionCvt;


::critical_section * cvt_critical_section() { return &g_criticalsectionCvt; }

#endif



