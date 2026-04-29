//
// Created by camilo on 2026-04-06.
//
#include "framework.h"
#include "subsystem/platform/particle.h"


   Particle::Particle(enum_particle eparticle):
           m_eparticle(eparticle)
   {

   }

   Particle::~Particle()
   {}


   ::Particle * Particle::_get_implementation()
   {

      return this;

   }


   Particle *Particle::_get_callback()
   {

      return this;

   }



   ::Particle * Particle::_get_implementation1()
   {

      return nullptr;

   }


   ::Particle *Particle::_get_callback1()
   {

      return nullptr;

   }
