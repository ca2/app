//
//  _.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/09/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acme/platform/system_setup.h"
#include "acme/primitive/primitive/factory.h"
////#include "acme/primitive/primitive/matter.h"
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


::pointer<::acme::application>app_factory::new_app(::particle * pparticle)
{

   auto pfactory = __allocate< ::factory::factory >();

   g_pfnFactoryApp(pfactory);

   auto papp = pfactory->create<::acme::application>(pparticle);

   return papp;

}


