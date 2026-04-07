#pragma once
#include "subsystem.h"
#include "openssl/ssl.h"


namespace subsystem
{

   CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory);

   enum enum_particle
   {

      e_particle_none,
      e_particle_interface,
      e_particle_implementation,

   };


   class CLASS_DECL_ACME particle_interface :
      virtual public ::particle
   {
   public:

      enum_particle m_eparticle;

      particle_interface(enum_particle eparticle = e_particle_interface);
      ~particle_interface() override;

   };


   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface, PARTICLE_INTERFACE>)
   class composite :
      virtual public PARTICLE_INTERFACE
   {
   public:


      ::pointer < PARTICLE_INTERFACE > m_pparticleThis;

      composite()
      {

        ::main_subsystem()->constructø(m_pparticleThis);

      }

      ~composite() override
      {

      }

   };


   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface, PARTICLE_INTERFACE>)
   class implementation :
   virtual public PARTICLE_INTERFACE
   {
   public:



      implementation()
      {

         this->m_eparticle = e_particle_implementation;

      }

      ~implementation() override
      {

      }

   };

} // namespace subsystem