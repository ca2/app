#pragma once


namespace subsystem
{

   CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory);

   class particle :
      virtual public ::particle
   {
   public:


      particle();
      ~particle() override;



   };

} // namespace subsystem