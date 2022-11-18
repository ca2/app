#pragma once


#include "acme/primitive/collection/atom_map.h"
#include "acme/primitive/primitive/particle.h"
#include "acme/primitive/primitive/pointer.h"
#include "acme/primitive/primitive/type.h"
//#include "acme/exception/exception.h"
//#include "acme/platform/library.h"


CLASS_DECL_ACME ::string demangle(const char * pszMangledName);


CLASS_DECL_ACME ::critical_section * factory_critical_section();

template < typename TYPE >
inline void __defer_construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory* pfactory = ::factory::get_factory());

namespace factory
{


   class CLASS_DECL_ACME factory_item_interface :
      virtual public ::particle
   {
   public:


      factory_item_interface();
      ~factory_item_interface() override;


      virtual string base_type_name() const = 0;

      virtual string __type_name() const = 0;

      virtual ::pointer < ::particle > create_particle() = 0;

      virtual void return_back(::particle * pelement) = 0;


   };


   template < typename ORIGIN_TYPE >
   class factory_item_base :
      public factory_item_interface
   {
   public:


      string base_type_name() const override { return ::demangle(typeid(ORIGIN_TYPE).name()); }

      virtual ::pointer<ORIGIN_TYPE> _create() = 0;

      virtual ::pointer < ::particle > create_particle() override
      {

         return _create();

      }

      virtual void return_back(::particle * pelement) override
      {

         delete pelement;

      }


   };


   template < typename TYPE, typename ORIGIN_TYPE >
   class factory_item :
      public factory_item_base < ORIGIN_TYPE >
   {
   public:


      string __type_name() const override { return ::demangle(typeid(TYPE).name()); }


      ::pointer<ORIGIN_TYPE>_create() override
      {

         return __new(TYPE);
            
      }


   };


   template < typename TYPE, typename ORIGIN_TYPE >
   class reusable_factory_item :
      public factory_item < TYPE, ORIGIN_TYPE >
   {
   public:

      critical_section   m_criticalsection;

      ORIGIN_TYPE * m_pfree;

      ~reusable_factory_item()
      {

         free_all();

      }

      ::pointer<ORIGIN_TYPE>_create() override;

      void return_back(ORIGIN_TYPE * p);

      void free_all()
      {

         while (m_pfree)
         {

            auto p = m_pfree;

            m_pfree = m_pfree->m_pnext;

            try
            {

               delete p;

            }
            catch (...)
            {

            }

         }

      }

   };


   using factory_base = atom_map < ::pointer<factory_item_interface > >;


   class CLASS_DECL_ACME factory :
      virtual public factory_base
   {
   public:


      ::atom                                 m_atomSource;
      ::pointer<::acme::library>             m_plibrary;


      factory();
      ~factory();


      inline ::pointer<::factory::factory_item_interface>& get_factory_item(const ::atom & atom);

      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::atom& atom, const ::atom & atomSource);

      inline ::factory::factory_item_interface * get_factory_item(const ::atom& atom) const;

      //inline ::factory::factory_item_interface * get_factory_item_from(const ::atom& atom, const ::atom & atomSource) const;

      template < typename ORIGIN_TYPE >
      inline ::pointer<::factory::factory_item_interface>& get_factory_item();

      template < typename ORIGIN_TYPE >
      inline ::pointer<::factory::factory_item_interface>& get_factory_item(const ::atom& atom);

      template < typename BASE_TYPE >
      inline void __defer_construct(::particle * pparticle, ::pointer<BASE_TYPE> &  ptype);


