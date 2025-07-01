// Created by camilo on 2025-06-30 01:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/call.h"


class CLASS_DECL_ACME pool_group :
   virtual public ::particle
{
public:


   ::particle* m_pallocator;
   ::particle_array  m_particleaOngoing;


   pool_group();
   ~pool_group() override;


   void on_initialize_particle();


   void call_ongoing(const ::call& call);


};





template < typename TYPE >
class pool
{
public:


   pool_group* m_ppoolgroup;
   ::pointer_array < TYPE >         m_aPool;


   pool()
   {

      m_ppoolgroup = nullptr;

   }


   ~pool()
   {

   }


   TYPE* get()
   {

      _synchronous_lock synchronouslock(m_ppoolgroup->synchronization());

      TYPE* pGet;

      if (m_aPool.is_empty())
      {

         auto p = m_ppoolgroup->m_pallocator->__øcreate<TYPE >();

         p->m_ppool = this;

         pGet = p;

         m_ppoolgroup->m_particleaOngoing.add(::transfer(p));

      }
      else
      {

         auto p = m_aPool.pop();

         ASSERT(p->m_ppool == this);

         if (p->m_bNew)
         {

            p->m_bNew = false;

         }

         pGet = p;

         m_ppoolgroup->m_particleaOngoing.add(::transfer(p));

      }

      return pGet;

   }


};




