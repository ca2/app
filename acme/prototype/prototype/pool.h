// Created by camilo on 2025-06-30 01:22 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/call.h"

class CLASS_DECL_ACME ongoing_particle_array_source :
   virtual public ::particle
{
public:

   virtual ::particle_array* ongoing_particle_array();


};


class CLASS_DECL_ACME pool_group :
   virtual public ::particle
{
public:


   ::particle*                   m_pallocator;
   // frame
   //::array<::particle_array >    m_particleaOngoing;
   ::pointer < ongoing_particle_array_source >    m_pongoingparticlearraysource;


   pool_group();
   ~pool_group() override;


   void on_initialize_particle() override;


   virtual void call_ongoing(const ::call& call);


   virtual ::particle_array* ongoing_particle_array();


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

         auto p = m_ppoolgroup->m_pallocator->øcreate<TYPE >();

         p->m_ppool = this;

         pGet = p;

         m_ppoolgroup->ongoing_particle_array()->add(::transfer(p));

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

         m_ppoolgroup->ongoing_particle_array()->add(::transfer(p));

      }

      return pGet;

   }


};




