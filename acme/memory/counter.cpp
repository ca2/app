// Created on 2021-03-21 16:35 <3ThomasBS_!!
#include "framework.h"
#include "counter.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/factory.h"



//
//
//bool particle_tracker::is_enabled()
//{
//
//   return m_iMemoryCountersStartable && m_iMemoryCounters;
//
//}
//
//
//void particle_tracker::initialize(::particle * pparticle)
//{
//
//   ::particle::initialize(pparticle);
//
//   if (m_iMemoryCountersStartable && m_iMemoryCounters < 0)
//   {
//
//      m_iMemoryCounters = pparticle->file_system()->exists(pparticle->directory_system()->config() / "system/particle_trackers.txt") ? 1 : 0;
//
//      //if (g_iMemoryCounters)
//      //{
//
//      //   //g_pmutexMemoryCounters = __allocate ::pointer < ::mutex > (e_create_new, false, "Global\\ca2_particle_trackers");
//      //   //__øconstruct(pparticle, g_pmutexMemoryCounters);
//
//      //   __construct_new(pparticle, g_pmapMemoryCounter);
//
//      //}
//
//   }
//
//   //return true;
//
//}
//
//
////::file::path particle_tracker_base_path(::matter* pmatter)
////{
////
////   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
////   {
////
////      g_pMemoryCounters = __allocate ::file::path();
////
////#if defined(UNIVERSAL_WINDOWS)
////
////      string strBasePath = pmatter->directory_system()->system() / "particle_trackers";
////
////#else
////
////      ::file::path strModule = module_path_from_pid(get_current_process_id());
////
////      string strBasePath = pmatter->directory_system()->system() / "particle_trackers" / strModule.title() / as_string(get_current_process_id());
////
////#endif
////
////      * g_pMemoryCounters = strBasePath;
////
////   }
////
////   return *g_pMemoryCounters;
////
////}
////
////
////
//
//void particle_tracker::increment_by_name(const ::scoped_string & scopedstr)
//{
//
//   critical_section_lock lock(&m_criticalsection);
//
//   m_mapMemoryCounter[scopedstr]++;
//
//}
//
//
//void particle_tracker::decrement_by_name(const ::scoped_string & scopedstr)
//{
//
//   critical_section_lock lock(&m_criticalsection);
//
//   m_mapMemoryCounter[scopedstr]--;
//
//}
//




CLASS_DECL_ACME void increment_particle_counter(::particle * pparticle)
{


}


CLASS_DECL_ACME void decrement_particle_counter(::particle * pparticle)
{


}



