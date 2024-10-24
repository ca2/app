#pragma once


namespace linux
{


  class CLASS_DECL_ACME directory_system :
    virtual public ::directory_system
  {
  public:


    ::file::path            m_pathTimeFolder;
    ::file::path            m_pathNetSeedFolder;

    //::file::path            m_pathCa2;
    ::file::path            m_pathCommonAppData;
    ::file::path            m_pathCommonPrograms;
    ::file::path            m_pathProfile;
    ::file::path            m_pathPrograms;


          directory_system();
      virtual ~directory_system();


    virtual void initialize(::particle * pparticle) override;

  };


} // namespace linux



