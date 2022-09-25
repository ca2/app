// Created on 2021-03-21 16:35 <3ThomasBS_!!
#include "framework.h"
#include "acme/platform/node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"


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

      g_iMemoryCounters = pmatter->m_psystem->m_pacmefile->exists(pmatter->m_psystem->m_pacmedirectory->config() / "system/memory_counters.txt") ? 1 : 0;

      if (g_iMemoryCounters)
      {

         //g_pmutexMemoryCounters = memory_new ::mutex(e_create_new, false, "Global\\ca2_memory_counters");
         g_pmutexMemoryCounters = memory_new ::mutex();

         g_pmapMemoryCounter = memory_new string_map < iptr >;

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
//      g_pMemoryCounters = memory_new ::file::path();
//
//#if defined(_UWP)
//
//      string strBasePath = pmatter->m_psystem->m_pacmedirectory->system() / "memory_counters";
//
//#else
//
//      ::file::path strModule = module_path_from_pid(get_current_process_id());
//
//      string strBasePath = pmatter->m_psystem->m_pacmedirectory->system() / "memory_counters" / strModule.title() / __string(get_current_process_id());
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

   synchronous_lock lock(g_pmutexMemoryCounters);

   g_pmapMemoryCounter->operator[](psz)++;

}


void _memory_counter_decrement(const char* psz)
{

   synchronous_lock lock(g_pmutexMemoryCounters);

   g_pmapMemoryCounter->operator[](psz)++;

}



