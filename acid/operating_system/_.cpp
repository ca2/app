//
//  _.cpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 21/09/20.
//  Copyright (c) 2020 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "acid/platform/system_setup.h"
#include "acid/primitive/primitive/factory.h"
////#include "acid/primitive/primitive/matter.h"
#include "acid/platform/application.h"
//
//
//
//
//CLASS_DECL_ACID void destroy_pointer(int_handle i)
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


::pointer<::acid::application>app_factory::new_app(::particle * pparticle)
{

   auto pfactory = __allocate< ::factory::factory >();

   g_pfnFactoryApp(pfactory);

   auto papp = pparticle->__create<::acid::application>(pfactory);

   return papp;

}


