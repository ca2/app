#pragma once


#include <typeindex>

////#include "acme/exception/exception.h"
#include "acme/parallelization/critical_section.h"
#include "acme/prototype/collection/atom_map.h"
#include "acme/prototype/collection/int_map.h"
#include "acme/prototype/collection/string_map.h"

#include "acme/prototype/prototype/type.h"
#include "acme/prototype/collection/list_iterator.h"
//////#include "acme/exception/exception.h"
//#include "acme/platform/library.h"


template < typename TYPE >
using pointer_key_map_base = ::map_base < pointer_key, TYPE >;


//CLASS_DECL_ACME ::string demangle_name(const ::std::type_index & typeindex);


CLASS_DECL_ACME string type_name(const ::std::type_info& typeinfo);


//CLASS_DECL_ACME ::critical_section * factory_critical_section();
//
//template < typename TYPE >
//inline void ødefer_construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory * pfactory = nullptr);

namespace factory
{


   class CLASS_DECL_ACME factory_item_interface :
      virtual public ::particle
   {
   public:


      factory_item_interface();
      ~factory_item_interface() override;


      virtual string base_type_raw_name() const;

      virtual string base_type_name() const;

      virtual string type_raw_name() const;

      virtual string type_name() const;

      virtual ::pointer < ::subparticle > __call__create_particle();

      virtual void return_back(::subparticle * pelement);


   };


   template < typename ORIGIN_TYPE >
   class factory_item_base :
      public factory_item_interface
   {
   public:


      factory_item_base()
      {
         
         
      }

      ~factory_item_base() override
      {
         
         
      }

      string base_type_raw_name() const override { return ::type_raw_name(typeid(ORIGIN_TYPE)); }
      string base_type_name() const override { return ::type_name(typeid(ORIGIN_TYPE)); }

      virtual ::pointer<ORIGIN_TYPE> __call__create() = 0;


      /// @brief consumes a referer
      virtual ::pointer < ::subparticle > __call__create_particle() override
      {

         return __call__create();

      }


      virtual void return_back(::subparticle * pelement) override
      {

         delete pelement;

      }


   };


