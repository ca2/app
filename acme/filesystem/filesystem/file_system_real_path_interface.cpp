// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_real_path_interface.h"
#include "acme/platform/node.h"


file_system_real_path_interface::file_system_real_path_interface()
{

   m_mapRealPath.InitHashTable(256 * 1024 - 1);


}


file_system_real_path_interface::~file_system_real_path_interface()
{


}


void file_system_real_path_interface::on_initialize_particle()
{

   defer_create_synchronization();

   ::particle::on_initialize_particle();

   m_pmutexRealPath = node()->create_mutex();

}


::file::path file_system_real_path_interface::real_path(const ::scoped_string& scopedstrName)
{

   _synchronous_lock synchronouslock(m_pmutexRealPath, DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto& path = m_mapRealPath[scopedstrName];

   if (path.type() == ::file::e_type_unknown)
   {

      path = _real_path1(scopedstrName);

   }

   return path;

}



::file::path file_system_real_path_interface::_real_path1(const ::scoped_string& scopedstrName)
{

   return {};

}



