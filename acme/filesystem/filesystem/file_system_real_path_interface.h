// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 17:34 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
// From programming by camilo on 2025-10-19 22:48 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once



class CLASS_DECL_ACME file_system_real_path_interface :
   virtual public ::particle
{
public:


   ::pointer < ::file_system_real_path_interface_cache > m_prealpathinterfacecache;
   

   file_system_real_path_interface();
   ~file_system_real_path_interface() override;

   void on_initialize_particle() override;

   //virtual bool file_system_file_exists(const ::file_system_cache_item& pfilesystemcacheitem);
   //virtual bool file_system_is_folder(const ::file_system_cache_item& pfilesystemcacheitem);
   //virtual bool file_system_has_script(const ::file_system_cache_item& pfilesystemcacheitem);
   //virtual string file_system_expanded_md5(const ::file_system_cache_item& pfilesystemcacheitem);


   //virtual class ::file_system_cache_item file_system_item(const ::scoped_string& scopedstrName, ::file_system_interface* pfilesysteminterface = nullptr);


   //virtual ::file_system_item* get_file_system_item(const ::scoped_string& scopedstr, ::file_system_interface* pfilesysteminterface = nullptr);
   virtual ::file::path real_path(const ::scoped_string& scopedstrName);
   virtual ::file::path _real_path1(const ::scoped_string& scopedstrName);


};