   template < typename TYPE, typename ORIGIN_TYPE >
   class factory_item :
      public factory_item_base < ORIGIN_TYPE >
   {
   public:

      
      factory_item()
      {
         
         
      }

      ~factory_item() override
      {
         
         
      }

      
      string type_raw_name() const override { return ::type_raw_name(typeid(TYPE)); }
      string type_name() const override { return ::type_name(typeid(TYPE)); }


      /// consumes a referer
      ::pointer<ORIGIN_TYPE>__call__create() override
      {

         return { place_t{}, __new_refdbg_continuation TYPE() };
            
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

      ::pointer<ORIGIN_TYPE>__call__create() override;

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


   //using factory_base_by_type_index_pointer = ::pointer_key_map_base < ::pointer < factory_item_interface > >;
   using factory_base_by_string = ::string_map_base<::pointer<factory_item_interface>>;
   using factory_base_by_type_index = ::map < ::std::type_index, ::pointer < factory_item_interface > >;
   using factory_base_by_custom_ipair_id = ::map_base<type_iptr_pair, ::pointer<factory_item_interface>>;


   class CLASS_DECL_ACME factory :
      virtual public ::particle
   {
   public:


      //factory_base_by_type_index_pointer   m_mapByRawNamePointer;
      factory_base_by_string                 m_mapByTypeName;
      factory_base_by_string                 m_mapByCustomNameId2;
      factory_base_by_type_index             m_mapByTypeIndex;
      factory_base_by_custom_ipair_id        m_mapByCustomIpairId;
      ::atom                                 m_atomSource;
      ::pointer<::acme::library>             m_plibrary;
      ::critical_section                     m_criticalsection;
      ::string                               m_strArgument;


      factory();
      ~factory();


      //::pointer<::factory::factory_item_interface>& get_factory_item_by_type_index(const ::std::type_index & typeindex);
      //::pointer<::factory::factory_item_interface>& get_factory_item_by_custom_id(const ::platform::type & type);

      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::platform::type & type, const ::platform::type & typeSource);

      ::factory::factory_item_interface * _get_factory_item_by_type_index(const ::std::type_index & typeindex) const;
      ::factory::factory_item_interface * _get_factory_item_by_type_name(const ::scoped_string & scopedstrTypeName) const;
      ::factory::factory_item_interface * _get_factory_item_by_type_id(const ::type_id & type_id) const;
      ::factory::factory_item_interface * _get_factory_item_by_custom_id(const ::type_custom_id & typecustomid) const;
      ::factory::factory_item_interface * _get_factory_item(const ::platform::type & type) const;

      //::factory::factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex) const;
      //::factory::factory_item_interface * get_factory_item_by_type_name(const ::scoped_string & scopedstrTypeName) const;
      //::factory::factory_item_interface * get_factory_item_by_type_id(const ::type_id & type_id) const;
      //::factory::factory_item_interface * get_factory_item_by_custom_id(const ::type_custom_id & typecustomid) const;


      bool has_factory_item_by_type_index(const ::std::type_index & typeindex) const;
      bool has_factory_item_by_type_name(const ::scoped_string & scopedstrTypeName) const;
      bool has_factory_item_by_custom_id(const ::type_custom_id & typecustomid) const;
      bool has_factory_item(const ::platform::type & type) const;

      template<typename ORIGIN_TYPE>
      bool has_factory_item() const
      {

         auto typeindex = ::std::type_index(::type<ORIGIN_TYPE>());

         return this->has_factory_item_by_type_index(typeindex);

      }

      //inline ::factory::factory_item_interface * get_factory_item_from(const ::platform::type & type, const ::platform::type & typeSource) const;

      template < typename ORIGIN_TYPE >
      inline ::factory::factory_item_interface * get_factory_item() const;

      //template < typename ORIGIN_TYPE >
      //inline ::factory::factory_item_interface * get_factory_item(const ::platform::type & type);
      //inline ::pointer<factory_item_interface>& get_factory_item(const ::platform::type & type)
         
      template < typename BASE_TYPE >
      inline bool __call__defer_construct(::particle * pparticle, ::pointer<BASE_TYPE> &  ptype);
      template < typename TYPE, typename ORIGIN_TYPE>
      inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > _add_factory_item_from(const ::platform::type & typeSource);


#if REFERENCING_DEBUGGING


      factory * __call__add_referer2(const ::reference_referer & referer) const;

#endif

      //template < typename ORIGIN_TYPE >
      //inline ::pointer<::factory::factory_item_interface>& get_factory_item_from(const ::platform::type & typeSource);

      template < typename TYPE, typename ORIGIN_TYPE = TYPE >
      inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item();

      template < typename ORIGIN_TYPE  >
      inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item_with_custom_id(const ::type_custom_id & typecustomid);
      //template < typename TYPE, typename ORIGIN_TYPE >
      //inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item_from(const ::platform::type & typeSource);
      virtual void set_factory_item_by_custom_id(const ::type_custom_id & typecustomid, const ::pointer<::factory::factory_item_interface> & pfactoryitem);
      virtual void set_factory_item_by_type(const ::platform::type & type, const ::pointer<::factory::factory_item_interface> & pfactoryitem);

      template < typename TYPE, typename ORIGIN_TYPE>
      inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > create_reusable_factory_item();

      template < typename ORIGIN_TYPE >
      inline ::pointer<ORIGIN_TYPE>__call__create(::particle * pparticle);

      void merge(const ::factory::factory* pfactory);

      void merge_to_global_factory() const;

      void set_currently_loading_library();

      void terminate();

      template < typename ORIGIN_TYPE >
      inline void __defer_raw_construct( ::pointer<ORIGIN_TYPE> & p)
      {

         if (::is_null(p))
         {

            this->øraw_construct(p);

         }

      }


      template < typename ORIGIN_TYPE >
      inline void __call__construct(::particle * pparticleInitializer, ::pointer<ORIGIN_TYPE> & p);


      template < typename ORIGIN_TYPE >
      inline void __call__raw_construct(::pointer<ORIGIN_TYPE> & p);


      virtual ::particle_pointer __call__create_by_type_index(const ::std::type_index & typeindex, ::particle * pparticle);
      virtual ::particle_pointer __call__create_by_type_name(const ::scoped_string & scopedstrTypeName, ::particle * pparticle);
      virtual ::particle_pointer __call__create_by_custom_id(const ::type_custom_id & typecustomid, ::particle* pparticle);
      virtual ::particle_pointer __call__create_by_type(const ::platform::type & type, ::particle* pparticle);


      virtual bool has_by_type_index(const ::std::type_index & typeindex) const;
      virtual bool has_by_type_name(const ::scoped_string & scopedstrTypeName) const;
      virtual bool has_by_custom_id(const ::type_custom_id & typecustomid) const;
      virtual bool has(const ::platform::type & type) const;


      template < typename TYPE >
      bool has() const
      {
       
         return this->has_by_type_index(::std::type_index(typeid(TYPE)));
         
      }


   };



   using factory_array = pointer_array < factory_item_interface >;

   //CLASS_DECL_ACME factory * get_factory();

   ///CLASS_DECL_ACME factory * get_factory(const ::platform::type & typeSource);
   ///


   CLASS_DECL_ACME factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex);
   CLASS_DECL_ACME factory_item_interface * get_factory_item_by_custom_id(const ::type_custom_id & typecustomid);


