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
   PARTICLE_INTERFACE *get_implementation(const composite<PARTICLE_INTERFACE> *pcomposite);

   template<typename PARTICLE_INTERFACE, typename BASE>
   PARTICLE_INTERFACE *get_implementation(const implementation<PARTICLE_INTERFACE, BASE> *pimplementation);


   class CLASS_DECL_SUBSYSTEM particle_base : virtual public ::particle
   {
   public:

      using BASE_TYPE = ::particle;
      using INTERFACE_TYPE = particle_base;

      enum_particle m_eparticle;

      particle_base(enum_particle eparticle = e_particle_interface);
      ~particle_base() override;

      virtual ::particle_base * get_implementation();

      template<typename IMPL>
      IMPL *impl();

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
   class implementation1 :
   virtual public PARTICLE_SLICE
   {
   public:
      //BASE m_base;

      ::pointer < PARTICLE_SLICE > m_pcomposite;

      ~implementation1() override
      {

      }

   };


   #define implement_compositeø(Name, name) \
   ::pointer<Name##Interface> m_p##name; \
   operator Name##Interface *() { return m_p##name; } \
   operator Name##Interface *() const { return m_p##name; } \
   ::particle_base * get_implementation() {return m_p##name.m_p;} \
   void set##Name##Composite(Name##Interface * pinterfaceImplementation) \
   { \
      m_p##name = pinterfaceImplementation; \
      ::cast < ::implementation1<Name##Interface> > pimplementation1 = pinterfaceImplementation; \
      pimplementation1->m_pcomposite = this; \
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
   class composite :
      virtual public PARTICLE_INTERFACE
   {
   public:

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
   class implementation :
      virtual public PARTICLE_SLICE,
      virtual public BASE
   {
   public:

      using BASE_TYPE1 = BASE;

      ::pointer < composite < PARTICLE_SLICE > > m_pcomposite;

      implementation()
      {

         //this->m_eparticle = e_particle_implementation;

      }

      ~implementation() override
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
   class implementation<PARTICLE_INTERFACE, particle_base >  :
      virtual public PARTICLE_INTERFACE
   {
   public:


      ::pointer<composite<PARTICLE_INTERFACE>> m_pcomposite;


      implementation() { this->m_eparticle = e_particle_implementation; }

      ~implementation() override {}


      template<typename IMPL>
      IMPL *impl()
      {

         ::cast<IMPL> pimp = get_implementation(this);

         return pimp;
      }
   };


#define implement_aggregateø(Name, Base) \
operator Name##Interface *() { return Name##Composite::operator Name##Interface *(); } \
operator Name##Interface *() const { return Name##Composite::operator Name##Interface *(); } \
Name() \
{ \
   auto pinterfaceImplementation = ::main_subsystem()->createø<Name##Interface>(); \
   this->set##Name##Composite(pinterfaceImplementation); \
   ::cast<Base##Interface> pbase = pinterfaceImplementation; \
   this->set##Base##Composite(pbase);                                    \
      }

#define implement_baseø(Name)                                                                                       \
operator Name##Interface *() { return Name##Composite::operator Name##Interface *(); } \
operator Name##Interface *() const { return Name##Composite::operator Name##Interface *(); } \
Name()                                                                                                           \
{                                                                                                                \
   auto pinterfaceImplementation = ::main_subsystem()->createø<Name##Interface>();                               \
   this->set##Name##Composite(pinterfaceImplementation);                                                         \
}

   template < typename COMPOSITE, typename BASE_AGGREGATE >
   class aggregate :
      virtual public COMPOSITE,
      virtual public BASE_AGGREGATE
   {
   public:


      ::particle_base * get_implementation() override
      {
         return COMPOSITE::get_implementation();
      }

   };


   template<typename COMPOSITE >
   class aggregate< COMPOSITE, ::particle_base > :
      virtual public COMPOSITE
   {
   public:
   };



   template < typename PARTICLE_INTERFACE, typename TYPE >
   PARTICLE_INTERFACE * _get_implementation(const TYPE * pinterfaceConst)
   {

      if (::is_null(pinterfaceConst))
      {

         return nullptr;

      }

      auto pinterface = (TYPE *) pinterfaceConst;

      ::cast < implementation < PARTICLE_INTERFACE > > pimplementation = pinterface;

      if (pimplementation)
      {

         return pimplementation;

      }

      ::cast < composite < PARTICLE_INTERFACE > > pcomposite = pinterface;

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


   template < typename PARTICLE_INTERFACE, typename BASE >
   PARTICLE_INTERFACE * get_implementation(const composite< PARTICLE_INTERFACE > * pcomposite)
   {

      return _get_implementation<PARTICLE_INTERFACE>(pcomposite);

   }


   template < typename PARTICLE_INTERFACE >
   PARTICLE_INTERFACE * get_implementation(const implementation< PARTICLE_INTERFACE > * pimplementation)
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
IMPL *particle_base::impl()
   {

      ::cast<IMPL> pimp = ::_get_implementation<IMPL>(get_implementation());

      return pimp;

   }



//} // namespace subsystem



