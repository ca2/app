#pragma once


namespace ios
{


   class CLASS_DECL_ACME file_context :
      virtual public ::file_context
   {
   public:

      
      __pointer(dir_system)      m_pdirsystem;
      __pointer(file_system)     m_pfilesystem;


      file_context();
      virtual ~file_context();

      virtual ::estatus initialize(::elemental * pobjectContext) override;
      
      virtual ::estatus update_module_path() override;

      virtual var length(const ::file::path & path, var * pvarQuery) override;
      
      virtual ::file_result get_file(const var & varFile, const efileopen & eopen) override;


   };


} // namespace ios



