//
// Created by camilo on 23/12/2022 02:00 <3ThomasBorregaardSorensen!!
//
#pragma once


namespace factory
{


    template < typename TYPE, typename ORIGIN_TYPE >
    inline ::pointer<ORIGIN_TYPE>reusable_factory_item < TYPE, ORIGIN_TYPE >::__call__create()
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

       return factory_item < TYPE, ORIGIN_TYPE >::__call__new();

    }


    template < typename TYPE, typename ORIGIN_TYPE >
    inline void reusable_factory_item < TYPE, ORIGIN_TYPE >::return_back(ORIGIN_TYPE * p)
    {

       critical_section_lock lock(&m_criticalsection);

       p->m_pnext = m_pfree;

       m_pfree = p;

    }


    template < typename ORIGIN_TYPE >
    inline ::pointer<ORIGIN_TYPE>factory::__call__create(::particle * pparticle)
    {

       auto pfactoryinterface = get_factory_item < ORIGIN_TYPE >();

       if (!pfactoryinterface)
       {

          throw_exception(error_no_factory);

       }

       auto p = pfactoryinterface->__call__create_particle();
       
       p->initialize(pparticle);
       
       return p;

    }


    template < typename TYPE, typename ORIGIN_TYPE>
    inline pointer< ::factory::factory_item_base < ORIGIN_TYPE > > factory::add_factory_item()
    {

       critical_section_lock lock(&m_criticalsection);

       auto pfactory = __allocate< ::factory::factory_item< TYPE, ORIGIN_TYPE > >();

       this->get_factory_item < ORIGIN_TYPE >() = pfactory;

       return pfactory;

    }


    template < typename ORIGIN_TYPE >
    inline void factory::__call__construct(::particle * pparticleInitializer, ::pointer < ORIGIN_TYPE > & p)
    {

       __call__raw_construct(p);

       p->initialize(pparticleInitializer);

    }


    template < typename ORIGIN_TYPE >
    inline void factory::__call__raw_construct(::pointer<ORIGIN_TYPE>  & p)
    {

//#if REFERENCING_DEBUGGING
//
//       ::allocator::add_referer(REFERENCING_DEBUGGING_ARGUMENTS);
//
//#endif
//
       auto & pfactoryitem = get_factory_item < ORIGIN_TYPE >();

       if (!pfactoryitem)
       {

          ::string strMessage;

          strMessage = "Factory hasn't creator for type \"" + ::type < ORIGIN_TYPE >().name() + "\"";

          warningf(strMessage);

          throw_exception(error_no_factory, strMessage);

       }

       auto pparticle = ::transfer(pfactoryitem->__call__create_particle());

       if (!pparticle)
       {

          ::string strMessage;

          strMessage = "Couldn't __call__create_particle for type \"" + ::type < ORIGIN_TYPE >().name() + "\"";

          warningf(strMessage);

          throw_exception(error_no_memory, strMessage);

       }

       p = pparticle;

       if (!p)
       {

          ::string strMessage;

          strMessage = "Created element is not of the base type \"" + ::type < ORIGIN_TYPE >().name() + "\"";

          warningf(strMessage);

          throw_exception(error_wrong_type, strMessage);

       }

    }




    template < typename ORIGIN_TYPE >
    inline ::pointer<::factory::factory_item_interface> & factory::get_factory_item()
    {

       string strTypename(typeid(ORIGIN_TYPE).name());

       strTypename = ::demangle(strTypename);

       return get_factory_item(strTypename);

    }


    //template < typename TYPE >
    //inline stream & load_object(stream & stream, ::pointer<TYPE>& p)
    //{

    //   string strText;

    //   stream >> strText;

    //   if (strText.is_empty() || strText.case_insensitive_begins_eat("factoryless://"))
    //   {

    //      if (p && ::type(p).name()) == strText
    //      {

    //         ::acme::get()->platform()->informationf("loading into existing matter of same class type (1)");

    //      }
    //      else
    //      {

    //         p.defer_create_new();

    //         if (!p)
    //         {

    //            ::acme::get()->platform()->informationf("defer_new failed (1.1)");

    //            stream.set_fail_bit();

    //         }
    //         else if (::type(p).name()) != strText
    //         {

    //            ::acme::get()->platform()->informationf("allocated matter type is different from streamed matter type (1.2)");

    //            stream.set_fail_bit();

    //         }

    //      }

    //   }
    //   else
    //   {

    //      auto atom = stream.text_to_factory_id(strText);

    //      if (p && atom == ::type(p).name())
    //      {

    //         ::acme::get()->platform()->informationf("loading into existing matter of same class type (2)");

    //      }
    //      else
    //      {

    //         p = stream.create_object_from_text(strText);

    //         if (!p)
    //         {

    //            ::acme::get()->platform()->informationf("stream::alloc_object_from_text failed (2.1)");

    //         }
    //         else if (::type(p).name()) != atom.to_string()
    //         {

    //            ::acme::get()->platform()->informationf("allocated matter type is different from streamed matter type (2.2)");

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
    inline bool factory::__call__defer_construct(::particle * pparticle, ::pointer<BASE_TYPE> & ptype)
    {

       if (ptype)
       {

#if REFERENCING_DEBUGGING

          ::allocator::defer_erase_referer();

#endif

          return false;

       }

       pparticle->__call__construct(ptype, this);

       return true;

    }


} // namespace factory


