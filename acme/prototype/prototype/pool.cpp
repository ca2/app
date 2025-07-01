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


void pool_group::call_ongoing(const ::call& call)
{

   _synchronous_lock synchronouslock(this->synchronization());

   auto particleaOngoing = ::transfer(m_particleaOngoing);

   for (auto& pparticleOngoing : particleaOngoing)
   {

      pparticleOngoing->handle(call);

   }

}