   CLASS_DECL_ACME factory_item_interface * get_existing_factory_item_by_type_index(const ::std::type_index & typeindex);
   CLASS_DECL_ACME factory_item_interface * get_existing_factory_item_by_custom_id(const ::type_custom_id & typecustomid);


   CLASS_DECL_ACME factory_item_interface * get_factory_item_by_type_index(const ::std::type_index & typeindex, const ::atom & atomFactory);
   CLASS_DECL_ACME factory_item_interface * get_factory_item_by_custom_id(const ::platform::type & type, const ::atom & atomFactory);


   CLASS_DECL_ACME bool has_by_type_index(const ::std::type_index & typeindex);
   CLASS_DECL_ACME bool has_by_custom_id(const ::type_custom_id & typecustomid);
   

   
   CLASS_DECL_ACME void set_factory_item_by_type(const ::platform::type & type, const ::pointer<factory_item_interface>& pfactory);

   template < typename ORIGIN_TYPE >
   inline ::atom get_id();
//   {
//
//      auto pszTypename = ::type<ORIGIN_TYPE>().name();
//
//#ifdef WINDOWS
//
//      pszTypename = c_demangle(scopedstrTypename);
//
//      return pszTypename;
//
//#else
//
//      auto strTypename = ::transfer(demangle(scopedstrTypename));
//
//      return strTypename;
//
//
//#endif
//
//   }


   //template < typename ORIGIN_TYPE >
   //inline ::pointer<factory_item_interface>& get_factory_item();
//   {
//
//      //static auto atom = get_atom<ORIGIN_TYPE>();
//
//      //return get_factory_item(atom);
//
//      return get_factory_item(get_atom<ORIGIN_TYPE>());
//
//   }


   template < typename ORIGIN_TYPE >
   inline ::pointer<factory_item_interface> get_factory_item_by_type_index(const ::std::type_index & typeindex);

   template < typename ORIGIN_TYPE >
   inline ::pointer<factory_item_interface> get_factory_item_by_custom_id(const ::type_custom_id & typecustomid);

   
   //   {
//
//      //static auto atom = get_atom<ORIGIN_TYPE>();
//
//      //return get_factory_item(atom, atomSource);
//
//      ///static auto atom = get_atom<ORIGIN_TYPE>();
//
//      return get_factory_item(atomSource, get_atom<ORIGIN_TYPE>());
//
//   }


} // namespace factory


// using factory_pointer = ::pointer<::factory::factory>;


// namespace factory
// {


//    template < typename TYPE, typename ORIGIN_TYPE = TYPE >
//    inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item();


//    template < typename TYPE, typename ORIGIN_TYPE = TYPE >
//    inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item(const ::platform::type & type);


//    template < typename TYPE, typename ORIGIN_TYPE = TYPE >
//    inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item_from(const ::platform::type & typeSource);


//    template < typename TYPE, typename ORIGIN_TYPE = TYPE >
//    inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > create_reusable_factory();


//    template < typename TYPE >
//    ::pointer<TYPE>__call__create();


// } // namespace factory






namespace factory
{