      //template < typename ORIGIN_TYPE >
      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::atom & atomSource);

      template < typename TYPE, typename ORIGIN_TYPE = TYPE >
      inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item();

      //template < typename TYPE, typename ORIGIN_TYPE >
      //inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item_from(const ::atom& atomSource);


      template < typename ORIGIN_TYPE >
      inline ::pointer<ORIGIN_TYPE>create();

      void merge(const ::factory::factory* pfactory);

      void merge_to_global_factory() const;

      void set_currently_loading_library();


      template < typename ORIGIN_TYPE >
      inline void __defer_raw_construct(::pointer<ORIGIN_TYPE> & p)
      {

         if (::is_null(p))
         {

            this->__raw_construct(p);

         }

      }


      template < typename ORIGIN_TYPE >
      inline void __construct(::particle * pparticleInitializer, ::pointer<ORIGIN_TYPE> & p);


      template < typename ORIGIN_TYPE >
      inline void __raw_construct(::pointer<ORIGIN_TYPE> & p);


      virtual ::pointer < ::particle > create(const ::string & strType);


      virtual bool has_type(const ::string & strType) const;


   };



   using factory_array = pointer_array < factory_item_interface >;

   CLASS_DECL_ACME factory * get_factory();

   CLASS_DECL_ACME factory * get_factory(const ::atom & atomSource);


   ::pointer<factory_item_interface>& get_factory_item(const ::atom & atom);


   ::pointer<factory_item_interface>& get_existing_factory_item(const ::atom & atom);


   ::pointer<factory_item_interface>& get_factory_item(const ::atom & atom, const ::atom & atomSource);


   bool has(const ::atom& atom);
   

   
   void set_factory(const ::atom & atom, const ::pointer<factory_item_interface>& pfactory);

   template < typename ORIGIN_TYPE >
   inline ::atom get_atom()
   {

      auto pszTypename = typeid(ORIGIN_TYPE).name();

#ifdef WINDOWS

      pszTypename = c_demangle(pszTypename);

      return pszTypename;

#else

      auto strTypename = ::move(demangle(pszTypename));

      return strTypename;


#endif

   }


   template < typename ORIGIN_TYPE >
   inline ::pointer<factory_item_interface>& get_factory_item()
   {

      //static auto atom = get_atom<ORIGIN_TYPE>();

      //return get_factory_item(atom);

      return get_factory_item(get_atom<ORIGIN_TYPE>());

   }


   template < typename ORIGIN_TYPE >
   inline ::pointer<factory_item_interface> get_factory_item(const ::atom & atomSource)
   {

      //static auto atom = get_atom<ORIGIN_TYPE>();

      //return get_factory_item(atom, atomSource);

      ///static auto atom = get_atom<ORIGIN_TYPE>();

      return get_factory_item(atomSource, get_atom<ORIGIN_TYPE>());

   }


} // namespace factory


using factory_pointer = ::pointer<::factory::factory>;


namespace factory
{


   template < typename TYPE, typename ORIGIN_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item();


   template < typename TYPE, typename ORIGIN_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item(const ::atom& atom);


   template < typename TYPE, typename ORIGIN_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item_from(const ::atom& atomSource);


   template < typename TYPE, typename ORIGIN_TYPE = TYPE >
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > create_reusable_factory();


   template < typename TYPE >
   ::pointer<TYPE>create();


} // namespace factory






namespace factory
{


   //CLASS_DECL_ACME critical_section * ::factory_critical_section();


   template < typename TYPE, typename ORIGIN_TYPE>
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item(const ::atom & atom)
   {

      critical_section_lock lock(::factory_critical_section());

      auto pfactory = __new(::factory::factory_item< TYPE, ORIGIN_TYPE >());

      ::factory::get_factory()->set_at(atom, pfactory);

      return pfactory;

   }


   CLASS_DECL_ACME::factory::factory * loading_library_factory();


   template < typename TYPE, typename ORIGIN_TYPE>
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > _add_factory_item_from(const ::atom & atomSource)
   {

      critical_section_lock lock(::factory_critical_section());

      auto pfactory = ::factory::loading_library_factory();

      if (::is_set(pfactory))
      {

         return pfactory->add_factory_item < TYPE, ORIGIN_TYPE >();

      }

      auto pfactoryitem = __new(::factory::factory_item< TYPE, ORIGIN_TYPE >());

      ::factory::get_factory_item < ORIGIN_TYPE >(atomSource) = pfactoryitem;

      return pfactoryitem;

   }


   template < typename TYPE, typename ORIGIN_TYPE>
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item()
   {

      critical_section_lock lock(::factory_critical_section());

      auto pfactory = __new(::factory::factory_item< TYPE, ORIGIN_TYPE >());

      ::factory::get_factory_item < ORIGIN_TYPE >() = pfactory;

      return pfactory;

   }


   template < typename TYPE, typename ORIGIN_TYPE>
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > create_reusable_factory()
   {

      critical_section_lock lock(::factory_critical_section());

      auto pfactory = __new(::factory::reusable_factory_item< TYPE, ORIGIN_TYPE >());

      ::factory::get_factory_item < ORIGIN_TYPE >() = pfactory;

      return pfactory;

   }


} // namespace factory




namespace factory
{


   template < typename TYPE, typename ORIGIN_TYPE >
   inline ::pointer<ORIGIN_TYPE>reusable_factory_item < TYPE, ORIGIN_TYPE >::_create()
   {

      {

         critical_section_lock lock(&m_criticalsection);

         if (m_pfree)
         {

            auto pNew = m_pfree;

            m_pfree = pNew->m_pnext;

            pNew->reuse();

            return pNew;

         }

      }

      return factory_item < TYPE, ORIGIN_TYPE >::_call_new();

   }


   template < typename TYPE, typename ORIGIN_TYPE >
   inline void reusable_factory_item < TYPE, ORIGIN_TYPE >::return_back(ORIGIN_TYPE * p)
   {

      critical_section_lock lock(&m_criticalsection);

      p->m_pnext = m_pfree;

      m_pfree = p;

   }


