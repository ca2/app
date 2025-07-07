// Created by camilo on 2025-06-30 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/call.h"


class call
{
public:


   enum_call                     m_ecall;
   long long                     m_ll;
   long long                     m_ll2; // here you should be able to put a pointer that has stable lifetime
   ::subparticle *               m_psubparticle; // here there can lie a object with reference count lifetime


   call(enum_call ecall, long long ll = 0ll, long long ll2 = 0ll) :
      m_ecall(ecall),
      m_ll(ll),
      m_ll2(ll2),
      m_psubparticle(nullptr)
   {


   }


   call(enum_call ecall, long long ll, long long ll2, ::subparticle* psubparticle) :
      m_ecall(ecall),
      m_ll(ll),
      m_ll2(ll2),
      m_psubparticle(psubparticle)
   {

      m_psubparticle->increment_reference_count();

   }


   call(const call& call) :
      m_ecall(call.m_ecall),
      m_ll(call.m_ll),
      m_ll2(call.m_ll2),
      m_psubparticle(call.m_psubparticle)
   {

      m_psubparticle->increment_reference_count();

   }


   call(call&& call) :
      m_ecall(call.m_ecall),
      m_ll(call.m_ll),
      m_ll2(call.m_ll2),
      m_psubparticle(call.m_psubparticle)
   {

      call.m_ecall = (enum_call)0;
      call.m_psubparticle = nullptr;

   }


   ~call()
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


   bool operator == (enum_call ecall) const
   {

      return m_ecall == ecall;

   }


};



