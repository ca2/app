#pragma once


namespace android
{


   class CLASS_DECL_CORE file_context :
      virtual public ::file_context
   {
   public:



      __reference(dir_system)       m_pdirsystem;
      __reference(file_system)      m_pfilesystem;


      file_context();
      virtual ~file_context();


      virtual void initialize(::object * pobject) override;


      virtual void update_module_path() override;


   };


} // namespace ca2

