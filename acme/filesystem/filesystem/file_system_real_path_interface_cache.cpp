// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_real_path_interface.h"
#include "file_system_real_path_interface_cache.h"
#include "acme/platform/node.h"


file_system_real_path_interface_cache::file_system_real_path_interface_cache()
{

   class ::time timeStart;

   timeStart.Now();

   m_mapRealPath.InitHashTable(256 * 1024 - 1);

   m_timeRealPathMapAllocationElapsed = timeStart.elapsed();

}


file_system_real_path_interface_cache::~file_system_real_path_interface_cache()
{


}


void file_system_real_path_interface_cache::on_initialize_particle()
{

   ::particle::on_initialize_particle();

}


::file::real_and_logical_path file_system_real_path_interface_cache::_real_path1(const ::scoped_string& scopedstrName, file_system_real_path_interface* prealpathinterface)
{

   critical_section_lock criticalsectionlock(&m_criticalsection);

   auto& realandlogicalpath = m_mapRealPath[scopedstrName];

   if (realandlogicalpath.m_pathReal1.type() == ::file::e_type_unknown)
   {

      criticalsectionlock.unlock();

      auto realandlogicalpathNew = prealpathinterface->_real_path1(scopedstrName);

      criticalsectionlock.lock();

      realandlogicalpath = realandlogicalpathNew;

   }

   return realandlogicalpath;

}



