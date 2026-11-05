//
// Created by camilo on 2026-04-06.
//
#include "platform.h"
#include "subsystem/platform/Particle.h"


namespace subsystem
{


   Particle::Particle(enum_particle eparticle) : m_eparticle(eparticle) {}

   Particle::~Particle() {}


   ::subsystem::Particle *Particle::_get_implementation() { return this; }


   Particle *Particle::_get_callback() { return this; }


   ::subsystem::Particle *Particle::_get_implementation1() { return nullptr; }


   ::subsystem::Particle *Particle::_get_callback1() { return nullptr; }


} // namespace subsystem
 


