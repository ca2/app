#pragma once


namespace linux
{


   class CLASS_DECL_ACME file_context :
      virtual public ::file_context
   {
   public:


      __reference(file_system)      m_pfilesystem;
      __reference(dir_system)       m_pdirsystem;


      file_context();
      virtual ~file_context();


      virtual ::e_status initialize(::matter * pobject) override;


      virtual ::e_status init_system() override;
      virtual ::e_status init_context() override;


      virtual ::file_transport get_file(const ::payload & payloadFile, const ::file::e_open & eopen) override;


      virtual bool is_link(string strPath) override;


      virtual ::file::path dropbox_info_json() override;


   };


} // namespace linux



