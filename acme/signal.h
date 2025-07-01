// Created by camilo on 2025-06-29 23:32 <3ThomasBorregaardSørensen!!
#pragma once


struct asignal
{


   enum_id                       m_eid;
   long long                     m_ll;
   long long                     m_ll2;
   ::subparticle *               m_psubparticle;


   asignal(enum_id eid, long long ll = 0ll, long long ll2 = 0ll) :
      m_eid(eid),
      m_ll(ll),
      m_ll2(ll2),
      m_psubparticle(nullptr)
   {


   }


   asignal(enum_id eid, long long ll, long long ll2, ::subparticle* psubparticle) :
      m_eid(eid),
      m_ll(ll),
      m_ll2(ll2),
      m_psubparticle(psubparticle)
   {

      m_psubparticle->increment_reference_count();

   }


   asignal(const asignal& asignal) :
      m_eid(asignal.m_eid),
      m_ll(asignal.m_ll),
      m_ll2(asignal.m_ll2),
      m_psubparticle(asignal.m_psubparticle)
   {

      m_psubparticle->increment_reference_count();

   }


   asignal(asignal&& asignal) :
      m_eid(asignal.m_eid),
      m_ll(asignal.m_ll),
      m_ll2(asignal.m_ll2),
      m_psubparticle(asignal.m_psubparticle)
   {

      asignal.m_eid = (enum_id)0;
      asignal.m_psubparticle = nullptr;

   }


   ~asignal()
   {

      if (m_psubparticle)
      {

         try
         {

            m_psubparticle->release();

         }
         catch (...)
         {


         }

      }

   }

   bool operator == (const enum_id & eid) const
   {

      return m_eid == eid;

   }


};



