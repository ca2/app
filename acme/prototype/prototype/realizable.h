// Created by camilo on 2024-10-08 08:10 <3ThomasBorregaardSorensen!!
#pragma once


template < typename REALIZABLE >
class reified;

template < typename REALIZABLE >
class reificator;

template < typename REALIZABLE >
class realizable :
   virtual public ::particle
{
public:


   ::pointer < ::reified < REALIZABLE > > m_preified;

   ::pointer < ::reified < REALIZABLE > > defer_realize(::reificator < REALIZABLE > * p)
   {

      if (m_preified)
      {

         return m_preified;

      }

      m_preified = p->realize(this);

      return m_preified;

   }


   ::pointer < ::reified < REALIZABLE > > defer_realize()
   {

      return defer_realize(dynamic_cast < ::reificator < REALIZABLE > * >(get_context_particle()));

   }


};


template < typename REALIZABLE >
class reified :
   virtual public ::subparticle
{
public:

   ::pointer < REALIZABLE > m_prealizable;

   virtual void realize(::realizable < REALIZABLE > * p)
   {

      m_prealizable = p;

      on_realize(m_prealizable);

   }

   virtual void on_realize(REALIZABLE * prealizable)
   {

   }

};

template < typename REALIZABLE >
class reificator :
   virtual public ::subparticle
{
public:


   virtual ::pointer < ::reified < REALIZABLE > > realize(::realizable < REALIZABLE > * p)
   {

      return nullptr;

   }


};




