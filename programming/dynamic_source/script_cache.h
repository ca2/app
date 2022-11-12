#pragma once


#include "acme/primitive/collection/string_map.h"
#include "acme/primitive/primitive/object.h"


namespace dynamic_source
{

   
   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      string_map < ::pointer<script >>   m_map;
      ::pointer<script_manager>          m_pmanager;


      script_cache();
      virtual ~script_cache();


      virtual void initialize_script_cache(script_manager * pscriptmanager);

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


