// Created by camilo on 2025-10-19 16:54 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:27 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#include "framework.h"
#include "file_system_real_path_interface.h"
#include "file_system_real_path_interface_cache.h"
#include "acme/platform/node.h"


//file_system_real_path_interface::file_system_real_path_interface()
//{
//
//
//}


file_system_real_path_interface::~file_system_real_path_interface()
{


}


void file_system_real_path_interface::on_initialize_particle()
{

   //defer_create_synchronization();

   ::particle::on_initialize_particle();

}


::file::real_and_logical_path file_system_real_path_interface::real_path(const ::scoped_string& scopedstrName)
{

   if (m_prealpathinterfacecache)
   {

      return m_prealpathinterfacecache->_real_path1(scopedstrName, this);

   }
  
   return _real_path1(scopedstrName);

}


::file::real_and_logical_path file_system_real_path_interface::_real_path1(const ::scoped_string& scopedstrName)
{

   return {};

}



