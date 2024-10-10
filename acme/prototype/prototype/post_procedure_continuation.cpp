// Created by camilo on 2024-10-08 09:06 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/handler/sequence.h"


sequence_continuation::sequence_continuation(::particle * pparticle, enum_dispatch edispatch) :
   m_pparticleTarget(pparticle),
   m_edispatch(edispatch)
{

}


sequence_continuation::sequence_continuation(::particle * pparticle, enum_dispatch edispatch, const ::procedure & procedure) :
   m_pparticleTarget(pparticle),
   m_edispatch(edispatch),
   m_procedure(procedure)
{

}


sequence_continuation & sequence_continuation::operator << (const ::procedure & procedure)
{

   if (!m_psequence)
   {

      m_pparticleTarget->__construct_new(m_psequence);

      if (m_procedure)
      {

         m_psequence->add(m_procedure);

      }

   }

   m_psequence->add(procedure);

   return *this;

}


sequence_continuation::~sequence_continuation()
{

   if (m_psequence)
   {

      m_pparticleTarget->_call_procedure(m_edispatch, m_psequence);

   }
   else if(m_procedure)
   {

      m_pparticleTarget->_call_procedure(m_edispatch, m_procedure);

   }

}
