// Created by camilo on 2024-10-08 09:06 <3ThomasBorregaardSorensen!!
#include "framework.h"


post_procedure_continuation::post_procedure_continuation(::particle * pparticle, const ::procedure & procedure) :
   m_pparticleTarget(pparticle),
   m_procedure(procedure)
{

}


post_procedure_continuation & post_procedure_continuation::operator << (const ::procedure & procedure)
{

   if (!m_pprocedurea)
   {

      m_pparticleTarget->__construct_new(m_pprocedurea);

      m_pprocedurea->add(m_procedure);

   }

   m_pprocedurea->add(procedure);

   return *this;

}

post_procedure_continuation::~post_procedure_continuation()
{

   if (m_pprocedurea)
   {

      m_pparticleTarget->_post(m_pprocedurea);

   }
   else
   {

      m_pparticleTarget->_post(m_procedure);

   }

}
