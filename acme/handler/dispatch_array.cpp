// Created by camilo on 2024-10-08 09:06 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/handler/sequence.h"


dispatch_array2::dispatch_array2(::particle * pparticleDispatcher, enum_dispatch edispatch) :
   m_pparticleDispatcher(pparticleDispatcher),
   m_edispatch(edispatch)
{

}


dispatch_array2::dispatch_array2(::particle * pparticleDispatcher, enum_dispatch edispatch, const ::procedure & procedure) :
   m_pparticleDispatcher(pparticleDispatcher),
   m_edispatch(edispatch)
{

   operator <<(procedure);

}


dispatch_array2::dispatch_array2(const dispatch_array2 & dispatcha) : 
   m_pparticleDispatcher(dispatcha.m_pparticleDispatcher), 
   m_edispatch(dispatcha.m_edispatch), 
   procedure_array(dispatcha), 
   ::array_particle<::procedure_array_base>(dispatcha)
{


}


dispatch_array2 & dispatch_array2::operator << (const ::procedure & procedure)
{

   this->add(procedure);

   return *this;

}


void dispatch_array2::run()
{

   for (auto & procedure : *this)
   {

      try
      {

         procedure();

      }
      catch (...)
      {


      }

   }

}


void dispatch_array2::dispatch_this()
{

   if (m_edispatch == e_dispatch_fork)
   {

      ::cast < ::object > pobjectThis = m_pparticleDispatcher;

      pobjectThis->fork(allocateø dispatch_array2(*this));

   }
   else
   {

      m_pparticleDispatcher->dispatch(*this);

   }

}


dispatch_array2::~dispatch_array2()
{


}
