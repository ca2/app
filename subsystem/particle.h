// Create by camilo on beginning of 2026-April <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem/subsystem.h"



   //template<typename PARTICLE_INTERFACE, typename BASE>
   //PARTICLE_INTERFACE *get_implementation(const particle_interface<PARTICLE_INTERFACE, BASE> *pinterface);

   template<typename PARTICLE_INTERFACE, typename TYPE>
   PARTICLE_INTERFACE *_get_implementation(const TYPE *pinterface);

   //template<typename PARTICLE_INTERFACE, typename BASE>
   //PARTICLE_INTERFACE *get_implementation(const particle_interface<PARTICLE_INTERFACE, BASE> *pinterface);

   template<typename PARTICLE_INTERFACE>
   PARTICLE_INTERFACE *get_implementation(const Composite<PARTICLE_INTERFACE> *pcomposite);

   template<typename PARTICLE_INTERFACE, typename BASE>
   PARTICLE_INTERFACE *get_implementation(const Implementation<PARTICLE_INTERFACE, BASE> *pimplementation);


   class CLASS_DECL_SUBSYSTEM Particle : virtual public ::particle
   {
   public:

      using BASE_TYPE = ::particle;
      using INTERFACE_TYPE = Particle;

      enum_particle m_eparticle;

      Particle(enum_particle eparticle = e_particle_interface);
      ~Particle() override;

      virtual ::Particle * get_implementation();

      template<typename IMPL>
      IMPL *impl();


      //virtual operator ::particle* () { return get_implementation();
      //}


      //virtual void set_composite
      // virtual particle_base* get_base_composite()
      //{

      //   return nullptr;

      //}
   };


   //template<typename PARTICLE_SLICE, typename BASE_PARTICLE_INTERFACE>
   //class particle_interface:
   //   virtual public PARTICLE_SLICE,
   //   virtual public BASE_PARTICLE_INTERFACE
   //{
   //public:

   //   using class_type = interface_t;
   //   using BASE_TYPE = BASE_PARTICLE_INTERFACE;
   //   using INTERFACE_TYPE = PARTICLE_SLICE;
   //   using BASE_INTERFACE_TYPE = typename BASE_TYPE::INTERFACE_TYPE;

   //   template<typename IMPL>
   //   IMPL *impl() const
   //   {
   //      ::cast<IMPL> pimp = get_implementation(this);

   //      return pimp;
   //   }
   //};


   //template<typename PARTICLE_SLICE >
   //class particle_interface <PARTICLE_SLICE>:
   //   virtual public PARTICLE_SLICE
   //{
   //public:

   //   using class_type = interface_t;
   //   using BASE_TYPE = ::particle_base;
   //   using INTERFACE_TYPE = PARTICLE_SLICE;
   //   using BASE_INTERFACE_TYPE = typename BASE_TYPE::INTERFACE_TYPE;

   //   template<typename IMPL>
   //   IMPL *impl() const
   //   {
   //      ::cast<IMPL> pimp = get_implementation(this);

   //      return pimp;
   //   }
   //};


   template < typename PARTICLE_SLICE >
   class Callback :
   virtual public PARTICLE_SLICE
   {
   public:
      //BASE m_base;

      //::pointer < PARTICLE_SLICE > m_pcomposite;

      ~Callback() override
      {

      }

   };

   //operator Name##Interface *() { return m_p##name; } \
   //operator Name##Interface *() const { return m_p##name; } \

   #define ImplementCompositeø(Name, name) \
   ::pointer<Name##Interface> m_p##name; \
   ::Particle * get_implementation() {return m_p##name.m_p;} \
   virtual void set##Name##Implementation(Name##Interface * pinterfaceImplementation) \
   { \
      m_p##name = pinterfaceImplementation; \
   }


 #define ImplementCallbackø(Name, name) \
 ::pointer<Composite<Name##Interface>> m_p##name##Callback; \
 ::Particle *get_callback() { return m_p##name##Callback.m_p; } \
 void set##Name##Composite(Composite < Name##Interface > * pcompositeCallback) \
 { \
 m_p##name##Callback = pcompositeCallback; \
 }

#define ImplementCompositeWithCallbackø(Name, name)                                                                             \
::pointer<Name##Interface> m_p##name;                                                                            \
::Particle *get_implementation() { return m_p##name.m_p; }                                                       \
virtual void set##Name##Implementation(Name##Interface *pinterfaceImplementation)                                \
{                                                                                                                \
   m_p##name = pinterfaceImplementation;                                                                         \
   ::cast<Name##Callback> pcallback = pinterfaceImplementation;                       \
   if (pcallback)                                                                                         \
   {                                                                                                             \
      pcallback->m_p##name##Callback = this;                                                                     \
   }                                                                                                             \
}


   // #define implement_base_compositeø(Name, name) \
   // ::pointer<Name##Interface> m_p##name; \
   // operator Name##Interface *() { return m_p##name; } \
   // operator Name##Interface *() const { return m_p##name; } \
   // void set##Name##Composite(Name##Interface * pinterfaceImplementation) \
   // { \
   // m_p##name = pinterfaceImplementation \
   // ::cast < implementation1<Name##Interface> > pimplementation1 = pinterfaceImplementation; \
   // pimplementation1->m_pcomposite = this; \
   // }

//auto pimpl = impl<implementation<Name##Interface>>();
//if(pimpl) pimpl->m_pcomposite = this;
//::main_subsystem()->constructø(m_p##name); \





   template < typename PARTICLE_INTERFACE >
   class Composite :
      virtual public PARTICLE_INTERFACE
   {
   public:


      using INTERFACE_TYPE = PARTICLE_INTERFACE;

      //BASE m_base;

      //::pointer < PARTICLE_INTERFACE > m_pparticleThis;

      //composite();

      //~composite() override
      //{

      //}

      template < typename IMPL >
      IMPL * impl()
      {

         ::cast < IMPL > pimp = get_implementation(this);

         return pimp;

      }

      //operator PARTICLE_INTERFACE *() { return m_pparticleThis; }
      //operator PARTICLE_INTERFACE *() const { return m_pparticleThis; }
      
      
      //particle_base *get_base_composite() override 
      //{
      //   
      //   using BASE1 = typename PARTICLE_INTERFACE::BASE_TYPE;

      //   using INTERFACE1 = typename BASE1::INTERFACE_TYPE;

      //   if constexpr (std::is_base_of_v<composite<INTERFACE1>, PARTICLE_INTERFACE>)
      //   {

      //      auto p = dynamic_cast<composite<INTERFACE1> *>(this);

      //      if (p)
      //      {

      //         return p->m_pparticleThis;

      //      }

      //   }

      //   return m_pparticleThis; 
      //
      //}


   };



   //template<typename PARTICLE_INTERFACE>
   //class composite<PARTICLE_INTERFACE, ::particle_base > :
   //   virtual public PARTICLE_INTERFACE
   //{
   //public:


   //   ::pointer<PARTICLE_INTERFACE> m_pparticleThis;

   //   composite();

   //   ~composite() override {}

   //   template<typename IMPL>
   //   IMPL *impl()
   //   {
   //      ::cast<IMPL> pimp = get_implementation(this);

   //      return pimp;
   //   }


   //   
   //   operator PARTICLE_INTERFACE *() { return m_pparticleThis; }
   //   operator PARTICLE_INTERFACE *() const { return m_pparticleThis; }


   //   // particle_base *get_base_composite() override
   //   //{
   //   //
   //   //    using BASE1 = typename PARTICLE_INTERFACE::BASE_TYPE;

   //   //   using INTERFACE1 = typename BASE1::INTERFACE_TYPE;

   //   //   if constexpr (std::is_base_of_v<composite<INTERFACE1>, PARTICLE_INTERFACE>)
   //   //   {

   //   //      auto p = dynamic_cast<composite<INTERFACE1> *>(this);

   //   //      if (p)
   //   //      {

   //   //         return p->m_pparticleThis;

   //   //      }

   //   //   }

   //   //   return m_pparticleThis;
   //   //
   //   //}
   //};


   //template<typename PARTICLE_INTERFACE, typename BASE>
   //class composite : 
   //   virtual public composite1<PARTICLE_INTERFACE>,
   //   virtual public BASE
   //{
   //public:


   //   composite()
   //   {


   //   }

   //   ~composite() override 
   //   {
   //   
   //   }


   //   PARTICLE_INTERFACE *get() { return composite1<PARTICLE_INTERFACE> ::m_pparticleThis.m_p; }
   //   PARTICLE_INTERFACE *get() const { return composite1<PARTICLE_INTERFACE> ::m_pparticleThis.m_p; }


   //   operator PARTICLE_INTERFACE *() { return this->get(); }
   //   operator PARTICLE_INTERFACE *() const { return this->get(); }


   //   // particle_base *get_base_composite() override
   //   //{
   //   //
   //   //    using BASE1 = typename PARTICLE_INTERFACE::BASE_TYPE;

   //   //   using INTERFACE1 = typename BASE1::INTERFACE_TYPE;

   //   //   if constexpr (std::is_base_of_v<composite<INTERFACE1>, PARTICLE_INTERFACE>)
   //   //   {

   //   //      auto p = dynamic_cast<composite<INTERFACE1> *>(this);

   //   //      if (p)
   //   //      {

   //   //         return p->m_pparticleThis;

   //   //      }

   //   //   }

   //   //   return m_pparticleThis;
   //   //
   //   //}
   //};

   //   template<typename PARTICLE_INTERFACE >
   //class implementation : virtual public PARTICLE_INTERFACE
   //{
   //public:


   //   ::pointer<composite<PARTICLE_INTERFACE>> m_pcomposite;


   //   implementation1() { this->m_eparticle = e_particle_implementation; }

   //   ~implementation1() override {}


   //   template<typename IMPL>
   //   IMPL *impl()
   //   {

   //      ::cast<IMPL> pimp = get_implementation(this);

   //      return pimp;
   //   }
   //};



   template < typename PARTICLE_SLICE, typename BASE >
   class Implementation :
      virtual public PARTICLE_SLICE,
      virtual public BASE
   {
   public:

      using BASE_TYPE1 = BASE;


      ///::pointer < Composite < PARTICLE_SLICE > > m_pcomposite;


      Implementation()
      {

         //this->m_eparticle = e_particle_implementation;

      }

      ~Implementation() override
      {

      }


      template < typename IMPL >
      IMPL * impl()
      {

         ::cast < IMPL > pimp = get_implementation(this);

         return pimp;

      }






   };


   template<typename PARTICLE_INTERFACE>
   class Implementation<PARTICLE_INTERFACE, Particle >  :
      virtual public PARTICLE_INTERFACE
   {
   public:


      //::pointer<Composite<PARTICLE_INTERFACE>> m_pcomposite;


      Implementation() { this->m_eparticle = e_particle_implementation; }

      ~Implementation() override {}


      template<typename IMPL>
      IMPL *impl()
      {

         ::cast<IMPL> pimp = get_implementation(this);

         return pimp;
      }
   };

//operator Name##Interface *() { return Name##Composite::operator Name##Interface *(); }
//operator Name##Interface *() const { return Name##Composite::operator Name##Interface *(); }

// #define ImplementAggregateø(Name, Base) \
// using MAIN_AGGREGATE_INTERFACE_TYPE = typename Aggregate<Name##Composite, Base##Aggregate>::MAIN_AGGREGATE_INTERFACE_TYPE; \
// Name##Aggregate() \
// { \
//    auto pinterfaceImplementation = ::main_subsystem()->createø<Name##Interface>(); \
//    this->set##Name##Composite(pinterfaceImplementation); \
//    ::cast<Base##Interface> pbase = pinterfaceImplementation; \
//    this->set##Base##Composite(pbase);                                    \
//       }

#define ImplementAggregateø(Name, Base) \
using MAIN_AGGREGATE_INTERFACE_TYPE = typename Aggregate<Name##Composite, Base##Aggregate>::MAIN_AGGREGATE_INTERFACE_TYPE; \
Name##Aggregate() \
{ \
}  \
virtual void set##Name##Implementation(MAIN_AGGREGATE_INTERFACE_TYPE * pimpl)                                                                                                         \
{                                                                                                                \
   Name##Composite::set##Name##Implementation(pimpl);                                                         \
   ::cast<Base##Interface> pimplBase = pimpl; \
   this->set##Base##Implementation(pimplBase);                                    \
}


//operator Name##Interface *() { return Name##Composite::operator Name##Interface *(); }
//operator Name##Interface *() const { return Name##Composite::operator Name##Interface *(); } \


// #define ImplementBaseø(Name)                                                                                       \
// using MAIN_AGGREGATE_INTERFACE_TYPE = typename Aggregate<Name##Composite>::MAIN_AGGREGATE_INTERFACE_TYPE; \
// Name##Aggregate()                                                                                                         \
// {                                                                                                                \
//    auto pinterfaceImplementation = ::main_subsystem()->createø<Name##Interface>();                               \
//    this->set##Name##Composite(pinterfaceImplementation);                                                         \
// }

#define ImplementBaseø(Name)                                                                                       \
using MAIN_AGGREGATE_INTERFACE_TYPE = typename Aggregate<Name##Composite>::MAIN_AGGREGATE_INTERFACE_TYPE; \
Name##Aggregate()                                                                                                         \
{                                                                                                                \
}  \
virtual void set##Name##Implementation(MAIN_AGGREGATE_INTERFACE_TYPE * pimpl)                                                                                                         \
{                                                                                                                \
Name##Composite::set##Name##Implementation(pimpl);                                                         \
}

//auto pinterfaceImplementation = pimpl;                               \
//this->set##Name##Implementation(pinterfaceImplementation);                                                         \


   template < typename COMPOSITE, typename BASE_AGGREGATE >
   class Aggregate :
      virtual public COMPOSITE,
      virtual public BASE_AGGREGATE
   {
   public:

      using MAIN_AGGREGATE_INTERFACE_TYPE = typename COMPOSITE::INTERFACE_TYPE;

      ::Particle * get_implementation() override
      {
         return COMPOSITE::get_implementation();
      }



   };


   template<typename COMPOSITE >
   class Aggregate< COMPOSITE, ::Particle > :
      virtual public COMPOSITE
   {
   public:

      using MAIN_AGGREGATE_INTERFACE_TYPE = typename COMPOSITE::INTERFACE_TYPE;


   };



   template < typename PARTICLE_INTERFACE, typename TYPE >
   PARTICLE_INTERFACE * _get_implementation(const TYPE * pinterfaceConst)
   {

      if (::is_null(pinterfaceConst))
      {

         return nullptr;

      }

      auto pinterface = (TYPE *) pinterfaceConst;

      ::cast < Implementation < PARTICLE_INTERFACE > > pimplementation = pinterface;

      if (pimplementation)
      {

         return pimplementation;

      }

      ::cast < Composite < PARTICLE_INTERFACE > > pcomposite = pinterface;

      if (pcomposite)
      {

         auto pcomposed = pcomposite->get_implementation();

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


   //template < typename PARTICLE_INTERFACE >
   //PARTICLE_INTERFACE * get_implementation(const particle_interface< PARTICLE_INTERFACE > * pinterface)
   //{

   //   return _get_implementation<PARTICLE_INTERFACE>(pinterface);

   //}


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const Composite< PARTICLE_INTERFACE > * pcomposite)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pcomposite);

   }


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const Implementation< PARTICLE_INTERFACE > * pimplementation)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pimplementation);

   }


   //template < typename PARTICLE_INTERFACE, typename BASE >
   //composite<PARTICLE_INTERFACE, BASE>::composite()
   //{

   //   //auto pbase = this->get_base_composite();

   //   //if (pbase)
   //   //{

   //   //   m_pparticleThis = pbase;

   //   //}

   //   //if (!m_pparticleThis)
   //   {

   //      ::main_subsystem()->constructø(m_pparticleThis);

   //   }

   //   auto pimpl = impl<implementation<PARTICLE_INTERFACE>>();

   //   pimpl->m_pcomposite = this;

   //}


   //template<typename PARTICLE_INTERFACE>
   //composite<PARTICLE_INTERFACE>::composite()
   //{

   //   // auto pbase = this->get_base_composite();

   //   // if (pbase)
   //   //{

   //   //   m_pparticleThis = pbase;

   //   //}

   //   // if (!m_pparticleThis)
   //   {

   //      ::main_subsystem()->constructø(m_pparticleThis);
   //   }

   //   auto pimpl = impl<implementation<PARTICLE_INTERFACE>>();

   //   pimpl->m_pcomposite = this;
   //}


template<typename IMPL>
IMPL *Particle::impl()
   {

      ::cast<IMPL> pimp = ::_get_implementation<IMPL>(get_implementation());

      return pimp;

   }


#define ImplementObjectø(Name)                                                                                       \
using MAIN_AGGREGATE_INTERFACE_TYPE = typename Name##Aggregate::MAIN_AGGREGATE_INTERFACE_TYPE;                       \
Name()                                                                                                         \
{                                                                                                                \
auto pinterfaceImplementation = ::main_subsystem()->createø<Name##Interface>();                               \
this->set##Name##Implementation(pinterfaceImplementation);                                                         \
}                                                                                                    \
operator MAIN_AGGREGATE_INTERFACE_TYPE *() { return this->impl<MAIN_AGGREGATE_INTERFACE_TYPE>(); }


   template<typename AGGREGATE >
   class Object : virtual public AGGREGATE
   {
   public:
      using INTERFACE_TYPE = AGGREGATE::MAIN_AGGREGATE_INTERFACE_TYPE;
   };

//} // namespace subsystem



