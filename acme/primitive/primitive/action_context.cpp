//
// Created by camilo on 2022-10-22 19:05 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


void action_context::add(const matter * pobject)
{

   if (!m_pobjecta) m_pobjecta = __new(pointer_array < ::matter >); m_pobjecta->add((::matter *)pobject);

}


index action_context::find(const matter * pobject) const
{

   return !m_pobjecta ? -1 : m_pobjecta->find_first(pobject);

}


bool action_context::contains(const matter * pobject) const
{

   return !m_pobjecta ? false : m_pobjecta->contains(pobject);

}
