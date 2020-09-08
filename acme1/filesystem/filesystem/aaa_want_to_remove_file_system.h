#pragma once


class CLASS_DECL_ACME file_system :
   virtual public generic
{
public:


   ::file::path         m_pathCa2Module;
   ::file::path         m_pathModule;


   file_system();
   virtual ~file_system();


   virtual ::estatus initialize(::generic * pobjectContext) override;

   virtual ::estatus init_system();

   virtual ::estatus update_module_path();




};