   //CLASS_DECL_ACME critical_section * &m_criticalsection;


   template <  typename TYPE >
   inline pointer< ::factory::factory_item_base < TYPE > > factory::add_factory_item_with_custom_id(const ::type_custom_id & typecustomid)
   {

      if (typecustomid.is_empty())
      {

         throw ::exception(error_bad_argument, "type custom id is not set");

      }

      critical_section_lock lock(&m_criticalsection);

      auto pfactoryitem = øallocate ::factory::factory_item< TYPE, TYPE > ();

      set_factory_item_by_custom_id(type, pfactoryitem);

      return pfactoryitem;

   }


   CLASS_DECL_ACME::factory::factory * loading_library_factory();

//
//   template < typename TYPE, typename ORIGIN_TYPE>
//   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > factory::_add_factory_item_from(const ::platform::type & typeSource)
//   {
//
////      critical_section_lock lock(&m_criticalsection);
//
//      auto pfactory = ::factory::loading_library_factory();
//
//      if (::is_set(pfactory))
//      {
//
//         return pfactory->add_factory_item < TYPE, ORIGIN_TYPE >();
//
//      }
//
//      critical_section_lock lock(&m_criticalsection);
//
//      auto pfactoryitem = øallocate ::factory::factory_item< TYPE, ORIGIN_TYPE > ();
//
//      get_factory_item < ORIGIN_TYPE >(atomSource) = pfactoryitem;
//
//      return pfactoryitem;
//
//   }
//

   //template < typename TYPE, typename ORIGIN_TYPE>
   //inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > add_factory_item()
   //{

   //   critical_section_lock lock(&m_criticalsection);

   //   auto pfactory = øallocate ::factory::factory_item< TYPE, ORIGIN_TYPE > ();

   //   factory_item < ORIGIN_TYPE >() = pfactory;

   //   return pfactory;

   //}


//   template < typename TYPE, typename ORIGIN_TYPE>
//   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > factory::create_reusable_factory_item()
//   {
//
//      critical_section_lock lock(&m_criticalsection);
//
//      auto pfactory = øallocate ::factory::reusable_factory_item< TYPE, ORIGIN_TYPE > ();
//
//      factory_item < TYPE, ORIGIN_TYPE >() = pfactory;
//
//      return pfactory;
//
//   }


} // namespace factory




namespace factory
{

//
//   template < typename TYPE, typename ORIGIN_TYPE >
//   inline ::pointer<ORIGIN_TYPE>reusable_factory_item < TYPE, ORIGIN_TYPE >::__call__create()
//   {
//
//      {
//
//         critical_section_lock lock(&m_criticalsection);
//
//         if (m_pfree)
//         {
//
//            auto pNew = m_pfree;
//
//            m_pfree = pNew->m_pnext;
//
//            pNew->reuse();
//
//            return pNew;
//
//         }
//
//      }
//
//      return factory_item < TYPE, ORIGIN_TYPE >::_call_new();
//
//   }

//
//   template < typename TYPE, typename ORIGIN_TYPE >
//   inline void reusable_factory_item < TYPE, ORIGIN_TYPE >::return_back(ORIGIN_TYPE * p)
//   {
//
//      critical_section_lock lock(&m_criticalsection);
//
//      p->m_pnext = m_pfree;
//
//      m_pfree = p;
//
//   }


//   template < typename ORIGIN_TYPE >
//   inline ::pointer<ORIGIN_TYPE>factory::__call__create()
//   {
//
//      auto pfactoryinterface = get_factory_item < ORIGIN_TYPE >();
//
//      if (!pfactoryinterface)
//      {
//
//         throw_exception(error_no_factory);
//
//      }
//
//      return pfactoryinterface->__call__create_particle();
//
//   }

//
//   template < typename TYPE, typename ORIGIN_TYPE>
//   inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > factory::add_factory_item()
//   {
//
//      critical_section_lock lock(&m_criticalsection);
//
//      auto pfactory = øallocate ::factory::factory_item< TYPE, ORIGIN_TYPE > ();
//
//      this->get_factory_item < ORIGIN_TYPE >() = pfactory;
//
//      return pfactory;
//
//   }

//
//   template < typename ORIGIN_TYPE >
//   inline void factory::øconstruct(::particle * pparticleInitializer, ::pointer < ORIGIN_TYPE > & p)
//   {
//
//      øraw_construct(p);
//
//      p->initialize(pparticleInitializer);
//
//   }
//

//   template < typename ORIGIN_TYPE >
//   inline void factory::øraw_construct(::pointer<ORIGIN_TYPE>  & p)
//   {
//
//      auto & pfactoryitem = get_factory_item < ORIGIN_TYPE >();
//
//      if (!pfactoryitem)
//      {
//
//         throw_exception(error_no_factory, "Factory hasn't creator for type \"" + __type_name<ORIGIN_TYPE>() + "\"");
//
//      }
//
//      auto pparticle = ::transfer(pfactoryitem->__call__create_particle());
//
//      if (!pparticle)
//      {
//
//         throw_exception(error_no_memory, "Couldn't __call__create_particle for type \"" + __type_name<ORIGIN_TYPE>() + "\"");
//
//      }
//
//      p = pparticle;
//
//      if (!p)
//      {
//
//         throw_exception(error_wrong_type, "Created element is not of the base type \"" + __type_name<ORIGIN_TYPE>() + "\"");
//
//      }
//
//   }
//


//   inline ::factory::factory_item_interface * factory::get_factory_item(const ::platform::type & type) const
//   {
//
//      critical_section_lock cs(&((factory*)this)->m_criticalsection);
//
//      auto iterator = this->find(atom);
//
//      if (iterator.is_null())
//      {
//
//         return nullptr;
//
//      }
//
//      return iterator->m_element2;
//
//   }


//   template < typename ORIGIN_TYPE >
//   inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item()
//   {
//
//      string strTypename(::type<ORIGIN_TYPE>().name());
//
//      strTypename = ::demangle(strTypename);
//
//      return get_factory_item(strTypename);
//
//   }


