#pragma once


namespace android
{


   class CLASS_DECL_ACME file_context :
      virtual public ::file_context
   {
   public:



      ::pointer<directory_system>       m_pdirectorysystem;
      ::pointer<file_system>      m_pfilesystem;


      file_context();
      virtual ~file_context();


      virtual void initialize(::particle * pparticle) override;


      virtual void update_module_path() override;


   };


} // namespace ca2


