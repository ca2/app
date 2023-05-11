//
// Created by camilo on 07/04/2023 22:48 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "audio_mixer.h"
#include "audio_mixer_user.h"
#include "acme/platform/system.h"


namespace aqua
{


   audio_mixer::audio_mixer()
   {


   }


   audio_mixer::~audio_mixer()
   {

   }


   ::aqua::audio_mixer_user * audio_mixer::audio_mixer_user()
   {

      return m_paudiomixeruser;

   }


   ::aqua::audio_mixer_user * audio_mixer::get_audio_mixer_user()
   {

      if (!m_paudiomixeruser)
      {

         defer_audio_mixer_user();

      }

      return m_paudiomixeruser;

   }


   void audio_mixer::defer_audio_mixer_user()
   {

      if (!m_paudiomixeruser)
      {

         auto pfactory = acmesystem()->factory("audio_mixer_user", "base");

         pfactory->__construct(this, m_paudiomixeruser);

      }

   }



} // namespace aqua