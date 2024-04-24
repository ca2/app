#pragma once


namespace linux
{


   class CLASS_DECL_ACME file_system:
      virtual public ::file_system
   {
   public:


      file_system();
      virtual ~file_system();


      virtual void initialize(::particle * pparticle) override;

      virtual void init_system() override;


      virtual void update_module_path() override;


   };


} // namespace linux



