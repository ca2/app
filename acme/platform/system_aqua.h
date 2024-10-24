//
// Created by camilo on 2024-10-24 18:19 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "platform.h"
//#include "acme.h"
#include "context.h"
//#include "system_factory.h"
#include "application_flags.h"
#include "acme/constant/gender.h"
#include "acme/parallelization/_types.h"
#include "acme/prototype/collection/map.h"
#include "acme/prototype/prototype/factory.h"

namespace platform
{

   struct aqua_system_layer_t
   {
      ::pointer<::aqua::audio>                        m_paudio;

      ::pointer<::aqua::multimedia>                   m_pmultimedia;

      ::pointer<::aqua::audio_mixer>                  m_paudiomixer;

      ::pointer<::aqua::estamira>                     m_pestamira;



   };


   class CLASS_DECL_ACME aqua_system_layer
   {
   public:



   };



} // namespace platform

