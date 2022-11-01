//
// Created by camilo on 2022-10-25 10:55 <3ThomasBorregaardSorensen!!
//
#pragma once


//#include "factory.h"
#include "acme/platform/tracer.h"


template < typename TYPE >
inline ::pointer<TYPE> __create_new(::particle * pparticle)
{

   if(::is_null(pparticle))
   {

      throw ::exception(error_wrong_state);

   }

   auto p = __new(TYPE());

   if (p)
   {

      p->initialize(pparticle);

   }

   return ::move(p);

}


template < typename TYPE >
inline void __raw_construct(::pointer<TYPE> & p, ::factory::factory * pfactory = ::factory::get_factory())
{

   auto & pfactoryitem = pfactory->get_factory_item< TYPE >();

   if (!pfactoryitem)
   {

      string strMessage;

      strMessage.format("matter::__construct has failed to find factory_item for type \"%s\"", __type_name < TYPE >().c_str());

      throw_exception(::error_not_implemented, strMessage);

   }

   auto ptypeNew = pfactoryitem->create_element();

   if (!ptypeNew)
   {

      string strMessage;

      strMessage.format("matter::__construct no memory to allocate implementation of type \"%ss\"", __type_name < TYPE >().c_str());

      throw_exception(::error_no_memory, strMessage);

   }

   p.release();

   p = ptypeNew;

   if (!p)
   {

      FORMATTED_ERROR("matter::__construct object(%s) is not of type \"%s\"", __type_name(ptypeNew).c_str(), __type_name < TYPE >().c_str());

      throw_exception(::error_wrong_type);

   }

}


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE> __raw_create(::factory::factory * pfactory)
{

   ::pointer<BASE_TYPE> p;

   __raw_construct(p, pfactory);

   return ::move(p);

}


template < typename TYPE >
inline void __construct(::particle * pparticle, ::pointer<TYPE> & p, ::factory::factory * pfactory = ::factory::get_factory())
{

   __raw_construct(p, pfactory);

   p->initialize(pparticle);

}


template < typename BASE_TYPE >
inline ::pointer < BASE_TYPE > __create(::particle * pparticle, ::factory::factory * pfactory = ::factory::get_factory())
{

   ::pointer < BASE_TYPE > p;

   __construct(pparticle, p, pfactory);

   return p;

}


template < typename TYPE >
inline void __defer_construct(::particle * pparticle, ::pointer<TYPE> & p, ::factory::factory * pfactory = ::factory::get_factory())
{

   if(!p)
   {

      __construct(pparticle, p, pfactory);

   }


}


template < typename TYPE >
inline void __construct_new(::particle * pparticle, ::pointer<TYPE> & p)
{

   p = __new(TYPE);

   if (!p)
   {

      throw_exception(error_no_memory);

   }

   p->initialize(pparticle);

}


template < typename TYPE >
inline void __id_construct(particle * pparticle, ::pointer<TYPE> & p, const ::atom & atom, ::factory::factory * pfactory = ::factory::get_factory())
{

   auto & pfactoryitem = pfactory->get_factory_item(atom);

   auto ptypeNew = pfactoryitem->create_element();

   //if (!ptypeNew)
   //{

   //   return error_no_memory;

   //}

   p = ptypeNew;

   if (!p)
   {

      throw_exception(error_wrong_type);

   }

   p->set(e_flag_factory);

   //auto estatus =

   p->initialize(pparticle);

   //if (!estatus)
   //{

   //   return estatus;

   //}

   //return estatus;

}


template < class T >
template < typename PARTICLE >
inline pointer < T > & pointer < T >::create(PARTICLE * pparticle, ::factory::factory * pfactory)
{

   auto p = ::__create < T >(pparticle);

   return operator =(p);

}


//template < class T >
//template < typename PARTICLE >
//inline pointer < T > & pointer < T >::create(PARTICLE * pparticle, bool bCreate)
//{
//
//   if (bCreate)
//   {
//
//      defer_create(pparticle);
//
//   }
//   else
//   {
//
//      release();
//
//   }
//
//   return *this;
//
//}