   //inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item(const ::platform::type & type);
//   {
//
//      critical_section_lock cs(&m_criticalsection);
//
//
//      return this->operator[](atom);
//
//   }


   //inline ::pointer<factory_item_interface> & factory::get_factory_item(const ::platform::type & type)
   //{

   //   critical_section_lock cs(&m_criticalsection);

   //   return (*get_factory())[atom];

   //}


   inline ::pointer<factory_item_interface> & get_existing_factory_item(const ::platform::type & type);
//   {
//
//      auto & pfactoryitem = get_factory_item(atom);
//
//      if (!pfactoryitem)
//      {
//
//         throw_exception(error_no_factory, "No factory for \"" + atom + "\"");
//
//      }
//
//      return pfactoryitem;
//
//   }
//



   //template < typename TYPE >
   //inline stream & load_object(stream & stream, ::pointer<TYPE>& p)
   //{

   //   string strText;

   //   stream >> strText;

   //   if (strText.is_empty() || strText.case_insensitive_begins_eat("factoryless://"))
   //   {

   //      if (p && ::platform::type(p).name()) == strText
   //      {

   //         informationf("loading into existing matter of same class type (1)");

   //      }
   //      else
   //      {

   //         p.defer_create_new();

   //         if (!p)
   //         {

   //            informationf("defer_new failed (1.1)");

   //            stream.set_fail_bit();

   //         }
   //         else if (::platform::type(p).name()) != strText
   //         {

   //            informationf("allocated matter type is different from streamed matter type (1.2)");

   //            stream.set_fail_bit();

   //         }

   //      }

   //   }
   //   else
   //   {

   //      auto atom = stream.text_to_factory_id(strText);

   //      if (p && atom == ::platform::type(p).name())
   //      {

   //         informationf("loading into existing matter of same class type (2)");

   //      }
   //      else
   //      {

   //         p = stream.create_object_from_text(strText);

   //         if (!p)
   //         {

   //            informationf("stream::alloc_object_from_text failed (2.1)");

   //         }
   //         else if (::platform::type(p).name()) != atom.to_string()
   //         {

