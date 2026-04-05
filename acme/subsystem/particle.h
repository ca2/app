#pragma once


namespace subsystem
{

   CLASS_DECL_ACME void subsystem_factory(::factory::factory * pfactory);

   struct implementation_t{};

   class particle_interface :
      virtual public ::particle
   {
   public:


      particle_interface();
      ~particle_interface() override;

      virtual bool is_subsystem_implementation() const = 0;
      virtual bool is_subsystem_composite() const = 0;


   };


   template < typename PARTICLE_INTERFACE >
   requires (::std::is_base_of_v<::subsystem::particle_interface, PARTICLE_INTERFACE >)
   class composite :
      virtual public PARTICLE_INTERFACE
   {
   public:


      static bool inline s_bFactory = false;

      ::pointer < PARTICLE_INTERFACE > m_pparticleThis;

      composite() :
         composite(m_pparticleThis)
      {



      }

      //template < typename PARTICLE >
      composite(::pointer < PARTICLE_INTERFACE > & p)
      {

         if (!s_bFactory)
         {

            s_bFactory = true;

            subsystem_factory(::system()->factory());

         }

         this->initialize(::system());

         this->constructø(p);

      }


      ~composite() override
      {


      }


      virtual bool is_subsystem_implementation() const {return false; }
      virtual bool is_subsystem_composite() const {return true;}



   };




   template < typename PARTICLE_INTERFACE >
   requires (::std::is_base_of_v<::subsystem::particle_interface, PARTICLE_INTERFACE >)
   class implementation :
      virtual public PARTICLE_INTERFACE
   {
   public:


      bool is_subsystem_implementation() const override { return true; }
      bool is_subsystem_composite() const override { return false; }

   };

} // namespace subsystem