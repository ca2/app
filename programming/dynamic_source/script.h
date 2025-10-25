#pragma once


////#include "acme/prototype/prototype/object.h"
#include "acme/filesystem/filesystem/file_system_cache.h"
#include "acme/filesystem/filesystem/file_system_cache_item.h"
#include "acme/filesystem/filesystem/file_system_real_path_interface_cache.h"
#include "programming/dynamic_source/data_object.h"

namespace dynamic_source
{



   class CLASS_DECL_APP_PROGRAMMING script :
      virtual public data_object,
      virtual public ::file_system_cache,
      virtual public ::file_system_real_path_interface_cache
   {
   public:


      ::pointer < script_manager >                       m_pscriptmanager1;
      //string                                             m_strName;
      //::file::path                                       m_path1;
      //::file_system_item *                               m_pfilesystemitem;
      ::file_system_cache_item                           m_pfilesystemcacheitem;
      memory_file_pointer                                m_pfileError;
      ::write_text_stream                                m_textstreamError;
      string                                             m_strError;
      bool                                               m_bNew;
      bool                                               m_bBuilding;
      ::string_map < ::file_system_cache_item >          m_mapScriptPath;
      critical_section                                   m_criticalsectionFileSystemCacheItem;
      index_map_base < ::file_system_cache_item >        m_mapFileSystemCacheItem;
      critical_section                                   m_criticalsectionFileSystemItem;
      ::string_map < ::pointer < ::file_system_item > >  m_mapFileSystemItem;
      //bool m_bShouldRunOnAfterCreate;
      //class site_data:
      //   virtual public ::particle
      //{
      //public:

      //};
      ::string_map < ::pointer < data_object > >  m_mapSiteDataDataObject;
      bool  m_bLoadedRootInitScript = false;
      bool  m_bLoadedStringTables = false;
      bool  m_bLoadedOnBeforeInclude = false;
      //bool  m_bLoadedMainStringTable = false;

      script();
      ~script() override;


      void on_initialize_particle() override;

      void destroy() override;

      virtual void defer_build();

      virtual ::pointer<::dynamic_source::script_instance>create_instance() = 0;

      virtual void run(script_instance * pinstance);

      virtual bool ShouldBuild();

      virtual bool HasCompileOrLinkError();


      virtual void set_manager(script_manager* pmanager);

      //virtual void on_after_create();
      virtual void load_stringtable(const ::scoped_string& scopedstrLoad);

      virtual ::file_system_cache_item netnode_file_path(const ::scoped_string& scopedstrName);
      //virtual ::file_system_cache_item _calculate_real_path(const ::scoped_string& scopedstrBase, ::f);

   };


   template < class T >
   class t_script :
      virtual public script
   {
   public:


      t_script()
      {


      };


      virtual ::pointer<script_instance>create_instance()
      {
         
         return øallocate T();

      }

   };


} // namespace dynamic_source



