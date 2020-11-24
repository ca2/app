#pragma once


namespace ios
{


   class CLASS_DECL_AXIS file_context :
      virtual public ::file_context
   {
   public:

      
      __pointer(dir_system)      m_pdirsystem;
      __pointer(file_system)     m_pfilesystem;


      file_context();
      virtual ~file_context();

      virtual ::estatus initialize(::layered * pobjectContext) override;
      
      virtual ::estatus update_module_path() override;

      virtual payload length(const ::file::path & path, payload * pvarQuery) override;
      
      virtual ::file_result get_file(const payload & varFile, const efileopen & eopen) override;


   };


} // namespace ios



