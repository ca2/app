#pragma once


namespace ios
{


   class CLASS_DECL_ACME file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;
      ::file::path            m_pathModule;
      //::file::path            m_pathCa2Module;
      

      file_system();
      ~file_system() override;

      
      virtual void initialize(::particle * pparticle) override;
      

      virtual void update_module_path() override;
      
      
      

   };


} // namespace ios



