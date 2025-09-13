// Created by camilo on 2025-06-30 02:10 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "pool.h"


pool_group::pool_group()
{


}


pool_group::~pool_group()
{


}


void pool_group::on_initialize_particle()
{

   defer_create_synchronization();

}


::particle_array* ongoing_particle_array_source::ongoing_particle_array()
{

   return nullptr;

}


void pool_group::call_ongoing(const ::call& call)
{

   _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

   auto pparticleaOngoing = m_pongoingparticlearraysource->ongoing_particle_array();

   for (auto& pparticleOngoing : *pparticleaOngoing)
   {

      pparticleOngoing->handle(call);

   }

}


::particle_array* pool_group::ongoing_particle_array()
{

   return m_pongoingparticlearraysource->ongoing_particle_array();

}



