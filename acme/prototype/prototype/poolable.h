// Created by camilo on 2025-06-30 00:48 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/prototype/prototype/call.h"
#include "acme/prototype/prototype/pool.h"


template < typename POOL_RESTORABLE >
class poolable :
   virtual public ::particle
{
public:


   bool m_bNew;

   ::pool < POOL_RESTORABLE >* m_ppool;

   poolable()
   {

      m_bNew = true;

   }

   bool is_new() const
   {

      return m_bNew;

   }

   void handle(const ::call& call) override
   {

      if (call == e_call_off_to_pool)
      {

         m_ppool->m_aPool.add(this);

      }

   }

};



