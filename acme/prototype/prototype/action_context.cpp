//
// Created by camilo on 2022-10-22 19:05 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "action_context.h"
#include "acme/user/user/activation_token.h"
//#include "acme/prototype/collection/pointer_array.h"


void action_context::add(const ::particle * pparticle)
{

   if (!m_pparticlea)
   {

      m_pparticlea = __allocate pointer_array < ::particle > ();

   }
   
   m_pparticlea->add((::particle *)pparticle);

}


::collection::index action_context::find(const ::particle * pparticle) const
{

   return !m_pparticlea ? -1 : m_pparticlea->find_first(pparticle);

}


bool action_context::contains(const ::particle * pparticle) const
{

   return !m_pparticlea ? false : m_pparticlea->contains(pparticle);

}


::user::activation_token * action_context::user_activation_token()
{

   auto puseractivationtoken = m_puseractivationtoken;

   if (::is_set(puseractivationtoken))
   {

      return puseractivationtoken;

   }

   auto pmessage = m_pmessage;

   if (::is_null(pmessage))
   {

      return nullptr;

   }

   puseractivationtoken = pmessage->user_activation_token();

   if (::is_null(puseractivationtoken))
   {

      return nullptr;

   }

   return puseractivationtoken;

}