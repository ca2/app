//
// Created by camilo on 2026-04-06.
//
#include "framework.h"
#include "subsystem/particle.h"


   particle_base::particle_base(enum_particle eparticle):
           m_eparticle(eparticle)
   {

   }

   particle_base::~particle_base()
   {}


::particle_base * particle_base::get_implementation()
   {

      return this;

   }