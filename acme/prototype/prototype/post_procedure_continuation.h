// Created by camilo on 2024-10-08 08:45 <3ThomasBorregaardSorensen!!
#pragma once


using particle_pointer = ::pointer <  ::particle  >;


class CLASS_DECL_ACME post_procedure_continuation
{
public:
   
   
   ::procedure                      m_procedure;
   ::pointer < procedure_array >    m_pprocedurea;
   ::particle_pointer               m_pparticleTarget;

   post_procedure_continuation(::particle * pparticleTarget, const ::procedure & procedure);
   post_procedure_continuation & operator << (const ::procedure & procedure);
   ~post_procedure_continuation();

};
