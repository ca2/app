// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:48 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From acme by camilo on 2025-10-22 16:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


#include "acme/filesystem/filesystem/real_and_logical_path.h"


class CLASS_DECL_ACME file_system_real_path_interface_cache :
   virtual public ::particle
{
public:


   critical_section                                   m_criticalsection;
   ::string_map < ::file::real_and_logical_path >     m_mapRealPath;
   class ::time                                       m_timeRealPathMapAllocationElapsed;


   file_system_real_path_interface_cache();
   ~file_system_real_path_interface_cache() override;


   virtual void on_initialize_particle() override;

   
   virtual ::file::real_and_logical_path _real_path1(const ::scoped_string& scopedstrName, file_system_real_path_interface * prealpathinterface);


};
