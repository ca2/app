//
//  _.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/09/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/platform/system_setup.h"
#include "acme/prototype/prototype/factory.h"
////#include "acme/prototype/prototype/matter.h"
#include "acme/platform/application.h"
//
//
//
//
//CLASS_DECL_ACME void destroy_pointer(int_handle i)
//{
//
//   if(i >= 0)
//   {
//
//      ::close(i.m_i);
//
//   }
//
//}



static PFN_factory g_pfnFactoryApp = nullptr;


app_factory::app_factory(PFN_factory pfnFactory)
{

    g_pfnFactoryApp = pfnFactory;

}


::pointer<::platform::application>app_factory::new_app(::particle * pparticle)
{

   auto pfactory = __allocate ::factory::factory();

   g_pfnFactoryApp(pfactory);

   auto papp = pparticle->__øcreate<::platform::application>(pfactory);

   return papp;

}


