// Created by camilo on 2021-11-01 17:18 BRT <3ThomasBorregaardSoerensen!!
#pragma once


#include "acme/platform/layer.h"


namespace apex
{


   class CLASS_DECL_APEX layer :
      virtual public ::acme::layer
   {
   public:


      ::static_object_factory < ::apex::system > m_factorySystem;


      layer();


   };


} // namespace apex



