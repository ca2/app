#pragma once


namespace macos
{


   class CLASS_DECL_AXIS file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;


      file_system();
      virtual ~file_system();
      
      
      virtual ::estatus initialize(::layered * pobjectContext) override;



      virtual ::estatus update_module_path() override;




   };


} // namespace macos