   template < typename ORIGIN_TYPE >
   inline ::pointer<ORIGIN_TYPE>factory::create()
   {

      auto pfactoryinterface = get_factory_item < ORIGIN_TYPE >();

      if (!pfactoryinterface)
      {

         throw_exception(error_no_factory);

      }

      return pfactoryinterface->create_particle();

   }


   template < typename TYPE, typename ORIGIN_TYPE>
   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > factory::add_factory_item()
   {

      critical_section_lock lock(::factory_critical_section());

      auto pfactory = __new(::factory::factory_item< TYPE, ORIGIN_TYPE >());

      this->get_factory_item < ORIGIN_TYPE >() = pfactory;

      return pfactory;

   }


   template < typename ORIGIN_TYPE >
   inline void factory::__construct(::particle * pparticleInitializer, ::pointer < ORIGIN_TYPE > & p)
   {

      __raw_construct(p);

      p->initialize(pparticleInitializer);

   }


   template < typename ORIGIN_TYPE >
   inline void factory::__raw_construct(::pointer<ORIGIN_TYPE>  & p)
   {

      auto & pfactoryitem = get_factory_item < ORIGIN_TYPE >();

      if (!pfactoryitem)
      {

         throw ::exception(error_no_factory, "Factory hasn't creator for type \"" + __type_name<ORIGIN_TYPE>() + "\"");

      }

      auto pparticle = ::move(pfactoryitem->create_particle());

      if (!pparticle)
      {

         throw ::exception(error_no_memory, "Couldn't create_particle for type \"" + __type_name<ORIGIN_TYPE>() + "\"");

      }

      p = pparticle;

      if (!p)
      {

         throw ::exception(error_wrong_type, "Created element is not of the base type \"" + __type_name<ORIGIN_TYPE>() + "\"");

      }

   }



   inline ::factory::factory_item_interface * factory::get_factory_item(const ::atom & atom) const
   {

      critical_section_lock cs(::factory_critical_section());

      auto p = this->plookup(atom);

      if (!p)
      {

         return nullptr;

      }

      return p->m_element2;

   }


   template < typename ORIGIN_TYPE >
   inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item()
   {

      string strTypename(typeid(ORIGIN_TYPE).name());

      strTypename = ::demangle(strTypename);

      return get_factory_item(strTypename);

   }


   inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item(const ::atom & atom)
   {

      critical_section_lock cs(::factory_critical_section());


      return this->operator[](atom);

   }


   inline ::pointer<factory_item_interface> & get_factory_item(const ::atom & atom)
   {

      critical_section_lock cs(::factory_critical_section());

      return (*get_factory())[atom];

   }


   inline ::pointer<factory_item_interface> & get_existing_factory_item(const ::atom & atom)
   {

      auto & pfactoryitem = get_factory_item(atom);

      if (!pfactoryitem)
      {

         throw_exception(error_no_factory, "No factory for \"" + atom + "\"");

      }

      return pfactoryitem;

   }


   inline ::pointer<factory_item_interface> & get_factory_item(const ::atom & atom, const ::atom & atomSource)
   {

      critical_section_lock cs(::factory_critical_section());

      return (*get_factory(atomSource))[atom];

   }


   inline bool has(const ::atom & atom)
   {

      critical_section_lock cs(::factory_critical_section());

      auto passociation = get_factory()->get_association(atom);

      if (::is_null(passociation))
      {

         return false;

      }

      if (::is_null(passociation->m_element2))
      {

         return false;

      }

      return true;

   }



   inline void set_factory(const ::atom & atom, const ::pointer<factory_item_interface> & pfactory)
   {

      critical_section_lock cs(::factory_critical_section());

      get_factory()->set_at(atom, pfactory);

   }


   inline void set_factory_from(const ::atom & atom, const ::atom & atomSource, const ::pointer<factory_item_interface> & pfactory)
   {

      critical_section_lock cs(::factory_critical_section());

      get_factory(atomSource)->set_at(atom, pfactory);

   }


   template < typename TYPE, typename BASE >
   inline void add_factory_item(const ::atom & atom)
   {

      set_factory(atom, __new(factory_item < TYPE, BASE >()));

   }


   //template < typename TYPE >
   //inline stream & load_object(stream & stream, ::pointer<TYPE>& p)
   //{

   //   string strText;

   //   stream >> strText;

   //   if (strText.is_empty() || strText.begins_eat_ci("factoryless://"))
   //   {

   //      if (p && __type_name(p)) == strText
   //      {

   //         ::output_debug_string("loading into existing matter of same class type (1)");

   //      }
   //      else
   //      {

   //         p.defer_create_new();

   //         if (!p)
   //         {

   //            ::output_debug_string("defer_new failed (1.1)");

   //            stream.set_fail_bit();

