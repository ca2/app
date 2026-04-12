// Create by camilo on beginning of 2026-April <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem_acme/subsystem.h"


namespace subsystem
{

   struct interface_t{};

   //CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory);


   enum enum_particle
   {

      e_particle_none,
      e_particle_interface,
      e_particle_implementation,

   };


   template < typename PARTICLE_INTERFACE >
   class particle_interface;

   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface< PARTICLE_INTERFACE >, PARTICLE_INTERFACE >)
   class composite;

   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface< PARTICLE_INTERFACE >, PARTICLE_INTERFACE >)
   class implementation;

   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::particle_interface< PARTICLE_INTERFACE > * pinterface);

   template < typename PARTICLE_INTERFACE, typename TYPE >
   PARTICLE_INTERFACE * _get_implementation(const TYPE * pinterface);

   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::particle_interface< PARTICLE_INTERFACE > * pinterface);

   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::composite< PARTICLE_INTERFACE > * pcomposite);

   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::implementation< PARTICLE_INTERFACE > * pimplementation);


   class CLASS_DECL_ACME particle_base :
      virtual public ::particle
   {
   public:

      enum_particle m_eparticle;

      particle_base(enum_particle eparticle = e_particle_interface);
      ~particle_base() override;



   };


   template < typename PARTICLE_INTERFACE >
   class particle_interface :
      virtual public particle_base
   {
   public:

      using class_type = ::subsystem::interface_t;


      template < typename IMPL >
      IMPL * impl()
      {
         ::cast < IMPL > pimp = ::subsystem::get_implementation(this);

         return pimp;

      }


   };


   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface< PARTICLE_INTERFACE >, PARTICLE_INTERFACE >)
   class composite :
      virtual public PARTICLE_INTERFACE
   {
   public:


      ::pointer < PARTICLE_INTERFACE > m_pparticleThis;

      composite();

      ~composite() override
      {

      }

      template < typename IMPL >
      IMPL * impl()
      {
         ::cast < IMPL > pimp = ::subsystem::get_implementation(this);

         return pimp;

      }



   };


   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface< PARTICLE_INTERFACE >, PARTICLE_INTERFACE >)
   class implementation :
   virtual public PARTICLE_INTERFACE
   {
   public:


      ::pointer < composite < PARTICLE_INTERFACE > > m_pcomposite;


      implementation()
      {

         this->m_eparticle = e_particle_implementation;

      }

      ~implementation() override
      {

      }


      template < typename IMPL >
      IMPL * impl()
      {

         ::cast < IMPL > pimp = ::subsystem::get_implementation(this);

         return pimp;

      }

   };


   template < typename PARTICLE_INTERFACE, typename TYPE >
   PARTICLE_INTERFACE * _get_implementation(const TYPE * pinterface)
   {

      if (::is_null(pinterface))
      {

         return nullptr;

      }

      ::cast < implementation < PARTICLE_INTERFACE > > pimplementation = pinterface;

      if (pimplementation)
      {

         return pimplementation;

      }

      ::cast < composite < PARTICLE_INTERFACE > > pcomposite = pinterface;

      if (pcomposite)
      {

         auto pcomposed = pcomposite->m_pparticleThis.m_p;

         if (::is_null(pcomposed))
         {

            return nullptr;

         }
         else if (pcomposed == pinterface)
         {

            throw ::exception(error_wrong_state);

         }

         return _get_implementation<PARTICLE_INTERFACE>(pcomposed);

      }

      ::cast < PARTICLE_INTERFACE > pparticleinterface = pinterface;

      return pparticleinterface;

   }


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::particle_interface< PARTICLE_INTERFACE > * pinterface)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pinterface);

   }


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::composite< PARTICLE_INTERFACE > * pcomposite)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pcomposite);

   }


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const ::subsystem::implementation< PARTICLE_INTERFACE > * pimplementation)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pimplementation);

   }


   template < typename PARTICLE_INTERFACE >
   requires(::std::is_base_of_v<::subsystem::particle_interface< PARTICLE_INTERFACE >, PARTICLE_INTERFACE >)
   composite<PARTICLE_INTERFACE>::composite()
   {

      ::main_subsystem()->constructø(m_pparticleThis);

      auto pimpl = impl<implementation<PARTICLE_INTERFACE>>();

      pimpl->m_pcomposite = this;

   }


} // namespace subsystem



