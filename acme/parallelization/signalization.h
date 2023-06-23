//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Soerensen
//
#pragma once


#include "acme/primitive/primitive/particle.h"
//#include "acme/primitive/primitive/pointer.h"
#include "acme/parallelization/manual_reset_event.h"


namespace parallelization
{


   class CLASS_DECL_ACME signalization :
      virtual public ::particle
   {
   public:



      manual_reset_event               m_evReady;
      ::pointer < ::particle >         m_pparticleHold;


      signalization();
      ~signalization() override;


   };


} // namespace parallelization



