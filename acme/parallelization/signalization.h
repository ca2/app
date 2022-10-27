//
// Created by camilo on 25/04/2021. ~08:00 <3Thomas Borregaard Sørensen
//
#pragma once


#include "acme/parallelization/manual_reset_event.h"
#include "acme/primitive/primitive/element.h"


namespace parallelization
{


   class CLASS_DECL_ACME signalization :
      virtual public ::element
   {
   public:



      manual_reset_event            m_evReady;
      ::pointer<::particle>         m_pparticleHold;


      signalization();
      ~signalization() override;


   };


} // namespace parallelization



