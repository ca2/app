// Created by camilo on 2021-11-01 17:06 BRT <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/platform/layer.h"


namespace aqua
{


   class CLASS_DECL_AQUA layer :
      virtual public acme::layer
   {
   public:


      ::static_object_factory < ::apex::system > m_factorySystem;

      
      layer();


   };


} // namespace aqua



