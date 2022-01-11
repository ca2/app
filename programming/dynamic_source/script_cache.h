#pragma once


namespace dynamic_source
{

   
   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      string_map < __pointer(script) >    m_map;
      __pointer(script_manager)           m_pmanager;


      script_cache();
      virtual ~script_cache();


      virtual void initialize_script_cache(script_manager * pscriptmanager);

      __pointer(script_instance) create_instance(const ::string & lpcszName, __pointer(script) & pscript);

      void set_all_out_of_date();

      void set_out_of_date(string str);

      //void cache(script * pscript);
      __pointer(ds_script) create_new_ds_script(const ::string & strName);
      void uncache(script * pscript);

      script * get(const ::string & lpcszName);
      script * register_script(const ::string & lpcszName, script * pscript);


   };


} // namespace dynamic_source


