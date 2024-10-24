#pragma once


namespace universal_windows
{


   class CLASS_DECL_APEX directory_system :
      virtual public ::directory_system
   {
   public:


      ::file::path         m_strCa2;
      ::file::path         m_strTimeFolder;
      ::file::path         m_strNetSeedFolder;


      directory_system();
      virtual ~directory_system();



      virtual void initialize(::particle * pparticle) override;


      virtual bool update_module_path() override;



   };


} // namespace universal_windows





