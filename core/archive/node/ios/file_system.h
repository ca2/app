#pragma once


namespace ios
{


   class CLASS_DECL_AURA file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;
      ::file::path            m_pathModule;
      ::file::path            m_pathCa2Module;
      

      file_system();
      virtual ~file_system();

      
      virtual ::estatus initialize(::object * pobjectContext) override;
      

      virtual ::estatus update_module_path() override;
      
      
      

   };


} // namespace ios



