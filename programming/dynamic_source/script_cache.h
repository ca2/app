#pragma once


#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


namespace dynamic_source
{

   
   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      //string_map_base < ::pointer<script >>    m_map;
      critical_section                                            m_criticalsectionScript;
      map_base < ::file_system_item*, ::pointer< script > >       m_mapScript;
      script_manager *                                            m_pmanager;


      script_cache();
      ~script_cache() override;


      virtual void initialize_script_cache(script_manager * pscriptmanager);

      void destroy() override;

      virtual ::pointer<script_instance>create_instance_2025(const ::file_system_cache_item& pfilesystemcacheitem, ::pointer<script>& pscript);

      virtual ::pointer<script_instance>create_instance(const ::file_system_cache_item & pfilesystemcacheitem, ::pointer<script> & pscript);

      void set_all_out_of_date();

      void set_out_of_date(const ::scoped_string & scopedstr);

      //void cache(script * pscript);
      //::pointer<ds_script> allocate_ds_script(const ::scoped_string & scopedstrName);
      ::pointer<ds_script> allocate_ds_script(const ::file_system_cache_item & pfilesystemcacheitem);
      void uncache(script * pscript);

      script * get(const ::file_system_cache_item & pfilesystemcacheitem, class ::time& timeLockElapsed, class ::time& timeLookUpElapsed);
      script * register_script(const ::file_system_cache_item & pfilesystemcacheitem, script * pscript);


   };


} // namespace dynamic_source


