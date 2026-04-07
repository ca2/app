//
// Created by camilo on 2026-04-06.
//
#include "framework.h"
#include "acme/subsystem/particle.h"


namespace subsystem
{

   particle_interface::particle_interface(enum_particle eparticle):
           m_eparticle(eparticle)
   {

   }

   particle_interface::~particle_interface()
   {}



} // namespace subsystem




