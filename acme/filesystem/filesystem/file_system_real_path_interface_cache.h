// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:48 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From acme by camilo on 2025-10-22 16:50 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


class CLASS_DECL_ACME file_system_real_path_interface_cache :
   virtual public ::particle
{
public:


   ::pointer < ::mutex >                              m_pmutexRealPath;
   ::string_map < ::file::path >                      m_mapRealPath;
   class ::time                                       m_timeRealPathMapAllocationElapsed;


   file_system_real_path_interface_cache();
   ~file_system_real_path_interface_cache() override;


   virtual void on_initialize_particle() override;

   
   virtual ::file::path _real_path1(const ::scoped_string& scopedstrName, file_system_real_path_interface * prealpathinterface);


};
