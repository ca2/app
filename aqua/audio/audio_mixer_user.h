//
// Created by camilo on 07/04/2023 22:48 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"

namespace user {class impact_kit;}

namespace aqua
{


   class CLASS_DECL_AQUA audio_mixer_user :
      virtual public ::acme::department
   {
   public:


      audio_mixer_user();
      ~audio_mixer_user() override;

      virtual ::pointer<::user::impact_kit>get_audio_control_impact_kit();

   };


} // namespace aqua


