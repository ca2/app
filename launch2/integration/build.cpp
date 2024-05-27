//
//  build.cpp
//  integration_console_integration
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 26/07/2023 17:57
//
#include "framework.h"
#include "build.h"
#include "acme/platform/node.h"
#include "acme/platform/integration_context.h"


namespace console_integration
{


   build::build()
   {

   }


   build::~build()
   {

   }


   void build::initialize(::particle * pparticle)
   {

      ::particle::initialize(pparticle);

      acmenode()->integration_factory();
      
      __defer_construct(m_pcontext);

   }


} // namespace console_integration



