#pragma once


namespace android
{


   class CLASS_DECL_ACME directory_system :
      virtual public ::directory_system
   {
   public:


      ::file::path				m_strTimeFolder;
      ::file::path				m_strNetSeedFolder;

      ::file::path				m_strCommonAppData;
      ::file::path      		m_strProfile;
      ::file::path   			m_strAppData;
      ::file::path				m_strPrograms;
      ::file::path  			   m_strCommonPrograms;


      directory_system();
      virtual ~directory_system();


      virtual void initialize(::particle * pparticle) override;



   };

} // namespace android


