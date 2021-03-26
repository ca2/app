// Created on 2021-03-21 16:35 <3ThomasBS_!!
#include "framework.h"
#include "acme/platform/acme.h"
#include "acme/filesystem/filesystem/acme_dir.h"


int g_iMemoryCounters = -1;

mutex* g_pmutexMemoryCounters = nullptr;

int g_iMemoryCountersStartable = 0;

string_map < iptr > * g_pmapMemoryCounter = nullptr;


bool memory_counter_on()
{

   return g_iMemoryCountersStartable && g_iMemoryCounters;

}



bool initialize_memory_counter(::matter* pmatter)
{

   if (g_iMemoryCountersStartable && g_iMemoryCounters < 0)
   {

      g_iMemoryCounters = file_exists(pmatter->m_psystem->m_pacmedir->config() / "system/memory_counters.txt") ? 1 : 0;

      if (g_iMemoryCounters)
      {

         //g_pmutexMemoryCounters = new ::mutex(e_create_new, false, "Global\\ca2_memory_counters");
         g_pmutexMemoryCounters = new ::mutex();

         g_pmapMemoryCounter = new string_map < iptr >;

      }

   }

   return true;

}



//::file::path memory_counter_base_path(::matter* pmatter)
//{
//
//   if (g_iMemoryCountersStartable && g_pMemoryCounters == nullptr)
//   {
//
//      g_pMemoryCounters = new ::file::path();
//
//#if defined(_UWP)
//
//      string strBasePath = pmatter->m_psystem->m_pacmedir->system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(get_current_process_id());
//
//      string strBasePath = pmatter->m_psystem->m_pacmedir->system() / "memory_counters" / strModule.title() / __str(get_current_process_id());
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

void _memory_counter_increment(const char* psz)
{

   synchronization_lock lock(g_pmutexMemoryCounters);

   g_pmapMemoryCounter->operator[](psz)++;

}


void _memory_counter_decrement(const char* psz)
{

   synchronization_lock lock(g_pmutexMemoryCounters);

   g_pmapMemoryCounter->operator[](psz)++;

}



