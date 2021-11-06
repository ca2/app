#pragma once


namespace linux
{


  class CLASS_DECL_APEX dir_system :
    virtual public ::dir_system
  {
  public:


    ::file::path            m_pathTimeFolder;
    ::file::path            m_pathNetSeedFolder;

    ::file::path            m_pathCa2;
    ::file::path            m_pathCommonAppData;
    ::file::path            m_pathCommonPrograms;
    ::file::path            m_pathProfile;
    ::file::path            m_pathPrograms;


          dir_system();
      virtual ~dir_system();


    virtual ::e_status initialize(::object * pobject) override;

  };


} // namespace linux



