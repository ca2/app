//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Soerensen
//
#pragma once


//#include "acme/prototype/prototype/pointer.h"
#include "acme/parallelization/manual_reset_happening.h"


namespace parallelization
{


   class CLASS_DECL_ACME signalization :
      virtual public ::particle
   {
   public:



      manual_reset_happening               m_happeningReady;
      ::particle_pointer         m_pparticleHold;


      signalization();
      ~signalization() override;


   };


} // namespace parallelization



