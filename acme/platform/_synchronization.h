//
// Created by camilo on 2022-10-26 17:21 <3ThomasBorregaardSorensen!!
//
#pragma once


#if defined(LINUX) || defined(__APPLE__)


::critical_section * tz_critical_section();

::critical_section * thread_handle_lock_critical_section();


#endif // defined(LINUX) || defined(__APPLE__)


CLASS_DECL_ACME ::critical_section * globals_critical_section();

CLASS_DECL_ACME ::critical_section * ref_dbg_critical_section();

CLASS_DECL_ACME ::critical_section * factory_critical_section();

CLASS_DECL_ACME ::critical_section * demangle_critical_section();

CLASS_DECL_ACME ::critical_section * system_heap_critical_section();

#ifdef WINDOWS


CLASS_DECL_ACME ::critical_section * sym_dbg_help_critical_section();


#endif


//CLASS_DECL_ACME ::critical_section * message_dispatch_critical_section();


CLASS_DECL_ACME ::particle * ui_destroyed_synchronization();


#ifdef ANDROID


CLASS_DECL_ACME ::critical_section * output_debug_string_a_critical_section();


#endif



#ifdef __APPLE__


//::critical_section g_criticalsectionCvt;


::critical_section * cvt_critical_section();

#endif



