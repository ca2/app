//
// Created by camilo on 2022-10-25 10:55 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "factory.h"
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


template < typename BASE_TYPE >
inline ::pointer<BASE_TYPE> __create(::particle * pparticle)
{

   auto & pfactory = ::factory::get_factory_item < BASE_TYPE >();

   if (!pfactory)
   {

      throw_exception(::error_not_implemented);

   }

   auto ptypeNew = pfactory->create_element();

   if (!ptypeNew)
   {

      throw_exception(::error_no_memory);

   }

   BASE_TYPE * p;

   __dynamic_cast(p, ptypeNew.m_p);

   if (!p)
   {

      throw_exception(::error_wrong_type);

   }

   p->initialize(pparticle);

   return p;

}


template < typename TYPE >
inline void __construct(::particle * pparticle, ::pointer<TYPE> & p)
{

   auto & pfactory = ::factory::get_factory_item < TYPE >();

   if (!pfactory)
   {

      string strMessage;

      strMessage.format("matter::__construct has failed to find factory_item for type \"%s\"", __type_name < TYPE >().c_str());

      throw_exception(::error_not_implemented, strMessage);

   }

   auto ptypeNew = pfactory->create_element();

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

   p->initialize(pparticle);

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
inline void __id_construct(particle * pparticle, ::pointer<TYPE> & p, const ::atom & atom)
{

   auto & pfactory = ::factory::get_existing_factory_item(atom);

   auto ptypeNew = pfactory->create_element();

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
inline pointer < T > & pointer < T >::create(PARTICLE * pparticle)
{

   auto p = ::__create < T >(pparticle);

   return operator =(p);

}


template < class T >
template < typename PARTICLE >
inline pointer < T > & pointer < T >::create(PARTICLE * pparticle, bool bCreate)
{

   if (bCreate)
   {

      defer_create(pparticle);

   }
   else
   {

      release();

   }

   return *this;

}





