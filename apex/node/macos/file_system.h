#pragma once


namespace macos
{


   class CLASS_DECL_APEX file_system :
      virtual public ::file_system
   {
   public:


      ::file::path            m_strUserFolder;


      file_system();
      virtual ~file_system();
      
      
      virtual ::e_status initialize(::context_object * pcontextobject) override;



      virtual ::e_status update_module_path() override;




   };


} // namespace macos



