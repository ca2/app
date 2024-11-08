#pragma once


#include "acme/prototype/collection/string_map.h"
////#include "acme/prototype/prototype/object.h"


namespace dynamic_source
{

   
   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      string_map < ::pointer<script >>    m_map;
      script_manager *                    m_pmanager;


      script_cache();
      ~script_cache() override;


      virtual void initialize_script_cache(script_manager * pscriptmanager);

      void destroy() override;

      ::pointer<script_instance>create_instance(const ::string & lpcszName, ::pointer<script> & pscript);

      void set_all_out_of_date();

      void set_out_of_date(string str);

      //void cache(script * pscript);
      ::pointer<ds_script>create_new_ds_script(const ::string & strName);
      void uncache(script * pscript);

      script * get(const ::string & lpcszName);
      script * register_script(const ::string & lpcszName, script * pscript);


   };


} // namespace dynamic_source


