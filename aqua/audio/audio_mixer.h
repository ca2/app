//
// Created by camilo on 07/04/2023 22:48 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace aqua
{


   class CLASS_DECL_AQUA audio_mixer :
      virtual public ::acme::department
   {
   public:





      audio_mixer();
      ~audio_mixer() override;


      virtual ::aqua::audio_mixer_userbase * audio_mixer_userbase();


   };


} // namespace aqua


