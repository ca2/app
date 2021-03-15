#pragma once


namespace dynamic_source
{

   
   class script;


   class CLASS_DECL_APP_PROGRAMMING script_cache :
      virtual public ::object
   {
   public:


      string_map < __pointer(script) >    m_map;
      __pointer(script_manager)           m_pmanager;


      script_cache();
      virtual ~script_cache();


      virtual ::e_status initialize(::context_object * pcontextobject) override;

      __pointer(script_instance) create_instance(const char * lpcszName, __pointer(script) & pscript);

      void set_all_out_of_date();

      void set_out_of_date(string str);

      //void cache(script * pscript);
      __pointer(ds_script) create_new_ds_script(const string & strName);
      void uncache(script * pscript);

      script * get(const char * lpcszName);
      script * register_script(const char * lpcszName, script * pscript);


   };


} // namespace dynamic_source


