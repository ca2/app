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


      ::pointer < ::aqua::audio_mixer_user >          m_paudiomixeruser;


      audio_mixer();
      ~audio_mixer() override;


      virtual ::aqua::audio_mixer_user * audio_mixer_user();

      virtual ::aqua::audio_mixer_user * get_audio_mixer_user();

      virtual void defer_audio_mixer_user();


   };


} // namespace aqua


