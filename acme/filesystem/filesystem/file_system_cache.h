// Created by camilo on 2025-10-19 16:53 <3ThomasBorregaardSørensen!!
// From programming by camilo on 2025-10-19 17:28 <3ThomasBorregaardSørensen!! ThomasKanGodLideTalFem.
#pragma once


class CLASS_DECL_ACME file_system_cache :
   virtual public ::particle
{
public:

   ::pointer < ::mutex >                                 m_pmutexIncludeMatches;
   string_map_base < ::logic::boolean >                       m_mapIncludeMatchesFileExists2;
   string_map_base < ::logic::boolean >                       m_mapIncludeMatchesIsDir2;
   ::pointer < ::mutex >                                 m_pmutexIncludeHasScript;
   string_map_base < ::logic::boolean >                       m_mapIncludeHasScript2;
   ::pointer < ::mutex >                                 m_pmutexIncludeExpandMd5;
   string_to_string_base                                      m_mapIncludeExpandMd5;

   file_system_cache();
   ~file_system_cache() override;


   void on_initialize_particle() override;


   virtual bool include_matches_file_exists(const ::file::real_path& realpath);
   virtual void set_include_matches_file_exists(const ::file::real_path& realpath, bool bFileExists);
   virtual bool include_matches_is_dir(const ::file::real_path& realpath);
   virtual bool include_has_script(const ::file::real_path& realpath);
   virtual string include_expand_md5(const ::file::real_path& realpath);
   virtual void set_include_expand_md5(const ::file::real_path& realpath, const ::scoped_string& scopedstrMd5);


   virtual void clear_include_matches(::file::path path);
   virtual void clear_include_matches();


};