   //            informationf("allocated matter type is different from streamed matter type (2.2)");

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
//
//
//namespace factory
//{
//
//
//   template < typename BASE_TYPE >
//   inline void factory::ødefer_construct(::particle * pparticle, ::pointer<BASE_TYPE> & ptype)
//   {
//
//      ::ødefer_construct(pparticle, ptype, this);
//
//   }
//
//
//} // namespace factory
//
//
//template < typename TYPE >
//inline void øraw_construct(::pointer<TYPE>& p, ::factory::factory * pfactory = nullptr);
//{
//
//   auto& pfactoryitem = pfactory->get_factory_item< TYPE >();
//
//   if (!pfactoryitem)
//   {
//
//      string strMessage;
//
//      strMessage.formatf("matter::øconstruct has failed to find factory_item for type \"%s\"", __type_name < TYPE >().c_str());
//
//      throw_exception(::error_not_implemented, strMessage);
//
//   }
//
//   auto pparticleNew = pfactoryitem->__call__create_particle();
//
//   if (!pparticleNew)
//   {
//
//      string strMessage;
//
//      strMessage.formatf("matter::øconstruct no memory to allocate implementation of type \"%ss\"", __type_name < TYPE >().c_str());
//
//      throw_exception(::error_no_memory, strMessage);
//
//   }
//
//   p.release();
//
//   p = pparticleNew;
//
//   if (!p)
//   {
//
//      string strMessage;
//
//      strMessage.formatf("matter::øconstruct object(%s) is not of type \"%s\"", ::platform::type(pparticleNew).name().c_str(), __type_name < TYPE >().c_str());
//
//      throw_exception(::error_wrong_type, strMessage);
//
//   }
//
//}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE> __raw_create(::factory::factory* pfactory);
//{
//
//   ::pointer<BASE_TYPE> p;
//
//   øraw_construct(p, pfactory);
//
//   return ::transfer(p);
//
//}


//template < typename TYPE >
//inline void øconstruct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory * pfactory = nullptr);
//{
//
//   øraw_construct(p, pfactory);
//
//   p->initialize(pparticle);
//
//}
//

//template < typename BASE_TYPE >
//inline ::pointer < BASE_TYPE > øcreate(::particle* pparticle, ::factory::factory * pfactory = nullptr);
//{
//
//   ::pointer < BASE_TYPE > p;
//
//   øconstruct(pparticle, p, pfactory);
//
//   return p;
//
//}


//template < typename TYPE >
//inline void __call__defer_construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory* pfactory);
//{
//
//   if (!p)
//   {
//
//      øconstruct(pparticle, p, pfactory);
//
//   }
//
//
//}





//template < typename TYPE >
//inline void øconstruct_by_custom_id(particle* pparticle, ::pointer<TYPE>& p, const ::platform::type & type, ::factory::factory * pfactory = nullptr);
//{
//
//   auto& pfactoryitem = pfactory->get_factory_item(atom);
//
//   auto pparticleNew = pfactoryitem->__call__create_particle();
//
//   //if (!pparticleNew)
//   //{
//
//   //   return error_no_memory;
//
//   //}
//
//   p = pparticleNew;
//
//   if (!p)
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   p->set_flag(e_flag_factory);
//
//   //auto estatus =
//
//   p->initialize(pparticle);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //return estatus;
//
//}


//template < typename TYPE >
//inline ::pointer < TYPE > øcreate_by_custom_id(particle* pparticle, const ::platform::type & type, ::factory::factory * pfactory = nullptr);
//{
//
//   auto& pfactoryitem = pfactory->get_factory_item(atom);
//
//   auto pparticleNew = pfactoryitem->__call__create_particle();
//
//   //if (!pparticleNew)
//   //{
//
//   //   return error_no_memory;
//
//   //}
//
//
//
//   ::pointer < TYPE > p = pparticleNew;
//
//   if (!p)
//   {
//
//      throw_exception(error_wrong_type);
//
//   }
//
//   p->set_flag(e_flag_factory);
//
//   //auto estatus =
//
//   p->initialize(pparticle);
//
//   //if (!estatus)
//   //{
//
//   //   return estatus;
//
//   //}
//
//   //return estatus;
//
//   return p;
//
//}

//
//template < class T >
//template < typename PARTICLE >
//inline pointer < T >& pointer < T >::__call__create(PARTICLE* pparticle, ::factory::factory* pfactory)
//{
//
//   auto p = ::øcreate < T >(pparticle);
//
//   return operator =(p);
//
//}



