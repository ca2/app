#pragma once


namespace ios
{


   class CLASS_DECL_APEX file_context :
      virtual public ::file_context
   {
   public:

      
      __pointer(dir_system)      m_pdirsystem;
      __pointer(file_system)     m_pfilesystem;


      file_context();
      virtual ~file_context();

      virtual void initialize(::object * pobject) override;
      
      virtual void update_module_path() override;

      virtual ::payload length(const ::file::path & path, ::payload * pvarQuery) override;
      
      virtual ::file_pointer get_file(const ::payload & payloadFile, const ::file::e_open & eopen) override;


   };


} // namespace ios



