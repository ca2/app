#pragma once


namespace linux
{


   class CLASS_DECL_ACME file_context :
      virtual public ::file_context
   {
   public:


      ::pointer<file_system>     m_pfilesystem;
      ::pointer<dir_system>      m_pdirsystem;


      file_context();
      virtual ~file_context();


      virtual void initialize(::particle * pparticle) override;


      virtual void init_system() override;
      virtual void init_context() override;


      virtual ::file_pointer get_file(const ::payload & payloadFile, ::file::e_open eopen) override;


      virtual bool is_link(string strPath) override;


      virtual ::file::path dropbox_info_network_payload() override;


   };


} // namespace linux



