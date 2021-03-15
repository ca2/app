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

      virtual ::e_status initialize(::context_object * pcontextobject) override;
      
      virtual ::e_status update_module_path() override;

      virtual ::payload length(const ::file::path & path, ::payload * pvarQuery) override;
      
      virtual ::file_result get_file(const ::payload & varFile, const ::file::e_open & eopen) override;


   };


} // namespace ios



