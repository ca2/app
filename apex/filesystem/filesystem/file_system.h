#pragma once


class CLASS_DECL_APEX file_system :
   virtual public object
{
public:


   ::file::path         m_pathCa2Module;
   ::file::path         m_pathModule;


   file_system();
   virtual ~file_system();


   virtual ::e_status initialize(::context_object * pcontextobject) override;

   virtual ::e_status init_system();

   virtual ::e_status update_module_path();




};