template < typename TYPE >
inline void particle__call__raw_construct2( ::pointer<TYPE> & p, ::factory::factory * pfactory)
{

#if REFERENCING_DEBUGGING

   ::allocator::add_referer(REFERENCING_DEBUGGING_ARGUMENTS);

#endif

   __call_raw_construct(p, factory);

}


template < typename TYPE >
inline void particle::__call__raw_construct(::pointer<TYPE>&p, ::factory::factory * pfactory)
{

   
   if (::is_null(pfactory))
   {

      pfactory = this->factory();

   }

   auto& pfactoryitem = pfactory->get_factory_item< TYPE >();

   if (!pfactoryitem)
   {

      string strMessage;

      strMessage.formatf("matter::__construct has failed to find factory_item for type \"%s\"", ::type < TYPE >().name().c_str());

      throw_exception(::error_not_implemented, strMessage);

   }

   auto pparticleNew = pfactoryitem->__call__create_particle();

   if (!pparticleNew)
   {

      string strMessage;

      strMessage.formatf("matter::__construct no memory to allocate implementation of type \"%ss\"", ::type < TYPE >().name().c_str());

      throw_exception(::error_no_memory, strMessage);

   }

   p = ::transfer(pparticleNew);

   if (!p)
   {

      string strMessage;

      strMessage.formatf("matter::__construct object(%s) is not of type \"%s\"", ::type(pparticleNew).name().c_str(), ::type < TYPE >().name().c_str());

      throw_exception(::error_wrong_type, strMessage);

   }

}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE> particle::__raw_create(::factory::factory* pfactory)
{

   ::pointer<BASE_TYPE> p;

   __raw_construct(p, pfactory);

   return ::transfer(p);

}




//template < typename TYPE >
//inline void __construct(::particle* pparticle, ::pointer<TYPE>& p, ::factory::factory* pfactory)
//{
//
//   __raw_construct(p, pfactory);
//
//   p->initialize(pparticle);
//
//}
//
//
//template < typename BASE_TYPE >
//inline ::pointer < BASE_TYPE > __create(::particle* pparticle, ::factory::factory* pfactory)
//{
//
//   ::pointer < BASE_TYPE > p;
//
//   __construct(pparticle, p, pfactory);
//
//   return p;
//
//}


template < typename TYPE >
inline bool particle::__call__defer_construct(::pointer<TYPE>& p, ::factory::factory* pfactory)
{

   if (p)
   {

#if REFERENCING_DEBUGGING

      ::allocator::defer_erase_referer();
#endif

      return false;

   }

   __call__construct(p, pfactory);

   return true;

}


//template < typename TYPE >
//inline bool particle::__defer_construct(::pointer<TYPE>& p, ::factory::factory* pfactory)
//{
//
//   if (!p)
//   {
//
//      __construct(p, pfactory);
//
//      return true;
//
//   }
//
//   return false;
//
//}


template < typename TYPE >
inline void particle::__call__id_construct(::pointer<TYPE>& p, const ::atom& atom, ::factory::factory * pfactory)
{

   if (::is_null(pfactory))
   {

      pfactory = this->factory();

   }

   auto& pfactoryitem = pfactory->get_factory_item(atom);

   auto pparticleNew = pfactoryitem->__call__create_particle();

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

   p->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


template < typename TYPE >
inline ::pointer < TYPE > particle::__call__id_create(const ::atom& atom, ::factory::factory * pfactory)
{

   if (::is_null(pfactory))
   {

      pfactory = this->factory();

   }

   auto& pfactoryitem = pfactory->get_factory_item(atom);

   auto pparticleNew = pfactoryitem->__call__create_particle();

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

   p->initialize(this);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

   return p;

}


//template < class T >
//template < typename PARTICLE >
//inline pointer < T >& pointer < T >::create(PARTICLE* pparticle, ::factory::factory* pfactory)
//{
//
//   auto p = pparticle->__create < T >(pfactory);
//
//   return operator =(p);
//
//}



