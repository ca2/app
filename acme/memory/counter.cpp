// Created on 2021-03-21 16:35 <3ThomasBS_!!
#include "framework.h"
#include "counter.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/factory.h"



bool memory_counter::is_enabled()
{

   return m_iMemoryCountersStartable && m_iMemoryCounters;

}


void memory_counter::initialize(::particle * pparticle)
{

   ::particle::initialize(pparticle);

   if (m_iMemoryCountersStartable && m_iMemoryCounters < 0)
   {

      m_iMemoryCounters = pparticle->acmefile()->exists(pparticle->acmedirectory()->config() / "system/memory_counters.txt") ? 1 : 0;

      //if (g_iMemoryCounters)
      //{

      //   //g_pmutexMemoryCounters = memory_new ::pointer < ::mutex >(e_create_new, false, "Global\\ca2_memory_counters");
      //   //__construct(pparticle, g_pmutexMemoryCounters);

      //   __construct_new(pparticle, g_pmapMemoryCounter);

      //}

   }

   //return true;

}


//::file::path memory_counter_base_path(::matter* pmatter)
//{
//
//   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
//   {
//
//      g_pMemoryCounters = memory_new ::file::path();
//
//#if defined(_UWP)
//
//      string strBasePath = pmatter->acmedirectory()->system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(get_current_process_id());
//
//      string strBasePath = pmatter->acmedirectory()->system() / "memory_counters" / strModule.title() / __string(get_current_process_id());
//
//#endif
//
//      * g_pMemoryCounters = strBasePath;
//
//   }
//
//   return *g_pMemoryCounters;
//
//}
//
//
//

void memory_counter::increment(const char* psz)
{

   critical_section_lock lock(&m_criticalsection);

   m_mapMemoryCounter[psz]++;

}


void memory_counter::decrement(const char* psz)
{

   critical_section_lock lock(&m_criticalsection);

   m_mapMemoryCounter[psz]--;

}



