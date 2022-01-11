#pragma once


class CLASS_DECL_APEX file_system :
   virtual public object
{
public:


   //::file::path         m_pathCa2Module;
   ::file::path         m_pathModule;


   file_system();
   ~file_system() override;


   virtual void initialize(::object * pobject) override;

   virtual void init_system();

   //virtual void update_module_path();


   //virtual ::file::path get_last_run_application_path_file(string strAppId);
   //virtual ::file::path get_last_run_application_path(string strAppId);
   //virtual bool set_last_run_application_path(string strAppId);


};



