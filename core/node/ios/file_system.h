#pragma once


namespace ios
{


   class CLASS_DECL_CORE file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;
      ::file::path            m_pathModule;
      ::file::path            m_pathCa2Module;
      

      file_system();
      virtual ~file_system();

      
      virtual ::e_status initialize(::layered * pobjectContext) override;
      

      virtual ::e_status update_module_path() override;
      
      
      

   };


} // namespace ios