   //         }
   //         else if (__type_name(p)) != strText
   //         {

   //            ::output_debug_string("allocated matter type is different from streamed matter type (1.2)");

   //            stream.set_fail_bit();

   //         }

   //      }

   //   }
   //   else
   //   {

   //      auto atom = stream.text_to_factory_id(strText);

   //      if (p && atom == __type_name(p))
   //      {

   //         ::output_debug_string("loading into existing matter of same class type (2)");

   //      }
   //      else
   //      {

   //         p = stream.create_object_from_text(strText);

   //         if (!p)
   //         {

   //            ::output_debug_string("stream::alloc_object_from_text failed (2.1)");

   //         }
   //         else if (__type_name(p)) != atom.to_string()
   //         {

   //            ::output_debug_string("allocated matter type is different from streamed matter type (2.2)");

   //            stream.set_fail_bit();

   //         }

   //      }

   //   }

   //   if (!stream.fail())
   //   {

   //      if (p->has(e_object_factory))
   //      {

   //         p->read(stream);

   //      }
   //      else
   //      {

   //         stream >> *p;

   //      }

   //   }

   //   return stream;

   //}


} // namespace factory


//#include "_factory.h"


namespace factory
{


   template < typename BASE_TYPE >
   inline void factory::__defer_construct(::particle * pparticle, ::pointer<BASE_TYPE> & ptype)
   {

      ::__defer_construct(pparticle, ptype, this);

   }


} // namespace factory


template < typename TYPE >
inline void __raw_construct(::pointer<TYPE>& p, ::factory::factory* pfactory = ::factory::get_factory())
{

   auto& pfactoryitem = pfactory->get_factory_item< TYPE >();

   if (!pfactoryitem)
   {

      string strMessage;

      strMessage.format("matter::__construct has failed to find factory_item for type \"%s\"", __type_name < TYPE >().c_str());

      throw_exception(::error_not_implemented, strMessage);

   }

   auto pparticleNew = pfactoryitem->create_particle();

   if (!pparticleNew)
   {

      string strMessage;

      strMessage.format("matter::__construct no memory to allocate implementation of type \"%ss\"", __type_name < TYPE >().c_str());

      throw_exception(::error_no_memory, strMessage);

   }

   p.release();

   p = pparticleNew;

   if (!p)
   {

      string strMessage;

      strMessage.format("matter::__construct object(%s) is not of type \"%s\"", __type_name(*pparticleNew).c_str(), __type_name < TYPE >().c_str());

      throw_exception(::error_wrong_type, strMessage);

   }

}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE> __raw_create(::factory::factory* pfactory)
{

   ::pointer<BASE_TYPE> p;

   __raw_construct(p, pfactory);

   return ::move(p);

}


template < typename TYPE >
inline void __construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory* pfactory = ::factory::get_factory())
{

   __raw_construct(p, pfactory);

   p->initialize(pparticle);

}


template < typename BASE_TYPE >
inline ::pointer < BASE_TYPE > __create(::particle* pparticle, ::factory::factory* pfactory = ::factory::get_factory())
{

   ::pointer < BASE_TYPE > p;

   __construct(pparticle, p, pfactory);

   return p;

}


template < typename TYPE >
inline void __defer_construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory* pfactory)
{

   if (!p)
   {

      __construct(pparticle, p, pfactory);

   }


}





template < typename TYPE >
inline void __id_construct(particle* pparticle, ::pointer<TYPE>& p, const ::atom& atom, ::factory::factory* pfactory = ::factory::get_factory())
{

   auto& pfactoryitem = pfactory->get_factory_item(atom);

   auto pparticleNew = pfactoryitem->create_particle();

   //if (!pparticleNew)
   //{

   //   return error_no_memory;

   //}

   p = pparticleNew;

   if (!p)
   {

      throw_exception(error_wrong_type);

   }

   p->set_flag(e_flag_factory);

   //auto estatus =

   p->initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


template < typename TYPE >
inline ::pointer < TYPE > __id_create(particle* pparticle, const ::atom& atom, ::factory::factory* pfactory = ::factory::get_factory())
{

   auto& pfactoryitem = pfactory->get_factory_item(atom);

   auto pparticleNew = pfactoryitem->create_particle();

   //if (!pparticleNew)
   //{

   //   return error_no_memory;

   //}

   

   ::pointer < TYPE > p = pparticleNew;

   if (!p)
   {

      throw_exception(error_wrong_type);

   }

   p->set_flag(e_flag_factory);

   //auto estatus =

   p->initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

   return p;

}


template < class T >
template < typename PARTICLE >
inline pointer < T >& pointer < T >::create(PARTICLE* pparticle, ::factory::factory* pfactory)
{

   auto p = ::__create < T >(pparticle);

   return operator =(p);

}



