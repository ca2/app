//
// Created by camilo on 2022-10-22 19:05 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "action_context.h"
//#include "acme/primitive/collection/pointer_array.h"


void action_context::add(const ::particle * pparticle)
{

   if (!m_pparticlea)
   {

      m_pparticlea = __new(pointer_array < ::particle >);

   }
   
   m_pparticlea->add((::particle *)pparticle);

}


index action_context::find(const ::particle * pparticle) const
{

   return !m_pparticlea ? -1 : m_pparticlea->find_first(pparticle);

}


bool action_context::contains(const ::particle * pparticle) const
{

   return !m_pparticlea ? false : m_pparticlea->contains(pparticle);

}
