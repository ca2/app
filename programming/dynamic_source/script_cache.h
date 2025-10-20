#pragma once


#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


namespace dynamic_source
{

   
   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      string_map_base < ::pointer<script >>    m_map;
      script_manager *                    m_pmanager;


      script_cache();
      ~script_cache() override;


      virtual void initialize_script_cache(script_manager * pscriptmanager);

      void destroy() override;

      virtual ::pointer<script_instance>create_instance(::file_system_item* pfilesystemitem, ::pointer<script> & pscript);

      void set_all_out_of_date();

      void set_out_of_date(const ::scoped_string & scopedstr);

      //void cache(script * pscript);
      //::pointer<ds_script> allocate_ds_script(const ::scoped_string & scopedstrName);
      ::pointer<ds_script> allocate_ds_script(::file_system_item* pfilesystemitem);
      void uncache(script * pscript);

      script * get(::file_system_item * pfilesystemitem);
      script * register_script(::file_system_item * pfilesystemitem, script * pscript);


   };


} // namespace dynamic_source


