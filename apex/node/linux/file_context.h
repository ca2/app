#pragma once


namespace linux
{


   class CLASS_DECL_APEX file_context :
      virtual public ::file_context
   {
   public:


      __reference(file_system)      m_pfilesystem;
      __reference(dir_system)       m_pdirsystem;


      file_context();
      virtual ~file_context();


      virtual ::estatus initialize(::layered * pobjectContext) override;


      virtual ::estatus init_system() override;
      virtual ::estatus init_context() override;


      virtual ::file_result get_file(const payload & varFile, const ::file::e_open & eopen) override;


      virtual bool is_link(string strPath) override;


      virtual ::file::path dropbox_info_json() override;


   };


} // namespace linux



